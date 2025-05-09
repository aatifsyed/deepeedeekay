use crate::{
    call, ffi, log, sys,
    util::{PhantomUnsend, cfor, konst::convert, neg},
};
use alloc::{
    boxed::Box,
    ffi::{CString, NulError},
    string::{String, ToString as _},
    vec,
    vec::Vec,
};
use core::{
    any::Any,
    ffi::{c_int, c_void},
    fmt,
    marker::PhantomData,
    mem,
    ops::Deref,
    panic::AssertUnwindSafe,
    ptr::NonNull,
    str::FromStr,
    sync::atomic::{AtomicUsize, Ordering},
};
use itertools::Itertools as _;
use std::panic;

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
        ffi::clear(); // catch a common usecase
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

#[derive(Debug, Default, Clone, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum Allocator {
    MountedHugepages {
        directory: Option<CString>,
    },
    #[cfg_attr(not(debug_assertions), default)]
    AnonymousHugepages,
    #[cfg_attr(debug_assertions, default)]
    Malloc,
}

impl FromStr for Allocator {
    type Err = ParseAllocatorError;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        Ok(match s {
            "malloc" => Self::Malloc,
            "anon-hugepages" => Self::AnonymousHugepages,
            "mounted-hugepages" => Self::MountedHugepages { directory: None },
            _ => match s.strip_prefix("mounted-hugepages:") {
                Some(rest) => match CString::new(rest) {
                    Ok(it) => Self::MountedHugepages {
                        directory: Some(it),
                    },
                    Err(e) => return Err(ParseAllocatorError(Some(e))),
                },
                None => return Err(ParseAllocatorError(None)),
            },
        })
    }
}

impl fmt::Display for Allocator {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Allocator::MountedHugepages { directory: None } => f.write_str("mounted-hugepages"),
            Allocator::MountedHugepages {
                directory: Some(dir),
            } => {
                f.write_str("mounted-hugepages:")?;
                let mut spans = dir.as_bytes().utf8_chunks().peekable();
                while let Some(span) = spans.next() {
                    f.write_str(span.valid())?;
                    if spans.peek().is_some() {
                        f.write_str("�")?
                    }
                }
                Ok(())
            }
            Allocator::AnonymousHugepages => f.write_str("anon-hugepages"),
            Allocator::Malloc => f.write_str("malloc"),
        }
    }
}

#[test]
fn parse_allocator() {
    #[track_caller]
    fn t(s: &str, expected: Allocator) {
        let actual = s.parse().unwrap();
        assert_eq!(expected, actual, "bad parse");
        assert_eq!(s, actual.to_string(), "bad print")
    }
    t("malloc", Allocator::Malloc);
    t("anon-hugepages", Allocator::AnonymousHugepages);
    t(
        "mounted-hugepages",
        Allocator::MountedHugepages { directory: None },
    );
    t(
        "mounted-hugepages:/some/dir",
        Allocator::MountedHugepages {
            directory: Some(c"/some/dir".into()),
        },
    );
}

#[derive(Debug)]
pub struct ParseAllocatorError(Option<NulError>);

impl fmt::Display for ParseAllocatorError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self.0 {
            Some(_) => f.write_str("Error parsing `mounted-hugepages:<dir>"),
            None => f.write_str("Expected one of `malloc`, `anon-hugepages`, `mounted-hugepages` or `mounted-hugepages:<dir>`"),
        }
    }
}
impl core::error::Error for ParseAllocatorError {
    fn source(&self) -> Option<&(dyn core::error::Error + 'static)> {
        self.0.as_ref().map(|x| x as _)
    }
}

#[derive(Debug)]
pub struct MainCore<'rt> {
    rt: &'rt Runtime,
    _unsend: PhantomUnsend,
}

impl<'rt> MainCore<'rt> {
    pub unsafe fn new(rt: &'rt Runtime) -> Self {
        Self {
            _unsend: PhantomUnsend::new(),
            rt,
        }
    }
    pub fn id(&self) -> LCoreId {
        LCoreId::current().unwrap()
    }
    pub fn workers(&self) -> impl use<> + Iterator<Item = LCoreId> {
        let skip_main = true as _;
        let wrap = false as _;
        cfor(
            unsafe { sys::rte_get_next_lcore(-1i32 as u32, skip_main, wrap) },
            move |it| it < sys::RTE_MAX_LCORE,
            move |it| unsafe { sys::rte_get_next_lcore(it, skip_main, wrap) },
        )
        .map(|raw| unsafe { LCoreId::new_unchecked(raw) })
    }

