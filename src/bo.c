#include <dpa/utils/bo.h>

extern void* dpa__u_bo_data(dpa_u_bo_t*restrict const bo);
extern const void* dpa__u_cbo_data(const dpa_u_bo_t*restrict const bo);
extern const void* dpa__u_bo_ro_data(const dpa_u_bo_ro_t*restrict const bo);
extern const void* dpa__u_bo_unique_data(const dpa_u_bo_unique_t*restrict const bo);
extern void dpa__u_bo_set_size(dpa_u_bo_t*restrict const bo, size_t size);
extern size_t dpa__u_bo_get_size(const dpa_u_bo_t bo);
extern size_t dpa__u_bo_ro_get_size(const dpa_u_bo_ro_t bo);
extern size_t dpa__u_bo_unique_get_size(const dpa_u_bo_unique_t bo);
extern dpa_u_bo_unique_t dpa__u_bo_intern(const dpa_u_p_bo_ro_t*const _bo);
extern void dpa__u_bo_unique_ref(dpa_u_bo_unique_t ubo);
extern bool dpa__u_bo_unique_put(dpa_u_bo_unique_t ubo);
extern struct dpa_u_refcount_freeable* dpa__u_bo_unique_get_refcount(const dpa_u_bo_unique_t ubo);
extern struct dpa_u_refcount_freeable* dpa__u_bo_ro_p_get_refcount(const dpa_u_bo_ro_t* ubo);
extern struct dpa_u_refcount_freeable* dpa__u_bo_ro_get_refcount(const dpa_u_bo_ro_t ubo);

#undef DPA_U_BO_INLINE
#undef DPA_U_BO_SIMPLE
#undef DPA_U_BO_UNIQUE_HASHMAP

const char*const dpa_u_bo_type_s[] = { DPA_U_ENUM_STR(dpa_u_bo_type_list) };
