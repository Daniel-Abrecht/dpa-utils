#define dpa_u_v_bo_hashed(...) dpa_u_assert_selection(dpa_u_v_bo_hashed_g((__VA_ARGS__)))
#define dpa_u_v_bo_hashed_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo_inline, v_bo_hashed, (X)), \
    dpa__u_helper_v_g(bo_hashed, v_bo_hashed, (X)) \
  )

#define dpa__u_v_bo_hashed__v_bo_hashed(X)    (X)
#define dpa__u_p_bo_hashed__v_bo_hashed(X)   *(X)
#define dpa__u_cp_bo_hashed__v_bo_hashed(X)  *(X)
#define dpa__u_any_bo_hashed__v_bo_hashed(X) *(const dpa_u_bo_hashed_t*)(X)

// The pointer to the data of a const dpa_u_bo_inline_t will be const, but dpa_u_bo_hashed needs to point to modifyable data.
#define dpa__u_v_bo_inline__v_bo_hashed(X) dpa_u_generic((X).all.all, \
    const char*: dpa_u_invalid_selection, \
    char*: dpa_u_rescope(const dpa_u_bo_hashed_t, dpa__u_v_bo_inline__t_bo_hashed_p((dpa_u_bo_inline_t*)(X).all.all)) \
  )
#define dpa__u_p_bo_inline__v_bo_hashed(X)   dpa_u_rescope(const dpa_u_bo_hashed_t, dpa__u_v_bo_inline__t_bo_hashed_p((X)))
#define dpa__u_cp_bo_inline__v_bo_hashed(X)  dpa_u_invalid_selection
#define dpa__u_any_bo_inline__v_bo_hashed(X) dpa_u_rescope(const dpa_u_bo_hashed_t, dpa__u_v_bo_inline__t_bo_hashed_p((dpa_u_bo_inline_t*)(X)))

// Note: no conversion from dpa_u_bo_with_hash, because it's const and can be a BO_INLINE.
