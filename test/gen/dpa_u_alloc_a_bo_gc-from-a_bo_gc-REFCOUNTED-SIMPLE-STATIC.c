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
  const dpa_u_a_bo_gc_t inbo = ((dpa_u_a_bo_gc_t){DPA__U_BO_TAG((&(struct dpa__u_bo_refcounted){
  .refcount = &dpa_u_refcount_static_v_freeable,
  .bo = bo
}.bo), DPA_U_BO_REFCOUNTED|DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)});
  const dpa_u_a_bo_gc_t outbo = dpa_u_alloc_a_bo_gc(inbo);
  expect((dpa_u_bo_get_type(outbo) & (DPA_U_BO_STATIC|DPA_U_BO_UNIQUE|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)) == (DPA_U_BO_SIMPLE|DPA_U_BO_STATIC));
  expect(dpa_u_bo_compare_data(inbo, outbo) == 0);
  dpa_u_bo_put(outbo);
  dpa_u_bo_free(outbo);
}

