

#define dpa_u_bo_data(...) dpa_u_assert_selection(dpa_u_bo_data_g(__VA_ARGS__))
#define dpa_u_bo_data_g(X) dpa_u_generic((X),dpa__u_helper_all_g(data,(X)))

#define dpa__u_v_bo_unique_hashmap__data(X)   ((X)->bo_hashed.bo_simple.data)
#define dpa__u_p_bo_unique_hashmap__data(X)   ((X)->bo_hashed.bo_simple.data)
#define dpa__u_cp_bo_unique_hashmap__data(X)  ((X)->bo_hashed.bo_simple.data)
#define dpa__u_any_bo_unique_hashmap__data(X) ((X)->bo_hashed.bo_simple.data)

#define dpa__u_v_bo_inline__data(X)   ((X).data)
#define dpa__u_p_bo_inline__data(X)   ((X)->data)
#define dpa__u_cp_bo_inline__data(X)  ((X)->data)
#define dpa__u_any_bo_inline__data(X) (((const dpa_u_bo_inline_t*)(X))->data)

#define dpa__u_v_bo_simple__data(X)   ((X).data)
#define dpa__u_p_bo_simple__data(X)   ((X)->data)
#define dpa__u_cp_bo_simple__data(X)  ((X)->data)
#define dpa__u_any_bo_simple__data(X) (((const dpa_u_bo_simple_t*)(X))->data)

#define dpa__u_v_bo_simple_ro__data(X)   ((X).data)
#define dpa__u_p_bo_simple_ro__data(X)   ((X)->data)
#define dpa__u_cp_bo_simple_ro__data(X)  ((X)->data)
#define dpa__u_any_bo_simple_ro__data(X) (((const dpa_u_bo_simple_ro_t*)(X))->data)

#define dpa__u_v_bo_hashed_ro__data(X)   ((X).bo_simple.data)
#define dpa__u_p_bo_hashed_ro__data(X)   ((X)->bo_simple.data)
#define dpa__u_cp_bo_hashed_ro__data(X)  ((X)->bo_simple.data)
#define dpa__u_any_bo_hashed_ro__data(X) (((const dpa_u_bo_hashed_ro_t*)(X))->bo_simple.data)

#define dpa__u_v_bo_hashed__data(X)   ((X).bo_simple.data)
#define dpa__u_p_bo_hashed__data(X)   ((X)->bo_simple.data)
#define dpa__u_cp_bo_hashed__data(X)  ((X)->bo_simple.data)
#define dpa__u_any_bo_hashed__data(X) (((const dpa_u_bo_hashed_t*)(X))->bo_simple.data)

#define dpa__u_v_bo_refcounted__data(X)   ((X).bo_simple.data)
#define dpa__u_p_bo_refcounted__data(X)   ((X)->bo_simple.data)
#define dpa__u_cp_bo_refcounted__data(X)  ((X)->bo_simple.data)
#define dpa__u_any_bo_refcounted__data(X) (((const dpa_u_bo_refcounted_t*)(X))->bo_simple.data)

#define dpa__u_v_bo_refcounted_ro__data(X)   ((X).bo_simple.data)
#define dpa__u_p_bo_refcounted_ro__data(X)   ((X)->bo_simple.data)
#define dpa__u_cp_bo_refcounted_ro__data(X)  ((X)->bo_simple.data)
#define dpa__u_any_bo_refcounted_ro__data(X) (((const dpa_u_bo_refcounted_ro_t*)(X))->bo_simple.data)

#define dpa__u_v_bo_refcounted_hashed_ro__data(X)   ((X).bo_refcounted.bo_simple.data)
#define dpa__u_p_bo_refcounted_hashed_ro__data(X)   ((X)->bo_refcounted.bo_simple.data)
#define dpa__u_cp_bo_refcounted_hashed_ro__data(X)  ((X)->bo_refcounted.bo_simple.data)
#define dpa__u_any_bo_refcounted_hashed_ro__data(X) (((const dpa_u_bo_refcounted_hashed_ro_t*)(X))->bo_refcounted.bo_simple.data)

