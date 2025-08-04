#ifndef DPA_U_LINKED_SET_H
#define DPA_U_LINKED_SET_H

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-linked-set Linked set
 * @{
 * Usually, this data structure is described as a doubly linked list.
 * It's really an ordered doubly linked set though. An object can only be once in the same list, hence it's a set,
 * and the insertion order is preserved, so it's ordered.
 * That's true for most linked list implementations, there is nothing unusual about this one.
 * The entries can also only be in one set at a time.
 * 
 * There are a few variations. The primary ones are:
 * \ref dpa_u_linked_set_p stores the number of current entries, and it's entries (\ref dpa_u_linked_set_p_entry)
 * store a reference to the list they are in.
 * \ref dpa_u_linked_set_s and \ref dpa_u_linked_set_s_entry do not store this additional information.
 * 
 * There are generic macros which will work for either variation.
 */

#include <dpa/utils/common.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

/**
 * If the next / previous members in \ref dpa_u_linked_set_s_entry have this tag set, then they don't point to the next
 * entry, but to the set itself.
 */
#define DPA_U_LINKED_SET_S_TAG_SET (((uintptr_t)1)<<(sizeof(uintptr_t)*CHAR_BIT-1))

typedef struct dpa_u_linked_set_s_entry {
  uintptr_t p[2];
} dpa_u_linked_set_s_entry_t;

typedef struct dpa_u_linked_set_p_entry {
  struct dpa_u_linked_set_p* set;
  uintptr_t p[2];
} dpa_u_linked_set_p_entry_t;

typedef struct dpa_u_linked_set_s {
  dpa_u_linked_set_s_entry_t v;
} dpa_u_linked_set_s_t;

typedef struct dpa_u_linked_set_p {
  size_t length;
  struct { uintptr_t p[2]; } v;
} dpa_u_linked_set_p_t;

/** \see dpa_u_linked_set_set */
dpa__u_api bool dpa_u_linked_set_s_set(
  struct dpa_u_linked_set_s* set,
  struct dpa_u_linked_set_s_entry* entry,
  struct dpa_u_linked_set_s_entry* before
);

/** \see dpa_u_linked_set_set */
dpa__u_api bool dpa_u_linked_set_p_set(
  struct dpa_u_linked_set_p* set,
  struct dpa_u_linked_set_p_entry* entry,
  struct dpa_u_linked_set_p_entry* before
);

/** \see dpa_u_linked_set_move */
dpa__u_api bool dpa_u_linked_set_s_move(
  struct dpa_u_linked_set_s* dst,
  struct dpa_u_linked_set_s* src,
  struct dpa_u_linked_set_s_entry* before
);

/** \see dpa_u_linked_set_move */
dpa__u_api bool dpa_u_linked_set_p_move(
  struct dpa_u_linked_set_p* dst,
  struct dpa_u_linked_set_p* src,
  struct dpa_u_linked_set_p_entry* before
);

/** \see dpa_u_linked_set_clear */
dpa__u_api void dpa_u_linked_set_s_clear(struct dpa_u_linked_set_s* set);
/** \see dpa_u_linked_set_clear */
dpa__u_api void dpa_u_linked_set_p_clear(struct dpa_u_linked_set_p* set);

/**
 * Adds an entry to a set before another entry. If the other entry is 0, it adds it to the end of the list.
 * The set can be omitted if the entry it is to be inserted before is specified.
 * If only the entry is specified, it will be removed from the set.
 * 
 * If an entry the entry is to be inserted before is specified, it must belong to a set, and if a set is also
 * passed to this function, it must be the same set. If it is not, inconsistencies can occur.
 * In a debug build, if such a condition is detected, the program aborts.
 * In a production build, if such a condition is detected, it returns false, and does not modify anything.
 * For a \ref dpa_u_linked_set_p_t, this condition is always detected. For a \ref dpa_u_linked_set_s_t, it is not
 * alwas detected. Regardless, if a program does pass such invalid arguments, it is always to be considered an error.
 * 
 * \param SET the set to add the entry to
 * \param ENTRY the entry to add or remove to/from a set
 * \param BEFORE the entry is to be inserted before this entry
 */
#define dpa_u_linked_set_set(SET, ENTRY, BEFORE) _Generic((ENTRY), \
    struct dpa_u_linked_set_s_entry*: dpa_u_linked_set_s_set, \
    struct dpa_u_linked_set_p_entry*: dpa_u_linked_set_p_set \
  )((SET), (ENTRY), (BEFORE))

