#ifndef DPA_U_MAP_STRING_H
#define DPA_U_MAP_STRING_H

#include <dpa/utils/map-int.h>

typedef struct dpa_u_map_string dpa_u_map_string_t;
typedef struct dpa_u_map_string_it_safe dpa_u_map_string_it_safe_t;
typedef struct dpa_u_map_string_it_fast dpa_u_map_string_it_fast_t;

struct dpa_u_map_string {
  dpa_u_map_u64_t v;
};

struct dpa_u_map_string_it_safe {
  dpa_u_map_u64_it_safe_t v;
};

struct dpa_u_map_string_it_fast {
  dpa_u_map_u64_it_fast_t v;
};



dpa__u_api dpa__u_really_inline inline bool dpa_u_map_string_it_safe_next(const dpa_u_map_string_t* that, dpa_u_map_string_it_safe_t* it){
  return dpa_u_map_u64_it_safe_next(&that->v, &it->v);
}
dpa__u_api dpa__u_really_inline inline bool dpa_u_map_string_it_safe_next_value(const dpa_u_map_string_t* that, dpa_u_map_string_it_safe_t* it, dpa_u_any_value_t* ret){
  return dpa_u_map_u64_it_safe_next_value(&that->v, &it->v, ret);
}
dpa__u_api dpa__u_really_inline inline bool dpa_u_map_string_it_safe_prev(const dpa_u_map_string_t* that, dpa_u_map_string_it_safe_t* it){
  return dpa_u_map_u64_it_safe_prev(&that->v, &it->v);
}
dpa__u_api dpa__u_really_inline inline bool dpa_u_map_string_it_safe_prev_value(const dpa_u_map_string_t* that, dpa_u_map_string_it_safe_t* it, dpa_u_any_value_t* ret){
  return dpa_u_map_u64_it_safe_prev_value(&that->v, &it->v, ret);
}
dpa__u_api dpa__u_really_inline inline dpa_u_a_bo_unique_t dpa_u_map_string_it_safe_get_key(const dpa_u_map_string_it_safe_t*const it){
  return dpa_u_bo_unique_from_uint(dpa_u_map_u64_it_safe_get_key(&it->v));
}

dpa__u_api dpa__u_really_inline inline bool dpa_u_map_string_it_fast_next(const dpa_u_map_string_t* that, dpa_u_map_string_it_fast_t* it){
  return dpa_u_map_u64_it_fast_next(&that->v, &it->v);
}
dpa__u_api dpa__u_really_inline inline bool dpa_u_map_string_it_fast_prev(const dpa_u_map_string_t* that, dpa_u_map_string_it_fast_t* it){
  return dpa_u_map_u64_it_fast_prev(&that->v, &it->v);
}
dpa__u_api dpa__u_really_inline dpa_u_reproducible inline dpa_u_a_bo_unique_t dpa_u_map_string_it_fast_get_key(const dpa_u_map_string_t* that, const dpa_u_map_string_it_fast_t*const it){
  return dpa_u_bo_unique_from_uint(dpa_u_map_u64_it_fast_get_key(&that->v, &it->v));
}
dpa__u_api dpa_u_reproducible dpa__u_really_inline inline dpa_u_any_value_t dpa_u_map_string_it_fast_get_value(const dpa_u_map_string_t* that, const dpa_u_map_string_it_fast_t*const it){
  return dpa_u_map_u64_it_fast_get_value(&that->v, &it->v);
}
dpa__u_api dpa__u_really_inline inline int dpa_u_map_string_set(dpa_u_map_string_t*restrict that, dpa_u_a_bo_unique_t key, dpa_u_any_value_t value){
  return dpa_u_map_u64_set(&that->v, dpa_u_a_bo_unique_to_uint(key), value);
}
dpa__u_api dpa__u_really_inline inline int dpa_u_map_string_set_if_unset(dpa_u_map_string_t*restrict that, dpa_u_a_bo_unique_t key, dpa_u_any_value_t value){
  return dpa_u_map_u64_set_if_unset(&that->v, dpa_u_a_bo_unique_to_uint(key), value);
}
dpa__u_api dpa__u_really_inline inline int dpa_u_map_string_exchange(dpa_u_map_string_t*restrict that, dpa_u_a_bo_unique_t key, dpa_u_any_value_t*const value){
  return dpa_u_map_u64_exchange(&that->v, dpa_u_a_bo_unique_to_uint(key), value);
}
dpa__u_api dpa__u_really_inline inline bool dpa_u_map_string_remove(dpa_u_map_string_t*restrict that, dpa_u_a_bo_unique_t key){
  return dpa_u_map_u64_remove(&that->v, dpa_u_a_bo_unique_to_uint(key));
}
dpa__u_api dpa_u_reproducible dpa__u_really_inline inline bool dpa_u_map_string_has(const dpa_u_map_string_t*restrict that, dpa_u_a_bo_unique_t key){
  return dpa_u_map_u64_has(&that->v, dpa_u_a_bo_unique_to_uint(key));
}
dpa__u_api dpa__u_really_inline inline void dpa_u_map_string_clear(dpa_u_map_string_t* that){
  dpa_u_map_u64_clear(&that->v);
}
dpa__u_api dpa_u_reproducible dpa__u_really_inline inline dpa_u_optional_t dpa_u_map_string_get(const dpa_u_map_string_t*restrict that, dpa_u_a_bo_unique_t key){
  return dpa_u_map_u64_get(&that->v, dpa_u_a_bo_unique_to_uint(key));
}
dpa__u_api dpa__u_really_inline inline dpa_u_optional_t dpa_u_map_string_get_and_remove(dpa_u_map_string_t*restrict that, dpa_u_a_bo_unique_t key){
  return dpa_u_map_u64_get_and_remove(&that->v, dpa_u_a_bo_unique_to_uint(key));
}
dpa__u_api dpa_u_reproducible dpa__u_really_inline inline size_t dpa_u_map_string_count(const dpa_u_map_string_t* that){
  return dpa_u_map_u64_count(&that->v);
}
dpa__u_api dpa__u_really_inline inline bool dpa_u_map_string_copy(dpa_u_map_string_t*restrict dst, const dpa_u_map_string_t*restrict src){
  return dpa_u_map_u64_copy(&dst->v, &src->v);
}
dpa__u_api dpa__u_really_inline inline void dpa_u_map_string_dump_hashmap_key_hashes(dpa_u_map_string_t* that){
  dpa_u_map_u64_dump_hashmap_key_hashes(&that->v);
}

#endif
