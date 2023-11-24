
#define dpa_u_bo_intern(...) dpa_u_assert_selection(dpa_u_bo_intern_g(__VA_ARGS__))
#define dpa_u_bo_intern_g(X) _Generic((X), \
    dpa_u_bo_unique_hashmap_t: (dpa__u_v_bo_unique_hashmap__ref(DPA__G(dpa_u_bo_unique_hashmap_t,(X))),(const dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = DPA__G(dpa_u_bo_unique_hashmap_t,(X)) }), \
    dpa_u_any_bo_unique_hashmap_t*: (dpa__u_any_bo_unique_hashmap__ref(DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))),(const dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X)) }), \
    dpa__u_helper_v_g(bo_inline, v_bo_unique, (X)), \
    dpa__u_helper_v_g(bo_unique, intern, (X)), \
    default: dpa_u_generic_if_selection( dpa_u_p_any_bo_ro_g(X), dpa_u_bo_intern_p((dpa_u_any_bo_ro_t*)dpa_u_p_any_bo_ro_g(X)) ) \
  )

#define dpa__u_v_bo_unique__intern(X) (dpa__u_v_bo_unique__ref((X)),(X))
#define dpa__u_p_bo_unique__intern(X) (dpa__u_p_bo_unique__ref((X)),(X))
#define dpa__u_cp_bo_unique__intern(X) (dpa__u_cp_bo_unique__ref((X)),(X))
#define dpa__u_any_bo_unique__intern(X) (dpa__u_any_bo_unique__ref((X)),(X))

dpa_u_export inline dpa_u_bo_unique_t dpa_u_bo_intern_p(dpa_u_any_bo_ro_t*const bo){
  // We allow the simple cases to be inlined, and the complicated one is handled in dpa__u_bo_do_intern instead
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (dpa_u_bo_unique_t){ .bo_inline = *(dpa_u_bo_inline_t*)bo };
    case DPA_U_BO_UNIQUE_HASHMAP: {
      dpa_u_bo_unique_hashmap_t ubo = (dpa_u_bo_unique_hashmap_t)bo;
#if defined(__GNUC__) && !defined(__llvm__)
// GCC will get confused about which branchs are reachable and warn. All we can do about it is disable the warning.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#endif
      dpa_u_bo_ref(ubo);
#if defined(__GNUC__) && !defined(__llvm__)
#pragma GCC diagnostic pop
#endif
      return (dpa_u_bo_unique_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = ubo,
      };
    }
    default: {
      if(dpa_u_bo_get_size(bo) <= DPA_U_BO_INLINE_MAX_SIZE){
        dpa_u_bo_inline_t boi = {
          .type = DPA_U_BO_INLINE,
          .size = dpa_u_bo_get_size(bo),
        };
        memcpy(boi.data, dpa_u_bo_data(bo), dpa_u_bo_get_size(bo));
        return (dpa_u_bo_unique_t){ .bo_inline = boi };
      }
      extern dpa_u_bo_unique_hashmap_t dpa__u_bo_do_intern(dpa_u_any_bo_ro_t*const bo);
      return (dpa_u_bo_unique_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = dpa__u_bo_do_intern(bo),
      };
    }
  }
}