/**
 * Takes all entries from the source set, and inserts them before the specified entry of the destination set,
 * or at the end of the destination set if no such entry is specified.
 * If such an entry is specified, but no destination set, the destination set is inferred from the entry.
 * If neither, a destination set, nor a source set is specified, all entries are removed from the source set.
 * 
 * This operation is O(n) for \ref dpa_u_linked_set_p_t, but O(1) for \ref dpa_u_linked_set_s_t, except when
 * removing all entries, then that's also O(n). This is because for \ref dpa_u_linked_set_p_t, the set the entries
 * point to has to be changed for every entry, but for a \ref dpa_u_linked_set_s_t, only the first and last entry need
 * to be modified.
 * 
 * If an entry the source set entries are to be inserted before is specified, it must belong to a set, and if a source
 * set is is also passed to this function, it must be the same set. If it is not, inconsistencies can occur.
 * Additionally, the source set and destination set must never be the same.
 * 
 * In a debug build, if such a condition is detected, the program aborts.
 * In a production build, if such a condition is detected, it returns false, and does not modify anything.
 * For a \ref dpa_u_linked_set_p_t, this condition is always detected. For a \ref dpa_u_linked_set_s_t, it is not
 * always detected. Regardless, if a program does pass such invalid arguments, it is always to be considered an error.
 * 
 * \param DST the set to add the entries to
 * \param SRC the set the entries are taken from
 * \param BEFORE the entry is to be inserted before this entry
 */
#define dpa_u_linked_set_move(DST, SRC, BEFORE) _Generic((SRC), \
    struct dpa_u_linked_set_s*: dpa_u_linked_set_s_move, \
    struct dpa_u_linked_set_p*: dpa_u_linked_set_p_move \
  )((DST), (SRC), (BEFORE))

/**
 * Removes all entries from a set.
 */
#define dpa_u_linked_set_clear(SET) _Generic((SET), \
    struct dpa_u_linked_set_s*: dpa_u_linked_set_s_clear, \
    struct dpa_u_linked_set_p*: dpa_u_linked_set_p_clear \
  )((SET))

/** Get the first entry from a set */
#define dpa_u_linked_set_get_first(SET) _Generic((SET), \
          struct dpa_u_linked_set_s : _Generic(DPA_U_G(struct dpa_u_linked_set_s, (SET)).v.p+0, \
                  uintptr_t*: (      dpa_u_linked_set_s_entry_t*)DPA_U_G (struct dpa_u_linked_set_s, (SET)).v.p[0], \
            const uintptr_t*: (const dpa_u_linked_set_s_entry_t*)DPA_U_G (struct dpa_u_linked_set_s, (SET)).v.p[0] \
    ), \
          struct dpa_u_linked_set_s*: (      dpa_u_linked_set_s_entry_t*)DPA_U_G(      struct dpa_u_linked_set_s*, (SET))->v.p[0], \
    const struct dpa_u_linked_set_s*: (const dpa_u_linked_set_s_entry_t*)DPA_U_G(const struct dpa_u_linked_set_s*, (SET))->v.p[0], \
          struct dpa_u_linked_set_p : _Generic(DPA_U_G(struct dpa_u_linked_set_p, (SET)).v.p+0, \
                  uintptr_t*: (      dpa_u_linked_set_p_entry_t*)DPA_U_G (struct dpa_u_linked_set_p, (SET)).v.p[0], \
            const uintptr_t*: (const dpa_u_linked_set_p_entry_t*)DPA_U_G (struct dpa_u_linked_set_p, (SET)).v.p[0] \
    ), \
          struct dpa_u_linked_set_p*: (      dpa_u_linked_set_p_entry_t*)DPA_U_G(      struct dpa_u_linked_set_p*, (SET))->v.p[0], \
    const struct dpa_u_linked_set_p*: (const dpa_u_linked_set_p_entry_t*)DPA_U_G(const struct dpa_u_linked_set_p*, (SET))->v.p[0] \
  )

/** Get the last entry from a set */
#define dpa_u_linked_set_get_last(SET)  _Generic((SET), \
          struct dpa_u_linked_set_s : _Generic(DPA_U_G(struct dpa_u_linked_set_s, (SET)).v.p+0, \
                  uintptr_t*: (      dpa_u_linked_set_s_entry_t*)DPA_U_G (struct dpa_u_linked_set_s, (SET)).v.p[1], \
            const uintptr_t*: (const dpa_u_linked_set_s_entry_t*)DPA_U_G (struct dpa_u_linked_set_s, (SET)).v.p[1] \
    ), \
          struct dpa_u_linked_set_s*: (      dpa_u_linked_set_s_entry_t*)DPA_U_G(      struct dpa_u_linked_set_s*, (SET))->v.p[1], \
    const struct dpa_u_linked_set_s*: (const dpa_u_linked_set_s_entry_t*)DPA_U_G(const struct dpa_u_linked_set_s*, (SET))->v.p[1], \
          struct dpa_u_linked_set_p : _Generic(DPA_U_G(struct dpa_u_linked_set_p, (SET)).v.p+0, \
                  uintptr_t*: (      dpa_u_linked_set_p_entry_t*)DPA_U_G (struct dpa_u_linked_set_p, (SET)).v.p[1], \
            const uintptr_t*: (const dpa_u_linked_set_p_entry_t*)DPA_U_G (struct dpa_u_linked_set_p, (SET)).v.p[1] \
    ), \
          struct dpa_u_linked_set_p*: (      dpa_u_linked_set_p_entry_t*)DPA_U_G(      struct dpa_u_linked_set_p*, (SET))->v.p[1], \
    const struct dpa_u_linked_set_p*: (const dpa_u_linked_set_p_entry_t*)DPA_U_G(const struct dpa_u_linked_set_p*, (SET))->v.p[1] \
  )

