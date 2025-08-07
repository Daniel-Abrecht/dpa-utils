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
 * It's really a doubly linked set though. An object can only be once in the same list, hence it's a set.
 * That's true for most linked list implementations, there is nothing unusual about this one.
 * 
 * There are two variations.
 * \ref dpa_u_linked_set_p stores the number of current entries, and it's entries (\ref dpa_u_linked_set_p_entry)
 * store a reference to the list they are in.
 * \ref dpa_u_linked_set_s and \ref dpa_u_linked_set_s_entry do not store this additional information.
 * 
 * There are generic macros which will work for either variation.
 */

#include <dpa/utils/common.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct dpa_u_linked_set_s_entry {
  struct dpa_u_linked_set_s_entry *previous, *next;
} dpa_u_linked_set_s_entry_t;

typedef struct dpa_u_linked_set_p_entry {
  struct dpa_u_linked_set_p* set;
  struct dpa_u_linked_set_p_entry *previous, *next;
} dpa_u_linked_set_p_entry_t;

typedef struct dpa_u_linked_set_s {
  dpa_u_linked_set_s_entry_t v;
} dpa_u_linked_set_s_t;

typedef struct dpa_u_linked_set_p {
  size_t length;
  struct {
    struct dpa_u_linked_set_p_entry *previous, *next;
  } v;
} dpa_u_linked_set_p_t;

dpa__u_api bool dpa_u_linked_set_s_set(
  struct dpa_u_linked_set_s* set,
  struct dpa_u_linked_set_s_entry* entry,
  struct dpa_u_linked_set_s_entry* before
);

dpa__u_api bool dpa_u_linked_set_p_set(
  struct dpa_u_linked_set_p* set,
  struct dpa_u_linked_set_p_entry* entry,
  struct dpa_u_linked_set_p_entry* before
);

dpa__u_api bool dpa_u_linked_set_s_move(
  struct dpa_u_linked_set_s* dst,
  struct dpa_u_linked_set_s* src,
  struct dpa_u_linked_set_s_entry* before
);

dpa__u_api bool dpa_u_linked_set_p_move(
  struct dpa_u_linked_set_p* dst,
  struct dpa_u_linked_set_p* src,
  struct dpa_u_linked_set_p_entry* before
);

dpa__u_api void dpa_u_linked_set_s_clear(struct dpa_u_linked_set_s* set);
dpa__u_api void dpa_u_linked_set_p_clear(struct dpa_u_linked_set_p* set);

#define dpa_u_linked_set_set(SET, ENTRY, BEFORE) _Generic((ENTRY), \
    struct dpa_u_linked_set_s_entry*: dpa_u_linked_set_s_set, \
    struct dpa_u_linked_set_p_entry*: dpa_u_linked_set_p_set \
  )((SET), (ENTRY), (BEFORE))

#define dpa_u_linked_set_move(DST, SRC, BEFORE) _Generic((SET), \
    struct dpa_u_linked_set_s*: dpa_u_linked_set_s_move, \
    struct dpa_u_linked_set_p*: dpa_u_linked_set_p_move \
  )((DST), (SRC), (BEFORE))

#define dpa_u_linked_set_clear(SET) _Generic((SET), \
    struct dpa_u_linked_set_s*: dpa_u_linked_set_s_clear, \
    struct dpa_u_linked_set_p*: dpa_u_linked_set_p_clear \
  )((SET))

/** @} */
/** @} */

#endif
