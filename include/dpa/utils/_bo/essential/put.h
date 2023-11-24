
#define dpa_u_bo_put(...) dpa_u_assert_selection(dpa_u_bo_put_g(__VA_ARGS__))
#define dpa_u_bo_put_g(X) dpa_u_generic((X), \
        dpa_u_bo_unique_hashmap_t : dpa__u_v_bo_unique_hashmap__put(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__put(DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    dpa__u_helper_v_g(bo_inline, put, (X)), \
    dpa__u_helper_v_g(bo_unique, put, (X)), \
    dpa__u_helper_v_g(bo_refcounted, put, (X)), \
    dpa__u_helper_v_g(bo_refcounted_ro, put, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, put, (X)), \
    dpa_u_bo_gc_ro_t*: dpa__u_bo_gc_ro__put(DPA__G(dpa_u_bo_gc_ro_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount_ro__put(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__put(DPA__G(dpa_u_bo_with_refcount_t*,(X))), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__put(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))) \
  )

#define dpa__u_v_bo_inline__put(X)   (void)0
#define dpa__u_p_bo_inline__put(X)   (void)0
#define dpa__u_cp_bo_inline__put(X)  (void)0
#define dpa__u_any_bo_inline__put(X) (void)0

#define dpa__u_v_bo_unique_hashmap__put(X)   dpa_u_refcount_put_s(&(X)->refcount.freeable)
#define dpa__u_p_bo_unique_hashmap__put(X)   dpa_u_refcount_put_s(&(X)->refcount.freeable)
#define dpa__u_cp_bo_unique_hashmap__put(X)  dpa_u_refcount_put_s(&(X)->refcount.freeable)
#define dpa__u_any_bo_unique_hashmap__put(X) dpa_u_refcount_put_s(&((dpa_u_bo_unique_hashmap_t)(X))->refcount.freeable)

dpa__u_really_inline dpa_u_export inline void dpa__u_v_bo_unique__put(dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__put(ubo.bo_unique_hashmap); return;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(ubo)));
}
#define dpa__u_p_bo_unique__put(X)   dpa__u_v_bo_unique__put(*(X))
#define dpa__u_cp_bo_unique__put(X)  dpa__u_v_bo_unique__put(*(X))
dpa__u_really_inline dpa_u_export inline void dpa__u_any_bo_unique__put(dpa_u_any_bo_unique_t*const ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__put((dpa_u_bo_unique_hashmap_t)ubo); return;
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(ubo)));
}

#define dpa__u_v_bo_refcounted__put(X)   dpa_u_refcount_put_s((X).refcount)
#define dpa__u_p_bo_refcounted__put(X)   dpa_u_refcount_put_s((X)->refcount)
#define dpa__u_cp_bo_refcounted__put(X)  dpa_u_refcount_put_s((X)->refcount)
#define dpa__u_any_bo_refcounted__put(X) dpa_u_refcount_put_s(((const dpa_u_bo_refcounted_t*)(X))->refcount)

#define dpa__u_v_bo_refcounted_ro__put(X)   dpa_u_refcount_put_s((X).refcount)
#define dpa__u_p_bo_refcounted_ro__put(X)   dpa_u_refcount_put_s((X)->refcount)
#define dpa__u_cp_bo_refcounted_ro__put(X)  dpa_u_refcount_put_s((X)->refcount)
#define dpa__u_any_bo_refcounted_ro__put(X) dpa_u_refcount_put_s(((const dpa_u_bo_refcounted_ro_t*)(X))->refcount)

#define dpa__u_v_bo_refcounted_hashed_ro__put(X)   dpa_u_refcount_put_s((X).bo_refcounted.refcount)
#define dpa__u_p_bo_refcounted_hashed_ro__put(X)   dpa_u_refcount_put_s((X)->bo_refcounted.refcount)
#define dpa__u_cp_bo_refcounted_hashed_ro__put(X)  dpa_u_refcount_put_s((X)->bo_refcounted.refcount)
#define dpa__u_any_bo_refcounted_hashed_ro__put(X) dpa_u_refcount_put_s(((const dpa_u_bo_refcounted_hashed_ro_t*)(X))->bo_refcounted.refcount)

dpa__u_really_inline dpa_u_export inline void dpa__u_bo_gc_ro__put(dpa_u_bo_gc_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__put((dpa_u_bo_unique_hashmap_t)bo); return;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED: dpa_u_refcount_put(((const dpa_u_bo_refcounted_ro_t*)bo)->refcount); return;
  }
  dpa_u_unreachable("dpa_u_bo_gc_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount_ro__put(X) dpa_u_refcount_put_s(((const dpa_u_bo_refcounted_ro_t*)(X))->refcount)
#define dpa__u_bo_with_refcount__put(X) dpa_u_refcount_put_s(((const dpa_u_bo_refcounted_ro_t*)(X))->refcount)
#define dpa__u_bo_with_refcount_and_hash_ro__put(X) dpa_u_refcount_put_s(((const dpa_u_bo_refcounted_ro_t*)(X))->refcount)
