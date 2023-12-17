#define dpa_u_t_bo_simple(...) dpa_u_assert_selection(dpa_u_t_bo_simple_g((__VA_ARGS__)))
#define dpa_u_t_bo_simple_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo, t_bo_simple, (X)), \
    /*dpa__u_helper_v_g(bo_inline, t_bo_simple, (X)),*/ \
    dpa__u_helper_v_g(bo_simple, t_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_hashed, t_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_refcounted, t_bo_simple, (X)), \
    /*dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__t_bo_simple(DPA__G(dpa_u_bo_with_hash_t*,(X))),*/ \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__t_bo_simple(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_t_bo_simple__helper(P,X) (dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa__u_ ## P ## __get_size((X)), .data=dpa__u_ ## P ## __data((X)) }

#define dpa__u_v_bo_inline__t_bo_simple(X) dpa__u_t_bo_simple__helper(v_bo_inline,(X))
#define dpa__u_p_bo_inline__t_bo_simple(X) dpa__u_t_bo_simple__helper(p_bo_inline,(X))
#define dpa__u_cp_bo_inline__t_bo_simple(X) dpa__u_t_bo_simple__helper(cp_bo_inline,(X))
#define dpa__u_any_bo_inline__t_bo_simple(X) dpa__u_t_bo_simple__helper(any_bo_inline,(X))

#define dpa__u_v_bo_simple__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t, (X))
#define dpa__u_p_bo_simple__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t, *(X))
#define dpa__u_cp_bo_simple__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t, *(X))
#define dpa__u_any_bo_simple__t_bo_simple(X) dpa__u_t_bo_simple__helper(any_bo_simple,(X))

#define dpa__u_v_bo_hashed__t_bo_simple(X) dpa__u_t_bo_simple__helper(v_bo_hashed,(X))
#define dpa__u_p_bo_hashed__t_bo_simple(X) dpa__u_t_bo_simple__helper(p_bo_hashed,(X))
#define dpa__u_cp_bo_hashed__t_bo_simple(X) dpa__u_t_bo_simple__helper(cp_bo_hashed,(X))
#define dpa__u_any_bo_hashed__t_bo_simple(X) dpa__u_t_bo_simple__helper(any_bo_hashed,(X))

#define dpa__u_v_bo_refcounted__t_bo_simple(X) dpa__u_t_bo_simple__helper(v_bo_refcounted,(X))
#define dpa__u_p_bo_refcounted__t_bo_simple(X) dpa__u_t_bo_simple__helper(p_bo_refcounted,(X))
#define dpa__u_cp_bo_refcounted__t_bo_simple(X) dpa__u_t_bo_simple__helper(cp_bo_refcounted,(X))
#define dpa__u_any_bo_refcounted__t_bo_simple(X) dpa__u_t_bo_simple__helper(any_bo_refcounted,(X))

#define dpa__u_v_bo__t_bo_simple(X) dpa__u_t_bo_simple__helper(v_bo,dpa_u_rescope(dpa_u_bo_t,(X)))
#define dpa__u_p_bo__t_bo_simple(X) dpa__u_v_bo__t_bo_simple(*(X))
#define dpa__u_cp_bo__t_bo_simple(X) dpa__u_v_bo__t_bo_simple(*(X))
#define dpa__u_any_bo__t_bo_simple(X) dpa__u_v_bo__t_bo_simple(*(dpa_u_bo_t*)(X)) // FIXME

#define dpa__u_bo_with_hash__t_bo_simple(X) dpa__u_t_bo_simple__helper(bo_with_hash,(X))
#define dpa__u_bo_with_refcount__t_bo_simple(X) dpa__u_t_bo_simple__helper(bo_with_refcount,(X))
