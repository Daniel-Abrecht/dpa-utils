#ifndef DPA_U_SET_H
#define DPA_U_SET_H


#define DPA__U_STR_AS_UINT_IMPL <dpa/utils/_set_s_uint.h>
#define DPA__U_SM_TEMPLATE <dpa/utils/_set-and-map.h.template>
#define DPA__U_SM_KIND DPA__U_SM_KIND_SET
#include <dpa/utils/_set-and-map.generator>

#define DPA_U__SET_GENERIC_WRAPPER_G(F, X) \
  dpa_u_generic((X), \
          dpa_u_set_pointer_t*: dpa_u_set_pointer_ ## F, \
    const dpa_u_set_pointer_t*: dpa_u_set_pointer_ ## F, \
          dpa_u_set_uc_t*: dpa_u_set_uc_ ## F, \
    const dpa_u_set_uc_t*: dpa_u_set_uc_ ## F, \
          dpa_u_set_us_t*: dpa_u_set_us_ ## F, \
    const dpa_u_set_us_t*: dpa_u_set_us_ ## F, \
          dpa_u_set_u_t*: dpa_u_set_u_ ## F, \
    const dpa_u_set_u_t*: dpa_u_set_u_ ## F, \
          dpa_u_set_lu_t*: dpa_u_set_lu_ ## F, \
    const dpa_u_set_lu_t*: dpa_u_set_lu_ ## F, \
          dpa_u_set_llu_t*: dpa_u_set_llu_ ## F, \
    const dpa_u_set_llu_t*: dpa_u_set_llu_ ## F, \
          dpa_u_set_z_t*: dpa_u_set_z_ ## F, \
    const dpa_u_set_z_t*: dpa_u_set_z_ ## F, \
    DPA_U_IF_HAS_UINT8(      dpa_u_set_u8_t*: dpa_u_set_u8_ ## F,) \
    DPA_U_IF_HAS_UINT8(const dpa_u_set_u8_t*: dpa_u_set_u8_ ## F,) \
    DPA_U_IF_HAS_UINT16(      dpa_u_set_u16_t*: dpa_u_set_u16_ ## F,) \
    DPA_U_IF_HAS_UINT16(const dpa_u_set_u16_t*: dpa_u_set_u16_ ## F,) \
    DPA_U_IF_HAS_UINT24(      dpa_u_set_u24_t*: dpa_u_set_u24_ ## F,) \
    DPA_U_IF_HAS_UINT24(const dpa_u_set_u24_t*: dpa_u_set_u24_ ## F,) \
    DPA_U_IF_HAS_UINT32(      dpa_u_set_u32_t*: dpa_u_set_u32_ ## F,) \
    DPA_U_IF_HAS_UINT32(const dpa_u_set_u32_t*: dpa_u_set_u32_ ## F,) \
    DPA_U_IF_HAS_UINT64(      dpa_u_set_u64_t*: dpa_u_set_u64_ ## F,) \
    DPA_U_IF_HAS_UINT64(const dpa_u_set_u64_t*: dpa_u_set_u64_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(      dpa_u_set_u128_t*: dpa_u_set_u128_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(const dpa_u_set_u128_t*: dpa_u_set_u128_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(      dpa_u_set_u256_t*: dpa_u_set_u256_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(const dpa_u_set_u256_t*: dpa_u_set_u256_ ## F,) \
          dpa_u_set_string_t*: dpa_u_set_string_ ## F, \
    const dpa_u_set_string_t*: dpa_u_set_string_ ## F \
  )

#define DPA_U__SET_GENERIC_WRAPPER_IT_G(F, X) \
  dpa_u_generic((X), \
          dpa_u_set_pointer_it_safe_t*: dpa_u_set_pointer_it_safe_ ## F, \
    const dpa_u_set_pointer_it_safe_t*: dpa_u_set_pointer_it_safe_ ## F, \
          dpa_u_set_uc_it_safe_t*: dpa_u_set_uc_it_safe_ ## F, \
    const dpa_u_set_uc_it_safe_t*: dpa_u_set_uc_it_safe_ ## F, \
          dpa_u_set_us_it_safe_t*: dpa_u_set_us_it_safe_ ## F, \
    const dpa_u_set_us_it_safe_t*: dpa_u_set_us_it_safe_ ## F, \
          dpa_u_set_u_it_safe_t*: dpa_u_set_u_it_safe_ ## F, \
    const dpa_u_set_u_it_safe_t*: dpa_u_set_u_it_safe_ ## F, \
          dpa_u_set_lu_it_safe_t*: dpa_u_set_lu_it_safe_ ## F, \
    const dpa_u_set_lu_it_safe_t*: dpa_u_set_lu_it_safe_ ## F, \
          dpa_u_set_llu_it_safe_t*: dpa_u_set_llu_it_safe_ ## F, \
    const dpa_u_set_llu_it_safe_t*: dpa_u_set_llu_it_safe_ ## F, \
          dpa_u_set_z_it_safe_t*: dpa_u_set_z_it_safe_ ## F, \
    const dpa_u_set_z_it_safe_t*: dpa_u_set_z_it_safe_ ## F, \
    DPA_U_IF_HAS_UINT8(      dpa_u_set_u8_it_safe_t*: dpa_u_set_u8_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT8(const dpa_u_set_u8_it_safe_t*: dpa_u_set_u8_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT16(      dpa_u_set_u16_it_safe_t*: dpa_u_set_u16_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT16(const dpa_u_set_u16_it_safe_t*: dpa_u_set_u16_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT24(      dpa_u_set_u24_it_safe_t*: dpa_u_set_u24_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT24(const dpa_u_set_u24_it_safe_t*: dpa_u_set_u24_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT32(      dpa_u_set_u32_it_safe_t*: dpa_u_set_u32_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT32(const dpa_u_set_u32_it_safe_t*: dpa_u_set_u32_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT64(      dpa_u_set_u64_it_safe_t*: dpa_u_set_u64_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT64(const dpa_u_set_u64_it_safe_t*: dpa_u_set_u64_it_safe_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(      dpa_u_set_u128_it_safe_t*: dpa_u_set_u128_it_safe_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(const dpa_u_set_u128_it_safe_t*: dpa_u_set_u128_it_safe_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(      dpa_u_set_u256_it_safe_t*: dpa_u_set_u256_it_safe_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(const dpa_u_set_u256_it_safe_t*: dpa_u_set_u256_it_safe_ ## F,) \
          dpa_u_set_string_it_safe_t*: dpa_u_set_string_it_safe_ ## F, \
    const dpa_u_set_string_it_safe_t*: dpa_u_set_string_it_safe_ ## F, \
    \
          dpa_u_set_pointer_it_fast_t*: dpa_u_set_pointer_it_fast_ ## F, \
    const dpa_u_set_pointer_it_fast_t*: dpa_u_set_pointer_it_fast_ ## F, \
          dpa_u_set_uc_it_fast_t*: dpa_u_set_uc_it_fast_ ## F, \
    const dpa_u_set_uc_it_fast_t*: dpa_u_set_uc_it_fast_ ## F, \
          dpa_u_set_us_it_fast_t*: dpa_u_set_us_it_fast_ ## F, \
    const dpa_u_set_us_it_fast_t*: dpa_u_set_us_it_fast_ ## F, \
          dpa_u_set_u_it_fast_t*: dpa_u_set_u_it_fast_ ## F, \
    const dpa_u_set_u_it_fast_t*: dpa_u_set_u_it_fast_ ## F, \
          dpa_u_set_lu_it_fast_t*: dpa_u_set_lu_it_fast_ ## F, \
    const dpa_u_set_lu_it_fast_t*: dpa_u_set_lu_it_fast_ ## F, \
          dpa_u_set_llu_it_fast_t*: dpa_u_set_llu_it_fast_ ## F, \
    const dpa_u_set_llu_it_fast_t*: dpa_u_set_llu_it_fast_ ## F, \
          dpa_u_set_z_it_fast_t*: dpa_u_set_z_it_fast_ ## F, \
    const dpa_u_set_z_it_fast_t*: dpa_u_set_z_it_fast_ ## F, \
    DPA_U_IF_HAS_UINT8(      dpa_u_set_u8_it_fast_t*: dpa_u_set_u8_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT8(const dpa_u_set_u8_it_fast_t*: dpa_u_set_u8_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT16(      dpa_u_set_u16_it_fast_t*: dpa_u_set_u16_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT16(const dpa_u_set_u16_it_fast_t*: dpa_u_set_u16_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT24(      dpa_u_set_u24_it_fast_t*: dpa_u_set_u24_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT24(const dpa_u_set_u24_it_fast_t*: dpa_u_set_u24_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT32(      dpa_u_set_u32_it_fast_t*: dpa_u_set_u32_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT32(const dpa_u_set_u32_it_fast_t*: dpa_u_set_u32_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT64(      dpa_u_set_u64_it_fast_t*: dpa_u_set_u64_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT64(const dpa_u_set_u64_it_fast_t*: dpa_u_set_u64_it_fast_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(      dpa_u_set_u128_it_fast_t*: dpa_u_set_u128_it_fast_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(const dpa_u_set_u128_it_fast_t*: dpa_u_set_u128_it_fast_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(      dpa_u_set_u256_it_fast_t*: dpa_u_set_u256_it_fast_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(const dpa_u_set_u256_it_fast_t*: dpa_u_set_u256_it_fast_ ## F,) \
          dpa_u_set_string_it_fast_t*: dpa_u_set_string_it_fast_ ## F, \
    const dpa_u_set_string_it_fast_t*: dpa_u_set_string_it_fast_ ## F \
  )

#define DPA_U__SET_GENERIC_WRAPPER(F, X) dpa_u_assert_selection(DPA_U__SET_GENERIC_WRAPPER_G(F, X))
#define DPA_U__SET_GENERIC_WRAPPER_IT(F, X) dpa_u_assert_selection(DPA_U__SET_GENERIC_WRAPPER_IT_G(F, X))

#define dpa_u_set_it_next(THAT, IT) DPA_U__SET_GENERIC_WRAPPER_IT(next, (IT))((THAT), (IT))
#define dpa_u_set_it_prev(THAT, IT) DPA_U__SET_GENERIC_WRAPPER_IT(prev, (IT))((THAT), (IT))

#define DPA__U_LAST_ARG__H1_S1(A, B) A
#define DPA__U_LAST_ARG__H1_S2(A, B) B
#define DPA__U_LAST_ARG__H1_S(A, B, N, ...) DPA__U_LAST_ARG__H1_S ## N(A,B)
#define DPA__U_LAST_ARG__H1(...) DPA__U_LAST_ARG__H1_S(__VA_ARGS__,2,1,0)

#define dpa_u_set_it_get_key(...) DPA_U__SET_GENERIC_WRAPPER_IT(get_key, DPA__U_LAST_ARG__H1(__VA_ARGS__))(__VA_ARGS__)

#define dpa_u_set_add(THAT, KEY) DPA_U__SET_GENERIC_WRAPPER(add, (THAT))((THAT), (KEY))
#define dpa_u_set_remove(THAT, KEY) DPA_U__SET_GENERIC_WRAPPER(remove, (THAT))((THAT), (KEY))
#define dpa_u_set_has(THAT, KEY) DPA_U__SET_GENERIC_WRAPPER(has, (THAT))((THAT), (KEY))
#define dpa_u_set_clear(THAT) DPA_U__SET_GENERIC_WRAPPER(clear, (THAT))((THAT))
#define dpa_u_set_count(THAT) DPA_U__SET_GENERIC_WRAPPER(count, (THAT))((THAT))
#define dpa_u_set_copy(DST,SRC) DPA_U__SET_GENERIC_WRAPPER(count, (SRC))((DST),(SRC))
#define dpa_u_set_hashmap_key_hashes(THAT) DPA_U__SET_GENERIC_WRAPPER(hashmap_key_hashes, (THAT))((THAT))

#endif
