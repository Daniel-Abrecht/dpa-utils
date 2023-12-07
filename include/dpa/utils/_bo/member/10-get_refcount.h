
#define dpa_u_bo_get_refcount(...) dpa_u_assert_selection(dpa_u_bo_get_refcount_g(__VA_ARGS__))
#define dpa_u_bo_get_refcount_g(X) dpa_u_generic((X), \
        dpa_u_bo_unique_hashmap_t : dpa__u_v_bo_unique_hashmap__get_refcount(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__get_refcount(DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    dpa__u_helper_v_g(bo_ro, get_refcount, (X)), \
    dpa__u_helper_v_g(bo_unique, get_refcount, (X)), \
    dpa__u_helper_v_g(bo_refcounted, get_refcount, (X)), \
    dpa__u_helper_v_g(bo_refcounted_ro, get_refcount, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, get_refcount, (X)), \
    dpa_u_bo_gc_ro_t*: dpa__u_bo_gc_ro__get_refcount(DPA__G(dpa_u_bo_gc_ro_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount_ro__get_refcount(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__get_refcount(DPA__G(dpa_u_bo_with_refcount_t*,(X))), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__get_refcount(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))) \
  )

#define dpa__u_bo_with_refcount__get_refcount(X) dpa__u_cp_bo_refcounted__get_refcount((const dpa_u_bo_refcounted_t*)(X))
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_refcount_freeable_t* dpa__u_bo_gc_ro__get_refcount(const dpa_u_bo_gc_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return 0;
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_unique_hashmap_t)bo)->refcount.freeable;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_refcounted_ro_t*)bo)->refcount;
  }
  dpa_u_unreachable("dpa_u_bo_gc_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_refcount_freeable_t* dpa__u_bo_with_refcount_ro__get_refcount(const dpa_u_bo_with_refcount_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_unique_hashmap_t)bo)->refcount.freeable;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_refcounted_ro_t*)bo)->refcount;
  }
  dpa_u_unreachable("dpa_u_bo_with_refcount_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_refcount_freeable_t* dpa__u_bo_with_refcount_and_hash_ro__get_refcount(const dpa_u_bo_with_refcount_and_hash_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_unique_hashmap_t)bo)->refcount.freeable;
    case DPA_U_BO_REFCOUNTED_HASHED: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_refcounted_ro_t*)bo)->refcount;
  }
  dpa_u_unreachable("dpa_u_bo_with_refcount_and_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_unsequenced dpa__u_really_inline dpa__u_api inline dpa_u_refcount_freeable_t* dpa__u_v_bo_unique__get_refcount(const dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_INLINE: return 0;
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&ubo.bo_unique_hashmap->refcount.freeable;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(ubo)));
}
#define dpa__u_p_bo_unique__get_refcount(X) dpa__u_v_bo_unique__get_refcount(*(X))
#define dpa__u_cp_bo_unique__get_refcount(X) dpa__u_v_bo_unique__get_refcount(*(X))
#define dpa__u_any_bo_unique__get_refcount(X) dpa__u_v_bo_unique__get_refcount(*(const dpa_u_bo_unique_t*)(X))

dpa_u_unsequenced dpa__u_really_inline dpa__u_api inline dpa_u_refcount_freeable_t* dpa__u_v_bo_ro__get_refcount(const dpa_u_bo_ro_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
    case DPA_U_BO_SIMPLE: return 0;
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&bo.bo_unique_hashmap->refcount.freeable;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo_ro__get_refcount(X) dpa__u_cp_bo_ro__get_refcount(X)
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_refcount_freeable_t* dpa__u_cp_bo_ro__get_refcount(const dpa_u_bo_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
    case DPA_U_BO_SIMPLE: return 0;
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&bo->bo_unique_hashmap->refcount.freeable;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_refcount_freeable_t* dpa__u_any_bo_ro__get_refcount(dpa_u_any_bo_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
    case DPA_U_BO_HASHED:
    case DPA_U_BO_SIMPLE: return 0;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED:
      return ((dpa_u_bo_refcounted_ro_t*)bo)->refcount;
    case DPA_U_BO_UNIQUE_HASHMAP:
      return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_unique_hashmap_t)bo)->refcount.freeable;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_unique_hashmap__get_refcount(X) ((dpa_u_refcount_freeable_t*)&(X)->refcount.freeable)
#define dpa__u_p_bo_unique_hashmap__get_refcount(X) ((dpa_u_refcount_freeable_t*)&((X))->refcount.freeable)
#define dpa__u_cp_bo_unique_hashmap__get_refcount(X) ((dpa_u_refcount_freeable_t*)&((X))->refcount.freeable)
#define dpa__u_any_bo_unique_hashmap__get_refcount(X) ((dpa_u_refcount_freeable_t*)&((dpa_u_bo_unique_hashmap_t)(X))->refcount.freeable)

#define dpa__u_v_bo_refcounted__get_refcount(X) ((X).refcount)
#define dpa__u_p_bo_refcounted__get_refcount(X) ((X)->refcount)
#define dpa__u_cp_bo_refcounted__get_refcount(X) ((dpa_u_refcount_freeable_t*)((X)->refcount))
#define dpa__u_any_bo_refcounted__get_refcount(X) ((dpa_u_refcount_freeable_t*)(((const dpa_u_bo_refcounted_t*)(X))->refcount))

#define dpa__u_v_bo_refcounted_ro__get_refcount(X) ((X).refcount)
#define dpa__u_p_bo_refcounted_ro__get_refcount(X) ((X)->refcount)
#define dpa__u_cp_bo_refcounted_ro__get_refcount(X) ((dpa_u_refcount_freeable_t*)((X)->refcount))
#define dpa__u_any_bo_refcounted_ro__get_refcount(X) ((dpa_u_refcount_freeable_t*)(((const dpa_u_bo_refcounted_ro_t*)(X))->refcount))

#define dpa__u_v_bo_refcounted_hashed_ro__get_refcount(X) ((X).bo_refcounted.refcount)
#define dpa__u_p_bo_refcounted_hashed_ro__get_refcount(X) ((X)->bo_refcounted.refcount)
#define dpa__u_cp_bo_refcounted_hashed_ro__get_refcount(X) ((dpa_u_refcount_freeable_t*)((X)->bo_refcounted.refcount))
#define dpa__u_any_bo_refcounted_hashed_ro__get_refcount(X) ((dpa_u_refcount_freeable_t*)(((const dpa_u_bo_refcounted_hashed_ro_t*)(X))->bo_refcounted.refcount))


