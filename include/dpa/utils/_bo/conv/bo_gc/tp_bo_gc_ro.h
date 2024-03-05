#define dpa_u_tp_bo_gc_ro(...) dpa_u_assert_selection(dpa_u_tp_bo_gc_ro_g((__VA_ARGS__)))
#define dpa_u_tp_bo_gc_ro_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__tp_bo_gc_ro(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__tp_bo_gc_ro((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*, (X))), \
    dpa__u_helper_v_g(bo_inline, tp_bo_gc_ro, (X)), \
    dpa__u_helper_v_g(bo_unique, tp_bo_gc_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted_ro, tp_bo_gc_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted, tp_bo_gc_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, tp_bo_gc_ro, (X)), \
    dpa_u_bo_gc_ro_t*: dpa__u_bo_gc_ro__tp_bo_gc_ro(DPA__G(dpa_u_bo_gc_ro_t*,(X))), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__tp_bo_gc_ro(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount_ro__tp_bo_gc_ro(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__tp_bo_gc_ro(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_v_bo_unique_hashmap__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_v_bo_unique_hashmap__tp_any_bo_refcounted_ro((X)))
#define dpa__u_any_bo_unique_hashmap__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_any_bo_unique_hashmap__tp_any_bo_refcounted_ro((X)))

#define dpa__u_v_bo_inline__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)&dpa_u_rescope(dpa_u_bo_inline_t, (X)))
#define dpa__u_p_bo_inline__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)&dpa_u_rescope(dpa_u_bo_inline_t,*(X)))
#define dpa__u_cp_bo_inline__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)&dpa_u_rescope(dpa_u_bo_inline_t,*(X)))
#define dpa__u_any_bo_inline__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)&dpa_u_rescope(dpa_u_bo_inline_t,*(const dpa_u_bo_inline_t*)(X)))

#define dpa__u_v_bo_unique__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_v_bo_unique__tp_any_bo_unique(X))
#define dpa__u_p_bo_unique__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_p_bo_unique__tp_any_bo_unique(X))
#define dpa__u_cp_bo_unique__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_cp_bo_unique__tp_any_bo_unique(X))
#define dpa__u_any_bo_unique__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_any_bo_unique__tp_any_bo_unique(X))

#define dpa__u_v_bo_refcounted_ro__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_v_bo_refcounted_ro__tp_any_bo_refcounted_ro((X)))
#define dpa__u_p_bo_refcounted_ro__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_p_bo_refcounted_ro__tp_any_bo_refcounted_ro((X)))
#define dpa__u_cp_bo_refcounted_ro__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_cp_bo_refcounted_ro__tp_any_bo_refcounted_ro((X)))
#define dpa__u_any_bo_refcounted_ro__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_any_bo_refcounted_ro__tp_any_bo_refcounted_ro((X)))

#define dpa__u_v_bo_refcounted__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_v_bo_refcounted__tp_any_bo_refcounted_ro((X)))
#define dpa__u_p_bo_refcounted__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_p_bo_refcounted__tp_any_bo_refcounted_ro((X)))
#define dpa__u_cp_bo_refcounted__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_cp_bo_refcounted__tp_any_bo_refcounted_ro((X)))
#define dpa__u_any_bo_refcounted__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_any_bo_refcounted__tp_any_bo_refcounted_ro((X)))

#define dpa__u_v_bo_refcounted_hashed_ro__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_v_bo_refcounted_hashed_ro__tp_any_bo_refcounted_ro((X)))
#define dpa__u_p_bo_refcounted_hashed_ro__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_p_bo_refcounted_hashed_ro__tp_any_bo_refcounted_ro((X)))
#define dpa__u_cp_bo_refcounted_hashed_ro__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_cp_bo_refcounted_hashed_ro__tp_any_bo_refcounted_ro((X)))
#define dpa__u_any_bo_refcounted_hashed_ro__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_any_bo_refcounted_hashed_ro__tp_any_bo_refcounted_ro((X)))

#define dpa__u_bo_with_refcount_and_hash_ro__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_bo_with_refcount_and_hash_ro__tp_any_bo_refcounted_ro((X)))
#define dpa__u_bo_with_refcount_ro__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_bo_with_refcount_ro__tp_any_bo_refcounted_ro((X)))
#define dpa__u_bo_with_refcount__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_bo_with_refcount__tp_any_bo_refcounted_ro((X)))

#define dpa__u_bo_gc_ro__tp_bo_gc_ro(X) ((dpa_u_bo_gc_ro_t*)dpa__u_bo_gc_ro__tp_any_bo_ro(X))
