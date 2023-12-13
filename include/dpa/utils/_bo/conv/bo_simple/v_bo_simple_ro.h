#define dpa_u_v_bo_simple_ro(...) dpa_u_assert_selection(dpa_u_v_bo_simple_ro_g((__VA_ARGS__)))
#define dpa_u_v_bo_simple_ro_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__v_bo_simple_ro((X)), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__v_bo_simple_ro((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    dpa__u_helper_v_g(bo_simple, v_bo_simple_ro, (X)), \
    dpa__u_helper_v_g(bo_simple_ro, v_bo_simple_ro, (X)), \
    dpa__u_helper_v_g(bo_hashed, v_bo_simple_ro, (X)), \
    dpa__u_helper_v_g(bo_hashed_ro, v_bo_simple_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted, v_bo_simple_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted_ro, v_bo_simple_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, v_bo_simple_ro, (X)), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__v_bo_simple_ro(DPA__G(dpa_u_bo_with_refcount_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount_ro__v_bo_simple_ro(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__v_bo_simple_ro(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))) \
  )

#define dpa__u_v_bo_unique_hashmap__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(v_bo_unique_hashmap,(X))
#define dpa__u_p_bo_unique_hashmap__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(p_bo_unique_hashmap,(X))
#define dpa__u_cp_bo_unique_hashmap__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(cp_bo_unique_hashmap,(X))
#define dpa__u_any_bo_unique_hashmap__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(any_bo_unique_hashmap,(X))

#define dpa__u_v_bo_simple__v_bo_simple_ro(X) (X).ro
#define dpa__u_p_bo_simple__v_bo_simple_ro(X) (X)->ro
#define dpa__u_cp_bo_simple__v_bo_simple_ro(X) (X)->ro
#define dpa__u_any_bo_simple__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(any_bo_simple,(X))

#define dpa__u_v_bo_simple_ro__v_bo_simple_ro(X) (X)
#define dpa__u_p_bo_simple_ro__v_bo_simple_ro(X) (*(X))
#define dpa__u_cp_bo_simple_ro__v_bo_simple_ro(X) (*(X))
#define dpa__u_any_bo_simple_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(any_bo_simple_ro,(X))

#define dpa__u_v_bo_hashed__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(v_bo_hashed,(X))
#define dpa__u_p_bo_hashed__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(p_bo_hashed,(X))
#define dpa__u_cp_bo_hashed__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(cp_bo_hashed,(X))
#define dpa__u_any_bo_hashed__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(any_bo_hashed,(X))

#define dpa__u_v_bo_hashed_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(v_bo_hashed_ro,(X))
#define dpa__u_p_bo_hashed_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(p_bo_hashed_ro,(X))
#define dpa__u_cp_bo_hashed_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(cp_bo_hashed_ro,(X))
#define dpa__u_any_bo_hashed_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(any_bo_hashed_ro,(X))

#define dpa__u_v_bo_refcounted__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(v_bo_refcounted,(X))
#define dpa__u_p_bo_refcounted__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(p_bo_refcounted,(X))
#define dpa__u_cp_bo_refcounted__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(cp_bo_refcounted,(X))
#define dpa__u_any_bo_refcounted__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(any_bo_refcounted,(X))

#define dpa__u_v_bo_refcounted_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(v_bo_refcounted_ro,(X))
#define dpa__u_p_bo_refcounted_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(p_bo_refcounted_ro,(X))
#define dpa__u_cp_bo_refcounted_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(cp_bo_refcounted_ro,(X))
#define dpa__u_any_bo_refcounted_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(any_bo_refcounted_ro,(X))

#define dpa__u_v_bo_refcounted_hashed_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(v_bo_refcounted_hashed_ro,(X))
#define dpa__u_p_bo_refcounted_hashed_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(p_bo_refcounted_hashed_ro,(X))
#define dpa__u_cp_bo_refcounted_hashed_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(cp_bo_refcounted_hashed_ro,(X))
#define dpa__u_any_bo_refcounted_hashed_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(any_bo_refcounted_hashed_ro,(X))

#define dpa__u_bo_with_refcount_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(bo_with_refcount_ro,(X))
#define dpa__u_bo_with_refcount__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(bo_with_refcount,(X))
#define dpa__u_bo_with_refcount_and_hash_ro__v_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper(bo_with_refcount_and_hash_ro,(X))
