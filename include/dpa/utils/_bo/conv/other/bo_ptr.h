#define dpa_u_bo_ptr(...) dpa_u_assert_selection(dpa_u_bo_ptr_g(__VA_ARGS__))
#define dpa_u_bo_ptr_g(X) dpa_u_generic((X),dpa__u_helper_all_g(ptr,(X)))

#define dpa__u_any_bo_inline__ptr(X) (X)
#define dpa__u_any_bo_unique_hashmap__ptr(X) (X)
#define dpa__u_any_bo_unique__ptr(X) (X)
#define dpa__u_any_bo_simple__ptr(X) (X)
#define dpa__u_any_bo_simple_ro__ptr(X) (X)
#define dpa__u_any_bo__ptr(X) (X)
#define dpa__u_any_bo_ro__ptr(X) (X)
#define dpa__u_any_bo_hashed_ro__ptr(X) (X)
#define dpa__u_any_bo_hashed__ptr(X) (X)
#define dpa__u_any_bo_refcounted_ro__ptr(X) (X)
#define dpa__u_any_bo_refcounted__ptr(X) (X)
#define dpa__u_any_bo_refcounted_hashed_ro__ptr(X) (X)
#define dpa__u_any_bo_refcounted_hashed__ptr(X) (X)

#define dpa__u_bo_with_hash_ro__ptr(X) (X)
#define dpa__u_bo_with_hash__ptr(X) (X)
#define dpa__u_bo_with_refcount_ro__ptr(X) (X)
#define dpa__u_bo_with_refcount__ptr(X) (X)
#define dpa__u_bo_with_refcount_and_hash_ro__ptr(X) (X)
#define dpa__u_bo_gc_ro__ptr(X) (X)

dpa_u_export inline dpa_u_any_bo_unique_t* dpa__u_cp_bo_unique__ptr(const dpa_u_bo_unique_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_any_bo_unique_t*)bo->bo_unique_hashmap;
    case DPA_U_BO_INLINE: return (dpa_u_any_bo_unique_t*)bo;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

dpa_u_export inline dpa_u_any_bo_ro_t* dpa__u_cp_bo_ro__ptr(const dpa_u_bo_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_any_bo_ro_t*)bo->bo_unique_hashmap;
    case DPA_U_BO_SIMPLE:
    case DPA_U_BO_INLINE: return (dpa_u_any_bo_ro_t*)bo;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_unique__ptr(X) dpa__u_cp_bo_unique__ptr(&(X))
#define dpa__u_v_bo_ro__ptr(X) dpa__u_cp_bo_ro__ptr(&(X))
#define dpa__u_v_bo_inline__ptr(X) (dpa_u_any_bo_inline_t*)&(X)
#define dpa__u_v_bo_unique_hashmap__ptr(X) (dpa_u_any_bo_unique_hashmap_t*)(X)
#define dpa__u_v_bo_simple__ptr(X) (dpa_u_any_bo_simple_t*)&(X)
#define dpa__u_v_bo_simple_ro__ptr(X) (dpa_u_any_bo_simple_ro_t*)&(X)
#define dpa__u_v_bo__ptr(X) (dpa_u_any_bo_t*)&(X)
#define dpa__u_v_bo_hashed_ro__ptr(X) (dpa_u_any_bo_hashed_ro_t*)&(X)
#define dpa__u_v_bo_hashed__ptr(X) (dpa_u_any_bo_hashed_t*)&(X)
#define dpa__u_v_bo_refcounted_ro__ptr(X) (dpa_u_any_bo_refcounted_ro_t*)&(X)
#define dpa__u_v_bo_refcounted__ptr(X) (dpa_u_any_bo_refcounted_t*)&(X)
#define dpa__u_v_bo_refcounted_hashed_ro__ptr(X) (dpa_u_any_bo_refcounted_hashed_ro_t*)&(X)
#define dpa__u_v_bo_refcounted_hashed__ptr(X) (dpa_u_any_bo_refcounted_hashed_t*)&(X)

#define dpa__u_p_bo_unique__ptr(X) dpa__u_cp_bo_unique__ptr(X)
#define dpa__u_p_bo_ro__ptr(X) dpa__u_cp_bo_ro__ptr(X)
#define dpa__u_p_bo_inline__ptr(X) (dpa_u_any_bo_inline_t*)(X)
#define dpa__u_p_bo_simple__ptr(X) (dpa_u_any_bo_simple_t*)(X)
#define dpa__u_p_bo_simple_ro__ptr(X) (dpa_u_any_bo_simple_ro_t*)(X)
#define dpa__u_p_bo__ptr(X) (dpa_u_any_bo_t*)(X)
#define dpa__u_p_bo_hashed_ro__ptr(X) (dpa_u_any_bo_hashed_ro_t*)(X)
#define dpa__u_p_bo_hashed__ptr(X) (dpa_u_any_bo_hashed_t*)(X)
#define dpa__u_p_bo_refcounted_ro__ptr(X) (dpa_u_any_bo_refcounted_ro_t*)(X)
#define dpa__u_p_bo_refcounted__ptr(X) (dpa_u_any_bo_refcounted_t*)(X)
#define dpa__u_p_bo_refcounted_hashed_ro__ptr(X) (dpa_u_any_bo_refcounted_hashed_ro_t*)(X)
#define dpa__u_p_bo_refcounted_hashed__ptr(X) (dpa_u_any_bo_refcounted_hashed_t*)(X)

#define dpa__u_cp_bo_inline__ptr(X) (dpa_u_any_bo_inline_t*)(X)
#define dpa__u_cp_bo_simple__ptr(X) (dpa_u_any_bo_simple_t*)(X)
#define dpa__u_cp_bo_simple_ro__ptr(X) (dpa_u_any_bo_simple_ro_t*)(X)
#define dpa__u_cp_bo__ptr(X) (dpa_u_any_bo_t*)(X)
#define dpa__u_cp_bo_hashed_ro__ptr(X) (dpa_u_any_bo_hashed_ro_t*)(X)
#define dpa__u_cp_bo_hashed__ptr(X) (dpa_u_any_bo_hashed_t*)(X)
#define dpa__u_cp_bo_refcounted_ro__ptr(X) (dpa_u_any_bo_refcounted_ro_t*)(X)
#define dpa__u_cp_bo_refcounted__ptr(X) (dpa_u_any_bo_refcounted_t*)(X)
#define dpa__u_cp_bo_refcounted_hashed_ro__ptr(X) (dpa_u_any_bo_refcounted_hashed_ro_t*)(X)
#define dpa__u_cp_bo_refcounted_hashed__ptr(X) (dpa_u_any_bo_refcounted_hashed_t*)(X)
