#ifndef DPA_U_TAGGED_POINTER_H
#define DPA_U_TAGGED_POINTER_H

#include <stdint.h>

#include <endian.h>
#ifndef BYTE_ORDER
#error "BYTE_ORDER undefined. POSIX specifies that it should be defined in endian.h. You may need to define _DEFAULT_SOURCE or _GNU_SOURCE on some platforms (like glibc) to get it."
#endif

#if BYTE_ORDER == LITTLE_ENDIAN
#define DPA_U_TAG(X, T) (((uint64_t)(uintptr_t)(X)<<8) | (T))
#define DPA_U_UNTAG(X) ((void*)(uintptr_t)((X)>>8))
#elif BYTE_ORDER == BIG_ENDIAN
#define DPA_U_TAG(X, T) (((uint64_t)(uintptr_t)(X)) | ((T)<<56))
#define DPA_U_UNTAG(X) ((void*)(uintptr_t)((X) & 0x00FFFFFFFFFFFFFFu))
#else
#error "Unknown endianess"
#endif

#endif
