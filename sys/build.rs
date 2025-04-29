use std::{
    collections::BTreeSet,
    fmt::Write as _,
    fs,
    process::{Command, Output},
};

use anyhow::{anyhow, bail, ensure, Context as _};
#[allow(deprecated)]
use bindgen::{Abi, CargoCallbacks};
use itertools::Itertools as _;
use serde::Deserialize;

fn main() -> anyhow::Result<()> {
    // discover and link dpdk
    // ----------------------

    let pkg_config::Library {
        include_paths,
        defines,
        ..
    } = pkg_config::Config::new()
        .exactly_version("24.07.0")
        .probe("libdpdk")?;

    // BUG: this isn't picked up by pkg-config by default
    println!("cargo::rustc-link-lib=rte_net_ring");

    let include_flags = include_paths
        .iter()
        .map(|path| format!("-I{}", path.display()));
    let define_flags = defines
        .iter()
        .map(|(k, v)| format!("-D{k}={}", v.as_deref().unwrap_or_default()));

    let shim_h_path = concat!(env!("CARGO_MANIFEST_DIR"), "/shim.h");
    let shim_c_path = concat!(env!("CARGO_MANIFEST_DIR"), "/shim.c");
    println!("cargo::rerun-if-changed={shim_h_path}");
    println!("cargo::rerun-if-changed={shim_c_path}");

    let bind_h_path = concat!(env!("CARGO_MANIFEST_DIR"), "/bind.h");
    println!("cargo::rerun-if-changed={bind_h_path}");

    // turn `static inline` functions into normal functions
    // ----------------------------------------------------

    let Output {
        status,
        stdout,
        stderr,
    } = Command::new(
        clang_sys::support::Clang::find(None, &[])
            .context("couldn't find clang binary")?
            .path,
    )
    .args(["-Xclang", "-ast-dump=json", "-fsyntax-only"])
    .args(include_flags.clone())
    .args(define_flags.clone())
    .arg("--")
    .arg(bind_h_path)
    .output()
    .context("couldn't exec clang")?;
    if !stderr.trim_ascii().is_empty() {
        bail!("clang stderr: {}", String::from_utf8_lossy(&stderr))
    }
    ensure!(status.success(), "clang exited with error");

    let Node { id: _, kind, inner } =
        serde_json::from_slice(&stdout).context("couldn't parse clang ast")?; // this bit is slow
    ensure!(kind == Clang::TranslationUnitDecl);

    let unstatic_h_path = concat!(env!("CARGO_MANIFEST_DIR"), "/generated/unstatic.h");
    let unstatic_c_path = concat!(env!("CARGO_MANIFEST_DIR"), "/generated/unstatic.c");
    let renames_path = concat!(env!("CARGO_MANIFEST_DIR"), "/generated/renames.rs");
    let bindings_path = concat!(env!("CARGO_MANIFEST_DIR"), "/generated/bindings.rs");

    let (names, unstatic_h_contents, unstatic_c_contents) = unstatic("deepeedeekay_", &inner)?;
    let unstatic_h_contents = format!("#include \"../bind.h\"\n{unstatic_h_contents}");
    // we're always clobbering the cache here, so cache ourselves.
    match fs::read_to_string(unstatic_h_path) {
        Ok(it) if it == unstatic_h_contents => {}
        _ => fs::write(unstatic_h_path, unstatic_h_contents)?,
    }
    fs::write(
        unstatic_c_path,
        format!("#include \"unstatic.h\"\n{unstatic_c_contents}"),
    )?;

    let renames = names.iter().fold(String::new(), |mut acc, el| {
        acc.write_fmt(format_args!("pub use deepeedeekay_{el} as {el};\n"))
            .unwrap();
        acc
    });
    fs::write(renames_path, renames)?;

    // generated bindings
    // ------------------

    bindgen::builder()
        .clang_arg(concat!("-I", env!("CARGO_MANIFEST_DIR")))
        .clang_args(include_flags.clone())
        .clang_args(define_flags.clone())
        .clang_arg("-fretain-comments-from-system-headers")
        .header(bind_h_path)
        .header(unstatic_h_path)
        .header(shim_h_path)
        .allowlist_function("deepeedeekay_.*")
        .allowlist_function("rte_.*")
        .allowlist_function("strerror")
        .allowlist_item("E.*")
        .blocklist_item("RTE_EAL_PMD_PATH") // depends on install location
        .allowlist_item("RTE_.*")
        .allowlist_item("SOCKET_ID_ANY")
        .allowlist_item("LCORE_ID_ANY")
        .blocklist_type("FILE")
        .blocklist_type("_IO.*")
        .override_abi(Abi::CUnwind, "rte_mempool_obj_cb_t")
        .override_abi(Abi::CUnwind, "rte_mempool_ctor_t")
        .raw_line("use ::libc::FILE;")
        .parse_callbacks(Box::new(ParseCallbacks {
            cargo: CargoCallbacks::new(),
            derives: vec![],
        }))
        .generate()
        .context("couldn't generate bindings")?
        .write_to_file(bindings_path)
        .context("couldn't write bindings")?;

    // Build the shim
    // --------------

    for (file, output) in [(unstatic_c_path, "unstatic"), (shim_c_path, "shim")] {
        cc::Build::new()
            .file(file)
            .emit_rerun_if_env_changed(true)
            .warnings(true)
            .warnings_into_errors(true)
            .flag("-Wno-deprecated-declarations")
            .flag("-mssse3")
            .flag("-mrtm")
            .includes(include_paths.iter())
            .compile(output);
    }

    Ok(())
}

