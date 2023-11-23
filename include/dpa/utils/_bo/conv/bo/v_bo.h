#define dpa_u_v_bo(...) dpa_u_assert_selection(dpa_u_v_bo_g(__VA_ARGS__))
#define dpa_u_v_bo_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo, v_bo, (X)), \
    dpa__u_helper_v_g(bo_inline, v_bo, (X)), \
    dpa__u_helper_v_g(bo_simple, v_bo, (X)), \
    dpa__u_helper_v_g(bo_hashed, v_bo, (X)), \
    dpa__u_helper_v_g(bo_refcounted, v_bo, (X)), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__v_bo_simple_ro(DPA__G(dpa_u_bo_with_hash_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__v_bo_simple_ro(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_v_bo__helper(P,X) (const dpa_u_bo_t){ .bo_simple = { .type = DPA_U_BO_SIMPLE, .size=dpa__u_ ## P ## __get_size((X)), .data=dpa__u_ ## P ## __data((X)) } }

#define dpa__u_v_bo__v_bo(X) (X)
#define dpa__u_p_bo__v_bo(X) *(X)
#define dpa__u_cp_bo__v_bo(X) *(X)
dpa_u_reproducible dpa__u_really_inline dpa_u_export inline dpa_u_bo_t dpa__u_any_bo__v_bo(dpa_u_any_bo_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (const dpa_u_bo_t){
        .bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    case DPA_U_BO_SIMPLE:
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED:
      return (const dpa_u_bo_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple__get_size(bo),
          .data = dpa__u_any_bo_simple__data(bo),
        }
      };
  }
  dpa_u_unreachable("dpa_u_any_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_inline__v_bo(X) (const dpa_u_bo_t){ .bo_inline = (X) }
#define dpa__u_p_bo_inline__v_bo(X) (const dpa_u_bo_t){ .bo_inline = *(X) }
#define dpa__u_cp_bo_inline__v_bo(X) (const dpa_u_bo_t){ .bo_inline = *(X) }
#define dpa__u_any_bo_inline__v_bo(X) (const dpa_u_bo_t){ .bo_inline = *(const dpa_u_bo_inline_t*)(X) }

#define dpa__u_v_bo_simple__v_bo(X) (const dpa_u_bo_t){ .bo_simple = (X).ro }
#define dpa__u_p_bo_simple__v_bo(X) (const dpa_u_bo_t){ .bo_simple = (X)->ro }
#define dpa__u_cp_bo_simple__v_bo(X) (const dpa_u_bo_t){ .bo_simple = (X)->ro }
#define dpa__u_any_bo_simple__v_bo(X) dpa__u_v_bo__helper(any_bo_simple,(X))

#define dpa__u_v_bo_hashed__v_bo(X) dpa__u_v_bo__helper(v_bo_hashed,(X))
#define dpa__u_p_bo_hashed__v_bo(X) dpa__u_v_bo__helper(p_bo_hashed,(X))
#define dpa__u_cp_bo_hashed__v_bo(X) dpa__u_v_bo__helper(cp_bo_hashed,(X))
#define dpa__u_any_bo_hashed__v_bo(X) dpa__u_v_bo__helper(any_bo_hashed,(X))

#define dpa__u_v_bo_refcounted__v_bo(X) dpa__u_v_bo__helper(v_bo_refcounted,(X))
#define dpa__u_p_bo_refcounted__v_bo(X) dpa__u_v_bo__helper(p_bo_refcounted,(X))
#define dpa__u_cp_bo_refcounted__v_bo(X) dpa__u_v_bo__helper(cp_bo_refcounted,(X))
#define dpa__u_any_bo_refcounted__v_bo(X) dpa__u_v_bo__helper(any_bo_refcounted,(X))
