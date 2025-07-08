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
  const dpa_u_a_bo_gc_t inbo = ((dpa_u_a_bo_gc_t){dpa_u_bo_intern_p(((dpa_u_a_bo_any_t){DPA__U_BO_TAG(&bo, DPA_U_BO_SIMPLE)})).p});
  const dpa_u_a_bo_refcounted_t outbo = dpa_u_make_a_bo_refcounted(inbo);
  expect(dpa_u_bo_is_error(outbo));
  dpa_u_bo_put(inbo);
}

