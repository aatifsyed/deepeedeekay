//! Packet data enters and exits the application through ports.

use core::{
    ffi::{CStr, c_char, c_int, c_uint},
    fmt,
    marker::PhantomData,
    mem,
    ptr::{self, NonNull},
};

use crate::{
    call, ffi, pkt,
    rt::Runtime,
    sys,
    util::{WithError, cstr, neg, to_bool},
};

use alloc::vec::Vec;
use bitbag::{BitBag, BitOr, Flags};
use seasick::{SeaArray, SeaStr, TransmuteFrom};

/// A port in the EAL.
#[repr(transparent)]
pub struct Raw<'rt> {
    id: u16,
    life: PhantomData<&'rt Runtime>,
}

impl fmt::Debug for Raw<'_> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let mut f = f.debug_struct("Port");
        f.field("id", &self.id);
        match self.info() {
            Some(ref it) => f.field("info", it).finish(),
            None => f.finish_non_exhaustive(),
        }
    }
}

#[derive(derive_more::Debug, TransmuteFrom)]
#[repr(C)]
#[transmute(from = sys::rte_eth_dev_info, strict)]
pub struct DeviceInfo<'rt> {
    #[transmute(*mut sys::rte_device)]
    pub device: Option<DeviceHandle<'rt>>,

    #[transmute(*const c_char)]
    pub driver_name: Option<&'rt SeaStr>,

    pub if_index: c_uint,
    pub min_mtu: u16,
    pub max_mtu: u16,
    #[transmute(*const u32)]
    pub dev_flags: &'rt BitBag<DeviceFlags>,
    pub min_rx_bufsize: u32,
    pub max_rx_bufsize: u32,
    pub max_rx_pktlen: u32,
    pub max_lro_pkt_size: u32,
    pub max_rx_queues: u16,
    pub max_tx_queues: u16,
    pub max_mac_addrs: u32,
    pub max_hash_mac_addrs: u32,
    pub max_vfs: u16,
    pub max_vmdq_pools: u16,
    pub rx_seg_capa: sys::rte_eth_rxseg_capa,
    #[transmute(u64)]
    pub rx_offload_capa: BitBag<RxOffloadFlags>,
    #[transmute(u64)]
    pub tx_offload_capa: BitBag<TxOffloadFlags>,
    #[transmute(u64)]
    pub rx_queue_offload_capa: BitBag<RxOffloadFlags>,
    #[transmute(u64)]
    pub tx_queue_offload_capa: BitBag<TxOffloadFlags>,
    pub reta_size: u16,
    pub hash_key_size: u8,
    #[transmute(u32)]
    pub rss_algo_capa: BitBag<RssAlgoFlags>,
    // TODO: flags
    pub flow_type_rss_offloads: u64,
    pub default_rxconf: sys::rte_eth_rxconf,
    pub default_txconf: sys::rte_eth_txconf,
    pub vmdq_queue_base: u16,
    pub vmdq_queue_num: u16,
    pub vmdq_pool_base: u16,
    pub rx_desc_lim: sys::rte_eth_desc_lim,
    pub tx_desc_lim: sys::rte_eth_desc_lim,
    #[transmute(u32)]
    pub speed_capa: BitBag<LinkSpeedFlags>,
    pub nb_rx_queues: u16,
    pub nb_tx_queues: u16,
    pub max_rx_mempools: u16,
    pub default_rxportconf: sys::rte_eth_dev_portconf,
    pub default_txportconf: sys::rte_eth_dev_portconf,
    #[transmute(u64)]
    pub dev_capa: BitBag<DevCapabilityFlags>,

    #[transmute(sys::rte_eth_switch_info)]
    pub switch_info: SwitchInfo<'rt>,

    pub err_handle_mode: sys::rte_eth_err_handle_mode,
    #[debug(skip)]
    reserved_64s: [u64; 2usize],
    #[debug(skip)]
    reserved_ptrs: [*mut ::std::os::raw::c_void; 2usize],
}

