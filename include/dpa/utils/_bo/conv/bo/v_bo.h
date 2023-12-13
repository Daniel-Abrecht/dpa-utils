#define dpa_u_v_bo(...) dpa_u_assert_selection(dpa_u_v_bo_g((__VA_ARGS__)))
#define dpa_u_v_bo_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo, v_bo, (X)), \
    dpa__u_helper_v_g(bo_inline, v_bo, (X)), \
    dpa__u_helper_v_g(bo_simple, v_bo, (X)), \
    dpa__u_helper_v_g(bo_hashed, v_bo, (X)), \
    dpa__u_helper_v_g(bo_refcounted, v_bo, (X)), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__v_bo(DPA__G(dpa_u_bo_with_hash_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__v_bo(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_v_bo__v_bo(X) (X)
#define dpa__u_p_bo__v_bo(X) *(X)
#define dpa__u_cp_bo__v_bo(X) *(X)
#define dpa__u_any_bo__v_bo(X) dpa__u_any_bo__t_bo(X)

#define dpa__u_v_bo_inline__v_bo(X) _Generic((X).all, char*: *(dpa_u_bo_t*)(X).all, const char*: *(const dpa_u_bo_t*)(X).all)
#define dpa__u_p_bo_inline__v_bo(X) (*(dpa_u_bo_t*)(X))
#define dpa__u_cp_bo_inline__v_bo(X) (*(const dpa_u_bo_t*)(X))
#define dpa__u_any_bo_inline__v_bo(X) (const dpa_u_bo_t){ .bo_inline = *(const dpa_u_bo_inline_t*)(X) }

#define dpa__u_v_bo_simple__v_bo(X) _Generic((X).all, char*: *(dpa_u_bo_t*)(X).all, const char*: *(const dpa_u_bo_t*)(X).all)
#define dpa__u_p_bo_simple__v_bo(X) (*(dpa_u_bo_t*)(X))
#define dpa__u_cp_bo_simple__v_bo(X) (*(const dpa_u_bo_t*)(X))
#define dpa__u_any_bo_simple__v_bo(X) dpa__u_t_bo__helper_s1(X)

#define dpa__u_v_bo_hashed__v_bo(X) dpa__u_t_bo__helper_s1(X)
#define dpa__u_p_bo_hashed__v_bo(X) dpa__u_t_bo__helper_s1(X)
#define dpa__u_cp_bo_hashed__v_bo(X) dpa__u_t_bo__helper_s1(X)
#define dpa__u_any_bo_hashed__v_bo(X) dpa__u_t_bo__helper_s1(X)

#define dpa__u_v_bo_refcounted__v_bo(X) dpa__u_t_bo__helper_s1(X)
#define dpa__u_p_bo_refcounted__v_bo(X) dpa__u_t_bo__helper_s1(X)
#define dpa__u_cp_bo_refcounted__v_bo(X) dpa__u_t_bo__helper_s1(X)
#define dpa__u_any_bo_refcounted__v_bo(X) dpa__u_t_bo__helper_s1(X)

#define dpa__u_bo_with_hash__v_bo(X) dpa__u_bo_with_hash__t_bo(X)
#define dpa__u_bo_with_refcount__v_bo(X) dpa__u_t_bo__helper_s1(*(const dpa_u_bo_simple_t*)(X))
