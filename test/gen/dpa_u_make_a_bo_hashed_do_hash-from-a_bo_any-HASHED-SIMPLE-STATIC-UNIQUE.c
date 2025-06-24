#include <dpa/utils/bo.h>
#include <stdio.h>

#define expect(X) \
  if(!(X)){ \
    fprintf(stderr, "assertion failed: %s\n", #X); \
    exit(1); \
  }

int main(){
  const dpa_u_bo_t bo = {
    .size=70,
    .data="test 1                                                                "
  };
  const dpa_u_a_bo_any_t inbo = ((dpa_u_a_bo_any_t){dpa__u_bo_intern_h(((dpa_u_a_bo_any_t){DPA__U_BO_TAG(&bo, DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)})).p});
  const dpa_u_a_bo_hashed_t outbo = dpa_u_make_a_bo_hashed_do_hash(inbo);
  expect(dpa_u_bo_is_error(outbo));
  dpa_u_bo_put(inbo);
}

