#define dpa_u_v_bo_hashed(...) dpa_u_assert_selection(dpa_u_v_bo_hashed_g((__VA_ARGS__)))
#define dpa_u_v_bo_hashed_g(X) dpa_u_generic((X), dpa__u_helper_v_g(bo_hashed, v_bo_hashed, (X)))

#define dpa__u_v_bo_hashed__v_bo_hashed(X)    (X)
#define dpa__u_p_bo_hashed__v_bo_hashed(X)   *(X)
#define dpa__u_cp_bo_hashed__v_bo_hashed(X)  *(X)
#define dpa__u_any_bo_hashed__v_bo_hashed(X) *(const dpa_u_bo_hashed_t*)(X)
