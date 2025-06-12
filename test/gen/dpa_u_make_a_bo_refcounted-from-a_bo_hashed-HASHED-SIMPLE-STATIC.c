#include <dpa/utils/bo.h>
#include <stdio.h>

#define expect(X) \
  if(!(X)){ \
    fprintf(stderr, "assertion failed: %s\n", #X); \
    exit(1); \
  }

int main(){
  const dpa_u_bo_t bo = {
    .size=3,
    .data="209"
  };
const dpa_u_a_bo_hashed_t inbo = ((dpa_u_a_bo_hashed_t){DPA__U_BO_TAG((&(struct dpa__u_bo_hashed){
  .bo = bo,
  .hash = dpa__u_bo_hash(bo)
}.bo), DPA_U_BO_STATIC|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)});
  const dpa_u_a_bo_refcounted_t outbo = dpa_u_make_a_bo_refcounted(inbo);
  expect((dpa_u_bo_get_type(outbo) & 0xF8) == (DPA_U_BO_STATIC|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE));
  expect(dpa_u_bo_compare_data(inbo, outbo) == 0);
  dpa_u_bo_put(outbo);
}

