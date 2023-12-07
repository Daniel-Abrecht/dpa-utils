#define dpa_u_v_bo_unique(...) dpa_u_assert_selection(dpa_u_v_bo_unique_g(__VA_ARGS__))
#define dpa_u_v_bo_unique_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__v_bo_unique(DPA__G(dpa_u_bo_unique_hashmap_t, (X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__v_bo_unique(DPA__G(dpa_u_any_bo_unique_hashmap_t*, (X))), \
    dpa__u_helper_v_g(bo_unique, v_bo_unique, (X)), \
    dpa__u_helper_v_g(bo_inline, v_bo_unique, (X)) \
  )

#define dpa__u_v_bo_unique_hashmap__v_bo_unique(X) (const dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (X) }
#define dpa__u_any_bo_unique_hashmap__v_bo_unique(X) (const dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)(X) }

#define dpa__u_v_bo_unique__v_bo_unique(X) (X)
#define dpa__u_p_bo_unique__v_bo_unique(X) *(X)
#define dpa__u_cp_bo_unique__v_bo_unique(X) *(X)
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_unique_t dpa__u_any_bo_unique__v_bo_unique(dpa_u_any_bo_unique_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (const dpa_u_bo_unique_t){
        .bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    case DPA_U_BO_UNIQUE_HASHMAP:
      return (const dpa_u_bo_unique_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)bo,
      };
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_inline__v_bo_unique(X) (const dpa_u_bo_unique_t){ .bo_inline = (X) }
#define dpa__u_p_bo_inline__v_bo_unique(X) (const dpa_u_bo_unique_t){ .bo_inline = *(X) }
#define dpa__u_cp_bo_inline__v_bo_unique(X) (const dpa_u_bo_unique_t){ .bo_inline = *(X) }
#define dpa__u_any_bo_inline__v_bo_unique(X) (const dpa_u_bo_unique_t){ .bo_inline = *(dpa_u_bo_inline_t*)(X) }
