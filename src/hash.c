#include <dpa/utils/hash.h>
#include <sys/random.h>
#include <errno.h>
#include <stdio.h>

extern uint64_t dpa_u_hash_64_FNV_1a_append_p(dpa_u_bo_ro_t bo, uint_fast64_t hash);
extern uint64_t dpa_u_hash_64_FNV_1a_p(dpa_u_bo_ro_t bo);
extern uint32_t dpa_u_hash_32_FNV_1a_append_p(dpa_u_bo_ro_t bo, uint_fast32_t hash);
extern uint32_t dpa_u_hash_32_FNV_1a_p(dpa_u_bo_ro_t bo);
extern uint16_t dpa_u_hash_16_append_p(dpa_u_bo_ro_t bo, uint_fast32_t hash);
extern uint16_t dpa_u_hash_16_p(dpa_u_bo_ro_t bo);
extern dpa_u_hash_t dpa_u_bo_hash_p(const struct dpa__u_default_hash_args args);

uint_fast64_t dpa_hash_offset_basis;

__attribute__((used,constructor(101)))
static inline void init(void){
  dpa_u_bo_inline_t buf = {
    .type = DPA_U_BO_INLINE,
    .size = DPA_U_BO_INLINE_MAX_SIZE
  };
  if(getrandom(buf.data, buf.size, 0) != buf.size){
    perror("getrandom failed");
    abort();
  }
  dpa_hash_offset_basis = dpa_u_hash_FNV_1a(buf);
}
