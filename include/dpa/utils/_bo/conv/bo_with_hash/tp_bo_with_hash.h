#define dpa_u_tp_bo_with_hash(...) dpa_u_assert_selection(dpa_u_tp_bo_with_hash_g((__VA_ARGS__)))
#define dpa_u_tp_bo_with_hash_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo_inline, tp_bo_with_hash, (X)), \
    dpa__u_helper_v_g(bo_hashed, tp_bo_with_hash, (X)), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__tp_bo_with_hash(DPA__G(dpa_u_bo_with_hash_t*,(X))) \
  )

#define dpa__u_v_bo_hashed__tp_bo_with_hash(X) ((dpa_u_bo_with_hash_t*)&dpa_u_rescope(dpa_u_bo_hashed_ro_t,(X).ro))
#define dpa__u_p_bo_hashed__tp_bo_with_hash(X) ((dpa_u_bo_with_hash_t*)&dpa_u_rescope(dpa_u_bo_hashed_ro_t,(X)->ro))
#define dpa__u_cp_bo_hashed__tp_bo_with_hash(X) ((dpa_u_bo_with_hash_t*)&dpa_u_rescope(dpa_u_bo_hashed_ro_t,(X)->ro))
#define dpa__u_any_bo_hashed__tp_bo_with_hash(X) ((dpa_u_bo_with_hash_t*)&dpa_u_rescope(dpa_u_bo_hashed_ro_t,*(dpa_u_bo_hashed_ro_t*)(X)))

#define dpa__u_v_bo_inline__tp_bo_with_hash(X) ((dpa_u_bo_with_hash_t*)&dpa_u_rescope(dpa_u_bo_inline_t,(X)))
#define dpa__u_p_bo_inline__tp_bo_with_hash(X) ((dpa_u_bo_with_hash_t*)&dpa_u_rescope(dpa_u_bo_inline_t,*(X)))
#define dpa__u_cp_bo_inline__tp_bo_with_hash(X) ((dpa_u_bo_with_hash_t*)&dpa_u_rescope(dpa_u_bo_inline_t,*(X)))
#define dpa__u_any_bo_inline__tp_bo_with_hash(X) ((dpa_u_bo_with_hash_t*)&dpa_u_rescope(dpa_u_bo_inline_t,*(dpa_u_bo_inline_t*)(X)))

#define dpa__u_bo_with_hash__tp_bo_with_hash(X) ((dpa_u_bo_with_hash_t*)dpa__u_bo_with_hash__tp_any_bo_ro(X))

