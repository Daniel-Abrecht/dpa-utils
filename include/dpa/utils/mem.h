#ifndef DPA_UTILS_MEM_H
#define DPA_UTILS_MEM_H

#include <dpa/utils/refcount.h>
#include <stdalign.h>
#include <stddef.h>

typedef struct dpa_u_refcount_freeable_data dpa_u_refcount_freeable_data_t;

struct dpa_u_refcount_freeable_data {
  struct dpa_u_refcount_freeable refcount;
  alignas(dpa__u_max_align_t) char data[];
};

dpa__u_api struct dpa_u_refcount_freeable_data* dpa_u_refcount_freeable_allocate(size_t size, uint_least64_t iref);
dpa__u_api struct dpa_u_refcount_freeable_data* dpa_u_refcount_freeable_copy(void*restrict data, size_t size, uint_least64_t iref);

#endif
