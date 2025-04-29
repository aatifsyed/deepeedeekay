#include "../bind.h"

/**
 Checks if a pointer is aligned to a given power-of-two value
 
in param ptr
   The pointer whose alignment is to be checked 
in param align
   The power-of-two value to which the ptr should be aligned
 
return
   True(1) where the pointer is correctly aligned, false(0) otherwise*/
int  deepeedeekay_rte_is_aligned(const void *const restrict ptr, const unsigned int align);
/**
 Copy uuid.
 
in param dst
    Destination uuid 
in param src
    Source uuid*/
void  deepeedeekay_rte_uuid_copy(unsigned char * dst, const unsigned char * src);
/**
 Get system unique thread id.
 
return
   On success, returns the thread ID of calling process.   It is always successful.*/
int  deepeedeekay_rte_gettid();
/**
 Get the target bit from a 32-bit value without memory ordering.
 
in param nr
   The target bit to get. 
in param addr
   The address holding the bit. 
return
   The target bit.*/
uint32_t  deepeedeekay_rte_bit_relaxed_get32(unsigned int nr, volatile uint32_t * addr);
/**
 Set the target bit in a 32-bit value to 1 without memory ordering.
 
in param nr
   The target bit to set. 
in param addr
   The address holding the bit.*/
void  deepeedeekay_rte_bit_relaxed_set32(unsigned int nr, volatile uint32_t * addr);
/**
 Clear the target bit in a 32-bit value to 0 without memory ordering.
 
in param nr
   The target bit to clear. 
in param addr
   The address holding the bit.*/
void  deepeedeekay_rte_bit_relaxed_clear32(unsigned int nr, volatile uint32_t * addr);
/**
 Return the original bit from a 32-bit value, then set it to 1 without memory ordering.
 
in param nr
   The target bit to get and set. 
in param addr
   The address holding the bit. 
return
   The original bit.*/
uint32_t  deepeedeekay_rte_bit_relaxed_test_and_set32(unsigned int nr, volatile uint32_t * addr);
/**
 Return the original bit from a 32-bit value, then clear it to 0 without memory ordering.
 
in param nr
   The target bit to get and clear. 
in param addr
   The address holding the bit. 
return
   The original bit.*/
uint32_t  deepeedeekay_rte_bit_relaxed_test_and_clear32(unsigned int nr, volatile uint32_t * addr);
/**
 Get the target bit from a 64-bit value without memory ordering.
 
in param nr
   The target bit to get. 
in param addr
   The address holding the bit. 
return
   The target bit.*/
uint64_t  deepeedeekay_rte_bit_relaxed_get64(unsigned int nr, volatile uint64_t * addr);
/**
 Set the target bit in a 64-bit value to 1 without memory ordering.
 
in param nr
   The target bit to set. 
in param addr
   The address holding the bit.*/
void  deepeedeekay_rte_bit_relaxed_set64(unsigned int nr, volatile uint64_t * addr);
/**
 Clear the target bit in a 64-bit value to 0 without memory ordering.
 
in param nr
   The target bit to clear. 
in param addr
   The address holding the bit.*/
void  deepeedeekay_rte_bit_relaxed_clear64(unsigned int nr, volatile uint64_t * addr);
/**
 Return the original bit from a 64-bit value, then set it to 1 without memory ordering.
 
in param nr
   The target bit to get and set. 
in param addr
   The address holding the bit. 
return
   The original bit.*/
uint64_t  deepeedeekay_rte_bit_relaxed_test_and_set64(unsigned int nr, volatile uint64_t * addr);
/**
 Return the original bit from a 64-bit value, then clear it to 0 without memory ordering.
 
in param nr
   The target bit to get and clear. 
in param addr
   The address holding the bit. 
return
   The original bit.*/
uint64_t  deepeedeekay_rte_bit_relaxed_test_and_clear64(unsigned int nr, volatile uint64_t * addr);
/**
 Get the count of leading 0-bits in v.
 
in param v
   The value. 
return
   The count of leading zero bits.*/
unsigned int  deepeedeekay_rte_clz32(uint32_t v);
/**
 Get the count of leading 0-bits in v.
 
in param v
   The value. 
return
   The count of leading zero bits.*/
unsigned int  deepeedeekay_rte_clz64(uint64_t v);
/**
 Get the count of trailing 0-bits in v.
 
in param v
   The value. 
return
   The count of trailing zero bits.*/
unsigned int  deepeedeekay_rte_ctz32(uint32_t v);
/**
 Get the count of trailing 0-bits in v.
 
in param v
   The value. 
return
   The count of trailing zero bits.*/
unsigned int  deepeedeekay_rte_ctz64(uint64_t v);
/**
 Get the count of 1-bits in v.
 
in param v
   The value. 
return
   The count of 1-bits.*/
unsigned int  deepeedeekay_rte_popcount32(uint32_t v);
/**
 Get the count of 1-bits in v.
 
in param v
   The value. 
return
   The count of 1-bits.*/
unsigned int  deepeedeekay_rte_popcount64(uint64_t v);
/**
 Combines 32b inputs most significant set bits into the least significant bits to construct a value with the same MSBs as x but all 1's under it.
 
in param x
    The integer whose MSBs need to be combined with its LSBs 
return
    The combined value.*/
uint32_t  deepeedeekay_rte_combine32ms1b(uint32_t x);
/**
 Combines 64b inputs most significant set bits into the least significant bits to construct a value with the same MSBs as x but all 1's under it.
 
in param v
    The integer whose MSBs need to be combined with its LSBs 
return
    The combined value.*/
uint64_t  deepeedeekay_rte_combine64ms1b(uint64_t v);
/**
 Searches the input parameter for the least significant set bit (starting from zero). If a least significant 1 bit is found, its bit index is returned. If the content of the input parameter is zero, then the content of the return value is undefined. 
in param v
     input parameter, should not be zero. 
return
     least significant set bit in the input parameter.*/
uint32_t  deepeedeekay_rte_bsf32(uint32_t v);
/**
 Searches the input parameter for the least significant set bit (starting from zero). Safe version (checks for input parameter being zero).
 
warning
 ``pos`` must be a valid pointer. It is not checked!
 
in param v
     The input parameter. 
in param pos
     If ``v`` was not 0, this value will contain position of least significant     bit within the input parameter. 
return
     Returns 0 if ``v`` was 0, otherwise returns 1.*/
int  deepeedeekay_rte_bsf32_safe(uint32_t v, uint32_t * pos);
/**
 Searches the input parameter for the least significant set bit (starting from zero). If a least significant 1 bit is found, its bit index is returned. If the content of the input parameter is zero, then the content of the return value is undefined. 
in param v
     input parameter, should not be zero. 
return
     least significant set bit in the input parameter.*/
uint32_t  deepeedeekay_rte_bsf64(uint64_t v);
/**
 Searches the input parameter for the least significant set bit (starting from zero). Safe version (checks for input parameter being zero).
 
warning
 ``pos`` must be a valid pointer. It is not checked!
 
in param v
     The input parameter. 
in param pos
     If ``v`` was not 0, this value will contain position of least significant     bit within the input parameter. 
return
     Returns 0 if ``v`` was 0, otherwise returns 1.*/
int  deepeedeekay_rte_bsf64_safe(uint64_t v, uint32_t * pos);
/**
 Return the last (most-significant) bit set.
 
note
 The last (most significant) bit is at position 32. 
note
 rte_fls_u32(0) = 0, rte_fls_u32(1) = 1, rte_fls_u32(0x80000000) = 32
 
in param x
     The input parameter. 
return
     The last (most-significant) bit set, or 0 if the input is 0.*/
uint32_t  deepeedeekay_rte_fls_u32(uint32_t x);
/**
 Return the last (most-significant) bit set.
 
note
 The last (most significant) bit is at position 64. 
note
 rte_fls_u64(0) = 0, rte_fls_u64(1) = 1,       rte_fls_u64(0x8000000000000000) = 64
 
in param x
     The input parameter. 
return
     The last (most-significant) bit set, or 0 if the input is 0.*/
uint32_t  deepeedeekay_rte_fls_u64(uint64_t x);
/**
 Returns true if n is a power of 2 
in param n
     Number to check 
return
 1 if true, 0 otherwise*/
int  deepeedeekay_rte_is_power_of_2(uint32_t n);
/**
 Aligns input parameter to the next power of 2
 
in param x
   The integer value to align
 
return
   Input parameter aligned to the next power of 2*/
uint32_t  deepeedeekay_rte_align32pow2(uint32_t x);
/**
 Aligns input parameter to the previous power of 2
 
in param x
   The integer value to align
 
return
   Input parameter aligned to the previous power of 2*/
uint32_t  deepeedeekay_rte_align32prevpow2(uint32_t x);
/**
 Aligns 64b input parameter to the next power of 2
 
in param v
   The 64b value to align
 
return
   Input parameter aligned to the next power of 2*/
uint64_t  deepeedeekay_rte_align64pow2(uint64_t v);
/**
 Aligns 64b input parameter to the previous power of 2
 
in param v
   The 64b value to align
 
return
   Input parameter aligned to the previous power of 2*/
uint64_t  deepeedeekay_rte_align64prevpow2(uint64_t v);
/**
 Return the rounded-up log2 of a integer.
 
note
 Contrary to the logarithm mathematical operation, rte_log2_u32(0) == 0 and not -inf.
 
in param v
     The input parameter. 
return
     The rounded-up log2 of the input, or 0 if the input is 0.*/
uint32_t  deepeedeekay_rte_log2_u32(uint32_t v);
/**
 Return the rounded-up log2 of a 64-bit integer.
 
note
 Contrary to the logarithm mathematical operation, rte_log2_u64(0) == 0 and not -inf.
 
in param v
     The input parameter. 
return
     The rounded-up log2 of the input, or 0 if the input is 0.*/
uint32_t  deepeedeekay_rte_log2_u64(uint64_t v);
/**
 Synchronization fence between threads based on the specified memory order.*/
void  deepeedeekay_rte_atomic_thread_fence(rte_memory_order memorder);
/**
 Atomic compare and set.
 (atomic) equivalent to:   if (*dst == exp)     *dst = src (all 16-bit words)
 
in param dst
   The destination location into which the value will be written. 
in param exp
   The expected value. 
in param src
   The new value. 
return
   Non-zero on success; 0 on failure.*/
int  deepeedeekay_rte_atomic16_cmpset(volatile uint16_t * dst, uint16_t exp, uint16_t src);
/**
 Atomic exchange.
 (atomic) equivalent to:   ret = *dst   *dst = val;   return ret;
 
in param dst
   The destination location into which the value will be written. 
in param val
   The new value. 
return
   The original value at that location*/
uint16_t  deepeedeekay_rte_atomic16_exchange(volatile uint16_t * dst, uint16_t val);
/**
 Initialize an atomic counter.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic16_init(rte_atomic16_t * v);
/**
 Atomically read a 16-bit value from a counter.
 
in param v
   A pointer to the atomic counter. 
return
   The value of the counter.*/
int16_t  deepeedeekay_rte_atomic16_read(const rte_atomic16_t * v);
/**
 Atomically set a counter to a 16-bit value.
 
in param v
   A pointer to the atomic counter. 
in param new_value
   The new value for the counter.*/
void  deepeedeekay_rte_atomic16_set(rte_atomic16_t * v, int16_t new_value);
/**
 Atomically add a 16-bit value to an atomic counter.
 
in param v
   A pointer to the atomic counter. 
in param inc
   The value to be added to the counter.*/
void  deepeedeekay_rte_atomic16_add(rte_atomic16_t * v, int16_t inc);
/**
 Atomically subtract a 16-bit value from an atomic counter.
 
in param v
   A pointer to the atomic counter. 
in param dec
   The value to be subtracted from the counter.*/
void  deepeedeekay_rte_atomic16_sub(rte_atomic16_t * v, int16_t dec);
/**
 Atomically increment a counter by one.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic16_inc(rte_atomic16_t * v);
/**
 Atomically decrement a counter by one.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic16_dec(rte_atomic16_t * v);
/**
 Atomically add a 16-bit value to a counter and return the result.
 Atomically adds the 16-bits value (inc) to the atomic counter (v) and returns the value of v after addition.
 
in param v
   A pointer to the atomic counter. 
in param inc
   The value to be added to the counter. 
return
   The value of v after the addition.*/
int16_t  deepeedeekay_rte_atomic16_add_return(rte_atomic16_t * v, int16_t inc);
/**
 Atomically subtract a 16-bit value from a counter and return the result.
 Atomically subtracts the 16-bit value (inc) from the atomic counter (v) and returns the value of v after the subtraction.
 
in param v
   A pointer to the atomic counter. 
in param dec
   The value to be subtracted from the counter. 
return
   The value of v after the subtraction.*/
int16_t  deepeedeekay_rte_atomic16_sub_return(rte_atomic16_t * v, int16_t dec);
/**
 Atomically increment a 16-bit counter by one and test.
 Atomically increments the atomic counter (v) by one and returns true if the result is 0, or false in all other cases.
 
in param v
   A pointer to the atomic counter. 
return
   True if the result after the increment operation is 0; false otherwise.*/
int  deepeedeekay_rte_atomic16_inc_and_test(rte_atomic16_t * v);
/**
 Atomically decrement a 16-bit counter by one and test.
 Atomically decrements the atomic counter (v) by one and returns true if the result is 0, or false in all other cases.
 
in param v
   A pointer to the atomic counter. 
return
   True if the result after the decrement operation is 0; false otherwise.*/
int  deepeedeekay_rte_atomic16_dec_and_test(rte_atomic16_t * v);
/**
 Atomically test and set a 16-bit atomic counter.
 If the counter value is already set, return 0 (failed). Otherwise, set the counter value to 1 and return 1 (success).
 
in param v
   A pointer to the atomic counter. 
return
   0 if failed; else 1, success.*/
int  deepeedeekay_rte_atomic16_test_and_set(rte_atomic16_t * v);
/**
 Atomically set a 16-bit counter to 0.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic16_clear(rte_atomic16_t * v);
/**
 Atomic compare and set.
 (atomic) equivalent to:   if (*dst == exp)     *dst = src (all 32-bit words)
 
in param dst
   The destination location into which the value will be written. 
in param exp
   The expected value. 
in param src
   The new value. 
return
   Non-zero on success; 0 on failure.*/
int  deepeedeekay_rte_atomic32_cmpset(volatile uint32_t * dst, uint32_t exp, uint32_t src);
/**
 Atomic exchange.
 (atomic) equivalent to:   ret = *dst   *dst = val;   return ret;
 
in param dst
   The destination location into which the value will be written. 
in param val
   The new value. 
return
   The original value at that location*/
uint32_t  deepeedeekay_rte_atomic32_exchange(volatile uint32_t * dst, uint32_t val);
/**
 Initialize an atomic counter.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic32_init(rte_atomic32_t * v);
/**
 Atomically read a 32-bit value from a counter.
 
in param v
   A pointer to the atomic counter. 
return
   The value of the counter.*/
int32_t  deepeedeekay_rte_atomic32_read(const rte_atomic32_t * v);
/**
 Atomically set a counter to a 32-bit value.
 
in param v
   A pointer to the atomic counter. 
in param new_value
   The new value for the counter.*/
void  deepeedeekay_rte_atomic32_set(rte_atomic32_t * v, int32_t new_value);
/**
 Atomically add a 32-bit value to an atomic counter.
 
in param v
   A pointer to the atomic counter. 
in param inc
   The value to be added to the counter.*/
void  deepeedeekay_rte_atomic32_add(rte_atomic32_t * v, int32_t inc);
/**
 Atomically subtract a 32-bit value from an atomic counter.
 
in param v
   A pointer to the atomic counter. 
in param dec
   The value to be subtracted from the counter.*/
void  deepeedeekay_rte_atomic32_sub(rte_atomic32_t * v, int32_t dec);
/**
 Atomically increment a counter by one.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic32_inc(rte_atomic32_t * v);
/**
 Atomically decrement a counter by one.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic32_dec(rte_atomic32_t * v);
/**
 Atomically add a 32-bit value to a counter and return the result.
 Atomically adds the 32-bits value (inc) to the atomic counter (v) and returns the value of v after addition.
 
in param v
   A pointer to the atomic counter. 
in param inc
   The value to be added to the counter. 
return
   The value of v after the addition.*/
int32_t  deepeedeekay_rte_atomic32_add_return(rte_atomic32_t * v, int32_t inc);
/**
 Atomically subtract a 32-bit value from a counter and return the result.
 Atomically subtracts the 32-bit value (inc) from the atomic counter (v) and returns the value of v after the subtraction.
 
in param v
   A pointer to the atomic counter. 
in param dec
   The value to be subtracted from the counter. 
return
   The value of v after the subtraction.*/
int32_t  deepeedeekay_rte_atomic32_sub_return(rte_atomic32_t * v, int32_t dec);
/**
 Atomically increment a 32-bit counter by one and test.
 Atomically increments the atomic counter (v) by one and returns true if the result is 0, or false in all other cases.
 
in param v
   A pointer to the atomic counter. 
return
   True if the result after the increment operation is 0; false otherwise.*/
