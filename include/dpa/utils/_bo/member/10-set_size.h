
#define dpa_u_bo_set_size(...) dpa_u_assert_selection(dpa_u_bo_set_size_g(__VA_ARGS__))
#define dpa_u_bo_set_size_g(X,S) dpa_u_generic((X), \
    dpa_u_bo_inline_t: dpa__u_v_bo_inline__set_size(DPA__G(dpa_u_bo_inline_t,(X)), (S)), \
    dpa_u_bo_simple_t: dpa__u_v_bo_simple__set_size(DPA__G(dpa_u_bo_simple_t,(X)), (S)), \
    dpa_u_bo_simple_ro_t: dpa__u_v_bo_simple_ro__set_size(DPA__G(dpa_u_bo_simple_ro_t,(X)), (S)), \
    dpa_u_bo_t: dpa__u_v_bo__set_size(DPA__G(dpa_u_bo_t,(X)),(S)), \
    dpa_u_bo_refcounted_t: dpa__u_v_bo_refcounted__set_size(DPA__G(dpa_u_bo_refcounted_t,(X)),(S)), \
    dpa_u_bo_refcounted_ro_t: dpa__u_v_bo_refcounted_ro__set_size(DPA__G(dpa_u_bo_refcounted_ro_t,(X)),(S)), \
    dpa_u_bo_refcounted_hashed_ro_t: dpa__u_v_bo_refcounted_hashed_ro__set_size(DPA__G(dpa_u_bo_refcounted_hashed_ro_t,(X)),(S)) \
    \
    dpa_u_bo_inline_t*: dpa__u_p_bo_inline__set_size(DPA__G(dpa_u_bo_inline_t*,(X)), (S)), \
    dpa_u_bo_simple_t*: dpa__u_p_bo_simple__set_size(&DPA__G(dpa_u_bo_simple_t*,(X)), (S)), \
    dpa_u_bo_simple_ro_t*: dpa__u_p_bo_simple_ro__set_size(&DPA__G(dpa_u_bo_simple_ro_t*,(X)), (S)), \
    dpa_u_bo_t*: dpa__u_p_bo__set_size(DPA__G(dpa_u_bo_t*,(X)),(S)), \
    dpa_u_bo_refcounted_t*: dpa__u_p_bo_refcounted__set_size(DPA__G(dpa_u_bo_refcounted_t*,(X)),(S)), \
    dpa_u_bo_refcounted_ro_t*: dpa__u_p_bo_refcounted_ro__set_size(DPA__G(dpa_u_bo_refcounted_ro_t*,(X)),(S)), \
    dpa_u_bo_refcounted_hashed_ro_t*: dpa__u_p_bo_refcounted_hashed_ro__set_size(DPA__G(dpa_u_bo_refcounted_hashed_ro_t*,(X)),(S)) \
  )

#define dpa__u_v_bo_inline__set_size(X,S) dpa__u_p_bo_inline__set_size(&(X),(S))
#define dpa__u_p_bo_inline__set_size(X,S) (void)(assert((S) <= DPA_U_BO_INLINE_MAX_SIZE),((X)->size=(S)&0xF))

#define dpa__u_v_bo_simple__set_size(X,S) dpa__u_p_bo_simple__set_size(&(X),(S))
#define dpa__u_p_bo_simple__set_size(X,S) (void)(assert((S) <= DPA_U_BO_MAX_SIZE       ),((X)->size=(S)))

#define dpa__u_v_bo_simple_ro__set_size(X,S) dpa__u_p_bo_simple_ro__set_size(&(X),(S))
#define dpa__u_p_bo_simple_ro__set_size(X,S) (void)(assert((S) <= DPA_U_BO_MAX_SIZE       ),((X)->size=(S)))

#define dpa__u_v_bo_refcounted__set_size(X,S) dpa__u_p_bo_refcounted__set_size(&(X),(S))
#define dpa__u_p_bo_refcounted__set_size(X,S) (void)(assert((S) <= DPA_U_BO_MAX_SIZE       ),((X)->size=(S)))

#define dpa__u_v_bo_refcounted_ro__set_size(X,S) dpa__u_p_bo_refcounted_ro__set_size(&(X),(S))
#define dpa__u_p_bo_refcounted_ro__set_size(X,S) (void)(assert((S) <= DPA_U_BO_MAX_SIZE       ),((X)->size=(S)))

#define dpa__u_v_bo_refcounted_hashed_ro__set_size(X,S) dpa__u_p_bo_refcounted_hashed_ro__set_size(&(X),(S))
#define dpa__u_p_bo_refcounted_hashed_ro__set_size(X,S) (void)(assert((S) <= DPA_U_BO_MAX_SIZE       ),((X)->size=(S)))

#define dpa__u_v_bo__set_size(X,S) dpa__u_p_bo__set_size(&(X),(S))
dpa__u_really_inline dpa__u_api inline void dpa__u_p_bo__set_size(dpa_u_bo_t*const bo, size_t size){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: {
      assert(size <= DPA_U_BO_INLINE_MAX_SIZE);
      bo->bo_inline.size = size;
    } return;
    case DPA_U_BO_SIMPLE: {
      bo->bo_simple.size = size;
    } return;
  }
  dpa_u_unreachable("Can't set size on bo of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
