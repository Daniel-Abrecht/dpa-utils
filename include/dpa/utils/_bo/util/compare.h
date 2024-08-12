
#define dpa_u_bo_compare(...) dpa_u_assert_selection(dpa_u_bo_compare_g(__VA_ARGS__))
#define dpa_u_bo_compare_g(X, Y) dpa__u_sort_param_by_type_g(dpa__u_bo_compare_g, (X), (Y))
#define dpa__u_bo_compare_g(X, Y, S) \
  _Generic((X), \
    DPA__U_BOCVHV(bo_inline, dpa__u_bo_compare_inline_g, (X), (Y), (S)), \
    dpa_u_bo_unique_hashmap_t: dpa__u_bo_compare_unique_hashmap_g(DPA__G(dpa_u_bo_unique_hashmap_t,(X)),(Y),(S)), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_bo_compare_unique_hashmap_g((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X)),(Y),(S)), \
    DPA__U_BOCVHV(bo_unique, dpa__u_bo_compare_unique_g, (X), (Y), (S)), \
    default: dpa__u_bo_compare_default(dpa_u_vp_any_bo_ro(X), dpa_u_vp_any_bo_ro(Y)) \
  )

dpa_u_unsequenced dpa__u_api inline int dpa__u_bo_compare_default_sub(const dpa_u_bo_simple_ro_t a, const dpa_u_bo_simple_ro_t b){
  const size_t a_size = dpa_u_bo_get_size(a);
  const size_t b_size = dpa_u_bo_get_size(b);
  if(a_size < b_size) return -1;
  if(a_size > b_size) return 1;
  const void*const a_data = dpa_u_bo_data(a);
  const void*const b_data = dpa_u_bo_data(b);
  if(a_data == b_data)
    return 0;
  return memcmp(a_data, b_data, a_size);
}

// Note: S is always 1
#define dpa__u_bo_compare_inline_g(X,Y,S) dpa_u_generic((Y), DPA__U_BOCVHV2(bo_inline, (-S) * dpa__u_bo_compare_inline, (Y), (X)))
dpa_u_unsequenced dpa__u_api inline int dpa__u_bo_compare_inline(const dpa_u_bo_inline_t a, const dpa_u_bo_inline_t b){
  if(a.size != b.size)
    return (int)a.size - b.size;
  return memcmp(a.data, b.data, a.size);
}

// Note: dpa_u_bo_intern will always return an inline bo if the string fits into it. Therefore, if we have an inline bo, it can not match a unique_hashmap bo.
#define dpa__u_bo_compare_unique_hashmap_g(X,Y,S) \
  dpa_u_generic((Y), \
    dpa_u_bo_inline_t: -S, \
    dpa_u_any_bo_inline_t*: -S, \
    dpa_u_bo_unique_hashmap_t: S * ((X) - DPA__G(dpa_u_bo_unique_hashmap_t,(Y))), \
    dpa_u_any_bo_unique_hashmap_t*: S * dpa_u_ptr_compare((X), DPA__G(dpa_u_any_bo_unique_hashmap_t*,(Y))) \
  )

#define dpa__u_bo_compare_unique_g(X,Y,S) \
  dpa_u_generic((Y), \
    dpa_u_bo_inline_t: -S, \
    dpa_u_any_bo_inline_t*: -S, \
    dpa_u_bo_unique_hashmap_t: (X).type == DPA_U_BO_UNIQUE_HASHMAP ? (S * dpa_u_ptr_compare((X).bo_unique_hashmap, DPA__G(dpa_u_bo_unique_hashmap_t,(Y)))) : -S, \
    dpa_u_any_bo_unique_hashmap_t*: (X).type == DPA_U_BO_UNIQUE_HASHMAP ? (S * dpa_u_ptr_compare((X).bo_unique_hashmap, DPA__G(dpa_u_any_bo_unique_hashmap_t*,(Y)))) : -S, \
    DPA__U_BOCVHV2(bo_unique, (-S) * dpa__u_bo_compare_unique, (Y), (X)) \
  )
dpa_u_unsequenced dpa__u_api inline int dpa__u_bo_compare_unique(const dpa_u_bo_unique_t a, const dpa_u_bo_unique_t b){
  const enum dpa_u_bo_unique_type a_type = dpa_u_bo_get_type(a);
  const enum dpa_u_bo_unique_type b_type = dpa_u_bo_get_type(b);
  if(a_type != b_type)
    return a_type - b_type;
  switch(a_type){
    case DPA_U_BO_INLINE: return dpa__u_bo_compare_inline(a.bo_inline, b.bo_inline);
    case DPA_U_BO_UNIQUE_HASHMAP: return dpa_u_ptr_compare(a.bo_unique_hashmap, b.bo_unique_hashmap);
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(a)));
}

dpa_u_reproducible dpa__u_api inline int dpa__u_bo_compare_default(dpa_u_any_bo_ro_t* a, dpa_u_any_bo_ro_t* b){
  const enum dpa_u_any_bo_ro_type a_type = dpa_u_bo_get_type(a);
  const enum dpa_u_any_bo_ro_type b_type = dpa_u_bo_get_type(b);
  if(a_type == b_type)
  switch(a_type){
    case DPA_U_BO_INLINE: return dpa__u_bo_compare_inline(*(const dpa_u_bo_inline_t*)a, *(const dpa_u_bo_inline_t*)b);
    case DPA_U_BO_UNIQUE_HASHMAP: return dpa_u_ptr_compare(a, b);
    default: break;
  }
  return dpa__u_bo_compare_default_sub(
    dpa_u_t_bo_simple_ro(a),
    dpa_u_t_bo_simple_ro(b)
  );
}
