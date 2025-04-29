#pragma once

#include <rte_errno.h>
#include <rte_log.h>
#include <errno.h>
#include <rte_mbuf.h>

/**
 * @returns the location of `rte_errno` on this thread.
 */
int *deepeedeekay_rte_errno_location();

/**
 * @returns the location of `errno` on this thread.
 */
int *deepeedeekay_errno_location();

/**
 * A function that returns the length of the packet.
 *
 * The value can be read or assigned.
 *
 * @param m
 *   The packet mbuf.
 */
unsigned int *deepeedeekay_pktmbuf_pkt_len(struct rte_mbuf *m);

/**
 * A function that returns the length of the segment.
 *
 * The value can be read or assigned.
 *
 * @param m
 *   The packet mbuf.
 */
short unsigned int *deepeedeekay_pktmbuf_data_len(struct rte_mbuf *m);

/**
 * A function that points to the start of the data in the mbuf.
 *
 * Before using this
 * function, the user must ensure that the first segment is large
 * enough to accommodate its data.
 *
 * @param m
 *   The packet mbuf.
 */
void *deepeedeekay_rte_pktmbuf_mtod(struct rte_mbuf *m);

/**
 * A function that points to the start of the data in the mbuf.
 *
 * Before using this
 * function, the user must ensure that the first segment is large
 * enough to accommodate its data.
 *
 * @param m
 *   The packet mbuf.
 * @param t
 *   The type to cast the result into.
 */
void *deepeedeekay_rte_pktmbuf_mtod_offset(struct rte_mbuf *m, unsigned int o);
