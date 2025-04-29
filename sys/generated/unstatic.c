#include "unstatic.h"

int  deepeedeekay_rte_is_aligned(const void *const restrict ptr, const unsigned int align) { return rte_is_aligned(ptr, align); }
void  deepeedeekay_rte_uuid_copy(unsigned char * dst, const unsigned char * src) { return rte_uuid_copy(dst, src); }
int  deepeedeekay_rte_gettid() { return rte_gettid(); }
uint32_t  deepeedeekay_rte_bit_relaxed_get32(unsigned int nr, volatile uint32_t * addr) { return rte_bit_relaxed_get32(nr, addr); }
void  deepeedeekay_rte_bit_relaxed_set32(unsigned int nr, volatile uint32_t * addr) { return rte_bit_relaxed_set32(nr, addr); }
void  deepeedeekay_rte_bit_relaxed_clear32(unsigned int nr, volatile uint32_t * addr) { return rte_bit_relaxed_clear32(nr, addr); }
uint32_t  deepeedeekay_rte_bit_relaxed_test_and_set32(unsigned int nr, volatile uint32_t * addr) { return rte_bit_relaxed_test_and_set32(nr, addr); }
uint32_t  deepeedeekay_rte_bit_relaxed_test_and_clear32(unsigned int nr, volatile uint32_t * addr) { return rte_bit_relaxed_test_and_clear32(nr, addr); }
uint64_t  deepeedeekay_rte_bit_relaxed_get64(unsigned int nr, volatile uint64_t * addr) { return rte_bit_relaxed_get64(nr, addr); }
void  deepeedeekay_rte_bit_relaxed_set64(unsigned int nr, volatile uint64_t * addr) { return rte_bit_relaxed_set64(nr, addr); }
void  deepeedeekay_rte_bit_relaxed_clear64(unsigned int nr, volatile uint64_t * addr) { return rte_bit_relaxed_clear64(nr, addr); }
uint64_t  deepeedeekay_rte_bit_relaxed_test_and_set64(unsigned int nr, volatile uint64_t * addr) { return rte_bit_relaxed_test_and_set64(nr, addr); }
uint64_t  deepeedeekay_rte_bit_relaxed_test_and_clear64(unsigned int nr, volatile uint64_t * addr) { return rte_bit_relaxed_test_and_clear64(nr, addr); }
unsigned int  deepeedeekay_rte_clz32(uint32_t v) { return rte_clz32(v); }
unsigned int  deepeedeekay_rte_clz64(uint64_t v) { return rte_clz64(v); }
unsigned int  deepeedeekay_rte_ctz32(uint32_t v) { return rte_ctz32(v); }
unsigned int  deepeedeekay_rte_ctz64(uint64_t v) { return rte_ctz64(v); }
unsigned int  deepeedeekay_rte_popcount32(uint32_t v) { return rte_popcount32(v); }
unsigned int  deepeedeekay_rte_popcount64(uint64_t v) { return rte_popcount64(v); }
uint32_t  deepeedeekay_rte_combine32ms1b(uint32_t x) { return rte_combine32ms1b(x); }
uint64_t  deepeedeekay_rte_combine64ms1b(uint64_t v) { return rte_combine64ms1b(v); }
uint32_t  deepeedeekay_rte_bsf32(uint32_t v) { return rte_bsf32(v); }
int  deepeedeekay_rte_bsf32_safe(uint32_t v, uint32_t * pos) { return rte_bsf32_safe(v, pos); }
uint32_t  deepeedeekay_rte_bsf64(uint64_t v) { return rte_bsf64(v); }
int  deepeedeekay_rte_bsf64_safe(uint64_t v, uint32_t * pos) { return rte_bsf64_safe(v, pos); }
uint32_t  deepeedeekay_rte_fls_u32(uint32_t x) { return rte_fls_u32(x); }
uint32_t  deepeedeekay_rte_fls_u64(uint64_t x) { return rte_fls_u64(x); }
int  deepeedeekay_rte_is_power_of_2(uint32_t n) { return rte_is_power_of_2(n); }
uint32_t  deepeedeekay_rte_align32pow2(uint32_t x) { return rte_align32pow2(x); }
uint32_t  deepeedeekay_rte_align32prevpow2(uint32_t x) { return rte_align32prevpow2(x); }
uint64_t  deepeedeekay_rte_align64pow2(uint64_t v) { return rte_align64pow2(v); }
uint64_t  deepeedeekay_rte_align64prevpow2(uint64_t v) { return rte_align64prevpow2(v); }
uint32_t  deepeedeekay_rte_log2_u32(uint32_t v) { return rte_log2_u32(v); }
uint32_t  deepeedeekay_rte_log2_u64(uint64_t v) { return rte_log2_u64(v); }
void  deepeedeekay_rte_atomic_thread_fence(rte_memory_order memorder) { return rte_atomic_thread_fence(memorder); }
int  deepeedeekay_rte_atomic16_cmpset(volatile uint16_t * dst, uint16_t exp, uint16_t src) { return rte_atomic16_cmpset(dst, exp, src); }
uint16_t  deepeedeekay_rte_atomic16_exchange(volatile uint16_t * dst, uint16_t val) { return rte_atomic16_exchange(dst, val); }
void  deepeedeekay_rte_atomic16_init(rte_atomic16_t * v) { return rte_atomic16_init(v); }
int16_t  deepeedeekay_rte_atomic16_read(const rte_atomic16_t * v) { return rte_atomic16_read(v); }
void  deepeedeekay_rte_atomic16_set(rte_atomic16_t * v, int16_t new_value) { return rte_atomic16_set(v, new_value); }
void  deepeedeekay_rte_atomic16_add(rte_atomic16_t * v, int16_t inc) { return rte_atomic16_add(v, inc); }
void  deepeedeekay_rte_atomic16_sub(rte_atomic16_t * v, int16_t dec) { return rte_atomic16_sub(v, dec); }
void  deepeedeekay_rte_atomic16_inc(rte_atomic16_t * v) { return rte_atomic16_inc(v); }
void  deepeedeekay_rte_atomic16_dec(rte_atomic16_t * v) { return rte_atomic16_dec(v); }
int16_t  deepeedeekay_rte_atomic16_add_return(rte_atomic16_t * v, int16_t inc) { return rte_atomic16_add_return(v, inc); }
int16_t  deepeedeekay_rte_atomic16_sub_return(rte_atomic16_t * v, int16_t dec) { return rte_atomic16_sub_return(v, dec); }
int  deepeedeekay_rte_atomic16_inc_and_test(rte_atomic16_t * v) { return rte_atomic16_inc_and_test(v); }
int  deepeedeekay_rte_atomic16_dec_and_test(rte_atomic16_t * v) { return rte_atomic16_dec_and_test(v); }
int  deepeedeekay_rte_atomic16_test_and_set(rte_atomic16_t * v) { return rte_atomic16_test_and_set(v); }
void  deepeedeekay_rte_atomic16_clear(rte_atomic16_t * v) { return rte_atomic16_clear(v); }
int  deepeedeekay_rte_atomic32_cmpset(volatile uint32_t * dst, uint32_t exp, uint32_t src) { return rte_atomic32_cmpset(dst, exp, src); }
uint32_t  deepeedeekay_rte_atomic32_exchange(volatile uint32_t * dst, uint32_t val) { return rte_atomic32_exchange(dst, val); }
void  deepeedeekay_rte_atomic32_init(rte_atomic32_t * v) { return rte_atomic32_init(v); }
int32_t  deepeedeekay_rte_atomic32_read(const rte_atomic32_t * v) { return rte_atomic32_read(v); }
void  deepeedeekay_rte_atomic32_set(rte_atomic32_t * v, int32_t new_value) { return rte_atomic32_set(v, new_value); }
void  deepeedeekay_rte_atomic32_add(rte_atomic32_t * v, int32_t inc) { return rte_atomic32_add(v, inc); }
void  deepeedeekay_rte_atomic32_sub(rte_atomic32_t * v, int32_t dec) { return rte_atomic32_sub(v, dec); }
void  deepeedeekay_rte_atomic32_inc(rte_atomic32_t * v) { return rte_atomic32_inc(v); }
void  deepeedeekay_rte_atomic32_dec(rte_atomic32_t * v) { return rte_atomic32_dec(v); }
int32_t  deepeedeekay_rte_atomic32_add_return(rte_atomic32_t * v, int32_t inc) { return rte_atomic32_add_return(v, inc); }
int32_t  deepeedeekay_rte_atomic32_sub_return(rte_atomic32_t * v, int32_t dec) { return rte_atomic32_sub_return(v, dec); }
int  deepeedeekay_rte_atomic32_inc_and_test(rte_atomic32_t * v) { return rte_atomic32_inc_and_test(v); }
int  deepeedeekay_rte_atomic32_dec_and_test(rte_atomic32_t * v) { return rte_atomic32_dec_and_test(v); }
int  deepeedeekay_rte_atomic32_test_and_set(rte_atomic32_t * v) { return rte_atomic32_test_and_set(v); }
void  deepeedeekay_rte_atomic32_clear(rte_atomic32_t * v) { return rte_atomic32_clear(v); }
int  deepeedeekay_rte_atomic64_cmpset(volatile uint64_t * dst, uint64_t exp, uint64_t src) { return rte_atomic64_cmpset(dst, exp, src); }
uint64_t  deepeedeekay_rte_atomic64_exchange(volatile uint64_t * dst, uint64_t val) { return rte_atomic64_exchange(dst, val); }
void  deepeedeekay_rte_atomic64_init(rte_atomic64_t * v) { return rte_atomic64_init(v); }
int64_t  deepeedeekay_rte_atomic64_read(rte_atomic64_t * v) { return rte_atomic64_read(v); }
void  deepeedeekay_rte_atomic64_set(rte_atomic64_t * v, int64_t new_value) { return rte_atomic64_set(v, new_value); }
void  deepeedeekay_rte_atomic64_add(rte_atomic64_t * v, int64_t inc) { return rte_atomic64_add(v, inc); }
void  deepeedeekay_rte_atomic64_sub(rte_atomic64_t * v, int64_t dec) { return rte_atomic64_sub(v, dec); }
void  deepeedeekay_rte_atomic64_inc(rte_atomic64_t * v) { return rte_atomic64_inc(v); }
void  deepeedeekay_rte_atomic64_dec(rte_atomic64_t * v) { return rte_atomic64_dec(v); }
int64_t  deepeedeekay_rte_atomic64_add_return(rte_atomic64_t * v, int64_t inc) { return rte_atomic64_add_return(v, inc); }
int64_t  deepeedeekay_rte_atomic64_sub_return(rte_atomic64_t * v, int64_t dec) { return rte_atomic64_sub_return(v, dec); }
int  deepeedeekay_rte_atomic64_inc_and_test(rte_atomic64_t * v) { return rte_atomic64_inc_and_test(v); }
int  deepeedeekay_rte_atomic64_dec_and_test(rte_atomic64_t * v) { return rte_atomic64_dec_and_test(v); }
int  deepeedeekay_rte_atomic64_test_and_set(rte_atomic64_t * v) { return rte_atomic64_test_and_set(v); }
void  deepeedeekay_rte_atomic64_clear(rte_atomic64_t * v) { return rte_atomic64_clear(v); }
void  deepeedeekay_rte_smp_mb() { return rte_smp_mb(); }
int  deepeedeekay_rte_atomic128_cmp_exchange(rte_int128_t * dst, rte_int128_t * exp, const rte_int128_t * src, unsigned int weak, int success, int failure) { return rte_atomic128_cmp_exchange(dst, exp, src, weak, success, failure); }
void  deepeedeekay_rte_pause() { return rte_pause(); }
void  deepeedeekay_rte_wait_until_equal_16(volatile uint16_t * addr, uint16_t expected, rte_memory_order memorder) { return rte_wait_until_equal_16(addr, expected, memorder); }
void  deepeedeekay_rte_wait_until_equal_32(volatile uint32_t * addr, uint32_t expected, rte_memory_order memorder) { return rte_wait_until_equal_32(addr, expected, memorder); }
void  deepeedeekay_rte_wait_until_equal_64(volatile uint64_t * addr, uint64_t expected, rte_memory_order memorder) { return rte_wait_until_equal_64(addr, expected, memorder); }
void  deepeedeekay_rte_rwlock_init(rte_rwlock_t * rwl) { return rte_rwlock_init(rwl); }
void  deepeedeekay_rte_rwlock_read_lock(rte_rwlock_t * rwl) { return rte_rwlock_read_lock(rwl); }
int  deepeedeekay_rte_rwlock_read_trylock(rte_rwlock_t * rwl) { return rte_rwlock_read_trylock(rwl); }
void  deepeedeekay_rte_rwlock_read_unlock(rte_rwlock_t * rwl) { return rte_rwlock_read_unlock(rwl); }
int  deepeedeekay_rte_rwlock_write_trylock(rte_rwlock_t * rwl) { return rte_rwlock_write_trylock(rwl); }
void  deepeedeekay_rte_rwlock_write_lock(rte_rwlock_t * rwl) { return rte_rwlock_write_lock(rwl); }
void  deepeedeekay_rte_rwlock_write_unlock(rte_rwlock_t * rwl) { return rte_rwlock_write_unlock(rwl); }
int  deepeedeekay_rte_rwlock_write_is_locked(rte_rwlock_t * rwl) { return rte_rwlock_write_is_locked(rwl); }
void  deepeedeekay_rte_rwlock_read_lock_tm(rte_rwlock_t * rwl) { return rte_rwlock_read_lock_tm(rwl); }
void  deepeedeekay_rte_rwlock_read_unlock_tm(rte_rwlock_t * rwl) { return rte_rwlock_read_unlock_tm(rwl); }
void  deepeedeekay_rte_rwlock_write_lock_tm(rte_rwlock_t * rwl) { return rte_rwlock_write_lock_tm(rwl); }
void  deepeedeekay_rte_rwlock_write_unlock_tm(rte_rwlock_t * rwl) { return rte_rwlock_write_unlock_tm(rwl); }
unsigned int  deepeedeekay_rte_lcore_id() { return rte_lcore_id(); }
void  deepeedeekay_rte_spinlock_init(rte_spinlock_t * sl) { return rte_spinlock_init(sl); }
void  deepeedeekay_rte_spinlock_lock(rte_spinlock_t * sl) { return rte_spinlock_lock(sl); }
void  deepeedeekay_rte_spinlock_unlock(rte_spinlock_t * sl) { return rte_spinlock_unlock(sl); }
int  deepeedeekay_rte_spinlock_trylock(rte_spinlock_t * sl) { return rte_spinlock_trylock(sl); }
int  deepeedeekay_rte_spinlock_is_locked(rte_spinlock_t * sl) { return rte_spinlock_is_locked(sl); }
int  deepeedeekay_rte_tm_supported() { return rte_tm_supported(); }
void  deepeedeekay_rte_spinlock_lock_tm(rte_spinlock_t * sl) { return rte_spinlock_lock_tm(sl); }
void  deepeedeekay_rte_spinlock_unlock_tm(rte_spinlock_t * sl) { return rte_spinlock_unlock_tm(sl); }
int  deepeedeekay_rte_spinlock_trylock_tm(rte_spinlock_t * sl) { return rte_spinlock_trylock_tm(sl); }
void  deepeedeekay_rte_spinlock_recursive_init(rte_spinlock_recursive_t * slr) { return rte_spinlock_recursive_init(slr); }
void  deepeedeekay_rte_spinlock_recursive_lock(rte_spinlock_recursive_t * slr) { return rte_spinlock_recursive_lock(slr); }
void  deepeedeekay_rte_spinlock_recursive_unlock(rte_spinlock_recursive_t * slr) { return rte_spinlock_recursive_unlock(slr); }
int  deepeedeekay_rte_spinlock_recursive_trylock(rte_spinlock_recursive_t * slr) { return rte_spinlock_recursive_trylock(slr); }
void  deepeedeekay_rte_spinlock_recursive_lock_tm(rte_spinlock_recursive_t * slr) { return rte_spinlock_recursive_lock_tm(slr); }
void  deepeedeekay_rte_spinlock_recursive_unlock_tm(rte_spinlock_recursive_t * slr) { return rte_spinlock_recursive_unlock_tm(slr); }
int  deepeedeekay_rte_spinlock_recursive_trylock_tm(rte_spinlock_recursive_t * slr) { return rte_spinlock_recursive_trylock_tm(slr); }
unsigned int  deepeedeekay_rte_xbegin() { return rte_xbegin(); }
void  deepeedeekay_rte_xend() { return rte_xend(); }
int  deepeedeekay_rte_xtest() { return rte_xtest(); }
uint64_t  deepeedeekay_rte_get_tsc_cycles() { return rte_get_tsc_cycles(); }
uint64_t  deepeedeekay_rte_get_timer_cycles() { return rte_get_timer_cycles(); }
uint64_t  deepeedeekay_rte_get_timer_hz() { return rte_get_timer_hz(); }
void  deepeedeekay_rte_delay_ms(unsigned int ms) { return rte_delay_ms(ms); }
uint64_t  deepeedeekay_rte_rdtsc() { return rte_rdtsc(); }
uint64_t  deepeedeekay_rte_rdtsc_precise() { return rte_rdtsc_precise(); }
int  deepeedeekay_rte_try_tm(volatile int * lock) { return rte_try_tm(lock); }
unsigned int  deepeedeekay_rte_ring_mp_enqueue_bulk_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space) { return rte_ring_mp_enqueue_bulk_elem(r, obj_table, esize, n, free_space); }
unsigned int  deepeedeekay_rte_ring_sp_enqueue_bulk_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space) { return rte_ring_sp_enqueue_bulk_elem(r, obj_table, esize, n, free_space); }
unsigned int  deepeedeekay_rte_ring_mp_hts_enqueue_bulk_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space) { return rte_ring_mp_hts_enqueue_bulk_elem(r, obj_table, esize, n, free_space); }
unsigned int  deepeedeekay_rte_ring_mc_hts_dequeue_bulk_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_mc_hts_dequeue_bulk_elem(r, obj_table, esize, n, available); }
unsigned int  deepeedeekay_rte_ring_mp_hts_enqueue_burst_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space) { return rte_ring_mp_hts_enqueue_burst_elem(r, obj_table, esize, n, free_space); }
unsigned int  deepeedeekay_rte_ring_mc_hts_dequeue_burst_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_mc_hts_dequeue_burst_elem(r, obj_table, esize, n, available); }
unsigned int  deepeedeekay_rte_ring_mp_hts_enqueue_bulk(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space) { return rte_ring_mp_hts_enqueue_bulk(r, obj_table, n, free_space); }
unsigned int  deepeedeekay_rte_ring_mc_hts_dequeue_bulk(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_mc_hts_dequeue_bulk(r, obj_table, n, available); }
unsigned int  deepeedeekay_rte_ring_mp_hts_enqueue_burst(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space) { return rte_ring_mp_hts_enqueue_burst(r, obj_table, n, free_space); }
unsigned int  deepeedeekay_rte_ring_mc_hts_dequeue_burst(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_mc_hts_dequeue_burst(r, obj_table, n, available); }
unsigned int  deepeedeekay_rte_ring_mp_rts_enqueue_bulk_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space) { return rte_ring_mp_rts_enqueue_bulk_elem(r, obj_table, esize, n, free_space); }
unsigned int  deepeedeekay_rte_ring_mc_rts_dequeue_bulk_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_mc_rts_dequeue_bulk_elem(r, obj_table, esize, n, available); }
unsigned int  deepeedeekay_rte_ring_mp_rts_enqueue_burst_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space) { return rte_ring_mp_rts_enqueue_burst_elem(r, obj_table, esize, n, free_space); }
unsigned int  deepeedeekay_rte_ring_mc_rts_dequeue_burst_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_mc_rts_dequeue_burst_elem(r, obj_table, esize, n, available); }
unsigned int  deepeedeekay_rte_ring_mp_rts_enqueue_bulk(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space) { return rte_ring_mp_rts_enqueue_bulk(r, obj_table, n, free_space); }
unsigned int  deepeedeekay_rte_ring_mc_rts_dequeue_bulk(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_mc_rts_dequeue_bulk(r, obj_table, n, available); }
unsigned int  deepeedeekay_rte_ring_mp_rts_enqueue_burst(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space) { return rte_ring_mp_rts_enqueue_burst(r, obj_table, n, free_space); }
unsigned int  deepeedeekay_rte_ring_mc_rts_dequeue_burst(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_mc_rts_dequeue_burst(r, obj_table, n, available); }
uint32_t  deepeedeekay_rte_ring_get_prod_htd_max(const struct rte_ring * r) { return rte_ring_get_prod_htd_max(r); }
int  deepeedeekay_rte_ring_set_prod_htd_max(struct rte_ring * r, uint32_t v) { return rte_ring_set_prod_htd_max(r, v); }
uint32_t  deepeedeekay_rte_ring_get_cons_htd_max(const struct rte_ring * r) { return rte_ring_get_cons_htd_max(r); }
int  deepeedeekay_rte_ring_set_cons_htd_max(struct rte_ring * r, uint32_t v) { return rte_ring_set_cons_htd_max(r, v); }
unsigned int  deepeedeekay_rte_ring_enqueue_bulk_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space) { return rte_ring_enqueue_bulk_elem(r, obj_table, esize, n, free_space); }
int  deepeedeekay_rte_ring_mp_enqueue_elem(struct rte_ring * r, void * obj, unsigned int esize) { return rte_ring_mp_enqueue_elem(r, obj, esize); }
int  deepeedeekay_rte_ring_sp_enqueue_elem(struct rte_ring * r, void * obj, unsigned int esize) { return rte_ring_sp_enqueue_elem(r, obj, esize); }
int  deepeedeekay_rte_ring_enqueue_elem(struct rte_ring * r, void * obj, unsigned int esize) { return rte_ring_enqueue_elem(r, obj, esize); }
unsigned int  deepeedeekay_rte_ring_mc_dequeue_bulk_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_mc_dequeue_bulk_elem(r, obj_table, esize, n, available); }
unsigned int  deepeedeekay_rte_ring_sc_dequeue_bulk_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_sc_dequeue_bulk_elem(r, obj_table, esize, n, available); }
unsigned int  deepeedeekay_rte_ring_dequeue_bulk_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_dequeue_bulk_elem(r, obj_table, esize, n, available); }
int  deepeedeekay_rte_ring_mc_dequeue_elem(struct rte_ring * r, void * obj_p, unsigned int esize) { return rte_ring_mc_dequeue_elem(r, obj_p, esize); }
int  deepeedeekay_rte_ring_sc_dequeue_elem(struct rte_ring * r, void * obj_p, unsigned int esize) { return rte_ring_sc_dequeue_elem(r, obj_p, esize); }
int  deepeedeekay_rte_ring_dequeue_elem(struct rte_ring * r, void * obj_p, unsigned int esize) { return rte_ring_dequeue_elem(r, obj_p, esize); }
unsigned int  deepeedeekay_rte_ring_mp_enqueue_burst_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space) { return rte_ring_mp_enqueue_burst_elem(r, obj_table, esize, n, free_space); }
unsigned int  deepeedeekay_rte_ring_sp_enqueue_burst_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space) { return rte_ring_sp_enqueue_burst_elem(r, obj_table, esize, n, free_space); }
unsigned int  deepeedeekay_rte_ring_enqueue_burst_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space) { return rte_ring_enqueue_burst_elem(r, obj_table, esize, n, free_space); }
unsigned int  deepeedeekay_rte_ring_mc_dequeue_burst_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_mc_dequeue_burst_elem(r, obj_table, esize, n, available); }
unsigned int  deepeedeekay_rte_ring_sc_dequeue_burst_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_sc_dequeue_burst_elem(r, obj_table, esize, n, available); }
unsigned int  deepeedeekay_rte_ring_dequeue_burst_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_dequeue_burst_elem(r, obj_table, esize, n, available); }
unsigned int  deepeedeekay_rte_ring_enqueue_bulk_elem_start(struct rte_ring * r, unsigned int n, unsigned int * free_space) { return rte_ring_enqueue_bulk_elem_start(r, n, free_space); }
unsigned int  deepeedeekay_rte_ring_enqueue_bulk_start(struct rte_ring * r, unsigned int n, unsigned int * free_space) { return rte_ring_enqueue_bulk_start(r, n, free_space); }
unsigned int  deepeedeekay_rte_ring_enqueue_burst_elem_start(struct rte_ring * r, unsigned int n, unsigned int * free_space) { return rte_ring_enqueue_burst_elem_start(r, n, free_space); }
unsigned int  deepeedeekay_rte_ring_enqueue_burst_start(struct rte_ring * r, unsigned int n, unsigned int * free_space) { return rte_ring_enqueue_burst_start(r, n, free_space); }
void  deepeedeekay_rte_ring_enqueue_elem_finish(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n) { return rte_ring_enqueue_elem_finish(r, obj_table, esize, n); }
void  deepeedeekay_rte_ring_enqueue_finish(struct rte_ring * r, void *const * obj_table, unsigned int n) { return rte_ring_enqueue_finish(r, obj_table, n); }
unsigned int  deepeedeekay_rte_ring_dequeue_bulk_elem_start(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_dequeue_bulk_elem_start(r, obj_table, esize, n, available); }
unsigned int  deepeedeekay_rte_ring_dequeue_bulk_start(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_dequeue_bulk_start(r, obj_table, n, available); }
unsigned int  deepeedeekay_rte_ring_dequeue_burst_elem_start(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available) { return rte_ring_dequeue_burst_elem_start(r, obj_table, esize, n, available); }
unsigned int  deepeedeekay_rte_ring_dequeue_burst_start(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_dequeue_burst_start(r, obj_table, n, available); }
void  deepeedeekay_rte_ring_dequeue_elem_finish(struct rte_ring * r, unsigned int n) { return rte_ring_dequeue_elem_finish(r, n); }
void  deepeedeekay_rte_ring_dequeue_finish(struct rte_ring * r, unsigned int n) { return rte_ring_dequeue_finish(r, n); }
unsigned int  deepeedeekay_rte_ring_enqueue_zc_bulk_elem_start(struct rte_ring * r, unsigned int esize, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * free_space) { return rte_ring_enqueue_zc_bulk_elem_start(r, esize, n, zcd, free_space); }
unsigned int  deepeedeekay_rte_ring_enqueue_zc_bulk_start(struct rte_ring * r, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * free_space) { return rte_ring_enqueue_zc_bulk_start(r, n, zcd, free_space); }
unsigned int  deepeedeekay_rte_ring_enqueue_zc_burst_elem_start(struct rte_ring * r, unsigned int esize, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * free_space) { return rte_ring_enqueue_zc_burst_elem_start(r, esize, n, zcd, free_space); }
unsigned int  deepeedeekay_rte_ring_enqueue_zc_burst_start(struct rte_ring * r, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * free_space) { return rte_ring_enqueue_zc_burst_start(r, n, zcd, free_space); }
void  deepeedeekay_rte_ring_enqueue_zc_elem_finish(struct rte_ring * r, unsigned int n) { return rte_ring_enqueue_zc_elem_finish(r, n); }
void  deepeedeekay_rte_ring_enqueue_zc_finish(struct rte_ring * r, unsigned int n) { return rte_ring_enqueue_zc_finish(r, n); }
unsigned int  deepeedeekay_rte_ring_dequeue_zc_bulk_elem_start(struct rte_ring * r, unsigned int esize, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * available) { return rte_ring_dequeue_zc_bulk_elem_start(r, esize, n, zcd, available); }
unsigned int  deepeedeekay_rte_ring_dequeue_zc_bulk_start(struct rte_ring * r, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * available) { return rte_ring_dequeue_zc_bulk_start(r, n, zcd, available); }
unsigned int  deepeedeekay_rte_ring_dequeue_zc_burst_elem_start(struct rte_ring * r, unsigned int esize, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * available) { return rte_ring_dequeue_zc_burst_elem_start(r, esize, n, zcd, available); }
unsigned int  deepeedeekay_rte_ring_dequeue_zc_burst_start(struct rte_ring * r, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * available) { return rte_ring_dequeue_zc_burst_start(r, n, zcd, available); }
void  deepeedeekay_rte_ring_dequeue_zc_elem_finish(struct rte_ring * r, unsigned int n) { return rte_ring_dequeue_zc_elem_finish(r, n); }
void  deepeedeekay_rte_ring_dequeue_zc_finish(struct rte_ring * r, unsigned int n) { return rte_ring_dequeue_zc_finish(r, n); }
unsigned int  deepeedeekay_rte_ring_mp_enqueue_bulk(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space) { return rte_ring_mp_enqueue_bulk(r, obj_table, n, free_space); }
unsigned int  deepeedeekay_rte_ring_sp_enqueue_bulk(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space) { return rte_ring_sp_enqueue_bulk(r, obj_table, n, free_space); }
unsigned int  deepeedeekay_rte_ring_enqueue_bulk(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space) { return rte_ring_enqueue_bulk(r, obj_table, n, free_space); }
int  deepeedeekay_rte_ring_mp_enqueue(struct rte_ring * r, void * obj) { return rte_ring_mp_enqueue(r, obj); }
int  deepeedeekay_rte_ring_sp_enqueue(struct rte_ring * r, void * obj) { return rte_ring_sp_enqueue(r, obj); }
int  deepeedeekay_rte_ring_enqueue(struct rte_ring * r, void * obj) { return rte_ring_enqueue(r, obj); }
unsigned int  deepeedeekay_rte_ring_mc_dequeue_bulk(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_mc_dequeue_bulk(r, obj_table, n, available); }
unsigned int  deepeedeekay_rte_ring_sc_dequeue_bulk(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_sc_dequeue_bulk(r, obj_table, n, available); }
unsigned int  deepeedeekay_rte_ring_dequeue_bulk(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_dequeue_bulk(r, obj_table, n, available); }
int  deepeedeekay_rte_ring_mc_dequeue(struct rte_ring * r, void ** obj_p) { return rte_ring_mc_dequeue(r, obj_p); }
int  deepeedeekay_rte_ring_sc_dequeue(struct rte_ring * r, void ** obj_p) { return rte_ring_sc_dequeue(r, obj_p); }
int  deepeedeekay_rte_ring_dequeue(struct rte_ring * r, void ** obj_p) { return rte_ring_dequeue(r, obj_p); }
unsigned int  deepeedeekay_rte_ring_count(const struct rte_ring * r) { return rte_ring_count(r); }
unsigned int  deepeedeekay_rte_ring_free_count(const struct rte_ring * r) { return rte_ring_free_count(r); }
int  deepeedeekay_rte_ring_full(const struct rte_ring * r) { return rte_ring_full(r); }
int  deepeedeekay_rte_ring_empty(const struct rte_ring * r) { return rte_ring_empty(r); }
unsigned int  deepeedeekay_rte_ring_get_size(const struct rte_ring * r) { return rte_ring_get_size(r); }
unsigned int  deepeedeekay_rte_ring_get_capacity(const struct rte_ring * r) { return rte_ring_get_capacity(r); }
enum rte_ring_sync_type  deepeedeekay_rte_ring_get_prod_sync_type(const struct rte_ring * r) { return rte_ring_get_prod_sync_type(r); }
int  deepeedeekay_rte_ring_is_prod_single(const struct rte_ring * r) { return rte_ring_is_prod_single(r); }
enum rte_ring_sync_type  deepeedeekay_rte_ring_get_cons_sync_type(const struct rte_ring * r) { return rte_ring_get_cons_sync_type(r); }
int  deepeedeekay_rte_ring_is_cons_single(const struct rte_ring * r) { return rte_ring_is_cons_single(r); }
unsigned int  deepeedeekay_rte_ring_mp_enqueue_burst(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space) { return rte_ring_mp_enqueue_burst(r, obj_table, n, free_space); }
unsigned int  deepeedeekay_rte_ring_sp_enqueue_burst(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space) { return rte_ring_sp_enqueue_burst(r, obj_table, n, free_space); }
unsigned int  deepeedeekay_rte_ring_enqueue_burst(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space) { return rte_ring_enqueue_burst(r, obj_table, n, free_space); }
unsigned int  deepeedeekay_rte_ring_mc_dequeue_burst(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_mc_dequeue_burst(r, obj_table, n, available); }
unsigned int  deepeedeekay_rte_ring_sc_dequeue_burst(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_sc_dequeue_burst(r, obj_table, n, available); }
unsigned int  deepeedeekay_rte_ring_dequeue_burst(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available) { return rte_ring_dequeue_burst(r, obj_table, n, available); }
size_t  deepeedeekay_rte_strlcpy(char * dst, const char * src, size_t size) { return rte_strlcpy(dst, src, size); }
size_t  deepeedeekay_rte_strlcat(char * dst, const char * src, size_t size) { return rte_strlcat(dst, src, size); }
const char * deepeedeekay_rte_str_skip_leading_spaces(const char * src) { return rte_str_skip_leading_spaces(src); }
bool  deepeedeekay_rte_trace_feature_is_enabled() { return rte_trace_feature_is_enabled(); }
void  deepeedeekay_rte_ethdev_trace_rx_burst_empty(uint16_t port_id, uint16_t queue_id, void ** pkt_tbl) { return rte_ethdev_trace_rx_burst_empty(port_id, queue_id, pkt_tbl); }
void  deepeedeekay_rte_ethdev_trace_rx_burst_nonempty(uint16_t port_id, uint16_t queue_id, void ** pkt_tbl, uint16_t nb_rx) { return rte_ethdev_trace_rx_burst_nonempty(port_id, queue_id, pkt_tbl, nb_rx); }
void  deepeedeekay_rte_ethdev_trace_tx_burst(uint16_t port_id, uint16_t queue_id, void ** pkts_tbl, uint16_t nb_pkts) { return rte_ethdev_trace_tx_burst(port_id, queue_id, pkts_tbl, nb_pkts); }
void  deepeedeekay_rte_eth_trace_call_rx_callbacks_empty(uint16_t port_id, uint16_t queue_id, void ** rx_pkts, uint16_t nb_pkts) { return rte_eth_trace_call_rx_callbacks_empty(port_id, queue_id, rx_pkts, nb_pkts); }
void  deepeedeekay_rte_eth_trace_call_rx_callbacks_nonempty(uint16_t port_id, uint16_t queue_id, void ** rx_pkts, uint16_t nb_rx, uint16_t nb_pkts) { return rte_eth_trace_call_rx_callbacks_nonempty(port_id, queue_id, rx_pkts, nb_rx, nb_pkts); }
void  deepeedeekay_rte_eth_trace_call_tx_callbacks(uint16_t port_id, uint16_t queue_id, void ** tx_pkts, uint16_t nb_pkts) { return rte_eth_trace_call_tx_callbacks(port_id, queue_id, tx_pkts, nb_pkts); }
void  deepeedeekay_rte_eth_trace_tx_buffer_drop_callback(void ** pkts, uint16_t unsent) { return rte_eth_trace_tx_buffer_drop_callback(pkts, unsent); }
void  deepeedeekay_rte_eth_trace_tx_buffer_count_callback(void ** pkts, uint16_t unsent, uint64_t count) { return rte_eth_trace_tx_buffer_count_callback(pkts, unsent, count); }
void  deepeedeekay_rte_eth_trace_tx_queue_count(uint16_t port_id, uint16_t queue_id, int rc) { return rte_eth_trace_tx_queue_count(port_id, queue_id, rc); }
uint64_t  deepeedeekay_rte_eth_rss_hf_refine(uint64_t rss_hf) { return rte_eth_rss_hf_refine(rss_hf); }
void * deepeedeekay_rte_memcpy(void * dst, const void * src, size_t n) { return rte_memcpy(dst, src, n); }
void * deepeedeekay_rte_mov15_or_less(void * dst, const void * src, size_t n) { return rte_mov15_or_less(dst, src, n); }
void  deepeedeekay_rte_mov16(uint8_t * dst, const uint8_t * src) { return rte_mov16(dst, src); }
void  deepeedeekay_rte_mov32(uint8_t * dst, const uint8_t * src) { return rte_mov32(dst, src); }
void  deepeedeekay_rte_mov64(uint8_t * dst, const uint8_t * src) { return rte_mov64(dst, src); }
void  deepeedeekay_rte_mov128(uint8_t * dst, const uint8_t * src) { return rte_mov128(dst, src); }
void  deepeedeekay_rte_mov256(uint8_t * dst, const uint8_t * src) { return rte_mov256(dst, src); }
void * deepeedeekay_rte_memcpy_generic(void * dst, const void * src, size_t n) { return rte_memcpy_generic(dst, src, n); }
void * deepeedeekay_rte_memcpy_aligned(void * dst, const void * src, size_t n) { return rte_memcpy_aligned(dst, src, n); }
void  deepeedeekay_rte_mempool_trace_ops_dequeue_bulk(void * mempool, void ** obj_table, uint32_t nb_objs) { return rte_mempool_trace_ops_dequeue_bulk(mempool, obj_table, nb_objs); }
void  deepeedeekay_rte_mempool_trace_ops_dequeue_contig_blocks(void * mempool, void ** first_obj_table, uint32_t nb_objs) { return rte_mempool_trace_ops_dequeue_contig_blocks(mempool, first_obj_table, nb_objs); }
void  deepeedeekay_rte_mempool_trace_ops_enqueue_bulk(void * mempool, void *const * obj_table, uint32_t nb_objs) { return rte_mempool_trace_ops_enqueue_bulk(mempool, obj_table, nb_objs); }
void  deepeedeekay_rte_mempool_trace_generic_put(void * mempool, void *const * obj_table, uint32_t nb_objs, void * cache) { return rte_mempool_trace_generic_put(mempool, obj_table, nb_objs, cache); }
void  deepeedeekay_rte_mempool_trace_put_bulk(void * mempool, void *const * obj_table, uint32_t nb_objs, void * cache) { return rte_mempool_trace_put_bulk(mempool, obj_table, nb_objs, cache); }
void  deepeedeekay_rte_mempool_trace_generic_get(void * mempool, void *const * obj_table, uint32_t nb_objs, void * cache) { return rte_mempool_trace_generic_get(mempool, obj_table, nb_objs, cache); }
void  deepeedeekay_rte_mempool_trace_get_bulk(void * mempool, void ** obj_table, uint32_t nb_objs, void * cache) { return rte_mempool_trace_get_bulk(mempool, obj_table, nb_objs, cache); }
void  deepeedeekay_rte_mempool_trace_get_contig_blocks(void * mempool, void ** first_obj_table, uint32_t nb_objs) { return rte_mempool_trace_get_contig_blocks(mempool, first_obj_table, nb_objs); }
void  deepeedeekay_rte_mempool_trace_default_cache(void * mempool, uint32_t lcore_id, void * default_cache) { return rte_mempool_trace_default_cache(mempool, lcore_id, default_cache); }
void  deepeedeekay_rte_mempool_trace_cache_flush(void * cache, void * mempool) { return rte_mempool_trace_cache_flush(cache, mempool); }
struct rte_mempool_objhdr * deepeedeekay_rte_mempool_get_header(void * obj) { return rte_mempool_get_header(obj); }
struct rte_mempool * deepeedeekay_rte_mempool_from_obj(void * obj) { return rte_mempool_from_obj(obj); }
struct rte_mempool_objtlr * deepeedeekay_rte_mempool_get_trailer(void * obj) { return rte_mempool_get_trailer(obj); }
struct rte_mempool_ops * deepeedeekay_rte_mempool_get_ops(int ops_index) { return rte_mempool_get_ops(ops_index); }
int  deepeedeekay_rte_mempool_ops_dequeue_bulk(struct rte_mempool * mp, void ** obj_table, unsigned int n) { return rte_mempool_ops_dequeue_bulk(mp, obj_table, n); }
int  deepeedeekay_rte_mempool_ops_dequeue_contig_blocks(struct rte_mempool * mp, void ** first_obj_table, unsigned int n) { return rte_mempool_ops_dequeue_contig_blocks(mp, first_obj_table, n); }
int  deepeedeekay_rte_mempool_ops_enqueue_bulk(struct rte_mempool * mp, void *const * obj_table, unsigned int n) { return rte_mempool_ops_enqueue_bulk(mp, obj_table, n); }
struct rte_mempool_cache * deepeedeekay_rte_mempool_default_cache(struct rte_mempool * mp, unsigned int lcore_id) { return rte_mempool_default_cache(mp, lcore_id); }
void  deepeedeekay_rte_mempool_cache_flush(struct rte_mempool_cache * cache, struct rte_mempool * mp) { return rte_mempool_cache_flush(cache, mp); }
void  deepeedeekay_rte_mempool_do_generic_put(struct rte_mempool * mp, void *const * obj_table, unsigned int n, struct rte_mempool_cache * cache) { return rte_mempool_do_generic_put(mp, obj_table, n, cache); }
void  deepeedeekay_rte_mempool_generic_put(struct rte_mempool * mp, void *const * obj_table, unsigned int n, struct rte_mempool_cache * cache) { return rte_mempool_generic_put(mp, obj_table, n, cache); }
void  deepeedeekay_rte_mempool_put_bulk(struct rte_mempool * mp, void *const * obj_table, unsigned int n) { return rte_mempool_put_bulk(mp, obj_table, n); }
void  deepeedeekay_rte_mempool_put(struct rte_mempool * mp, void * obj) { return rte_mempool_put(mp, obj); }
int  deepeedeekay_rte_mempool_do_generic_get(struct rte_mempool * mp, void ** obj_table, unsigned int n, struct rte_mempool_cache * cache) { return rte_mempool_do_generic_get(mp, obj_table, n, cache); }
int  deepeedeekay_rte_mempool_generic_get(struct rte_mempool * mp, void ** obj_table, unsigned int n, struct rte_mempool_cache * cache) { return rte_mempool_generic_get(mp, obj_table, n, cache); }
int  deepeedeekay_rte_mempool_get_bulk(struct rte_mempool * mp, void ** obj_table, unsigned int n) { return rte_mempool_get_bulk(mp, obj_table, n); }
int  deepeedeekay_rte_mempool_get(struct rte_mempool * mp, void ** obj_p) { return rte_mempool_get(mp, obj_p); }
int  deepeedeekay_rte_mempool_get_contig_blocks(struct rte_mempool * mp, void ** first_obj_table, unsigned int n) { return rte_mempool_get_contig_blocks(mp, first_obj_table, n); }
int  deepeedeekay_rte_mempool_full(const struct rte_mempool * mp) { return rte_mempool_full(mp); }
int  deepeedeekay_rte_mempool_empty(const struct rte_mempool * mp) { return rte_mempool_empty(mp); }
rte_iova_t  deepeedeekay_rte_mempool_virt2iova(const void * elt) { return rte_mempool_virt2iova(elt); }
void * deepeedeekay_rte_mempool_get_priv(struct rte_mempool * mp) { return rte_mempool_get_priv(mp); }
void  deepeedeekay_rte_prefetch0(const volatile void * p) { return rte_prefetch0(p); }
void  deepeedeekay_rte_prefetch1(const volatile void * p) { return rte_prefetch1(p); }
void  deepeedeekay_rte_prefetch2(const volatile void * p) { return rte_prefetch2(p); }
void  deepeedeekay_rte_prefetch_non_temporal(const volatile void * p) { return rte_prefetch_non_temporal(p); }
void  deepeedeekay_rte_prefetch0_write(const void * p) { return rte_prefetch0_write(p); }
void  deepeedeekay_rte_prefetch1_write(const void * p) { return rte_prefetch1_write(p); }
void  deepeedeekay_rte_prefetch2_write(const void * p) { return rte_prefetch2_write(p); }
void  deepeedeekay_rte_cldemote(const volatile void * p) { return rte_cldemote(p); }
uint16_t  deepeedeekay_rte_constant_bswap16(uint16_t x) { return rte_constant_bswap16(x); }
uint32_t  deepeedeekay_rte_constant_bswap32(uint32_t x) { return rte_constant_bswap32(x); }
uint64_t  deepeedeekay_rte_constant_bswap64(uint64_t x) { return rte_constant_bswap64(x); }
uint16_t  deepeedeekay_rte_arch_bswap16(uint16_t _x) { return rte_arch_bswap16(_x); }
uint32_t  deepeedeekay_rte_arch_bswap32(uint32_t _x) { return rte_arch_bswap32(_x); }
uint64_t  deepeedeekay_rte_arch_bswap64(uint64_t _x) { return rte_arch_bswap64(_x); }
void  deepeedeekay_rte_mbuf_prefetch_part1(struct rte_mbuf * m) { return rte_mbuf_prefetch_part1(m); }
void  deepeedeekay_rte_mbuf_prefetch_part2(struct rte_mbuf * m) { return rte_mbuf_prefetch_part2(m); }
uint16_t  deepeedeekay_rte_pktmbuf_priv_size(struct rte_mempool * mp) { return rte_pktmbuf_priv_size(mp); }
rte_iova_t  deepeedeekay_rte_mbuf_iova_get(const struct rte_mbuf * m) { return rte_mbuf_iova_get(m); }
void  deepeedeekay_rte_mbuf_iova_set(struct rte_mbuf * m, rte_iova_t iova) { return rte_mbuf_iova_set(m, iova); }
rte_iova_t  deepeedeekay_rte_mbuf_data_iova(const struct rte_mbuf * mb) { return rte_mbuf_data_iova(mb); }
rte_iova_t  deepeedeekay_rte_mbuf_data_iova_default(const struct rte_mbuf * mb) { return rte_mbuf_data_iova_default(mb); }
struct rte_mbuf * deepeedeekay_rte_mbuf_from_indirect(struct rte_mbuf * mi) { return rte_mbuf_from_indirect(mi); }
char * deepeedeekay_rte_mbuf_buf_addr(struct rte_mbuf * mb, struct rte_mempool * mp) { return rte_mbuf_buf_addr(mb, mp); }
char * deepeedeekay_rte_mbuf_data_addr_default(struct rte_mbuf * mb) { return rte_mbuf_data_addr_default(mb); }
char * deepeedeekay_rte_mbuf_to_baddr(struct rte_mbuf * md) { return rte_mbuf_to_baddr(md); }
void * deepeedeekay_rte_mbuf_to_priv(struct rte_mbuf * m) { return rte_mbuf_to_priv(m); }
uint32_t  deepeedeekay_rte_pktmbuf_priv_flags(struct rte_mempool * mp) { return rte_pktmbuf_priv_flags(mp); }
uint16_t  deepeedeekay_rte_mbuf_refcnt_read(const struct rte_mbuf * m) { return rte_mbuf_refcnt_read(m); }
void  deepeedeekay_rte_mbuf_refcnt_set(struct rte_mbuf * m, uint16_t new_value) { return rte_mbuf_refcnt_set(m, new_value); }
uint16_t  deepeedeekay_rte_mbuf_refcnt_update(struct rte_mbuf * m, int16_t value) { return rte_mbuf_refcnt_update(m, value); }
uint16_t  deepeedeekay_rte_mbuf_ext_refcnt_read(const struct rte_mbuf_ext_shared_info * shinfo) { return rte_mbuf_ext_refcnt_read(shinfo); }
void  deepeedeekay_rte_mbuf_ext_refcnt_set(struct rte_mbuf_ext_shared_info * shinfo, uint16_t new_value) { return rte_mbuf_ext_refcnt_set(shinfo, new_value); }
uint16_t  deepeedeekay_rte_mbuf_ext_refcnt_update(struct rte_mbuf_ext_shared_info * shinfo, int16_t value) { return rte_mbuf_ext_refcnt_update(shinfo, value); }
struct rte_mbuf * deepeedeekay_rte_mbuf_raw_alloc(struct rte_mempool * mp) { return rte_mbuf_raw_alloc(mp); }
void  deepeedeekay_rte_mbuf_raw_free(struct rte_mbuf * m) { return rte_mbuf_raw_free(m); }
uint16_t  deepeedeekay_rte_pktmbuf_data_room_size(struct rte_mempool * mp) { return rte_pktmbuf_data_room_size(mp); }
void  deepeedeekay_rte_pktmbuf_reset_headroom(struct rte_mbuf * m) { return rte_pktmbuf_reset_headroom(m); }
void  deepeedeekay_rte_pktmbuf_reset(struct rte_mbuf * m) { return rte_pktmbuf_reset(m); }
struct rte_mbuf * deepeedeekay_rte_pktmbuf_alloc(struct rte_mempool * mp) { return rte_pktmbuf_alloc(mp); }
int  deepeedeekay_rte_pktmbuf_alloc_bulk(struct rte_mempool * pool, struct rte_mbuf ** mbufs, unsigned int count) { return rte_pktmbuf_alloc_bulk(pool, mbufs, count); }
struct rte_mbuf_ext_shared_info * deepeedeekay_rte_pktmbuf_ext_shinfo_init_helper(void * buf_addr, uint16_t * buf_len, rte_mbuf_extbuf_free_callback_t free_cb, void * fcb_opaque) { return rte_pktmbuf_ext_shinfo_init_helper(buf_addr, buf_len, free_cb, fcb_opaque); }
void  deepeedeekay_rte_pktmbuf_attach_extbuf(struct rte_mbuf * m, void * buf_addr, rte_iova_t buf_iova, uint16_t buf_len, struct rte_mbuf_ext_shared_info * shinfo) { return rte_pktmbuf_attach_extbuf(m, buf_addr, buf_iova, buf_len, shinfo); }
void  deepeedeekay_rte_mbuf_dynfield_copy(struct rte_mbuf * mdst, const struct rte_mbuf * msrc) { return rte_mbuf_dynfield_copy(mdst, msrc); }
void  deepeedeekay_rte_pktmbuf_attach(struct rte_mbuf * mi, struct rte_mbuf * m) { return rte_pktmbuf_attach(mi, m); }
void  deepeedeekay_rte_pktmbuf_detach(struct rte_mbuf * m) { return rte_pktmbuf_detach(m); }
struct rte_mbuf * deepeedeekay_rte_pktmbuf_prefree_seg(struct rte_mbuf * m) { return rte_pktmbuf_prefree_seg(m); }
void  deepeedeekay_rte_pktmbuf_free_seg(struct rte_mbuf * m) { return rte_pktmbuf_free_seg(m); }
void  deepeedeekay_rte_pktmbuf_free(struct rte_mbuf * m) { return rte_pktmbuf_free(m); }
void  deepeedeekay_rte_pktmbuf_refcnt_update(struct rte_mbuf * m, int16_t v) { return rte_pktmbuf_refcnt_update(m, v); }
uint16_t  deepeedeekay_rte_pktmbuf_headroom(const struct rte_mbuf * m) { return rte_pktmbuf_headroom(m); }
uint16_t  deepeedeekay_rte_pktmbuf_tailroom(const struct rte_mbuf * m) { return rte_pktmbuf_tailroom(m); }
struct rte_mbuf * deepeedeekay_rte_pktmbuf_lastseg(struct rte_mbuf * m) { return rte_pktmbuf_lastseg(m); }
char * deepeedeekay_rte_pktmbuf_prepend(struct rte_mbuf * m, uint16_t len) { return rte_pktmbuf_prepend(m, len); }
char * deepeedeekay_rte_pktmbuf_append(struct rte_mbuf * m, uint16_t len) { return rte_pktmbuf_append(m, len); }
char * deepeedeekay_rte_pktmbuf_adj(struct rte_mbuf * m, uint16_t len) { return rte_pktmbuf_adj(m, len); }
int  deepeedeekay_rte_pktmbuf_trim(struct rte_mbuf * m, uint16_t len) { return rte_pktmbuf_trim(m, len); }
int  deepeedeekay_rte_pktmbuf_is_contiguous(const struct rte_mbuf * m) { return rte_pktmbuf_is_contiguous(m); }
const void * deepeedeekay_rte_pktmbuf_read(const struct rte_mbuf * m, uint32_t off, uint32_t len, void * buf) { return rte_pktmbuf_read(m, off, len, buf); }
int  deepeedeekay_rte_pktmbuf_chain(struct rte_mbuf * head, struct rte_mbuf * tail) { return rte_pktmbuf_chain(head, tail); }
uint64_t  deepeedeekay_rte_mbuf_tx_offload(uint64_t il2, uint64_t il3, uint64_t il4, uint64_t tso, uint64_t ol3, uint64_t ol2, uint64_t unused) { return rte_mbuf_tx_offload(il2, il3, il4, tso, ol3, ol2, unused); }
int  deepeedeekay_rte_validate_tx_offload(const struct rte_mbuf * m) { return rte_validate_tx_offload(m); }
int  deepeedeekay_rte_pktmbuf_linearize(struct rte_mbuf * mbuf) { return rte_pktmbuf_linearize(mbuf); }
uint32_t  deepeedeekay_rte_mbuf_sched_queue_get(const struct rte_mbuf * m) { return rte_mbuf_sched_queue_get(m); }
uint8_t  deepeedeekay_rte_mbuf_sched_traffic_class_get(const struct rte_mbuf * m) { return rte_mbuf_sched_traffic_class_get(m); }
uint8_t  deepeedeekay_rte_mbuf_sched_color_get(const struct rte_mbuf * m) { return rte_mbuf_sched_color_get(m); }
void  deepeedeekay_rte_mbuf_sched_get(const struct rte_mbuf * m, uint32_t * queue_id, uint8_t * traffic_class, uint8_t * color) { return rte_mbuf_sched_get(m, queue_id, traffic_class, color); }
void  deepeedeekay_rte_mbuf_sched_queue_set(struct rte_mbuf * m, uint32_t queue_id) { return rte_mbuf_sched_queue_set(m, queue_id); }
void  deepeedeekay_rte_mbuf_sched_traffic_class_set(struct rte_mbuf * m, uint8_t traffic_class) { return rte_mbuf_sched_traffic_class_set(m, traffic_class); }
void  deepeedeekay_rte_mbuf_sched_color_set(struct rte_mbuf * m, uint8_t color) { return rte_mbuf_sched_color_set(m, color); }
void  deepeedeekay_rte_mbuf_sched_set(struct rte_mbuf * m, uint32_t queue_id, uint8_t traffic_class, uint8_t color) { return rte_mbuf_sched_set(m, queue_id, traffic_class, color); }
int  deepeedeekay_rte_is_same_ether_addr(const struct rte_ether_addr * ea1, const struct rte_ether_addr * ea2) { return rte_is_same_ether_addr(ea1, ea2); }
int  deepeedeekay_rte_is_zero_ether_addr(const struct rte_ether_addr * ea) { return rte_is_zero_ether_addr(ea); }
int  deepeedeekay_rte_is_unicast_ether_addr(const struct rte_ether_addr * ea) { return rte_is_unicast_ether_addr(ea); }
int  deepeedeekay_rte_is_multicast_ether_addr(const struct rte_ether_addr * ea) { return rte_is_multicast_ether_addr(ea); }
int  deepeedeekay_rte_is_broadcast_ether_addr(const struct rte_ether_addr * ea) { return rte_is_broadcast_ether_addr(ea); }
int  deepeedeekay_rte_is_universal_ether_addr(const struct rte_ether_addr * ea) { return rte_is_universal_ether_addr(ea); }
int  deepeedeekay_rte_is_local_admin_ether_addr(const struct rte_ether_addr * ea) { return rte_is_local_admin_ether_addr(ea); }
int  deepeedeekay_rte_is_valid_assigned_ether_addr(const struct rte_ether_addr * ea) { return rte_is_valid_assigned_ether_addr(ea); }
void  deepeedeekay_rte_ether_addr_copy(const struct rte_ether_addr *restrict ea_from, struct rte_ether_addr *restrict ea_to) { return rte_ether_addr_copy(ea_from, ea_to); }
int  deepeedeekay_rte_vlan_strip(struct rte_mbuf * m) { return rte_vlan_strip(m); }
int  deepeedeekay_rte_vlan_insert(struct rte_mbuf ** m) { return rte_vlan_insert(m); }
uint16_t  deepeedeekay_rte_raw_cksum(const void * buf, size_t len) { return rte_raw_cksum(buf, len); }
int  deepeedeekay_rte_raw_cksum_mbuf(const struct rte_mbuf * m, uint32_t off, uint32_t len, uint16_t * cksum) { return rte_raw_cksum_mbuf(m, off, len, cksum); }
uint8_t  deepeedeekay_rte_ipv4_hdr_len(const struct rte_ipv4_hdr * ipv4_hdr) { return rte_ipv4_hdr_len(ipv4_hdr); }
uint16_t  deepeedeekay_rte_ipv4_cksum(const struct rte_ipv4_hdr * ipv4_hdr) { return rte_ipv4_cksum(ipv4_hdr); }
uint16_t  deepeedeekay_rte_ipv4_cksum_simple(const struct rte_ipv4_hdr * ipv4_hdr) { return rte_ipv4_cksum_simple(ipv4_hdr); }
uint16_t  deepeedeekay_rte_ipv4_phdr_cksum(const struct rte_ipv4_hdr * ipv4_hdr, uint64_t ol_flags) { return rte_ipv4_phdr_cksum(ipv4_hdr, ol_flags); }
uint16_t  deepeedeekay_rte_ipv4_udptcp_cksum(const struct rte_ipv4_hdr * ipv4_hdr, const void * l4_hdr) { return rte_ipv4_udptcp_cksum(ipv4_hdr, l4_hdr); }
uint16_t  deepeedeekay_rte_ipv4_udptcp_cksum_mbuf(const struct rte_mbuf * m, const struct rte_ipv4_hdr * ipv4_hdr, uint16_t l4_off) { return rte_ipv4_udptcp_cksum_mbuf(m, ipv4_hdr, l4_off); }
int  deepeedeekay_rte_ipv4_udptcp_cksum_verify(const struct rte_ipv4_hdr * ipv4_hdr, const void * l4_hdr) { return rte_ipv4_udptcp_cksum_verify(ipv4_hdr, l4_hdr); }
int  deepeedeekay_rte_ipv4_udptcp_cksum_mbuf_verify(const struct rte_mbuf * m, const struct rte_ipv4_hdr * ipv4_hdr, uint16_t l4_off) { return rte_ipv4_udptcp_cksum_mbuf_verify(m, ipv4_hdr, l4_off); }
bool  deepeedeekay_rte_ipv6_addr_eq(const struct rte_ipv6_addr * a, const struct rte_ipv6_addr * b) { return rte_ipv6_addr_eq(a, b); }
void  deepeedeekay_rte_ipv6_addr_mask(struct rte_ipv6_addr * ip, uint8_t depth) { return rte_ipv6_addr_mask(ip, depth); }
bool  deepeedeekay_rte_ipv6_addr_eq_prefix(const struct rte_ipv6_addr * a, const struct rte_ipv6_addr * b, uint8_t depth) { return rte_ipv6_addr_eq_prefix(a, b, depth); }
uint8_t  deepeedeekay_rte_ipv6_mask_depth(const struct rte_ipv6_addr * mask) { return rte_ipv6_mask_depth(mask); }
bool  deepeedeekay_rte_ipv6_addr_is_unspec(const struct rte_ipv6_addr * ip) { return rte_ipv6_addr_is_unspec(ip); }
bool  deepeedeekay_rte_ipv6_addr_is_loopback(const struct rte_ipv6_addr * ip) { return rte_ipv6_addr_is_loopback(ip); }
bool  deepeedeekay_rte_ipv6_addr_is_linklocal(const struct rte_ipv6_addr * ip) { return rte_ipv6_addr_is_linklocal(ip); }
bool  deepeedeekay_rte_ipv6_addr_is_sitelocal(const struct rte_ipv6_addr * ip) { return rte_ipv6_addr_is_sitelocal(ip); }
bool  deepeedeekay_rte_ipv6_addr_is_v4compat(const struct rte_ipv6_addr * ip) { return rte_ipv6_addr_is_v4compat(ip); }
bool  deepeedeekay_rte_ipv6_addr_is_v4mapped(const struct rte_ipv6_addr * ip) { return rte_ipv6_addr_is_v4mapped(ip); }
bool  deepeedeekay_rte_ipv6_addr_is_mcast(const struct rte_ipv6_addr * ip) { return rte_ipv6_addr_is_mcast(ip); }
enum rte_ipv6_mc_scope  deepeedeekay_rte_ipv6_mc_scope(const struct rte_ipv6_addr * ip) { return rte_ipv6_mc_scope(ip); }
void  deepeedeekay_rte_ipv6_llocal_from_ethernet(struct rte_ipv6_addr * ip, const struct rte_ether_addr * mac) { return rte_ipv6_llocal_from_ethernet(ip, mac); }
void  deepeedeekay_rte_ipv6_solnode_from_addr(struct rte_ipv6_addr * sol, const struct rte_ipv6_addr * ip) { return rte_ipv6_solnode_from_addr(sol, ip); }
void  deepeedeekay_rte_ether_mcast_from_ipv6(struct rte_ether_addr * mac, const struct rte_ipv6_addr * ip) { return rte_ether_mcast_from_ipv6(mac, ip); }
int  deepeedeekay_rte_ipv6_check_version(const struct rte_ipv6_hdr * ip) { return rte_ipv6_check_version(ip); }
uint16_t  deepeedeekay_rte_ipv6_phdr_cksum(const struct rte_ipv6_hdr * ipv6_hdr, uint64_t ol_flags) { return rte_ipv6_phdr_cksum(ipv6_hdr, ol_flags); }
uint16_t  deepeedeekay_rte_ipv6_udptcp_cksum(const struct rte_ipv6_hdr * ipv6_hdr, const void * l4_hdr) { return rte_ipv6_udptcp_cksum(ipv6_hdr, l4_hdr); }
uint16_t  deepeedeekay_rte_ipv6_udptcp_cksum_mbuf(const struct rte_mbuf * m, const struct rte_ipv6_hdr * ipv6_hdr, uint16_t l4_off) { return rte_ipv6_udptcp_cksum_mbuf(m, ipv6_hdr, l4_off); }
int  deepeedeekay_rte_ipv6_udptcp_cksum_verify(const struct rte_ipv6_hdr * ipv6_hdr, const void * l4_hdr) { return rte_ipv6_udptcp_cksum_verify(ipv6_hdr, l4_hdr); }
int  deepeedeekay_rte_ipv6_udptcp_cksum_mbuf_verify(const struct rte_mbuf * m, const struct rte_ipv6_hdr * ipv6_hdr, uint16_t l4_off) { return rte_ipv6_udptcp_cksum_mbuf_verify(m, ipv6_hdr, l4_off); }
int  deepeedeekay_rte_ipv6_get_next_ext(const uint8_t * p, int proto, size_t * ext_len) { return rte_ipv6_get_next_ext(p, proto, ext_len); }
enum rte_color  deepeedeekay_rte_meter_srtcm_color_blind_check(struct rte_meter_srtcm * m, struct rte_meter_srtcm_profile * p, uint64_t time, uint32_t pkt_len) { return rte_meter_srtcm_color_blind_check(m, p, time, pkt_len); }
enum rte_color  deepeedeekay_rte_meter_srtcm_color_aware_check(struct rte_meter_srtcm * m, struct rte_meter_srtcm_profile * p, uint64_t time, uint32_t pkt_len, enum rte_color pkt_color) { return rte_meter_srtcm_color_aware_check(m, p, time, pkt_len, pkt_color); }
enum rte_color  deepeedeekay_rte_meter_trtcm_color_blind_check(struct rte_meter_trtcm * m, struct rte_meter_trtcm_profile * p, uint64_t time, uint32_t pkt_len) { return rte_meter_trtcm_color_blind_check(m, p, time, pkt_len); }
enum rte_color  deepeedeekay_rte_meter_trtcm_color_aware_check(struct rte_meter_trtcm * m, struct rte_meter_trtcm_profile * p, uint64_t time, uint32_t pkt_len, enum rte_color pkt_color) { return rte_meter_trtcm_color_aware_check(m, p, time, pkt_len, pkt_color); }
enum rte_color  deepeedeekay_rte_meter_trtcm_rfc4115_color_blind_check(struct rte_meter_trtcm_rfc4115 * m, struct rte_meter_trtcm_rfc4115_profile * p, uint64_t time, uint32_t pkt_len) { return rte_meter_trtcm_rfc4115_color_blind_check(m, p, time, pkt_len); }
enum rte_color  deepeedeekay_rte_meter_trtcm_rfc4115_color_aware_check(struct rte_meter_trtcm_rfc4115 * m, struct rte_meter_trtcm_rfc4115_profile * p, uint64_t time, uint32_t pkt_len, enum rte_color pkt_color) { return rte_meter_trtcm_rfc4115_color_aware_check(m, p, time, pkt_len, pkt_color); }
uint32_t  deepeedeekay_rte_flow_dynf_metadata_get(struct rte_mbuf * m) { return rte_flow_dynf_metadata_get(m); }
void  deepeedeekay_rte_flow_dynf_metadata_set(struct rte_mbuf * m, uint32_t v) { return rte_flow_dynf_metadata_set(m, v); }
int  deepeedeekay_rte_flow_dynf_metadata_avail() { return rte_flow_dynf_metadata_avail(); }
uint16_t  deepeedeekay_rte_eth_rx_burst(uint16_t port_id, uint16_t queue_id, struct rte_mbuf ** rx_pkts, const uint16_t nb_pkts) { return rte_eth_rx_burst(port_id, queue_id, rx_pkts, nb_pkts); }
int  deepeedeekay_rte_eth_rx_queue_count(uint16_t port_id, uint16_t queue_id) { return rte_eth_rx_queue_count(port_id, queue_id); }
int  deepeedeekay_rte_eth_rx_descriptor_status(uint16_t port_id, uint16_t queue_id, uint16_t offset) { return rte_eth_rx_descriptor_status(port_id, queue_id, offset); }
int  deepeedeekay_rte_eth_tx_descriptor_status(uint16_t port_id, uint16_t queue_id, uint16_t offset) { return rte_eth_tx_descriptor_status(port_id, queue_id, offset); }
uint16_t  deepeedeekay_rte_eth_tx_burst(uint16_t port_id, uint16_t queue_id, struct rte_mbuf ** tx_pkts, uint16_t nb_pkts) { return rte_eth_tx_burst(port_id, queue_id, tx_pkts, nb_pkts); }
uint16_t  deepeedeekay_rte_eth_tx_prepare(uint16_t port_id, uint16_t queue_id, struct rte_mbuf ** tx_pkts, uint16_t nb_pkts) { return rte_eth_tx_prepare(port_id, queue_id, tx_pkts, nb_pkts); }
uint16_t  deepeedeekay_rte_eth_tx_buffer_flush(uint16_t port_id, uint16_t queue_id, struct rte_eth_dev_tx_buffer * buffer) { return rte_eth_tx_buffer_flush(port_id, queue_id, buffer); }
uint16_t  deepeedeekay_rte_eth_tx_buffer(uint16_t port_id, uint16_t queue_id, struct rte_eth_dev_tx_buffer * buffer, struct rte_mbuf * tx_pkt) { return rte_eth_tx_buffer(port_id, queue_id, buffer, tx_pkt); }
uint16_t  deepeedeekay_rte_eth_recycle_mbufs(uint16_t rx_port_id, uint16_t rx_queue_id, uint16_t tx_port_id, uint16_t tx_queue_id, struct rte_eth_recycle_rxq_info * recycle_rxq_info) { return rte_eth_recycle_mbufs(rx_port_id, rx_queue_id, tx_port_id, tx_queue_id, recycle_rxq_info); }
int  deepeedeekay_rte_eth_tx_queue_count(uint16_t port_id, uint16_t queue_id) { return rte_eth_tx_queue_count(port_id, queue_id); }