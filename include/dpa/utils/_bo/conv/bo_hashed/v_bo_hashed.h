#define dpa_u_v_bo_hashed(...) dpa_u_assert_selection(dpa_u_v_bo_hashed_g((__VA_ARGS__)))
#define dpa_u_v_bo_hashed_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo_inline, v_bo_hashed, (X)), \
    dpa__u_helper_v_g(bo_hashed, v_bo_hashed, (X)), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__v_bo_hashed(DPA__G(dpa_u_bo_with_hash_t*,(X))) \
  )

#define dpa__u_v_bo_hashed__v_bo_hashed(X)    (X)
#define dpa__u_p_bo_hashed__v_bo_hashed(X)   *(X)
#define dpa__u_cp_bo_hashed__v_bo_hashed(X)  *(X)
#define dpa__u_any_bo_hashed__v_bo_hashed(X) *(const dpa_u_bo_hashed_t*)(X)

#define dpa__u_v_bo_inline__v_bo_hashed(X)   dpa_u_rescope(const dpa_u_bo_hashed_t, dpa__u_v_bo_inline__t_bo_hashed_p((dpa_u_bo_inline_t*)(X).all.all))
#define dpa__u_p_bo_inline__v_bo_hashed(X)   dpa_u_rescope(const dpa_u_bo_hashed_t, dpa__u_v_bo_inline__t_bo_hashed_p((X)))
#define dpa__u_cp_bo_inline__v_bo_hashed(X)  dpa_u_invalid_selection
#define dpa__u_any_bo_inline__v_bo_hashed(X) dpa_u_rescope(const dpa_u_bo_hashed_t, dpa__u_v_bo_inline__t_bo_hashed_p((dpa_u_bo_inline_t*)(X)))

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_hashed_t dpa__u_bo_with_hash__v_bo_hashed_sub(dpa_u_bo_with_hash_t*const bo){
  const dpa__u_bo_meta_t meta = *(const dpa__u_bo_meta_t*)bo;
  if(meta.type == DPA_U_BO_INLINE){
    return (const dpa_u_bo_hashed_t){
      .bo_simple = {
        .type = DPA_U_BO_HASHED,
        .size = dpa__u_p_bo_inline__get_size((dpa_u_bo_inline_t*)bo),
        .data = dpa__u_p_bo_inline__data((dpa_u_bo_inline_t*)bo),
      },
      .hash = dpa__u_p_bo_inline__get_hash((dpa_u_bo_inline_t*)bo),
    };
  }else{
    // TODO: Copying the BO may be unintuitive, should we keep the object the same?
    return *(dpa_u_bo_hashed_t*)bo;
  }
}

#define dpa__u_bo_with_hash__v_bo_hashed(X)  dpa_u_rescope(const dpa_u_bo_hashed_t, (dpa__u_bo_with_hash__v_bo_hashed_sub((X))))
