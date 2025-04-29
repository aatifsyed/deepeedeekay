use alloc::{boxed::Box, collections::TryReserveError, ffi::CString, string::String};
use bstr::BStr;
use core::{
    alloc::Layout,
    borrow::Borrow,
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
                    assert!(dpdk_sys::$name < i32::MAX as u32);
                    match (dpdk_sys::$name as i32).checked_neg() {
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

/// A nul-terminated, UTF-8 buffer.
///
/// Any `nul`s that are [written](fmt::write) to this are replaced with [`char::REPLACEMENT_CHARACTER`].
#[derive(Default, Debug, Clone, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub struct SeeString(
    /// If [`!String::is_empty`](String::is_empty),
    /// this is guaranteed to meet the contract.
    String,
);

impl SeeString {
    fn try_push_str(&mut self, s: &str) -> Result<(), TryReserveError> {
        self.0.try_reserve(s.len())?;
        self.0.push_str(s);
        Ok(())
    }
    pub const fn new() -> Self {
        Self(String::new())
    }
    pub fn as_str(&self) -> &str {
        &self.0
    }
    pub fn as_cstr(&self) -> &CStr {
        if self.0.is_empty() {
            return c"";
        }
        let bytes = self.as_str().as_bytes();
        match cfg!(debug_assertions) {
            true => CStr::from_bytes_with_nul(bytes).unwrap(),
            false => unsafe { CStr::from_bytes_with_nul_unchecked(bytes) },
        }
    }
    pub fn clear(&mut self) {
        self.0.clear();
    }
}

impl fmt::Write for SeeString {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        const REPLACEMENT_STR: &str = "�";
        const TERMINATION_STR: &str = "\0";
        self.0.pop(); // pop the terminator.
        let res = (|| {
            let mut spans = s.split('\0').peekable();
            while let Some(span) = spans.next() {
                self.try_push_str(span)?;
                if spans.peek().is_some() {
                    self.try_push_str(REPLACEMENT_STR)?
                }
            }
            Ok::<_, TryReserveError>(())
        })();
        match (res, self.try_push_str(TERMINATION_STR)) {
            (Ok(()), Ok(())) => Ok(()),
            (Err(_), Ok(())) => Err(fmt::Error),
            (_, Err(_)) => {
                // rollback until we can add a terminator
                while self.0.pop().is_some() {
                    if self.try_push_str(TERMINATION_STR).is_ok() {
                        break;
                    }
                }
                Err(fmt::Error)
            }
        }
    }
}

impl FromStr for SeeString {
    type Err = Infallible;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut this = Self::new();
        match this.write_str(s) {
            Ok(()) => Ok(this),
            Err(_) => alloc::alloc::handle_alloc_error(Layout::for_value(s)), // close enough
        }
    }
}

impl fmt::Display for SeeString {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        self.as_str().fmt(f)
    }
}

impl From<SeeString> for String {
    fn from(value: SeeString) -> Self {
        value.0
    }
}

impl From<SeeString> for Box<str> {
    fn from(value: SeeString) -> Self {
        String::from(value).into_boxed_str()
    }
}

impl From<SeeString> for Box<CStr> {
    fn from(value: SeeString) -> Self {
        let raw = Box::into_raw(Box::<str>::from(value));
        unsafe { Box::from_raw(raw as _) }
    }
}

impl From<SeeString> for CString {
    fn from(value: SeeString) -> Self {
        match value.0.is_empty() {
            true => CString::default(),
            false => {
                let bytes = String::from(value).into_bytes();
                match cfg!(debug_assertions) {
                    true => CString::from_vec_with_nul(bytes).unwrap(),
                    false => unsafe { CString::from_vec_with_nul_unchecked(bytes) },
                }
            }
        }
    }
}

impl AsRef<str> for SeeString {
    fn as_ref(&self) -> &str {
        self.as_str()
    }
}

impl AsRef<CStr> for SeeString {
    fn as_ref(&self) -> &CStr {
        self.as_cstr()
    }
}

impl Borrow<str> for SeeString {
    fn borrow(&self) -> &str {
        self.as_str()
    }
}

impl Borrow<CStr> for SeeString {
    fn borrow(&self) -> &CStr {
        self.as_cstr()
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
