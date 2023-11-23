#define dpa_u_v_bo_ro(...) dpa_u_assert_selection(dpa_u_v_bo_ro_g(__VA_ARGS__))
#define dpa_u_v_bo_ro_g(X) dpa_u_generic((X),dpa__u_helper_all_g(v_bo_ro,(X)))

#define dpa__u_v_bo_ro__helper(P,X) (const dpa_u_bo_ro_t){ .bo_simple = { .type = DPA_U_BO_SIMPLE, .size=dpa__u_ ## P ## __get_size((X)), .data=dpa__u_ ## P ## __data((X)) } }

#define dpa__u_v_bo__v_bo_ro(X) (X).ro
#define dpa__u_p_bo__v_bo_ro(X) (X)->ro
#define dpa__u_cp_bo__v_bo_ro(X) (X)->ro
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline dpa_u_bo_ro_t dpa__u_any_bo__v_bo_ro(dpa_u_any_bo_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (const dpa_u_bo_ro_t){
        .bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    case DPA_U_BO_SIMPLE:
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED:
      return (const dpa_u_bo_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple_ro__get_size(bo),
          .data = dpa__u_any_bo_simple_ro__data(bo),
        }
      };
  }
  dpa_u_unreachable("dpa_u_any_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_ro__v_bo_ro(X) (X)
#define dpa__u_p_bo_ro__v_bo_ro(X) (X)[0]
#define dpa__u_cp_bo_ro__v_bo_ro(X) (X)[0]
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline dpa_u_bo_ro_t dpa__u_any_bo_ro__v_bo_ro(dpa_u_any_bo_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (const dpa_u_bo_ro_t){
        .bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    case DPA_U_BO_UNIQUE_HASHMAP:
      return (const dpa_u_bo_ro_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)bo,
      };
    case DPA_U_BO_SIMPLE:
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED:
      return (const dpa_u_bo_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple_ro__get_size(bo),
          .data = dpa__u_any_bo_simple_ro__data(bo),
        }
      };
  }
  dpa_u_unreachable("dpa_u_any_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_inline__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_inline = (X) }
#define dpa__u_p_bo_inline__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_inline = *(X) }
#define dpa__u_cp_bo_inline__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_inline = *(X) }
#define dpa__u_any_bo_inline__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_inline = *(const dpa_u_bo_inline_t*)(X) }

#define dpa__u_v_bo_simple__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = (X).ro }
#define dpa__u_p_bo_simple__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = (X)->ro }
#define dpa__u_cp_bo_simple__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = (X)->ro }
#define dpa__u_any_bo_simple__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = { .type=DPA_U_BO_SIMPLE, .size=dpa__u_any_bo_simple__get_size((X)), .data=dpa__u_any_bo_simple__data((X)) } }

#define dpa__u_v_bo_simple_ro__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = (X) }
#define dpa__u_p_bo_simple_ro__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = *(X) }
#define dpa__u_cp_bo_simple_ro__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = *(X) }
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline dpa_u_bo_ro_t dpa__u_any_bo_simple_ro__v_bo_ro(dpa_u_any_bo_simple_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP:
      return (const dpa_u_bo_ro_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)bo,
      };
    case DPA_U_BO_SIMPLE:
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED:
      return (const dpa_u_bo_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple_ro__get_size(bo),
          .data = dpa__u_any_bo_simple_ro__data(bo),
        }
      };
  }
  dpa_u_unreachable("dpa_u_any_bo_simple_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_unique_hashmap__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (X) }
#define dpa__u_p_bo_unique_hashmap__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (X) }
#define dpa__u_cp_bo_unique_hashmap__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (X) }
#define dpa__u_any_bo_unique_hashmap__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)(X) }

#define dpa__u_v_bo_unique__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique = (X) }
#define dpa__u_p_bo_unique__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique = *(X) }
#define dpa__u_cp_bo_unique__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique = *(X) }
#define dpa__u_any_bo_unique__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_unique = *(const dpa_u_bo_unique_t*)(X) }

#define dpa__u_v_bo_hashed__v_bo_ro(X) dpa__u_v_bo_ro__helper(v_bo_hashed,(X))
#define dpa__u_p_bo_hashed__v_bo_ro(X) dpa__u_v_bo_ro__helper(p_bo_hashed,(X))
#define dpa__u_cp_bo_hashed__v_bo_ro(X) dpa__u_v_bo_ro__helper(cp_bo_hashed,(X))
#define dpa__u_any_bo_hashed__v_bo_ro(X) dpa__u_v_bo_ro__helper(any_bo_hashed,(X))

#define dpa__u_v_bo_hashed_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(v_bo_hashed_ro,(X))
#define dpa__u_p_bo_hashed_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(p_bo_hashed_ro,(X))
#define dpa__u_cp_bo_hashed_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(cp_bo_hashed_ro,(X))
#define dpa__u_any_bo_hashed_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(any_bo_hashed_ro,(X))

#define dpa__u_v_bo_refcounted__v_bo_ro(X) dpa__u_v_bo_ro__helper(v_bo_refcounted,(X))
#define dpa__u_p_bo_refcounted__v_bo_ro(X) dpa__u_v_bo_ro__helper(p_bo_refcounted,(X))
#define dpa__u_cp_bo_refcounted__v_bo_ro(X) dpa__u_v_bo_ro__helper(cp_bo_refcounted,(X))
#define dpa__u_any_bo_refcounted__v_bo_ro(X) dpa__u_v_bo_ro__helper(any_bo_refcounted,(X))

#define dpa__u_v_bo_refcounted_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(v_bo_refcounted_ro,(X))
#define dpa__u_p_bo_refcounted_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(p_bo_refcounted_ro,(X))
#define dpa__u_cp_bo_refcounted_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(cp_bo_refcounted_ro,(X))
#define dpa__u_any_bo_refcounted_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(any_bo_refcounted_ro,(X))

#define dpa__u_v_bo_refcounted_hashed_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(v_bo_refcounted_hashed_ro,(X))
#define dpa__u_p_bo_refcounted_hashed_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(p_bo_refcounted_hashed_ro,(X))
#define dpa__u_cp_bo_refcounted_hashed_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(cp_bo_refcounted_hashed_ro,(X))
#define dpa__u_any_bo_refcounted_hashed_ro__v_bo_ro(X) dpa__u_v_bo_ro__helper(any_bo_refcounted_hashed_ro,(X))

dpa_u_reproducible dpa__u_really_inline dpa_u_export inline dpa_u_bo_ro_t dpa__u_bo_gc_ro__v_bo_ro(dpa_u_bo_gc_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (const dpa_u_bo_ro_t){
        .bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    case DPA_U_BO_UNIQUE_HASHMAP:
      return (const dpa_u_bo_ro_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)bo,
      };
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED:
      return (const dpa_u_bo_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple_ro__get_size(bo),
          .data = dpa__u_any_bo_simple_ro__data(bo),
        }
      };
  }
  dpa_u_unreachable("dpa_u_bo_gc_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline dpa_u_bo_ro_t dpa__u_bo_with_hash_ro__v_bo_ro(dpa_u_bo_with_hash_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (const dpa_u_bo_ro_t){
        .bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    case DPA_U_BO_UNIQUE_HASHMAP:
      return (const dpa_u_bo_ro_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)bo,
      };
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED_HASHED:
      return (const dpa_u_bo_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple_ro__get_size(bo),
          .data = dpa__u_any_bo_simple_ro__data(bo),
        }
      };
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline dpa_u_bo_ro_t dpa__u_bo_with_hash__v_bo_ro(dpa_u_bo_with_hash_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (const dpa_u_bo_ro_t){
        .bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    case DPA_U_BO_HASHED:
      return (const dpa_u_bo_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple_ro__get_size(bo),
          .data = dpa__u_any_bo_simple_ro__data(bo),
        }
      };
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline dpa_u_bo_ro_t dpa__u_bo_with_refcount_ro__v_bo_ro(dpa_u_bo_with_refcount_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP:
      return (const dpa_u_bo_ro_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)bo,
      };
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED:
      return (const dpa_u_bo_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple_ro__get_size(bo),
          .data = dpa__u_any_bo_simple_ro__data(bo),
        }
      };
  }
  dpa_u_unreachable("dpa_u_bo_with_refcount_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount__v_bo_ro(X) (const dpa_u_bo_ro_t){ .bo_simple = { .type=DPA_U_BO_SIMPLE, .size=dpa__u_any_bo_refcounted_hashed_ro__get_size((X)), .data=dpa__u_any_bo_refcounted_hashed_ro__data((X)) } }
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline dpa_u_bo_ro_t dpa__u_bo_with_refcount_and_hash_ro__v_bo_ro(dpa_u_bo_with_refcount_and_hash_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP:
      return (const dpa_u_bo_ro_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)bo,
      };
    case DPA_U_BO_REFCOUNTED_HASHED:
      return (const dpa_u_bo_ro_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple_ro__get_size(bo),
          .data = dpa__u_any_bo_simple_ro__data(bo),
        }
      };
  }
  dpa_u_unreachable("dpa_u_bo_with_refcount_and_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