int  deepeedeekay_rte_atomic32_inc_and_test(rte_atomic32_t * v);
/**
 Atomically decrement a 32-bit counter by one and test.
 Atomically decrements the atomic counter (v) by one and returns true if the result is 0, or false in all other cases.
 
in param v
   A pointer to the atomic counter. 
return
   True if the result after the decrement operation is 0; false otherwise.*/
int  deepeedeekay_rte_atomic32_dec_and_test(rte_atomic32_t * v);
/**
 Atomically test and set a 32-bit atomic counter.
 If the counter value is already set, return 0 (failed). Otherwise, set the counter value to 1 and return 1 (success).
 
in param v
   A pointer to the atomic counter. 
return
   0 if failed; else 1, success.*/
int  deepeedeekay_rte_atomic32_test_and_set(rte_atomic32_t * v);
/**
 Atomically set a 32-bit counter to 0.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic32_clear(rte_atomic32_t * v);
/**
 An atomic compare and set function used by the mutex functions. (atomic) equivalent to:   if (*dst == exp)     *dst = src (all 64-bit words)
 
in param dst
   The destination into which the value will be written. 
in param exp
   The expected value. 
in param src
   The new value. 
return
   Non-zero on success; 0 on failure.*/
int  deepeedeekay_rte_atomic64_cmpset(volatile uint64_t * dst, uint64_t exp, uint64_t src);
/**
 Atomic exchange.
 (atomic) equivalent to:   ret = *dst   *dst = val;   return ret;
 
in param dst
   The destination location into which the value will be written. 
in param val
   The new value. 
return
   The original value at that location*/
uint64_t  deepeedeekay_rte_atomic64_exchange(volatile uint64_t * dst, uint64_t val);
/**
 Initialize the atomic counter.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic64_init(rte_atomic64_t * v);
/**
 Atomically read a 64-bit counter.
 
in param v
   A pointer to the atomic counter. 
return
   The value of the counter.*/
int64_t  deepeedeekay_rte_atomic64_read(rte_atomic64_t * v);
/**
 Atomically set a 64-bit counter.
 
in param v
   A pointer to the atomic counter. 
in param new_value
   The new value of the counter.*/
void  deepeedeekay_rte_atomic64_set(rte_atomic64_t * v, int64_t new_value);
/**
 Atomically add a 64-bit value to a counter.
 
in param v
   A pointer to the atomic counter. 
in param inc
   The value to be added to the counter.*/
void  deepeedeekay_rte_atomic64_add(rte_atomic64_t * v, int64_t inc);
/**
 Atomically subtract a 64-bit value from a counter.
 
in param v
   A pointer to the atomic counter. 
in param dec
   The value to be subtracted from the counter.*/
void  deepeedeekay_rte_atomic64_sub(rte_atomic64_t * v, int64_t dec);
/**
 Atomically increment a 64-bit counter by one and test.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic64_inc(rte_atomic64_t * v);
/**
 Atomically decrement a 64-bit counter by one and test.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic64_dec(rte_atomic64_t * v);
/**
 Add a 64-bit value to an atomic counter and return the result.
 Atomically adds the 64-bit value (inc) to the atomic counter (v) and returns the value of v after the addition.
 
in param v
   A pointer to the atomic counter. 
in param inc
   The value to be added to the counter. 
return
   The value of v after the addition.*/
int64_t  deepeedeekay_rte_atomic64_add_return(rte_atomic64_t * v, int64_t inc);
/**
 Subtract a 64-bit value from an atomic counter and return the result.
 Atomically subtracts the 64-bit value (dec) from the atomic counter (v) and returns the value of v after the subtraction.
 
in param v
   A pointer to the atomic counter. 
in param dec
   The value to be subtracted from the counter. 
return
   The value of v after the subtraction.*/
int64_t  deepeedeekay_rte_atomic64_sub_return(rte_atomic64_t * v, int64_t dec);
/**
 Atomically increment a 64-bit counter by one and test.
 Atomically increments the atomic counter (v) by one and returns true if the result is 0, or false in all other cases.
 
in param v
   A pointer to the atomic counter. 
return
   True if the result after the addition is 0; false otherwise.*/
int  deepeedeekay_rte_atomic64_inc_and_test(rte_atomic64_t * v);
/**
 Atomically decrement a 64-bit counter by one and test.
 Atomically decrements the atomic counter (v) by one and returns true if the result is 0, or false in all other cases.
 
in param v
   A pointer to the atomic counter. 
return
   True if the result after subtraction is 0; false otherwise.*/
int  deepeedeekay_rte_atomic64_dec_and_test(rte_atomic64_t * v);
/**
 Atomically test and set a 64-bit atomic counter.
 If the counter value is already set, return 0 (failed). Otherwise, set the counter value to 1 and return 1 (success).
 
in param v
   A pointer to the atomic counter. 
return
   0 if failed; else 1, success.*/
int  deepeedeekay_rte_atomic64_test_and_set(rte_atomic64_t * v);
/**
 Atomically set a 64-bit counter to 0.
 
in param v
   A pointer to the atomic counter.*/
void  deepeedeekay_rte_atomic64_clear(rte_atomic64_t * v);
/***/
void  deepeedeekay_rte_smp_mb();
/***/
int  deepeedeekay_rte_atomic128_cmp_exchange(rte_int128_t * dst, rte_int128_t * exp, const rte_int128_t * src, unsigned int weak, int success, int failure);
/**
 Pause CPU execution for a short while
 This call is intended for tight loops which poll a shared resource or wait for an event. A short pause within the loop may reduce the power consumption.*/
void  deepeedeekay_rte_pause();
/**
 Wait for *addr to be updated with a 16-bit expected value, with a relaxed memory ordering model meaning the loads around this API can be reordered.
 
in param addr
  A pointer to the memory location. 
in param expected
  A 16-bit expected value to be in the memory location. 
in param memorder
  Two different memory orders that can be specified:  rte_memory_order_acquire and rte_memory_order_relaxed.*/
void  deepeedeekay_rte_wait_until_equal_16(volatile uint16_t * addr, uint16_t expected, rte_memory_order memorder);
/**
 Wait for *addr to be updated with a 32-bit expected value, with a relaxed memory ordering model meaning the loads around this API can be reordered.
 
in param addr
  A pointer to the memory location. 
in param expected
  A 32-bit expected value to be in the memory location. 
in param memorder
  Two different memory orders that can be specified:  rte_memory_order_acquire and rte_memory_order_relaxed.*/
void  deepeedeekay_rte_wait_until_equal_32(volatile uint32_t * addr, uint32_t expected, rte_memory_order memorder);
/**
 Wait for *addr to be updated with a 64-bit expected value, with a relaxed memory ordering model meaning the loads around this API can be reordered.
 
in param addr
  A pointer to the memory location. 
in param expected
  A 64-bit expected value to be in the memory location. 
in param memorder
  Two different memory orders that can be specified:  rte_memory_order_acquire and rte_memory_order_relaxed.*/
void  deepeedeekay_rte_wait_until_equal_64(volatile uint64_t * addr, uint64_t expected, rte_memory_order memorder);
/**
 Initialize the rwlock to an unlocked state.
 
in param rwl
   A pointer to the rwlock structure.*/
void  deepeedeekay_rte_rwlock_init(rte_rwlock_t * rwl);
/**
 Take a read lock. Loop until the lock is held.
 
note
 The RW lock isn't recursive, so calling this function on the same lock twice without releasing it could potentially result in a deadlock scenario when a write lock is involved.
 
in param rwl
   A pointer to a rwlock structure.*/
void  deepeedeekay_rte_rwlock_read_lock(rte_rwlock_t * rwl);
/**
 Try to take a read lock.
 
in param rwl
   A pointer to a rwlock structure. 
return
   - zero if the lock is successfully taken   - -EBUSY if lock could not be acquired for reading because a     writer holds the lock*/
int  deepeedeekay_rte_rwlock_read_trylock(rte_rwlock_t * rwl);
/**
 Release a read lock.
 
in param rwl
   A pointer to the rwlock structure.*/
void  deepeedeekay_rte_rwlock_read_unlock(rte_rwlock_t * rwl);
/**
 Try to take a write lock.
 
in param rwl
   A pointer to a rwlock structure. 
return
   - zero if the lock is successfully taken   - -EBUSY if lock could not be acquired for writing because     it was already locked for reading or writing*/
int  deepeedeekay_rte_rwlock_write_trylock(rte_rwlock_t * rwl);
/**
 Take a write lock. Loop until the lock is held.
 
in param rwl
   A pointer to a rwlock structure.*/
void  deepeedeekay_rte_rwlock_write_lock(rte_rwlock_t * rwl);
/**
 Release a write lock.
 
in param rwl
   A pointer to a rwlock structure.*/
void  deepeedeekay_rte_rwlock_write_unlock(rte_rwlock_t * rwl);
/**
 Test if the write lock is taken.
 
in param rwl
   A pointer to a rwlock structure. 
return
   1 if the write lock is currently taken; 0 otherwise.*/
int  deepeedeekay_rte_rwlock_write_is_locked(rte_rwlock_t * rwl);
/**
 Try to execute critical section in a hardware memory transaction, if it fails or not available take a read lock
 NOTE: An attempt to perform a HW I/O operation inside a hardware memory transaction always aborts the transaction since the CPU is not able to roll-back should the transaction fail. Therefore, hardware transactional locks are not advised to be used around rte_eth_rx_burst() and rte_eth_tx_burst() calls.
 
in param rwl
   A pointer to a rwlock structure.*/
void  deepeedeekay_rte_rwlock_read_lock_tm(rte_rwlock_t * rwl);
/**
 Commit hardware memory transaction or release the read lock if the lock is used as a fall-back
 
in param rwl
   A pointer to the rwlock structure.*/
void  deepeedeekay_rte_rwlock_read_unlock_tm(rte_rwlock_t * rwl);
/**
 Try to execute critical section in a hardware memory transaction, if it fails or not available take a write lock
 NOTE: An attempt to perform a HW I/O operation inside a hardware memory transaction always aborts the transaction since the CPU is not able to roll-back should the transaction fail. Therefore, hardware transactional locks are not advised to be used around rte_eth_rx_burst() and rte_eth_tx_burst() calls.
 
in param rwl
   A pointer to a rwlock structure.*/
void  deepeedeekay_rte_rwlock_write_lock_tm(rte_rwlock_t * rwl);
/**
 Commit hardware memory transaction or release the write lock if the lock is used as a fall-back
 
in param rwl
   A pointer to a rwlock structure.*/
void  deepeedeekay_rte_rwlock_write_unlock_tm(rte_rwlock_t * rwl);
/**
 Return the Application thread ID of the execution unit.
 Note: in most cases the lcore id returned here will also correspond   to the processor id of the CPU on which the thread is pinned, this   will not be the case if the user has explicitly changed the thread to   core affinities using --lcores EAL argument e.g. --lcores '(0-3)@10'   to run threads with lcore IDs 0, 1, 2 and 3 on physical core 10..
 
return
  Logical core ID (in EAL thread or registered non-EAL thread) or  LCORE_ID_ANY (in unregistered non-EAL thread)*/
unsigned int  deepeedeekay_rte_lcore_id();
/**
 Initialize the spinlock to an unlocked state.
 
in param sl
   A pointer to the spinlock.*/
void  deepeedeekay_rte_spinlock_init(rte_spinlock_t * sl);
/**
 Take the spinlock.
 
in param sl
   A pointer to the spinlock.*/
void  deepeedeekay_rte_spinlock_lock(rte_spinlock_t * sl);
/**
 Release the spinlock.
 
in param sl
   A pointer to the spinlock.*/
void  deepeedeekay_rte_spinlock_unlock(rte_spinlock_t * sl);
/**
 Try to take the lock.
 
in param sl
   A pointer to the spinlock. 
return
   1 if the lock is successfully taken; 0 otherwise.*/
int  deepeedeekay_rte_spinlock_trylock(rte_spinlock_t * sl);
/**
 Test if the lock is taken.
 
in param sl
   A pointer to the spinlock. 
return
   1 if the lock is currently taken; 0 otherwise.*/
int  deepeedeekay_rte_spinlock_is_locked(rte_spinlock_t * sl);
/**
 Test if hardware transactional memory (lock elision) is supported
 
return
   1 if the hardware transactional memory is supported; 0 otherwise.*/
int  deepeedeekay_rte_tm_supported();
/**
 Try to execute critical section in a hardware memory transaction, if it fails or not available take the spinlock.
 NOTE: An attempt to perform a HW I/O operation inside a hardware memory transaction always aborts the transaction since the CPU is not able to roll-back should the transaction fail. Therefore, hardware transactional locks are not advised to be used around rte_eth_rx_burst() and rte_eth_tx_burst() calls.
 
in param sl
   A pointer to the spinlock.*/
void  deepeedeekay_rte_spinlock_lock_tm(rte_spinlock_t * sl);
/**
 Commit hardware memory transaction or release the spinlock if the spinlock is used as a fall-back
 
in param sl
   A pointer to the spinlock.*/
void  deepeedeekay_rte_spinlock_unlock_tm(rte_spinlock_t * sl);
/**
 Try to execute critical section in a hardware memory transaction, if it fails or not available try to take the lock.
 NOTE: An attempt to perform a HW I/O operation inside a hardware memory transaction always aborts the transaction since the CPU is not able to roll-back should the transaction fail. Therefore, hardware transactional locks are not advised to be used around rte_eth_rx_burst() and rte_eth_tx_burst() calls.
 
in param sl
   A pointer to the spinlock. 
return
   1 if the hardware memory transaction is successfully started   or lock is successfully taken; 0 otherwise.*/
int  deepeedeekay_rte_spinlock_trylock_tm(rte_spinlock_t * sl);
/**
 Initialize the recursive spinlock to an unlocked state.
 
in param slr
   A pointer to the recursive spinlock.*/
void  deepeedeekay_rte_spinlock_recursive_init(rte_spinlock_recursive_t * slr);
/**
 Take the recursive spinlock.
 
in param slr
   A pointer to the recursive spinlock.*/
void  deepeedeekay_rte_spinlock_recursive_lock(rte_spinlock_recursive_t * slr);
/**
 Release the recursive spinlock.
 
in param slr
   A pointer to the recursive spinlock.*/
void  deepeedeekay_rte_spinlock_recursive_unlock(rte_spinlock_recursive_t * slr);
/**
 Try to take the recursive lock.
 
in param slr
   A pointer to the recursive spinlock. 
return
   1 if the lock is successfully taken; 0 otherwise.*/
int  deepeedeekay_rte_spinlock_recursive_trylock(rte_spinlock_recursive_t * slr);
/**
 Try to execute critical section in a hardware memory transaction, if it fails or not available take the recursive spinlocks
 NOTE: An attempt to perform a HW I/O operation inside a hardware memory transaction always aborts the transaction since the CPU is not able to roll-back should the transaction fail. Therefore, hardware transactional locks are not advised to be used around rte_eth_rx_burst() and rte_eth_tx_burst() calls.
 
in param slr
   A pointer to the recursive spinlock.*/
void  deepeedeekay_rte_spinlock_recursive_lock_tm(rte_spinlock_recursive_t * slr);
/**
 Commit hardware memory transaction or release the recursive spinlock if the recursive spinlock is used as a fall-back
 
in param slr
   A pointer to the recursive spinlock.*/
void  deepeedeekay_rte_spinlock_recursive_unlock_tm(rte_spinlock_recursive_t * slr);
/**
 Try to execute critical section in a hardware memory transaction, if it fails or not available try to take the recursive lock
 NOTE: An attempt to perform a HW I/O operation inside a hardware memory transaction always aborts the transaction since the CPU is not able to roll-back should the transaction fail. Therefore, hardware transactional locks are not advised to be used around rte_eth_rx_burst() and rte_eth_tx_burst() calls.
 
in param slr
   A pointer to the recursive spinlock. 
return
   1 if the hardware memory transaction is successfully started   or lock is successfully taken; 0 otherwise.*/
int  deepeedeekay_rte_spinlock_recursive_trylock_tm(rte_spinlock_recursive_t * slr);
/***/
unsigned int  deepeedeekay_rte_xbegin();
/***/
void  deepeedeekay_rte_xend();
/***/
int  deepeedeekay_rte_xtest();
/**
 Return the number of TSC cycles since boot
 
return
   the number of cycles*/
uint64_t  deepeedeekay_rte_get_tsc_cycles();
/**
 Get the number of cycles since boot from the default timer.
 
return
   The number of cycles*/
uint64_t  deepeedeekay_rte_get_timer_cycles();
/**
 Get the number of cycles in one second for the default timer.
 
return
   The number of cycles in one second.*/
uint64_t  deepeedeekay_rte_get_timer_hz();
/**
 Wait at least ms milliseconds.
 
in param ms
   The number of milliseconds to wait.*/
void  deepeedeekay_rte_delay_ms(unsigned int ms);
/***/
uint64_t  deepeedeekay_rte_rdtsc();
/***/
uint64_t  deepeedeekay_rte_rdtsc_precise();
/***/
int  deepeedeekay_rte_try_tm(volatile int * lock);
/**
 Enqueue several objects on the ring (multi-producers safe).
 This function uses a "compare and set" instruction to move the producer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mp_enqueue_bulk_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space);
/**
 Enqueue several objects on a ring
 
warning
 This API is NOT multi-producers safe
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_sp_enqueue_bulk_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space);
/**
 Enqueue several objects on the HTS ring (multi-producers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mp_hts_enqueue_bulk_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space);
/**
 Dequeue several objects from an HTS ring (multi-consumers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects dequeued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mc_hts_dequeue_bulk_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Enqueue several objects on the HTS ring (multi-producers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   - n: Actual number of objects enqueued.*/
