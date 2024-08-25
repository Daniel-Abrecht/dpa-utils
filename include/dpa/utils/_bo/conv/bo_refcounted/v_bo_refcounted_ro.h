#define dpa_u_v_bo_refcounted_ro(...) dpa_u_assert_selection(dpa_u_v_bo_refcounted_ro_g((__VA_ARGS__)))
#define dpa_u_v_bo_refcounted_ro_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__v_bo_refcounted_ro(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_v_any_bo_unique_hashmap__v_bo_refcounted_ro((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*, (X))), \
    dpa__u_helper_v_g(bo_refcounted_ro, v_bo_refcounted_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted, v_bo_refcounted_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, v_bo_refcounted_ro, (X)), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__v_bo_refcounted_ro(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount__v_bo_refcounted_ro(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__v_bo_refcounted_ro(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_v_bo_refcounted_ro__helper_s1(X) dpa_u_rescope(const dpa_u_bo_refcounted_ro_t, dpa__u_refcounted_ro_fix_type(X))

#define dpa__u_v_bo_unique_hashmap__v_bo_refcounted_ro(X) dpa_u_rescope(const dpa_u_bo_refcounted_ro_t, dpa__u_v_bo_unique_hashmap__t_bo_refcounted_ro_p((X)))
#define dpa__u_v_any_bo_unique_hashmap__v_bo_refcounted_ro(X) dpa__u_v_bo_unique_hashmap__t_bo_refcounted_ro((const dpa_u_bo_unique_hashmap_t)(X))

#define dpa__u_v_bo_refcounted_ro__v_bo_refcounted_ro(X)   (X)
#define dpa__u_p_bo_refcounted_ro__v_bo_refcounted_ro(X)  *(X)
#define dpa__u_cp_bo_refcounted_ro__v_bo_refcounted_ro(X) *(X)
#define dpa__u_any_bo_refcounted_ro__v_bo_refcounted_ro(X) dpa__u_v_bo_refcounted_ro__helper_s1(*(dpa_u_bo_refcounted_ro_t*)(X))

#define dpa__u_v_bo_refcounted__v_bo_refcounted_ro(X)  (X).ro
#define dpa__u_p_bo_refcounted__v_bo_refcounted_ro(X)  (X)->ro
#define dpa__u_cp_bo_refcounted__v_bo_refcounted_ro(X) (X)->ro
#define dpa__u_any_bo_refcounted__v_bo_refcounted_ro(X) ((const dpa_u_bo_refcounted_t*)(X))->ro

#define dpa__u_v_bo_refcounted_hashed_ro__v_bo_refcounted_ro(X) dpa__u_v_bo_refcounted_ro__helper_s1((X).bo_refcounted)
#define dpa__u_p_bo_refcounted_hashed_ro__v_bo_refcounted_ro(X) dpa__u_v_bo_refcounted_ro__helper_s1((X)->bo_refcounted)
#define dpa__u_cp_bo_refcounted_hashed_ro__v_bo_refcounted_ro(X) dpa__u_v_bo_refcounted_ro__helper_s1((X)->bo_refcounted)
#define dpa__u_any_bo_refcounted_hashed_ro__v_bo_refcounted_ro(X) dpa__u_v_bo_refcounted_ro__helper_s1(*(dpa_u_bo_refcounted_ro_t*)(X))

#define dpa__u_bo_with_refcount_and_hash_ro__v_bo_refcounted_ro(X) dpa_u_rescope(const dpa_u_bo_refcounted_ro_t, dpa__u_bo_with_refcount_and_hash_ro__t_bo_refcounted_ro_p(X))
#define dpa__u_bo_with_refcount_ro__v_bo_refcounted_ro(X) dpa_u_rescope(const dpa_u_bo_refcounted_ro_t, dpa__u_bo_with_refcount_ro__v_bo_refcounted_ro_p(X))
#define dpa__u_bo_with_refcount__v_bo_refcounted_ro(X) ((const dpa_u_bo_refcounted_t*)(X))->ro
