#include <dpa/utils/bo.h>
#include <stdio.h>

#define expect(X) \
  if(!(X)){ \
    fprintf(stderr, "assertion failed: %s\n", #X); \
    exit(1); \
  }

int main(){
  dpa_u_refcount_freeable_data_t* refdata = dpa_u_refcount_freeable_copy("test 1", 6, 1);
  const dpa_u_bo_t bo = {
    .size=6,
    .data=refdata->data
  };
  const dpa_u_bo_t inbo = bo;
  dpa_u_refcount_freeable_t* refcount = &refdata->refcount;
  const dpa_u_a_bo_gc_t outbo = dpa_u_alloc_a_bo_gc_with_refcount_do_hash(inbo, refcount);
  expect((dpa_u_bo_get_type(outbo) & (DPA_U_BO_STATIC|DPA_U_BO_REFCOUNTED|DPA_U_BO_UNIQUE|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)) == (DPA_U_BO_HASHED|DPA_U_BO_REFCOUNTED|DPA_U_BO_SIMPLE));
  expect(dpa_u_bo_compare_data(inbo, outbo) == 0);
  dpa_u_bo_put(outbo);
  dpa_u_bo_free(outbo);
}

