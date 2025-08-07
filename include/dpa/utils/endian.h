#ifndef DPA_U_ENDIAN_H
#define DPA_U_ENDIAN_H

#include <dpa/utils/common.h>

#define DPA_U_ENDIAN_LITTLE 2
#define DPA_U_ENDIAN_BIG 3
#define DPA_U_ENDIAN_MIXED 4

#ifndef DPA_U_BYTE_ORDER

#if __STDC_VERSION__ >= 202311 && DPA__U__has_include(<stdbit.h>)

#include <stdbit.h>
#if __STDC_ENDIAN_NATIVE__ == __STDC_ENDIAN_LITTLE__
#define DPA_U_BYTE_ORDER DPA_U_ENDIAN_LITTLE
#elif __STDC_ENDIAN_NATIVE__ == __STDC_ENDIAN_BIG__
#define DPA_U_BYTE_ORDER DPA_U_ENDIAN_BIG
#else
#define DPA_U_BYTE_ORDER DPA_U_ENDIAN_MIXED
#endif

#else

#ifndef BYTE_ORDER
#include <endian.h>
#endif
#ifndef BYTE_ORDER
#error "BYTE_ORDER undefined. \
  POSIX specifies that it should be defined in endian.h. \
  You may need to define _DEFAULT_SOURCE or _GNU_SOURCE on some platforms (like glibc) to get it. \
  Alternatively, starting with C23, stdbit.h should contain __STDC_ENDIAN_NATIVE__"
#endif

#if BYTE_ORDER == LITTLE_ENDIAN
#define DPA_U_BYTE_ORDER DPA_U_ENDIAN_LITTLE
#elif BYTE_ORDER == BIG_ENDIAN
#define DPA_U_BYTE_ORDER DPA_U_ENDIAN_BIG
#else
#define DPA_U_BYTE_ORDER DPA_U_ENDIAN_MIXED
#endif

#endif

#endif

#endif
