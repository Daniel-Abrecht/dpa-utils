
#define dpa_u_p_any_bo_ro(...) dpa_u_assert_selection(dpa_u_p_any_bo_ro_g(__VA_ARGS__))
#define dpa_u_p_any_bo_ro_g(X) dpa_u_generic_if_selection(dpa_u_bo_ptr_g(X), (dpa_u_any_bo_ro_t*)dpa_u_bo_ptr((X)))
