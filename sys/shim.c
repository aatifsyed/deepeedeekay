#include "shim.h"

int *deepeedeekay_rte_errno_location()
{
    return &rte_errno;
}

int *deepeedeekay_errno_location()
{
    return &errno;
}

unsigned int *deepeedeekay_pktmbuf_pkt_len(struct rte_mbuf *m)
{
    return &rte_pktmbuf_pkt_len(m);
}

short unsigned int *deepeedeekay_pktmbuf_data_len(struct rte_mbuf *m)
{
    return &rte_pktmbuf_data_len(m);
}

void *deepeedeekay_rte_pktmbuf_mtod(struct rte_mbuf *m)
{
    return rte_pktmbuf_mtod(m, void *);
}

void *deepeedeekay_rte_pktmbuf_mtod_offset(struct rte_mbuf *m, unsigned int o)
{
    return rte_pktmbuf_mtod_offset(m, void *, o);
}
