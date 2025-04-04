#include <dpa/utils/bo.h>

extern dpa_u_bo_ro_t dpa__u_bo_to_bo_ro_h(dpa_u_bo_t bo);
extern dpa_u_bo_ro_t dpa_u_to_bo_ro_h(const dpa_u__boptr_t*restrict const boptr);
extern dpa_u_refcount_freeable_t* dpa_u_bo_get_refcount_h(dpa_u_a_bo_any_t bo);
extern dpa_u_refcount_freeable_t* dpa_u_bo_get_refcount_h1(dpa_u_a_bo_unique_t bo);
extern int dpa__u_bo_compare_h1(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b);
extern int dpa__u_bo_compare_h2(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b);
extern uint64_t dpa_u__bo_get_hash(dpa_u__boptr_t boptr);
extern uint64_t dpa_u__bo_hash(dpa_u_bo_ro_t bo);
extern void dpa_u_bo_put_h(dpa_u_a_bo_any_t bo);
extern void dpa_u_bo_put_h1(dpa_u_a_bo_unique_t bo);
extern void dpa_u_bo_ref_h(dpa_u_a_bo_any_t bo);
extern void dpa_u_bo_ref_h1(dpa_u_a_bo_unique_t bo);
