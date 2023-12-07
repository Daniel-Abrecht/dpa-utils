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
#elif _MSC_VER
#include <windows.h>
#include <ntsecapi.h>
void dpa_u_getrandom(void* buf, size_t buflen){
  if(!RtlGenRandom(buf, buflen))
    dpa_u_abort("getrandom failed (%d): %s", errno, strerror(errno));
}
#endif

dpa__u_api dpa_u_hash_t dpa_hash_offset_basis;

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
