
#define dpa_u_bo_get_hash(...) dpa_u_assert_selection(dpa_u_bo_get_hash_g(__VA_ARGS__))
#define dpa_u_bo_get_hash_g(X) dpa_u_generic((X), \
        dpa_u_bo_unique_hashmap_t : dpa__u_v_bo_unique_hashmap__get_hash(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__get_hash(DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    dpa__u_helper_v_g(bo_inline, get_hash, (X)), \
    dpa__u_helper_v_g(bo_unique, get_hash, (X)), \
    dpa__u_helper_v_g(bo_hashed_ro, get_hash, (X)), \
    dpa__u_helper_v_g(bo_hashed, get_hash, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, get_hash, (X)), \
    dpa_u_bo_with_hash_ro_t*: dpa__u_bo_with_hash_ro__get_hash(DPA__G(dpa_u_bo_with_hash_ro_t*,(X))), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__get_hash(DPA__G(dpa_u_bo_with_hash_t*,(X))), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__get_hash(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))) \
  )

#define dpa__u_v_bo_inline__get_hash(X)   ((dpa_u_hash_t)0) // TODO
#define dpa__u_p_bo_inline__get_hash(X)   dpa__u_v_bo_inline__get_hash(*(X))
#define dpa__u_cp_bo_inline__get_hash(X)  dpa__u_v_bo_inline__get_hash(*(X))
#define dpa__u_any_bo_inline__get_hash(X) dpa__u_v_bo_inline__get_hash(*(const dpa_u_bo_inline_t*)(X))

#define dpa__u_v_bo_unique_hashmap__get_hash(X) (X)->bo_hashed.hash
#define dpa__u_p_bo_unique_hashmap__get_hash(X) (X)->bo_hashed.hash
#define dpa__u_cp_bo_unique_hashmap__get_hash(X) (X)->bo_hashed.hash
#define dpa__u_any_bo_unique_hashmap__get_hash(X) ((dpa_u_bo_unique_hashmap_t)(X))->bo_hashed.hash

#define dpa__u_v_bo_hashed_ro__get_hash(X) (X).hash
#define dpa__u_p_bo_hashed_ro__get_hash(X) (X)->hash
#define dpa__u_cp_bo_hashed_ro__get_hash(X) (X)->hash
#define dpa__u_any_bo_hashed_ro__get_hash(X) ((const dpa_u_bo_hashed_ro_t*)(X))->hash

#define dpa__u_v_bo_hashed__get_hash(X) (X).hash
#define dpa__u_p_bo_hashed__get_hash(X) (X)->hash
#define dpa__u_cp_bo_hashed__get_hash(X) (X)->hash
#define dpa__u_any_bo_hashed__get_hash(X) ((const dpa_u_bo_hashed_t*)(X))->hash

#define dpa__u_v_bo_refcounted_hashed_ro__get_hash(X) (X).hash
#define dpa__u_p_bo_refcounted_hashed_ro__get_hash(X) (X)->hash
#define dpa__u_cp_bo_refcounted_hashed_ro__get_hash(X) (X)->hash
#define dpa__u_any_bo_refcounted_hashed_ro__get_hash(X) ((const dpa_u_bo_refcounted_hashed_ro_t*)(X))->hash

dpa_u_reproducible dpa__u_api inline dpa_u_hash_t dpa__u_v_bo_unique__get_hash(const dpa_u_bo_unique_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return dpa__u_v_bo_inline__get_hash(bo.bo_inline);
    case DPA_U_BO_UNIQUE_HASHMAP:
      return dpa__u_v_bo_unique_hashmap__get_hash(bo.bo_unique_hashmap);
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo_unique__get_hash(X) dpa__u_v_bo_unique__get_hash(*(X))
#define dpa__u_cp_bo_unique__get_hash(X) dpa__u_v_bo_unique__get_hash(*(X))
dpa_u_reproducible dpa__u_api inline dpa_u_hash_t dpa__u_any_bo_unique__get_hash(dpa_u_any_bo_unique_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return dpa__u_any_bo_inline__get_hash(bo);
    case DPA_U_BO_UNIQUE_HASHMAP:
      return dpa__u_any_bo_unique_hashmap__get_hash(bo);
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

dpa_u_reproducible dpa__u_api inline dpa_u_hash_t dpa__u_bo_with_hash_ro__get_hash(dpa_u_bo_with_hash_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return dpa__u_any_bo_inline__get_hash(bo);
    case DPA_U_BO_UNIQUE_HASHMAP:
    case DPA_U_BO_HASHED:
      return ((const dpa_u_bo_hashed_ro_t*)bo)->hash;
    case DPA_U_BO_REFCOUNTED_HASHED:
      return ((const dpa_u_bo_refcounted_hashed_ro_t*)bo)->hash;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

dpa_u_reproducible dpa__u_api inline dpa_u_hash_t dpa__u_bo_with_hash__get_hash(dpa_u_bo_with_hash_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return dpa__u_any_bo_inline__get_hash(bo);
    case DPA_U_BO_HASHED:
      return ((const dpa_u_bo_hashed_ro_t*)bo)->hash;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

dpa_u_reproducible dpa__u_api inline dpa_u_hash_t dpa__u_bo_with_refcount_and_hash_ro__get_hash(dpa_u_bo_with_refcount_and_hash_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP:
      return dpa__u_any_bo_unique_hashmap__get_hash(bo);
    case DPA_U_BO_REFCOUNTED_HASHED:
      return dpa__u_any_bo_refcounted_hashed_ro__get_hash(bo);
  }
  dpa_u_unreachable("dpa_u_bo_with_refcount_and_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
