#include <dpa/utils/bo.h>
#include <stdio.h>

#define expect(X) \
  if(!(X)){ \
    fprintf(stderr, "assertion failed: %s\n", #X); \
    exit(1); \
  }

int main(){
  const dpa_u_bo_t bo = {
    .size=1,
    .data="2"
  };
const dpa_u_bo_t inbo = bo;
  const uint64_t hash = dpa__u_bo_hash(bo);
  const dpa_u_a_bo_any_t outbo = dpa_u_make_a_bo_any_with_hash(inbo, hash);
  expect((dpa_u_bo_get_type(outbo) & 0xF8) == (DPA_U_BO_HASHED|DPA_U_BO_SIMPLE));
  expect(dpa_u_bo_compare_data(inbo, outbo) == 0);
  dpa_u_bo_put(outbo);
}

