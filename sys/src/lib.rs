#[allow(
    clippy::all,
    deref_nullptr,
    improper_ctypes,
    non_camel_case_types,
    non_snake_case,
    non_upper_case_globals
)]
#[path = "../generated/bindings.rs"]
mod bindings;
use core::fmt;

pub use bindings::*;

include!("../generated/renames.rs");

pub use bindings::{
    deepeedeekay_errno_location as errno_location,
    deepeedeekay_pktmbuf_data_len as pktmbuf_data_len,
    deepeedeekay_pktmbuf_pkt_len as pktmbuf_pkt_len,
    deepeedeekay_rte_errno_location as rte_errno_location,
    deepeedeekay_rte_pktmbuf_mtod as rte_pktmbuf_mtod,
    deepeedeekay_rte_pktmbuf_mtod_offset as rte_pktmbuf_mtod_offset,
};

pub const RTE_MAX_ETHPORTS: u16 = bindings::RTE_MAX_ETHPORTS as u16;

impl fmt::Debug for rte_eth_conf__bindgen_ty_2 {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("rte_eth_conf__bindgen_ty_2")
            .finish_non_exhaustive()
    }
}

impl fmt::Debug for rte_eth_conf {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("rte_eth_conf")
            .field("link_speeds", &self.link_speeds)
            .field("rxmode", &self.rxmode)
            .field("txmode", &self.txmode)
            .field("lpbk_mode", &self.lpbk_mode)
            .field("rx_adv_conf", &self.rx_adv_conf)
            .field("tx_adv_conf", &self.tx_adv_conf)
            .field("dcb_capability_en", &self.dcb_capability_en)
            .field("intr_conf", &self.intr_conf)
            .finish()
    }
}

#[test]
fn test() {
    let version = unsafe { core::ffi::CStr::from_ptr(rte_version()) }.to_string_lossy();
    println!("{}", version);
}
