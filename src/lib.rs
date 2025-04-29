//! Safe interface to [`DPDK`](https://www.dpdk.org/).

#![allow(clippy::missing_safety_doc)]
#![no_std]

extern crate alloc;
extern crate std;

use alloc::vec::Vec;

pub mod pkt;
pub use deepeedeekay_sys as sys;
pub mod ffi;
pub mod log;
pub mod port;
pub mod rt;
pub mod util;

use port::{Naive, Raw};

pub fn run(
    rt: rt::Runtime,
    f: impl for<'rt> FnOnce(rt::MainCore<'rt>, Vec<port::Naive<'rt>>),
) -> ffi::Result<()> {
    let ports = (0..=sys::RTE_MAX_ETHPORTS)
        .filter_map(|id| {
            let call;
            match util::to_bool(call!(sys::rte_eth_dev_is_valid_port(id) in call)) {
                Ok(false) => None,
                Ok(true) => Some(unsafe { Naive::from_raw(Raw::from_raw(&rt, id)) }),
                Err(e) => panic!("{e}: {call}"),
            }
        })
        .collect();
    f(unsafe { rt::MainCore::new(&rt) }, ports);
    rt.cleanup()
}
