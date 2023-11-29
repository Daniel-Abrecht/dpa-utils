#include <dpa/utils/hash.h>

extern dpa_u_hash_t dpa_u_bo_hash_p(const struct dpa__u_default_hash_args args);
extern uint16_t dpa_u_hash_16_append_p(dpa_u_bo_simple_ro_t bo, uint_fast32_t hash);
extern uint16_t dpa_u_hash_16_p(dpa_u_bo_simple_ro_t bo);
extern uint32_t dpa_u_hash_32_FNV_1a_append_p(dpa_u_bo_simple_ro_t bo, uint_fast32_t hash);
extern uint32_t dpa_u_hash_32_FNV_1a_p(dpa_u_bo_simple_ro_t bo);
extern uint64_t dpa_u_hash_64_FNV_1a_append_p(dpa_u_bo_simple_ro_t bo, uint_fast64_t hash);
extern uint64_t dpa_u_hash_64_FNV_1a_p(dpa_u_bo_simple_ro_t bo);
