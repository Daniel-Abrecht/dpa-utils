#include <dpa/utils/mem.h>
#include <string.h>

dpa__u_api struct dpa_u_refcount_freeable_data* dpa_u_refcount_freeable_allocate(size_t size, uint_least64_t iref){
  assert((iref & ~DPA__U_REFCOUNT_MASK) == 0);
  struct dpa_u_refcount_freeable_data* res = calloc(1, sizeof(struct dpa_u_refcount_freeable_data)+size);
  if(res) res->refcount = (dpa_u_refcount_freeable_t)dpa_u_refcount_i_freeable(iref);
  return res;
}

dpa__u_api struct dpa_u_refcount_freeable_data* dpa_u_refcount_freeable_copy(void*restrict data, size_t size, uint_least64_t iref){
  struct dpa_u_refcount_freeable_data* res = dpa_u_refcount_freeable_allocate(size, iref);
  if(res) memcpy(res->data, data, size);
  return res;
}
