#include <dpa/utils/bo.h>

extern void* dpa__u_bo_data(dpa_u_bo_t*restrict const);
extern const void* dpa__u_cbo_data(const dpa_u_bo_t*restrict const);
extern const void* dpa__u_bo_ro_data(const dpa_u_bo_ro_t*restrict const);
extern const void* dpa__u_bo_unique_data(const dpa_u_bo_unique_t*restrict const);
extern void dpa__u_bo_set_size(dpa_u_bo_t*restrict const bo, size_t size);
extern size_t dpa__u_bo_get_size(const dpa_u_bo_t);
extern size_t dpa__u_bo_ro_get_size(const dpa_u_bo_ro_t);
extern size_t dpa__u_bo_unique_get_size(const dpa_u_bo_unique_t);
extern dpa_u_bo_unique_t dpa__u_bo_intern(const dpa_u_p_bo_ro_t*const _bo);
extern void dpa__u_bo_unique_ref(dpa_u_bo_unique_t);
extern bool dpa__u_bo_unique_put(dpa_u_bo_unique_t);
extern struct dpa_u_refcount_freeable* dpa__u_bo_unique_get_refcount(const dpa_u_bo_unique_t);
extern struct dpa_u_refcount_freeable* dpa__u_bo_ro_p_get_refcount(const dpa_u_bo_ro_t*);
extern struct dpa_u_refcount_freeable* dpa__u_bo_ro_get_refcount(const dpa_u_bo_ro_t);
extern struct dpa_u_refcount_freeable* dpa__u_bo_p_get_refcount(const dpa_u_bo_t*);
extern int dpa__u_bo_compare_inline(const dpa_u_bo_inline_t, const dpa_u_bo_inline_t);
extern int dpa__u_bo_compare_unique(const dpa_u_bo_unique_t, const dpa_u_bo_unique_t);
extern int dpa__u_bo_compare_default(const dpa_u_bo_simple_ro_t, const dpa_u_bo_simple_ro_t);

#undef DPA_U_BO_INLINE
#undef DPA_U_BO_SIMPLE
#undef DPA_U_BO_UNIQUE_HASHMAP

const char*const dpa_u_bo_type_s[] = { DPA_U_ENUM_STR(dpa_u_bo_type_list) };
