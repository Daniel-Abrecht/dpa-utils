#define dpa_u_t_bo_hashed_ro(...) dpa_u_assert_selection(dpa_u_t_bo_hashed_ro_g(__VA_ARGS__))
#define dpa_u_t_bo_hashed_ro_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: dpa__u_v_bo_unique_hashmap__t_bo_hashed_ro((X)), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_v_any_bo_unique_hashmap__t_bo_hashed_ro((X)), \
    dpa__u_helper_v_g(bo_hashed_ro, t_bo_hashed_ro, (X)), \
    dpa__u_helper_v_g(bo_hashed, t_bo_hashed_ro, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, t_bo_hashed_ro, (X)) \
  )

#define dpa__u_t_bo_hashed_ro__helper_s1(X) dpa_u_rescope(const dpa_u_bo_hashed_ro_t,dpa__u_hashed_ro_fix_type(X))

#define dpa__u_v_bo_unique_hashmap__t_bo_hashed_ro(X) dpa__u_t_bo_hashed__helper_s1((X)->bo_hashed)
#define dpa__u_v_any_bo_unique_hashmap__t_bo_hashed_ro(X) dpa__u_t_bo_hashed__helper_s1(*(const dpa_u_bo_hashed_ro_t*)(X))

#define dpa__u_v_bo_hashed_ro__t_bo_hashed_ro(X)  dpa_u_rescope(const dpa_u_bo_hashed_ro_t,(X))
#define dpa__u_p_bo_hashed_ro__t_bo_hashed_ro(X)  dpa_u_rescope(const dpa_u_bo_hashed_ro_t,(X))
#define dpa__u_cp_bo_hashed_ro__t_bo_hashed_ro(X) dpa_u_rescope(const dpa_u_bo_hashed_ro_t,(X))
#define dpa__u_any_bo_hashed_ro__t_bo_hashed_ro(X) dpa__u_t_bo_hashed__helper_s1(*(const dpa_u_bo_hashed_ro_t*)(X))

#define dpa__u_v_bo_hashed__t_bo_hashed_ro(X) dpa_u_rescope(const dpa_u_bo_hashed_ro_t,(X).ro)
#define dpa__u_p_bo_hashed__t_bo_hashed_ro(X) dpa_u_rescope(const dpa_u_bo_hashed_ro_t,(X)->ro)
#define dpa__u_cp_bo_hashed__t_bo_hashed_ro(X) dpa_u_rescope(const dpa_u_bo_hashed_ro_t,(X)->ro)
#define dpa__u_any_bo_hashed__t_bo_hashed_ro(X) dpa__u_t_bo_hashed__helper_s1(*(const dpa_u_bo_hashed_ro_t*)(X))

dpa_u_unsequenced dpa__u_really_inline dpa_u_export inline dpa_u_bo_hashed_ro_t dpa__u_v_bo_refcounted_hashed_ro__t_bo_hashed_ro_p(const dpa_u_bo_refcounted_hashed_ro_t bo){
  return (dpa_u_bo_hashed_ro_t){
    .bo_simple = {
      .type = DPA_U_BO_HASHED,
      .size = bo.bo_refcounted.bo_simple.size,
      .data = bo.bo_refcounted.bo_simple.data,
    },
    .hash = bo.hash,
  };
}
#define dpa__u_v_bo_refcounted_hashed_ro__t_bo_hashed_ro(X) dpa_u_rescope(const dpa_u_bo_hashed_ro_t,dpa__u_v_bo_refcounted_hashed_ro__t_bo_hashed_ro_p(X))
#define dpa__u_p_bo_refcounted_hashed_ro__t_bo_hashed_ro(X) dpa_u_rescope(const dpa_u_bo_hashed_ro_t,dpa__u_v_bo_refcounted_hashed_ro__t_bo_hashed_ro_p(*(X)))
#define dpa__u_cp_bo_refcounted_hashed_ro__t_bo_hashed_ro(X) dpa_u_rescope(const dpa_u_bo_hashed_ro_t,dpa__u_v_bo_refcounted_hashed_ro__t_bo_hashed_ro_p(*(X)))
#define dpa__u_any_bo_refcounted_hashed_ro__t_bo_hashed_ro(X) dpa_u_rescope(const dpa_u_bo_hashed_ro_t,dpa__u_v_bo_refcounted_hashed_ro__t_bo_hashed_ro_p(*(const dpa_u_bo_refcounted_hashed_ro_t*)(X)))

#define dpa__u_bo_gc_ro__t_bo_hashed_ro(X) dpa__u_bo_gc_ro__t_bo_ro(X)
#define dpa__u_bo_with_hash_ro__t_bo_hashed_ro(X) dpa__u_bo_with_hash_ro__t_bo_ro(X)
#define dpa__u_bo_with_hash__t_bo_hashed_ro(X) dpa__u_bo_with_hash__t_bo_ro(X)
#define dpa__u_bo_with_refcount_and_hash_ro__t_bo_hashed_ro(X) dpa__u_bo_with_refcount_and_hash_ro__t_bo_ro(X)
