#ifndef DPA_U_SET_H
#define DPA_U_SET_H

#include <dpa/utils/set-int.h>
#include <dpa/utils/set-string.h>

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-set Set
 * @{
 * A simple "unordered" set, meaning the insertion order doesn't correspond with the iteration order.
 * The order changes between program executions, based on \ref dpa_u_seed.  
 * Different sets with the same key types do have their entries in the same order, though, even if their size is different.
 * This strict ordering of the unorderd set was originally intended to allow for faster intersection & merge functions,
 * but those haven't been implemented yet.
 * 
 * There are dedicated set types for various data types, along with corresponding iterator types.
 * Those types can be a pointer, an unsigned integer, or a string, as a unique BO pointer.
 * Some of the unsigned integer types may not be available on some platforms, and then neither will the corresponding set types.
 * 
 * There are `*_fast_t` and `*_safe_t` iterators.  
 * The fast iterators become invalid if the set is modified. The first/last entry may also vary.  
 * The safe iterator can handle the set being modified while it's being used. If the current iterator index no longer
 * matches the current entry, it simply looks up the current entry again, before performing any operation.
 * 
 * For all generic function macros, there also exist dedicated functions for all set types.  
 * For example, for `dpa_u_set_count`, there also exists `dpa_u_set_u_count`,  `dpa_u_set_string_count`, etc.
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
 * This set implementation is not thread safe.
 */


#define DPA__U_SET_GENERIC_WRAPPER_G(F, X) \
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

#define DPA__U_SET_GENERIC_WRAPPER_IT_G(F, X) \
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

#define DPA__U_SET_GENERIC_WRAPPER(F, X) dpa_u_assert_selection(DPA__U_SET_GENERIC_WRAPPER_G(F, X))
#define DPA__U_SET_GENERIC_WRAPPER_IT(F, X) dpa_u_assert_selection(DPA__U_SET_GENERIC_WRAPPER_IT_G(F, X))

#define DPA__U_LAST_ARG__H1_S1(A, B) A
#define DPA__U_LAST_ARG__H1_S2(A, B) B
#define DPA__U_LAST_ARG__H1_S(A, B, N, ...) DPA__U_LAST_ARG__H1_S ## N(A,B)
#define DPA__U_LAST_ARG__H1(...) DPA__U_LAST_ARG__H1_S(__VA_ARGS__,2,1,0)


/**
 * Moves the iterator to the next entry.
 * Using the safe iterator on different sets is allowed if it is a safe iterator.
 * See \ref dpa-u-set for restrictions of fast iterators.
 * 
 * \param THAT a set
 * \param IT an iterator
 * \returns if there was a next entry, returns true
 */
#define dpa_u_set_it_next(THAT, IT) DPA__U_SET_GENERIC_WRAPPER_IT(next, (IT))((THAT), (IT))

/**
 * Moves the iterator to the preceeding entry.
 * Using the safe iterator on different sets is allowed if it is a safe iterator.
 * See \ref dpa-u-set for restrictions of fast iterators.
 * 
 * \param THAT a set
 * \param IT an iterator
 * \returns if there was a preceeding entry, returns true
 */
#define dpa_u_set_it_prev(THAT, IT) DPA__U_SET_GENERIC_WRAPPER_IT(prev, (IT))((THAT), (IT))


/**
 * Takes either a safe iterator, or a set and a fast iterator.
 * Returns the key the iterator points to. In the case of a safe iterator, the iterator has a copy of the keys value,
 * which is what is returned.  
 * In the case of a fast iterator, the key at the index indicated by the iterator is returned.
 */
#define dpa_u_set_it_get_key(...) DPA__U_SET_GENERIC_WRAPPER_IT(get_key, DPA__U_LAST_ARG__H1(__VA_ARGS__))(__VA_ARGS__)


/**
 * Add an entry to the set.
 * \param THAT the set
 * \param KEY the entry to add
 * \returns -1 on failure
 * \returns  1 (true)  if the entry already existed in the set
 * \returns  0 (false) if the entry didn't exist yet in the set
 */
#define dpa_u_set_add(THAT, KEY) DPA__U_SET_GENERIC_WRAPPER(add, (THAT))((THAT), (KEY))

/**
 * Remove an entry to the set.
 * \param THAT the set
 * \param KEY the entry to remove
 * \returns true  if the entry was in the set
 * \returns false if the entry wasn't in the set
 */
#define dpa_u_set_remove(THAT, KEY) DPA__U_SET_GENERIC_WRAPPER(remove, (THAT))((THAT), (KEY))

/**
 * Check if an entry is in the set.
 * \param THAT the set
 * \param KEY the entry
 * \returns true if the entry is in the set
 * \returns false if the entry is in the set
 */
#define dpa_u_set_has(THAT, KEY) DPA__U_SET_GENERIC_WRAPPER(has, (THAT))((THAT), (KEY))

/**
 * Remove all entries from the set.
 * This will free all the memory that was allocated by the set, call it if you no longer need the set.
 * \param THAT the set
 */
#define dpa_u_set_clear(THAT) DPA__U_SET_GENERIC_WRAPPER(clear, (THAT))((THAT))

/**
 * \param THAT the set
 * \returns the number of entreis in the set
 */
#define dpa_u_set_count(THAT) DPA__U_SET_GENERIC_WRAPPER(count, (THAT))((THAT))

/**
 * Create a copy of a set. This does not merge sets.
 * \param DST this set is going to be the copy
 * \param SRC the set to be copied
 */
#define dpa_u_set_copy(DST,SRC) DPA__U_SET_GENERIC_WRAPPER(count, (SRC))((DST),(SRC))


/** This function is mainly meant for debuggin purposes. */
#define dpa_u_set_dump(THAT) DPA__U_SET_GENERIC_WRAPPER(dump, (THAT))((THAT))

/** @} */
/** @} */

#endif
