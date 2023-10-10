#include <dpa/utils/bo.h>

extern void* dpa__u_bo_data(dpa_u_bo_t*restrict const bo);
extern const void* dpa__u_cbo_data(const dpa_u_bo_t*restrict const bo);
extern const void* dpa__u_bo_ro_data(const dpa_u_bo_ro_t*restrict const bo);
extern const void* dpa__u_bo_unique_data(const dpa_u_bo_unique_t*restrict const bo);
extern void dpa__u_bo_set_size(dpa_u_bo_t*restrict const bo, size_t size);
extern size_t dpa__u_bo_get_size(const dpa_u_bo_t bo);
extern size_t dpa__u_bo_ro_get_size(const dpa_u_bo_ro_t bo);
extern size_t dpa__u_bo_unique_get_size(const dpa_u_bo_unique_t bo);
extern dpa_u_bo_unique_t dpa__u_bo_intern(const dpa_u_bo_ro_t bo);
extern void dpa__u_bo_unique_ref(dpa_u_bo_unique_t ubo);
extern bool dpa__u_bo_unique_put(dpa_u_bo_unique_t ubo);
