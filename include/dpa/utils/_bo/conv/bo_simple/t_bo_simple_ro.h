#define dpa_u_t_bo_simple_ro(...) dpa_u_assert_selection(dpa_u_t_bo_simple_ro_g((__VA_ARGS__)))
#define dpa_u_t_bo_simple_ro_g(X) dpa_u_generic((X),dpa__u_helper_all_g(t_bo_simple_ro,(X)))

#define dpa__u_t_bo_simple_ro__helper_s1(X) dpa_u_rescope(dpa_u_bo_simple_ro_t, dpa__u_simple_ro_fix_type((X)))

#define dpa__u_v_bo_unique_hashmap__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X)->bo_hashed.bo_simple)
#define dpa__u_any_bo_unique_hashmap__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1(((dpa_u_bo_unique_hashmap_t)(X))->bo_hashed.bo_simple)

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_simple_ro_t dpa__u_p_bo_inline__t_bo_simple_ro_p(dpa_u_bo_inline_t*const bo){
  return (const dpa_u_bo_simple_ro_t){
    .type = DPA_U_BO_SIMPLE,
    .size = dpa__u_p_bo_inline__get_size(bo),
    .data = dpa__u_p_bo_inline__data(bo),
  };
}
#define dpa__u_v_bo_inline__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t, dpa__u_p_bo_inline__t_bo_simple_ro_p(&dpa_u_rescope(dpa_u_bo_inline_t,(X))))
#define dpa__u_p_bo_inline__t_bo_simple_ro(X) dpa__u_v_bo_inline__t_bo_simple_ro(*(X))
#define dpa__u_cp_bo_inline__t_bo_simple_ro(X) dpa__u_v_bo_inline__t_bo_simple_ro(*(X))
#define dpa__u_any_bo_inline__t_bo_simple_ro(X) dpa__u_v_bo_inline__t_bo_simple_ro(*(const dpa_u_bo_inline_t*)(X))

#define dpa__u_v_bo_simple__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t, (X).ro)
#define dpa__u_p_bo_simple__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t, (X)->ro)
#define dpa__u_cp_bo_simple__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t, (X)->ro)
#define dpa__u_any_bo_simple__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1(*(const dpa_u_bo_simple_ro_t*)(X))

#define dpa__u_v_bo_simple_ro__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t, (X))
#define dpa__u_p_bo_simple_ro__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t, *(X))
#define dpa__u_cp_bo_simple_ro__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t, *(X))
#define dpa__u_any_bo_simple_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1(*(const dpa_u_bo_simple_ro_t*)(X))

#define dpa__u_v_bo_hashed__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X).bo_simple.ro)
#define dpa__u_p_bo_hashed__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X)->bo_simple.ro)
#define dpa__u_cp_bo_hashed__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X)->bo_simple.ro)
#define dpa__u_any_bo_hashed__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1(*(const dpa_u_bo_simple_ro_t*)(X))

#define dpa__u_v_bo_hashed_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X).bo_simple)
#define dpa__u_p_bo_hashed_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X)->bo_simple)
#define dpa__u_cp_bo_hashed_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X)->bo_simple)
#define dpa__u_any_bo_hashed_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1(*(const dpa_u_bo_simple_ro_t*)(X))

#define dpa__u_v_bo_refcounted__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X).bo_simple.ro)
#define dpa__u_p_bo_refcounted__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X)->bo_simple.ro)
#define dpa__u_cp_bo_refcounted__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X)->bo_simple.ro)
#define dpa__u_any_bo_refcounted__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1(*(const dpa_u_bo_simple_ro_t*)(X))

#define dpa__u_v_bo_refcounted_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X).bo_simple)
#define dpa__u_p_bo_refcounted_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X)->bo_simple)
#define dpa__u_cp_bo_refcounted_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X)->bo_simple)
#define dpa__u_any_bo_refcounted_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1(*(const dpa_u_bo_simple_ro_t*)(X))

