use std::ffi::CString;

use bstr::ByteSlice as _;
use bytes::BufMut as _;
use clap::Parser;
use deepeedeekay::{log, port, rt, util::WithError};
use seasick::WriteBuffer;

/// This program loops configures all input ports with a single rx queue,
/// and loops over each queue, printing packet stats (and optionally, contents).
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
    #[arg(long, default_value_t = 16)]
    buffer_depth: usize,
    #[arg(long, default_value_t = rt::Allocator::default())]
    allocator: rt::Allocator,
}

fn main() -> anyhow::Result<()> {
    let Args {
        vdev,
        log_level,
        pool_capacity,
        segment_capacity,
        rx_depth,
        buffer_depth,
        allocator,
    } = Args::parse();
    deepeedeekay::run(
        rt::Runtime::new(
            c"rt",
            rt::Args {
                allocator,
                vdevs: to_cstrings(vdev),
                log_levels: to_cstrings(log_level),
                ..Default::default()
            },
        )?,
        |rt, ports| {
            // create a mempool
            let pool = &rt.pkt_pool(c"pool", pool_capacity, segment_capacity)?;

            // start the ports
            let ports = ports
                .into_iter()
                .map(|port| {
                    log::log(
                        log::Level::Info,
                        log::Type::User1,
                        format_args!("port {port:?}"),
                    );
                    port.start(
                        [port::RxConfig {
                            depth: rx_depth,
                            pool,
                        }],
                        [],
                    )
                    .map_err(WithError::into_error)
                })
                .collect::<Result<Vec<_>, _>>()?;

            // create a container for packets
            let pkts = &mut Vec::with_capacity(buffer_depth);

            // loop over the receive queues, until they're empty
            for rxq in ports.iter().flat_map(|port| port.rx_queues()).cycle() {
                rxq.receive_into(pkts);
                if pkts.is_empty() {
                    break;
                }
                for pkt in pkts.drain(..) {
                    let mut data = Vec::with_capacity(pkt.len() as _);
                    data.put(pkt.buf());
                    log::log(
                        log::Level::Info,
                        log::Type::User1,
                        format_args!(
                            "packet of {} bytes in {} segments",
                            pkt.len(),
                            pkt.iter().count(),
                        ),
                    );
                    log::log(
                        log::Level::Debug,
                        log::Type::User1,
                        format_args!("\t{:?}", data.as_bstr()),
                    );
                }
            }
            anyhow::Ok(())
        },
    )
    .map_err(|it| it.error)??;
    Ok(())
}

fn to_cstrings(v: Vec<WriteBuffer>) -> Vec<CString> {
    v.into_iter().map(Into::into).collect()
}
