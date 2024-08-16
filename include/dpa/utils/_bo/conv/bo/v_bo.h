#define dpa_u_v_bo(...) dpa_u_assert_selection(dpa_u_v_bo_g((__VA_ARGS__)))
#define dpa_u_v_bo_g(X) dpa_u_generic((X), \
    dpa__u_helper_v_g(bo, v_bo, (X)), \
    dpa__u_helper_v_g(bo_inline, v_bo, (X)), \
    dpa__u_helper_v_g(bo_simple, v_bo, (X)), \
    dpa__u_helper_v_g(bo_hashed, v_bo, (X)), \
    dpa__u_helper_v_g(bo_refcounted, v_bo, (X)), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__v_bo(DPA__G(dpa_u_bo_with_hash_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__v_bo(DPA__G(dpa_u_bo_with_refcount_t*,(X))) \
  )

/*
 * bo_simple to bo, bo_inline to bo.
 * It's an lvalue, so it can be referenced, but it's const, so it can't be changed.
 * It'd be bad if the type of the bo_simple was changed to an incompatiple bo variant using the bo typed instance.
 * This is done like this to avoid accidents when automatically converting BOs when passed to functions.
 * The opposite conversion (bo to bo_simple, bo to bo_inline), when possible (uv/uvp conversion macros), will be a
 * non-const lvalue.
 *
 * bo_hashed / bo_refcounted currently needs to be copied, the result is a non-const lvalue, but this may be changed to
 * a const lvalue in the future, for consistency.
 */

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline const dpa_u_bo_t* dpa__u_any_bo__v_bo_sub(dpa_u_any_bo_t*const restrict orig, dpa_u_bo_t*const restrict copy){
  switch(dpa_u_bo_get_type(orig)){
    case DPA_U_BO_INLINE:;
    case DPA_U_BO_SIMPLE: return (dpa_u_bo_t*)orig;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_HASHED:
      *copy = (const dpa_u_bo_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple__get_size(orig),
          .data = dpa__u_any_bo_simple__data(orig),
        }
      };
      return copy;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(orig)));
}

#define dpa__u_v_bo__v_bo(X) (X)
#define dpa__u_p_bo__v_bo(X) *(X)
#define dpa__u_cp_bo__v_bo(X) *(X)
#define dpa__u_any_bo__v_bo(X) (*dpa__u_any_bo__v_bo_sub((X), &(dpa_u_bo_t){0}))

#define dpa__u_v_bo_inline__v_bo(X) (*(const dpa_u_bo_t*)DPA__G(dpa_u_bo_inline_t,(X)).all.all)
#define dpa__u_p_bo_inline__v_bo(X) (*(dpa_u_bo_t*)(X))
#define dpa__u_cp_bo_inline__v_bo(X) (*(const dpa_u_bo_t*)(X))
#define dpa__u_any_bo_inline__v_bo(X) (*(const dpa_u_bo_t*)(X))

#define dpa__u_v_bo_simple__v_bo(X) (*(const dpa_u_bo_t*)DPA__G(dpa_u_bo_simple_t,(X)).all.all)
#define dpa__u_p_bo_simple__v_bo(X) (*(dpa_u_bo_t*)(X))
#define dpa__u_cp_bo_simple__v_bo(X) (*(const dpa_u_bo_t*)(X))
#define dpa__u_any_bo_simple__v_bo(X) dpa__u_any_bo_simple__t_bo(X)

#define dpa__u_v_bo_hashed__v_bo(X) dpa__u_v_bo_hashed__t_bo(X)
#define dpa__u_p_bo_hashed__v_bo(X) dpa__u_p_bo_hashed__t_bo(X)
#define dpa__u_cp_bo_hashed__v_bo(X) dpa__u_cp_bo_hashed__t_bo(X)
#define dpa__u_any_bo_hashed__v_bo(X) dpa__u_any_bo_hashed__t_bo(X)

#define dpa__u_v_bo_refcounted__v_bo(X) dpa__u_v_bo_refcounted__t_bo(X)
#define dpa__u_p_bo_refcounted__v_bo(X) dpa__u_p_bo_refcounted__t_bo(X)
#define dpa__u_cp_bo_refcounted__v_bo(X) dpa__u_cp_bo_refcounted__t_bo(X)
#define dpa__u_any_bo_refcounted__v_bo(X) dpa__u_any_bo_refcounted__t_bo(X)

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline const dpa_u_bo_t* dpa__u_bo_with_hash__v_bo_sub(dpa_u_bo_with_hash_t*const restrict orig, dpa_u_bo_t*const restrict copy){
  switch(dpa_u_bo_get_type(orig)){
    case DPA_U_BO_INLINE: return (dpa_u_bo_t*)orig;
    case DPA_U_BO_HASHED:
      *copy = (const dpa_u_bo_t){
        .bo_simple = {
          .type = DPA_U_BO_SIMPLE,
          .size = dpa__u_any_bo_simple__get_size(orig),
          .data = dpa__u_any_bo_simple__data(orig),
        }
      };
      return copy;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(orig)));
}

#define dpa__u_bo_with_hash__v_bo(X) (*dpa__u_bo_with_hash__v_bo_sub((X), &(dpa_u_bo_t){0}))
#define dpa__u_bo_with_refcount__v_bo(X) dpa__u_bo_with_refcount__t_bo(X)
