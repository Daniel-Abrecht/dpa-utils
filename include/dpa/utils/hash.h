#ifndef DPA_U_HASH_H
#define DPA_U_HASH_H

#include <dpa/utils/bo.h>
#include <stdint.h>

#if defined(DPA__U_ISS_MULTITARGET) || defined(DPA__U_ISS_IFUNC)
#ifdef __has_include
#if __has_include(<immintrin.h>)
#include <immintrin.h>
#ifdef DPA_HAS_INT128
__attribute__((target("aes")))
#ifdef DPA__U_ISS_MULTITARGET
static inline dpa_uint128_t dpa__u128_mix(const dpa_uint128_t x){
#elif defined(DPA__U_ISS_IFUNC)
static inline dpa_uint128_t dpa__u128_mix__aes(const dpa_uint128_t x){
#endif
  return *(const dpa_uint128_t*)(const __m128i[]){_mm_aesimc_si128(*(const __m128i*)&x)};
}
#define DPA__U128_MIX
#endif
#endif
#endif
#endif

#if defined(DPA__U_ISS_MULTITARGET) && defined(DPA__U128_MIX)
__attribute__((target("default")))
#endif
#if defined(DPA__U_ISS_MULTITARGET) || defined(DPA__U_ISS_NONE) || !defined(DPA__U128_MIX)
static inline dpa_uint128_t dpa__u128_mix(const dpa_uint128_t x){
#elif defined(DPA__U_ISS_IFUNC)
static inline dpa_uint128_t dpa__u128_mix__default(const dpa_uint128_t x){
#endif
  // TODO
  return x;
}

#if defined(DPA__U_ISS_IFUNC) && defined(DPA__U128_MIX)
static inline dpa_uint128_t (*dpa__u128_mix__resolve(void)) (dpa_uint128_t){
  __builtin_cpu_init();
  return __builtin_cpu_supports("aes") ? dpa__u128_mix__aes : dpa__u128_mix__default;
}
static inline dpa_uint128_t dpa__u128_mix(const dpa_uint128_t x)
  __attribute__((ifunc("dpa__u128_mix__resolve")));
#endif

static inline uint64_t dpa__u_bo_inline_get_hash_16(const dpa_u_bo_inline_t bo){
#ifdef DPA_HAS_INT128
  return dpa__u128_mix(*(const dpa_uint128_t*)bo.all.all);
#else
  typedef struct { DPA__U_BO_ALIGN uint64_t x[2]; } T;
  const T x = *(const T*)bo.all.all;
  // TODO: Mix it
  return x;
#endif
}

static inline uint64_t dpa__u_bo_inline_get_hash_8(const dpa_u_bo_inline_t bo){
  // TODO
  (void)bo;
  return 0;
}

static inline uint64_t dpa__u_bo_inline_get_hash_4(const dpa_u_bo_inline_t bo){
  // TODO
  (void)bo;
  return 0;
}

static inline uint64_t dpa__u_bo_inline_get_hash_fallback(const dpa_u_bo_inline_t bo){
  // TODO
  (void)bo;
  return 0;
}


#define dpa__u_bo_inline_get_hash _Generic(char(*)[sizeof(dpa_u_bo_inline_t)], \
    char(*)[16]: dpa__u_bo_inline_get_hash_16, \
    char(*)[ 8]: dpa__u_bo_inline_get_hash_8, \
    char(*)[ 4]: dpa__u_bo_inline_get_hash_4, \
    default: dpa__u_bo_inline_get_hash_fallback \
  )


/**
 * This function returns a platform dependent, non-cryptografic hash, intended for use in hash maps and similar datastructures.
 */
#define dpa_u_bo_get_hash(X) _Generic((X), \
    dpa_u_bo_inline_t: dpa__u_bo_inline_get_hash(DPA__G(dpa_u_bo_inline_t, (X))) \
  )

#endif
