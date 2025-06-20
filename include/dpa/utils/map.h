#ifndef DPA_U_MAP_H
#define DPA_U_MAP_H

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-map Map
 * @{
 */

#include <dpa/utils/map-int.h>
#include <dpa/utils/map-string.h>


#define DPA__U_MAP_GENERIC_WRAPPER_G(F, X) \
  dpa_u_generic((X), \
          dpa_u_map_pointer_t*: dpa_u_map_pointer_ ## F, \
    const dpa_u_map_pointer_t*: dpa_u_map_pointer_ ## F, \
          dpa_u_map_uc_t*: dpa_u_map_uc_ ## F, \
    const dpa_u_map_uc_t*: dpa_u_map_uc_ ## F, \
          dpa_u_map_us_t*: dpa_u_map_us_ ## F, \
    const dpa_u_map_us_t*: dpa_u_map_us_ ## F, \
          dpa_u_map_u_t*: dpa_u_map_u_ ## F, \
    const dpa_u_map_u_t*: dpa_u_map_u_ ## F, \
          dpa_u_map_lu_t*: dpa_u_map_lu_ ## F, \
    const dpa_u_map_lu_t*: dpa_u_map_lu_ ## F, \
          dpa_u_map_llu_t*: dpa_u_map_llu_ ## F, \
    const dpa_u_map_llu_t*: dpa_u_map_llu_ ## F, \
          dpa_u_map_z_t*: dpa_u_map_z_ ## F, \
    const dpa_u_map_z_t*: dpa_u_map_z_ ## F, \
    DPA_U_IF_HAS_UINT8(      dpa_u_map_u8_t*: dpa_u_map_u8_ ## F,) \
    DPA_U_IF_HAS_UINT8(const dpa_u_map_u8_t*: dpa_u_map_u8_ ## F,) \
    DPA_U_IF_HAS_UINT16(      dpa_u_map_u16_t*: dpa_u_map_u16_ ## F,) \
    DPA_U_IF_HAS_UINT16(const dpa_u_map_u16_t*: dpa_u_map_u16_ ## F,) \
    DPA_U_IF_HAS_UINT24(      dpa_u_map_u24_t*: dpa_u_map_u24_ ## F,) \
    DPA_U_IF_HAS_UINT24(const dpa_u_map_u24_t*: dpa_u_map_u24_ ## F,) \
    DPA_U_IF_HAS_UINT32(      dpa_u_map_u32_t*: dpa_u_map_u32_ ## F,) \
    DPA_U_IF_HAS_UINT32(const dpa_u_map_u32_t*: dpa_u_map_u32_ ## F,) \
    DPA_U_IF_HAS_UINT64(      dpa_u_map_u64_t*: dpa_u_map_u64_ ## F,) \
    DPA_U_IF_HAS_UINT64(const dpa_u_map_u64_t*: dpa_u_map_u64_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(      dpa_u_map_u128_t*: dpa_u_map_u128_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(const dpa_u_map_u128_t*: dpa_u_map_u128_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(      dpa_u_map_u256_t*: dpa_u_map_u256_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(const dpa_u_map_u256_t*: dpa_u_map_u256_ ## F,) \
          dpa_u_map_string_t*: dpa_u_map_string_ ## F, \
    const dpa_u_map_string_t*: dpa_u_map_string_ ## F \
  )

#define DPA__U_MAP_GENERIC_WRAPPER_IT_G(F, X) \
  dpa_u_generic((X), \
          dpa_u_map_pointer_it_safe_t*: dpa_u_map_pointer_it_safe_ ## F, \
    const dpa_u_map_pointer_it_safe_t*: dpa_u_map_pointer_it_safe_ ## F, \
          dpa_u_map_uc_it_safe_t*: dpa_u_map_uc_it_safe_ ## F, \
    const dpa_u_map_uc_it_safe_t*: dpa_u_map_uc_it_safe_ ## F, \
          dpa_u_map_us_it_safe_t*: dpa_u_map_us_it_safe_ ## F, \
    const dpa_u_map_us_it_safe_t*: dpa_u_map_us_it_safe_ ## F, \
          dpa_u_map_u_it_safe_t*: dpa_u_map_u_it_safe_ ## F, \
    const dpa_u_map_u_it_safe_t*: dpa_u_map_u_it_safe_ ## F, \
          dpa_u_map_lu_it_safe_t*: dpa_u_map_lu_it_safe_ ## F, \
    const dpa_u_map_lu_it_safe_t*: dpa_u_map_lu_it_safe_ ## F, \
          dpa_u_map_llu_it_safe_t*: dpa_u_map_llu_it_safe_ ## F, \
    const dpa_u_map_llu_it_safe_t*: dpa_u_map_llu_it_safe_ ## F, \
          dpa_u_map_z_it_safe_t*: dpa_u_map_z_it_safe_ ## F, \
    const dpa_u_map_z_it_safe_t*: dpa_u_map_z_it_safe_ ## F, \
    DPA_U_IF_HAS_UINT8(      dpa_u_map_u8_it_safe_t*: dpa_u_map_u8_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT8(const dpa_u_map_u8_it_safe_t*: dpa_u_map_u8_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT16(      dpa_u_map_u16_it_safe_t*: dpa_u_map_u16_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT16(const dpa_u_map_u16_it_safe_t*: dpa_u_map_u16_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT24(      dpa_u_map_u24_it_safe_t*: dpa_u_map_u24_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT24(const dpa_u_map_u24_it_safe_t*: dpa_u_map_u24_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT32(      dpa_u_map_u32_it_safe_t*: dpa_u_map_u32_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT32(const dpa_u_map_u32_it_safe_t*: dpa_u_map_u32_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT64(      dpa_u_map_u64_it_safe_t*: dpa_u_map_u64_it_safe_ ## F,) \
    DPA_U_IF_HAS_UINT64(const dpa_u_map_u64_it_safe_t*: dpa_u_map_u64_it_safe_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(      dpa_u_map_u128_it_safe_t*: dpa_u_map_u128_it_safe_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(const dpa_u_map_u128_it_safe_t*: dpa_u_map_u128_it_safe_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(      dpa_u_map_u256_it_safe_t*: dpa_u_map_u256_it_safe_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(const dpa_u_map_u256_it_safe_t*: dpa_u_map_u256_it_safe_ ## F,) \
          dpa_u_map_string_it_safe_t*: dpa_u_map_string_it_safe_ ## F, \
    const dpa_u_map_string_it_safe_t*: dpa_u_map_string_it_safe_ ## F, \
    \
          dpa_u_map_pointer_it_fast_t*: dpa_u_map_pointer_it_fast_ ## F, \
    const dpa_u_map_pointer_it_fast_t*: dpa_u_map_pointer_it_fast_ ## F, \
          dpa_u_map_uc_it_fast_t*: dpa_u_map_uc_it_fast_ ## F, \
    const dpa_u_map_uc_it_fast_t*: dpa_u_map_uc_it_fast_ ## F, \
          dpa_u_map_us_it_fast_t*: dpa_u_map_us_it_fast_ ## F, \
    const dpa_u_map_us_it_fast_t*: dpa_u_map_us_it_fast_ ## F, \
          dpa_u_map_u_it_fast_t*: dpa_u_map_u_it_fast_ ## F, \
    const dpa_u_map_u_it_fast_t*: dpa_u_map_u_it_fast_ ## F, \
          dpa_u_map_lu_it_fast_t*: dpa_u_map_lu_it_fast_ ## F, \
    const dpa_u_map_lu_it_fast_t*: dpa_u_map_lu_it_fast_ ## F, \
          dpa_u_map_llu_it_fast_t*: dpa_u_map_llu_it_fast_ ## F, \
    const dpa_u_map_llu_it_fast_t*: dpa_u_map_llu_it_fast_ ## F, \
          dpa_u_map_z_it_fast_t*: dpa_u_map_z_it_fast_ ## F, \
    const dpa_u_map_z_it_fast_t*: dpa_u_map_z_it_fast_ ## F, \
    DPA_U_IF_HAS_UINT8(      dpa_u_map_u8_it_fast_t*: dpa_u_map_u8_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT8(const dpa_u_map_u8_it_fast_t*: dpa_u_map_u8_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT16(      dpa_u_map_u16_it_fast_t*: dpa_u_map_u16_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT16(const dpa_u_map_u16_it_fast_t*: dpa_u_map_u16_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT24(      dpa_u_map_u24_it_fast_t*: dpa_u_map_u24_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT24(const dpa_u_map_u24_it_fast_t*: dpa_u_map_u24_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT32(      dpa_u_map_u32_it_fast_t*: dpa_u_map_u32_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT32(const dpa_u_map_u32_it_fast_t*: dpa_u_map_u32_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT64(      dpa_u_map_u64_it_fast_t*: dpa_u_map_u64_it_fast_ ## F,) \
    DPA_U_IF_HAS_UINT64(const dpa_u_map_u64_it_fast_t*: dpa_u_map_u64_it_fast_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(      dpa_u_map_u128_it_fast_t*: dpa_u_map_u128_it_fast_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT128(const dpa_u_map_u128_it_fast_t*: dpa_u_map_u128_it_fast_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(      dpa_u_map_u256_it_fast_t*: dpa_u_map_u256_it_fast_ ## F,) \
    DPA_U_IF_HAS_DPA_UINT256(const dpa_u_map_u256_it_fast_t*: dpa_u_map_u256_it_fast_ ## F,) \
          dpa_u_map_string_it_fast_t*: dpa_u_map_string_it_fast_ ## F, \
    const dpa_u_map_string_it_fast_t*: dpa_u_map_string_it_fast_ ## F \
  )

#define DPA__U_MAP_GENERIC_WRAPPER(F, X) dpa_u_assert_selection(DPA__U_MAP_GENERIC_WRAPPER_G(F, X))
#define DPA__U_MAP_GENERIC_WRAPPER_IT(F, X) dpa_u_assert_selection(DPA__U_MAP_GENERIC_WRAPPER_IT_G(F, X))

#define DPA__U_MAP_VALUE_GENERIC(VAL) _Generic((VAL), \
    dpa_u_any_value_t : (VAL), \
    char              : (dpa_u_any_value_t){.u64=DPA__G(char, (VAL))}, \
    signed char       : (dpa_u_any_value_t){.u64=DPA__G(signed char, (VAL))}, \
    signed short      : (dpa_u_any_value_t){.u64=DPA__G(signed short, (VAL))}, \
    signed int        : (dpa_u_any_value_t){.u64=DPA__G(signed int, (VAL))}, \
    signed long       : (dpa_u_any_value_t){.u64=DPA__G(signed long, (VAL))}, \
    signed long long  : (dpa_u_any_value_t){.u64=DPA__G(signed long long, (VAL))}, \
    unsigned char     : (dpa_u_any_value_t){.u64=DPA__G(unsigned char, (VAL))}, \
    unsigned short    : (dpa_u_any_value_t){.u64=DPA__G(unsigned short, (VAL))}, \
    unsigned int      : (dpa_u_any_value_t){.u64=DPA__G(unsigned int, (VAL))}, \
    unsigned long     : (dpa_u_any_value_t){.u64=DPA__G(unsigned long, (VAL))}, \
    unsigned long long: (dpa_u_any_value_t){.u64=DPA__G(unsigned long long, (VAL))}, \
    default: (dpa_u_any_value_t){.ptr=(void*)(VAL)} \
  )

#define dpa_u_map_it_next(THAT, IT) DPA__U_MAP_GENERIC_WRAPPER_IT(next, (IT))((THAT), (IT))
#define dpa_u_map_it_prev(THAT, IT) DPA__U_MAP_GENERIC_WRAPPER_IT(prev, (IT))((THAT), (IT))

#define dpa_u_map_it_next_value(THAT, IT, RVAL) DPA__U_MAP_GENERIC_WRAPPER(it_safe_next_value, (THAT))((THAT), (IT), (RVAL))
#define dpa_u_map_it_prev_value(THAT, IT, RVAL) DPA__U_MAP_GENERIC_WRAPPER(it_safe_prev_value, (THAT))((THAT), (IT), (RVAL))

#define DPA__U_LAST_ARG__H2_S1(A, B) A
#define DPA__U_LAST_ARG__H2_S2(A, B) B
#define DPA__U_LAST_ARG__H2_S(A, B, N, ...) DPA__U_LAST_ARG__H2_S ## N(A,B)
#define DPA__U_LAST_ARG__H2(...) DPA__U_LAST_ARG__H2_S(__VA_ARGS__,2,1,0)

#define dpa_u_map_it_get_key(...) DPA__U_MAP_GENERIC_WRAPPER_IT(get_key, DPA__U_LAST_ARG__H2(__VA_ARGS__))(__VA_ARGS__)
#define dpa_u_map_it_get_value(THAT, IT) DPA__U_MAP_GENERIC_WRAPPER(it_fast_value, (THAT))((THAT), (IT))

#define dpa_u_map_set(THAT, KEY, VAL) DPA__U_MAP_GENERIC_WRAPPER(set, (THAT))((THAT), (KEY), DPA__U_MAP_VALUE_GENERIC(VAL))
#define dpa_u_map_exchange(THAT, KEY, VAL) DPA__U_MAP_GENERIC_WRAPPER(exchange, (THAT))((THAT), (KEY), DPA__U_MAP_VALUE_GENERIC(VAL))
#define dpa_u_map_set_if_unset(THAT, KEY, VAL) DPA__U_MAP_GENERIC_WRAPPER(set_if_unset, (THAT))((THAT), (KEY), DPA__U_MAP_VALUE_GENERIC(VAL))
#define dpa_u_map_remove(THAT, KEY) DPA__U_MAP_GENERIC_WRAPPER(remove, (THAT))((THAT), (KEY))
#define dpa_u_map_has(THAT, KEY) DPA__U_MAP_GENERIC_WRAPPER(has, (THAT))((THAT), (KEY))
#define dpa_u_map_get(THAT, KEY) DPA__U_MAP_GENERIC_WRAPPER(get, (THAT))((THAT), (KEY))
#define dpa_u_map_get_and_remove(THAT, KEY) DPA__U_MAP_GENERIC_WRAPPER(get_and_remove, (THAT))((THAT), (KEY))
#define dpa_u_map_clear(THAT) DPA__U_MAP_GENERIC_WRAPPER(clear, (THAT))((THAT))
#define dpa_u_map_count(THAT) DPA__U_MAP_GENERIC_WRAPPER(count, (THAT))((THAT))
#define dpa_u_map_copy(DST,SRC) DPA__U_MAP_GENERIC_WRAPPER(count, (SRC))((DST),(SRC))
#define dpa_u_map_dump_hashmap_key_hashes(THAT) DPA__U_MAP_GENERIC_WRAPPER(dump_hashmap_key_hashes, (THAT))((THAT))

/** @} */
/** @} */

#endif
