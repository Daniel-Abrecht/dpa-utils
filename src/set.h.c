#include <dpa/utils/set.h>
#ifdef DPA__U_SET_STR_IS_UINT

extern bool dpa_u_set_string_copy(dpa_u_set_string_t*restrict dst, const dpa_u_set_string_t*restrict src);
extern bool dpa_u_set_string_has(const dpa_u_set_string_t*restrict that, dpa_u_a_bo_unique_t key);
extern bool dpa_u_set_string_it_fast_next(const dpa_u_set_string_t* that, dpa_u_set_string_it_fast_t* it);
extern bool dpa_u_set_string_it_fast_prev(const dpa_u_set_string_t* that, dpa_u_set_string_it_fast_t* it);
extern bool dpa_u_set_string_it_safe_next(const dpa_u_set_string_t* that, dpa_u_set_string_it_safe_t* it);
extern bool dpa_u_set_string_it_safe_prev(const dpa_u_set_string_t* that, dpa_u_set_string_it_safe_t* it);
extern bool dpa_u_set_string_remove(dpa_u_set_string_t*restrict that, dpa_u_a_bo_unique_t key);
extern dpa_u_a_bo_unique_t dpa_u_set_string_it_fast_get_key(const dpa_u_set_string_t* that, const dpa_u_set_string_it_fast_t*const it);
extern dpa_u_a_bo_unique_t dpa_u_set_string_it_safe_get_key(const dpa_u_set_string_it_safe_t*const it);
extern int dpa_u_set_string_add(dpa_u_set_string_t*restrict that, dpa_u_a_bo_unique_t key);
extern size_t dpa_u_set_string_count(const dpa_u_set_string_t* that);
extern void dpa_u_set_string_clear(dpa_u_set_string_t* that);
extern void dpa_u_set_string_dump_hashmap_key_hashes(dpa_u_set_string_t* that);

#endif