static inline
dpa_u_linked_set_s_entry_t* dpa__u_linked_set_s_to_entry(uintptr_t x){
  if(x & DPA_U_LINKED_SET_S_TAG_SET)
    return 0;
  return (dpa_u_linked_set_s_entry_t*)x;
}

/** Get the next entry in the set */
#define dpa_u_linked_set_get_next(ENTRY) _Generic((ENTRY), \
          struct dpa_u_linked_set_s_entry : _Generic(DPA_U_G(struct dpa_u_linked_set_s_entry, (ENTRY)).p+0, \
                  uintptr_t*: dpa__u_linked_set_s_to_entry(DPA_U_G (struct dpa_u_linked_set_s_entry, (ENTRY)).p[0]), \
            const uintptr_t*: (const dpa_u_linked_set_s_entry_t*)dpa__u_linked_set_s_to_entry(DPA_U_G (struct dpa_u_linked_set_s_entry, (ENTRY)).p[0]) \
    ), \
          struct dpa_u_linked_set_s_entry*:       dpa__u_linked_set_s_to_entry( DPA_U_G(      struct dpa_u_linked_set_s_entry*, (ENTRY))->p[0] ), \
    const struct dpa_u_linked_set_s_entry*: (const dpa_u_linked_set_s_entry_t*)dpa__u_linked_set_s_to_entry( DPA_U_G(const struct dpa_u_linked_set_s_entry*, (ENTRY))->p[0] ), \
          struct dpa_u_linked_set_p_entry : _Generic(DPA_U_G(struct dpa_u_linked_set_p_entry, (ENTRY)).p+0, \
                  uintptr_t*: (      dpa_u_linked_set_p_entry_t*)DPA_U_G (struct dpa_u_linked_set_p_entry, (ENTRY)).p[0], \
            const uintptr_t*: (const dpa_u_linked_set_p_entry_t*)DPA_U_G (struct dpa_u_linked_set_p_entry, (ENTRY)).p[0] \
    ), \
          struct dpa_u_linked_set_p_entry*: (      dpa_u_linked_set_p_entry_t*) DPA_U_G(      struct dpa_u_linked_set_p_entry*, (ENTRY))->p[0], \
    const struct dpa_u_linked_set_p_entry*: (const dpa_u_linked_set_p_entry_t*) DPA_U_G(const struct dpa_u_linked_set_p_entry*, (ENTRY))->p[0] \
  )

/** Get the previous entry in the set */
#define dpa_u_linked_set_get_previous(ENTRY)  _Generic((ENTRY), \
          struct dpa_u_linked_set_s_entry : _Generic(DPA_U_G(struct dpa_u_linked_set_s_entry, (ENTRY)).p+0, \
                  uintptr_t*: dpa__u_linked_set_s_to_entry(DPA_U_G (struct dpa_u_linked_set_s_entry, (ENTRY)).p[1]), \
            const uintptr_t*: (const dpa_u_linked_set_s_entry_t*)dpa__u_linked_set_s_to_entry(DPA_U_G (struct dpa_u_linked_set_s_entry, (ENTRY)).p[1]) \
    ), \
          struct dpa_u_linked_set_s_entry*: dpa__u_linked_set_s_to_entry( DPA_U_G(      struct dpa_u_linked_set_s_entry*, (ENTRY))->p[1] ), \
    const struct dpa_u_linked_set_s_entry*: (const dpa_u_linked_set_s_entry_t*)dpa__u_linked_set_s_to_entry( DPA_U_G(const struct dpa_u_linked_set_s_entry*, (ENTRY))->p[1] ), \
          struct dpa_u_linked_set_p_entry : _Generic(DPA_U_G(struct dpa_u_linked_set_p_entry, (ENTRY)).p+0, \
                  uintptr_t*: (      dpa_u_linked_set_p_entry_t*)DPA_U_G (struct dpa_u_linked_set_p_entry, (ENTRY)).p[1], \
            const uintptr_t*: (const dpa_u_linked_set_p_entry_t*)DPA_U_G (struct dpa_u_linked_set_p_entry, (ENTRY)).p[1] \
    ), \
          struct dpa_u_linked_set_p_entry*: (      dpa_u_linked_set_p_entry_t*) DPA_U_G(      struct dpa_u_linked_set_p_entry*, (ENTRY))->p[1], \
    const struct dpa_u_linked_set_p_entry*: (const dpa_u_linked_set_p_entry_t*) DPA_U_G(const struct dpa_u_linked_set_p_entry*, (ENTRY))->p[1] \
  )

/** @} */
/** @} */

#endif
