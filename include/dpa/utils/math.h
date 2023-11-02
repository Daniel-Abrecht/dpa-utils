#ifndef DPA_U_MATH_H
#define DPA_U_MATH_H

#include <dpa/utils/common.h>
#include <stdbool.h>

dpa_u_unsequenced DPA_U_EXPORT inline int dpa_u_log2(long long unsigned int x){
#if DPA__U__has_builtin(__builtin_clzll)
  return 63 - __builtin_clzll(x);
#else
  int i = 0;
  while (x >>= 1) i++;
  return i;
#endif
}

dpa_u_unsequenced DPA_U_EXPORT inline int dpa_u_ctzll(long long unsigned int x){
#if DPA__U__has_builtin(__builtin_ctzll)
  return __builtin_ctzll(x);
#else
  int i = 0;
  for(; i<64 && !(1&x); i++)
    x >>= 1;
  return i;
#endif
}


dpa_u_unsequenced DPA_U_EXPORT inline bool dpa_u_rbit_less_than_unsigned(long long unsigned x, long long unsigned y){
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

dpa_u_unsequenced dpa__u_really_inline DPA_U_EXPORT inline bool dpa_u_sign(long long x){
  return (x > 0) - (x < 0);
}

#endif
