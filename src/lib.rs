//! Safe interface to [`DPDK`](https://www.dpdk.org/).

#![allow(clippy::missing_safety_doc)]
#![no_std]

extern crate alloc;
extern crate std;

use core::sync::atomic::Ordering;
use std::panic;

use alloc::vec::Vec;

pub mod pkt;
pub use deepeedeekay_sys as sys;
pub mod ffi;
pub mod log;
pub mod port;
pub mod rt;
pub mod util;

use util::{WithError, to_bool};

pub fn run<'env, F, T>(rt: rt::Runtime, f: F) -> Result<T, WithError<T, ffi::Error>>
where
    F: for<'rt> FnOnce(&'rt rt::MainCore<'rt>, Vec<port::Naive<'rt>>) -> T,
{
    let ports = (0..=sys::RTE_MAX_ETHPORTS)
        .filter_map(|id| {
            let call;
            match to_bool(call!(sys::rte_eth_dev_is_valid_port(id) in call)) {
                Ok(false) => None,
                Ok(true) => Some(unsafe { port::Naive::from_raw(port::Raw::from_raw(&rt, id)) }),
                Err(e) => panic!("{e}: {call}"),
            }
        })
        .collect();
    let main = unsafe { rt::MainCore::new(&rt) };
    let res = f(&main, ports);
    unsafe { sys::rte_eal_mp_wait_lcore() };

    // prefer to raise the first panic
    #[allow(static_mut_refs)]
    if let Some(Err(e)) = unsafe {
        rt::SLOTS
            .get_mut(rt::FIRST_PANIC.load(Ordering::Acquire))
            .and_then(|it| it.take())
    } {
        panic::resume_unwind(e)
    }

    #[allow(static_mut_refs)]
    for it in unsafe { rt::SLOTS.iter_mut() } {
        if let Some(Err(e)) = it.take() {
            panic::resume_unwind(e)
        }
    }
    match rt.cleanup() {
        Ok(()) => Ok(res),
        Err(error) => Err(WithError { with: res, error }),
    }
}
