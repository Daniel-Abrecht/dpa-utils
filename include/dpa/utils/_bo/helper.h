
#define dpa__u_helper_g(T,P,S,X) \
    T: dpa__u_ ## P ## __ ## S(DPA__G(T,(X)))

#define dpa__u_helper_v_g(T,S,X) \
    dpa__u_helper_g(dpa_u_ ## T ## _t, v_ ## T, S, (X)), \
    dpa__u_helper_g(dpa_u_ ## T ## _t*, p_ ## T, S, (X)), \
    dpa__u_helper_g(const dpa_u_ ## T ## _t*, cp_ ## T, S, (X)), \
    dpa_u_any_ ## T ## _t*: dpa__u_any_ ## T ## __ ## S(DPA__G(dpa_u_any_ ## T ## _t*,(X)))

#define dpa__u_helper_all_g(S,X) \
    dpa__u_helper_v_g(bo_inline, S, (X)), \
    dpa__u_helper_g(dpa_u_bo_unique_hashmap_t, v_bo_unique_hashmap, S, (X)), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__ ## S((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    dpa__u_helper_v_g(bo_unique, S, (X)), \
    dpa__u_helper_v_g(bo_simple, S, (X)), \
    dpa__u_helper_v_g(bo_simple_ro, S, (X)), \
    dpa__u_helper_v_g(bo, S, (X)), \
    dpa__u_helper_v_g(bo_ro, S, (X)), \
    dpa__u_helper_v_g(bo_hashed, S, (X)), \
    dpa__u_helper_v_g(bo_hashed_ro, S, (X)), \
    dpa__u_helper_v_g(bo_refcounted, S, (X)), \
    dpa__u_helper_v_g(bo_refcounted_ro, S, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, S, (X)), \
    dpa_u_bo_gc_ro_t*: dpa__u_bo_gc_ro__ ## S(DPA__G(dpa_u_bo_gc_ro_t*,(X))), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__ ## S(DPA__G(dpa_u_bo_with_hash_t*,(X))), \
    dpa_u_bo_with_hash_ro_t*: dpa__u_bo_with_hash_ro__ ## S(DPA__G(dpa_u_bo_with_hash_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__ ## S(DPA__G(dpa_u_bo_with_refcount_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount_ro__ ## S(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__ ## S(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X)))

#define DPA__U_BOCVHV(T,F,X,...) \
  dpa_u_ ## T ## _t: F(DPA__G(dpa_u_ ## T ## _t,(X)), __VA_ARGS__), \
  dpa_u_ ## T ## _t*: F(*DPA__G(dpa_u_ ## T ## _t*,(X)), __VA_ARGS__), \
  const dpa_u_ ## T ## _t*: F(*DPA__G(const dpa_u_ ## T ## _t*,(X)), __VA_ARGS__), \
  dpa_u_any_ ## T ## _t*: F(*(dpa_u_ ## T ## _t*)DPA__G(dpa_u_any_ ## T ## _t*,(X)), __VA_ARGS__)

// This is the same as DPA__U_BOCVHV. It's a copy because I need to nest it, once, and the C preprocessor will not allow recursion.
#define DPA__U_BOCVHV2(T,F,X,...) \
  dpa_u_ ## T ## _t: F(DPA__G(dpa_u_ ## T ## _t,(X)), __VA_ARGS__), \
  dpa_u_ ## T ## _t*: F(*DPA__G(dpa_u_ ## T ## _t*,(X)), __VA_ARGS__), \
  const dpa_u_ ## T ## _t*: F(*DPA__G(const dpa_u_ ## T ## _t*,(X)), __VA_ARGS__), \
  dpa_u_any_ ## T ## _t*: F(*(dpa_u_ ## T ## _t*)DPA__G(dpa_u_any_ ## T ## _t*,(X)), __VA_ARGS__)

////

#define dpa__u_sort__priority_g(X) _Generic((X), \
    dpa_u_bo_inline_t: 0x10, \
    dpa_u_bo_inline_t*: 0x11, \
    const dpa_u_bo_inline_t*: 0x12, \
    dpa_u_any_bo_inline_t*: 0x14, \
    dpa_u_bo_unique_hashmap_t: 0x20, \
    dpa_u_any_bo_unique_hashmap_t*: 0x24, \
    dpa_u_bo_unique_t: 0x30, \
    dpa_u_bo_unique_t*: 0x31, \
    const dpa_u_bo_unique_t*: 0x32, \
    dpa_u_any_bo_unique_t*: 0x34, \
    dpa_u_bo_simple_t: 0x40, \
    dpa_u_bo_simple_t*: 0x41, \
    const dpa_u_bo_simple_t*: 0x42, \
    dpa_u_any_bo_simple_t*: 0x44, \
    dpa_u_bo_simple_ro_t: 0x50, \
    dpa_u_bo_simple_ro_t*: 0x51, \
    const dpa_u_bo_simple_ro_t*: 0x52, \
    dpa_u_any_bo_simple_ro_t*: 0x54, \
    dpa_u_bo_t: 0x60, \
    dpa_u_bo_t*: 0x61, \
    const dpa_u_bo_t*: 0x62, \
    dpa_u_any_bo_t*: 0x64, \
    dpa_u_bo_hashed_t: 0x70, \
    dpa_u_bo_hashed_t*: 0x71, \
    const dpa_u_bo_hashed_t*: 0x72, \
    dpa_u_any_bo_hashed_t*: 0x74, \
    dpa_u_bo_refcounted_t: 0x80, \
    dpa_u_bo_refcounted_t*: 0x81, \
    const dpa_u_bo_refcounted_t*: 0x82, \
    dpa_u_any_bo_refcounted_t*: 0x84, \
    dpa_u_bo_refcounted_ro_t: 0x90, \
    dpa_u_bo_refcounted_ro_t*: 0x91, \
    const dpa_u_bo_refcounted_ro_t*: 0x92, \
    dpa_u_any_bo_refcounted_ro_t*: 0x94, \
    dpa_u_bo_refcounted_hashed_ro_t: 0xA0, \
    dpa_u_bo_refcounted_hashed_ro_t*: 0xA1, \
    const dpa_u_bo_refcounted_hashed_ro_t*: 0xA2, \
    dpa_u_any_bo_refcounted_hashed_ro_t*: 0xA4, \
    dpa_u_bo_with_refcount_t*: 0xB4, \
    dpa_u_bo_with_refcount_ro_t*: 0xB5, \
    dpa_u_bo_with_refcount_and_hash_ro_t*: 0xB6, \
    dpa_u_bo_ro_t: 0xF0, \
    dpa_u_bo_ro_t*: 0xF1, \
    const dpa_u_bo_ro_t*: 0xF2, \
    dpa_u_any_bo_ro_t*: 0xF4, \
    default: 0xFFF \
  )

// This cuts down the number of type combinations I need to handle.
// For any type in the first argument, only the preceeding or same types in dpa__u_sort__priority_g are possible to appear in the second.
// Because otherwise, the arguments are swapped
// This means we can't rely on argument order anymore, but we only have to deal with each type combination once.
#define dpa__u_sort_param_by_type_g(F,X,Y) _Generic((char(*)[1+(dpa__u_sort__priority_g((X))<dpa__u_sort__priority_g((Y)))]){0}, \
    char(*)[1]: F((X),(Y), 1), \
    char(*)[2]: F((Y),(X),-1) \
  )

dpa_u_unsequenced dpa__u_really_inline dpa_u_export inline dpa_u_bo_simple_ro_t dpa__u_simple_ro_fix_type(dpa_u_bo_simple_ro_t v){
  return (dpa_u_bo_simple_ro_t){
    .type = DPA_U_BO_SIMPLE,
    .size = v.size,
    .data = v.data,
  };
}

dpa_u_unsequenced dpa__u_really_inline dpa_u_export inline dpa_u_bo_simple_t dpa__u_simple_fix_type(dpa_u_bo_simple_t v){
  return (dpa_u_bo_simple_t){
    .type = DPA_U_BO_SIMPLE,
    .size = v.size,
    .data = v.data,
  };
}

dpa_u_unsequenced dpa__u_really_inline dpa_u_export inline dpa_u_bo_hashed_ro_t dpa__u_hashed_ro_fix_type(dpa_u_bo_hashed_ro_t v){
  return (dpa_u_bo_hashed_ro_t){
    .bo_simple = {
      .type = DPA_U_BO_HASHED,
      .size = v.bo_simple.size,
      .data = v.bo_simple.data,
    },
    .hash = v.hash,
  };
}
