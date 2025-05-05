use alloc::string::String;
use bstr::BStr;
use core::{
    alloc::Layout,
    convert::Infallible,
    ffi::{CStr, c_char, c_void},
    fmt::{self, Write},
    marker::PhantomData,
    slice,
    str::FromStr,
};

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash, Default)]
pub struct PhantomUnsend(PhantomData<*mut c_void>);
impl PhantomUnsend {
    pub const fn new() -> Self {
        Self(PhantomData)
    }
}

#[cfg(test)]
static_assertions::assert_not_impl_any!(PhantomUnsend: Send);

/// Return [`None`] if `ptr` is null.
///
/// # Safety
/// - See [`CStr::from_ptr`]
pub const unsafe fn cstr<'a>(ptr: *const c_char) -> Option<&'a CStr> {
    match ptr.is_null() {
        true => None,
        false => Some(unsafe { CStr::from_ptr(ptr) }),
    }
}

pub fn bstr_till_nul<const N: usize>(buf: &[c_char; N]) -> &BStr {
    let buf = &buf[..];
    let buf = unsafe { slice::from_raw_parts(buf.as_ptr().cast::<u8>(), buf.len()) };
    match CStr::from_bytes_until_nul(buf) {
        Ok(it) => BStr::new(it.to_bytes()),
        Err(_) => BStr::new(buf),
    }
}

/// `true` if `t` is `1`.
/// `false` if `t` is `0`.
///
/// Else, an [`Err`].
#[track_caller]
pub fn to_bool<T: num::Zero + num::One + fmt::Display + PartialEq>(
    t: T,
) -> Result<bool, ToBoolError<T>> {
    match (t.is_one(), t.is_zero()) {
        (true, false) => Ok(true),
        (false, true) => Ok(false),
        (true, true) => unreachable!("bad impl of num::Zero, num::One"),
        (false, false) => Err(ToBoolError(t)),
    }
}

#[derive(Debug)]
pub struct ToBoolError<T>(pub T);

impl<T: fmt::Display> fmt::Display for ToBoolError<T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "invalid bool `{}`, expected `0` or `1`", self.0)
    }
}

impl<T: fmt::Display + fmt::Debug> core::error::Error for ToBoolError<T> {}

/// Negative error codes for match arms
pub mod neg {
    macro_rules! neg {
        ($($name:ident),* $(,)?) => {
            $(
                pub const $name: i32 = {
                    assert!(crate::sys::$name < i32::MAX as u32);
                    match (crate::sys::$name as i32).checked_neg() {
                        Some(it) => it,
                        None => panic!()
                    }
                };
            )*
        };
    }
    neg!(
        EFAULT, ENOENT, ENOBUFS, ENOTSUP, EINVAL, ENOMEM, ENODEV, EIO, EAGAIN, EOVERFLOW
    );
}

/// Implementor of [`fmt::Write`] which returns [`fmt::Error`] on allocation failure.
#[derive(Default, Debug, Clone, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub struct MemString(pub String);

impl fmt::Write for MemString {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        let Self(inner) = self;
        inner
            .try_reserve(s.len())
            .map_err(|_| fmt::Error)
            .and_then(|()| inner.write_str(s))
    }
}

impl fmt::Display for MemString {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        self.0.fmt(f)
    }
}
impl From<String> for MemString {
    fn from(value: String) -> Self {
        Self(value)
    }
}
impl From<MemString> for String {
    fn from(MemString(value): MemString) -> Self {
        value
    }
}
impl FromStr for MemString {
    type Err = Infallible;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut this = Self::default();
        match this.write_str(s) {
            Ok(()) => Ok(this),
            Err(_) => alloc::alloc::handle_alloc_error(Layout::for_value(s)),
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub struct WithError<T, E> {
    pub with: T,
    pub error: E,
}

impl<T, E: fmt::Display> fmt::Display for WithError<T, E> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        self.error.fmt(f)
    }
}

impl<T: fmt::Debug, E: core::error::Error> core::error::Error for WithError<T, E> {
    fn source(&self) -> Option<&(dyn core::error::Error + 'static)> {
        self.error.source()
    }
}

#[derive(Clone, Copy)]
#[repr(transparent)]
pub struct FmtFn<F = fn(fmt::Formatter<'_>) -> fmt::Result>(pub F);

impl<F: Fn(&mut fmt::Formatter<'_>) -> fmt::Result> FmtFn<F> {
    pub fn new(f: F) -> Self {
        Self(f)
    }
}

macro_rules! do_impl {
    ($($trait:ident),* $(,)?) => {
        $(
            impl<F: Fn(&mut fmt::Formatter) -> fmt::Result> fmt::$trait for FmtFn<F> {
                fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
                    (self.0)(f)
                }
            }
        )*
    };
}

do_impl!(
    Binary, Debug, Display, LowerExp, LowerHex, Octal, Pointer, UpperExp, UpperHex
);
