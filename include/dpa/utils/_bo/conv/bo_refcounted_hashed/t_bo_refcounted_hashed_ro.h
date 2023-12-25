#define dpa_u_t_bo_refcounted_hashed_ro(...) dpa_u_assert_selection(dpa_u_t_bo_refcounted_hashed_ro_g((__VA_ARGS__)))
#define dpa_u_tp_bo_refcounted_hashed_ro(...) &dpa_u_assert_selection(dpa_u_t_bo_refcounted_hashed_ro_g((__VA_ARGS__)))
#define dpa_u_t_bo_refcounted_hashed_ro_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__t_bo_refcounted_hashed_ro(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_v_any_bo_unique_hashmap__t_bo_refcounted_hashed_ro(DPA__G(dpa_u_any_bo_unique_hashmap_t*, (X))), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, t_bo_refcounted_hashed_ro, (X)), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__t_bo_refcounted_hashed_ro(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))) \
  )

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_refcounted_hashed_ro_t dpa__u_v_bo_unique_hashmap__t_bo_refcounted_hashed_ro_p(dpa_u_bo_unique_hashmap_t bo){
  return (dpa_u_bo_refcounted_hashed_ro_t){
    .bo_refcounted = {
      .bo_simple = {
        .type = DPA_U_BO_REFCOUNTED_HASHED,
        .size = dpa__u_v_bo_unique_hashmap__get_size(bo),
        .data = dpa__u_v_bo_unique_hashmap__data(bo),
      },
      .refcount = dpa__u_v_bo_unique_hashmap__get_refcount(bo),
    },
    .hash = dpa__u_v_bo_unique_hashmap__get_hash(bo),
  };
}
#define dpa__u_v_bo_unique_hashmap__t_bo_refcounted_hashed_ro(X) dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t, dpa__u_v_bo_unique_hashmap__t_bo_refcounted_hashed_ro_p((X)))
#define dpa__u_v_any_bo_unique_hashmap__t_bo_refcounted_hashed_ro(X) dpa__u_v_bo_unique_hashmap__t_bo_refcounted_hashed_ro((dpa_u_bo_unique_hashmap_t)(X))

#define dpa__u_v_bo_refcounted_hashed_ro__t_bo_refcounted_hashed_ro(X)  dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t, (X))
#define dpa__u_p_bo_refcounted_hashed_ro__t_bo_refcounted_hashed_ro(X)  dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t, *(X))
#define dpa__u_cp_bo_refcounted_hashed_ro__t_bo_refcounted_hashed_ro(X)  dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t, *(X))
#define dpa__u_any_bo_refcounted_hashed_ro__t_bo_refcounted_hashed_ro(X) dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t, *(dpa_u_bo_refcounted_hashed_ro_t*)(X))

#define dpa__u_bo_with_refcount_and_hash_ro__t_bo_refcounted_hashed_ro(X) dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t, dpa__u_bo_with_refcount_and_hash_ro__t_bo_refcounted_hashed_ro_p((X)))
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_refcounted_hashed_ro_t dpa__u_bo_with_refcount_and_hash_ro__t_bo_refcounted_hashed_ro_p(dpa_u_bo_with_refcount_and_hash_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: {
      return (dpa_u_bo_refcounted_hashed_ro_t){
        .bo_refcounted = {
          .bo_simple = {
            .type = DPA_U_BO_REFCOUNTED_HASHED,
            .size = dpa__u_any_bo_unique_hashmap__get_size(bo),
            .data = dpa__u_any_bo_unique_hashmap__data(bo),
          },
          .refcount = dpa__u_any_bo_unique_hashmap__get_refcount(bo),
        },
        .hash = dpa__u_any_bo_unique_hashmap__get_hash(bo),
      };
    }
    case DPA_U_BO_REFCOUNTED_HASHED: {
      return *(const dpa_u_bo_refcounted_hashed_ro_t*)bo;
    }
  }
  dpa_u_unreachable("dpa_u_bo_with_refcount_and_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
