
#define dpa_u_bo_get_size(...) dpa_u_assert_selection(dpa_u_bo_get_size_g(__VA_ARGS__))
#define dpa_u_bo_get_size_g(X) dpa_u_generic((X),dpa__u_helper_all_g(get_size,(X)))

#define dpa__u_v_bo_unique_hashmap__get_size(X) ((X)->bo_hashed.bo_simple.size)
#define dpa__u_p_bo_unique_hashmap__get_size(X) ((X)->bo_hashed.bo_simple.size)
#define dpa__u_cp_bo_unique_hashmap__get_size(X) ((X)->bo_hashed.bo_simple.size)
#define dpa__u_any_bo_unique_hashmap__get_size(X) ((X)->bo_hashed.bo_simple.size)

#define dpa__u_v_bo_inline__get_size(X) ((X).size)
#define dpa__u_p_bo_inline__get_size(X) ((X)->size)
#define dpa__u_cp_bo_inline__get_size(X) ((X)->size)
#define dpa__u_any_bo_inline__get_size(X) (((const dpa_u_bo_inline_t*)(X))->size)

#define dpa__u_v_bo_simple__get_size(X) ((X).size)
#define dpa__u_p_bo_simple__get_size(X) ((X)->size)
#define dpa__u_cp_bo_simple__get_size(X) ((X)->size)
#define dpa__u_any_bo_simple__get_size(X) (((const dpa_u_bo_simple_t*)(X))->size)

#define dpa__u_v_bo_simple_ro__get_size(X) ((X).size)
#define dpa__u_p_bo_simple_ro__get_size(X) ((X)->size)
#define dpa__u_cp_bo_simple_ro__get_size(X) ((X)->size)
#define dpa__u_any_bo_simple_ro__get_size(X) (((const dpa_u_bo_simple_ro_t*)(X))->size)

#define dpa__u_v_bo_hashed__get_size(X) ((X).bo_simple.size)
#define dpa__u_p_bo_hashed__get_size(X) ((X)->bo_simple.size)
#define dpa__u_cp_bo_hashed__get_size(X) ((X)->bo_simple.size)
#define dpa__u_any_bo_hashed__get_size(X) (((const dpa_u_bo_hashed_t*)(X))->bo_simple.size)

#define dpa__u_v_bo_hashed_ro__get_size(X) ((X).bo_simple.size)
#define dpa__u_p_bo_hashed_ro__get_size(X) ((X)->bo_simple.size)
#define dpa__u_cp_bo_hashed_ro__get_size(X) ((X)->bo_simple.size)
#define dpa__u_any_bo_hashed_ro__get_size(X) (((const dpa_u_bo_hashed_ro_t*)(X))->bo_simple.size)

#define dpa__u_v_bo_refcounted__get_size(X) ((X).bo_simple.size)
#define dpa__u_p_bo_refcounted__get_size(X) ((X)->bo_simple.size)
#define dpa__u_cp_bo_refcounted__get_size(X) ((X)->bo_simple.size)
#define dpa__u_any_bo_refcounted__get_size(X) (((const dpa_u_bo_refcounted_t*)(X))->bo_simple.size)

#define dpa__u_v_bo_refcounted_ro__get_size(X) ((X).bo_simple.size)
#define dpa__u_p_bo_refcounted_ro__get_size(X) ((X)->bo_simple.size)
#define dpa__u_cp_bo_refcounted_ro__get_size(X) ((X)->bo_simple.size)
#define dpa__u_any_bo_refcounted_ro__get_size(X) (((const dpa_u_bo_refcounted_ro_t*)(X))->bo_simple.size)

#define dpa__u_v_bo_refcounted_hashed_ro__get_size(X) ((X).bo_refcounted.bo_simple.size)
#define dpa__u_p_bo_refcounted_hashed_ro__get_size(X) ((X)->bo_refcounted.bo_simple.size)
#define dpa__u_cp_bo_refcounted_hashed_ro__get_size(X) ((X)->bo_refcounted.bo_simple.size)
#define dpa__u_any_bo_refcounted_hashed_ro__get_size(X) (((const dpa_u_bo_refcounted_hashed_ro_t*)(X))->bo_refcounted.bo_simple.size)

dpa_u_reproducible dpa__u_really_inline dpa_u_export inline size_t dpa__u_bo_gc_ro__get_size(const dpa_u_bo_gc_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((dpa_u_bo_inline_ro_t*)bo)->size;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED:
    case DPA_U_BO_UNIQUE_HASHMAP: return ((const dpa_u_bo_simple_ro_t*)bo)->size;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline size_t dpa__u_bo_with_hash_ro__get_size(const dpa_u_bo_with_hash_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((dpa_u_bo_inline_ro_t*)bo)->size;
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED_HASHED:
    case DPA_U_BO_UNIQUE_HASHMAP: return ((const dpa_u_bo_simple_ro_t*)bo)->size;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline size_t dpa__u_bo_with_hash__get_size(const dpa_u_bo_with_hash_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((dpa_u_bo_inline_ro_t*)bo)->size;
    case DPA_U_BO_HASHED: return ((const dpa_u_bo_simple_ro_t*)bo)->size;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount_ro__get_size(X) (((const dpa_u_bo_simple_ro_t*)(X))->size)
#define dpa__u_bo_with_refcount__get_size(X) (((const dpa_u_bo_simple_ro_t*)(X))->size)
#define dpa__u_bo_with_refcount_and_hash_ro__get_size(X) (((const dpa_u_bo_simple_ro_t*)(X))->size)


dpa_u_unsequenced dpa__u_really_inline dpa_u_export inline size_t dpa__u_v_bo_unique__get_size(const dpa_u_bo_unique_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo.bo_unique_hashmap->bo_hashed.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo_unique__get_size(X) dpa__u_v_bo_unique__get_size(*(X))
#define dpa__u_cp_bo_unique__get_size(X) dpa__u_v_bo_unique__get_size(*(X))
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline size_t dpa__u_any_bo_unique__get_size(const dpa_u_any_bo_unique_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->size;
    case DPA_U_BO_UNIQUE_HASHMAP: return ((dpa_u_bo_unique_hashmap_t)bo)->bo_hashed.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

dpa_u_unsequenced dpa__u_really_inline dpa_u_export inline size_t dpa__u_v_bo__get_size(const dpa_u_bo_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_SIMPLE: return bo.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo__get_size(X) dpa__u_v_bo__get_size(*(X))
#define dpa__u_cp_bo__get_size(X) dpa__u_v_bo__get_size(*(X))
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline size_t dpa__u_any_bo__get_size(const dpa_u_any_bo_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->size;
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->size;
  }
  dpa_u_unreachable("dpa_u_any_bo_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

dpa_u_unsequenced dpa__u_really_inline dpa_u_export inline size_t dpa__u_v_bo_ro__get_size(const dpa_u_bo_ro_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_SIMPLE: return bo.bo_simple.size;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo.bo_unique_hashmap->bo_hashed.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo_ro__get_size(X) dpa__u_v_bo_ro__get_size(*(X))
#define dpa__u_cp_bo_ro__get_size(X) dpa__u_v_bo_ro__get_size(*(X))
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline size_t dpa__u_any_bo_ro__get_size(const dpa_u_any_bo_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->size;
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED:
    case DPA_U_BO_UNIQUE_HASHMAP:
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->size;
  }
  dpa_u_unreachable("dpa_u_any_bo_ro_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
