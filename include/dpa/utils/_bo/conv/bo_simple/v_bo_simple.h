
#define dpa_u_v_bo_simple(...) dpa_u_assert_selection(dpa_u_v_bo_simple_g((__VA_ARGS__)))
#define dpa_u_v_bo_simple_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo, v_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_inline, v_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_simple, v_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_hashed, v_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_refcounted, v_bo_simple, (X)), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__v_bo_simple(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_v_bo_inline__v_bo_simple(X) dpa_u_generic((X).all.all, \
    const char*: dpa_u_invalid_selection, \
    char*: dpa_u_rescope(const dpa_u_bo_simple_t, dpa__u_p_bo_inline__t_bo_simple_p((dpa_u_bo_inline_t*)(X).all.all)) \
  )
#define dpa__u_p_bo_inline__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, dpa__u_p_bo_inline__t_bo_simple_p((X)))
#define dpa__u_cp_bo_inline__v_bo_simple(X) dpa_u_invalid_selection
#define dpa__u_any_bo_inline__v_bo_simple(X) dpa_u_invalid_selection // opaque types are const, so dpa_u_inline data is const too.

#define dpa__u_v_bo__v_bo_simple(X) dpa_u_generic((X).all.all, \
    const char*: dpa_u_invalid_selection, \
    char*: dpa_u_rescope(const dpa_u_bo_simple_t, dpa__u_p_bo__t_bo_simple_p((dpa_u_bo_t*)(X).all.all)) \
  )
#define dpa__u_p_bo__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, dpa__u_p_bo__t_bo_simple_p((X)))
#define dpa__u_cp_bo__v_bo_simple(X) dpa_u_invalid_selection
#define dpa__u_any_bo__v_bo_simple(X) dpa_u_invalid_selection

#define dpa__u_v_bo_simple__v_bo_simple(X)   (X)
#define dpa__u_p_bo_simple__v_bo_simple(X)  *(X)
#define dpa__u_cp_bo_simple__v_bo_simple(X) *(X)
#define dpa__u_any_bo_simple__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, dpa__u_simple_fix_type(*(const dpa_u_bo_simple_t*)(X)))

#define dpa__u_v_bo_hashed__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X).bo_simple)
#define dpa__u_p_bo_hashed__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X)->bo_simple)
#define dpa__u_cp_bo_hashed__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X)->bo_simple)
#define dpa__u_any_bo_hashed__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, dpa__u_simple_fix_type(*(const dpa_u_bo_simple_t*)(X)))

#define dpa__u_v_bo_refcounted__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X).bo_simple)
#define dpa__u_p_bo_refcounted__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X)->bo_simple)
#define dpa__u_cp_bo_refcounted__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, (X)->bo_simple)
#define dpa__u_any_bo_refcounted__v_bo_simple(X)dpa_u_rescope(const dpa_u_bo_simple_t, dpa__u_simple_fix_type(*(const dpa_u_bo_simple_t*)(X)))

// Note: no conversion from dpa_u_bo_with_hash, because it's const and can be a BO_INLINE.
#define dpa__u_bo_with_refcount__v_bo_simple(X) dpa_u_rescope(const dpa_u_bo_simple_t, dpa__u_simple_fix_type(*(const dpa_u_bo_simple_t*)(X)))
