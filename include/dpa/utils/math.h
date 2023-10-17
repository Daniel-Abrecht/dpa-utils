#ifndef DPA_U_MATH_H
#define DPA_U_MATH_H

#include <dpa/utils/common.h>

DPA_U_EXPORT inline int dpa_u_log2(long long unsigned int x){
#if defined(__has_builtin) && __has_builtin(__builtin_clzll)
  return 63 - __builtin_clzll(x);
#else
  int i = 0;
  while (x >>= 1) i++;
  return i;
#endif
}

DPA_U_EXPORT inline int dpa_u_ctzll(long long unsigned int x){
#if defined(__has_builtin) && __has_builtin(__builtin_ctzll)
  return __builtin_ctzll(x);
#else
  int i = 0;
  for(; i<64 && !(1&x); i++)
    x >>= 1;
  return i;
#endif
}

#endif
