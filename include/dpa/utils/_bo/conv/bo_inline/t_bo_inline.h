#define dpa_u_t_bo_inline(...) dpa_u_assert_selection(dpa_u_t_bo_inline_g((__VA_ARGS__)))
#define dpa_u_t_bo_inline_g(X) dpa_u_generic((X), dpa__u_helper_v_g(bo_inline, t_bo_inline, (X)))

#define dpa__u_v_bo_inline__t_bo_inline(X) dpa_u_rescope(const dpa_u_bo_inline_t, (X))
#define dpa__u_p_bo_inline__t_bo_inline(X) dpa_u_rescope(const dpa_u_bo_inline_t,*(X))
#define dpa__u_cp_bo_inline__t_bo_inline(X) dpa_u_rescope(const dpa_u_bo_inline_t,*(X))
#define dpa__u_any_bo_inline__t_bo_inline(X) dpa_u_rescope(const dpa_u_bo_inline_t,*(const dpa_u_bo_inline_t*)(X))
