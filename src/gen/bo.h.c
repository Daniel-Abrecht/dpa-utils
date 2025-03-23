#include <dpa/utils/bo.h>

extern dpa_u_a_bo_unique_t dpa_u_bo_unique_from_uint(const uint64_t x);
extern dpa_u_bo_ro_t dpa__u_bo_to_bo_ro_h(dpa_u_bo_t bo);
extern dpa_u_bo_t dpa__u_bo_ro_to_p_bo_h(dpa_u_bo_ro_t bo);
extern dpa_u_bo_t dpa_u__inline_to_bo_h(const char*restrict const c);
extern dpa_u_bo_t dpa_u__to_bo_h(const dpa_u__boptr_t*restrict const boptr);
extern int dpa__u_bo_compare_h1(dpa_u_a_bo_any_ro_t a, dpa_u_a_bo_any_ro_t b);
extern int dpa__u_bo_compare_h2(dpa_u_a_bo_any_ro_t a, dpa_u_a_bo_any_ro_t b);
extern uint64_t dpa_u__bo_get_hash(dpa_u__boptr_t boptr);
extern uint64_t dpa_u__bo_hash(dpa_u_bo_ro_t bo);
