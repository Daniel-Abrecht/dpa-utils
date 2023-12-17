#define dpa_u_t_bo(...) dpa_u_assert_selection(dpa_u_t_bo_g((__VA_ARGS__)))
#define dpa_u_t_bo_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo, t_bo, (X)), \
    dpa__u_helper_v_g(bo_inline, t_bo, (X)), \
    dpa__u_helper_v_g(bo_simple, t_bo, (X)), \
    dpa__u_helper_v_g(bo_hashed, t_bo, (X)), \
    dpa__u_helper_v_g(bo_refcounted, t_bo, (X)), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__t_bo(DPA__G(dpa_u_bo_with_hash_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__t_bo(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

#define dpa__u_t_bo__helper_s1(X) (const dpa_u_bo_t){ .bo_simple = dpa__u_simple_fix_type((X)) }

#define dpa__u_v_bo__t_bo(X) dpa_u_rescope(const dpa_u_bo_t,X)
#define dpa__u_p_bo__t_bo(X) dpa_u_rescope(const dpa_u_bo_t,*(X))
#define dpa__u_cp_bo__t_bo(X) dpa_u_rescope(const dpa_u_bo_t,*(X))
#define dpa__u_any_bo__t_bo(X) dpa_u_rescope(const dpa_u_bo_t,dpa__u_any_bo__t_bo_p(X))
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_t dpa__u_any_bo__t_bo_p(dpa_u_any_bo_t*const bo){
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

#define dpa__u_v_bo_inline__t_bo(X) (const dpa_u_bo_t){ .bo_inline = (X) }
#define dpa__u_p_bo_inline__t_bo(X) (const dpa_u_bo_t){ .bo_inline = *(X) }
#define dpa__u_cp_bo_inline__t_bo(X) (const dpa_u_bo_t){ .bo_inline = *(X) }
#define dpa__u_any_bo_inline__t_bo(X) (const dpa_u_bo_t){ .bo_inline = *(const dpa_u_bo_inline_t*)(X) }

#define dpa__u_v_bo_simple__t_bo(X) (const dpa_u_bo_t){ .bo_simple = (X).ro }
#define dpa__u_p_bo_simple__t_bo(X) (const dpa_u_bo_t){ .bo_simple = (X)->ro }
#define dpa__u_cp_bo_simple__t_bo(X) (const dpa_u_bo_t){ .bo_simple = (X)->ro }
#define dpa__u_any_bo_simple__t_bo(X) dpa__u_t_bo__helper_s1(*(dpa_u_bo_simple_t*)X)

#define dpa__u_v_bo_hashed__t_bo(X) dpa__u_t_bo__helper_s1((X).bo_simple)
#define dpa__u_p_bo_hashed__t_bo(X) dpa__u_t_bo__helper_s1((X)->bo_simple)
#define dpa__u_cp_bo_hashed__t_bo(X) dpa__u_t_bo__helper_s1((X)->bo_simple)
#define dpa__u_any_bo_hashed__t_bo(X) dpa__u_t_bo__helper_s1(*(dpa_u_bo_simple_t*)(X))

#define dpa__u_v_bo_refcounted__t_bo(X) dpa__u_t_bo__helper_s1((X).bo_simple)
#define dpa__u_p_bo_refcounted__t_bo(X) dpa__u_t_bo__helper_s1((X)->bo_simple)
#define dpa__u_cp_bo_refcounted__t_bo(X) dpa__u_t_bo__helper_s1((X)->bo_simple)
#define dpa__u_any_bo_refcounted__t_bo(X) dpa__u_t_bo__helper_s1(*(dpa_u_bo_simple_t*)(X))

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline dpa_u_bo_t dpa__u_bo_with_hash__t_bo_p(dpa_u_bo_with_hash_t*const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (const dpa_u_bo_t){
        .bo_inline = *(const dpa_u_bo_inline_t*)bo,
      };
    case DPA_U_BO_HASHED:
      return (const dpa_u_bo_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple__get_size(bo),
          .data = dpa__u_any_bo_simple__data(bo),
        }
      };
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_hash__t_bo(X) dpa_u_rescope(const dpa_u_bo_t,dpa__u_bo_with_hash__t_bo_p(X))
#define dpa__u_bo_with_refcount__t_bo(X) dpa__u_t_bo__helper_s1(*(const dpa_u_bo_simple_t*)(X))
