#include <dpa/utils/hash.h>
#include <sys/random.h>
#include <errno.h>
#include <stdio.h>

uint_fast64_t dpa_hash_offset_basis;

__attribute__((used,constructor(101)))
void init_hash_basis(void){
  dpa_u_bo_inline_t buf;
  if(getrandom(buf.data, sizeof(buf.data), 0) != sizeof(buf.data)){
    perror("getrandom failed");
    abort();
  }
  dpa_hash_offset_basis = dpa_u_hash_FNV_1a(buf);
}
