//! Packet data enters and exits the application through ports.

use core::{fmt, marker::PhantomData, mem, ptr};

use crate::{
    call, ffi, pkt,
    rt::Runtime,
    sys,
    util::{WithError, bstr_till_nul, cstr, neg, to_bool},
};

use alloc::vec::Vec;

/// A live port in the EAL.
#[repr(transparent)]
pub struct Raw<'rt> {
    id: u16,
    life: PhantomData<&'rt Runtime>,
}

impl fmt::Debug for Raw<'_> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let mut f = f.debug_struct("Port");
        f.field("id", &self.id);
        if let Some(info) = self.info() {
            f.field("info", &Fmt(info));
        }
        f.finish_non_exhaustive()
    }
}

struct Fmt<T>(T);

impl fmt::Debug for Fmt<sys::rte_eth_dev_info> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        #[expect(unused_variables)]
        let sys::rte_eth_dev_info {
            device,
            driver_name,
            if_index,
            min_mtu,
            max_mtu,
            dev_flags,
            min_rx_bufsize,
            max_rx_bufsize,
            max_rx_pktlen,
            max_lro_pkt_size,
            max_rx_queues,
            max_tx_queues,
            max_mac_addrs,
            max_hash_mac_addrs,
            max_vfs,
            max_vmdq_pools,
            rx_seg_capa,
            rx_offload_capa,
            tx_offload_capa,
            rx_queue_offload_capa,
            tx_queue_offload_capa,
            reta_size,
            hash_key_size,
            rss_algo_capa,
            flow_type_rss_offloads,
            default_rxconf,
            default_txconf,
            vmdq_queue_base,
            vmdq_queue_num,
            vmdq_pool_base,
            rx_desc_lim,
            tx_desc_lim,
            speed_capa,
            nb_rx_queues,
            nb_tx_queues,
            max_rx_mempools,
            default_rxportconf,
            default_txportconf,
            dev_capa,
            switch_info,
            err_handle_mode,
            reserved_64s,
            reserved_ptrs,
        } = self.0;
        let mut f = f.debug_struct("rte_eth_dev_info");
        if let Some(ref it) = unsafe { cstr(driver_name) } {
            f.field("driver_name", it);
        }
        if let Some(it) = unsafe { device.as_ref() } {
            f.field("device", &Fmt(it));
        }

        f.field("switch_info", &Fmt(switch_info));

        f.finish_non_exhaustive()
    }
}

impl fmt::Debug for Fmt<&sys::rte_device> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let mut f = f.debug_struct("rte_device");
        let this = self.0;
        if let Some(ref it) = unsafe { cstr(sys::rte_dev_name(this)) } {
            f.field("name", it);
        }
        if let Some(ref it) = unsafe { cstr(sys::rte_dev_bus_info(this)) } {
            f.field("bus_info", it);
        }
        if let Some(it) = unsafe { sys::rte_dev_devargs(this).as_ref() } {
            f.field("devargs", &Fmt(it));
        }
        f.field(
            "is_probed",
            &to_bool(unsafe { sys::rte_dev_is_probed(this) }).unwrap(),
        )
        .field("numa_node", &unsafe { sys::rte_dev_numa_node(this) })
        .finish_non_exhaustive()
    }
}

impl fmt::Debug for Fmt<sys::rte_eth_switch_info> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let sys::rte_eth_switch_info {
            name,
            domain_id,
            port_id,
            rx_domain,
        } = self.0;
        let mut f = f.debug_struct("rte_eth_switch_info");
        if let Some(ref it) = unsafe { cstr(name) } {
            f.field("name", it);
        }
        for (name, value) in [
            ("domain_id", domain_id),
            ("port_id", port_id),
            ("rx_domain", rx_domain),
        ] {
            if value != 0 {
                f.field(name, &value);
            }
        }
        f.finish_non_exhaustive()
    }
}

