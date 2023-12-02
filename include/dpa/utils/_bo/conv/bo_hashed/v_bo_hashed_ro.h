#define dpa_u_v_bo_hashed_ro(...) dpa_u_assert_selection(dpa_u_v_bo_hashed_ro_g(__VA_ARGS__))
#define dpa_u_v_bo_hashed_ro_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__v_bo_hashed_ro((X)), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_v_any_bo_unique_hashmap__v_bo_hashed_ro((X)), \
    dpa__u_helper_v_g(bo_hashed_ro, v_bo_hashed_ro, (X)), \
    dpa__u_helper_v_g(bo_hashed, v_bo_hashed_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, v_bo_hashed_ro, (X)), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__v_bo_hashed_ro(X), \
    dpa_u_bo_with_hash_ro_t*: dpa__u_bo_with_hash_ro__v_bo_hashed_ro(X), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__v_bo_hashed_ro((X)) \
  )

#define dpa__u_v_bo_hashed_ro__helper(P,X) (const dpa_u_bo_hashed_ro_t){ .bo_simple = { .type = DPA_U_BO_HASHED, .size=dpa__u_ ## P ## __get_size((X)), .data=dpa__u_ ## P ## __data((X)) }, .hash=dpa__u_ ## P ## __get_hash((X)) }

#define dpa__u_v_bo_unique_hashmap__v_bo_hashed_ro(X) dpa__u_v_bo_hashed_ro__helper(v_bo_unique_hashmap,(X))
#define dpa__u_v_any_bo_unique_hashmap__v_bo_hashed_ro(X) dpa__u_v_bo_hashed_ro__helper(v_any_bo_unique_hashmap,(X))

#define dpa__u_v_bo_hashed_ro__v_bo_hashed_ro(X)   (X)
#define dpa__u_p_bo_hashed_ro__v_bo_hashed_ro(X)  *(X)
#define dpa__u_cp_bo_hashed_ro__v_bo_hashed_ro(X) *(X)
#define dpa__u_any_bo_hashed_ro__v_bo_hashed_ro(X) dpa__u_v_bo_hashed_ro__helper(any_bo_hashed_ro,(X))

#define dpa__u_v_bo_hashed__v_bo_hashed_ro(X)  (X).ro
#define dpa__u_p_bo_hashed__v_bo_hashed_ro(X)  (X)->ro
#define dpa__u_cp_bo_hashed__v_bo_hashed_ro(X) (X)->ro
#define dpa__u_any_bo_hashed__v_bo_hashed_ro(X) dpa__u_v_bo_hashed_ro__helper(any_bo_hashed,(X))

#define dpa__u_v_bo_refcounted_hashed_ro__v_bo_hashed_ro(X) dpa__u_v_bo_hashed_ro__helper(v_bo_refcounted_hashed_ro,(X))
#define dpa__u_p_bo_refcounted_hashed_ro__v_bo_hashed_ro(X) dpa__u_v_bo_hashed_ro__helper(p_bo_refcounted_hashed_ro,(X))
#define dpa__u_cp_bo_refcounted_hashed_ro__v_bo_hashed_ro(X) dpa__u_v_bo_hashed_ro__helper(cp_bo_refcounted_hashed_ro,(X))
#define dpa__u_any_bo_refcounted_hashed_ro__v_bo_hashed_ro(X) dpa__u_v_bo_hashed_ro__helper(any_bo_refcounted_hashed_ro,(X))

#define dpa__u_bo_with_hash__v_bo_hashed_ro(X) dpa_u_rescope(const dpa_u_bo_hashed_ro_t,dpa__u_bo_with_hash__v_bo_hashed_ro_p(X))
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline dpa_u_bo_hashed_ro_t dpa__u_bo_with_hash__v_bo_hashed_ro_p(dpa_u_bo_with_hash_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (const dpa_u_bo_hashed_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_HASHED,
          .size = dpa__u_any_bo_inline__get_size(bo),
          .data = dpa__u_any_bo_inline__data(bo),
        },
        .hash = dpa__u_any_bo_inline__get_hash(bo),
      };
    case DPA_U_BO_HASHED:
      return (const dpa_u_bo_hashed_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_HASHED,
          .size = dpa__u_any_bo_hashed_ro__get_size(bo),
          .data = dpa__u_any_bo_hashed_ro__data(bo),
        },
        .hash = dpa__u_any_bo_hashed_ro__get_hash(bo),
      };
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_hash_ro__v_bo_hashed_ro(X) dpa_u_rescope(const dpa_u_bo_hashed_ro_t,dpa__u_bo_with_hash_ro__v_bo_hashed_ro_p(X))
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline dpa_u_bo_hashed_ro_t dpa__u_bo_with_hash_ro__v_bo_hashed_ro_p(dpa_u_bo_with_hash_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (const dpa_u_bo_hashed_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_HASHED,
          .size = dpa__u_any_bo_inline__get_size(bo),
          .data = dpa__u_any_bo_inline__data(bo),
        },
        .hash = dpa__u_any_bo_inline__get_hash(bo),
      };
    case DPA_U_BO_UNIQUE_HASHMAP:
    case DPA_U_BO_HASHED:
      return (const dpa_u_bo_hashed_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_HASHED,
          .size = dpa__u_any_bo_hashed_ro__get_size(bo),
          .data = dpa__u_any_bo_hashed_ro__data(bo),
        },
        .hash = dpa__u_any_bo_hashed_ro__get_hash(bo),
      };
    case DPA_U_BO_REFCOUNTED_HASHED:
      return (const dpa_u_bo_hashed_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_HASHED,
          .size = dpa__u_any_bo_refcounted_hashed_ro__get_size(bo),
          .data = dpa__u_any_bo_refcounted_hashed_ro__data(bo),
        },
        .hash = dpa__u_any_bo_refcounted_hashed_ro__get_hash(bo),
      };
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount_and_hash_ro__v_bo_hashed_ro(X) dpa__u_bo_with_refcount_and_hash_ro__t_bo_hashed_ro(X)
