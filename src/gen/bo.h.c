#include <dpa/utils/bo.h>

extern dpa_u_bo_ro_t dpa__u_bo_to_bo_ro_h(dpa_u_bo_t bo);
extern dpa_u_bo_t dpa__u_bo_ro_to_p_bo_h(dpa_u_bo_ro_t bo);
extern dpa_u_bo_t dpa_u__inline_to_bo_h(const char*restrict const c);
extern dpa_u_bo_t dpa_u__to_bo_h(const dpa_u__boptr_t*restrict const boptr);
extern uint64_t dpa_u__bo_get_hash(dpa_u__boptr_t boptr);
