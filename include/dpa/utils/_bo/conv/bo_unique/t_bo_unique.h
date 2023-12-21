#define dpa_u_t_bo_unique(...) dpa_u_assert_selection(dpa_u_t_bo_unique_g((__VA_ARGS__)))
#define dpa_u_t_bo_unique_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__t_bo_unique(DPA__G(dpa_u_bo_unique_hashmap_t, (X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__t_bo_unique(DPA__G(dpa_u_any_bo_unique_hashmap_t*, (X))), \
    dpa__u_helper_v_g(bo_unique, t_bo_unique, (X)), \
    dpa__u_helper_v_g(bo_inline, t_bo_unique, (X)) \
  )

#define dpa__u_v_bo_unique_hashmap__t_bo_unique(X) (dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (X) }
#define dpa__u_any_bo_unique_hashmap__t_bo_unique(X) (dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)(X) }

#define dpa__u_v_bo_unique__t_bo_unique(X) dpa_u_rescope(dpa_u_bo_unique_t, (X))
#define dpa__u_p_bo_unique__t_bo_unique(X) dpa_u_rescope(dpa_u_bo_unique_t, *(X))
#define dpa__u_cp_bo_unique__t_bo_unique(X) dpa_u_rescope(dpa_u_bo_unique_t, *(X))
#define dpa__u_any_bo_unique__t_bo_unique(X) dpa_u_rescope(dpa_u_bo_unique_t, dpa__u_any_bo_unique__v_bo_unique(X))

#define dpa__u_v_bo_inline__t_bo_unique(X) (dpa_u_bo_unique_t){ .bo_inline = (X) }
#define dpa__u_p_bo_inline__t_bo_unique(X) (dpa_u_bo_unique_t){ .bo_inline = *(X) }
#define dpa__u_cp_bo_inline__t_bo_unique(X) (dpa_u_bo_unique_t){ .bo_inline = *(X) }
#define dpa__u_any_bo_inline__t_bo_unique(X) (dpa_u_bo_unique_t){ .bo_inline = *(dpa_u_bo_inline_t*)(X) }