dpa_u_reproducible dpa__u_really_inline dpa_u_export inline const void* dpa__u_bo_gc_ro__data(const dpa_u_bo_gc_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_ro_t*)bo)->data;
    case DPA_U_BO_UNIQUE_HASHMAP:
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED: return ((const dpa_u_bo_simple_ro_t*)bo)->data;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline const void* dpa__u_bo_with_hash_ro__data(const dpa_u_bo_with_hash_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_ro_t*)bo)->data;
    case DPA_U_BO_UNIQUE_HASHMAP:
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED_HASHED: return ((const dpa_u_bo_simple_ro_t*)bo)->data;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline const void* dpa__u_bo_with_hash__data(const dpa_u_bo_with_hash_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((dpa_u_bo_inline_ro_t*)bo)->data;
    case DPA_U_BO_HASHED: return ((const dpa_u_bo_simple_ro_t*)bo)->data;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount_ro__data(X) (((const dpa_u_bo_simple_ro_t*)(X))->data)
#define dpa__u_bo_with_refcount__data(X) (((const dpa_u_bo_simple_ro_t*)(X))->data)
#define dpa__u_bo_with_refcount_and_hash_ro__data(X) (((const dpa_u_bo_simple_ro_t*)(X))->data)

// bo_unique could contain bo_inline. Copying a bo_inline would mean copying it's data.
// We can't reference it, because it could be an rvalue. Casting the all char array is allowed,
// but in case of an rvalue, this will have temporary storage duration, it will only be valid for the current statement!
#define dpa__u_v_bo_unique__data(X)   dpa__u_cp_bo_unique__data((const dpa_u_bo_unique_t*)(X).all.all)
#define dpa__u_p_bo_unique__data(X)   dpa__u_cp_bo_unique__data((X))
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline const void* dpa__u_cp_bo_unique__data(const dpa_u_bo_unique_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo->bo_unique_hashmap->bo_hashed.bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline const void* dpa__u_any_bo_unique__data(const dpa_u_any_bo_unique_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->data;
    case DPA_U_BO_UNIQUE_HASHMAP: return ((dpa_u_bo_unique_hashmap_t)bo)->bo_hashed.bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

// dpa_u_bo could contain bo_inline. Copying a bo_inline would mean copying it's data.
// We can't reference it, because it could be an rvalue. Casting the all char array is allowed,
// but in case of an rvalue, this will have temporary storage duration, it will only be valid for the current statement!
#define dpa__u_v_bo__data(X) dpa_u_generic((X).all.all, \
          char*: dpa__u_p_bo__data((dpa_u_bo_t*)(X).all.all), \
    const char*: dpa__u_cp_bo__data((const dpa_u_bo_t*)(X).all.all) \
  )
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline void* dpa__u_p_bo__data(dpa_u_bo_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline const void* dpa__u_cp_bo__data(const dpa_u_bo_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline const void* dpa__u_any_bo__data(const dpa_u_any_bo_t* const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->data;
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->data;
  }
  dpa_u_unreachable("dpa_u_any_bo_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

// dpa_u_bo_ro_t could contain bo_inline. Copying a bo_inline would mean copying it's data.
// We can't reference it, because it could be an rvalue. Casting the all char array is allowed,
// but in case of an rvalue, this will have temporary storage duration, it will only be valid for the current statement!
#define dpa__u_v_bo_ro__data(X)   dpa__u_cp_bo_ro__data((const dpa_u_bo_ro_t*)(X).all.all)
#define dpa__u_p_bo_ro__data(X)   dpa__u_cp_bo_ro__data((X))
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline const void* dpa__u_cp_bo_ro__data(const dpa_u_bo_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo->bo_unique_hashmap->bo_hashed.bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline const void* dpa__u_any_bo_ro__data(const dpa_u_any_bo_ro_t* const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->data;
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED:
    case DPA_U_BO_UNIQUE_HASHMAP:
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->data;
  }
  dpa_u_unreachable("dpa_u_any_bo_ro_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