    pub fn spawn<F, T>(&self, lcore_id: LCoreId, f: F) -> JoinHandle<T>
    where
        F: FnOnce(WorkerCore<'rt>) -> T + Send,
        T: Any + Send,
    {
        match self.try_spawn(lcore_id, f) {
            Ok(it) => it,
            Err(e) => panic!("{e}"),
        }
    }
    pub fn try_spawn<F, T>(
        &self,
        LCoreId { raw: worker_id }: LCoreId,
        f: F,
    ) -> ffi::Result<JoinHandle<T>>
    where
        F: FnOnce(WorkerCore<'rt>) -> T + Send,
        T: Any + Send,
    {
        unsafe extern "C" fn _launch<'rt, F: FnOnce(WorkerCore<'rt>) -> T, T: Any + Send>(
            ptr: *mut c_void,
        ) -> c_int {
            let f = unsafe { Box::from_raw(ptr as *mut F) };
            let ix = unsafe { sys::rte_lcore_id() };
            assert_ne!(ix, sys::LCORE_ID_ANY);
            let ix = convert::u32_to_usize(ix);
            let res = match panic::catch_unwind(AssertUnwindSafe(|| {
                f(unsafe { WorkerCore::new(NonNull::dangling().as_ref()) })
            })) {
                Ok(it) => Ok(Box::new(it) as _),
                Err(e) => {
                    let first = match FIRST_PANIC.compare_exchange(
                        MAX_LCORE,
                        ix,
                        Ordering::Release,
                        Ordering::Relaxed,
                    ) {
                        Ok(_) => " (first)",
                        Err(_) => "",
                    };
                    let msg = match (e.downcast_ref::<&'static str>(), e.downcast_ref::<String>()) {
                        (Some(&it), _) => it,
                        (_, Some(it)) => it.as_str(),
                        _ => "Box<dyn Any>",
                    };
                    log::log(
                        log::Level::Err,
                        log::Type::User1,
                        format_args!("Thread on core {ix} panicked{first}: {msg}"),
                    );
                    Err(e)
                }
            };
            let clobbered = unsafe { mem::replace(&mut SLOTS[ix], Some(res)) };
            assert!(clobbered.is_none());
            0
        }

        let call;
        match call!(sys::rte_eal_remote_launch(
            Some(_launch::<F, T> as _),
            Box::into_raw(Box::new(f)) as *mut c_void,
            worker_id,
        ) in call)
        {
            0 => Ok(JoinHandle {
                worker_id,
                data: PhantomData,
            }),
            neg::EBUSY | neg::EPIPE => Err(ffi::Error(call)),
            other => panic!("unexpected return code {other} in {call}"),
        }
    }
    pub fn worker_busy(&self, LCoreId { raw: worker_id }: LCoreId) -> bool {
        match unsafe { sys::rte_eal_get_lcore_state(worker_id) } {
            sys::rte_lcore_state_t::WAIT => false,
            sys::rte_lcore_state_t::RUNNING => true,
        }
    }
    pub fn try_spawn_all<F, T>(&self, f: F) -> Result<(), SpawnError>
    where
        F: FnOnce(WorkerCore<'rt>) + Send + Clone,
    {
        for id in self.workers() {
            if self.worker_busy(id) {
                return Err(SpawnError);
            }
        }
        for id in self.workers() {
            let _jh = self.try_spawn(id, f.clone()).unwrap();
        }
        Ok(())
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, derive_more::Display)]
#[display("A worker core was busy")]
pub struct SpawnError;

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
    pub fn id(&self) -> LCoreId {
        LCoreId::current().unwrap()
    }
}

impl Deref for WorkerCore<'_> {
    type Target = Runtime;
    fn deref(&self) -> &Self::Target {
        self.rt
    }
}

#[derive(
    Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash, derive_more::Into, derive_more::Display,
)]
pub struct LCoreId {
    /// Valid core ID, i.e:
    /// - not [sys::LCORE_ID_ANY].
    /// - < [sys::RTE_MAX_LCORE].
    /// - live.
    raw: u32,
}

impl LCoreId {
    pub const unsafe fn new_unchecked(raw: u32) -> Self {
        assert!(raw <= sys::RTE_MAX_LCORE);
        Self { raw }
    }
    pub fn current() -> Option<Self> {
        let raw = unsafe { sys::rte_lcore_id() };
        if raw > sys::RTE_MAX_LCORE || raw == sys::LCORE_ID_ANY {
            None
        } else {
            Some(Self { raw })
        }
    }
    pub fn raw(&self) -> u32 {
        self.raw
    }
}

impl fmt::Debug for LCoreId {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_tuple("CoreId").field(&self.raw).finish()
    }
}

const MAX_LCORE: usize = convert::u32_to_usize(sys::RTE_MAX_LCORE);

pub(crate) static FIRST_PANIC: AtomicUsize = AtomicUsize::new(MAX_LCORE);

#[allow(clippy::type_complexity)]
pub(crate) static mut SLOTS: [Option<Result<Box<dyn Any + Send>, Box<dyn Any + Send>>>; MAX_LCORE] =
    [const { None }; MAX_LCORE];

pub struct JoinHandle<T> {
    worker_id: u32,
    data: PhantomData<fn() -> T>,
}

impl<T: Any> JoinHandle<T> {
    pub fn join(self) -> T {
        match self.try_join() {
            Ok(it) => it,
            Err(e) => panic::resume_unwind(e),
        }
    }
    pub fn try_join(self) -> Result<T, Box<dyn Any + Send>> {
        let ix = convert::u32_to_usize(self.worker_id);
        let call;
        match call!(
            sys::rte_eal_wait_lcore(self.worker_id) in call
        ) {
            0 => match unsafe { SLOTS[ix].take() }.unwrap() {
                Ok(it) => match it.downcast() {
                    Ok(it) => Ok(*it),
                    Err(_) => panic!("bad downcast in {call}"),
                },
                Err(e) => Err(e),
            },
            other => panic!("unexpected rc {other} in {call}"),
        }
    }
}
