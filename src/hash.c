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

dpa__u_api alignas(DPA_U_SEED_SIZE) char dpa_u_seed[DPA_U_SEED_SIZE];

static int hex2int(char digit){
  if(digit >= '0' && digit <= '9')
    return digit - '0';
  if(digit >= 'a' && digit <= 'z')
    return digit - 'a';
  if(digit >= 'A' && digit <= 'Z')
    return digit - 'A';
  return 0;
}

dpa_u_init void dpa_u_init_seed(void){
  static bool init_done = false;
  if(init_done) return;
  init_done = true;
  unsigned seed_predefined_length = 0;
  const char* force_seed = getenv("DPA_U_SEED");
  if(force_seed)
    for(
      int i = 0;
      seed_predefined_length < sizeof(dpa_u_seed) && force_seed[i] && force_seed[i+1];
      i+=2, seed_predefined_length++
    ) dpa_u_seed[seed_predefined_length] = hex2int(force_seed[i])*0x10 + hex2int(force_seed[i+1]);
  dpa_u_getrandom(dpa_u_seed+seed_predefined_length, sizeof(dpa_u_seed)-seed_predefined_length);
}
