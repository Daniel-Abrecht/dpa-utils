#ifndef DPA_U_MATH_H
#define DPA_U_MATH_H

#include <dpa/utils/common.h>
#include <stdbool.h>
#include <limits.h>

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-math Math functions
 * @{
 */

#define DPA_U_CONSTEXPR_LOG2(X) ( \
    (X)<=0x0000000000000001llu? 0: \
    (X)<=0x0000000000000002llu? 1: \
    (X)<=0x0000000000000004llu? 2: \
    (X)<=0x0000000000000008llu? 3: \
    (X)<=0x0000000000000010llu? 4: \
    (X)<=0x0000000000000020llu? 5: \
    (X)<=0x0000000000000040llu? 6: \
    (X)<=0x0000000000000080llu? 7: \
    (X)<=0x0000000000000100llu? 8: \
    (X)<=0x0000000000000200llu? 9: \
    (X)<=0x0000000000000400llu?10: \
    (X)<=0x0000000000000800llu?11: \
    (X)<=0x0000000000001000llu?12: \
    (X)<=0x0000000000002000llu?13: \
    (X)<=0x0000000000004000llu?14: \
    (X)<=0x0000000000008000llu?15: \
    (X)<=0x0000000000010000llu?16: \
    (X)<=0x0000000000020000llu?17: \
    (X)<=0x0000000000040000llu?18: \
    (X)<=0x0000000000080000llu?19: \
    (X)<=0x0000000000100000llu?20: \
    (X)<=0x0000000000200000llu?21: \
    (X)<=0x0000000000400000llu?22: \
    (X)<=0x0000000000800000llu?23: \
    (X)<=0x0000000001000000llu?24: \
    (X)<=0x0000000002000000llu?25: \
    (X)<=0x0000000004000000llu?26: \
    (X)<=0x0000000008000000llu?27: \
    (X)<=0x0000000010000000llu?28: \
    (X)<=0x0000000020000000llu?29: \
    (X)<=0x0000000040000000llu?30: \
    (X)<=0x0000000080000000llu?31: \
    (X)<=0x0000000100000000llu?32: \
    (X)<=0x0000000200000000llu?33: \
    (X)<=0x0000000400000000llu?34: \
    (X)<=0x0000000800000000llu?35: \
    (X)<=0x0000001000000000llu?36: \
    (X)<=0x0000002000000000llu?37: \
    (X)<=0x0000004000000000llu?38: \
    (X)<=0x0000008000000000llu?39: \
    (X)<=0x0000010000000000llu?40: \
    (X)<=0x0000020000000000llu?41: \
    (X)<=0x0000040000000000llu?42: \
    (X)<=0x0000080000000000llu?43: \
    (X)<=0x0000100000000000llu?44: \
    (X)<=0x0000200000000000llu?45: \
    (X)<=0x0000400000000000llu?46: \
    (X)<=0x0000800000000000llu?47: \
    (X)<=0x0001000000000000llu?48: \
    (X)<=0x0002000000000000llu?49: \
    (X)<=0x0004000000000000llu?50: \
    (X)<=0x0008000000000000llu?51: \
    (X)<=0x0010000000000000llu?52: \
    (X)<=0x0020000000000000llu?53: \
    (X)<=0x0040000000000000llu?54: \
    (X)<=0x0080000000000000llu?55: \
    (X)<=0x0100000000000000llu?56: \
    (X)<=0x0200000000000000llu?57: \
    (X)<=0x0400000000000000llu?58: \
    (X)<=0x0800000000000000llu?59: \
    (X)<=0x1000000000000000llu?60: \
    (X)<=0x2000000000000000llu?61: \
    (X)<=0x4000000000000000llu?62: \
    (X)<=0x8000000000000000llu?63: \
    64 \
  )

dpa_u_unsequenced dpa__u_api inline int dpa_u_log2(long long unsigned int x){
#if DPA__U__has_builtin(__builtin_clzll)
  return 63 - __builtin_clzll(x);
#else
  int i = 0;
  while (x >>= 1) i++;
  return i;
#endif
}

#if DPA__U__has_builtin(__builtin_ctzg)
#define dpa_u_ctzll __builtin_ctzg
#elif DPA__U__has_builtin(__builtin_ctzll)
#define dpa_u_ctzll __builtin_ctzll
#else
dpa_u_unsequenced dpa__u_api inline int dpa_u_ctzll(long long unsigned int x){
  int i = 0;
  for(; i<64 && !(1&x); i++)
    x >>= 1;
  return i;
}
#endif


dpa_u_unsequenced dpa__u_api inline bool dpa_u_rbit_less_than_unsigned(long long unsigned x, long long unsigned y){
#if DPA__U__has_builtin(__builtin_bitreverse64) && defined(__aarch64__)
  // Note: clang has __builtin_bitreverse64. gcc does not. And some archs have it, but the compiler won't use it.
  return (long long unsigned)__builtin_bitreverse64(x) < (long long unsigned)__builtin_bitreverse64(y);
#else
  x ^= y;
  if(!x) return 0;
  int i = dpa_u_ctzll(x);
  return y & (1llu<<i);
#endif
}

#if DPA__U__has_builtin(__builtin_popcountg)
#define dpa_u_count_bits __builtin_popcountg
#elif DPA__U__has_builtin(__builtin_popcountll)
#define dpa_u_count_bits __builtin_popcountll
#else
dpa_u_unsequenced dpa__u_api inline int dpa_u_count_bits(long long unsigned int x){
  int n = 0;
  for(unsigned i=0; i<sizeof(x)*CHAR_BIT; i++)
    if(x & (1llu<<i))
      n++;
  return n;
}
#endif

dpa_u_unsequenced dpa__u_really_inline dpa__u_api inline bool dpa_u_sign(long long x){
  return (x > 0) - (x < 0);
}

/** @} */
/** @} */

#endif