#[derive(BitOr, Flags, Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
#[repr(u32)]
pub enum DeviceFlags {
    FlowOpsThreadSafe = sys::RTE_ETH_DEV_FLOW_OPS_THREAD_SAFE,
    IntrLsc = sys::RTE_ETH_DEV_INTR_LSC,
    BondingMember = sys::RTE_ETH_DEV_BONDING_MEMBER,
    IntrRmv = sys::RTE_ETH_DEV_INTR_RMV,
    Representor = sys::RTE_ETH_DEV_REPRESENTOR,
    NoliveMacAddr = sys::RTE_ETH_DEV_NOLIVE_MAC_ADDR,
    AutofillQueueXstats = sys::RTE_ETH_DEV_AUTOFILL_QUEUE_XSTATS,
}

#[derive(BitOr, Flags, Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
#[repr(u64)]
pub enum RxOffloadFlags {
    VlanStrip = sys::RTE_ETH_RX_OFFLOAD_VLAN_STRIP,
    Ipv4Cksum = sys::RTE_ETH_RX_OFFLOAD_IPV4_CKSUM,
    UdpCksum = sys::RTE_ETH_RX_OFFLOAD_UDP_CKSUM,
    TcpCksum = sys::RTE_ETH_RX_OFFLOAD_TCP_CKSUM,
    TcpLro = sys::RTE_ETH_RX_OFFLOAD_TCP_LRO,
    QinqStrip = sys::RTE_ETH_RX_OFFLOAD_QINQ_STRIP,
    OuterIpv4Cksum = sys::RTE_ETH_RX_OFFLOAD_OUTER_IPV4_CKSUM,
    MacsecStrip = sys::RTE_ETH_RX_OFFLOAD_MACSEC_STRIP,
    VlanFilter = sys::RTE_ETH_RX_OFFLOAD_VLAN_FILTER,
    VlanExtend = sys::RTE_ETH_RX_OFFLOAD_VLAN_EXTEND,
    Scatter = sys::RTE_ETH_RX_OFFLOAD_SCATTER,
    Timestamp = sys::RTE_ETH_RX_OFFLOAD_TIMESTAMP,
    Security = sys::RTE_ETH_RX_OFFLOAD_SECURITY,
    KeepCrc = sys::RTE_ETH_RX_OFFLOAD_KEEP_CRC,
    SctpCksum = sys::RTE_ETH_RX_OFFLOAD_SCTP_CKSUM,
    OuterUdpCksum = sys::RTE_ETH_RX_OFFLOAD_OUTER_UDP_CKSUM,
    RssHash = sys::RTE_ETH_RX_OFFLOAD_RSS_HASH,
    BufferSplit = sys::RTE_ETH_RX_OFFLOAD_BUFFER_SPLIT,
}

#[derive(BitOr, Flags, Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
#[repr(u64)]
pub enum TxOffloadFlags {
    VlanInsert = sys::RTE_ETH_TX_OFFLOAD_VLAN_INSERT,
    Ipv4Cksum = sys::RTE_ETH_TX_OFFLOAD_IPV4_CKSUM,
    UdpCksum = sys::RTE_ETH_TX_OFFLOAD_UDP_CKSUM,
    TcpCksum = sys::RTE_ETH_TX_OFFLOAD_TCP_CKSUM,
    SctpCksum = sys::RTE_ETH_TX_OFFLOAD_SCTP_CKSUM,
    TcpTso = sys::RTE_ETH_TX_OFFLOAD_TCP_TSO,
    UdpTso = sys::RTE_ETH_TX_OFFLOAD_UDP_TSO,
    OuterIpv4Cksum = sys::RTE_ETH_TX_OFFLOAD_OUTER_IPV4_CKSUM,
    QinqInsert = sys::RTE_ETH_TX_OFFLOAD_QINQ_INSERT,
    VxlanTnlTso = sys::RTE_ETH_TX_OFFLOAD_VXLAN_TNL_TSO,
    GreTnlTso = sys::RTE_ETH_TX_OFFLOAD_GRE_TNL_TSO,
    IpipTnlTso = sys::RTE_ETH_TX_OFFLOAD_IPIP_TNL_TSO,
    GeneveTnlTso = sys::RTE_ETH_TX_OFFLOAD_GENEVE_TNL_TSO,
    MacsecInsert = sys::RTE_ETH_TX_OFFLOAD_MACSEC_INSERT,
    MtLockfree = sys::RTE_ETH_TX_OFFLOAD_MT_LOCKFREE,
    MultiSegs = sys::RTE_ETH_TX_OFFLOAD_MULTI_SEGS,
    MbufFastFree = sys::RTE_ETH_TX_OFFLOAD_MBUF_FAST_FREE,
    Security = sys::RTE_ETH_TX_OFFLOAD_SECURITY,
    UdpTnlTso = sys::RTE_ETH_TX_OFFLOAD_UDP_TNL_TSO,
    IpTnlTso = sys::RTE_ETH_TX_OFFLOAD_IP_TNL_TSO,
    OuterUdpCksum = sys::RTE_ETH_TX_OFFLOAD_OUTER_UDP_CKSUM,
    SendOnTimestamp = sys::RTE_ETH_TX_OFFLOAD_SEND_ON_TIMESTAMP,
}

