
#define dpa_u_v_bo_simple(...) dpa_u_assert_selection(dpa_u_v_bo_simple_g((__VA_ARGS__)))
#define dpa_u_v_bo_simple_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo_simple, v_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_hashed, v_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_refcounted, v_bo_simple, (X)), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__v_bo_simple(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_v_bo_simple__v_bo_simple(X)   (X)
#define dpa__u_p_bo_simple__v_bo_simple(X)  *(X)
#define dpa__u_cp_bo_simple__v_bo_simple(X) *(X)
#define dpa__u_any_bo_simple__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, *(const dpa_u_bo_simple_t*)(X))

#define dpa__u_v_bo_hashed__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X).bo_simple)
#define dpa__u_p_bo_hashed__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X)->bo_simple)
#define dpa__u_cp_bo_hashed__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X)->bo_simple)
#define dpa__u_any_bo_hashed__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, *(const dpa_u_bo_simple_t*)(X))

#define dpa__u_v_bo_refcounted__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X).bo_simple)
#define dpa__u_p_bo_refcounted__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X)->bo_simple)
#define dpa__u_cp_bo_refcounted__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X)->bo_simple)
#define dpa__u_any_bo_refcounted__v_bo_simple(X)dpa_u_rescope(const dpa_u_bo_simple_t, *(const dpa_u_bo_simple_t*)(X))

#define dpa__u_bo_with_refcount__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, *(const dpa_u_bo_simple_t*)(X))