impl fmt::Debug for Fmt<&sys::rte_devargs> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        #[expect(unused_variables)]
        let sys::rte_devargs {
            next: _,
            type_,
            policy,
            name,
            __bindgen_anon_1,
            bus,
            cls,
            bus_str,
            cls_str,
            data,
        } = *self.0;

        #[derive(Debug)]
        enum Policy {
            Allowed,
            Blocked,
            #[expect(dead_code)]
            Unknown(u32),
        }

        impl From<u32> for Policy {
            fn from(value: u32) -> Self {
                match value {
                    sys::rte_dev_policy_RTE_DEV_ALLOWED => Self::Allowed,
                    sys::rte_dev_policy_RTE_DEV_BLOCKED => Self::Blocked,
                    other => Self::Unknown(other),
                }
            }
        }

        let mut f = f.debug_struct("rte_devargs");
        f.field("name", &bstr_till_nul(&name))
            .field("type", &type_)
            .field("policy", &Policy::from(policy));
        if let Some(ref it) = unsafe { cstr(bus_str) } {
            f.field("bus_str", it);
        }
        if let Some(ref it) = unsafe { cstr(cls_str) } {
            f.field("cls_str", it);
        }
        if let Some(ref it) = unsafe { cstr(__bindgen_anon_1.drv_str) } {
            f.field("drv_str", it);
        }
        if let Some(ref it) = unsafe { cstr(data) } {
            f.field("data", it);
        }
        f.finish_non_exhaustive()
    }
}

impl<'rt> Raw<'rt> {
    pub unsafe fn from_raw(rt: &'rt Runtime, id: u16) -> Self {
        let _ = rt;
        Self {
            id,
            life: PhantomData,
        }
    }
    #[doc(alias = "id")]
    pub fn raw(&self) -> u16 {
        self.id
    }
    pub fn info(&self) -> Option<sys::rte_eth_dev_info> {
        let mut info = unsafe { mem::zeroed() };
        let call;
        #[allow(clippy::wildcard_in_or_patterns)]
        match call!(
            sys::rte_eth_dev_info_get(self.id, &mut info) in call)
        {
            0 => Some(info),
            neg::ENOTSUP => None,
            neg::ENODEV => panic!("stale port id in {call}"),
            neg::EINVAL | _ => panic!("{call}"),
        }
    }
}

#[derive(Debug)]
pub struct Naive<'rt>(Raw<'rt>);

impl<'rt> Naive<'rt> {
    pub unsafe fn from_raw(port: Raw<'rt>) -> Self {
        Self(port)
    }
    pub unsafe fn as_raw(&self) -> &Raw<'rt> {
        &self.0
    }
    /// # Panics
    /// - if `rx` or `tx`'s len overflows a [`u16`].
    pub fn start<'pool, T, RxI, TxI>(
        self,
        rx: impl IntoIterator<IntoIter = RxI>,
        tx: impl IntoIterator<IntoIter = TxI>,
    ) -> Result<Running<'pool, 'rt, T>, WithError<Self, ffi::Error>>
    where
        RxI: ExactSizeIterator<Item = RxConfig<'pool, T>>,
        TxI: ExactSizeIterator<Item = TxConfig>,
    {
        let rx = rx.into_iter();
        let tx = tx.into_iter();

        let Self(raw) = self;
        let mut call;
        if call!(sys::rte_eth_dev_configure(raw.id, rx.len().try_into().unwrap(), tx.len().try_into().unwrap(), &mem::zeroed::<sys::rte_eth_conf>()) in call)
            != 0
        {
            return Err(WithError {
                with: Self(raw),
                error: ffi::Error(call),
            });
        }
        for (id, TxConfig { depth }) in tx.enumerate() {
            if call!(sys::rte_eth_tx_queue_setup(raw.id, id.try_into().unwrap(), depth, sys::SOCKET_ID_ANY as _, ptr::null()) in call)
                != 0
            {
                return Err(WithError {
                    with: Self(raw),
                    error: ffi::Error(call),
                });
            }
        }
        for (id, RxConfig { depth, pool }) in rx.into_iter().enumerate() {
            if call!(sys::rte_eth_rx_queue_setup(
                raw.id,
                id.try_into().unwrap(),
                depth,
                sys::SOCKET_ID_ANY as _,
                ptr::null(),
                pool.as_raw().as_ptr(),
            ) in call)
                != 0
            {
                return Err(WithError {
                    with: Self(raw),
                    error: ffi::Error(call),
                });
            }
        }
        if call!(sys::rte_eth_dev_start(raw.id)) != 0 {
            return Err(WithError {
                with: Self(raw),
                error: ffi::Error(call),
            });
        }
        Ok(Running {
            raw,
            pool: PhantomData,
        })
    }
    pub fn close(self) -> Result<(), WithError<Self, ffi::Error>> {
        let call;
        match call!(sys::rte_eth_dev_close(self.0.id) in call) {
            0 => Ok(()),
            _ => Err(WithError {
                with: self,
                error: ffi::Error(call),
            }),
        }
    }
}

