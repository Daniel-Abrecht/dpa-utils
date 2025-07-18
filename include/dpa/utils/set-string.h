#ifndef DPA_U_SET_STRING_H
#define DPA_U_SET_STRING_H

#include <dpa/utils/set-int.h>


/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-set Set
 * @{
 */

typedef struct dpa_u_set_string dpa_u_set_string_t;
typedef struct dpa_u_set_string_it_safe dpa_u_set_string_it_safe_t;
typedef struct dpa_u_set_string_it_fast dpa_u_set_string_it_fast_t;

struct dpa_u_set_string {
  dpa_u_set_u64_t v;
};

struct dpa_u_set_string_it_safe {
  dpa_u_set_u64_it_safe_t v;
};

struct dpa_u_set_string_it_fast {
  dpa_u_set_u64_it_fast_t v;
};


/** \cond 0 */

dpa__u_api dpa__u_really_inline inline bool dpa_u_set_string_it_safe_next(const dpa_u_set_string_t* that, dpa_u_set_string_it_safe_t* it){
  return dpa_u_set_u64_it_safe_next(&that->v, &it->v);
}
dpa__u_api dpa__u_really_inline inline bool dpa_u_set_string_it_safe_prev(const dpa_u_set_string_t* that, dpa_u_set_string_it_safe_t* it){
  return dpa_u_set_u64_it_safe_prev(&that->v, &it->v);
}

dpa__u_api dpa__u_really_inline inline dpa_u_a_bo_unique_t dpa_u_set_string_it_safe_get_key(const dpa_u_set_string_it_safe_t*const it){
  return dpa_u_bo_unique_from_uint(dpa_u_set_u64_it_safe_get_key(&it->v));
}

dpa__u_api dpa__u_really_inline inline bool dpa_u_set_string_it_fast_next(const dpa_u_set_string_t* that, dpa_u_set_string_it_fast_t* it){
  return dpa_u_set_u64_it_fast_next(&that->v, &it->v);
}
dpa__u_api dpa__u_really_inline inline bool dpa_u_set_string_it_fast_prev(const dpa_u_set_string_t* that, dpa_u_set_string_it_fast_t* it){
  return dpa_u_set_u64_it_fast_prev(&that->v, &it->v);
}
dpa__u_api dpa__u_really_inline dpa_u_reproducible inline dpa_u_a_bo_unique_t dpa_u_set_string_it_fast_get_key(const dpa_u_set_string_t* that, const dpa_u_set_string_it_fast_t*const it){
  return dpa_u_bo_unique_from_uint(dpa_u_set_u64_it_fast_get_key(&that->v, &it->v));
}

dpa__u_api dpa__u_really_inline inline int dpa_u_set_string_add(dpa_u_set_string_t*restrict that, dpa_u_a_bo_unique_t key){
  return dpa_u_set_u64_add(&that->v, dpa_u_bo_unique_to_uint(key));
}
dpa__u_api dpa__u_really_inline inline bool dpa_u_set_string_remove(dpa_u_set_string_t*restrict that, dpa_u_a_bo_unique_t key){
  return dpa_u_set_u64_remove(&that->v, dpa_u_bo_unique_to_uint(key));
}
dpa__u_api dpa_u_reproducible dpa__u_really_inline inline bool dpa_u_set_string_has(const dpa_u_set_string_t*restrict that, dpa_u_a_bo_unique_t key){
  return dpa_u_set_u64_has(&that->v, dpa_u_bo_unique_to_uint(key));
}
dpa__u_api dpa__u_really_inline inline void dpa_u_set_string_clear(dpa_u_set_string_t* that){
  dpa_u_set_u64_clear(&that->v);
}
dpa__u_api dpa_u_reproducible dpa__u_really_inline inline size_t dpa_u_set_string_count(const dpa_u_set_string_t* that){
  return dpa_u_set_u64_count(&that->v);
}
dpa__u_api dpa__u_really_inline inline bool dpa_u_set_string_copy(dpa_u_set_string_t*restrict dst, const dpa_u_set_string_t*restrict src){
  return dpa_u_set_u64_copy(&dst->v, &src->v);
}
dpa__u_api dpa__u_really_inline inline void dpa_u_set_string_dump(dpa_u_set_string_t* that){
  dpa_u_set_u64_dump(&that->v);
}

/** \endcond */
/** @} */
/** @} */

#endif
