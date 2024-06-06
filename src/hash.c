#include <dpa/utils/hash.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#include <ntsecapi.h>
void dpa_u_getrandom(void* buf, size_t buflen){
  if(!RtlGenRandom(buf, buflen))
    dpa_u_abort("getrandom failed (%d): %s", errno, strerror(errno));
}
#elif DPA__U__has_include(<sys/random.h>)
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

dpa__u_api alignas(256) char dpa_u_seed[256];

dpa_u_init void dpa_u_init_seed(void){
  static bool init_done = false;
  if(init_done) return;
  init_done = true;
  dpa_u_getrandom(dpa_u_seed, sizeof(dpa_u_seed));
}

dpa_u_reproducible dpa__u_api dpa_u_hash_t dpa__u_cp_bo_inline__get_hash(const dpa_u_bo_inline_t*const bo){
  return dpa_u_bo_hash(bo);
}
