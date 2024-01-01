#define dpa_u_tp_any_bo_ro(...) dpa_u_assert_selection(dpa_u_tp_any_bo_ro_g((__VA_ARGS__)))
#define dpa_u_tp_any_bo_ro_g(X) dpa_u_generic((X),dpa__u_helper_all_g(tp_any_bo_ro,(X)))

#define dpa__u_tp_any_bo_ro__helper_s1(X) (dpa_u_bo_ro_t){ .bo_simple = dpa__u_simple_ro_fix_type((X)) }

#define dpa__u_v_bo__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_ro_t,(X).ro))
#define dpa__u_p_bo__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_ro_t,(X)->ro))
#define dpa__u_cp_bo__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_ro_t,(X)->ro))
#define dpa__u_any_bo__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO

#define dpa__u_v_bo_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)dpa__u_v_bo_ro__ptr(dpa_u_rescope(dpa_u_bo_ro_t,(X))))
#define dpa__u_p_bo_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)dpa__u_v_bo_ro__ptr(dpa_u_rescope(dpa_u_bo_ro_t,*(X))))
#define dpa__u_cp_bo_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)dpa__u_v_bo_ro__ptr(dpa_u_rescope(dpa_u_bo_ro_t,*(X))))
#define dpa__u_any_bo_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO

#define dpa__u_v_bo_inline__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&(dpa_u_bo_ro_t){ .bo_inline = (X) })
#define dpa__u_p_bo_inline__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&(dpa_u_bo_ro_t){ .bo_inline = *(X) })
#define dpa__u_cp_bo_inline__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&(dpa_u_bo_ro_t){ .bo_inline = *(X) })
#define dpa__u_any_bo_inline__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&(dpa_u_bo_ro_t){ .bo_inline = *(const dpa_u_bo_inline_t*)(X) })

#define dpa__u_v_bo_simple__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&(dpa_u_bo_ro_t){ .bo_simple = (X).ro })
#define dpa__u_p_bo_simple__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&(dpa_u_bo_ro_t){ .bo_simple = (X)->ro })
#define dpa__u_cp_bo_simple__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&(dpa_u_bo_ro_t){ .bo_simple = (X)->ro })
#define dpa__u_any_bo_simple__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO

#define dpa__u_v_bo_simple_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&(dpa_u_bo_ro_t){ .bo_simple = (X) })
#define dpa__u_p_bo_simple_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&(dpa_u_bo_ro_t){ .bo_simple = *(X) })
#define dpa__u_cp_bo_simple_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&(dpa_u_bo_ro_t){ .bo_simple = *(X) })
#define dpa__u_any_bo_simple_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO

#define dpa__u_v_bo_unique_hashmap__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*){(dpa_u_any_bo_ro_t*)(X)})
#define dpa__u_p_bo_unique_hashmap__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*){(dpa_u_any_bo_ro_t*)(X)})
#define dpa__u_cp_bo_unique_hashmap__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*){(dpa_u_any_bo_ro_t*)(X)})
#define dpa__u_any_bo_unique_hashmap__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*){(dpa_u_any_bo_ro_t*)(X)})

#define dpa__u_v_bo_unique__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)dpa__u_v_bo_unique__tp_any_bo_unique(X))
#define dpa__u_p_bo_unique__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)dpa__u_p_bo_unique__tp_any_bo_unique(X))
#define dpa__u_cp_bo_unique__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)dpa__u_cp_bo_unique__tp_any_bo_unique(X))
#define dpa__u_any_bo_unique__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)dpa__u_any_bo_unique__tp_any_bo_unique(X))

#define dpa__u_v_bo_hashed__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_hashed_t,(X)))
#define dpa__u_p_bo_hashed__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_hashed_t,*(X)))
#define dpa__u_cp_bo_hashed__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_hashed_t,*(X)))
#define dpa__u_any_bo_hashed__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_hashed_t,*(dpa_u_bo_hashed_t*)(X)))

#define dpa__u_v_bo_hashed_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_hashed_ro_t,(X)))
#define dpa__u_p_bo_hashed_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_hashed_ro_t,*(X)))
#define dpa__u_cp_bo_hashed_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_hashed_ro_t,*(X)))
#define dpa__u_any_bo_hashed_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO

#define dpa__u_v_bo_refcounted__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)(&dpa_u_rescope(dpa_u_bo_refcounted_t, (X)).bo_simple.ro))
#define dpa__u_p_bo_refcounted__tp_any_bo_ro(X) dpa__u_v_bo_refcounted__tp_any_bo_ro(*(X))
#define dpa__u_cp_bo_refcounted__tp_any_bo_ro(X) dpa__u_v_bo_refcounted__tp_any_bo_ro(*(X))
#define dpa__u_any_bo_refcounted__tp_any_bo_ro(X) dpa__u_cp_bo_refcounted__tp_any_bo_ro((const dpa_u_bo_refcounted_t*)(X))

#define dpa__u_v_bo_refcounted_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_ro_t,(X)))
#define dpa__u_p_bo_refcounted_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_ro_t,*(X)))
#define dpa__u_cp_bo_refcounted_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_ro_t,*(X)))
#define dpa__u_any_bo_refcounted_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO

#define dpa__u_v_bo_refcounted_hashed_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t,(X)))
#define dpa__u_p_bo_refcounted_hashed_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t,*(X)))
#define dpa__u_cp_bo_refcounted_hashed_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t,*(X)))
#define dpa__u_any_bo_refcounted_hashed_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO

#define dpa__u_bo_gc_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO
#define dpa__u_bo_with_hash_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO
#define dpa__u_bo_with_hash__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO
#define dpa__u_bo_with_refcount_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO
#define dpa__u_bo_with_refcount__tp_any_bo_ro(X) dpa__u_any_bo_refcounted__tp_any_bo_ro((X))
#define dpa__u_bo_with_refcount_and_hash_ro__tp_any_bo_ro(X) ((dpa_u_any_bo_ro_t*)0) // TODO
