use std::ffi::CString;

use anyhow::Context as _;
use clap::Parser;
use deepeedeekay::{ffi, log, port, rt, util::WithError};
use itertools::Itertools as _;
use seasick::WriteBuffer;

/// This program loops configures two input ports with a single rx queue,
/// and a single tx queue.
///
/// It then assigns a worker core a cross tx/rx pair to perform forwarding,
/// reporting stats.
#[derive(Parser)]
struct Args {
    #[arg(long)]
    vdev: Vec<WriteBuffer>,
    #[arg(long)]
    log_level: Vec<WriteBuffer>,
    #[arg(long, default_value_t = 1024)]
    pool_capacity: u32,
    #[arg(long, default_value_t = 128)]
    segment_capacity: u16,
    #[arg(long, default_value_t = 256)]
    rx_depth: u16,
    #[arg(long, default_value_t = 256)]
    tx_depth: u16,
    #[arg(long, default_value_t = 16)]
    buffer_depth: usize,
    #[arg(long, default_value_t = rt::Allocator::default())]
    allocator: rt::Allocator,
    #[arg(long)]
    limit: Option<usize>,
}

fn main() -> anyhow::Result<()> {
    let Args {
        vdev,
        log_level,
        pool_capacity,
        segment_capacity,
        rx_depth,
        tx_depth,
        buffer_depth,
        allocator,
        limit,
    } = Args::parse();
    deepeedeekay::run(
        rt::Runtime::new(
            c"rt",
            rt::Args {
                log_levels: to_cstrings(log_level),
                vdevs: to_cstrings(vdev),
                allocator,
                ..Default::default()
            },
        )?,
        |rt, ports| {
            const N: usize = 2;

            let [worker0, worker1] = rt
                .workers()
                .take(N)
                .collect_array::<N>()
                .context(format!("Expected at least {N} workers"))?;

            let [port0, port1] = ports
                .into_iter()
                .take(N)
                .collect_array::<N>()
                .context(format!("Expected at least {N} ports"))?;

            let pool = &rt.pkt_pool(c"pool", pool_capacity, segment_capacity)?;

            let rx = port::RxConfig {
                depth: rx_depth,
                pool,
            };
            let tx = port::TxConfig { depth: tx_depth };

            let port0 = start_port(port0, rx.clone(), tx.clone())?;
            let port1 = start_port(port1, rx, tx)?;

            let (rx0, tx0) = get_queues(&port0).context("Inconsistent port0")?;
            let (rx1, tx1) = get_queues(&port1).context("Inconsistent port1")?;

            rt.spawn(worker0, |_| {
                rx2tx(buffer_depth, limit, log::Type::User1, rx0, tx1)
            });
            rt.spawn(worker1, |_| {
                rx2tx(buffer_depth, limit, log::Type::User2, rx1, tx0)
            });

            anyhow::Ok(())
        },
    )
    .map_err(WithError::into_error)??;
    Ok(())
}

fn to_cstrings(v: Vec<WriteBuffer>) -> Vec<CString> {
    v.into_iter().map(Into::into).collect()
}

fn start_port<'pool, 'rt, T>(
    port: port::Naive<'rt>,
    rx: port::RxConfig<'pool, T>,
    tx: port::TxConfig,
) -> ffi::Result<port::Running<'pool, 'rt, T>> {
    port.start([rx], [tx]).map_err(WithError::into_error)
}

fn get_queues<'port, 'pool, 'rt, T>(
    port: &'port port::Running<'pool, 'rt, T>,
) -> Option<(
    port::RxQueue<'port, 'pool, 'rt, T>,
    port::TxQueue<'port, 'pool, 'rt, T>,
)> {
    let rx = port.rx_queues().next()?;
    let tx = port.tx_queues().next()?;
    Some((rx, tx))
}

fn rx2tx<T>(
    depth: usize,
    mut limit: Option<usize>,
    logty: log::Type,
    rx: port::RxQueue<'_, '_, '_, T>,
    tx: port::TxQueue<'_, '_, '_, T>,
) {
    let mut buf = Vec::with_capacity(depth);
    loop {
        rx.receive_into(&mut buf);
        if buf.is_empty() {
            continue;
        }
        log::log(
            log::Level::Info,
            logty,
            format_args!("Received {} packets", buf.len()),
        );
        while !buf.is_empty() {
            let n = tx.transmit_from(&mut buf);
            if n != 0 {
                log::log(
                    log::Level::Info,
                    logty,
                    format_args!("Forwarded {n} packets"),
                )
            }
            if let Some(limit) = &mut limit {
                match limit.checked_sub(n) {
                    Some(new) => *limit = new,
                    None => break,
                }
            }
        }
    }
}
