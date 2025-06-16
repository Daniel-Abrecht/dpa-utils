#ifndef DPA_UTILS_MEM_H
#define DPA_UTILS_MEM_H

#include <dpa/utils/refcount.h>
#include <stdalign.h>
#include <stddef.h>
#include <string.h>

typedef struct dpa_u_refcount_freeable_data dpa_u_refcount_freeable_data_t;

struct dpa_u_refcount_freeable_data {
  struct dpa_u_refcount_freeable refcount;
  alignas(max_align_t) char data[];
};

dpa__u_api struct dpa_u_refcount_freeable_data* dpa_u_refcount_freeable_allocate(size_t size, uint_least64_t iref);
dpa__u_api struct dpa_u_refcount_freeable_data* dpa_u_refcount_freeable_copy(void*restrict data, size_t size, uint_least64_t iref);

dpa__u_api inline void* dpa_u_copy_p(const void* p, size_t s){
  void* r = malloc(s);
  if(!r) return 0;
  memcpy(r, p, s);
  return r;
}

#ifdef dpa_u_typeof
#define dpa_u_copy(...) ((dpa_u_typeof(__VA_ARGS__)*) dpa_u_copy_p(&(__VA_ARGS__), sizeof(__VA_ARGS__)))
#else
#define dpa_u_copy(...) ((void*) dpa_u_copy_p(&(__VA_ARGS__), sizeof(__VA_ARGS__)))
#endif

#ifdef dpa_u_typeof
#define dpa_u_calloc(T) ((typeof(T)*)calloc(1, sizeof(T)))
#else
// The following won't always work, but there is nothing that can be done about that
#define dpa_u_calloc(T) ((T*)calloc(1, sizeof(T)))
#endif

#endif
