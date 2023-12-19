#define dpa_u_t_bo_refcounted_ro(...) dpa_u_assert_selection(dpa_u_t_bo_refcounted_ro_g((__VA_ARGS__)))
#define dpa_u_t_bo_refcounted_ro_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__t_bo_refcounted_ro(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_v_any_bo_unique_hashmap__t_bo_refcounted_ro((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*, (X))), \
    dpa__u_helper_v_g(bo_refcounted_ro, t_bo_refcounted_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted, t_bo_refcounted_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, t_bo_refcounted_ro, (X)), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__t_bo_refcounted_ro(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount__t_bo_refcounted_ro(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__t_bo_refcounted_ro(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_t_bo_refcounted_ro__helper(P,X) (dpa_u_bo_refcounted_ro_t){ .bo_simple = { .type = DPA_U_BO_REFCOUNTED, .size=dpa__u_ ## P ## __get_size((X)), .data=dpa__u_ ## P ## __data((X)) }, .refcount=dpa__u_ ## P ## __get_refcount((X)) }
#define dpa__u_t_bo_refcounted_ro__helper_s1(X) dpa_u_rescope(dpa_u_bo_refcounted_ro_t, dpa__u_refcounted_ro_fix_type(X))

#define dpa__u_v_bo_unique_hashmap__t_bo_refcounted_ro(X) dpa__u_t_bo_refcounted_ro__helper(v_bo_unique_hashmap,(X))
#define dpa__u_v_any_bo_unique_hashmap__t_bo_refcounted_ro(X) dpa__u_t_bo_refcounted_ro__helper(any_bo_unique_hashmap,(X))

#define dpa__u_v_bo_refcounted_ro__t_bo_refcounted_ro(X)   dpa_u_rescope(dpa_u_bo_refcounted_ro_t,  (X))
#define dpa__u_p_bo_refcounted_ro__t_bo_refcounted_ro(X)   dpa_u_rescope(dpa_u_bo_refcounted_ro_t, *(X))
#define dpa__u_cp_bo_refcounted_ro__t_bo_refcounted_ro(X)  dpa_u_rescope(dpa_u_bo_refcounted_ro_t, *(X))
#define dpa__u_any_bo_refcounted_ro__t_bo_refcounted_ro(X) dpa__u_t_bo_refcounted_ro__helper_s1(*(dpa_u_bo_refcounted_ro_t*)(X))

#define dpa__u_v_bo_refcounted__t_bo_refcounted_ro(X)   dpa_u_rescope(dpa_u_bo_refcounted_ro_t, (X).ro)
#define dpa__u_p_bo_refcounted__t_bo_refcounted_ro(X)   dpa_u_rescope(dpa_u_bo_refcounted_ro_t, (X)->ro)
#define dpa__u_cp_bo_refcounted__t_bo_refcounted_ro(X)  dpa_u_rescope(dpa_u_bo_refcounted_ro_t, (X)->ro)
#define dpa__u_any_bo_refcounted__t_bo_refcounted_ro(X) dpa__u_t_bo_refcounted_ro__helper_s1(*(dpa_u_bo_refcounted_ro_t*)(X))

#define dpa__u_v_bo_refcounted_hashed_ro__t_bo_refcounted_ro(X) dpa__u_t_bo_refcounted_ro__helper_s1((X).bo_refcounted)
#define dpa__u_p_bo_refcounted_hashed_ro__t_bo_refcounted_ro(X) dpa__u_t_bo_refcounted_ro__helper_s1((X)->bo_refcounted)
#define dpa__u_cp_bo_refcounted_hashed_ro__t_bo_refcounted_ro(X) dpa__u_t_bo_refcounted_ro__helper_s1((X)->bo_refcounted)
#define dpa__u_any_bo_refcounted_hashed_ro__t_bo_refcounted_ro(X) dpa__u_t_bo_refcounted_ro__helper_s1(*(dpa_u_bo_refcounted_ro_t*)(X))

#define dpa__u_bo_with_refcount_and_hash_ro__t_bo_refcounted_ro(X) dpa__u_t_bo_refcounted_ro__helper(bo_with_refcount_and_hash_ro,(X))
#define dpa__u_bo_with_refcount_ro__t_bo_refcounted_ro(X) dpa__u_t_bo_refcounted_ro__helper(bo_with_refcount_ro,(X))
#define dpa__u_bo_with_refcount__t_bo_refcounted_ro(X) dpa__u_t_bo_refcounted_ro__helper_s1(*(dpa_u_bo_refcounted_ro_t*)(X))
