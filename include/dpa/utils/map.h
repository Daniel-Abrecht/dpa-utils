#ifndef DPA_U_MAP_H
#define DPA_U_MAP_H

#include <dpa/utils/map-int.h>
#include <dpa/utils/map-string.h>

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-map Map
 * @{
 * A simple "unordered" map, meaning the insertion order doesn't correspond with the iteration order.
 * The order changes between program executions, based on \ref dpa_u_seed.  
 * Different maps with the same key types do have their entries in the same order, though, even if their size is different.
 * This strict ordering of the unorderd map was originally intended to allow for faster intersection & merge functions,
 * but those haven't been implemented yet.
 * 
 * There are dedicated map types for various data types, along with corresponding iterator types.
 * Those types can be a pointer, an unsigned integer, or a string, as a unique BO pointer.
 * Some of the unsigned integer types may not be available on some platforms, and then neither will the corresponding map types.
 * 
 * There are `*_fast_t` and `*_safe_t` iterators.  
 * The fast iterators become invalid if the map is modified. The first/last entry may also vary.  
 * The safe iterator can handle the map being modified while it's being used. If the current iterator index no longer
 * matches the current entry, it simply looks up the current entry again, before performing any operation.
 * 
 * For all generic function macros, there also exist dedicated functions for all map types.  
 * For example, for `dpa_u_map_count`, there also exists `dpa_u_map_u_count`,  `dpa_u_map_string_count`, etc.
 * 
 * Currently, these maps only store \ref dpa_u_any_value_t values, which can hold pointers and integers.
 * 
 * Here is what types the various type names correspond to:
 * | name    | type                |
 * |---------|---------------------|
 * | pointer | void*               |
 * | string  | dpa_u_a_bo_unique_t |
 * | uc      | unsigned char       |
 * | us      | unsigned short      |
 * | u       | unsigned            |
 * | lu      | long unsigned       |
 * | llu     | long long unsigned  |
 * | z       | size_t              |
 * | u8      | uint8_t             |
 * | u16     | uint16_t            |
 * | u24     | uint24_t            |
 * | u32     | uint32_t            |
 * | u64     | uint64_t            |
 * | u128    | uint128_t           |
 * | u256    | uint256_t           |
 * 
 * This map implementation is not thread safe.
 */


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
    char              : (dpa_u_any_value_t){.u64=DPA_U_G(char, (VAL))}, \
    signed char       : (dpa_u_any_value_t){.u64=DPA_U_G(signed char, (VAL))}, \
    signed short      : (dpa_u_any_value_t){.u64=DPA_U_G(signed short, (VAL))}, \
    signed int        : (dpa_u_any_value_t){.u64=DPA_U_G(signed int, (VAL))}, \
    signed long       : (dpa_u_any_value_t){.u64=DPA_U_G(signed long, (VAL))}, \
    signed long long  : (dpa_u_any_value_t){.u64=DPA_U_G(signed long long, (VAL))}, \
    unsigned char     : (dpa_u_any_value_t){.u64=DPA_U_G(unsigned char, (VAL))}, \
    unsigned short    : (dpa_u_any_value_t){.u64=DPA_U_G(unsigned short, (VAL))}, \
    unsigned int      : (dpa_u_any_value_t){.u64=DPA_U_G(unsigned int, (VAL))}, \
    unsigned long     : (dpa_u_any_value_t){.u64=DPA_U_G(unsigned long, (VAL))}, \
    unsigned long long: (dpa_u_any_value_t){.u64=DPA_U_G(unsigned long long, (VAL))}, \
    default: (dpa_u_any_value_t){.ptr=(void*)(VAL)} \
  )

#define DPA__U_LAST_ARG__H2_S1(A, B) A
#define DPA__U_LAST_ARG__H2_S2(A, B) B
#define DPA__U_LAST_ARG__H2_S(A, B, N, ...) DPA__U_LAST_ARG__H2_S ## N(A,B)
#define DPA__U_LAST_ARG__H2(...) DPA__U_LAST_ARG__H2_S(__VA_ARGS__,2,1,0)


/**
 * Moves the iterator to the next entry.
 * Using the safe iterator on different maps is allowed if it is a safe iterator.
 * See \ref dpa-u-map for restrictions of fast iterators.
 * 
 * \param THAT a map
 * \param IT an iterator
 * \returns if there was a next entry, returns true
 */
#define dpa_u_map_it_next(THAT, IT) DPA__U_MAP_GENERIC_WRAPPER_IT(next, (IT))((THAT), (IT))

/**
 * Moves the iterator to the preceeding entry.
 * Using the safe iterator on different maps is allowed if it is a safe iterator.
 * See \ref dpa-u-map for restrictions of fast iterators.
 * 
 * \param THAT a map
 * \param IT an iterator
 * \returns if there was a preceeding entry, returns true
 */
#define dpa_u_map_it_prev(THAT, IT) DPA__U_MAP_GENERIC_WRAPPER_IT(prev, (IT))((THAT), (IT))


/**
 * Moves the iterator to the next entry and returns the value at the new location.
 * The iterator has to be a safe iterator.
 * 
 * \param THAT a map
 * \param IT an iterator
 * \param RVAL A pointer to a variable which will be set to the value at the new iterator location.
 * \returns if there was a next entry, returns true
 */
#define dpa_u_map_it_next_value(THAT, IT, RVAL) DPA__U_MAP_GENERIC_WRAPPER(it_safe_next_value, (THAT))((THAT), (IT), (RVAL))

