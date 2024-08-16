#include <dpa/utils/bo.h>

extern const dpa_u_bo_t* dpa__u_any_bo__v_bo_sub(dpa_u_any_bo_t*const restrict orig, dpa_u_bo_t*const restrict copy);
extern const dpa_u_bo_t* dpa__u_bo_with_hash__v_bo_sub(dpa_u_bo_with_hash_t*const restrict orig, dpa_u_bo_t*const restrict copy);
extern const void* dpa__u_any_bo__data(const dpa_u_any_bo_t* const bo);
extern const void* dpa__u_any_bo_ro__data(const dpa_u_any_bo_ro_t* const bo);
extern const void* dpa__u_any_bo_unique__data(const dpa_u_any_bo_unique_t*const bo);
extern const void* dpa__u_bo_any_unpack_ptr(const void*const bo);
extern const void* dpa__u_bo_gc_ro__data(const dpa_u_bo_gc_ro_t*const bo);
extern const void* dpa__u_bo_with_hash__data(const dpa_u_bo_with_hash_t*const bo);
extern const void* dpa__u_bo_with_hash_ro__data(const dpa_u_bo_with_hash_ro_t*const bo);
extern const void* dpa__u_cp_bo__data(const dpa_u_bo_t*const bo);
extern const void* dpa__u_cp_bo_ro__data(const dpa_u_bo_ro_t*const bo);
extern const void* dpa__u_cp_bo_unique__data(const dpa_u_bo_unique_t*const bo);
extern dpa_u_any_bo_ro_t* dpa__u_cp_bo_ro__ptr(const dpa_u_bo_ro_t*const bo);
extern dpa_u_any_bo_unique_t* dpa__u_cp_bo_unique__ptr(const dpa_u_bo_unique_t*const bo);
extern dpa_u_bo_hashed_ro_t dpa__u_bo_with_hash__v_bo_hashed_ro_p(dpa_u_bo_with_hash_t*const bo);
extern dpa_u_bo_hashed_ro_t dpa__u_bo_with_hash_ro__t_bo_hashed_ro_2_p(const union dpa__u_hashed_conv_helper*const bo);
extern dpa_u_bo_hashed_ro_t dpa__u_bo_with_hash_ro__v_bo_hashed_ro_p(dpa_u_bo_with_hash_ro_t*const bo);
extern dpa_u_bo_hashed_ro_t dpa__u_bo_with_refcount_and_hash_ro__t_bo_hashed_ro_p(const dpa_u_bo_with_refcount_and_hash_ro_t*const bo);
extern dpa_u_bo_hashed_ro_t dpa__u_hashed_ro_fix_type(dpa_u_bo_hashed_ro_t v);
extern dpa_u_bo_hashed_ro_t dpa__u_v_bo_inline__t_bo_hashed_ro_p(const dpa_u_bo_inline_t* bo);
extern dpa_u_bo_hashed_ro_t dpa__u_v_bo_refcounted_hashed_ro__t_bo_hashed_ro_p(const dpa_u_bo_refcounted_hashed_ro_t bo);
extern dpa_u_bo_hashed_ro_t dpa__u_v_bo_unique__t_bo_hashed_ro_p(const dpa_u_bo_unique_t* bo);
extern dpa_u_bo_hashed_t dpa__u_bo_with_hash__t_bo_hashed_2_p(union dpa__u_hashed_conv_helper*const bo);
extern dpa_u_bo_hashed_t dpa__u_v_bo_inline__t_bo_hashed_p(dpa_u_bo_inline_t*const bo);
extern dpa_u_bo_refcounted_hashed_ro_t dpa__u_bo_with_refcount_and_hash_ro__t_bo_refcounted_hashed_ro_p(dpa_u_bo_with_refcount_and_hash_ro_t* bo);
extern dpa_u_bo_refcounted_hashed_ro_t dpa__u_v_bo_unique_hashmap__t_bo_refcounted_hashed_ro_p(dpa_u_bo_unique_hashmap_t bo);
extern dpa_u_bo_refcounted_ro_t dpa__u_bo_with_refcount_and_hash_ro__t_bo_refcounted_ro_p(const dpa_u_bo_with_refcount_and_hash_ro_t*const bo);
extern dpa_u_bo_refcounted_ro_t dpa__u_bo_with_refcount_ro__t_bo_refcounted_ro_p(const dpa_u_bo_with_refcount_ro_t*const bo);
extern dpa_u_bo_refcounted_ro_t dpa__u_refcounted_ro_fix_type(dpa_u_bo_refcounted_ro_t v);
extern dpa_u_bo_refcounted_ro_t dpa__u_v_bo_unique_hashmap__t_bo_refcounted_ro_p(dpa_u_bo_unique_hashmap_t bo);
extern dpa_u_bo_ro_t dpa__u_any_bo__t_bo_ro_p(dpa_u_any_bo_t*const bo);
extern dpa_u_bo_ro_t dpa__u_any_bo_ro__t_bo_ro_p(dpa_u_any_bo_ro_t*const bo);
extern dpa_u_bo_ro_t dpa__u_any_bo_simple_ro__t_bo_ro_p(dpa_u_any_bo_simple_ro_t*const bo);
extern dpa_u_bo_ro_t dpa__u_bo_gc_ro__t_bo_ro_p(dpa_u_bo_gc_ro_t*const bo);
extern dpa_u_bo_ro_t dpa__u_bo_with_hash__t_bo_ro_p(dpa_u_bo_with_hash_t*const bo);
extern dpa_u_bo_ro_t dpa__u_bo_with_hash_ro__t_bo_ro_p(dpa_u_bo_with_hash_ro_t*const bo);
extern dpa_u_bo_ro_t dpa__u_bo_with_refcount_and_hash_ro__t_bo_ro_p(dpa_u_bo_with_refcount_and_hash_ro_t*const bo);
extern dpa_u_bo_ro_t dpa__u_bo_with_refcount_ro__t_bo_ro_p(dpa_u_bo_with_refcount_ro_t*const bo);
extern dpa_u_bo_ro_t dpa__u_p_bo_ro__t_bo_simple_ro_p2_sub(dpa_u_any_bo_ro_t*const bo);
extern dpa_u_bo_ro_t dpa__u_p_bo_ro__tp_any_bo_simple_ro_p(const dpa_u_bo_ro_t* bo);
extern dpa_u_bo_ro_t dpa__u_p_bo_unique__tp_any_bo_simple_ro_p(const dpa_u_bo_unique_t* bo);
extern dpa_u_bo_simple_ro_t dpa__u_p_bo__t_bo_simple_ro_p(const dpa_u_bo_t* bo);
extern dpa_u_bo_simple_ro_t dpa__u_p_bo__tp_any_bo_simple_ro_p(const dpa_u_bo_t* bo);
extern dpa_u_bo_simple_ro_t dpa__u_p_bo_inline__t_bo_simple_ro_p(dpa_u_bo_inline_t*const bo);
extern dpa_u_bo_simple_ro_t dpa__u_p_bo_ro__t_bo_simple_ro_p1(const dpa_u_bo_ro_t* bo);
extern dpa_u_bo_simple_ro_t dpa__u_p_bo_ro__t_bo_simple_ro_p2(const dpa_u_bo_ro_t* bo);
extern dpa_u_bo_simple_ro_t dpa__u_p_bo_unique__t_bo_simple_ro_p(const dpa_u_bo_unique_t* bo);
extern dpa_u_bo_simple_ro_t dpa__u_simple_ro_fix_type(dpa_u_bo_simple_ro_t v);
extern dpa_u_bo_simple_t dpa__u_p_bo__t_bo_simple_p(dpa_u_bo_t* bo);
extern dpa_u_bo_simple_t dpa__u_p_bo__tp_any_bo_simple_p(dpa_u_bo_t* bo);
extern dpa_u_bo_simple_t dpa__u_p_bo_inline__t_bo_simple_p(dpa_u_bo_inline_t*const bo);
extern dpa_u_bo_simple_t dpa__u_simple_fix_type(dpa_u_bo_simple_t v);
extern dpa_u_bo_t dpa__u_any_bo__t_bo_p(dpa_u_any_bo_t*const bo);
extern dpa_u_bo_t dpa__u_bo_with_hash__t_bo_p(dpa_u_bo_with_hash_t*const bo);
extern dpa_u_bo_unique_t dpa__u_any_bo_unique__v_bo_unique(dpa_u_any_bo_unique_t*const bo);
extern dpa_u_bo_unique_t dpa_u_bo_intern_p(dpa_u_any_bo_ro_t*const bo);
extern dpa_u_hash_t dpa__u_any_bo_unique__get_hash(dpa_u_any_bo_unique_t* bo);
extern dpa_u_hash_t dpa__u_bo_with_hash__get_hash(dpa_u_bo_with_hash_t*const bo);
extern dpa_u_hash_t dpa__u_bo_with_hash_ro__get_hash(dpa_u_bo_with_hash_ro_t*const bo);
extern dpa_u_hash_t dpa__u_bo_with_refcount_and_hash_ro__get_hash(dpa_u_bo_with_refcount_and_hash_ro_t*const bo);
extern dpa_u_hash_t dpa__u_v_bo_unique__get_hash(const dpa_u_bo_unique_t bo);
extern dpa_u_refcount_freeable_t* dpa__u_any_bo_ro__get_refcount(dpa_u_any_bo_ro_t*const bo);
extern dpa_u_refcount_freeable_t* dpa__u_bo_gc_ro__get_refcount(const dpa_u_bo_gc_ro_t*const bo);
extern dpa_u_refcount_freeable_t* dpa__u_bo_with_refcount_and_hash_ro__get_refcount(const dpa_u_bo_with_refcount_and_hash_ro_t*const bo);
extern dpa_u_refcount_freeable_t* dpa__u_bo_with_refcount_ro__get_refcount(const dpa_u_bo_with_refcount_ro_t*const bo);
extern dpa_u_refcount_freeable_t* dpa__u_cp_bo_ro__get_refcount(const dpa_u_bo_ro_t*const bo);
extern dpa_u_refcount_freeable_t* dpa__u_v_bo_ro__get_refcount(const dpa_u_bo_ro_t bo);
extern dpa_u_refcount_freeable_t* dpa__u_v_bo_unique__get_refcount(const dpa_u_bo_unique_t ubo);
extern int dpa__u_bo_compare_default(dpa_u_any_bo_ro_t* a, dpa_u_any_bo_ro_t* b);
extern int dpa__u_bo_compare_default_sub(const dpa_u_bo_simple_ro_t a, const dpa_u_bo_simple_ro_t b);
extern int dpa__u_bo_compare_inline(const dpa_u_bo_inline_t a, const dpa_u_bo_inline_t b);
extern int dpa__u_bo_compare_unique(const dpa_u_bo_unique_t a, const dpa_u_bo_unique_t b);
extern size_t dpa__u_any_bo__get_size(const dpa_u_any_bo_t*const bo);
extern size_t dpa__u_any_bo_ro__get_size(const dpa_u_any_bo_ro_t*const bo);
extern size_t dpa__u_any_bo_unique__get_size(const dpa_u_any_bo_unique_t*const bo);
extern size_t dpa__u_bo_gc_ro__get_size(const dpa_u_bo_gc_ro_t*const bo);
extern size_t dpa__u_bo_with_hash__get_size(const dpa_u_bo_with_hash_t*const bo);
extern size_t dpa__u_bo_with_hash_ro__get_size(const dpa_u_bo_with_hash_ro_t*const bo);
extern size_t dpa__u_v_bo__get_size(const dpa_u_bo_t bo);
extern size_t dpa__u_v_bo_ro__get_size(const dpa_u_bo_ro_t bo);
extern size_t dpa__u_v_bo_unique__get_size(const dpa_u_bo_unique_t bo);
extern union dpa__u_any_helper dpa__u_any_bo__tp_any_bo_p(dpa_u_any_bo_t*const bo);
extern union dpa__u_any_helper dpa__u_any_bo__tp_any_bo_simple_p(union dpa__u_bo_ptr_helper*restrict bo);
extern union dpa__u_any_helper dpa__u_any_bo_simple__tp_any_bo_p(dpa_u_any_bo_simple_t*const bo);
extern union dpa__u_any_helper dpa__u_any_bo_simple__tp_any_bo_simple_p(dpa_u_any_bo_simple_t* bo);
extern union dpa__u_any_helper dpa__u_bo_with_hash__tp_any_bo_p(dpa_u_bo_with_hash_t*const bo);
extern union dpa__u_any_helper dpa__u_bo_with_hash__tp_any_bo_simple_p(union dpa__u_bo_ptr_helper*restrict bo);
extern union dpa__u_any_ro_helper dpa__u_any_bo_hashed_ro__tp_any_bo_hashed_ro_p(const dpa_u_any_bo_hashed_ro_t*const bo);
extern union dpa__u_any_ro_helper dpa__u_bo_with_hash_ro__tp_any_bo_hashed_ro_1_p(union dpa__u_bo_ptr_helper*restrict bo);
extern union dpa__u_any_ro_helper dpa__u_bo_with_refcount_and_hash_ro__tp_any_bo_hashed_ro_p(const dpa_u_bo_with_refcount_and_hash_ro_t*const bo);
extern union dpa__u_any_ro_helper_2 dpa__u_any_bo_refcounted_ro__tp_any_bo_refcounted_ro_p(const dpa_u_any_bo_refcounted_ro_t*const bo);
extern union dpa__u_any_ro_helper_2 dpa__u_any_bo_ro__tp_any_bo_ro_1_p(dpa_u_any_bo_ro_t*const bo);
extern union dpa__u_any_ro_helper_2 dpa__u_any_bo_ro__tp_any_bo_simple_p(union dpa__u_bo_ptr_helper*restrict bo);
extern union dpa__u_any_ro_helper_2 dpa__u_any_bo_simple_ro__tp_any_bo_ro_1_p(dpa_u_any_bo_simple_ro_t*const bo);
extern union dpa__u_any_ro_helper_2 dpa__u_bo_gc_ro__tp_any_bo_ro_1_p(dpa_u_bo_gc_ro_t*const bo);
extern union dpa__u_any_ro_helper_2 dpa__u_bo_with_hash_ro__tp_any_bo_ro_1_p(const dpa_u_bo_with_hash_ro_t*const bo);
extern union dpa__u_any_ro_helper_2 dpa__u_bo_with_refcount_and_hash_ro__tp_any_bo_refcounted_ro_p(const dpa_u_bo_with_refcount_and_hash_ro_t*const bo);
extern union dpa__u_any_ro_helper_2 dpa__u_bo_with_refcount_ro__tp_any_bo_refcounted_ro_p(const dpa_u_bo_with_refcount_ro_t*const bo);
extern union dpa__u_bo_ptr_helper dpa__u_bo_any_inline_ptr(const void*const bo);
extern union dpa__u_hashed_conv_helper dpa__u_bo_with_hash__t_bo_hashed_1_p(const dpa_u_bo_with_hash_t*const bo);
extern union dpa__u_hashed_conv_helper dpa__u_bo_with_hash__t_bo_hashed_ro_1_p(const dpa_u_bo_with_hash_t*const bo);
extern union dpa__u_hashed_conv_helper dpa__u_bo_with_hash_ro__t_bo_hashed_ro_1_p(const dpa_u_bo_with_hash_ro_t*const bo);
extern void dpa__u_any_bo_unique__put(dpa_u_any_bo_unique_t*const ubo);
extern void dpa__u_any_bo_unique__ref(dpa_u_any_bo_unique_t*const ubo);
extern void dpa__u_bo_gc_ro__put(dpa_u_bo_gc_ro_t*const bo);
extern void dpa__u_bo_gc_ro__ref(dpa_u_bo_gc_ro_t*const bo);
extern void dpa__u_p_bo__set_size(dpa_u_bo_t*const bo, size_t size);
extern void dpa__u_v_bo_unique__put(dpa_u_bo_unique_t ubo);
extern void dpa__u_v_bo_unique__ref(dpa_u_bo_unique_t ubo);
extern void* dpa__u_p_bo__data(dpa_u_bo_t*const bo);
