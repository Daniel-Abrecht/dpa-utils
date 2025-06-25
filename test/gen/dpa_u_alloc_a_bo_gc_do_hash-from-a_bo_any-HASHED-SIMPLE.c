#include <dpa/utils/bo.h>
#include <stdio.h>

#define expect(X) \
  if(!(X)){ \
    fprintf(stderr, "assertion failed: %s\n", #X); \
    exit(1); \
  }

int main(){
  const dpa_u_bo_t bo = {
    .size=6,
    .data="test 1"
  };
  const dpa_u_a_bo_any_t inbo = ((dpa_u_a_bo_any_t){DPA__U_BO_TAG((&(struct dpa__u_bo_hashed){
  .bo = bo,
  .hash = dpa__u_bo_hash(bo)
}.bo), DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)});
  const dpa_u_a_bo_gc_t outbo = dpa_u_alloc_a_bo_gc_do_hash(inbo);
  expect(dpa_u_bo_is_error(outbo));
  dpa_u_bo_put(inbo);
}

