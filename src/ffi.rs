//! Report errors over the FFI boundary with [`sys`].

use crate::sys;
use alloc::boxed::Box;
use core::{ffi::CStr, fmt};
use std::io;

/// Clear the thread-local errors.
pub fn clear() {
    unsafe {
        *sys::rte_errno_location() = 0;
        *sys::errno_location() = 0;
    }
}

pub type Result<T> = core::result::Result<T, Error>;

/// Error making an FFI call.
#[derive(Debug)]
pub struct Error(pub Call<'static>);

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_fmt(format_args!("Error in {}", self.0))
    }
}

impl From<Call<'static>> for Error {
    fn from(value: Call<'static>) -> Self {
        Self(value)
    }
}

impl From<Error> for Call<'static> {
    fn from(Error(value): Error) -> Self {
        value
    }
}

impl core::error::Error for Error {}

/// Will allocate
impl From<Error> for io::Error {
    fn from(value: Error) -> Self {
        match (
            io::Error::from_raw_os_error(value.0.rte_errno).kind(),
            io::Error::from_raw_os_error(value.0.errno).kind(),
        ) {
            (kind @ io::ErrorKind::Other, io::ErrorKind::Other)
            | (kind, io::ErrorKind::Other)
            | (_, kind) => io::Error::new(kind, value),
        }
    }
}

/// Record of an FFI call.
pub struct Call<'a> {
    pub source: &'a Source<'a>,
    /// Debug-formatted arguments and return types.
    pub diags: Box<str>,
    pub backtrace: std::backtrace::Backtrace,
    pub rte_errno: i32,
    pub errno: i32,
}

impl fmt::Debug for Call<'_> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("Call")
            .field("source", &self.source)
            .field("diags", &self.diags)
            .field("backtrace", &self.backtrace)
            .field(
                "rte_errno",
                &format_args!(
                    "{} ({})",
                    self.rte_errno,
                    unsafe { CStr::from_ptr(sys::rte_strerror(self.rte_errno)) }
                        .to_bytes()
                        .escape_ascii(),
                ),
            )
            .field(
                "errno",
                &format_args!(
                    "{} ({})",
                    self.errno,
                    io::Error::from_raw_os_error(self.errno)
                ),
            )
            .finish()
    }
}

impl fmt::Display for Call<'_> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let Call {
            ref diags,
            rte_errno,
            errno,
            source:
                Source {
                    snippet,
                    file,
                    line,
                    column,
                },
            ref backtrace,
        } = *self;
        f.write_fmt(format_args!("call `{snippet}`"))?;
        if !diags.is_empty() {
            f.write_fmt(format_args!(" ({diags})"))?
        }
        f.write_fmt(format_args!(
            " at {file}:{line}:{column}. `rte_errno` was {rte_errno} ({}) and `errno` was {errno} ({}).",
            unsafe { CStr::from_ptr(sys::rte_strerror(rte_errno)) }.to_bytes().escape_ascii(),
            io::Error::from_raw_os_error(errno)
        ))?;
        f.write_fmt(format_args!(" backtrace: {backtrace}"))?;
        Ok(())
    }
}

/// Source code location and snippet of a foreign function call.
#[derive(Default, Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub struct Source<'a> {
    /// Snippet of source code.
    pub snippet: &'a str,
    /// Path the file in the source.
    pub file: &'a str,
    /// Line number in [`Self::file`].
    pub line: u32,
    /// Column number in [`Self::file`].
    pub column: u32,
}

#[macro_export]
macro_rules! call {
    (sys::$func:ident($($arg0:expr $(, $argn:expr)*)? $(,)?) in $call:ident) => {{
        use ::core::{concat, stringify, format_args, fmt, column, file, line, debug_assert_eq, default::Default, convert::From};
        let source = const { &$crate::ffi::Source {
            snippet: concat!(
                stringify!($func)
                , "("
                $(, stringify!($arg0)
                    $(, ", ", stringify!($argn))*
                )*
                , ")"
            ),
            column: column!(),
            file: file!(),
            line: line!(),
        }};
        unsafe {
            debug_assert_eq!(*$crate::sys::rte_errno_location(), 0, "rte_errno should be clear before call");
            debug_assert_eq!(*$crate::sys::errno_location(), 0, "errno should be clear before call");
        }
        let mut diags = $crate::util::MemString(Default::default());
        #[allow(unused_unsafe, clippy::macro_metavars_in_unsafe)]
        let ret = unsafe {
            $crate::sys::$func($(
                {
                    let arg = $arg0;
                    let _ = fmt::write(&mut diags, format_args!("{:?}", arg));
                    arg
                }
                $(, {
                    let arg = $argn;
                    let _ = fmt::write(&mut diags, format_args!(", {:?}", arg));
                    arg
                })*
            )*)
        };
        let _ = fmt::write(&mut diags, format_args!(" -> {:?}", ret));
        let (rte_errno, errno) = unsafe {(
            *$crate::sys::rte_errno_location(),
            *$crate::sys::errno_location(),
        )};
        $crate::ffi::clear();
        #[allow(unused_assignments)]
        {
            $call = $crate::ffi::Call {
                diags: From::from(diags.0),
                backtrace: ::std::backtrace::Backtrace::capture(),
                source,
                rte_errno,
                errno,
            }
        }
        ret
    }};
    (sys::$func:ident($($arg0:expr $(, $argn:expr)*)? $(,)?)) => {{
        use ::core::debug_assert_eq;
        unsafe {
            debug_assert_eq!(*$crate::sys::rte_errno_location(), 0, "rte_errno should be clear before call");
            debug_assert_eq!(*$crate::sys::errno_location(), 0, "errno should be clear before call");
        }
        #[allow(unused_unsafe, clippy::macro_metavars_in_unsafe)]
        let ret = unsafe {
            $crate::sys::$func($($arg0 $(,$argn)*)*)
        };
        $crate::ffi::clear();
        ret
    }};
}
