#define dpa_u_tp_any_bo(...) dpa_u_assert_selection(dpa_u_tp_any_bo_g((__VA_ARGS__)))
#define dpa_u_tp_any_bo_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo, tp_any_bo, (X)), \
    dpa__u_helper_v_g(bo_inline, tp_any_bo, (X)), \
    dpa__u_helper_v_g(bo_simple, tp_any_bo, (X)), \
    dpa__u_helper_v_g(bo_hashed, tp_any_bo, (X)), \
    dpa__u_helper_v_g(bo_refcounted, tp_any_bo, (X)), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__tp_any_bo(DPA__G(dpa_u_bo_with_hash_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__tp_any_bo(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_v_bo__tp_any_bo(X) ((dpa_u_any_bo_t*)&dpa_u_rescope(dpa_u_bo_t,X))
#define dpa__u_p_bo__tp_any_bo(X) ((dpa_u_any_bo_t*)&dpa_u_rescope(dpa_u_bo_t,*X))
#define dpa__u_cp_bo__tp_any_bo(X) ((dpa_u_any_bo_t*)&dpa_u_rescope(dpa_u_bo_t,*X))
#define dpa__u_any_bo__tp_any_bo(X) ((dpa_u_any_bo_t*)&dpa_u_rescope(union dpa__u_any_helper, dpa__u_any_bo__tp_any_bo_p((X))))
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline union dpa__u_any_helper dpa__u_any_bo__tp_any_bo_p(dpa_u_any_bo_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: {
      return (const union dpa__u_any_helper){
        .bo.bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    }
    case DPA_U_BO_SIMPLE: {
      return (const union dpa__u_any_helper){
        .bo.bo_simple = *(const dpa_u_bo_simple_t*)bo,
      };
    }
    case DPA_U_BO_HASHED: {
      return (const union dpa__u_any_helper){
        .bo_hashed = *(const dpa_u_bo_hashed_t*)bo,
      };
    }
    case DPA_U_BO_REFCOUNTED: {
      return (const union dpa__u_any_helper){
        .bo_refcounted = *(const dpa_u_bo_refcounted_t*)bo,
      };
    }
  }
  dpa_u_unreachable("dpa_u_any_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_inline__tp_any_bo(X) ((dpa_u_any_bo_t*)&(dpa_u_bo_t){ .bo_inline = (X) })
#define dpa__u_p_bo_inline__tp_any_bo(X) ((dpa_u_any_bo_t*)&(dpa_u_bo_t){ .bo_inline = *(X) })
#define dpa__u_cp_bo_inline__tp_any_bo(X) ((dpa_u_any_bo_t*)&(dpa_u_bo_t){ .bo_inline = *(X) })
#define dpa__u_any_bo_inline__tp_any_bo(X) ((dpa_u_any_bo_t*)&(dpa_u_bo_t){ .bo_inline = *(const dpa_u_bo_inline_t*)(X) })

#define dpa__u_v_bo_simple__tp_any_bo(X)  ((dpa_u_any_bo_t*)&(dpa_u_bo_t){ .bo_simple = (X) })
#define dpa__u_p_bo_simple__tp_any_bo(X)  dpa__u_v_bo_simple__tp_any_bo(*(X))
#define dpa__u_cp_bo_simple__tp_any_bo(X) dpa__u_v_bo_simple__tp_any_bo(*(X))
#define dpa__u_any_bo_simple__tp_any_bo(X) ((dpa_u_any_bo_t*)&dpa_u_rescope(union dpa__u_any_helper, dpa__u_any_bo_simple__tp_any_bo_p((X))))
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline union dpa__u_any_helper dpa__u_any_bo_simple__tp_any_bo_p(dpa_u_any_bo_simple_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_SIMPLE: {
      return (const union dpa__u_any_helper){
        .bo.bo_simple = *(const dpa_u_bo_simple_t*)bo,
      };
    }
    case DPA_U_BO_HASHED: {
      return (const union dpa__u_any_helper){
        .bo_hashed = *(const dpa_u_bo_hashed_t*)bo,
      };
    }
    case DPA_U_BO_REFCOUNTED: {
      return (const union dpa__u_any_helper){
        .bo_refcounted = *(const dpa_u_bo_refcounted_t*)bo,
      };
    }
  }
  dpa_u_unreachable("dpa_u_any_bo_simple_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_hashed__tp_any_bo(X) ((dpa_u_any_bo_t*)&dpa_u_rescope(dpa_u_bo_hashed_t, (X)))
#define dpa__u_p_bo_hashed__tp_any_bo(X) dpa__u_v_bo_hashed__tp_any_bo(*(X))
#define dpa__u_cp_bo_hashed__tp_any_bo(X) dpa__u_v_bo_hashed__tp_any_bo(*(X))
#define dpa__u_any_bo_hashed__tp_any_bo(X) dpa__u_v_bo_hashed__tp_any_bo(*(dpa_u_bo_hashed_t*)(X))

#define dpa__u_v_bo_refcounted__tp_any_bo(X) ((dpa_u_any_bo_t*)&dpa_u_rescope(dpa_u_bo_refcounted_t, (X)))
#define dpa__u_p_bo_refcounted__tp_any_bo(X) dpa__u_v_bo_refcounted__tp_any_bo(*(X))
#define dpa__u_cp_bo_refcounted__tp_any_bo(X) dpa__u_v_bo_refcounted__tp_any_bo(*(X))
#define dpa__u_any_bo_refcounted__tp_any_bo(X) dpa__u_v_bo_refcounted__tp_any_bo(*(dpa_u_bo_refcounted_t*)(X))

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline union dpa__u_any_helper dpa__u_bo_with_hash__tp_any_bo_p(dpa_u_bo_with_hash_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: {
      return (const union dpa__u_any_helper){
        .bo.bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    }
    case DPA_U_BO_HASHED: {
      return (const union dpa__u_any_helper){
        .bo_hashed = *(const dpa_u_bo_hashed_t*)bo,
      };
    }
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_hash__tp_any_bo(X) ((dpa_u_any_bo_t*)&dpa_u_rescope(union dpa__u_any_helper, dpa__u_bo_with_hash__tp_any_bo_p((X))))
#define dpa__u_bo_with_refcount__tp_any_bo(X) dpa__u_any_bo_refcounted__tp_any_bo(X)