/**
 * Moves the iterator to the preceeding entry and returns the value at the new location.
 * The iterator has to be a safe iterator.
 * 
 * \param THAT a map
 * \param IT an iterator
 * \param RVAL A pointer to a variable which will be set to the value at the new iterator location.
 * \returns if there was a preceeding entry, returns true
 */
#define dpa_u_map_it_prev_value(THAT, IT, RVAL) DPA__U_MAP_GENERIC_WRAPPER(it_safe_prev_value, (THAT))((THAT), (IT), (RVAL))


/**
 * Takes either a safe iterator, or a map and a fast iterator.
 * Returns the key the iterator points to. In the case of a safe iterator, the iterator has a copy of the keys value,
 * which is what is returned.  
 * In the case of a fast iterator, the key at the index indicated by the iterator is returned.
 */
#define dpa_u_map_it_get_key(...) DPA__U_MAP_GENERIC_WRAPPER_IT(get_key, DPA__U_LAST_ARG__H2(__VA_ARGS__))(__VA_ARGS__)

/**
 * Returns the value at the current iterator position.
 * This operation is only defined for fast iterators, for safe iterators, use the
 * \ref dpa_u_map_get, \ref dpa_u_map_it_prev_value and \ref dpa_u_map_it_next_value functions to get the value if you
 * have a safe iterator.
 *
 * \param THAT a map
 * \param IT an iterator
 * \returns the value
 */
#define dpa_u_map_it_get_value(THAT, IT) DPA__U_MAP_GENERIC_WRAPPER(it_fast_value, (THAT))((THAT), (IT))

/**
 * Sets the value for a given key in the set.
 * 
 * \param THAT the map
 * \param KEY the key
 * \param VAL the value to be set
 * \returns -1 on failure
 * \returns  1 (true)  if the entry already existed in the set
 * \returns  0 (false) if the entry didn't exist yet in the set
 */
#define dpa_u_map_set(THAT, KEY, VAL) DPA__U_MAP_GENERIC_WRAPPER(set, (THAT))((THAT), (KEY), DPA__U_MAP_VALUE_GENERIC(VAL))

/**
 * Sets the value for a given key in the set, and returns the old value.
 * 
 * \param THAT the map
 * \param KEY the key
 * \param VAL a pointer to a variable. The variables value will be set in the map. The variable will be set to the old value in the set.
 * \returns -1 on failure
 * \returns  1 (true)  if the entry already existed in the set
 * \returns  0 (false) if the entry didn't exist yet in the set
 */
#define dpa_u_map_exchange(THAT, KEY, VAL) DPA__U_MAP_GENERIC_WRAPPER(exchange, (THAT))((THAT), (KEY), DPA__U_MAP_VALUE_GENERIC(VAL))

/**
 * Sets the value for a given key in the set, if the key is not in the map yet.
 * 
 * \param THAT the map
 * \param KEY the key
 * \param VAL the value to be set
 * \returns -1 on failure
 * \returns  1 (true)  if the entry already existed in the set
 * \returns  0 (false) if the entry didn't exist yet in the set
 */
#define dpa_u_map_set_if_unset(THAT, KEY, VAL) DPA__U_MAP_GENERIC_WRAPPER(set_if_unset, (THAT))((THAT), (KEY), DPA__U_MAP_VALUE_GENERIC(VAL))

/**
 * Remove an entry to the map.
 * \param THAT the map
 * \param KEY the entry to remove
 * \returns true  if the entry was in the map
 * \returns false if the entry wasn't in the map
 */
#define dpa_u_map_remove(THAT, KEY) DPA__U_MAP_GENERIC_WRAPPER(remove, (THAT))((THAT), (KEY))

/**
 * Check if an entry is in the map.
 * \param THAT the map
 * \param KEY the entry
 * \returns true if the entry is in the map
 * \returns false if the entry is in the map
 */
#define dpa_u_map_has(THAT, KEY) DPA__U_MAP_GENERIC_WRAPPER(has, (THAT))((THAT), (KEY))

/**
 * Get the value for a key in the map.
 * \param THAT the map
 * \param KEY the key
 * \returns The value in a \ref dpa_u_optional_t. That structure has a member to indicate if the entry was found.
 */
#define dpa_u_map_get(THAT, KEY) DPA__U_MAP_GENERIC_WRAPPER(get, (THAT))((THAT), (KEY))

/**
 * Get the value for a key in the map, and remove it from the map.
 * \param THAT the map
 * \param KEY the key
 * \returns The value in a \ref dpa_u_optional_t. That structure has a member to indicate if the entry was found.
 */
#define dpa_u_map_get_and_remove(THAT, KEY) DPA__U_MAP_GENERIC_WRAPPER(get_and_remove, (THAT))((THAT), (KEY))

/**
 * Remove all entries from the map.
 * This will free all the memory that was allocated by the map, call it if you no longer need the map.
 * \param THAT the map
 */
#define dpa_u_map_clear(THAT) DPA__U_MAP_GENERIC_WRAPPER(clear, (THAT))((THAT))

/**
 * \param THAT the map
 * \returns the number of entreis in the map
 */
#define dpa_u_map_count(THAT) DPA__U_MAP_GENERIC_WRAPPER(count, (THAT))((THAT))

/**
 * Create a copy of a map. This does not merge maps.
 * \param DST this map is going to be the copy
 * \param SRC the map to be copied
 */
#define dpa_u_map_copy(DST,SRC) DPA__U_MAP_GENERIC_WRAPPER(count, (SRC))((DST),(SRC))


/** This function is mainly meant for debuggin purposes. */
#define dpa_u_map_dump(THAT) DPA__U_MAP_GENERIC_WRAPPER(dump, (THAT))((THAT))

/** @} */
/** @} */

#endif
