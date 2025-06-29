#ifndef DPA_UTILS_MEM_H
#define DPA_UTILS_MEM_H

#include <dpa/utils/common.h>
#include <dpa/utils/refcount.h>
#include <stdalign.h>
#include <stddef.h>
#include <string.h>

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-mem Memory Management
 * Some memory management related functions
 * @{
 */

/**
 * This datatype has a refcount, followed by aligned data.
 * It's useful for data which is to be freed when it's refcount hits 0.
 */
typedef struct dpa_u_refcount_freeable_data dpa_u_refcount_freeable_data_t;

/**
 * \copydoc dpa_u_refcount_freeable_data_t
 * \see dpa_u_refcount_freeable_data_t
 */
struct dpa_u_refcount_freeable_data {
  struct dpa_u_refcount_freeable refcount;
  alignas(max_align_t) char data[];
};

/**
 * Allocate some refcounted data.
 * 
 * \param size The size of the data
 * \param iref The initial value of the refcount
 */
dpa__u_api struct dpa_u_refcount_freeable_data* dpa_u_refcount_freeable_allocate(size_t size, uint_least64_t iref);

/**
 * Copy some data, and make the resulting data refcounted.
 * 
 * \param data The data to be copied
 * \param size The size of the data
 * \param iref The initial value of the refcount
 */
dpa__u_api struct dpa_u_refcount_freeable_data* dpa_u_refcount_freeable_copy(void*restrict data, size_t size, uint_least64_t iref);

dpa__u_api inline void* dpa_u_copy_p(const void* p, size_t s){
  void* r = malloc(s);
  if(!r) return 0;
  memcpy(r, p, s);
  return r;
}

#ifdef dpa_u_typeof
/**
 * Takes an object, and returns a copy of it.
 */
#define dpa_u_copy(...) ((dpa_u_typeof(__VA_ARGS__)*) dpa_u_copy_p(&(__VA_ARGS__), sizeof(__VA_ARGS__)))
#else
#define dpa_u_copy(...) ((void*) dpa_u_copy_p(&(__VA_ARGS__), sizeof(__VA_ARGS__)))
#endif

#ifdef dpa_u_typeof
/**
 * Allocate an object. It will be zeroed out.
 */
#define dpa_u_calloc(...) ((dpa_u_typeof(__VA_ARGS__)*)calloc(1, sizeof(__VA_ARGS__)))
#else
#define dpa_u_calloc(...) (calloc(1, sizeof(__VA_ARGS__)))
#endif

/** @} */
/** @} */

#endif