unsigned int  deepeedeekay_rte_ring_mp_hts_enqueue_burst_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space);
/**
 Dequeue several objects from an HTS  ring (multi-consumers safe). When the requested objects are more than the available objects, only dequeue the actual number of objects.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   - n: Actual number of objects dequeued, 0 if ring is empty*/
unsigned int  deepeedeekay_rte_ring_mc_hts_dequeue_burst_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Enqueue several objects on the HTS ring (multi-producers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mp_hts_enqueue_bulk(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space);
/**
 Dequeue several objects from an HTS ring (multi-consumers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects dequeued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mc_hts_dequeue_bulk(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 Enqueue several objects on the HTS ring (multi-producers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   - n: Actual number of objects enqueued.*/
unsigned int  deepeedeekay_rte_ring_mp_hts_enqueue_burst(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space);
/**
 Dequeue several objects from an HTS  ring (multi-consumers safe). When the requested objects are more than the available objects, only dequeue the actual number of objects.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   - n: Actual number of objects dequeued, 0 if ring is empty*/
unsigned int  deepeedeekay_rte_ring_mc_hts_dequeue_burst(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 Enqueue several objects on the RTS ring (multi-producers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mp_rts_enqueue_bulk_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space);
/**
 Dequeue several objects from an RTS ring (multi-consumers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects dequeued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mc_rts_dequeue_bulk_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Enqueue several objects on the RTS ring (multi-producers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   - n: Actual number of objects enqueued.*/
unsigned int  deepeedeekay_rte_ring_mp_rts_enqueue_burst_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space);
/**
 Dequeue several objects from an RTS  ring (multi-consumers safe). When the requested objects are more than the available objects, only dequeue the actual number of objects.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   - n: Actual number of objects dequeued, 0 if ring is empty*/
unsigned int  deepeedeekay_rte_ring_mc_rts_dequeue_burst_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Enqueue several objects on the RTS ring (multi-producers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mp_rts_enqueue_bulk(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space);
/**
 Dequeue several objects from an RTS ring (multi-consumers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects dequeued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mc_rts_dequeue_bulk(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 Enqueue several objects on the RTS ring (multi-producers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   - n: Actual number of objects enqueued.*/
unsigned int  deepeedeekay_rte_ring_mp_rts_enqueue_burst(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space);
/**
 Dequeue several objects from an RTS  ring (multi-consumers safe). When the requested objects are more than the available objects, only dequeue the actual number of objects.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   - n: Actual number of objects dequeued, 0 if ring is empty*/
unsigned int  deepeedeekay_rte_ring_mc_rts_dequeue_burst(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 Return producer max Head-Tail-Distance (HTD).
 
in param r
   A pointer to the ring structure. 
return
   Producer HTD value, if producer is set in appropriate sync mode,   or UINT32_MAX otherwise.*/
uint32_t  deepeedeekay_rte_ring_get_prod_htd_max(const struct rte_ring * r);
/**
 Set producer max Head-Tail-Distance (HTD). Note that producer has to use appropriate sync mode (RTS).
 
in param r
   A pointer to the ring structure. 
in param v
   new HTD value to setup. 
return
   Zero on success, or negative error code otherwise.*/
int  deepeedeekay_rte_ring_set_prod_htd_max(struct rte_ring * r, uint32_t v);
/**
 Return consumer max Head-Tail-Distance (HTD).
 
in param r
   A pointer to the ring structure. 
return
   Consumer HTD value, if consumer is set in appropriate sync mode,   or UINT32_MAX otherwise.*/
uint32_t  deepeedeekay_rte_ring_get_cons_htd_max(const struct rte_ring * r);
/**
 Set consumer max Head-Tail-Distance (HTD). Note that consumer has to use appropriate sync mode (RTS).
 
in param r
   A pointer to the ring structure. 
in param v
   new HTD value to setup. 
return
   Zero on success, or negative error code otherwise.*/
int  deepeedeekay_rte_ring_set_cons_htd_max(struct rte_ring * r, uint32_t v);
/**
 Enqueue several objects on a ring.
 This function calls the multi-producer or the single-producer version depending on the default behavior that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_enqueue_bulk_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space);
/**
 Enqueue one object on a ring (multi-producers safe).
 This function uses a "compare and set" instruction to move the producer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj
   A pointer to the object to be added. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
return
   - 0: Success; objects enqueued.   - -ENOBUFS: Not enough room in the ring to enqueue; no object is enqueued.*/
int  deepeedeekay_rte_ring_mp_enqueue_elem(struct rte_ring * r, void * obj, unsigned int esize);
/**
 Enqueue one object on a ring
 
warning
 This API is NOT multi-producers safe
 
in param r
   A pointer to the ring structure. 
in param obj
   A pointer to the object to be added. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
return
   - 0: Success; objects enqueued.   - -ENOBUFS: Not enough room in the ring to enqueue; no object is enqueued.*/
int  deepeedeekay_rte_ring_sp_enqueue_elem(struct rte_ring * r, void * obj, unsigned int esize);
/**
 Enqueue one object on a ring.
 This function calls the multi-producer or the single-producer version, depending on the default behaviour that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj
   A pointer to the object to be added. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
return
   - 0: Success; objects enqueued.   - -ENOBUFS: Not enough room in the ring to enqueue; no object is enqueued.*/
int  deepeedeekay_rte_ring_enqueue_elem(struct rte_ring * r, void * obj, unsigned int esize);
/**
 Dequeue several objects from a ring (multi-consumers safe).
 This function uses a "compare and set" instruction to move the consumer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects dequeued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mc_dequeue_bulk_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Dequeue several objects from a ring (NOT multi-consumers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table,   must be strictly positive. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects dequeued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_sc_dequeue_bulk_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Dequeue several objects from a ring.
 This function calls the multi-consumers or the single-consumer version, depending on the default behaviour that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects dequeued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_dequeue_bulk_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Dequeue one object from a ring (multi-consumers safe).
 This function uses a "compare and set" instruction to move the consumer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj_p
   A pointer to the object that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
return
   - 0: Success; objects dequeued.   - -ENOENT: Not enough entries in the ring to dequeue; no object is     dequeued.*/
int  deepeedeekay_rte_ring_mc_dequeue_elem(struct rte_ring * r, void * obj_p, unsigned int esize);
/**
 Dequeue one object from a ring (NOT multi-consumers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_p
   A pointer to the object that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
return
   - 0: Success; objects dequeued.   - -ENOENT: Not enough entries in the ring to dequeue, no object is     dequeued.*/
int  deepeedeekay_rte_ring_sc_dequeue_elem(struct rte_ring * r, void * obj_p, unsigned int esize);
/**
 Dequeue one object from a ring.
 This function calls the multi-consumers or the single-consumer version depending on the default behaviour that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj_p
   A pointer to the object that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
return
   - 0: Success, objects dequeued.   - -ENOENT: Not enough entries in the ring to dequeue, no object is     dequeued.*/
int  deepeedeekay_rte_ring_dequeue_elem(struct rte_ring * r, void * obj_p, unsigned int esize);
/**
 Enqueue several objects on the ring (multi-producers safe).
 This function uses a "compare and set" instruction to move the producer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   - n: Actual number of objects enqueued.*/
unsigned int  deepeedeekay_rte_ring_mp_enqueue_burst_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space);
/**
 Enqueue several objects on a ring
 
warning
 This API is NOT multi-producers safe
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   - n: Actual number of objects enqueued.*/
unsigned int  deepeedeekay_rte_ring_sp_enqueue_burst_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space);
/**
 Enqueue several objects on a ring.
 This function calls the multi-producer or the single-producer version depending on the default behavior that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   - n: Actual number of objects enqueued.*/
unsigned int  deepeedeekay_rte_ring_enqueue_burst_elem(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n, unsigned int * free_space);
/**
 Dequeue several objects from a ring (multi-consumers safe). When the request objects are more than the available objects, only dequeue the actual number of objects
 This function uses a "compare and set" instruction to move the consumer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   - n: Actual number of objects dequeued, 0 if ring is empty*/
unsigned int  deepeedeekay_rte_ring_mc_dequeue_burst_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Dequeue several objects from a ring (NOT multi-consumers safe).When the request objects are more than the available objects, only dequeue the actual number of objects
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   - n: Actual number of objects dequeued, 0 if ring is empty*/
unsigned int  deepeedeekay_rte_ring_sc_dequeue_burst_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Dequeue multiple objects from a ring up to a maximum number.
 This function calls the multi-consumers or the single-consumer version, depending on the default behaviour that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   - Number of objects dequeued*/
unsigned int  deepeedeekay_rte_ring_dequeue_burst_elem(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Start to enqueue several objects on the ring. Note that no actual objects are put in the queue by this function, it just reserves for user such ability. User has to call appropriate enqueue_elem_finish() to copy objects into the queue and complete given enqueue operation.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects that can be enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_enqueue_bulk_elem_start(struct rte_ring * r, unsigned int n, unsigned int * free_space);
/**
 Start to enqueue several objects on the ring. Note that no actual objects are put in the queue by this function, it just reserves for user such ability. User has to call appropriate enqueue_finish() to copy objects into the queue and complete given enqueue operation.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects that can be enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_enqueue_bulk_start(struct rte_ring * r, unsigned int n, unsigned int * free_space);
/**
 Start to enqueue several objects on the ring. Note that no actual objects are put in the queue by this function, it just reserves for user such ability. User has to call appropriate enqueue_elem_finish() to copy objects into the queue and complete given enqueue operation.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   Actual number of objects that can be enqueued.*/
unsigned int  deepeedeekay_rte_ring_enqueue_burst_elem_start(struct rte_ring * r, unsigned int n, unsigned int * free_space);
/**
 Start to enqueue several objects on the ring. Note that no actual objects are put in the queue by this function, it just reserves for user such ability. User has to call appropriate enqueue_finish() to copy objects into the queue and complete given enqueue operation.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   Actual number of objects that can be enqueued.*/
unsigned int  deepeedeekay_rte_ring_enqueue_burst_start(struct rte_ring * r, unsigned int n, unsigned int * free_space);
/**
 Complete to enqueue several objects on the ring. Note that number of objects to enqueue should not exceed previous enqueue_start return value.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to add to the ring from the obj_table.*/
void  deepeedeekay_rte_ring_enqueue_elem_finish(struct rte_ring * r, const void * obj_table, unsigned int esize, unsigned int n);
/**
 Complete to enqueue several objects on the ring. Note that number of objects to enqueue should not exceed previous enqueue_start return value.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects. 
in param n
   The number of objects to add to the ring from the obj_table.*/
void  deepeedeekay_rte_ring_enqueue_finish(struct rte_ring * r, void *const * obj_table, unsigned int n);
/**
 Start to dequeue several objects from the ring. Note that user has to call appropriate dequeue_finish() to complete given dequeue operation and actually remove objects the ring.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects dequeued, either 0 or n.*/
unsigned int  deepeedeekay_rte_ring_dequeue_bulk_elem_start(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Start to dequeue several objects from the ring. Note that user has to call appropriate dequeue_finish() to complete given dequeue operation and actually remove objects the ring.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   Actual number of objects dequeued.*/
unsigned int  deepeedeekay_rte_ring_dequeue_bulk_start(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 Start to dequeue several objects from the ring. Note that user has to call appropriate dequeue_finish() to complete given dequeue operation and actually remove objects the ring.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of objects that will be filled. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The actual number of objects dequeued.*/
unsigned int  deepeedeekay_rte_ring_dequeue_burst_elem_start(struct rte_ring * r, void * obj_table, unsigned int esize, unsigned int n, unsigned int * available);
/**
 Start to dequeue several objects from the ring. Note that user has to call appropriate dequeue_finish() to complete given dequeue operation and actually remove objects the ring.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The actual number of objects dequeued.*/
unsigned int  deepeedeekay_rte_ring_dequeue_burst_start(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 Complete to dequeue several objects from the ring. Note that number of objects to dequeue should not exceed previous dequeue_start return value.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to remove from the ring.*/
void  deepeedeekay_rte_ring_dequeue_elem_finish(struct rte_ring * r, unsigned int n);
/**
 Complete to dequeue several objects from the ring. Note that number of objects to dequeue should not exceed previous dequeue_start return value.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to remove from the ring.*/
void  deepeedeekay_rte_ring_dequeue_finish(struct rte_ring * r, unsigned int n);
/**
 Start to enqueue several objects on the ring. Note that no actual objects are put in the queue by this function, it just reserves space for the user on the ring. User has to copy objects into the queue using the returned pointers. User should call rte_ring_enqueue_zc_elem_finish to complete the enqueue operation.
 
in param r
   A pointer to the ring structure. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4. 
in param n
   The number of objects to add in the ring. 
in param zcd
   Structure containing the pointers and length of the space   reserved on the ring storage. 
in param free_space
   If non-NULL, returns the amount of space in the ring after the   reservation operation has finished. 
return
   The number of objects that can be enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_enqueue_zc_bulk_elem_start(struct rte_ring * r, unsigned int esize, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * free_space);
/**
 Start to enqueue several pointers to objects on the ring. Note that no actual pointers are put in the queue by this function, it just reserves space for the user on the ring. User has to copy pointers to objects into the queue using the returned pointers. User should call rte_ring_enqueue_zc_finish to complete the enqueue operation.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to add in the ring. 
in param zcd
   Structure containing the pointers and length of the space   reserved on the ring storage. 
in param free_space
   If non-NULL, returns the amount of space in the ring after the   reservation operation has finished. 
return
   The number of objects that can be enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_enqueue_zc_bulk_start(struct rte_ring * r, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * free_space);
/**
 Start to enqueue several objects on the ring. Note that no actual objects are put in the queue by this function, it just reserves space for the user on the ring. User has to copy objects into the queue using the returned pointers. User should call rte_ring_enqueue_zc_elem_finish to complete the enqueue operation.
 
in param r
   A pointer to the ring structure. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4. 
in param n
   The number of objects to add in the ring. 
in param zcd
   Structure containing the pointers and length of the space   reserved on the ring storage. 
in param free_space
   If non-NULL, returns the amount of space in the ring after the   reservation operation has finished. 
return
   The number of objects that can be enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_enqueue_zc_burst_elem_start(struct rte_ring * r, unsigned int esize, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * free_space);
/**
 Start to enqueue several pointers to objects on the ring. Note that no actual pointers are put in the queue by this function, it just reserves space for the user on the ring. User has to copy pointers to objects into the queue using the returned pointers. User should call rte_ring_enqueue_zc_finish to complete the enqueue operation.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to add in the ring. 
in param zcd
   Structure containing the pointers and length of the space   reserved on the ring storage. 
in param free_space
   If non-NULL, returns the amount of space in the ring after the   reservation operation has finished. 
return
   The number of objects that can be enqueued, either 0 or n.*/
unsigned int  deepeedeekay_rte_ring_enqueue_zc_burst_start(struct rte_ring * r, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * free_space);
/**
 Complete enqueuing several objects on the ring. Note that number of objects to enqueue should not exceed previous enqueue_start return value.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to add to the ring.*/
void  deepeedeekay_rte_ring_enqueue_zc_elem_finish(struct rte_ring * r, unsigned int n);
/**
 Complete enqueuing several pointers to objects on the ring. Note that number of objects to enqueue should not exceed previous enqueue_start return value.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of pointers to objects to add to the ring.*/
void  deepeedeekay_rte_ring_enqueue_zc_finish(struct rte_ring * r, unsigned int n);
/**
 Start to dequeue several objects from the ring. Note that no actual objects are copied from the queue by this function. User has to copy objects from the queue using the returned pointers. User should call rte_ring_dequeue_zc_elem_finish to complete the dequeue operation.
 
in param r
   A pointer to the ring structure. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4. 
in param n
   The number of objects to remove from the ring. 
in param zcd
   Structure containing the pointers and length of the space   reserved on the ring storage. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects that can be dequeued, either 0 or n.*/
unsigned int  deepeedeekay_rte_ring_dequeue_zc_bulk_elem_start(struct rte_ring * r, unsigned int esize, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * available);
/**
 Start to dequeue several pointers to objects from the ring. Note that no actual pointers are removed from the queue by this function. User has to copy pointers to objects from the queue using the returned pointers. User should call rte_ring_dequeue_zc_finish to complete the dequeue operation.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to remove from the ring. 
in param zcd
   Structure containing the pointers and length of the space   reserved on the ring storage. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects that can be dequeued, either 0 or n.*/
unsigned int  deepeedeekay_rte_ring_dequeue_zc_bulk_start(struct rte_ring * r, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * available);
/**
 Start to dequeue several objects from the ring. Note that no actual objects are copied from the queue by this function. User has to copy objects from the queue using the returned pointers. User should call rte_ring_dequeue_zc_elem_finish to complete the dequeue operation.
 
in param r
   A pointer to the ring structure. 
in param esize
   The size of ring element, in bytes. It must be a multiple of 4.   This must be the same value used while creating the ring. Otherwise   the results are undefined. 
in param n
   The number of objects to dequeue from the ring. 
in param zcd
   Structure containing the pointers and length of the space   reserved on the ring storage. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects that can be dequeued, either 0 or n.*/
unsigned int  deepeedeekay_rte_ring_dequeue_zc_burst_elem_start(struct rte_ring * r, unsigned int esize, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * available);
/**
 Start to dequeue several pointers to objects from the ring. Note that no actual pointers are removed from the queue by this function. User has to copy pointers to objects from the queue using the returned pointers. User should call rte_ring_dequeue_zc_finish to complete the dequeue operation.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to remove from the ring. 
in param zcd
   Structure containing the pointers and length of the space   reserved on the ring storage. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects that can be dequeued, either 0 or n.*/
unsigned int  deepeedeekay_rte_ring_dequeue_zc_burst_start(struct rte_ring * r, unsigned int n, struct rte_ring_zc_data * zcd, unsigned int * available);
/**
 Complete dequeuing several objects from the ring. Note that number of objects to dequeued should not exceed previous dequeue_start return value.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to remove from the ring.*/
void  deepeedeekay_rte_ring_dequeue_zc_elem_finish(struct rte_ring * r, unsigned int n);
/**
 Complete dequeuing several objects from the ring. Note that number of objects to dequeued should not exceed previous dequeue_start return value.
 
in param r
   A pointer to the ring structure. 
in param n
   The number of objects to remove from the ring.*/
void  deepeedeekay_rte_ring_dequeue_zc_finish(struct rte_ring * r, unsigned int n);
/**
 Enqueue several objects on the ring (multi-producers safe).
 This function uses a "compare and set" instruction to move the producer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mp_enqueue_bulk(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space);
/**
 Enqueue several objects on a ring (NOT multi-producers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_sp_enqueue_bulk(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space);
/**
 Enqueue several objects on a ring.
 This function calls the multi-producer or the single-producer version depending on the default behavior that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   The number of objects enqueued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_enqueue_bulk(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space);
/**
 Enqueue one object on a ring (multi-producers safe).
 This function uses a "compare and set" instruction to move the producer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj
   A pointer to the object to be added. 
return
   - 0: Success; objects enqueued.   - -ENOBUFS: Not enough room in the ring to enqueue; no object is enqueued.*/
int  deepeedeekay_rte_ring_mp_enqueue(struct rte_ring * r, void * obj);
/**
 Enqueue one object on a ring (NOT multi-producers safe).
 
in param r
   A pointer to the ring structure. 
in param obj
   A pointer to the object to be added. 
return
   - 0: Success; objects enqueued.   - -ENOBUFS: Not enough room in the ring to enqueue; no object is enqueued.*/
int  deepeedeekay_rte_ring_sp_enqueue(struct rte_ring * r, void * obj);
/**
 Enqueue one object on a ring.
 This function calls the multi-producer or the single-producer version, depending on the default behaviour that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj
   A pointer to the object to be added. 
return
   - 0: Success; objects enqueued.   - -ENOBUFS: Not enough room in the ring to enqueue; no object is enqueued.*/
int  deepeedeekay_rte_ring_enqueue(struct rte_ring * r, void * obj);
/**
 Dequeue several objects from a ring (multi-consumers safe).
 This function uses a "compare and set" instruction to move the consumer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects dequeued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_mc_dequeue_bulk(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 Dequeue several objects from a ring (NOT multi-consumers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table,   must be strictly positive. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects dequeued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_sc_dequeue_bulk(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 Dequeue several objects from a ring.
 This function calls the multi-consumers or the single-consumer version, depending on the default behaviour that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   The number of objects dequeued, either 0 or n*/
unsigned int  deepeedeekay_rte_ring_dequeue_bulk(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 Dequeue one object from a ring (multi-consumers safe).
 This function uses a "compare and set" instruction to move the consumer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj_p
   A pointer to a void * pointer (object) that will be filled. 
return
   - 0: Success; objects dequeued.   - -ENOENT: Not enough entries in the ring to dequeue; no object is     dequeued.*/
int  deepeedeekay_rte_ring_mc_dequeue(struct rte_ring * r, void ** obj_p);
/**
 Dequeue one object from a ring (NOT multi-consumers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_p
   A pointer to a void * pointer (object) that will be filled. 
return
   - 0: Success; objects dequeued.   - -ENOENT: Not enough entries in the ring to dequeue, no object is     dequeued.*/
int  deepeedeekay_rte_ring_sc_dequeue(struct rte_ring * r, void ** obj_p);
/**
 Dequeue one object from a ring.
 This function calls the multi-consumers or the single-consumer version depending on the default behaviour that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj_p
   A pointer to a void * pointer (object) that will be filled. 
return
   - 0: Success, objects dequeued.   - -ENOENT: Not enough entries in the ring to dequeue, no object is     dequeued.*/
int  deepeedeekay_rte_ring_dequeue(struct rte_ring * r, void ** obj_p);
/**
 Return the number of entries in a ring.
 
in param r
   A pointer to the ring structure. 
return
   The number of entries in the ring.*/
unsigned int  deepeedeekay_rte_ring_count(const struct rte_ring * r);
/**
 Return the number of free entries in a ring.
 
in param r
   A pointer to the ring structure. 
return
   The number of free entries in the ring.*/
unsigned int  deepeedeekay_rte_ring_free_count(const struct rte_ring * r);
/**
 Test if a ring is full.
 
in param r
   A pointer to the ring structure. 
return
   - 1: The ring is full.   - 0: The ring is not full.*/
int  deepeedeekay_rte_ring_full(const struct rte_ring * r);
/**
 Test if a ring is empty.
 
in param r
   A pointer to the ring structure. 
return
   - 1: The ring is empty.   - 0: The ring is not empty.*/
int  deepeedeekay_rte_ring_empty(const struct rte_ring * r);
/**
 Return the size of the ring.
 
in param r
   A pointer to the ring structure. 
return
   The size of the data store used by the ring.   NOTE: this is not the same as the usable space in the ring. To query that   use ``rte_ring_get_capacity()``.*/
unsigned int  deepeedeekay_rte_ring_get_size(const struct rte_ring * r);
/**
 Return the number of elements which can be stored in the ring.
 
in param r
   A pointer to the ring structure. 
return
   The usable size of the ring.*/
unsigned int  deepeedeekay_rte_ring_get_capacity(const struct rte_ring * r);
/**
 Return sync type used by producer in the ring.
 
in param r
   A pointer to the ring structure. 
return
   Producer sync type value.*/
enum rte_ring_sync_type  deepeedeekay_rte_ring_get_prod_sync_type(const struct rte_ring * r);
/**
 Check is the ring for single producer.
 
in param r
   A pointer to the ring structure. 
return
   true if ring is SP, zero otherwise.*/
int  deepeedeekay_rte_ring_is_prod_single(const struct rte_ring * r);
/**
 Return sync type used by consumer in the ring.
 
in param r
   A pointer to the ring structure. 
return
   Consumer sync type value.*/
enum rte_ring_sync_type  deepeedeekay_rte_ring_get_cons_sync_type(const struct rte_ring * r);
/**
 Check is the ring for single consumer.
 
in param r
   A pointer to the ring structure. 
return
   true if ring is SC, zero otherwise.*/
int  deepeedeekay_rte_ring_is_cons_single(const struct rte_ring * r);
/**
 Enqueue several objects on the ring (multi-producers safe).
 This function uses a "compare and set" instruction to move the producer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   - n: Actual number of objects enqueued.*/
unsigned int  deepeedeekay_rte_ring_mp_enqueue_burst(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space);
/**
 Enqueue several objects on a ring (NOT multi-producers safe).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   - n: Actual number of objects enqueued.*/
unsigned int  deepeedeekay_rte_ring_sp_enqueue_burst(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space);
/**
 Enqueue several objects on a ring.
 This function calls the multi-producer or the single-producer version depending on the default behavior that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the ring from the obj_table. 
in param free_space
   if non-NULL, returns the amount of space in the ring after the   enqueue operation has finished. 
return
   - n: Actual number of objects enqueued.*/
unsigned int  deepeedeekay_rte_ring_enqueue_burst(struct rte_ring * r, void *const * obj_table, unsigned int n, unsigned int * free_space);
/**
 Dequeue several objects from a ring (multi-consumers safe). When the request objects are more than the available objects, only dequeue the actual number of objects
 This function uses a "compare and set" instruction to move the consumer index atomically.
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   - n: Actual number of objects dequeued, 0 if ring is empty*/
unsigned int  deepeedeekay_rte_ring_mc_dequeue_burst(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 Dequeue several objects from a ring (NOT multi-consumers safe).When the request objects are more than the available objects, only dequeue the actual number of objects
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   - n: Actual number of objects dequeued, 0 if ring is empty*/
unsigned int  deepeedeekay_rte_ring_sc_dequeue_burst(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 Dequeue multiple objects from a ring up to a maximum number.
 This function calls the multi-consumers or the single-consumer version, depending on the default behaviour that was specified at ring creation time (see flags).
 
in param r
   A pointer to the ring structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to dequeue from the ring to the obj_table. 
in param available
   If non-NULL, returns the number of remaining ring entries after the   dequeue has finished. 
return
   - Number of objects dequeued*/
unsigned int  deepeedeekay_rte_ring_dequeue_burst(struct rte_ring * r, void ** obj_table, unsigned int n, unsigned int * available);
/**
 */
size_t  deepeedeekay_rte_strlcpy(char * dst, const char * src, size_t size);
/**
 */
size_t  deepeedeekay_rte_strlcat(char * dst, const char * src, size_t size);
/**
 
warning
  this API may change without prior notice.
 Search for the first non whitespace character.
 
in param src
   The input string to be analysed.
 
return
  The address of the first non whitespace character.*/
const char * deepeedeekay_rte_str_skip_leading_spaces(const char * src);
/**
 
warning
  this API may change, or be removed, without prior notice
 Test if trace feature is enabled at compile time.
 
return
   true if trace feature is enabled, false otherwise.*/
bool  deepeedeekay_rte_trace_feature_is_enabled();
/***/
void  deepeedeekay_rte_ethdev_trace_rx_burst_empty(uint16_t port_id, uint16_t queue_id, void ** pkt_tbl);
/***/
void  deepeedeekay_rte_ethdev_trace_rx_burst_nonempty(uint16_t port_id, uint16_t queue_id, void ** pkt_tbl, uint16_t nb_rx);
/***/
void  deepeedeekay_rte_ethdev_trace_tx_burst(uint16_t port_id, uint16_t queue_id, void ** pkts_tbl, uint16_t nb_pkts);
/***/
void  deepeedeekay_rte_eth_trace_call_rx_callbacks_empty(uint16_t port_id, uint16_t queue_id, void ** rx_pkts, uint16_t nb_pkts);
/***/
void  deepeedeekay_rte_eth_trace_call_rx_callbacks_nonempty(uint16_t port_id, uint16_t queue_id, void ** rx_pkts, uint16_t nb_rx, uint16_t nb_pkts);
/***/
void  deepeedeekay_rte_eth_trace_call_tx_callbacks(uint16_t port_id, uint16_t queue_id, void ** tx_pkts, uint16_t nb_pkts);
/***/
void  deepeedeekay_rte_eth_trace_tx_buffer_drop_callback(void ** pkts, uint16_t unsent);
/***/
void  deepeedeekay_rte_eth_trace_tx_buffer_count_callback(void ** pkts, uint16_t unsent, uint64_t count);
/***/
void  deepeedeekay_rte_eth_trace_tx_queue_count(uint16_t port_id, uint16_t queue_id, int rc);
/**
 For input set change of hash filter, if SRC_ONLY and DST_ONLY of the same level are used simultaneously, it is the same case as none of them are added.
 
in param rss_hf
   RSS types with SRC/DST_ONLY. 
return
   RSS types.*/
uint64_t  deepeedeekay_rte_eth_rss_hf_refine(uint64_t rss_hf);
/**
 Copy bytes from one location to another. The locations must not overlap.
 
note
 This is implemented as a macro, so it's address should not be taken and care is needed as parameter expressions may be evaluated multiple times.
 
in param dst
   Pointer to the destination of the data. 
in param src
   Pointer to the source data. 
in param n
   Number of bytes to copy. 
return
   Pointer to the destination data.*/
void * deepeedeekay_rte_memcpy(void * dst, const void * src, size_t n);
/**
 Use the following structs to avoid violating C standard alignment requirements and to avoid strict aliasing bugs
 Copy bytes from one location to another, locations should not overlap. Use with n <= 15.*/
void * deepeedeekay_rte_mov15_or_less(void * dst, const void * src, size_t n);
/**
 Copy 16 bytes from one location to another, locations should not overlap.*/
void  deepeedeekay_rte_mov16(uint8_t * dst, const uint8_t * src);
/**
 Copy 32 bytes from one location to another, locations should not overlap.*/
void  deepeedeekay_rte_mov32(uint8_t * dst, const uint8_t * src);
/**
 Copy 64 bytes from one location to another, locations should not overlap.*/
void  deepeedeekay_rte_mov64(uint8_t * dst, const uint8_t * src);
/**
 Copy 128 bytes from one location to another, locations should not overlap.*/
void  deepeedeekay_rte_mov128(uint8_t * dst, const uint8_t * src);
/**
 Copy 256 bytes from one location to another, locations should not overlap.*/
void  deepeedeekay_rte_mov256(uint8_t * dst, const uint8_t * src);
/***/
void * deepeedeekay_rte_memcpy_generic(void * dst, const void * src, size_t n);
/***/
void * deepeedeekay_rte_memcpy_aligned(void * dst, const void * src, size_t n);
/***/
void  deepeedeekay_rte_mempool_trace_ops_dequeue_bulk(void * mempool, void ** obj_table, uint32_t nb_objs);
/***/
void  deepeedeekay_rte_mempool_trace_ops_dequeue_contig_blocks(void * mempool, void ** first_obj_table, uint32_t nb_objs);
/***/
void  deepeedeekay_rte_mempool_trace_ops_enqueue_bulk(void * mempool, void *const * obj_table, uint32_t nb_objs);
/***/
void  deepeedeekay_rte_mempool_trace_generic_put(void * mempool, void *const * obj_table, uint32_t nb_objs, void * cache);
/***/
void  deepeedeekay_rte_mempool_trace_put_bulk(void * mempool, void *const * obj_table, uint32_t nb_objs, void * cache);
/***/
void  deepeedeekay_rte_mempool_trace_generic_get(void * mempool, void *const * obj_table, uint32_t nb_objs, void * cache);
/***/
void  deepeedeekay_rte_mempool_trace_get_bulk(void * mempool, void ** obj_table, uint32_t nb_objs, void * cache);
/***/
void  deepeedeekay_rte_mempool_trace_get_contig_blocks(void * mempool, void ** first_obj_table, uint32_t nb_objs);
/***/
void  deepeedeekay_rte_mempool_trace_default_cache(void * mempool, uint32_t lcore_id, void * default_cache);
/***/
void  deepeedeekay_rte_mempool_trace_cache_flush(void * cache, void * mempool);
/***/
struct rte_mempool_objhdr * deepeedeekay_rte_mempool_get_header(void * obj);
/**
 Return a pointer to the mempool owning this object.
 
in param obj
   An object that is owned by a pool. If this is not the case,   the behavior is undefined. 
return
   A pointer to the mempool structure.*/
struct rte_mempool * deepeedeekay_rte_mempool_from_obj(void * obj);
/***/
struct rte_mempool_objtlr * deepeedeekay_rte_mempool_get_trailer(void * obj);
/**
 */
struct rte_mempool_ops * deepeedeekay_rte_mempool_get_ops(int ops_index);
/**
 */
int  deepeedeekay_rte_mempool_ops_dequeue_bulk(struct rte_mempool * mp, void ** obj_table, unsigned int n);
/**
 */
int  deepeedeekay_rte_mempool_ops_dequeue_contig_blocks(struct rte_mempool * mp, void ** first_obj_table, unsigned int n);
/**
 */
int  deepeedeekay_rte_mempool_ops_enqueue_bulk(struct rte_mempool * mp, void *const * obj_table, unsigned int n);
/**
 Get a pointer to the per-lcore default mempool cache.
 
in param mp
   A pointer to the mempool structure. 
in param lcore_id
   The logical core id. 
return
   A pointer to the mempool cache or NULL if disabled or unregistered non-EAL   thread.*/
struct rte_mempool_cache * deepeedeekay_rte_mempool_default_cache(struct rte_mempool * mp, unsigned int lcore_id);
/**
 Flush a user-owned mempool cache to the specified mempool.
 
in param cache
   A pointer to the mempool cache. 
in param mp
   A pointer to the mempool.*/
void  deepeedeekay_rte_mempool_cache_flush(struct rte_mempool_cache * cache, struct rte_mempool * mp);
/**
 */
void  deepeedeekay_rte_mempool_do_generic_put(struct rte_mempool * mp, void *const * obj_table, unsigned int n, struct rte_mempool_cache * cache);
/**
 Put several objects back in the mempool.
 
in param mp
   A pointer to the mempool structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the mempool from the obj_table. 
in param cache
   A pointer to a mempool cache structure. May be NULL if not needed.*/
void  deepeedeekay_rte_mempool_generic_put(struct rte_mempool * mp, void *const * obj_table, unsigned int n, struct rte_mempool_cache * cache);
/**
 Put several objects back in the mempool.
 This function calls the multi-producer or the single-producer version depending on the default behavior that was specified at mempool creation time (see flags).
 
in param mp
   A pointer to the mempool structure. 
in param obj_table
   A pointer to a table of void * pointers (objects). 
in param n
   The number of objects to add in the mempool from obj_table.*/
void  deepeedeekay_rte_mempool_put_bulk(struct rte_mempool * mp, void *const * obj_table, unsigned int n);
/**
 Put one object back in the mempool.
 This function calls the multi-producer or the single-producer version depending on the default behavior that was specified at mempool creation time (see flags).
 
in param mp
   A pointer to the mempool structure. 
in param obj
   A pointer to the object to be added.*/
void  deepeedeekay_rte_mempool_put(struct rte_mempool * mp, void * obj);
/**
 */
int  deepeedeekay_rte_mempool_do_generic_get(struct rte_mempool * mp, void ** obj_table, unsigned int n, struct rte_mempool_cache * cache);
/**
 Get several objects from the mempool.
 If cache is enabled, objects will be retrieved first from cache, subsequently from the common pool. Note that it can return -ENOENT when the local cache and common pool are empty, even if cache from other lcores are full.
 
in param mp
   A pointer to the mempool structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to get from mempool to obj_table. 
in param cache
   A pointer to a mempool cache structure. May be NULL if not needed. 
return
   - 0: Success; objects taken.   - -ENOENT: Not enough entries in the mempool; no object is retrieved.*/
int  deepeedeekay_rte_mempool_generic_get(struct rte_mempool * mp, void ** obj_table, unsigned int n, struct rte_mempool_cache * cache);
/**
 Get several objects from the mempool.
 This function calls the multi-consumers or the single-consumer version, depending on the default behaviour that was specified at mempool creation time (see flags).
 If cache is enabled, objects will be retrieved first from cache, subsequently from the common pool. Note that it can return -ENOENT when the local cache and common pool are empty, even if cache from other lcores are full.
 
in param mp
   A pointer to the mempool structure. 
in param obj_table
   A pointer to a table of void * pointers (objects) that will be filled. 
in param n
   The number of objects to get from the mempool to obj_table. 
return
   - 0: Success; objects taken   - -ENOENT: Not enough entries in the mempool; no object is retrieved.*/
int  deepeedeekay_rte_mempool_get_bulk(struct rte_mempool * mp, void ** obj_table, unsigned int n);
/**
 Get one object from the mempool.
 This function calls the multi-consumers or the single-consumer version, depending on the default behavior that was specified at mempool creation (see flags).
 If cache is enabled, objects will be retrieved first from cache, subsequently from the common pool. Note that it can return -ENOENT when the local cache and common pool are empty, even if cache from other lcores are full.
 
in param mp
   A pointer to the mempool structure. 
in param obj_p
   A pointer to a void * pointer (object) that will be filled. 
return
   - 0: Success; objects taken.   - -ENOENT: Not enough entries in the mempool; no object is retrieved.*/
int  deepeedeekay_rte_mempool_get(struct rte_mempool * mp, void ** obj_p);
/**
 Get a contiguous blocks of objects from the mempool.
 If cache is enabled, consider to flush it first, to reuse objects as soon as possible.
 The application should check that the driver supports the operation by calling rte_mempool_ops_get_info() and checking that `contig_block_size` is not zero.
 
in param mp
   A pointer to the mempool structure. 
in param first_obj_table
   A pointer to a pointer to the first object in each block. 
in param n
   The number of blocks to get from mempool. 
return
   - 0: Success; blocks taken.   - -ENOBUFS: Not enough entries in the mempool; no object is retrieved.   - -EOPNOTSUPP: The mempool driver does not support block dequeue*/
int  deepeedeekay_rte_mempool_get_contig_blocks(struct rte_mempool * mp, void ** first_obj_table, unsigned int n);
/**
 Test if the mempool is full.
 When cache is enabled, this function has to browse the length of all lcores, so it should not be used in a data path, but only for debug purposes. User-owned mempool caches are not accounted for.
 
in param mp
   A pointer to the mempool structure. 
return
   - 1: The mempool is full.   - 0: The mempool is not full.*/
int  deepeedeekay_rte_mempool_full(const struct rte_mempool * mp);
/**
 Test if the mempool is empty.
 When cache is enabled, this function has to browse the length of all lcores, so it should not be used in a data path, but only for debug purposes. User-owned mempool caches are not accounted for.
 
in param mp
   A pointer to the mempool structure. 
return
   - 1: The mempool is empty.   - 0: The mempool is not empty.*/
int  deepeedeekay_rte_mempool_empty(const struct rte_mempool * mp);
/**
 Return the IO address of elt, which is an element of the pool mp.
 
in param elt
   A pointer (virtual address) to the element of the pool. 
return
   The IO address of the elt element.   If the mempool was created with RTE_MEMPOOL_F_NO_IOVA_CONTIG, the   returned value is RTE_BAD_IOVA.*/
rte_iova_t  deepeedeekay_rte_mempool_virt2iova(const void * elt);
/**
 Return a pointer to the private data in an mempool structure.
 
in param mp
   A pointer to the mempool structure. 
return
   A pointer to the private data.*/
void * deepeedeekay_rte_mempool_get_priv(struct rte_mempool * mp);
/**
 Prefetch a cache line into all cache levels. 
in param p
   Address to prefetch*/
void  deepeedeekay_rte_prefetch0(const volatile void * p);
/**
 Prefetch a cache line into all cache levels except the 0th cache level. 
in param p
   Address to prefetch*/
void  deepeedeekay_rte_prefetch1(const volatile void * p);
/**
 Prefetch a cache line into all cache levels except the 0th and 1th cache levels. 
in param p
   Address to prefetch*/
void  deepeedeekay_rte_prefetch2(const volatile void * p);
/**
 Prefetch a cache line into all cache levels (non-temporal/transient version)
 The non-temporal prefetch is intended as a prefetch hint that processor will use the prefetched data only once or short period, unlike the rte_prefetch0() function which imply that prefetched data to use repeatedly.
 
in param p
   Address to prefetch*/
void  deepeedeekay_rte_prefetch_non_temporal(const volatile void * p);
/**
 
warning
  this API may change, or be removed, without prior notice
 Prefetch a cache line into all cache levels, with intention to write. This prefetch variant hints to the CPU that the program is expecting to write to the cache line being prefetched.
 
in param p
 Address to prefetch*/
void  deepeedeekay_rte_prefetch0_write(const void * p);
/**
 
warning
  this API may change, or be removed, without prior notice
 Prefetch a cache line into all cache levels, except the 0th, with intention to write. This prefetch variant hints to the CPU that the program is expecting to write to the cache line being prefetched.
 
in param p
 Address to prefetch*/
void  deepeedeekay_rte_prefetch1_write(const void * p);
/**
 
warning
  this API may change, or be removed, without prior notice
 Prefetch a cache line into all cache levels, except the 0th and 1st, with intention to write. This prefetch variant hints to the CPU that the program is expecting to write to the cache line being prefetched.
 
in param p
 Address to prefetch*/
void  deepeedeekay_rte_prefetch2_write(const void * p);
/**
 
warning
  this API may change, or be removed, without prior notice
 Demote a cache line to a more distant level of cache from the processor. CLDEMOTE hints to hardware to move (demote) a cache line from the closest to the processor to a level more distant from the processor. It is a hint and not guaranteed. rte_cldemote is intended to move the cache line to the more remote cache, where it expects sharing to be efficient and to indicate that a line may be accessed by a different core in the future.
 
in param p
   Address to demote*/
void  deepeedeekay_rte_cldemote(const volatile void * p);
/***/
uint16_t  deepeedeekay_rte_constant_bswap16(uint16_t x);
/***/
uint32_t  deepeedeekay_rte_constant_bswap32(uint32_t x);
/***/
uint64_t  deepeedeekay_rte_constant_bswap64(uint64_t x);
/***/
uint16_t  deepeedeekay_rte_arch_bswap16(uint16_t _x);
/***/
uint32_t  deepeedeekay_rte_arch_bswap32(uint32_t _x);
/***/
uint64_t  deepeedeekay_rte_arch_bswap64(uint64_t _x);
/**
 Prefetch the first part of the mbuf
 The first 64 bytes of the mbuf corresponds to fields that are used early in the receive path. If the cache line of the architecture is higher than 64B, the second part will also be prefetched.
 
in param m
   The pointer to the mbuf.*/
void  deepeedeekay_rte_mbuf_prefetch_part1(struct rte_mbuf * m);
/**
 Prefetch the second part of the mbuf
 The next 64 bytes of the mbuf corresponds to fields that are used in the transmit path. If the cache line of the architecture is higher than 64B, this function does nothing as it is expected that the full mbuf is already in cache.
 
in param m
   The pointer to the mbuf.*/
void  deepeedeekay_rte_mbuf_prefetch_part2(struct rte_mbuf * m);
/***/
uint16_t  deepeedeekay_rte_pktmbuf_priv_size(struct rte_mempool * mp);
/**
 Get the IOVA address of the mbuf data buffer.
 
in param m
   The pointer to the mbuf. 
return
   The IOVA address of the mbuf.*/
rte_iova_t  deepeedeekay_rte_mbuf_iova_get(const struct rte_mbuf * m);
/**
 Set the IOVA address of the mbuf data buffer.
 
in param m
   The pointer to the mbuf. 
in param iova
   Value to set as IOVA address of the mbuf.*/
void  deepeedeekay_rte_mbuf_iova_set(struct rte_mbuf * m, rte_iova_t iova);
/**
 Return the IO address of the beginning of the mbuf data
 
in param mb
   The pointer to the mbuf. 
return
   The IO address of the beginning of the mbuf data*/
rte_iova_t  deepeedeekay_rte_mbuf_data_iova(const struct rte_mbuf * mb);
/**
 Return the default IO address of the beginning of the mbuf data
 This function is used by drivers in their receive function, as it returns the location where data should be written by the NIC, taking the default headroom in account.
 
in param mb
   The pointer to the mbuf. 
return
   The IO address of the beginning of the mbuf data*/
rte_iova_t  deepeedeekay_rte_mbuf_data_iova_default(const struct rte_mbuf * mb);
/**
 Return the mbuf owning the data buffer address of an indirect mbuf.
 
in param mi
   The pointer to the indirect mbuf. 
return
   The address of the direct mbuf corresponding to buffer_addr.*/
struct rte_mbuf * deepeedeekay_rte_mbuf_from_indirect(struct rte_mbuf * mi);
/**
 Return address of buffer embedded in the given mbuf.
 The return value shall be same as mb->buf_addr if the mbuf is already initialized and direct. However, this API is useful if mempool of the mbuf is already known because it doesn't need to access mbuf contents in order to get the mempool pointer.
 
in param mb
   The pointer to the mbuf. 
in param mp
   The pointer to the mempool of the mbuf. 
return
   The pointer of the mbuf buffer.*/
char * deepeedeekay_rte_mbuf_buf_addr(struct rte_mbuf * mb, struct rte_mempool * mp);
/**
 Return the default address of the beginning of the mbuf data.
 
in param mb
   The pointer to the mbuf. 
return
   The pointer of the beginning of the mbuf data.*/
char * deepeedeekay_rte_mbuf_data_addr_default(struct rte_mbuf * mb);
/**
 Return address of buffer embedded in the given mbuf.
 
note
: Accessing mempool pointer of a mbuf is expensive because the pointer is stored in the 2nd cache line of mbuf. If mempool is known, it is better not to reference the mempool pointer in mbuf but calling rte_mbuf_buf_addr() would be more efficient.
 
in param md
   The pointer to the mbuf. 
return
   The address of the data buffer owned by the mbuf.*/
char * deepeedeekay_rte_mbuf_to_baddr(struct rte_mbuf * md);
/**
 Return the starting address of the private data area embedded in the given mbuf.
 Note that no check is made to ensure that a private data area actually exists in the supplied mbuf.
 
in param m
   The pointer to the mbuf. 
return
   The starting address of the private data area of the given mbuf.*/
void * deepeedeekay_rte_mbuf_to_priv(struct rte_mbuf * m);
/**
 Return the flags from private data in an mempool structure.
 
in param mp
   A pointer to the mempool structure. 
return
   The flags from the private data structure.*/
uint32_t  deepeedeekay_rte_pktmbuf_priv_flags(struct rte_mempool * mp);
/**
 Reads the value of an mbuf's refcnt. 
in param m
   Mbuf to read 
return
   Reference count number.*/
uint16_t  deepeedeekay_rte_mbuf_refcnt_read(const struct rte_mbuf * m);
/**
 Sets an mbuf's refcnt to a defined value. 
in param m
   Mbuf to update 
in param new_value
   Value set*/
void  deepeedeekay_rte_mbuf_refcnt_set(struct rte_mbuf * m, uint16_t new_value);
/**
 Adds given value to an mbuf's refcnt and returns its new value. 
in param m
   Mbuf to update 
in param value
   Value to add/subtract 
return
   Updated value*/
uint16_t  deepeedeekay_rte_mbuf_refcnt_update(struct rte_mbuf * m, int16_t value);
/**
 Reads the refcnt of an external buffer.
 
in param shinfo
   Shared data of the external buffer. 
return
   Reference count number.*/
uint16_t  deepeedeekay_rte_mbuf_ext_refcnt_read(const struct rte_mbuf_ext_shared_info * shinfo);
/**
 Set refcnt of an external buffer.
 
in param shinfo
   Shared data of the external buffer. 
in param new_value
   Value set*/
void  deepeedeekay_rte_mbuf_ext_refcnt_set(struct rte_mbuf_ext_shared_info * shinfo, uint16_t new_value);
/**
 Add given value to refcnt of an external buffer and return its new value.
 
in param shinfo
   Shared data of the external buffer. 
in param value
   Value to add/subtract 
return
   Updated value*/
uint16_t  deepeedeekay_rte_mbuf_ext_refcnt_update(struct rte_mbuf_ext_shared_info * shinfo, int16_t value);
/**
 Allocate an uninitialized mbuf from mempool *mp*.
 This function can be used by PMDs (especially in RX functions) to allocate an uninitialized mbuf. The driver is responsible of initializing all the required fields. See rte_pktmbuf_reset(). For standard needs, prefer rte_pktmbuf_alloc().
 The caller can expect that the following fields of the mbuf structure are initialized: buf_addr, buf_iova, buf_len, refcnt=1, nb_segs=1, next=NULL, pool, priv_size. The other fields must be initialized by the caller.
 
in param mp
   The mempool from which mbuf is allocated. 
return
   - The pointer to the new mbuf on success.   - NULL if allocation failed.*/
struct rte_mbuf * deepeedeekay_rte_mbuf_raw_alloc(struct rte_mempool * mp);
/**
 Put mbuf back into its original mempool.
 The caller must ensure that the mbuf is direct and properly reinitialized (refcnt=1, next=NULL, nb_segs=1), as done by rte_pktmbuf_prefree_seg().
 This function should be used with care, when optimization is required. For standard needs, prefer rte_pktmbuf_free() or rte_pktmbuf_free_seg().
 
in param m
   The mbuf to be freed.*/
void  deepeedeekay_rte_mbuf_raw_free(struct rte_mbuf * m);
/**
 Get the data room size of mbufs stored in a pktmbuf_pool
 The data room size is the amount of data that can be stored in a mbuf including the headroom (RTE_PKTMBUF_HEADROOM).
 
in param mp
   The packet mbuf pool. 
return
   The data room size of mbufs stored in this mempool.*/
uint16_t  deepeedeekay_rte_pktmbuf_data_room_size(struct rte_mempool * mp);
/**
 Reset the data_off field of a packet mbuf to its default value.
 The given mbuf must have only one segment, which should be empty.
 
in param m
   The packet mbuf's data_off field has to be reset.*/
void  deepeedeekay_rte_pktmbuf_reset_headroom(struct rte_mbuf * m);
/**
 Reset the fields of a packet mbuf to their default values.
 The given mbuf must have only one segment.
 
in param m
   The packet mbuf to be reset.*/
void  deepeedeekay_rte_pktmbuf_reset(struct rte_mbuf * m);
/**
 Allocate a new mbuf from a mempool.
 This new mbuf contains one segment, which has a length of 0. The pointer to data is initialized to have some bytes of headroom in the buffer (if buffer size allows).
 
in param mp
   The mempool from which the mbuf is allocated. 
return
   - The pointer to the new mbuf on success.   - NULL if allocation failed.*/
struct rte_mbuf * deepeedeekay_rte_pktmbuf_alloc(struct rte_mempool * mp);
/**
 Allocate a bulk of mbufs, initialize refcnt and reset the fields to default values.
  
in param pool
    The mempool from which mbufs are allocated.  
in param mbufs
    Array of pointers to mbufs  
in param count
    Array size  
return
   - 0: Success   - -ENOENT: Not enough entries in the mempool; no mbufs are retrieved.*/
int  deepeedeekay_rte_pktmbuf_alloc_bulk(struct rte_mempool * pool, struct rte_mbuf ** mbufs, unsigned int count);
/**
 Initialize shared data at the end of an external buffer before attaching to a mbuf by ``rte_pktmbuf_attach_extbuf()``. This is not a mandatory initialization but a helper function to simply spare a few bytes at the end of the buffer for shared data. If shared data is allocated separately, this should not be called but application has to properly initialize the shared data according to its need.
 Free callback and its argument is saved and the refcnt is set to 1.
 
warning
 The value of buf_len will be reduced to RTE_PTR_DIFF(shinfo, buf_addr) after this initialization. This shall be used for ``rte_pktmbuf_attach_extbuf()``
 
in param buf_addr
   The pointer to the external buffer. 
inout param buf_len
   The pointer to length of the external buffer. Input value must be   larger than the size of ``struct rte_mbuf_ext_shared_info`` and   padding for alignment. If not enough, this function will return NULL.   Adjusted buffer length will be returned through this pointer. 
in param free_cb
   Free callback function to call when the external buffer needs to be   freed. 
in param fcb_opaque
   Argument for the free callback function.
 
return
   A pointer to the initialized shared data on success, return NULL   otherwise.*/
struct rte_mbuf_ext_shared_info * deepeedeekay_rte_pktmbuf_ext_shinfo_init_helper(void * buf_addr, uint16_t * buf_len, rte_mbuf_extbuf_free_callback_t free_cb, void * fcb_opaque);
/**
 Attach an external buffer to a mbuf.
 User-managed anonymous buffer can be attached to an mbuf. When attaching it, corresponding free callback function and its argument should be provided via shinfo. This callback function will be called once all the mbufs are detached from the buffer (refcnt becomes zero).
 The headroom length of the attaching mbuf will be set to zero and this can be properly adjusted after attachment. For example, ``rte_pktmbuf_adj()`` or ``rte_pktmbuf_reset_headroom()`` might be used.
 Similarly, the packet length is initialized to 0. If the buffer contains data, the user has to adjust ``data_len`` and the ``pkt_len`` field of the mbuf accordingly.
 More mbufs can be attached to the same external buffer by ``rte_pktmbuf_attach()`` once the external buffer has been attached by this API.
 Detachment can be done by either ``rte_pktmbuf_detach_extbuf()`` or ``rte_pktmbuf_detach()``.
 Memory for shared data must be provided and user must initialize all of the content properly, especially free callback and refcnt. The pointer of shared data will be stored in m->shinfo. ``rte_pktmbuf_ext_shinfo_init_helper`` can help to simply spare a few bytes at the end of buffer for the shared data, store free callback and its argument and set the refcnt to 1. The following is an example:
   struct rte_mbuf_ext_shared_info *shinfo =          rte_pktmbuf_ext_shinfo_init_helper(buf_addr, &buf_len,                                             free_cb, fcb_arg);   rte_pktmbuf_attach_extbuf(m, buf_addr, buf_iova, buf_len, shinfo);   rte_pktmbuf_reset_headroom(m);   rte_pktmbuf_adj(m, data_len);
 Attaching an external buffer is quite similar to mbuf indirection in replacing buffer addresses and length of a mbuf, but a few differences: - When an indirect mbuf is attached, refcnt of the direct mbuf would be   2 as long as the direct mbuf itself isn't freed after the attachment.   In such cases, the buffer area of a direct mbuf must be read-only. But   external buffer has its own refcnt and it starts from 1. Unless   multiple mbufs are attached to a mbuf having an external buffer, the   external buffer is writable. - There's no need to allocate buffer from a mempool. Any buffer can be   attached with appropriate free callback and its IO address. - Smaller metadata is required to maintain shared data such as refcnt.
 
in param m
   The pointer to the mbuf. 
in param buf_addr
   The pointer to the external buffer. 
in param buf_iova
   IO address of the external buffer. 
in param buf_len
   The size of the external buffer. 
in param shinfo
   User-provided memory for shared data of the external buffer.*/
void  deepeedeekay_rte_pktmbuf_attach_extbuf(struct rte_mbuf * m, void * buf_addr, rte_iova_t buf_iova, uint16_t buf_len, struct rte_mbuf_ext_shared_info * shinfo);
/**
 Copy dynamic fields from msrc to mdst.
 
in param mdst
   The destination mbuf. 
in param msrc
   The source mbuf.*/
void  deepeedeekay_rte_mbuf_dynfield_copy(struct rte_mbuf * mdst, const struct rte_mbuf * msrc);
/**
 Attach packet mbuf to another packet mbuf.
 If the mbuf we are attaching to isn't a direct buffer and is attached to an external buffer, the mbuf being attached will be attached to the external buffer instead of mbuf indirection.
 Otherwise, the mbuf will be indirectly attached. After attachment we refer the mbuf we attached as 'indirect', while mbuf we attached to as 'direct'.  The direct mbuf's reference counter is incremented.
 Right now, not supported:  - attachment for already indirect mbuf (e.g. - mi has to be direct).  - mbuf we trying to attach (mi) is used by someone else    e.g. it's reference counter is greater then 1.
 
in param mi
   The indirect packet mbuf. 
in param m
   The packet mbuf we're attaching to.*/
void  deepeedeekay_rte_pktmbuf_attach(struct rte_mbuf * mi, struct rte_mbuf * m);
/**
 Detach a packet mbuf from external buffer or direct buffer.
  - decrement refcnt and free the external/direct buffer if refcnt    becomes zero.  - restore original mbuf address and length values.  - reset pktmbuf data and data_len to their default values.
 All other fields of the given packet mbuf will be left intact.
 If the packet mbuf was allocated from the pool with pinned external buffers the rte_pktmbuf_detach does nothing with the mbuf of this kind, because the pinned buffers are not supposed to be detached.
 
in param m
   The indirect attached packet mbuf.*/
void  deepeedeekay_rte_pktmbuf_detach(struct rte_mbuf * m);
/**
 Decrease reference counter and unlink a mbuf segment
 This function does the same than a free, except that it does not return the segment to its pool. It decreases the reference counter, and if it reaches 0, it is detached from its parent for an indirect mbuf.
 
in param m
   The mbuf to be unlinked 
return
   - (m) if it is the last reference. It can be recycled or freed.   - (NULL) if the mbuf still has remaining references on it.*/
struct rte_mbuf * deepeedeekay_rte_pktmbuf_prefree_seg(struct rte_mbuf * m);
/**
 Free a segment of a packet mbuf into its original mempool.
 Free an mbuf, without parsing other segments in case of chained buffers.
 
in param m
   The packet mbuf segment to be freed.*/
void  deepeedeekay_rte_pktmbuf_free_seg(struct rte_mbuf * m);
/**
 Free a packet mbuf back into its original mempool.
 Free an mbuf, and all its segments in case of chained buffers. Each segment is added back into its original mempool.
 
in param m
   The packet mbuf to be freed. If NULL, the function does nothing.*/
void  deepeedeekay_rte_pktmbuf_free(struct rte_mbuf * m);
/**
 Adds given value to the refcnt of all packet mbuf segments.
 Walks through all segments of given packet mbuf and for each of them invokes rte_mbuf_refcnt_update().
 
in param m
   The packet mbuf whose refcnt to be updated. 
in param v
   The value to add to the mbuf's segments refcnt.*/
void  deepeedeekay_rte_pktmbuf_refcnt_update(struct rte_mbuf * m, int16_t v);
/**
 Get the headroom in a packet mbuf.
 
in param m
   The packet mbuf. 
return
   The length of the headroom.*/
uint16_t  deepeedeekay_rte_pktmbuf_headroom(const struct rte_mbuf * m);
/**
 Get the tailroom of a packet mbuf.
 
in param m
   The packet mbuf. 
return
   The length of the tailroom.*/
uint16_t  deepeedeekay_rte_pktmbuf_tailroom(const struct rte_mbuf * m);
/**
 Get the last segment of the packet.
 
in param m
   The packet mbuf. 
return
   The last segment of the given mbuf.*/
struct rte_mbuf * deepeedeekay_rte_pktmbuf_lastseg(struct rte_mbuf * m);
/**
 Prepend len bytes to an mbuf data area.
 Returns a pointer to the new data start address. If there is not enough headroom in the first segment, the function will return NULL, without modifying the mbuf.
 
in param m
   The pkt mbuf. 
in param len
   The amount of data to prepend (in bytes). 
return
   A pointer to the start of the newly prepended data, or   NULL if there is not enough headroom space in the first segment*/
char * deepeedeekay_rte_pktmbuf_prepend(struct rte_mbuf * m, uint16_t len);
/**
 Append len bytes to an mbuf.
 Append len bytes to an mbuf and return a pointer to the start address of the added data. If there is not enough tailroom in the last segment, the function will return NULL, without modifying the mbuf.
 
in param m
   The packet mbuf. 
in param len
   The amount of data to append (in bytes). 
return
   A pointer to the start of the newly appended data, or   NULL if there is not enough tailroom space in the last segment*/
char * deepeedeekay_rte_pktmbuf_append(struct rte_mbuf * m, uint16_t len);
/**
 Remove len bytes at the beginning of an mbuf.
 Returns a pointer to the start address of the new data area. If the length is greater than the length of the first segment, then the function will fail and return NULL, without modifying the mbuf.
 
in param m
   The packet mbuf. 
in param len
   The amount of data to remove (in bytes). 
return
   A pointer to the new start of the data.*/
char * deepeedeekay_rte_pktmbuf_adj(struct rte_mbuf * m, uint16_t len);
/**
 Remove len bytes of data at the end of the mbuf.
 If the length is greater than the length of the last segment, the function will fail and return -1 without modifying the mbuf.
 
in param m
   The packet mbuf. 
in param len
   The amount of data to remove (in bytes). 
return
   - 0: On success.   - -1: On error.*/
int  deepeedeekay_rte_pktmbuf_trim(struct rte_mbuf * m, uint16_t len);
/**
 Test if mbuf data is contiguous.
 
in param m
   The packet mbuf. 
return
   - 1, if all data is contiguous (one segment).   - 0, if there is several segments.*/
int  deepeedeekay_rte_pktmbuf_is_contiguous(const struct rte_mbuf * m);
/**
 Read len data bytes in a mbuf at specified offset.
 If the data is contiguous, return the pointer in the mbuf data, else copy the data in the buffer provided by the user and return its pointer.
 
in param m
   The pointer to the mbuf. 
in param off
   The offset of the data in the mbuf. 
in param len
   The amount of bytes to read. 
in param buf
   The buffer where data is copied if it is not contiguous in mbuf   data. Its length should be at least equal to the len parameter. 
return
   The pointer to the data, either in the mbuf if it is contiguous,   or in the user buffer. If mbuf is too small, NULL is returned.*/
const void * deepeedeekay_rte_pktmbuf_read(const struct rte_mbuf * m, uint32_t off, uint32_t len, void * buf);
/**
 Chain an mbuf to another, thereby creating a segmented packet.
 Note: The implementation will do a linear walk over the segments to find the tail entry. For cases when there are many segments, it's better to chain the entries manually.
 
in param head
   The head of the mbuf chain (the first packet) 
in param tail
   The mbuf to put last in the chain
 
return
   - 0, on success.   - -EOVERFLOW, if the chain segment limit exceeded*/
int  deepeedeekay_rte_pktmbuf_chain(struct rte_mbuf * head, struct rte_mbuf * tail);
/**
 For given input values generate raw tx_offload value. Note that it is caller responsibility to make sure that input parameters don't exceed maximum bit-field values. 
in param il2
   l2_len value. 
in param il3
   l3_len value. 
in param il4
   l4_len value. 
in param tso
   tso_segsz value. 
in param ol3
   outer_l3_len value. 
in param ol2
   outer_l2_len value. 
in param unused
   unused value. 
return
   raw tx_offload value.*/
uint64_t  deepeedeekay_rte_mbuf_tx_offload(uint64_t il2, uint64_t il3, uint64_t il4, uint64_t tso, uint64_t ol3, uint64_t ol2, uint64_t unused);
/**
 Validate general requirements for Tx offload in mbuf.
 This function checks correctness and completeness of Tx offload settings.
 
in param m
   The packet mbuf to be validated. 
return
   0 if packet is valid*/
int  deepeedeekay_rte_validate_tx_offload(const struct rte_mbuf * m);
/**
 Linearize data in mbuf.
 This function moves the mbuf data in the first segment if there is enough tailroom. The subsequent segments are unchained and freed.
 
in param mbuf
   mbuf to linearize 
return
   - 0, on success   - -1, on error*/
int  deepeedeekay_rte_pktmbuf_linearize(struct rte_mbuf * mbuf);
/**
 Get the value of mbuf sched queue_id field.*/
uint32_t  deepeedeekay_rte_mbuf_sched_queue_get(const struct rte_mbuf * m);
/**
 Get the value of mbuf sched traffic_class field.*/
uint8_t  deepeedeekay_rte_mbuf_sched_traffic_class_get(const struct rte_mbuf * m);
/**
 Get the value of mbuf sched color field.*/
uint8_t  deepeedeekay_rte_mbuf_sched_color_get(const struct rte_mbuf * m);
/**
 Get the values of mbuf sched queue_id, traffic_class and color.
 
in param m
   Mbuf to read 
in param queue_id
  Returns the queue id 
in param traffic_class
  Returns the traffic class id 
in param color
  Returns the colour id*/
void  deepeedeekay_rte_mbuf_sched_get(const struct rte_mbuf * m, uint32_t * queue_id, uint8_t * traffic_class, uint8_t * color);
/**
 Set the mbuf sched queue_id to the defined value.*/
void  deepeedeekay_rte_mbuf_sched_queue_set(struct rte_mbuf * m, uint32_t queue_id);
/**
 Set the mbuf sched traffic_class id to the defined value.*/
void  deepeedeekay_rte_mbuf_sched_traffic_class_set(struct rte_mbuf * m, uint8_t traffic_class);
/**
 Set the mbuf sched color id to the defined value.*/
void  deepeedeekay_rte_mbuf_sched_color_set(struct rte_mbuf * m, uint8_t color);
/**
 Set the mbuf sched queue_id, traffic_class and color.
 
in param m
   Mbuf to set 
in param queue_id
  Queue id value to be set 
in param traffic_class
  Traffic class id value to be set 
in param color
  Color id to be set*/
void  deepeedeekay_rte_mbuf_sched_set(struct rte_mbuf * m, uint32_t queue_id, uint8_t traffic_class, uint8_t color);
/**
 Check if two Ethernet addresses are the same.
 
in param ea1
  A pointer to the first ether_addr structure containing  the ethernet address. 
in param ea2
  A pointer to the second ether_addr structure containing  the ethernet address.
 
return
  True  (1) if the given two ethernet address are the same;  False (0) otherwise.*/
int  deepeedeekay_rte_is_same_ether_addr(const struct rte_ether_addr * ea1, const struct rte_ether_addr * ea2);
/**
 Check if an Ethernet address is filled with zeros.
 
in param ea
   A pointer to a ether_addr structure containing the ethernet address   to check. 
return
   True  (1) if the given ethernet address is filled with zeros;   false (0) otherwise.*/
int  deepeedeekay_rte_is_zero_ether_addr(const struct rte_ether_addr * ea);
/**
 Check if an Ethernet address is a unicast address.
 
in param ea
   A pointer to a ether_addr structure containing the ethernet address   to check. 
return
   True  (1) if the given ethernet address is a unicast address;   false (0) otherwise.*/
int  deepeedeekay_rte_is_unicast_ether_addr(const struct rte_ether_addr * ea);
/**
 Check if an Ethernet address is a multicast address.
 
in param ea
   A pointer to a ether_addr structure containing the ethernet address   to check. 
return
   True  (1) if the given ethernet address is a multicast address;   false (0) otherwise.*/
int  deepeedeekay_rte_is_multicast_ether_addr(const struct rte_ether_addr * ea);
/**
 Check if an Ethernet address is a broadcast address.
 
in param ea
   A pointer to a ether_addr structure containing the ethernet address   to check. 
return
   True  (1) if the given ethernet address is a broadcast address;   false (0) otherwise.*/
int  deepeedeekay_rte_is_broadcast_ether_addr(const struct rte_ether_addr * ea);
/**
 Check if an Ethernet address is a universally assigned address.
 
in param ea
   A pointer to a ether_addr structure containing the ethernet address   to check. 
return
   True  (1) if the given ethernet address is a universally assigned address;   false (0) otherwise.*/
int  deepeedeekay_rte_is_universal_ether_addr(const struct rte_ether_addr * ea);
/**
 Check if an Ethernet address is a locally assigned address.
 
in param ea
   A pointer to a ether_addr structure containing the ethernet address   to check. 
return
   True  (1) if the given ethernet address is a locally assigned address;   false (0) otherwise.*/
int  deepeedeekay_rte_is_local_admin_ether_addr(const struct rte_ether_addr * ea);
/**
 Check if an Ethernet address is a valid address. Checks that the address is a unicast address and is not filled with zeros.
 
in param ea
   A pointer to a ether_addr structure containing the ethernet address   to check. 
return
   True  (1) if the given ethernet address is valid;   false (0) otherwise.*/
int  deepeedeekay_rte_is_valid_assigned_ether_addr(const struct rte_ether_addr * ea);
/**
 Copy an Ethernet address.
 
in param ea_from
   A pointer to a ether_addr structure holding the Ethernet address to copy. 
in param ea_to
   A pointer to a ether_addr structure where to copy the Ethernet address.*/
void  deepeedeekay_rte_ether_addr_copy(const struct rte_ether_addr *restrict ea_from, struct rte_ether_addr *restrict ea_to);
/**
 Extract VLAN tag information into mbuf
 Software version of VLAN stripping
 
in param m
   The packet mbuf. 
return
   - 0: Success   - 1: not a vlan packet*/
int  deepeedeekay_rte_vlan_strip(struct rte_mbuf * m);
/**
 Insert VLAN tag into mbuf.
 Software version of VLAN unstripping
 
in param m
   The packet mbuf. 
return
   - 0: On success   -EPERM: mbuf is shared overwriting would be unsafe   -ENOSPC: not enough headroom in mbuf*/
int  deepeedeekay_rte_vlan_insert(struct rte_mbuf ** m);
/**
 Process the non-complemented checksum of a buffer.
 
in param buf
   Pointer to the buffer. 
in param len
   Length of the buffer. 
return
   The non-complemented checksum.*/
uint16_t  deepeedeekay_rte_raw_cksum(const void * buf, size_t len);
/**
 Compute the raw (non complemented) checksum of a packet.
 
in param m
   The pointer to the mbuf. 
in param off
   The offset in bytes to start the checksum. 
in param len
   The length in bytes of the data to checksum. 
in param cksum
   A pointer to the checksum, filled on success. 
return
   0 on success, -1 on error (bad length or offset).*/
int  deepeedeekay_rte_raw_cksum_mbuf(const struct rte_mbuf * m, uint32_t off, uint32_t len, uint16_t * cksum);
/**
 Get the length of an IPv4 header.
 
in param ipv4_hdr
   Pointer to the IPv4 header. 
return
   The length of the IPv4 header (with options if present) in bytes.*/
uint8_t  deepeedeekay_rte_ipv4_hdr_len(const struct rte_ipv4_hdr * ipv4_hdr);
/**
 Process the IPv4 checksum of an IPv4 header.
 The checksum field must be set to 0 by the caller.
 
in param ipv4_hdr
   The pointer to the contiguous IPv4 header. 
return
   The complemented checksum to set in the IP packet.*/
uint16_t  deepeedeekay_rte_ipv4_cksum(const struct rte_ipv4_hdr * ipv4_hdr);
/**
 
warning
  this API may change without prior notice.
 Process the IPv4 checksum of an IPv4 header without any extensions.
 The checksum field does NOT have to be set by the caller, the field is skipped by the calculation.
 
in param ipv4_hdr
   The pointer to the contiguous IPv4 header. 
return
   The complemented checksum to set in the IP packet.*/
uint16_t  deepeedeekay_rte_ipv4_cksum_simple(const struct rte_ipv4_hdr * ipv4_hdr);
/**
 Process the pseudo-header checksum of an IPv4 header.
 The checksum field must be set to 0 by the caller.
 Depending on the ol_flags, the pseudo-header checksum expected by the drivers is not the same. For instance, when TSO is enabled, the IP payload length must not be included in the packet.
 When ol_flags is 0, it computes the standard pseudo-header checksum.
 
in param ipv4_hdr
   The pointer to the contiguous IPv4 header. 
in param ol_flags
   The ol_flags of the associated mbuf. 
return
   The non-complemented checksum to set in the L4 header.*/
uint16_t  deepeedeekay_rte_ipv4_phdr_cksum(const struct rte_ipv4_hdr * ipv4_hdr, uint64_t ol_flags);
/**
 Process the IPv4 UDP or TCP checksum.
 The layer 4 checksum must be set to 0 in the L4 header by the caller.
 
in param ipv4_hdr
   The pointer to the contiguous IPv4 header. 
in param l4_hdr
   The pointer to the beginning of the L4 header. 
return
   The complemented checksum to set in the L4 header.*/
uint16_t  deepeedeekay_rte_ipv4_udptcp_cksum(const struct rte_ipv4_hdr * ipv4_hdr, const void * l4_hdr);
/**
 Compute the IPv4 UDP/TCP checksum of a packet.
 
in param m
   The pointer to the mbuf. 
in param ipv4_hdr
   The pointer to the contiguous IPv4 header. 
in param l4_off
   The offset in bytes to start L4 checksum. 
return
   The complemented checksum to set in the L4 header.*/
uint16_t  deepeedeekay_rte_ipv4_udptcp_cksum_mbuf(const struct rte_mbuf * m, const struct rte_ipv4_hdr * ipv4_hdr, uint16_t l4_off);
/**
 Validate the IPv4 UDP or TCP checksum.
 In case of UDP, the caller must first check if udp_hdr->dgram_cksum is 0 (i.e. no checksum).
 
in param ipv4_hdr
   The pointer to the contiguous IPv4 header. 
in param l4_hdr
   The pointer to the beginning of the L4 header. 
return
   Return 0 if the checksum is correct, else -1.*/
int  deepeedeekay_rte_ipv4_udptcp_cksum_verify(const struct rte_ipv4_hdr * ipv4_hdr, const void * l4_hdr);
/**
 Verify the IPv4 UDP/TCP checksum of a packet.
 In case of UDP, the caller must first check if udp_hdr->dgram_cksum is 0 (i.e. no checksum).
 
in param m
   The pointer to the mbuf. 
in param ipv4_hdr
   The pointer to the contiguous IPv4 header. 
in param l4_off
   The offset in bytes to start L4 checksum. 
return
   Return 0 if the checksum is correct, else -1.*/
int  deepeedeekay_rte_ipv4_udptcp_cksum_mbuf_verify(const struct rte_mbuf * m, const struct rte_ipv4_hdr * ipv4_hdr, uint16_t l4_off);
/**
 Check if two IPv6 Addresses are equal.
 
in param a
   The first address. 
in param b
   The second address. 
return
   true if both addresses are identical.*/
bool  deepeedeekay_rte_ipv6_addr_eq(const struct rte_ipv6_addr * a, const struct rte_ipv6_addr * b);
/**
 Mask an IPv6 address using the specified depth.
 Leave untouched one bit per unit in the depth variable and set the rest to 0.
 
in param ip
   The address to mask. 
out param depth
   All bits starting from this bit number will be set to zero.*/
void  deepeedeekay_rte_ipv6_addr_mask(struct rte_ipv6_addr * ip, uint8_t depth);
/**
 Check if two IPv6 addresses belong to the same network prefix.
 
in param a
  The first address or network. 
in param b
  The second address or network. 
in param depth
  The network prefix length. 
return
    if the first  bits of both addresses are identical.*/
bool  deepeedeekay_rte_ipv6_addr_eq_prefix(const struct rte_ipv6_addr * a, const struct rte_ipv6_addr * b, uint8_t depth);
/**
 Get the depth of a given IPv6 address mask.
 
in param mask
   The address mask. 
return
   The number of consecutive bits set to 1 starting from the beginning of the mask.*/
uint8_t  deepeedeekay_rte_ipv6_mask_depth(const struct rte_ipv6_addr * mask);
/**
 Check if an IPv6 address is unspecified as defined in RFC 4291, section 2.5.2.
 
in param ip
   The address to check. 
return
    if the address is the unspecified address (all zeroes).*/
bool  deepeedeekay_rte_ipv6_addr_is_unspec(const struct rte_ipv6_addr * ip);
/**
 Check if an IPv6 address is the loopback address as defined in RFC 4291, section 2.5.3.
 
in param ip
   The address to check. 
return
    if the address is the loopback address (all zeroes except the last bit).*/
bool  deepeedeekay_rte_ipv6_addr_is_loopback(const struct rte_ipv6_addr * ip);
/**
 Check if an IPv6 address is link-local as defined in RFC 4291, section 2.5.6.
 
in param ip
   The address to check. 
return
    if the address is a link-local address.*/
bool  deepeedeekay_rte_ipv6_addr_is_linklocal(const struct rte_ipv6_addr * ip);
/**
 Check if an IPv6 address is site-local as defined in RFC 4291, section 2.5.7.
 
in param ip
   The address to check. 
return
    if the address is a site-local address.*/
bool  deepeedeekay_rte_ipv6_addr_is_sitelocal(const struct rte_ipv6_addr * ip);
/**
 Check if an IPv6 address is an IPv4-compatible address as defined in RFC 4291, section 2.5.5.1.
 
in param ip
   The address to check. 
return
    if the address is an IPv4-compatible address.*/
bool  deepeedeekay_rte_ipv6_addr_is_v4compat(const struct rte_ipv6_addr * ip);
/**
 Check if an IPv6 address is an IPv4-mapped address as defined in RFC 4291, section 2.5.5.2.
 
in param ip
   The address to check. 
return
    if the address is an IPv4-mapped address.*/
bool  deepeedeekay_rte_ipv6_addr_is_v4mapped(const struct rte_ipv6_addr * ip);
/**
 Check if an IPv6 address is multicast as defined in RFC 4291, section 2.7.
 
in param ip
   The address to check. 
return
    if the address is multicast.*/
bool  deepeedeekay_rte_ipv6_addr_is_mcast(const struct rte_ipv6_addr * ip);
/**
 Extract the IPv6 multicast scope value as defined in RFC 4291, section 2.7.
 
in param ip
   The address from which to get the multicast scope. 
return
   The multicast scope of the address, or #RTE_IPV6_MC_SCOPE_NONE if the   address is not multicast.*/
enum rte_ipv6_mc_scope  deepeedeekay_rte_ipv6_mc_scope(const struct rte_ipv6_addr * ip);
/***/
void  deepeedeekay_rte_ipv6_llocal_from_ethernet(struct rte_ipv6_addr * ip, const struct rte_ether_addr * mac);
/**
 Convert a unicast or anycast IPv6 address to a solicited-node multicast address as defined in RFC 4291, section 2.7.1.
 
out param sol
   The IPv6 solicited-node multicast address to generate. 
in param ip
   A unicast or anycast address.*/
void  deepeedeekay_rte_ipv6_solnode_from_addr(struct rte_ipv6_addr * sol, const struct rte_ipv6_addr * ip);
/**
 Generate a multicast Ethernet address from a multicast IPv6 address as defined in RFC 2464, section 7.
 
out param mac
   The multicast Ethernet address to generate. 
in param ip
   A multicast IPv6 address.*/
void  deepeedeekay_rte_ether_mcast_from_ipv6(struct rte_ether_addr * mac, const struct rte_ipv6_addr * ip);
/**
 Check that the IPv6 header version field is valid according to RFC 8200 section 3.
 
in param ip
   The IPv6 header. 
return
    if the version field is valid.  otherwise.*/
int  deepeedeekay_rte_ipv6_check_version(const struct rte_ipv6_hdr * ip);
/**
 Process the pseudo-header checksum of an IPv6 header.
 Depending on the ol_flags, the pseudo-header checksum expected by the drivers is not the same. For instance, when TSO is enabled, the IPv6 payload length must not be included in the packet.
 When ol_flags is 0, it computes the standard pseudo-header checksum.
 
in param ipv6_hdr
   The pointer to the contiguous IPv6 header. 
in param ol_flags
   The ol_flags of the associated mbuf. 
return
   The non-complemented checksum to set in the L4 header.*/
uint16_t  deepeedeekay_rte_ipv6_phdr_cksum(const struct rte_ipv6_hdr * ipv6_hdr, uint64_t ol_flags);
/**
 Process the IPv6 UDP or TCP checksum.
 The IPv6 header must not be followed by extension headers. The layer 4 checksum must be set to 0 in the L4 header by the caller.
 
in param ipv6_hdr
   The pointer to the contiguous IPv6 header. 
in param l4_hdr
   The pointer to the beginning of the L4 header. 
return
   The complemented checksum to set in the L4 header.*/
uint16_t  deepeedeekay_rte_ipv6_udptcp_cksum(const struct rte_ipv6_hdr * ipv6_hdr, const void * l4_hdr);
/**
 Process the IPv6 UDP or TCP checksum of a packet.
 The IPv6 header must not be followed by extension headers. The layer 4 checksum must be set to 0 in the L4 header by the caller.
 
in param m
   The pointer to the mbuf. 
in param ipv6_hdr
   The pointer to the contiguous IPv6 header. 
in param l4_off
   The offset in bytes to start L4 checksum. 
return
   The complemented checksum to set in the L4 header.*/
uint16_t  deepeedeekay_rte_ipv6_udptcp_cksum_mbuf(const struct rte_mbuf * m, const struct rte_ipv6_hdr * ipv6_hdr, uint16_t l4_off);
/**
 Validate the IPv6 UDP or TCP checksum.
 In case of UDP, the caller must first check if udp_hdr->dgram_cksum is 0: this is either invalid or means no checksum in some situations. See 8.1 (Upper-Layer Checksums) in RFC 8200.
 
in param ipv6_hdr
   The pointer to the contiguous IPv6 header. 
in param l4_hdr
   The pointer to the beginning of the L4 header. 
return
   Return 0 if the checksum is correct, else -1.*/
int  deepeedeekay_rte_ipv6_udptcp_cksum_verify(const struct rte_ipv6_hdr * ipv6_hdr, const void * l4_hdr);
/**
 Validate the IPv6 UDP or TCP checksum of a packet.
 In case of UDP, the caller must first check if udp_hdr->dgram_cksum is 0: this is either invalid or means no checksum in some situations. See 8.1 (Upper-Layer Checksums) in RFC 8200.
 
in param m
   The pointer to the mbuf. 
in param ipv6_hdr
   The pointer to the contiguous IPv6 header. 
in param l4_off
   The offset in bytes to start L4 checksum. 
return
   Return 0 if the checksum is correct, else -1.*/
int  deepeedeekay_rte_ipv6_udptcp_cksum_mbuf_verify(const struct rte_mbuf * m, const struct rte_ipv6_hdr * ipv6_hdr, uint16_t l4_off);
/**
 Parse next IPv6 header extension
 This function checks if proto number is an IPv6 extensions and parses its data if so, providing information on next header and extension length.
 
in param p
   Pointer to an extension raw data. 
in param proto
   Protocol number extracted from the "next header" field from   the IPv6 header or the previous extension. 
in param ext_len
   Extension data length. 
return
   next protocol number if proto is an IPv6 extension, -EINVAL otherwise*/
int  deepeedeekay_rte_ipv6_get_next_ext(const uint8_t * p, int proto, size_t * ext_len);
/**
 srTCM color blind traffic metering
 
in param m
    Handle to srTCM instance 
in param p
    srTCM profile specified at srTCM object creation time 
in param time
    Current CPU time stamp (measured in CPU cycles) 
in param pkt_len
    Length of the current IP packet (measured in bytes) 
return
    Color assigned to the current IP packet*/
enum rte_color  deepeedeekay_rte_meter_srtcm_color_blind_check(struct rte_meter_srtcm * m, struct rte_meter_srtcm_profile * p, uint64_t time, uint32_t pkt_len);
/**
 srTCM color aware traffic metering
 
in param m
    Handle to srTCM instance 
in param p
    srTCM profile specified at srTCM object creation time 
in param time
    Current CPU time stamp (measured in CPU cycles) 
in param pkt_len
    Length of the current IP packet (measured in bytes) 
in param pkt_color
    Input color of the current IP packet 
return
    Color assigned to the current IP packet*/
enum rte_color  deepeedeekay_rte_meter_srtcm_color_aware_check(struct rte_meter_srtcm * m, struct rte_meter_srtcm_profile * p, uint64_t time, uint32_t pkt_len, enum rte_color pkt_color);
/**
 trTCM color blind traffic metering
 
in param m
    Handle to trTCM instance 
in param p
    trTCM profile specified at trTCM object creation time 
in param time
    Current CPU time stamp (measured in CPU cycles) 
in param pkt_len
    Length of the current IP packet (measured in bytes) 
return
    Color assigned to the current IP packet*/
enum rte_color  deepeedeekay_rte_meter_trtcm_color_blind_check(struct rte_meter_trtcm * m, struct rte_meter_trtcm_profile * p, uint64_t time, uint32_t pkt_len);
/**
 trTCM color aware traffic metering
 
in param m
    Handle to trTCM instance 
in param p
    trTCM profile specified at trTCM object creation time 
in param time
    Current CPU time stamp (measured in CPU cycles) 
in param pkt_len
    Length of the current IP packet (measured in bytes) 
in param pkt_color
    Input color of the current IP packet 
return
    Color assigned to the current IP packet*/
enum rte_color  deepeedeekay_rte_meter_trtcm_color_aware_check(struct rte_meter_trtcm * m, struct rte_meter_trtcm_profile * p, uint64_t time, uint32_t pkt_len, enum rte_color pkt_color);
/**
 trTCM RFC4115 color blind traffic metering
 
in param m
    Handle to trTCM instance 
in param p
    trTCM profile specified at trTCM object creation time 
in param time
    Current CPU time stamp (measured in CPU cycles) 
in param pkt_len
    Length of the current IP packet (measured in bytes) 
return
    Color assigned to the current IP packet*/
enum rte_color  deepeedeekay_rte_meter_trtcm_rfc4115_color_blind_check(struct rte_meter_trtcm_rfc4115 * m, struct rte_meter_trtcm_rfc4115_profile * p, uint64_t time, uint32_t pkt_len);
/**
 trTCM RFC4115 color aware traffic metering
 
in param m
    Handle to trTCM instance 
in param p
    trTCM profile specified at trTCM object creation time 
in param time
    Current CPU time stamp (measured in CPU cycles) 
in param pkt_len
    Length of the current IP packet (measured in bytes) 
in param pkt_color
    Input color of the current IP packet 
return
    Color assigned to the current IP packet*/
enum rte_color  deepeedeekay_rte_meter_trtcm_rfc4115_color_aware_check(struct rte_meter_trtcm_rfc4115 * m, struct rte_meter_trtcm_rfc4115_profile * p, uint64_t time, uint32_t pkt_len, enum rte_color pkt_color);
/***/
uint32_t  deepeedeekay_rte_flow_dynf_metadata_get(struct rte_mbuf * m);
/***/
void  deepeedeekay_rte_flow_dynf_metadata_set(struct rte_mbuf * m, uint32_t v);
/**
 Check if mbuf dynamic field for metadata is registered.
 
return
   True if registered, false otherwise.*/
int  deepeedeekay_rte_flow_dynf_metadata_avail();
/**
 Retrieve a burst of input packets from a receive queue of an Ethernet device. The retrieved packets are stored in *rte_mbuf* structures whose pointers are supplied in the *rx_pkts* array.
 The rte_eth_rx_burst() function loops, parsing the Rx ring of the receive queue, up to *nb_pkts* packets, and for each completed Rx descriptor in the ring, it performs the following operations:
 - Initialize the *rte_mbuf* data structure associated with the   Rx descriptor according to the information provided by the NIC into   that Rx descriptor.
 - Store the *rte_mbuf* data structure into the next entry of the   *rx_pkts* array.
 - Replenish the Rx descriptor with a new *rte_mbuf* buffer   allocated from the memory pool associated with the receive queue at   initialization time.
 When retrieving an input packet that was scattered by the controller into multiple receive descriptors, the rte_eth_rx_burst() function appends the associated *rte_mbuf* buffers to the first buffer of the packet.
 The rte_eth_rx_burst() function returns the number of packets actually retrieved, which is the number of *rte_mbuf* data structures effectively supplied into the *rx_pkts* array. A return value equal to *nb_pkts* indicates that the Rx queue contained at least *rx_pkts* packets, and this is likely to signify that other received packets remain in the input queue. Applications implementing a "retrieve as much received packets as possible" policy can check this specific case and keep invoking the rte_eth_rx_burst() function until a value less than *nb_pkts* is returned.
 This receive method has the following advantages:
 - It allows a run-to-completion network stack engine to retrieve and   to immediately process received packets in a fast burst-oriented   approach, avoiding the overhead of unnecessary intermediate packet   queue/dequeue operations.
 - Conversely, it also allows an asynchronous-oriented processing   method to retrieve bursts of received packets and to immediately   queue them for further parallel processing by another logical core,   for instance. However, instead of having received packets being   individually queued by the driver, this approach allows the caller   of the rte_eth_rx_burst() function to queue a burst of retrieved   packets at a time and therefore dramatically reduce the cost of   enqueue/dequeue operations per packet.
 - It allows the rte_eth_rx_burst() function of the driver to take   advantage of burst-oriented hardware features (CPU cache,   prefetch instructions, and so on) to minimize the number of CPU   cycles per packet.
 To summarize, the proposed receive API enables many burst-oriented optimizations in both synchronous and asynchronous packet processing environments with no overhead in both cases.
 
note
   Some drivers using vector instructions require that *nb_pkts* is   divisible by 4 or 8, depending on the driver implementation.
 The rte_eth_rx_burst() function does not provide any error notification to avoid the corresponding overhead. As a hint, the upper-level application might check the status of the device link once being systematically returned a 0 value for a given number of tries.
 
in param port_id
   The port identifier of the Ethernet device. 
in param queue_id
   The index of the receive queue from which to retrieve input packets.   The value must be in the range [0, nb_rx_queue - 1] previously supplied   to rte_eth_dev_configure(). 
in param rx_pkts
   The address of an array of pointers to *rte_mbuf* structures that   must be large enough to store *nb_pkts* pointers in it. 
in param nb_pkts
   The maximum number of packets to retrieve.   The value must be divisible by 8 in order to work with any driver. 
return
   The number of packets actually retrieved, which is the number   of pointers to *rte_mbuf* structures effectively supplied to the   *rx_pkts* array.*/
uint16_t  deepeedeekay_rte_eth_rx_burst(uint16_t port_id, uint16_t queue_id, struct rte_mbuf ** rx_pkts, const uint16_t nb_pkts);
/**
 Get the number of used descriptors of a Rx queue
 Since it's a dataplane function, no check is performed on port_id and queue_id. The caller must therefore ensure that the port is enabled and the queue is configured and running.
 
in param port_id
  The port identifier of the Ethernet device. 
in param queue_id
  The queue ID on the specific port. 
return
  The number of used descriptors in the specific queue, or:   - (-ENODEV) if *port_id* is invalid.   - (-EINVAL) if *queue_id* is invalid   - (-ENOTSUP) if the device does not support this function*/
int  deepeedeekay_rte_eth_rx_queue_count(uint16_t port_id, uint16_t queue_id);
/**
 Check the status of a Rx descriptor in the queue
 It should be called in a similar context than the Rx function: - on a dataplane core - not concurrently on the same queue
 Since it's a dataplane function, no check is performed on port_id and queue_id. The caller must therefore ensure that the port is enabled and the queue is configured and running.
 Note: accessing to a random descriptor in the ring may trigger cache misses and have a performance impact.
 
in param port_id
  A valid port identifier of the Ethernet device which. 
in param queue_id
  A valid Rx queue identifier on this port. 
in param offset
  The offset of the descriptor starting from tail (0 is the next  packet to be received by the driver).
 
return
  - (RTE_ETH_RX_DESC_AVAIL): Descriptor is available for the hardware to    receive a packet.  - (RTE_ETH_RX_DESC_DONE): Descriptor is done, it is filled by hw, but    not yet processed by the driver (i.e. in the receive queue).  - (RTE_ETH_RX_DESC_UNAVAIL): Descriptor is unavailable, either hold by    the driver and not yet returned to hw, or reserved by the hw.  - (-EINVAL) bad descriptor offset.  - (-ENOTSUP) if the device does not support this function.  - (-ENODEV) bad port or queue (only if compiled with debug).*/
int  deepeedeekay_rte_eth_rx_descriptor_status(uint16_t port_id, uint16_t queue_id, uint16_t offset);
/**
 Check the status of a Tx descriptor in the queue.
 It should be called in a similar context than the Tx function: - on a dataplane core - not concurrently on the same queue
 Since it's a dataplane function, no check is performed on port_id and queue_id. The caller must therefore ensure that the port is enabled and the queue is configured and running.
 Note: accessing to a random descriptor in the ring may trigger cache misses and have a performance impact.
 
in param port_id
  A valid port identifier of the Ethernet device which. 
in param queue_id
  A valid Tx queue identifier on this port. 
in param offset
  The offset of the descriptor starting from tail (0 is the place where  the next packet will be send).
 
return
  - (RTE_ETH_TX_DESC_FULL) Descriptor is being processed by the hw, i.e.    in the transmit queue.  - (RTE_ETH_TX_DESC_DONE) Hardware is done with this descriptor, it can    be reused by the driver.  - (RTE_ETH_TX_DESC_UNAVAIL): Descriptor is unavailable, reserved by the    driver or the hardware.  - (-EINVAL) bad descriptor offset.  - (-ENOTSUP) if the device does not support this function.  - (-ENODEV) bad port or queue (only if compiled with debug).*/
int  deepeedeekay_rte_eth_tx_descriptor_status(uint16_t port_id, uint16_t queue_id, uint16_t offset);
/**
 Send a burst of output packets on a transmit queue of an Ethernet device.
 The rte_eth_tx_burst() function is invoked to transmit output packets on the output queue *queue_id* of the Ethernet device designated by its *port_id*. The *nb_pkts* parameter is the number of packets to send which are supplied in the *tx_pkts* array of *rte_mbuf* structures, each of them allocated from a pool created with rte_pktmbuf_pool_create(). The rte_eth_tx_burst() function loops, sending *nb_pkts* packets, up to the number of transmit descriptors available in the Tx ring of the transmit queue. For each packet to send, the rte_eth_tx_burst() function performs the following operations:
 - Pick up the next available descriptor in the transmit ring.
 - Free the network buffer previously sent with that descriptor, if any.
 - Initialize the transmit descriptor with the information provided   in the *rte_mbuf data structure.
 In the case of a segmented packet composed of a list of *rte_mbuf* buffers, the rte_eth_tx_burst() function uses several transmit descriptors of the ring.
 The rte_eth_tx_burst() function returns the number of packets it actually sent. A return value equal to *nb_pkts* means that all packets have been sent, and this is likely to signify that other output packets could be immediately transmitted again. Applications that implement a "send as many packets to transmit as possible" policy can check this specific case and keep invoking the rte_eth_tx_burst() function until a value less than *nb_pkts* is returned.
 It is the responsibility of the rte_eth_tx_burst() function to transparently free the memory buffers of packets previously sent. This feature is driven by the *tx_free_thresh* value supplied to the rte_eth_dev_configure() function at device configuration time. When the number of free Tx descriptors drops below this threshold, the rte_eth_tx_burst() function must [attempt to] free the *rte_mbuf*  buffers of those packets whose transmission was effectively completed.
 If the PMD is RTE_ETH_TX_OFFLOAD_MT_LOCKFREE capable, multiple threads can invoke this function concurrently on the same Tx queue without SW lock. 
see
 rte_eth_dev_info_get, struct rte_eth_txconf::offloads
 
see
 rte_eth_tx_prepare to perform some prior checks or adjustments for offloads.
 
note
 This function must not modify mbufs (including packets data) unless the refcnt is 1. An exception is the bonding PMD, which does not have "Tx prepare" support, in this case, mbufs may be modified.
 
in param port_id
   The port identifier of the Ethernet device. 
in param queue_id
   The index of the transmit queue through which output packets must be   sent.   The value must be in the range [0, nb_tx_queue - 1] previously supplied   to rte_eth_dev_configure(). 
in param tx_pkts
   The address of an array of *nb_pkts* pointers to *rte_mbuf* structures   which contain the output packets. 
in param nb_pkts
   The maximum number of packets to transmit. 
return
   The number of output packets actually stored in transmit descriptors of   the transmit ring. The return value can be less than the value of the   *tx_pkts* parameter when the transmit ring is full or has been filled up.*/
uint16_t  deepeedeekay_rte_eth_tx_burst(uint16_t port_id, uint16_t queue_id, struct rte_mbuf ** tx_pkts, uint16_t nb_pkts);
/***/
uint16_t  deepeedeekay_rte_eth_tx_prepare(uint16_t port_id, uint16_t queue_id, struct rte_mbuf ** tx_pkts, uint16_t nb_pkts);
/**
 Send any packets queued up for transmission on a port and HW queue
 This causes an explicit flush of packets previously buffered via the rte_eth_tx_buffer() function. It returns the number of packets successfully sent to the NIC, and calls the error callback for any unsent packets. Unless explicitly set up otherwise, the default callback simply frees the unsent packets back to the owning mempool.
 
in param port_id
   The port identifier of the Ethernet device. 
in param queue_id
   The index of the transmit queue through which output packets must be   sent.   The value must be in the range [0, nb_tx_queue - 1] previously supplied   to rte_eth_dev_configure(). 
in param buffer
   Buffer of packets to be transmit. 
return
   The number of packets successfully sent to the Ethernet device. The error   callback is called for any packets which could not be sent.*/
uint16_t  deepeedeekay_rte_eth_tx_buffer_flush(uint16_t port_id, uint16_t queue_id, struct rte_eth_dev_tx_buffer * buffer);
/**
 Buffer a single packet for future transmission on a port and queue
 This function takes a single mbuf/packet and buffers it for later transmission on the particular port and queue specified. Once the buffer is full of packets, an attempt will be made to transmit all the buffered packets. In case of error, where not all packets can be transmitted, a callback is called with the unsent packets as a parameter. If no callback is explicitly set up, the unsent packets are just freed back to the owning mempool. The function returns the number of packets actually sent i.e. 0 if no buffer flush occurred, otherwise the number of packets successfully flushed
 
in param port_id
   The port identifier of the Ethernet device. 
in param queue_id
   The index of the transmit queue through which output packets must be   sent.   The value must be in the range [0, nb_tx_queue - 1] previously supplied   to rte_eth_dev_configure(). 
in param buffer
   Buffer used to collect packets to be sent. 
in param tx_pkt
   Pointer to the packet mbuf to be sent. 
return
   0 = packet has been buffered for later transmission   N > 0 = packet has been buffered, and the buffer was subsequently flushed,     causing N packets to be sent, and the error callback to be called for     the rest.*/
uint16_t  deepeedeekay_rte_eth_tx_buffer(uint16_t port_id, uint16_t queue_id, struct rte_eth_dev_tx_buffer * buffer, struct rte_mbuf * tx_pkt);
/**
 
warning
  this API may change, or be removed, without prior notice
 Recycle used mbufs from a transmit queue of an Ethernet device, and move these mbufs into a mbuf ring for a receive queue of an Ethernet device. This can bypass mempool path to save CPU cycles.
 The rte_eth_recycle_mbufs() function loops, with rte_eth_rx_burst() and rte_eth_tx_burst() functions, freeing Tx used mbufs and replenishing Rx descriptors. The number of recycling mbufs depends on the request of Rx mbuf ring, with the constraint of enough used mbufs from Tx mbuf ring.
 For each recycling mbufs, the rte_eth_recycle_mbufs() function performs the following operations:
 - Copy used *rte_mbuf* buffer pointers from Tx mbuf ring into Rx mbuf ring.
 - Replenish the Rx descriptors with the recycling *rte_mbuf* mbufs freed   from the Tx mbuf ring.
 This function spilts Rx and Tx path with different callback functions. The callback function recycle_tx_mbufs_reuse is for Tx driver. The callback function recycle_rx_descriptors_refill is for Rx driver. rte_eth_recycle_mbufs() can support the case that Rx Ethernet device is different from Tx Ethernet device.
 It is the responsibility of users to select the Rx/Tx queue pair to recycle mbufs. Before call this function, users must call rte_eth_recycle_rxq_info_get function to retrieve selected Rx queue information. 
see
 rte_eth_recycle_rxq_info_get, struct rte_eth_recycle_rxq_info
 Currently, the rte_eth_recycle_mbufs() function can support to feed 1 Rx queue from 2 Tx queues in the same thread. Do not pair the Rx queue and Tx queue in different threads, in order to avoid memory error rewriting.
 
in param rx_port_id
   Port identifying the receive side. 
in param rx_queue_id
   The index of the receive queue identifying the receive side.   The value must be in the range [0, nb_rx_queue - 1] previously supplied   to rte_eth_dev_configure(). 
in param tx_port_id
   Port identifying the transmit side. 
in param tx_queue_id
   The index of the transmit queue identifying the transmit side.   The value must be in the range [0, nb_tx_queue - 1] previously supplied   to rte_eth_dev_configure(). 
in param recycle_rxq_info
   A pointer to a structure of type *rte_eth_recycle_rxq_info* which contains   the information of the Rx queue mbuf ring. 
return
   The number of recycling mbufs.*/
uint16_t  deepeedeekay_rte_eth_recycle_mbufs(uint16_t rx_port_id, uint16_t rx_queue_id, uint16_t tx_port_id, uint16_t tx_queue_id, struct rte_eth_recycle_rxq_info * recycle_rxq_info);
/**
 
warning
  this API may change, or be removed, without prior notice.
 Get the number of used descriptors of a Tx queue.
 This function retrieves the number of used descriptors of a transmit queue. Applications can use this API in the fast path to inspect Tx queue occupancy and take appropriate actions based on the available free descriptors. An example action could be implementing Random Early Discard (RED).
 Since it's a fast-path function, no check is performed on port_id and queue_id. The caller must therefore ensure that the port is enabled and the queue is configured and running.
 
in param port_id
   The port identifier of the device. 
in param queue_id
   The index of the transmit queue.   The value must be in the range [0, nb_tx_queue - 1]   previously supplied to rte_eth_dev_configure(). 
return
   The number of used descriptors in the specific queue, or:   - (-ENODEV) if *port_id* is invalid. Enabled only when RTE_ETHDEV_DEBUG_TX is enabled.   - (-EINVAL) if *queue_id* is invalid. Enabled only when RTE_ETHDEV_DEBUG_TX is enabled.   - (-ENOTSUP) if the device does not support this function.
 
note
 This function is designed for fast-path use. 
note
 There is no requirement to call this function before rte_eth_tx_burst() invocation. 
note
 Utilize this function exclusively when the caller needs to determine the used queue count across all descriptors of a Tx queue. If the use case only involves checking the status of a specific descriptor slot, opt for rte_eth_tx_descriptor_status() instead.*/
int  deepeedeekay_rte_eth_tx_queue_count(uint16_t port_id, uint16_t queue_id);