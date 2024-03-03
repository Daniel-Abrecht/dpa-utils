#define dpa_u_tp_any_bo_simple(...) dpa_u_assert_selection(dpa_u_tp_any_bo_simple_g((__VA_ARGS__)))
#define dpa_u_tp_any_bo_simple_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo, tp_any_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_inline, tp_any_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_simple, tp_any_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_hashed, tp_any_bo_simple, (X)), \
    dpa__u_helper_v_g(bo_refcounted, tp_any_bo_simple, (X)), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__tp_any_bo_simple(DPA__G(dpa_u_bo_with_hash_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__tp_any_bo_simple(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_v_bo_inline__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_simple_t, dpa__u_p_bo_inline__t_bo_simple_p(&dpa_u_rescope(dpa_u_bo_inline_t,(X)))))
#define dpa__u_p_bo_inline__tp_any_bo_simple(X) dpa__u_v_bo_inline__tp_any_bo_simple(*(X))
#define dpa__u_cp_bo_inline__tp_any_bo_simple(X) dpa__u_v_bo_inline__tp_any_bo_simple(*(X))
#define dpa__u_any_bo_inline__tp_any_bo_simple(X) dpa__u_v_bo_inline__tp_any_bo_simple(*(const dpa_u_bo_inline_t*)(X))

#define dpa__u_v_bo_simple__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_simple_t, (X)))
#define dpa__u_p_bo_simple__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_simple_t, *(X)))
#define dpa__u_cp_bo_simple__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_simple_t, *(X)))
#define dpa__u_any_bo_simple__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(union dpa__u_any_helper,dpa__u_any_bo_simple__tp_any_bo_simple_p((X))))
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline union dpa__u_any_helper dpa__u_any_bo_simple__tp_any_bo_simple_p(dpa_u_any_bo_simple_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_SIMPLE: {
      return (const union dpa__u_any_helper){
        .bo.bo_simple = *(dpa_u_bo_simple_t*)bo,
      };
    }
    case DPA_U_BO_REFCOUNTED: {
      return (const union dpa__u_any_helper){
        .bo_refcounted = *(dpa_u_bo_refcounted_t*)bo,
      };
    }
    case DPA_U_BO_HASHED: {
      return (const union dpa__u_any_helper){
        .bo_hashed = *(dpa_u_bo_hashed_t*)bo,
      };
    }
  }
  dpa_u_unreachable("dpa_u_any_bo_simple_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_hashed__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_hashed_t, (X)))
#define dpa__u_p_bo_hashed__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_hashed_t, *(X)))
#define dpa__u_cp_bo_hashed__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_hashed_t, *(X)))
#define dpa__u_any_bo_hashed__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_hashed_t, *(dpa_u_bo_hashed_t*)(X)))

#define dpa__u_v_bo_refcounted__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_refcounted_t, (X)))
#define dpa__u_p_bo_refcounted__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_refcounted_t, *(X)))
#define dpa__u_cp_bo_refcounted__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_refcounted_t, *(X)))
#define dpa__u_any_bo_refcounted__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_refcounted_t, *(dpa_u_bo_refcounted_t*)(X)))

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_simple_t dpa__u_p_bo__tp_any_bo_simple_p(dpa_u_bo_t* bo){
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
#define dpa__u_v_bo__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_simple_t,dpa__u_p_bo__tp_any_bo_simple_p(&dpa_u_rescope(dpa_u_bo_t,(X)))))
#define dpa__u_p_bo__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_simple_t,dpa__u_p_bo__tp_any_bo_simple_p(&dpa_u_rescope(dpa_u_bo_t,(*(X))))))
#define dpa__u_cp_bo__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(dpa_u_bo_simple_t,dpa__u_p_bo__tp_any_bo_simple_p(&dpa_u_rescope(dpa_u_bo_t,(*(X))))))
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline union dpa__u_any_helper dpa__u_any_bo__tp_any_bo_simple_p(union dpa__u_bo_ptr_helper*restrict bo){
  switch(bo->meta.type){
    case DPA_U_BO_SIMPLE: {
      return (const union dpa__u_any_helper){
        .bo.bo_simple = *(dpa_u_bo_simple_t*)(bo->ptr),
      };
    }
    case DPA_U_BO_INLINE: {
      return (const union dpa__u_any_helper){
        .bo.bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_p_bo_inline__get_size(&bo->bo_inline),
          .data = dpa__u_p_bo_inline__data(&bo->bo_inline),
        },
      };
    }
    case DPA_U_BO_REFCOUNTED: {
      return (const union dpa__u_any_helper){
        .bo_refcounted = *(dpa_u_bo_refcounted_t*)(bo->ptr),
      };
    }
    case DPA_U_BO_HASHED: {
      return (const union dpa__u_any_helper){
        .bo_hashed = *(dpa_u_bo_hashed_t*)(bo->ptr),
      };
    }
  }
  dpa_u_unreachable("dpa_u_any_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, bo->meta.type));
}
#define dpa__u_any_bo__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(union dpa__u_any_helper,dpa__u_any_bo__tp_any_bo_simple_p(dpa__u_bo_any_inline_ptr_h((X)))))

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline union dpa__u_any_helper dpa__u_bo_with_hash__tp_any_bo_simple_p(union dpa__u_bo_ptr_helper*restrict bo){
  switch(bo->meta.type){
    case DPA_U_BO_INLINE: {
      return (const union dpa__u_any_helper){
        .bo.bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_p_bo_inline__get_size(&bo->bo_inline),
          .data = dpa__u_p_bo_inline__data(&bo->bo_inline),
        },
      };
    }
    case DPA_U_BO_HASHED: {
      return (const union dpa__u_any_helper){
        .bo_hashed = *(dpa_u_bo_hashed_t*)bo->ptr,
      };
    }
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, bo->meta.type));
}
#define dpa__u_bo_with_hash__tp_any_bo_simple(X) ((dpa_u_any_bo_simple_t*)&dpa_u_rescope(union dpa__u_any_helper,dpa__u_bo_with_hash__tp_any_bo_simple_p(dpa__u_bo_any_inline_ptr_h((X)))))
#define dpa__u_bo_with_refcount__tp_any_bo_simple(X) dpa__u_any_bo_refcounted__tp_any_bo_simple((X))
