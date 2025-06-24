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
  const dpa_u_a_bo_hashed_t inbo = ((dpa_u_a_bo_hashed_t){DPA__U_BO_TAG((&(struct dpa__u_bo_hashed){
  .bo = bo,
  .hash = dpa__u_bo_hash(bo)
}.bo), DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)});
  const dpa_u_a_bo_any_t outbo = dpa_u_alloc_a_bo_any(inbo);
  expect((dpa_u_bo_get_type(outbo) & (DPA_U_BO_STATIC|DPA_U_BO_REFCOUNTED|DPA_U_BO_UNIQUE|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)) == (DPA_U_BO_HASHED|DPA_U_BO_SIMPLE));
  expect(dpa_u_bo_compare_data(inbo, outbo) == 0);
  dpa_u_bo_put(outbo);
  dpa_u_bo_free(outbo);
}

