#include <dpa/utils/bo.h>

extern void* dpa__u_p_bo__data(dpa_u_bo_t*restrict const);
extern const void* dpa__u_cp_bo__data(const dpa_u_bo_t*restrict const);
extern const void* dpa__u_cp_bo_ro__data(const dpa_u_bo_ro_t*restrict const);
extern const void* dpa__u_cp_bo_unique__data(const dpa_u_bo_unique_t*restrict const);
extern const void* dpa__u_any_bo_unique__data(const dpa_u_any_bo_unique_t* bo);
extern const void* dpa__u_any_bo__data(const dpa_u_any_bo_t* const bo);
extern const void* dpa__u_any_bo_ro__data(const dpa_u_any_bo_ro_t* const bo);
extern const void* dpa__u_bo_with_hash_ro__data(const dpa_u_bo_with_hash_ro_t*restrict const bo);
extern const void* dpa__u_bo_with_hash__data(const dpa_u_bo_with_hash_t*restrict const bo);
extern const void* dpa__u_bo_gc_ro__data(const dpa_u_bo_gc_ro_t*restrict const bo);

extern size_t dpa__u_any_bo_unique__get_size(const dpa_u_any_bo_unique_t* bo);
extern size_t dpa__u_any_bo__get_size(const dpa_u_any_bo_t* bo);
extern size_t dpa__u_any_bo_ro__get_size(const dpa_u_any_bo_ro_t* bo);
extern size_t dpa__u_bo_with_hash_ro__get_size(const dpa_u_bo_with_hash_ro_t* bo);
extern size_t dpa__u_bo_with_hash__get_size(const dpa_u_bo_with_hash_t* bo);
extern size_t dpa__u_v_bo__get_size(const dpa_u_bo_t);
extern size_t dpa__u_v_bo_ro__get_size(const dpa_u_bo_ro_t);
extern size_t dpa__u_v_bo_unique__get_size(const dpa_u_bo_unique_t);
extern size_t dpa__u_bo_gc_ro__get_size(const dpa_u_bo_gc_ro_t* bo);

extern void dpa__u_p_bo__set_size(dpa_u_bo_t*restrict const bo, size_t size);

extern dpa_u_bo_unique_t dpa__u_bo_intern(const dpa_u_any_bo_ro_t*const _bo);

extern void dpa__u_v_bo_unique__ref(dpa_u_bo_unique_t ubo);
extern void dpa__u_any_bo_unique__ref(dpa_u_any_bo_unique_t* ubo);
extern void dpa__u_bo_gc_ro__ref(dpa_u_bo_gc_ro_t* bo);

extern void dpa__u_v_bo_unique__put(dpa_u_bo_unique_t ubo);
extern void dpa__u_any_bo_unique__put(dpa_u_any_bo_unique_t* ubo);
extern void dpa__u_bo_gc_ro__put(dpa_u_bo_gc_ro_t* bo);

extern struct dpa_u_refcount_freeable* dpa__u_v_bo_unique__get_refcount(const dpa_u_bo_unique_t);
extern struct dpa_u_refcount_freeable* dpa__u_cp_bo_ro__get_refcount(const dpa_u_bo_ro_t*);
extern struct dpa_u_refcount_freeable* dpa__u_v_bo_ro__get_refcount(const dpa_u_bo_ro_t);
extern dpa_u_refcount_freeable_t* dpa__u_any_bo_ro__get_refcount(dpa_u_any_bo_ro_t* bo);
extern dpa_u_refcount_freeable_t* dpa__u_bo_with_refcount_ro__get_refcount(const dpa_u_bo_with_refcount_ro_t* bo);
extern dpa_u_refcount_freeable_t* dpa__u_bo_with_refcount_and_hash_ro__get_refcount(const dpa_u_bo_with_refcount_and_hash_ro_t* bo);
extern dpa_u_refcount_freeable_t* dpa__u_bo_gc_ro__get_refcount(const dpa_u_bo_gc_ro_t* bo);

extern int dpa__u_bo_compare_inline(const dpa_u_bo_inline_t, const dpa_u_bo_inline_t);
extern int dpa__u_bo_compare_unique(const dpa_u_bo_unique_t, const dpa_u_bo_unique_t);
extern int dpa__u_bo_compare_default(const dpa_u_bo_simple_ro_t, const dpa_u_bo_simple_ro_t);


#undef DPA_U_BO_INLINE
#undef DPA_U_BO_SIMPLE
#undef DPA_U_BO_UNIQUE_HASHMAP
#undef DPA_U_BO_HASHED
#undef DPA_U_BO_REFCOUNTED
#undef DPA_U_BO_REFCOUNTED_HASHED

DPA_U_ENUM_DEF(dpa_u_bo_any_type)
