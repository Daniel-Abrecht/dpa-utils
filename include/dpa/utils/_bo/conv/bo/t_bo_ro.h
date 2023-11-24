#define dpa_u_t_bo_ro(...) dpa_u_assert_selection(dpa_u_t_bo_ro_g(__VA_ARGS__))
#define dpa_u_t_bo_ro_g(X) dpa_u_generic((X),dpa__u_helper_all_g(t_bo_ro,(X)))

#define dpa__u_t_bo_ro__helper(P,X) (const dpa_u_bo_ro_t){ .bo_simple = { .type = DPA_U_BO_SIMPLE, .size=dpa__u_ ## P ## __get_size((X)), .data=dpa__u_ ## P ## __data((X)) } }

#define dpa__u_v_bo__t_bo_ro(X) (X).ro
#define dpa__u_p_bo__t_bo_ro(X) (X)->ro
#define dpa__u_cp_bo__t_bo_ro(X) (X)->ro
#define dpa__u_any_bo__t_bo_ro(X) (X)->ro

#define dpa__u_v_bo_ro__t_bo_ro(X) (X)
#define dpa__u_p_bo_ro__t_bo_ro(X) (X)[0]
#define dpa__u_cp_bo_ro__t_bo_ro(X) (X)[0]
#define dpa__u_any_bo_ro__t_bo_ro(X) dpa__u_any_bo_ro__v_bo_ro(X)

#define dpa__u_v_bo_inline__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_inline = (X) }
#define dpa__u_p_bo_inline__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_inline = *(X) }
#define dpa__u_cp_bo_inline__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_inline = *(X) }
#define dpa__u_any_bo_inline__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_inline = *(const dpa_u_bo_inline_t*)(X) }

#define dpa__u_v_bo_simple__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = (X).ro }
#define dpa__u_p_bo_simple__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = (X)->ro }
#define dpa__u_cp_bo_simple__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = (X)->ro }
#define dpa__u_any_bo_simple__t_bo_ro(X) dpa__u_t_bo_ro__helper(any_bo_simple,(X))

#define dpa__u_v_bo_simple_ro__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = (X) }
#define dpa__u_p_bo_simple_ro__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = *(X) }
#define dpa__u_cp_bo_simple_ro__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = *(X) }
#define dpa__u_any_bo_simple_ro__t_bo_ro(X) dpa__u_any_bo_simple_ro__v_bo_ro(X)

#define dpa__u_v_bo_unique_hashmap__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (X) }
#define dpa__u_p_bo_unique_hashmap__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (X) }
#define dpa__u_cp_bo_unique_hashmap__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (X) }
#define dpa__u_any_bo_unique_hashmap__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)(X) }

#define dpa__u_v_bo_unique__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique = (X) }
#define dpa__u_p_bo_unique__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique = *(X) }
#define dpa__u_cp_bo_unique__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique = *(X) }
#define dpa__u_any_bo_unique__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique = *(const dpa_u_bo_unique_t*)(X) }

#define dpa__u_v_bo_hashed__t_bo_ro(X) dpa__u_t_bo_ro__helper(v_bo_hashed,(X))
#define dpa__u_p_bo_hashed__t_bo_ro(X) dpa__u_t_bo_ro__helper(p_bo_hashed,(X))
#define dpa__u_cp_bo_hashed__t_bo_ro(X) dpa__u_t_bo_ro__helper(cp_bo_hashed,(X))
#define dpa__u_any_bo_hashed__t_bo_ro(X) dpa__u_t_bo_ro__helper(any_bo_hashed,(X))

#define dpa__u_v_bo_hashed_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(v_bo_hashed_ro,(X))
#define dpa__u_p_bo_hashed_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(p_bo_hashed_ro,(X))
#define dpa__u_cp_bo_hashed_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(cp_bo_hashed_ro,(X))
#define dpa__u_any_bo_hashed_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(any_bo_hashed_ro,(X))

#define dpa__u_v_bo_refcounted__t_bo_ro(X) dpa__u_t_bo_ro__helper(v_bo_refcounted,(X))
#define dpa__u_p_bo_refcounted__t_bo_ro(X) dpa__u_t_bo_ro__helper(p_bo_refcounted,(X))
#define dpa__u_cp_bo_refcounted__t_bo_ro(X) dpa__u_t_bo_ro__helper(cp_bo_refcounted,(X))
#define dpa__u_any_bo_refcounted__t_bo_ro(X) dpa__u_t_bo_ro__helper(any_bo_refcounted,(X))

#define dpa__u_v_bo_refcounted_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(v_bo_refcounted_ro,(X))
#define dpa__u_p_bo_refcounted_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(p_bo_refcounted_ro,(X))
#define dpa__u_cp_bo_refcounted_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(cp_bo_refcounted_ro,(X))
#define dpa__u_any_bo_refcounted_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(any_bo_refcounted_ro,(X))

#define dpa__u_v_bo_refcounted_hashed_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(v_bo_refcounted_hashed_ro,(X))
#define dpa__u_p_bo_refcounted_hashed_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(p_bo_refcounted_hashed_ro,(X))
#define dpa__u_cp_bo_refcounted_hashed_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(cp_bo_refcounted_hashed_ro,(X))
#define dpa__u_any_bo_refcounted_hashed_ro__t_bo_ro(X) dpa__u_t_bo_ro__helper(any_bo_refcounted_hashed_ro,(X))

#define dpa__u_bo_gc_ro__t_bo_ro(X) dpa__u_bo_gc_ro__v_bo_ro(X)
#define dpa__u_bo_with_hash_ro__t_bo_ro(X) dpa__u_bo_with_hash_ro__v_bo_ro(X)
#define dpa__u_bo_with_hash__t_bo_ro(X) dpa__u_bo_with_hash__v_bo_ro(X)
#define dpa__u_bo_with_refcount_ro__t_bo_ro(X) dpa__u_bo_with_refcount_ro__t_bo_ro(X)
#define dpa__u_bo_with_refcount__t_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = { .type=DPA_U_BO_SIMPLE, .size=dpa__u_any_bo_refcounted_hashed_ro__get_size((X)), .data=dpa__u_any_bo_refcounted_hashed_ro__data((X)) } }
#define dpa__u_bo_with_refcount_and_hash_ro__t_bo_ro(X) dpa__u_bo_with_refcount_and_hash_ro__t_bo_ro(X)
