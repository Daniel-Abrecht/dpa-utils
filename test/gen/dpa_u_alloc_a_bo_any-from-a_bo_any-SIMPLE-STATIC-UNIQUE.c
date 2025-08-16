#include <dpa/utils/bo.h>
#include <stdio.h>

#define expect(X) \
  if(!(X)){ \
    fprintf(stderr, "assertion failed: %s\n", #X); \
    exit(1); \
  }

int main(void){
  const dpa_u_bo_t bo = {
    .size=13,
    .data="test 1       "
  };
  const dpa_u_a_bo_any_t inbo = ((dpa_u_a_bo_any_t){dpa_u_bo_intern_p(((dpa_u_a_bo_any_t){DPA__U_BO_TAG(&bo, DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)})).p});
  const dpa_u_a_bo_any_t outbo = dpa_u_alloc_a_bo_any(inbo);
  expect((dpa_u_bo_get_type(outbo) & (DPA_U_BO_STATIC|DPA_U_BO_UNIQUE|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)) == (DPA_U_BO_SIMPLE|DPA_U_BO_STATIC|DPA_U_BO_UNIQUE));
  expect(dpa_u_bo_compare_data(inbo, outbo) == 0);
  dpa_u_bo_put(outbo);
  dpa_u_bo_free(outbo);
}

