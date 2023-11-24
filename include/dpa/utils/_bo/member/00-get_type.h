
#define dpa_u_bo_get_type(...) dpa_u_assert_selection(dpa_u_bo_get_type_g(__VA_ARGS__))
#define dpa_u_bo_get_type_g(X) dpa_u_generic((X),dpa__u_helper_all_g(get_type,(X)))

#define dpa__u_v_bo_unique_hashmap__get_type(X)   DPA_U_BO_UNIQUE_HASHMAP_3
#define dpa__u_p_bo_unique_hashmap__get_type(X)   DPA_U_BO_UNIQUE_HASHMAP_3
#define dpa__u_cp_bo_unique_hashmap__get_type(X)  DPA_U_BO_UNIQUE_HASHMAP_3
#define dpa__u_any_bo_unique_hashmap__get_type(X) DPA_U_BO_UNIQUE_HASHMAP_A3

#define dpa__u_v_bo_inline__get_type(X)   DPA_U_BO_INLINE_1
#define dpa__u_p_bo_inline__get_type(X)   DPA_U_BO_INLINE_1
#define dpa__u_cp_bo_inline__get_type(X)  DPA_U_BO_INLINE_1
#define dpa__u_any_bo_inline__get_type(X) DPA_U_BO_INLINE_A1

#define dpa__u_v_bo_simple__get_type(X)   DPA_U_BO_SIMPLE_2
#define dpa__u_p_bo_simple__get_type(X)   DPA_U_BO_SIMPLE_2
#define dpa__u_cp_bo_simple__get_type(X)  DPA_U_BO_SIMPLE_2
#define dpa__u_any_bo_simple__get_type(X) ((enum dpa_u_any_bo_simple_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_simple_ro__get_type(X)   DPA_U_BO_SIMPLE_4
#define dpa__u_p_bo_simple_ro__get_type(X)   DPA_U_BO_SIMPLE_4
#define dpa__u_cp_bo_simple_ro__get_type(X)  DPA_U_BO_SIMPLE_4
#define dpa__u_any_bo_simple_ro__get_type(X) ((enum dpa_u_any_bo_simple_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_unique__get_type(X)   ((enum dpa_u_bo_unique_type)((X).type))
#define dpa__u_p_bo_unique__get_type(X)   ((enum dpa_u_bo_unique_type)((X)->type))
#define dpa__u_cp_bo_unique__get_type(X)  ((enum dpa_u_bo_unique_type)((X)->type))
#define dpa__u_any_bo_unique__get_type(X) ((enum dpa_u_any_bo_unique_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo__get_type(X)   ((enum dpa_u_bo_type)((X).type))
#define dpa__u_p_bo__get_type(X)   ((enum dpa_u_bo_type)((X)->type))
#define dpa__u_cp_bo__get_type(X)  ((enum dpa_u_bo_type)((X)->type))
#define dpa__u_any_bo__get_type(X) ((enum dpa_u_any_bo_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_ro__get_type(X)   ((enum dpa_u_bo_ro_type)((X).type))
#define dpa__u_p_bo_ro__get_type(X)   ((enum dpa_u_bo_ro_type)((X)->type))
#define dpa__u_cp_bo_ro__get_type(X)  ((enum dpa_u_bo_ro_type)((X)->type))
#define dpa__u_any_bo_ro__get_type(X) ((enum dpa_u_any_bo_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_hashed_ro__get_type(X)   DPA_U_BO_HASHED_6
#define dpa__u_p_bo_hashed_ro__get_type(X)   DPA_U_BO_HASHED_6
#define dpa__u_cp_bo_hashed_ro__get_type(X)  DPA_U_BO_HASHED_6
#define dpa__u_any_bo_hashed_ro__get_type(X) ((enum dpa_u_any_bo_hashed_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_hashed__get_type(X)   DPA_U_BO_HASHED_5
#define dpa__u_p_bo_hashed__get_type(X)   DPA_U_BO_HASHED_5
#define dpa__u_cp_bo_hashed__get_type(X)  DPA_U_BO_HASHED_5
#define dpa__u_any_bo_hashed__get_type(X) ((enum dpa_u_any_bo_hashed_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_refcounted__get_type(X)   DPA_U_BO_REFCOUNTED_7
#define dpa__u_p_bo_refcounted__get_type(X)   DPA_U_BO_REFCOUNTED_7
#define dpa__u_cp_bo_refcounted__get_type(X)  DPA_U_BO_REFCOUNTED_7
#define dpa__u_any_bo_refcounted__get_type(X) ((enum dpa_u_any_bo_refcounted_type)(((const dpa_u_bo_refcounted_t*)(X))->type))

#define dpa__u_v_bo_refcounted_ro__get_type(X)   DPA_U_BO_REFCOUNTED_8
#define dpa__u_p_bo_refcounted_ro__get_type(X)   DPA_U_BO_REFCOUNTED_8
#define dpa__u_cp_bo_refcounted_ro__get_type(X)  DPA_U_BO_REFCOUNTED_8
#define dpa__u_any_bo_refcounted_ro__get_type(X) ((enum dpa_u_any_bo_refcounted_ro_type)(((const dpa_u_bo_refcounted_ro_t*)(X))->type))

#define dpa__u_v_bo_refcounted_hashed_ro__get_type(X)   DPA_U_BO_REFCOUNTED_HASHED_9
#define dpa__u_p_bo_refcounted_hashed_ro__get_type(X)   DPA_U_BO_REFCOUNTED_HASHED_9
#define dpa__u_cp_bo_refcounted_hashed_ro__get_type(X)  DPA_U_BO_REFCOUNTED_HASHED_9
#define dpa__u_any_bo_refcounted_hashed_ro__get_type(X) DPA_U_BO_REFCOUNTED_HASHED_A9

#define dpa__u_bo_gc_ro__get_type(X) ((enum dpa_u_bo_gc_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))
#define dpa__u_bo_with_hash_ro__get_type(X) ((enum dpa_u_bo_with_hash_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))
#define dpa__u_bo_with_hash__get_type(X) ((enum dpa_u_bo_with_hash_type)(((const dpa__u_bo_meta_t*)(X))->type))
#define dpa__u_bo_with_refcount_ro__get_type(X) ((enum dpa_u_bo_with_refcount_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))
#define dpa__u_bo_with_refcount__get_type(X) ((enum dpa_u_bo_with_refcount_type)(((const dpa__u_bo_meta_t*)(X))->type))
#define dpa__u_bo_with_refcount_and_hash_ro__get_type(X) ((enum dpa_u_bo_with_refcount_and_hash_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))
