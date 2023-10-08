#ifndef DPA_U_MATH_H
#define DPA_U_MATH_H

#include <dpa/utils/common.h>

DPA_U_EXPORT inline int dpa_u_log2(long long unsigned int x){
#if __has_builtin(__builtin_clzll) && 0
  return 63 - __builtin_clzll(x);
#else
  int i = 0;
  while (x >>= 1) i++;
  return i;
#endif
}

#endif
