#define dpa_u_t_bo_unique_hashmap(...) dpa_u_assert_selection(dpa_u_t_bo_unique_hashmap_g((__VA_ARGS__)))
#define dpa_u_tp_bo_unique_hashmap(...) dpa_u_assert_selection(dpa_u_t_bo_unique_hashmap_g((__VA_ARGS__)))
#define dpa_u_t_bo_unique_hashmap_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__t_bo_unique_hashmap(DPA__G(dpa_u_bo_unique_hashmap_t, (X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_v_any_bo_unique_hashmap__t_bo_unique_hashmap(DPA__G(dpa_u_any_bo_unique_hashmap_t*, (X))) \
  )

#define dpa__u_v_bo_unique_hashmap__t_bo_unique_hashmap(X)     (dpa_u_bo_unique_hashmap_t){(X)}
#define dpa__u_p_bo_unique_hashmap__t_bo_unique_hashmap(X)     (dpa_u_bo_unique_hashmap_t){(X)}
#define dpa__u_cp_bo_unique_hashmap__t_bo_unique_hashmap(X)    (dpa_u_bo_unique_hashmap_t){(X)}
#define dpa__u_v_any_bo_unique_hashmap__t_bo_unique_hashmap(X) (dpa_u_bo_unique_hashmap_t){(dpa_u_bo_unique_hashmap_t)(X)}