#[derive(Debug)]
pub struct TxConfig {
    pub depth: u16,
}

#[derive(Debug)]
pub struct RxConfig<'pool, T> {
    pub depth: u16,
    pub pool: &'pool pkt::Pool<'pool, T>,
}

#[derive(Debug)]
pub struct Running<'pool, 'rt, T = ()> {
    raw: Raw<'rt>,
    pool: PhantomData<&'pool pkt::Pool<'rt, T>>,
}

impl<'pool, 'rt, T> Running<'pool, 'rt, T> {
    pub unsafe fn from_raw(port: Raw<'rt>) -> Self {
        Self {
            raw: port,
            pool: PhantomData,
        }
    }
    pub fn raw(&self) -> &Raw<'rt> {
        &self.raw
    }
    pub fn rx_queues<'port>(
        &'port self,
    ) -> impl ExactSizeIterator<Item = RxQueue<'port, 'pool, 'rt, T>> + DoubleEndedIterator + Clone
    {
        (0..self
            .raw
            .info()
            .map(|it| it.nb_rx_queues)
            .unwrap_or_default())
            .map(|queue| RxQueue {
                port: self.raw.id,
                queue,
                life: PhantomData,
            })
    }
    pub fn tx_queues<'port>(
        &'port self,
    ) -> impl ExactSizeIterator<Item = TxQueue<'port, 'pool, 'rt, T>> + DoubleEndedIterator + Clone
    {
        (0..self
            .raw
            .info()
            .map(|it| it.nb_tx_queues)
            .unwrap_or_default())
            .map(|queue| TxQueue {
                port: self.raw.id,
                queue,
                life: PhantomData,
            })
    }
    pub fn stop(self) -> Result<Naive<'rt>, WithError<Self, ffi::Error>> {
        let call;
        match call!(sys::rte_eth_dev_stop(self.raw.id) in call) {
            0 => Ok(Naive(self.raw)),
            _ => Err(WithError {
                with: self,
                error: ffi::Error(call),
            }),
        }
    }
}

#[derive(Debug, Clone)]
pub struct RxQueue<'port, 'pool, 'rt, T> {
    port: u16,
    queue: u16,
    life: PhantomData<(&'port (), &'pool pkt::Pool<'rt, T>)>,
}

impl<'pool, T> RxQueue<'_, 'pool, '_, T> {
    /// Fill the [`spare_capacity`](Vec::spare_capacity_mut) of the `v` with packets from the port.
    pub fn receive_into(&self, v: &mut Vec<pkt::Packet<'pool, T>>) {
        let fillme = v.spare_capacity_mut();
        let ptr = fillme.as_mut_ptr();
        let len = fillme.len().try_into().unwrap_or(u16::MAX);
        let additional = unsafe { sys::rte_eth_rx_burst(self.port, self.queue, ptr as _, len) };
        unsafe { v.set_len(v.len() + usize::from(additional)) }
    }
}

#[derive(Debug, Clone)]
pub struct TxQueue<'port, 'pool, 'rt, T> {
    port: u16,
    queue: u16,
    life: PhantomData<(&'port (), &'pool pkt::Pool<'rt, T>)>,
}

impl<'pool, T> TxQueue<'_, 'pool, '_, T> {
    /// Send as many packets as possible from `v` to the port.
    pub fn transmit_from(&self, v: &mut Vec<pkt::Packet<'pool, T>>) {
        let Self { port, queue, .. } = *self;
        let ptr = v.as_mut_ptr();
        let len = v.len().try_into().unwrap_or(u16::MAX);
        let sent = unsafe { sys::rte_eth_tx_burst(port, queue, ptr as _, len) };
        v.drain(..usize::from(sent));
    }
}
