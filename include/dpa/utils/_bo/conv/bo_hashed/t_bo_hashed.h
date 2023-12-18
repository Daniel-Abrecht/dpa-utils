#define dpa_u_t_bo_hashed(...) dpa_u_assert_selection(dpa_u_t_bo_hashed_g((__VA_ARGS__)))
#define dpa_u_t_bo_hashed_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo_inline, t_bo_hashed, (X)), \
    dpa__u_helper_v_g(bo_hashed, t_bo_hashed, (X)), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__t_bo_hashed(DPA__G(dpa_u_bo_with_hash_t*,(X))) \
  )

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_hashed_t dpa__u_v_bo_inline__t_bo_hashed_p(dpa_u_bo_inline_t*const bo){
  return (const dpa_u_bo_hashed_t){
    .bo_simple = {
      .type = DPA_U_BO_HASHED,
      .size = dpa__u_p_bo_inline__get_size(bo),
      .data = dpa__u_p_bo_inline__data(bo),
    },
    .hash = dpa__u_p_bo_inline__get_hash(bo),
  };
}
#define dpa__u_v_bo_inline__t_bo_hashed(X)   dpa_u_rescope(dpa_u_bo_hashed_t, dpa__u_v_bo_inline__t_bo_hashed_p(&dpa_u_rescope(dpa_u_bo_inline_t, (X))))
#define dpa__u_p_bo_inline__t_bo_hashed(X)   dpa__u_v_bo_inline__t_bo_hashed(*(X))
#define dpa__u_cp_bo_inline__t_bo_hashed(X)  dpa__u_v_bo_inline__t_bo_hashed(*(X))
#define dpa__u_any_bo_inline__t_bo_hashed(X) dpa__u_v_bo_inline__t_bo_hashed(*(const dpa_u_bo_inline_t*)(X))

#define dpa__u_v_bo_hashed__t_bo_hashed(X)   dpa_u_rescope(dpa_u_bo_hashed_t, (X))
#define dpa__u_p_bo_hashed__t_bo_hashed(X)   dpa_u_rescope(dpa_u_bo_hashed_t, *(X))
#define dpa__u_cp_bo_hashed__t_bo_hashed(X)  dpa_u_rescope(dpa_u_bo_hashed_t, *(X))
#define dpa__u_any_bo_hashed__t_bo_hashed(X) dpa_u_rescope(dpa_u_bo_hashed_t, *(const dpa_u_bo_hashed_t*)(X))

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_hashed_t dpa__u_bo_with_hash__t_bo_hashed_2_p(union dpa__u_hashed_conv_helper*const bo){
  if(bo->meta.type != DPA_U_BO_INLINE){
    return bo->bo_hashed;
  }else{
    return (const dpa_u_bo_hashed_t){
      .bo_simple = {
        .type = DPA_U_BO_HASHED,
        .size = dpa__u_v_bo_inline__get_size(bo->bo_inline),
        .data = dpa__u_v_bo_inline__data(bo->bo_inline),
      },
      .hash = dpa__u_v_bo_inline__get_hash(bo->bo_inline),
    };
  }
}
#define dpa__u_bo_with_hash__t_bo_hashed(X) dpa_u_rescope(dpa_u_bo_hashed_t,dpa__u_bo_with_hash__t_bo_hashed_2_p(&dpa_u_rescope(union dpa__u_hashed_conv_helper,dpa__u_bo_with_hash__t_bo_hashed_1_p(X))))
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline union dpa__u_hashed_conv_helper dpa__u_bo_with_hash__t_bo_hashed_1_p(const dpa_u_bo_with_hash_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (const union dpa__u_hashed_conv_helper){
        .bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    case DPA_U_BO_HASHED:
      return (const union dpa__u_hashed_conv_helper){
        .bo_hashed = *(const dpa_u_bo_hashed_t*)bo,
      };
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
