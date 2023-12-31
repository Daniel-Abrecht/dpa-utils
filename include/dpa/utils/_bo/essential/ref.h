
#define dpa_u_bo_ref(...) dpa_u_assert_selection(dpa_u_bo_ref_g(__VA_ARGS__))
#define dpa_u_bo_ref_g(X) dpa_u_generic((X), \
        dpa_u_bo_unique_hashmap_t : dpa__u_v_bo_unique_hashmap__ref(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__ref(DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    dpa__u_helper_v_g(bo_inline, ref, (X)), \
    dpa__u_helper_v_g(bo_unique, ref, (X)), \
    dpa__u_helper_v_g(bo_refcounted, ref, (X)), \
    dpa__u_helper_v_g(bo_refcounted_ro, ref, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, ref, (X)), \
    dpa_u_bo_gc_ro_t*: dpa__u_bo_gc_ro__ref(DPA__G(dpa_u_bo_gc_ro_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount_ro__ref(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__ref(DPA__G(dpa_u_bo_with_refcount_t*,(X))), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__ref(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))) \
  )

#define dpa__u_v_bo_inline__ref(X)   (void)0
#define dpa__u_p_bo_inline__ref(X)   (void)0
#define dpa__u_cp_bo_inline__ref(X)  (void)0
#define dpa__u_any_bo_inline__ref(X) (void)0

#define dpa__u_v_bo_unique_hashmap__ref(X)   dpa_u_refcount_increment_p(&(X)->refcount.freeable.refcount)
#define dpa__u_p_bo_unique_hashmap__ref(X)   dpa_u_refcount_increment_p(&(X)->refcount.freeable.refcount)
#define dpa__u_cp_bo_unique_hashmap__ref(X)  dpa_u_refcount_increment_p(&(X)->refcount.freeable.refcount)
#define dpa__u_any_bo_unique_hashmap__ref(X) dpa_u_refcount_increment_p(&((dpa_u_bo_unique_hashmap_t)(X))->refcount.freeable.refcount)

dpa__u_really_inline dpa__u_api inline void dpa__u_v_bo_unique__ref(dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__ref(ubo.bo_unique_hashmap); return;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(ubo)));
}
#define dpa__u_p_bo_unique__ref(X)   dpa__u_v_bo_unique__ref(*(X))
#define dpa__u_cp_bo_unique__ref(X)  dpa__u_v_bo_unique__ref(*(X))
dpa__u_really_inline dpa__u_api inline void dpa__u_any_bo_unique__ref(dpa_u_any_bo_unique_t*const ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__ref((dpa_u_bo_unique_hashmap_t)ubo); return;
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(ubo)));
}

#define dpa__u_v_bo_refcounted__ref(X)   dpa_u_refcount_increment_p(&(X).refcount->refcount)
#define dpa__u_p_bo_refcounted__ref(X)   dpa_u_refcount_increment_p(&(X)->refcount->refcount)
#define dpa__u_cp_bo_refcounted__ref(X)  dpa_u_refcount_increment_p(&(X)->refcount->refcount)
#define dpa__u_any_bo_refcounted__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_t*)(X))->refcount->refcount)

#define dpa__u_v_bo_refcounted_ro__ref(X)   dpa_u_refcount_increment_p(&(X).refcount->refcount)
#define dpa__u_p_bo_refcounted_ro__ref(X)   dpa_u_refcount_increment_p(&(X)->refcount->refcount)
#define dpa__u_cp_bo_refcounted_ro__ref(X)  dpa_u_refcount_increment_p(&(X)->refcount->refcount)
#define dpa__u_any_bo_refcounted_ro__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_ro_t*)(X))->refcount->refcount)

#define dpa__u_v_bo_refcounted_hashed_ro__ref(X)   dpa_u_refcount_increment_p(&(X).bo_refcounted.refcount->refcount)
#define dpa__u_p_bo_refcounted_hashed_ro__ref(X)   dpa_u_refcount_increment_p(&(X)->bo_refcounted.refcount->refcount)
#define dpa__u_cp_bo_refcounted_hashed_ro__ref(X)  dpa_u_refcount_increment_p(&(X)->bo_refcounted.refcount->refcount)
#define dpa__u_any_bo_refcounted_hashed_ro__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_hashed_ro_t*)(X))->bo_refcounted.refcount->refcount)

dpa__u_really_inline dpa__u_api inline void dpa__u_bo_gc_ro__ref(dpa_u_bo_gc_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__ref((dpa_u_bo_unique_hashmap_t)bo); return;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED: dpa_u_refcount_ref(((const dpa_u_bo_refcounted_ro_t*)bo)->refcount); return;
  }
  dpa_u_unreachable("dpa_u_bo_gc_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount_ro__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_ro_t*)(X))->refcount->refcount)
#define dpa__u_bo_with_refcount__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_ro_t*)(X))->refcount->refcount)
#define dpa__u_bo_with_refcount_and_hash_ro__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_ro_t*)(X))->refcount->refcount)