#define dpa__u_v_bo_refcounted_hashed_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X).bo_refcounted.bo_simple)
#define dpa__u_p_bo_refcounted_hashed_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X)->bo_refcounted.bo_simple)
#define dpa__u_cp_bo_refcounted_hashed_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1((X)->bo_refcounted.bo_simple)
#define dpa__u_any_bo_refcounted_hashed_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1(*(const dpa_u_bo_simple_ro_t*)(X))

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_simple_ro_t dpa__u_p_bo_unique__t_bo_simple_ro_p(const dpa_u_bo_unique_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: {
      return (const dpa_u_bo_simple_ro_t){
        .type = DPA_U_BO_SIMPLE,
        .size = dpa__u_v_bo_unique_hashmap__get_size(bo->bo_unique_hashmap),
        .data = dpa__u_v_bo_unique_hashmap__data(bo->bo_unique_hashmap),
      };
    }
    case DPA_U_BO_INLINE: {
      return (const dpa_u_bo_simple_ro_t){
        .type = DPA_U_BO_SIMPLE,
        .size = dpa__u_v_bo_inline__get_size(bo->bo_inline),
        .data = dpa__u_v_bo_inline__data(bo->bo_inline),
      };
    }
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_v_bo_unique__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo_unique__t_bo_simple_ro_p(&dpa_u_rescope(const dpa_u_bo_unique_t,(X))))
#define dpa__u_p_bo_unique__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo_unique__t_bo_simple_ro_p(&dpa_u_rescope(const dpa_u_bo_unique_t,(*(X)))))
#define dpa__u_cp_bo_unique__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo_unique__t_bo_simple_ro_p(&dpa_u_rescope(const dpa_u_bo_unique_t,(*(X)))))
#define dpa__u_any_bo_unique__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo_unique__t_bo_simple_ro_p(&dpa__u_any_bo_unique__t_bo_unique(X)))

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_simple_ro_t dpa__u_p_bo__t_bo_simple_ro_p(const dpa_u_bo_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_SIMPLE: {
      return bo->bo_simple.ro;
    }
    case DPA_U_BO_INLINE: {
      return (const dpa_u_bo_simple_ro_t){
        .type = DPA_U_BO_SIMPLE,
        .size = dpa__u_v_bo_inline__get_size(bo->bo_inline),
        .data = dpa__u_v_bo_inline__data(bo->bo_inline),
      };
    }
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_v_bo__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo__t_bo_simple_ro_p(&dpa_u_rescope(const dpa_u_bo_t,(X))))
#define dpa__u_p_bo__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo__t_bo_simple_ro_p(&dpa_u_rescope(const dpa_u_bo_t,(*(X)))))
#define dpa__u_cp_bo__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo__t_bo_simple_ro_p(&dpa_u_rescope(const dpa_u_bo_t,(*(X)))))
#define dpa__u_any_bo__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo__t_bo_simple_ro_p(&dpa__u_any_bo__t_bo(X)))

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_ro_t dpa__u_p_bo_ro__t_bo_simple_ro_p2_sub(dpa_u_any_bo_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: {
      return (const dpa_u_bo_ro_t){
        .bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    }
    case DPA_U_BO_UNIQUE_HASHMAP:
    case DPA_U_BO_SIMPLE:
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED: {
      return (const dpa_u_bo_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple_ro__get_size(bo),
          .data = dpa__u_any_bo_simple_ro__data(bo),
        }
      };
    }
  }
  dpa_u_unreachable("dpa_u_any_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_simple_ro_t dpa__u_p_bo_ro__t_bo_simple_ro_p1(const dpa_u_bo_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_SIMPLE: {
      return bo->bo_simple;
    }
    case DPA_U_BO_INLINE: {
      return (const dpa_u_bo_simple_ro_t){
        .type = DPA_U_BO_SIMPLE,
        .size = dpa__u_v_bo_inline__get_size(bo->bo_inline),
        .data = dpa__u_v_bo_inline__data(bo->bo_inline),
      };
    }
    case DPA_U_BO_UNIQUE_HASHMAP: {
      return (const dpa_u_bo_simple_ro_t){
        .type = DPA_U_BO_SIMPLE,
        .size = dpa__u_v_bo_unique_hashmap__get_size(bo->bo_unique_hashmap),
        .data = dpa__u_v_bo_unique_hashmap__data(bo->bo_unique_hashmap),
      };
    }
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_simple_ro_t dpa__u_p_bo_ro__t_bo_simple_ro_p2(const dpa_u_bo_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_SIMPLE: {
      return bo->bo_simple;
    }
    case DPA_U_BO_INLINE: {
      return (const dpa_u_bo_simple_ro_t){
        .type = DPA_U_BO_SIMPLE,
        .size = dpa__u_v_bo_inline__get_size(bo->bo_inline),
        .data = dpa__u_v_bo_inline__data(bo->bo_inline),
      };
    }
    case DPA_U_BO_UNIQUE_HASHMAP: break;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_v_bo_ro__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo_ro__t_bo_simple_ro_p1(&dpa_u_rescope(const dpa_u_bo_ro_t,(X))))
#define dpa__u_p_bo_ro__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo_ro__t_bo_simple_ro_p1(&dpa_u_rescope(const dpa_u_bo_ro_t,(*(X)))))
#define dpa__u_cp_bo_ro__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo_ro__t_bo_simple_ro_p1(&dpa_u_rescope(const dpa_u_bo_ro_t,(*(X)))))
#define dpa__u_any_bo_ro__t_bo_simple_ro(X) dpa_u_rescope(dpa_u_bo_simple_ro_t,dpa__u_p_bo_ro__t_bo_simple_ro_p2(&dpa_u_rescope(const dpa_u_bo_ro_t,dpa__u_p_bo_ro__t_bo_simple_ro_p2_sub(X))))

#define dpa__u_bo_gc_ro__t_bo_simple_ro(X) dpa__u_any_bo_ro__t_bo_simple_ro((dpa_u_any_bo_ro_t*)(X)) // Hack: allows a few more dynamic types than necessary
#define dpa__u_bo_with_hash_ro__t_bo_simple_ro(X) dpa__u_any_bo_ro__t_bo_simple_ro((dpa_u_any_bo_ro_t*)(X)) // "
#define dpa__u_bo_with_hash__t_bo_simple_ro(X) dpa__u_any_bo_ro__t_bo_simple_ro((dpa_u_any_bo_ro_t*)(X)) // "
#define dpa__u_bo_with_refcount_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1(*(const dpa_u_bo_simple_ro_t*)(X))
#define dpa__u_bo_with_refcount__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1(*(const dpa_u_bo_simple_ro_t*)(X))
#define dpa__u_bo_with_refcount_and_hash_ro__t_bo_simple_ro(X) dpa__u_t_bo_simple_ro__helper_s1(*(const dpa_u_bo_simple_ro_t*)(X))
