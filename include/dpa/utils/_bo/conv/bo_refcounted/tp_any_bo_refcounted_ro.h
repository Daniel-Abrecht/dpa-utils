#define dpa_u_tp_any_bo_refcounted_ro(...) dpa_u_assert_selection(dpa_u_tp_any_bo_refcounted_ro_g((__VA_ARGS__)))
#define dpa_u_tp_any_bo_refcounted_ro_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__tp_any_bo_refcounted_ro(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__tp_any_bo_refcounted_ro((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*, (X))), \
    dpa__u_helper_v_g(bo_refcounted_ro, tp_any_bo_refcounted_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted, tp_any_bo_refcounted_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, tp_any_bo_refcounted_ro, (X)), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__tp_any_bo_refcounted_ro(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount_ro__tp_any_bo_refcounted_ro(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__tp_any_bo_refcounted_ro(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_v_bo_unique_hashmap__tp_any_bo_refcounted_ro(X) ((dpa_u_any_bo_refcounted_ro_t*)&dpa__u_v_bo_unique_hashmap__t_bo_refcounted_ro((X)))
#define dpa__u_any_bo_unique_hashmap__tp_any_bo_refcounted_ro(X) ((dpa_u_any_bo_refcounted_ro_t*)&dpa__u_v_any_bo_unique_hashmap__t_bo_refcounted_ro((X)))

#define dpa__u_v_bo_refcounted_ro__tp_any_bo_refcounted_ro(X)   ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_ro_t,  (X)))
#define dpa__u_p_bo_refcounted_ro__tp_any_bo_refcounted_ro(X)   ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_ro_t, *(X)))
#define dpa__u_cp_bo_refcounted_ro__tp_any_bo_refcounted_ro(X)  ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_ro_t, *(X)))
#define dpa__u_any_bo_refcounted_ro__tp_any_bo_refcounted_ro(X) ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(union dpa__u_any_ro_helper_2, dpa__u_any_bo_refcounted_ro__tp_any_bo_refcounted_ro_p((X))))
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline union dpa__u_any_ro_helper_2 dpa__u_any_bo_refcounted_ro__tp_any_bo_refcounted_ro_p(const dpa_u_any_bo_refcounted_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_REFCOUNTED: {
      return (const union dpa__u_any_ro_helper_2){
        .bo_refcounted = *(dpa_u_bo_refcounted_ro_t*)bo,
      };
    }
    case DPA_U_BO_REFCOUNTED_HASHED: {
      return (const union dpa__u_any_ro_helper_2){
        .bo_refcounted_hashed = *(dpa_u_bo_refcounted_hashed_ro_t*)bo,
      };
    }
  }
  dpa_u_unreachable("dpa_u_bo_with_refcount_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_refcounted__tp_any_bo_refcounted_ro(X)   ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_ro_t, (X).ro))
#define dpa__u_p_bo_refcounted__tp_any_bo_refcounted_ro(X)   ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_ro_t, (X)->ro))
#define dpa__u_cp_bo_refcounted__tp_any_bo_refcounted_ro(X)  ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_ro_t, (X)->ro))
#define dpa__u_any_bo_refcounted__tp_any_bo_refcounted_ro(X) ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_ro_t, *(dpa_u_bo_refcounted_ro_t*)(X)))

#define dpa__u_v_bo_refcounted_hashed_ro__tp_any_bo_refcounted_ro(X) ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t, (X)))
#define dpa__u_p_bo_refcounted_hashed_ro__tp_any_bo_refcounted_ro(X) ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t, *(X)))
#define dpa__u_cp_bo_refcounted_hashed_ro__tp_any_bo_refcounted_ro(X) ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t, *(X)))
#define dpa__u_any_bo_refcounted_hashed_ro__tp_any_bo_refcounted_ro(X) ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_hashed_ro_t, *(dpa_u_bo_refcounted_hashed_ro_t*)(X)))

#define dpa__u_bo_with_refcount_and_hash_ro__tp_any_bo_refcounted_ro(X) ((dpa_u_any_bo_refcounted_ro_t*)dpa__u_bo_any_unpack_ptr(&dpa_u_rescope(union dpa__u_any_ro_helper_2,dpa__u_bo_with_refcount_and_hash_ro__tp_any_bo_refcounted_ro_p(X))))
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline union dpa__u_any_ro_helper_2 dpa__u_bo_with_refcount_and_hash_ro__tp_any_bo_refcounted_ro_p(const dpa_u_bo_with_refcount_and_hash_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: {
      return (const union dpa__u_any_ro_helper_2){
        .bo = {
          .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
          .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)bo,
        }
      };
    }
    case DPA_U_BO_REFCOUNTED_HASHED: {
      return (const union dpa__u_any_ro_helper_2){
        .bo_refcounted_hashed = *(dpa_u_bo_refcounted_hashed_ro_t*)bo,
      };
    }
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount_ro__tp_any_bo_refcounted_ro(X) ((dpa_u_any_bo_refcounted_ro_t*)dpa__u_bo_any_unpack_ptr(&dpa_u_rescope(union dpa__u_any_ro_helper_2, dpa__u_bo_with_refcount_ro__tp_any_bo_refcounted_ro_p(X))))
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline union dpa__u_any_ro_helper_2 dpa__u_bo_with_refcount_ro__tp_any_bo_refcounted_ro_p(const dpa_u_bo_with_refcount_ro_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: {
      return (const union dpa__u_any_ro_helper_2){
        .bo = {
          .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
          .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)bo,
        }
      };
    }
    case DPA_U_BO_REFCOUNTED: {
      return (const union dpa__u_any_ro_helper_2){
        .bo_refcounted = *(dpa_u_bo_refcounted_ro_t*)bo,
      };
    }
    case DPA_U_BO_REFCOUNTED_HASHED: {
      return (const union dpa__u_any_ro_helper_2){
        .bo_refcounted_hashed = *(dpa_u_bo_refcounted_hashed_ro_t*)bo,
      };
    }
  }
  dpa_u_unreachable("dpa_u_bo_with_refcount_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount__tp_any_bo_refcounted_ro(X) ((dpa_u_any_bo_refcounted_ro_t*)&dpa_u_rescope(dpa_u_bo_refcounted_ro_t,*(dpa_u_bo_refcounted_ro_t*)(X))) /*TODO*/
