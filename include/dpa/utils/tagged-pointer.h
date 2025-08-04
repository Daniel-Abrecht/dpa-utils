#ifndef DPA_U_TAGGED_POINTER_H
#define DPA_U_TAGGED_POINTER_H

#include <dpa/utils/common.h>
#include <dpa/utils/endian.h>
#include <stdint.h>

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-tag Tagged Pointer
 * The first byte is used as the tag. This may not be ideal for all use-cases.
 * @{
 */


#if DPA_U_BYTE_ORDER == DPA_U_ENDIAN_LITTLE
/**
 * \param X a pointer
 * \param T a tag
 * \returns the tagged pointer, as a uint64_t. If cast to a char, the first byte is the tag.
 */
#define DPA_U_TAG(X, T) (((uint64_t)(uintptr_t)(X)<<8) | (T))
/**
 * \param X a tagged pointer
 * \returns the original, untagged, pointer
 */
#define DPA_U_UNTAG(X) ((void*)(uintptr_t)((X)>>8))
/**
 * \param X a tagged pointer
 * \returns the tag
 */
#define DPA_U_GET_TAG(X) ((X) & 0xFF)
/**
 * \param X a tag
 * \returns Moves the tag such that it can be and-ed or or-ed with a tagged pointer
 */
#define DPA_U_MOVE_TAG(X) ((uint64_t)(X))
#elif DPA_U_BYTE_ORDER == DPA_U_ENDIAN_BIG
#define DPA_U_TAG(X, T) (((uint64_t)(uintptr_t)(X)) | ((T)<<56))
#define DPA_U_UNTAG(X) ((void*)(uintptr_t)((X) & 0x00FFFFFFFFFFFFFFu))
#define DPA_U_GET_TAG(X) ((X) >> 56)
#define DPA_U_MOVE_TAG(X) ((uint64_t)(X) << 56)
#else
#error "Unknown endianess"
#endif

/** @} */
/** @} */

#endif
