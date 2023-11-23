#define dpa_u_t_bo_refcounted(...) dpa_u_assert_selection(dpa_u_t_bo_refcounted_g(__VA_ARGS__))
#define dpa_u_t_bo_refcounted_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo_refcounted, t_bo_refcounted, (X)), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__t_bo_refcounted(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_v_bo_refcounted__t_bo_refcounted(X)  (X).ro
#define dpa__u_p_bo_refcounted__t_bo_refcounted(X)  (X)->ro
#define dpa__u_cp_bo_refcounted__t_bo_refcounted(X) (X)->ro
#define dpa__u_any_bo_refcounted__t_bo_refcounted(X) (const dpa_u_bo_refcount_ro_t){ .bo_simple = { .type=DPA_U_BO_REFCOUNTED, .size=dpa__u_any_bo_refcounted__get_size((X)), .data=dpa__u_any_bo_refcounted__data((X)) }, .refcount=dpa__u_any_bo_refcounted__get_refcount((X)) }

#define dpa__u_bo_with_refcount__t_bo_refcounted(X) (const dpa_u_bo_refcount_ro_t){ .bo_simple = { .type=DPA_U_BO_REFCOUNTED, .size=dpa__u_bo_with_refcount__get_size((X)), .data=dpa__u_bo_with_refcount__data((X)) }, .refcount=dpa__u_bo_with_refcount__get_refcount((X)) }
