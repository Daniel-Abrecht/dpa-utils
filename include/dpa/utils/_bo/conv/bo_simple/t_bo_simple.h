#define dpa_u_t_bo_simple(...) dpa_u_assert_selection(dpa_u_t_bo_simple_g((__VA_ARGS__)))
#define dpa_u_tp_bo_simple(...) &dpa_u_assert_selection(dpa_u_t_bo_simple_g((__VA_ARGS__)))
#define dpa_u_t_bo_simple_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo, t_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_inline, t_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_simple, t_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_hashed, t_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_refcounted, t_bo_simple, (X)), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__t_bo_simple(DPA__G(dpa_u_bo_with_hash_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__t_bo_simple(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_t_bo_simple__helper(P,X) (dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa__u_ ## P ## __get_size((X)), .data=dpa__u_ ## P ## __data((X)) }
#define dpa__u_t_bo_simple__helper_s1(X) dpa_u_rescope(dpa_u_bo_simple_t, dpa__u_simple_fix_type((X)))

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_simple_t dpa__u_p_bo_inline__t_bo_simple_p(dpa_u_bo_inline_t*const bo){
  return (const dpa_u_bo_simple_t){
    .type = DPA_U_BO_SIMPLE,
    .size = dpa__u_p_bo_inline__get_size(bo),
    .data = dpa__u_p_bo_inline__data(bo),
  };
}
#define dpa__u_v_bo_inline__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t, dpa__u_p_bo_inline__t_bo_simple_p(&dpa_u_rescope(dpa_u_bo_inline_t,(X))))
#define dpa__u_p_bo_inline__t_bo_simple(X) dpa__u_v_bo_inline__t_bo_simple(*(X))
#define dpa__u_cp_bo_inline__t_bo_simple(X) dpa__u_v_bo_inline__t_bo_simple(*(X))
#define dpa__u_any_bo_inline__t_bo_simple(X) dpa__u_v_bo_inline__t_bo_simple(*(const dpa_u_bo_inline_t*)(X))

#define dpa__u_v_bo_simple__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t, (X))
#define dpa__u_p_bo_simple__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t, *(X))
#define dpa__u_cp_bo_simple__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t, *(X))
#define dpa__u_any_bo_simple__t_bo_simple(X) dpa__u_t_bo_simple__helper_s1(*(const dpa_u_bo_simple_t*)(X))

#define dpa__u_v_bo_hashed__t_bo_simple(X) dpa__u_t_bo_simple__helper_s1((X).bo_simple)
#define dpa__u_p_bo_hashed__t_bo_simple(X) dpa__u_t_bo_simple__helper_s1((X)->bo_simple)
#define dpa__u_cp_bo_hashed__t_bo_simple(X) dpa__u_t_bo_simple__helper_s1((X)->bo_simple)
#define dpa__u_any_bo_hashed__t_bo_simple(X) dpa__u_t_bo_simple__helper_s1(*(const dpa_u_bo_simple_t*)(X))

#define dpa__u_v_bo_refcounted__t_bo_simple(X) dpa__u_t_bo_simple__helper_s1((X).bo_simple)
#define dpa__u_p_bo_refcounted__t_bo_simple(X) dpa__u_t_bo_simple__helper_s1((X)->bo_simple)
#define dpa__u_cp_bo_refcounted__t_bo_simple(X) dpa__u_t_bo_simple__helper_s1((X)->bo_simple)
#define dpa__u_any_bo_refcounted__t_bo_simple(X) dpa__u_t_bo_simple__helper_s1(*(const dpa_u_bo_simple_t*)(X))

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_simple_t dpa__u_p_bo__t_bo_simple_p(dpa_u_bo_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_SIMPLE: {
      return bo->bo_simple;
    }
    case DPA_U_BO_INLINE: {
      return (const dpa_u_bo_simple_t){
        .type = DPA_U_BO_SIMPLE,
        .size = dpa__u_v_bo_inline__get_size(bo->bo_inline),
        .data = dpa__u_v_bo_inline__data(bo->bo_inline),
      };
    }
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_v_bo__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t,dpa__u_p_bo__t_bo_simple_p(&dpa_u_rescope(dpa_u_bo_t,(X))))
#define dpa__u_p_bo__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t,dpa__u_p_bo__t_bo_simple_p(&dpa_u_rescope(dpa_u_bo_t,(*(X)))))
#define dpa__u_cp_bo__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t,dpa__u_p_bo__t_bo_simple_p(&dpa_u_rescope(dpa_u_bo_t,(*(X)))))
#define dpa__u_any_bo__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t,dpa__u_p_bo__t_bo_simple_p(&dpa__u_any_bo__t_bo(X)))

#define dpa__u_bo_with_hash__t_bo_simple(X) dpa_u_rescope(dpa_u_bo_simple_t,dpa__u_p_bo__t_bo_simple_p(&dpa__u_any_bo__t_bo((dpa_u_any_bo_t*)(X)))) // hack
#define dpa__u_bo_with_refcount__t_bo_simple(X) dpa__u_t_bo_simple__helper_s1(*(const dpa_u_bo_simple_t*)(X))