#[derive(Debug)]
struct ParseCallbacks {
    cargo: CargoCallbacks,
    derives: Vec<String>,
}

impl bindgen::callbacks::ParseCallbacks for ParseCallbacks {
    fn header_file(&self, filename: &str) {
        self.cargo.header_file(filename);
    }
    fn include_file(&self, filename: &str) {
        self.cargo.include_file(filename);
    }
    fn read_env_var(&self, key: &str) {
        self.cargo.read_env_var(key);
    }
    fn add_derives(&self, info: &bindgen::callbacks::DeriveInfo<'_>) -> Vec<String> {
        let _ = info;
        self.derives.clone()
    }
}

/// Walk the AST, generating wrappers for `static inline` functions.
///
/// Returns `([original] names, header, implementation)`
fn unstatic<'a>(
    prefix: &str,
    nodes: &'a [Node],
) -> anyhow::Result<(BTreeSet<&'a str>, String, String)> {
    let mut seen = BTreeSet::new();
    let mut header = String::new();
    let mut implementation = String::new();
    for Node { id: _, kind, inner } in nodes {
        if let Clang::FunctionDecl {
            name,
            inline,
            r#type: Type { qual_type },
            storage_class,
            loc:
                clang_ast::SourceLocation {
                    spelling_loc,
                    expansion_loc,
                },
        } = kind
        {
            if name.starts_with("rte_")
                && matches!(inline, Some(true))
                && matches!(storage_class, Some(StorageClass::Static))
                && matches!(
                    expansion_loc,
                    Some(clang_ast::BareSourceLocation {
                        included_from: Some(clang_ast::IncludedFrom {
                            included_from: None,
                            file: _
                        }),
                        ..
                    })
                )
                && matches!(
                    spelling_loc,
                    Some(clang_ast::BareSourceLocation {
                        included_from: Some(clang_ast::IncludedFrom {
                            included_from: None,
                            file: _
                        }),
                        ..
                    })
                )
                && seen.insert(name.as_str())
            {
                let Some((returns, _)) = qual_type.split_once('(') else {
                    bail!("qual_type={qual_type}")
                };
                let params = inner
                    .iter()
                    .filter_map(|it| match &it.kind {
                        Clang::ParmVarDecl {
                            name,
                            r#type: Type { qual_type },
                        } => match name.as_deref() {
                            Some(name) => Some(Ok((name, qual_type))),
                            None => Some(Err(anyhow!(
                                "non-extern FunctionDecl with unnamed ParmValDecl"
                            ))),
                        },
                        _ => None,
                    })
                    .collect::<Result<Vec<_>, _>>()?;
                let param_decl = params
                    .iter()
                    .map(|(name, ty)| format!("{ty} {name}"))
                    .join(", ");
                let param_fwd = params.iter().map(|(name, _)| name).join(", ");

                let mut comment = String::new();
                for node in inner {
                    build_comment(&mut comment, node);
                }

                header
                    .write_fmt(format_args!(
                        "\n/**{comment}*/\n{returns} {prefix}{name}({param_decl});"
                    ))
                    .unwrap();
                implementation
                    .write_fmt(format_args!(
                    "\n{returns} {prefix}{name}({param_decl}) {{ return {name}({param_fwd}); }}"
                ))
                    .unwrap();
            }
        }
    }
    Ok((seen, header, implementation))
}

fn build_comment(s: &mut String, node: &Node) {
    match &node.kind {
        Clang::FullComment => {}
        Clang::ParagraphComment => s.push('\n'),
        Clang::TextComment { text } => s.push_str(text),
        Clang::ParamCommandComment { param, direction } => {
            s.push('\n');
            s.push_str({
                match direction {
                    Direction::In => "in",
                    Direction::Out => "out",
                    Direction::Inout => "inout",
                }
            });
            s.push_str(" param ");
            s.push_str(param);
        }
        Clang::BlockCommandComment { name } => {
            s.push('\n');
            s.push_str(name);
        }
        _ => {}
    }
    for node in &node.inner {
        build_comment(s, node);
    }
}

type Node = clang_ast::Node<Clang>;

#[derive(Debug, Deserialize, PartialEq, Eq)]
enum Clang {
    TranslationUnitDecl,
    ParmVarDecl {
        name: Option<String>,
        r#type: Type,
    },
    FunctionDecl {
        name: String,
        inline: Option<bool>,
        r#type: Type,
        #[serde(rename = "storageClass")]
        storage_class: Option<StorageClass>,
        loc: clang_ast::SourceLocation,
    },
    FullComment,
    ParagraphComment,
    TextComment {
        text: String,
    },
    ParamCommandComment {
        param: String,
        direction: Direction,
    },
    BlockCommandComment {
        name: String,
    },
    Other,
}

#[derive(Debug, Deserialize, PartialEq, Eq, Default)]
#[serde(rename_all = "camelCase")]
struct Type {
    qual_type: String,
}

#[derive(Debug, Deserialize, PartialEq, Eq, Default)]
#[serde(rename_all = "lowercase")]
enum StorageClass {
    Static,
    #[serde(other)]
    #[default]
    Other,
}

#[derive(Debug, Deserialize, PartialEq, Eq)]
#[serde(rename_all = "lowercase")]
enum Direction {
    In,
    Out,
    #[serde(rename = "in,out")]
    Inout,
}
