use std::{
    env,
    ffi::{c_char, c_uint, CStr, CString},
    fmt, io, mem, process, ptr,
};

use anyhow::{ensure, Context as _};
use deepeedeekay_sys::*;

fn main() -> anyhow::Result<()> {
    let args = env::args_os()
        .enumerate()
        .map(|(ix, arg)| {
            CString::new(arg.as_encoded_bytes()).context(format!("bad argument at index {ix}"))
        })
        .collect::<Result<Vec<_>, _>>()?;
    let mut args = args
        .iter()
        .map(|it| it.as_ptr().cast_mut())
        .collect::<Vec<_>>();
    match _main(&mut args) {
        Ok(()) => Ok(()),
        Err(e) => {
            for (ix, e) in e.chain().enumerate() {
                println!("{ix}: {e}")
            }
            println!("rte_errno: {}", Errno::current_thread());
            let e = io::Error::last_os_error();
            match e.raw_os_error() {
                Some(0) => {}
                Some(n) => println!("os_error: {n} ({e})"),
                None => println!("os_error: {e}"),
            }
            process::exit(1)
        }
    }
}

fn _main(args: &mut [*mut c_char]) -> anyhow::Result<()> {
    unsafe {
        let argc = args.len().try_into()?;
        let rte_eal_init = rte_eal_init(argc, args.as_mut_ptr());
        rte_log(
            RTE_LOG_DEBUG,
            RTE_LOGTYPE_USER1,
            c"USER1: finished init eal\n".as_ptr(),
        );
        ensure!(rte_eal_init != -1);
        let rte_eal_parsed = rte_eal_init + 1;
        ensure!(rte_eal_parsed == argc);
        Errno::clear_current_thread();
        let pool = rte_pktmbuf_pool_create(
            c"MBUF_POOL".as_ptr(),
            8191,
            0,
            0,
            2048 + 128,
            rte_socket_id() as _,
        );
        ensure!(!pool.is_null());
        Errno::clear_current_thread();
        rte_log(
            RTE_LOG_INFO,
            RTE_LOGTYPE_USER1,
            c"USER1: created pktmbuf pool\n".as_ptr(),
        );
        let mut obj = ptr::null_mut();
        let rc = rte_mempool_get(pool, &mut obj);
        ensure!(rc == 0);
        ensure!(!obj.is_null());
        rte_log(
            RTE_LOG_INFO,
            RTE_LOGTYPE_USER1,
            c"USER1: allocated mbuf\n".as_ptr(),
        );
        rte_mempool_put(pool, obj);
        rte_log(
            RTE_LOG_INFO,
            RTE_LOGTYPE_USER1,
            c"USER1: freed mbuf\n".as_ptr(),
        );

        for port_id in 0..RTE_MAX_ETHPORTS {
            if rte_eth_dev_is_valid_port(port_id) == 0 {
                rte_log(
                    RTE_LOG_INFO,
                    RTE_LOGTYPE_USER1,
                    c"USER1: stopping at port id %d\n".as_ptr(),
                    port_id as c_uint,
                );
                break;
            }

            print_info(port_id)?;

            for (nb_rx_queue, nb_tx_queue) in [(0, 0), (1, 1), (2, 2)] {
                let eth_conf = mem::zeroed();
                let rte_eth_dev_configure =
                    rte_eth_dev_configure(port_id, nb_rx_queue, nb_tx_queue, &eth_conf);
                ensure!(rte_eth_dev_configure == 0);
                for tx_queue_id in 0..nb_tx_queue {
                    let rte_eth_tx_queue_setup = rte_eth_tx_queue_setup(
                        port_id,
                        tx_queue_id,
                        1024,
                        SOCKET_ID_ANY as _,
                        ptr::null(),
                    );
                    ensure!(rte_eth_tx_queue_setup == 0);
                }
                for rx_queue_id in 0..nb_rx_queue {
                    let rte_eth_rx_queue_setup = rte_eth_rx_queue_setup(
                        port_id,
                        rx_queue_id,
                        1024,
                        SOCKET_ID_ANY as _,
                        ptr::null(),
                        pool,
                    );
                    ensure!(rte_eth_rx_queue_setup == 0);
                }
                let rte_eth_dev_start = rte_eth_dev_start(port_id);
                ensure!(rte_eth_dev_start == 0);
                print_info(port_id)?;
                let rte_eth_dev_stop = rte_eth_dev_stop(port_id);
                ensure!(rte_eth_dev_stop == 0);
            }

            // rte_eth_dev_configure(port_id, nb_rx_queue, nb_tx_queue, eth_conf);
            // rte_eth_tx_queue_setup()
        }

        Ok(())
    }
}

unsafe fn print_info(port_id: u16) -> anyhow::Result<()> {
    let mut info = mem::zeroed();
    let dev_info_get = rte_eth_dev_info_get(port_id, &mut info);
    ensure!(dev_info_get == 0);

    rte_log(
        RTE_LOG_INFO,
        RTE_LOGTYPE_USER1,
        c"USER1: port id %d: nb_rx_queues = %d; nb_tx_queues = %d\n".as_ptr(),
        port_id as c_uint,
        info.nb_rx_queues as c_uint,
        info.nb_tx_queues as c_uint,
    );
    Ok(())
}

#[derive(Debug)]
struct Errno(i32);

impl Errno {
    fn clear_current_thread() {
        unsafe { *rte_errno_location() = 0 }
    }
    fn current_thread() -> Self {
        Self(unsafe { *rte_errno_location() })
    }
    fn message(&self) -> Option<&'static CStr> {
        let s = unsafe { rte_strerror(self.0) };
        match s.is_null() {
            true => None,
            false => Some(unsafe { CStr::from_ptr(s) }),
        }
    }
}

impl fmt::Display for Errno {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_fmt(format_args!("{}", self.0))?;
        match self.message() {
            Some(msg) => f.write_fmt(format_args!(" ({msg:?})")),
            None => Ok(()),
        }
    }
}

impl core::error::Error for Errno {}
