use crate::{call, ffi, util::PhantomUnsend};
use alloc::{ffi::CString, string::ToString as _, vec, vec::Vec};
use core::{mem, ops::Deref};
use itertools::Itertools as _;

#[cfg(test)]
pub fn test() -> &'static Runtime {
    use std::sync::LazyLock;

    static RUNTIME: LazyLock<Runtime> = LazyLock::new(|| {
        Runtime::new(
            c"test-runtime",
            Args {
                allocator: Allocator::Malloc,
                ..Default::default()
            },
        )
        .unwrap()
    });
    &RUNTIME
}

/// Represents an initialized DPDK runtime, a.k.a EAL.
///
/// Only one of these may be live at any one time.
#[derive(Debug)]
pub struct Runtime(());

impl Runtime {
    pub fn new(name: impl Into<CString>, args: Args) -> Result<Self, ffi::Error> {
        let mut cli_args = vec![name.into()];
        args.extend_into(&mut cli_args);
        Self::from_cli(cli_args)
    }
    /// # Safety
    /// - [`rte_eal_init`](crate::sys::rte_eal_init) must have been called successfully.
    /// - Only one of these structs may exist.
    pub const unsafe fn new_unchecked() -> Self {
        Self(())
    }
    /// # Panics
    /// - If the number of args overflows `c_int`.
    pub fn from_cli(args: Vec<CString>) -> Result<Self, ffi::Error> {
        let mut args = args
            .iter()
            .map(|it| it.as_ptr().cast_mut())
            .collect::<Vec<_>>();
        let argc = args.len().try_into().unwrap();
        let call;
        match call!(sys::rte_eal_init(argc, args.as_mut_ptr()) in call) {
            -1 => Err(ffi::Error(call)),
            _ => Ok(unsafe { Self::new_unchecked() }),
        }
    }
    pub fn cleanup(self) -> Result<(), ffi::Error> {
        mem::forget(self);
        let call;
        match call!(sys::rte_eal_cleanup() in call) {
            0 => Ok(()),
            _ => Err(ffi::Error(call)),
        }
    }
}

impl Drop for Runtime {
    fn drop(&mut self) {
        call!(sys::rte_eal_cleanup());
    }
}

#[derive(Debug, Default, Clone)]
pub struct Args {
    pub cores: Option<Vec<u8>>,
    pub main_core: Option<u8>,
    pub vdevs: Vec<CString>,
    pub log_levels: Vec<CString>,
    pub trace: Vec<CString>,
    pub telemetry: Option<bool>,
    pub allocator: Allocator,
}

impl Args {
    pub fn extend_into<T: Extend<CString>>(self, it: &mut T) {
        let Self {
            cores,
            main_core,
            vdevs,
            log_levels,
            trace,
            telemetry,
            allocator,
        } = self;

        if let Some(cores) = cores {
            it.extend([
                c"-l".into(),
                CString::new(cores.iter().join(","))
                    .expect("formatting numbers and commas should not produce NUL"),
            ])
        }
        if let Some(main_core) = main_core {
            it.extend([
                c"--main-lcore".into(),
                CString::new(main_core.to_string())
                    .expect("formatting number should not produce NUL"),
            ])
        }
        for vdev in vdevs {
            it.extend([c"--vdev".into(), vdev])
        }
        for log_level in log_levels {
            it.extend([c"--log-level".into(), log_level])
        }
        for trace in trace {
            it.extend([c"--trace".into(), trace])
        }
        if let Some(telementry) = telemetry {
            match telementry {
                true => it.extend([c"--telemetry".into()]),
                false => it.extend([c"--no-telemetry".into()]),
            }
        }
        match allocator {
            Allocator::MountedHugepages { directory: None } => {}
            Allocator::MountedHugepages {
                directory: Some(directory),
            } => it.extend([c"--huge-dir".into(), directory]),
            Allocator::AnonymousHugepages => it.extend([c"--in-memory".into()]),
            Allocator::Malloc => it.extend([c"--no-huge".into()]),
        }
    }
}

#[derive(Debug, Default, Clone)]
pub enum Allocator {
    MountedHugepages {
        directory: Option<CString>,
    },
    #[default]
    AnonymousHugepages,
    Malloc,
}

#[derive(Debug)]
pub struct MainCore<'rt> {
    rt: &'rt Runtime,
    _unsend: PhantomUnsend,
}

impl<'rt> MainCore<'rt> {
    pub const unsafe fn new(rt: &'rt Runtime) -> Self {
        Self {
            _unsend: PhantomUnsend::new(),
            rt,
        }
    }
}

impl Deref for MainCore<'_> {
    type Target = Runtime;
    fn deref(&self) -> &Self::Target {
        self.rt
    }
}

#[derive(Debug)]
pub struct WorkerCore<'rt> {
    rt: &'rt Runtime,
    _unsend: PhantomUnsend,
}

impl<'rt> WorkerCore<'rt> {
    pub const unsafe fn new(rt: &'rt Runtime) -> Self {
        Self {
            _unsend: PhantomUnsend::new(),
            rt,
        }
    }
}

impl Deref for WorkerCore<'_> {
    type Target = Runtime;
    fn deref(&self) -> &Self::Target {
        self.rt
    }
}