#[derive(BitOr, Flags, Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
#[repr(u32)]
pub enum RssAlgoFlags {
    Default = 1 << sys::rte_eth_hash_function::RTE_ETH_HASH_FUNCTION_DEFAULT as u32,
    Toeplitz = 1 << sys::rte_eth_hash_function::RTE_ETH_HASH_FUNCTION_TOEPLITZ as u32,
    SimpleXor = 1 << sys::rte_eth_hash_function::RTE_ETH_HASH_FUNCTION_SIMPLE_XOR as u32,
    SymmetricToeplitz =
        1 << sys::rte_eth_hash_function::RTE_ETH_HASH_FUNCTION_SYMMETRIC_TOEPLITZ as u32,
    SymmetricToeplitzSort =
        1 << sys::rte_eth_hash_function::RTE_ETH_HASH_FUNCTION_SYMMETRIC_TOEPLITZ_SORT as u32,
    Max = 1 << sys::rte_eth_hash_function::RTE_ETH_HASH_FUNCTION_MAX as u32,
}

#[derive(BitOr, Flags, Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
#[repr(u32)]
pub enum LinkSpeedFlags {
    Fixed = sys::RTE_ETH_LINK_SPEED_FIXED,
    _10MHd = sys::RTE_ETH_LINK_SPEED_10M_HD,
    _10M = sys::RTE_ETH_LINK_SPEED_10M,
    _100MHd = sys::RTE_ETH_LINK_SPEED_100M_HD,
    _100M = sys::RTE_ETH_LINK_SPEED_100M,
    _1G = sys::RTE_ETH_LINK_SPEED_1G,
    _2_5G = sys::RTE_ETH_LINK_SPEED_2_5G,
    _5G = sys::RTE_ETH_LINK_SPEED_5G,
    _10G = sys::RTE_ETH_LINK_SPEED_10G,
    _20G = sys::RTE_ETH_LINK_SPEED_20G,
    _25G = sys::RTE_ETH_LINK_SPEED_25G,
    _40G = sys::RTE_ETH_LINK_SPEED_40G,
    _50G = sys::RTE_ETH_LINK_SPEED_50G,
    _56G = sys::RTE_ETH_LINK_SPEED_56G,
    _100G = sys::RTE_ETH_LINK_SPEED_100G,
    _200G = sys::RTE_ETH_LINK_SPEED_200G,
    _400G = sys::RTE_ETH_LINK_SPEED_400G,
}

#[derive(BitOr, Flags, Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
#[repr(u64)]
pub enum DevCapabilityFlags {
    RuntimeRxQueueSetup = sys::RTE_ETH_DEV_CAPA_RUNTIME_RX_QUEUE_SETUP,
    RuntimeTxQueueSetup = sys::RTE_ETH_DEV_CAPA_RUNTIME_TX_QUEUE_SETUP,
    RxqShare = sys::RTE_ETH_DEV_CAPA_RXQ_SHARE,
    FlowRuleKeep = sys::RTE_ETH_DEV_CAPA_FLOW_RULE_KEEP,
    FlowSharedObjectKeep = sys::RTE_ETH_DEV_CAPA_FLOW_SHARED_OBJECT_KEEP,
}

