#include <dpa/utils/hash.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>

#if DPA__U__has_include(<sys/random.h>)
#include <sys/random.h>
void dpa_u_getrandom(void* _buf, size_t buflen){
  char* buf = _buf;
  while(buflen){
    ssize_t i = getrandom(buf, buflen, 0);
    if(i == -1 && errno == EINTR)
      continue;
    if(((size_t)i)>buflen)
      dpa_u_abort("getrandom failed (%d): %s", errno, strerror(errno));
    buf += i;
    buflen -= i;
  }
}
#endif

extern uint64_t dpa_u_hash_64_FNV_1a_append_p(dpa_u_bo_simple_ro_t bo, uint_fast64_t hash);
extern uint64_t dpa_u_hash_64_FNV_1a_p(dpa_u_bo_simple_ro_t bo);
extern uint32_t dpa_u_hash_32_FNV_1a_append_p(dpa_u_bo_simple_ro_t bo, uint_fast32_t hash);
extern uint32_t dpa_u_hash_32_FNV_1a_p(dpa_u_bo_simple_ro_t bo);
extern uint16_t dpa_u_hash_16_append_p(dpa_u_bo_simple_ro_t bo, uint_fast32_t hash);
extern uint16_t dpa_u_hash_16_p(dpa_u_bo_simple_ro_t bo);
extern dpa_u_hash_t dpa_u_bo_hash_p(const struct dpa__u_default_hash_args args);

dpa_u_hash_t dpa_hash_offset_basis;

dpa_u_init void dpa_u_init_dpa_hash_offset_basis(void){
  static bool init_done = false;
  if(init_done) return;
  init_done = true;
  dpa_u_bo_inline_t buf = {
    .type = DPA_U_BO_INLINE,
    .size = DPA_U_BO_INLINE_MAX_SIZE
  };
  dpa_u_getrandom(buf.data, buf.size);
  dpa_hash_offset_basis = dpa_u_hash_FNV_1a(buf);
}
