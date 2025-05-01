#include <dpa/utils/bo.h>

extern dpa__u_bo_hashed_t dpa__u_a_to_bo_hashed_h(const dpa__u_boptr_t*restrict const boptr);
extern dpa__u_bo_hashed_t dpa__u_bo_to_bo_hashed_h(const dpa_u_bo_t bo);
extern dpa__u_boptr_t dpa__u_bo_copy_bo_maybe_h(const dpa__u_boptr_t bo);
extern dpa__u_boptr_t dpa__u_bo_copy_maybe_h(const dpa__u_boptr_t bo);
extern dpa__u_boptr_t dpa__u_bo_needs_copy_h(const dpa__u_boptr_t bo);
extern dpa__u_boptr_t dpa__u_to_bo_gc_h(dpa__u_boptr_t p);
extern dpa_u_a_bo_unique_t dpa__u_bo_copy_maybe_h1(const dpa_u_a_bo_unique_t bo);
extern dpa_u_bo_t dpa__u_to_bo_h(const dpa__u_boptr_t*restrict const boptr);
extern dpa_u_bo_t* dpa__u_bo_copy_maybe_h2(const dpa_u_bo_t bo);
extern dpa_u_refcount_freeable_t* dpa__u_bo_get_refcount_h(const dpa__u_boptr_t bo);
extern dpa_u_refcount_freeable_t* dpa__u_bo_get_refcount_h1(const dpa_u_a_bo_unique_t bo);
extern int dpa__u_bo_compare_h1(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b);
extern int dpa__u_bo_compare_h2(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b);
extern int dpa__u_bo_is_equal_h1(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b);
extern int dpa__u_bo_is_equal_h2(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b);
extern int dpa_u_bo_compare_data_p(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b);
extern int dpa_u_bo_is_same_p(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b);
extern uint64_t dpa__u_bo_get_hash(const dpa__u_boptr_t boptr);
extern uint64_t dpa__u_bo_hash(dpa_u_bo_t bo);
extern void dpa__u_bo_free_h(const dpa__u_boptr_t bo);
extern void dpa__u_bo_put_h(const dpa__u_boptr_t bo);
extern void dpa__u_bo_put_h1(const dpa_u_a_bo_unique_t bo);
extern void dpa__u_bo_ref_h(const dpa__u_boptr_t bo);
extern void dpa__u_bo_ref_h1(const dpa_u_a_bo_unique_t bo);