#[repr(transparent)]
pub struct DeviceHandle<'rt> {
    ptr: NonNull<sys::rte_device>,
    life: PhantomData<&'rt Runtime>,
}

impl<'rt> DeviceHandle<'rt> {
    pub fn device(&self) -> Device<'rt> {
        let dev = self.ptr.as_ptr();
        unsafe {
            Device {
                name: cstr(sys::rte_dev_name(dev)),
                bus_info: cstr(sys::rte_dev_bus_info(dev)),
                devargs: NonNull::new(sys::rte_dev_devargs(dev).cast_mut())
                    .map(|it| it.cast().as_ref()),
                is_probed: to_bool(sys::rte_dev_is_probed(dev)).unwrap(),
                numa_node: sys::rte_dev_numa_node(dev),
            }
        }
    }
}

impl fmt::Debug for DeviceHandle<'_> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        self.device().fmt(f)
    }
}

#[derive(Debug)]
pub struct Device<'rt> {
    pub name: Option<&'rt CStr>,
    pub bus_info: Option<&'rt CStr>,
    pub devargs: Option<&'rt Devargs>,
    pub is_probed: bool,
    pub numa_node: c_int,
}

#[derive(Debug, TransmuteFrom)]
#[repr(C)]
#[transmute(from = sys::rte_eth_switch_info, strict)]
pub struct SwitchInfo<'rt> {
    #[transmute(*const c_char)]
    pub name: Option<&'rt SeaStr>,

    pub domain_id: u16,
    pub port_id: u16,
    pub rx_domain: u16,
}

#[derive(derive_more::Debug, TransmuteFrom)]
#[repr(C)]
#[transmute(from = sys::rte_devargs, strict)]
pub struct Devargs {
    #[transmute(sys::rte_devargs__bindgen_ty_1)]
    #[debug(skip)]
    next: [*const Self; 2],

    pub type_: sys::rte_devtype,
    pub policy: sys::rte_dev_policy,

    #[transmute([c_char; 64])]
    pub name: SeaArray<64>,

    /// Pointer into [`Self::data`]
    #[transmute(__bindgen_anon_1: sys::rte_devargs__bindgen_ty_2)]
    #[debug("{:?}", self.drv_str())]
    drv_str: *const SeaStr,

    bus: *mut sys::rte_bus,
    cls: *mut sys::rte_class,

    /// Pointer into [`Self::data`]
    #[transmute(*const c_char)]
    #[debug("{:?}", self.bus_str())]
    bus_str: *const SeaStr,

    /// Pointer into [`Self::data`]
    #[transmute(*const c_char)]
    #[debug("{:?}", self.cls_str())]
    cls_str: *const SeaStr,

    #[debug(skip)]
    data: *mut c_char,
}

impl Devargs {
    pub fn drv_str(&self) -> Option<&SeaStr> {
        unsafe { self.drv_str.as_ref() }
    }
    pub fn bus_str(&self) -> Option<&SeaStr> {
        unsafe { self.bus_str.as_ref() }
    }
    pub fn cls_str(&self) -> Option<&SeaStr> {
        unsafe { self.cls_str.as_ref() }
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
    pub fn info(&self) -> Option<DeviceInfo<'rt>> {
        let mut info = unsafe { mem::zeroed() };
        let call;
        #[allow(clippy::wildcard_in_or_patterns)]
        match call!(
            sys::rte_eth_dev_info_get(self.id, &mut info) in call)
        {
            0 => Some(unsafe { mem::transmute::<sys::rte_eth_dev_info, DeviceInfo>(info) }),
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
    pub fn raw(&self) -> &Raw<'rt> {
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
        let conf = unsafe { mem::zeroed() };
        let mut call;
        if call!(sys::rte_eth_dev_configure(raw.id, rx.len().try_into().unwrap(), tx.len().try_into().unwrap(), &conf) in call)
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
