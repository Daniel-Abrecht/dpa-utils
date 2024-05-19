#include <dpa/utils/map.h>
#ifdef DPA__U_MAP_STR_IS_UINT

extern bool dpa_u_map_string_copy(dpa_u_map_string_t*restrict dst, const dpa_u_map_string_t*restrict src);
extern bool dpa_u_map_string_has(const dpa_u_map_string_t*restrict that, dpa_u_bo_unique_t key);
extern bool dpa_u_map_string_it_fast_next(const dpa_u_map_string_t* that, dpa_u_map_string_it_fast_t* it);
extern bool dpa_u_map_string_it_fast_prev(const dpa_u_map_string_t* that, dpa_u_map_string_it_fast_t* it);
extern bool dpa_u_map_string_it_safe_next(const dpa_u_map_string_t* that, dpa_u_map_string_it_safe_t* it);
extern bool dpa_u_map_string_it_safe_next_value(const dpa_u_map_string_t* that, dpa_u_map_string_it_safe_t* it, void** ret);
extern bool dpa_u_map_string_it_safe_prev(const dpa_u_map_string_t* that, dpa_u_map_string_it_safe_t* it);
extern bool dpa_u_map_string_it_safe_prev_value(const dpa_u_map_string_t* that, dpa_u_map_string_it_safe_t* it, void** ret);
extern bool dpa_u_map_string_remove(dpa_u_map_string_t*restrict that, dpa_u_bo_unique_t key);
extern dpa_u_bo_unique_t dpa_u_map_string_it_fast_get_key(const dpa_u_map_string_t* that, const dpa_u_map_string_it_fast_t*const it);
extern dpa_u_bo_unique_t dpa_u_map_string_it_safe_get_key(const dpa_u_map_string_it_safe_t*const it);
extern dpa_u_optional_pointer_t dpa_u_map_string_get(const dpa_u_map_string_t*restrict that, dpa_u_bo_unique_t key);
extern dpa_u_optional_pointer_t dpa_u_map_string_get_and_remove(dpa_u_map_string_t*restrict that, dpa_u_bo_unique_t key);
extern int dpa_u_map_string_exchange(dpa_u_map_string_t*restrict that, dpa_u_bo_unique_t key, void*restrict*const value);
extern int dpa_u_map_string_set(dpa_u_map_string_t*restrict that, dpa_u_bo_unique_t key, void*restrict value);
extern size_t dpa_u_map_string_count(const dpa_u_map_string_t* that);
extern void dpa_u_map_string_clear(dpa_u_map_string_t* that);
extern void dpa_u_map_string_dump_hashmap_key_hashes(dpa_u_map_string_t* that);
extern void* dpa_u_map_string_it_fast_get_value(const dpa_u_map_string_t* that, const dpa_u_map_string_it_fast_t*const it);

#endif
