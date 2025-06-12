#include <dpa/utils/bo.h>
#include <stdio.h>

#define expect(X) \
  if(!(X)){ \
    fprintf(stderr, "assertion failed: %s\n", #X); \
    exit(1); \
  }

int main(){
  dpa_u_refcount_freeable_data_t* refdata = dpa_u_refcount_freeable_copy("137", 3, 1);
  const dpa_u_bo_t bo = {
    .size=3,
    .data=refdata->data
  };
const dpa_u_a_bo_gc_t inbo = ((dpa_u_a_bo_gc_t){DPA__U_BO_TAG((&(struct dpa__u_bo_refcounted){
  .refcount = &refdata->refcount,
  .bo = bo
}.bo), DPA_U_BO_SIMPLE|DPA_U_BO_REFCOUNTED)});
  const dpa_u_a_bo_gc_t outbo = dpa_u_make_a_bo_gc(inbo);
  expect((dpa_u_bo_get_type(outbo) & 0xF8) == (DPA_U_BO_SIMPLE|DPA_U_BO_REFCOUNTED));
  expect(dpa_u_bo_compare_data(inbo, outbo) == 0);
  dpa_u_bo_put(outbo);
}

