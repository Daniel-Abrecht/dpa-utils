#define dpa_u_v_bo_refcounted_hashed_ro(...) dpa_u_assert_selection(dpa_u_v_bo_refcounted_hashed_ro_g((__VA_ARGS__)))
#define dpa_u_v_bo_refcounted_hashed_ro_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__v_bo_refcounted_hashed_ro((X)), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_v_any_bo_unique_hashmap__v_bo_refcounted_hashed_ro((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*, (X))), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, v_bo_refcounted_hashed_ro, (X)), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__v_bo_refcounted_hashed_ro(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))) \
  )

#define dpa__u_v_bo_unique_hashmap__v_bo_refcounted_hashed_ro(X) (const dpa_u_bo_refcounted_hashed_ro_t){ .bo_refcounted = { .bo_simple = { .type=DPA_U_BO_REFCOUNTED, .size=dpa__u_v_bo_unique_hashmap__get_size((X)), .data=dpa__u_v_bo_unique_hashmap__data((X)) }, .refcount=dpa__u_v_bo_unique_hashmap__get_refcount((X)) } }
#define dpa__u_v_any_bo_unique_hashmap__v_bo_refcounted_hashed_ro(X) (const dpa_u_bo_refcounted_hashed_ro_t){ .bo_refcounted = { .bo_simple = { .type=DPA_U_BO_REFCOUNTED, .size=dpa__u_any_bo_unique_hashmap__get_size((X)), .data=dpa__u_any_bo_unique_hashmap__data((X)) }, .refcount=dpa__u_any_bo_unique_hashmap__get_refcount((X)) } }

#define dpa__u_v_bo_refcounted_hashed_ro__v_bo_refcounted_hashed_ro(X) (X)
#define dpa__u_p_bo_refcounted_hashed_ro__v_bo_refcounted_hashed_ro(X) *(X)
#define dpa__u_cp_bo_refcounted_hashed_ro__v_bo_refcounted_hashed_ro(X) *(X)
#define dpa__u_any_bo_refcounted_hashed_ro__v_bo_refcounted_hashed_ro(X) *(const dpa_u_bo_refcounted_hashed_ro_t*)(X)

#define dpa__u_bo_with_refcount_and_hash_ro__v_bo_refcounted_hashed_ro(X)  (const dpa_u_bo_refcounted_hashed_ro_t){ .bo_refcounted = { .bo_simple = { .type=DPA_U_BO_REFCOUNTED_HASHED, .size=dpa__u_bo_with_refcount_and_hash_ro__get_size((X)), .data=dpa__u_bo_with_refcount_and_hash_ro__data((X)) }, .refcount=dpa__u_bo_with_refcount_and_hash_ro__get_refcount((X)) } }
