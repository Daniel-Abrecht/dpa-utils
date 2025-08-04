/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-list List
 * @{
 * This is a simple dynamic array.
 * All the macros will call the functions of the same name, suffixed with `_sa_p` or `_ma_p`.
 * Which one is called depends on the alignment requirement of the type of the list entries.
 */
#ifndef DPA_U_LIST_H
#define DPA_U_LIST_H 1

#include <dpa/utils/common.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stdalign.h>

/** This is a generic opaque type to signify all lists. */
typedef struct dpa_u_list dpa_u_list_t;

/**
 * Generic type for linked lists. In a definition, it is to be used like so:
 * ```
 * dpa_u_list(int) mylist;
 * ```
 * 
 * \param T the type of the list entries
 */
#define dpa_u_list(T) union { \
    dpa__u_typeof_maybe(T)* ptr; /* All access is done using this member. */ \
    dpa_u_list_t* _meta; /* This is to verify that it's a dpa_u_list_t. */ \
  }

#define dpa__u_list_list(X)   (1? (dpa_u_list_t* ) (X)->ptr : ((void)((dpa_u_list_t*){(X)->_meta}), (dpa_u_list_t* )0) )
#define dpa__u_list_plist(X)  (1? (dpa_u_list_t**)&(X)->ptr : ((void)((X)->_meta=(dpa_u_list_t*)0), (dpa_u_list_t**)0) )

#ifdef dpa_u_typeof
#define dpa__u_list_av(LIST, NAME) (sizeof(struct dpa__u_list_small) % alignof(dpa_u_typeof((LIST)->ptr[0])) ? NAME ## _ma_p : NAME ## _sa_p)
#else
#define dpa__u_list_av(LIST, NAME) (sizeof(struct dpa__u_list_small) % sizeof((LIST)->ptr[0]) ? NAME ## _ma_p : NAME ## _sa_p)
#endif

/**
 * List A will be replaced by list B.
 * List A is freed if necessary.
 * List B is set to 0.
 */
#define dpa_u_list_move(A, B) (1? dpa__u_list_av((A), dpa_u_list_move)(dpa__u_list_plist((A)), dpa__u_list_plist((B))) : (((A)->ptr=(B)->ptr),(void)0) )

/**
 * Swaps lists A and B.
 */
#define dpa_u_list_swap(A, B) (1? dpa__u_list_swap_p(dpa__u_list_plist((A)), dpa__u_list_plist((B))) : (((A)->ptr=(B)->ptr),(void)0) )

/**
 * Append new entries to a list.
 * 
 * \param LIST the list pointer
 * \param COUNT the number of new items
 * \param ENTRIES an array of new entries
 */
#define dpa_u_list_append(LIST, COUNT, ...) dpa__u_list_av((LIST), dpa_u_list_append)( dpa__u_list_plist((LIST)), sizeof((LIST)->ptr[0]), COUNT, (1? (__VA_ARGS__) : (LIST)->ptr) )

/** Returns the number of entries in the list. */
#define dpa_u_list_length(LIST) dpa__u_list_av((LIST), dpa_u_list_length)( dpa__u_list_list((LIST)) )

/** Returns a pointer to the first entry of the array */
#define dpa_u_list_data(LIST) (1? (LIST)->ptr : ((void)((dpa_u_list_t*){(LIST)->_meta}), (LIST)->ptr) )

/**
 * Increase the size of the array. The new entries will be 0 initialized.
 * 
 * \param LIST the list pointer
 * \param COUNT the number of new entries
 */
#define dpa_u_list_grow(LIST, COUNT) dpa__u_list_av((LIST), dpa_u_list_grow)( dpa__u_list_plist((LIST)), sizeof((LIST)->ptr[0]), COUNT )

/**
 * Reserve enough space for COUNT additional entries.
 * This does not change the length of the list.
 * 
 * \param LIST the list pointer
 * \param COUNT the number of additional entries
 */
#define dpa_u_list_reserve(LIST, COUNT) dpa__u_list_av((LIST), dpa_u_list_reserve)( dpa__u_list_plist((LIST)), sizeof((LIST)->ptr[0]), COUNT )

/**
 * Decrease the size of the array.
 * 
 * \param LIST the list pointer
 * \param COUNT the number of items to remove
 */
#define dpa_u_list_shrink(LIST, COUNT) dpa__u_list_av((LIST), dpa_u_list_shrink)( dpa__u_list_plist((LIST)), sizeof((LIST)->ptr[0]), COUNT )

/**
 * Frees all list entries. The list will be empty afterwards.
 * 
 * \param LIST the list pointer
 */
#define dpa_u_list_clear(LIST) dpa__u_list_av((LIST), dpa_u_list_clear)( dpa__u_list_plist((LIST)) )

#ifdef dpa_u_typeof
#define dpa_u_list_push(LIST, VALUE) dpa_u_list_append((LIST), 1, (dpa_u_typeof(VALUE)[]){(VALUE)})
#endif

/**
 * Returns the last item in RET & removes it from the list.
 * 
 * \param LIST the list
 * \param RET A pointer to the variable the item is to be stored in
 */
#define dpa_u_list_pop(LIST, RET) dpa__u_list_av((LIST), dpa_u_list_pop)( dpa__u_list_plist((LIST)), sizeof((LIST)->ptr[0]), (1? (RET) : (LIST)->ptr) )

struct dpa__u_list_small {
  size_t count : sizeof(size_t)*CHAR_BIT-CHAR_BIT;
  size_t lbsize : CHAR_BIT;
};

struct dpa__u_list_maxalign {
  size_t count;
  int lbsize;
  max_align_t data[];
};

dpa__u_api inline void dpa__u_list_swap_p(dpa_u_list_t** a, dpa_u_list_t** b){
  void* tmp = *a;
  *a = *b;
  *b = tmp;
}
/** \cond 0 */
#define dpa_u_list_swap_sa_p dpa__u_list_swap_p
#define dpa_u_list_swap_ma_p dpa__u_list_swap_p
/** \endcond */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#elif DPA_U_LIST_H < 3
#if DPA_U_LIST_H == 1
#undef DPA_U_LIST_H
#define DPA_U_LIST_H 2
#define X(NAME) NAME ## _ma_p
#define DPA__U_LIST_T struct dpa__u_list_maxalign
#elif DPA_U_LIST_H == 2
#undef DPA_U_LIST_H
#define DPA_U_LIST_H 3
#define X(NAME) NAME ## _sa_p
#define DPA__U_LIST_T struct dpa__u_list_small
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This section is included twice. Once for the _ma_p and once for the _sa_p functions.
// One uses the struct dpa__u_list_small type for metadata, the other one the struct dpa__u_list_maxalign type.
// This is because dpa__u_list_maxalign usually wastes 8 bytes, but on some architectures, max_align_t is 16 bytes big,
// so if a type with such an insanely big alignment is used, we do need to make the metadata structure that big anyway
// for the following data to align properly...

dpa__u_api inline
size_t X(dpa_u_list_length)(dpa_u_list_t* list){
  return list ? ((DPA__U_LIST_T*)list)[-1].count : 0;
}

dpa__u_api inline
void X(dpa_u_list_move)(dpa_u_list_t** dst, dpa_u_list_t** src){
  if(*dst == *src)
    return;
  if(*dst)
    free(((DPA__U_LIST_T*)*dst)-1);
  *dst = *src;
  *src = 0;
}

dpa__u_api inline
void X(dpa_u_list_clear)(dpa_u_list_t** list){
  if(!*list)
    return;
  free(((DPA__U_LIST_T*)*list)-1);
  *list = 0;
}

dpa__u_api bool X(dpa_u_list_pop)(dpa_u_list_t** list, unsigned entry_size, void* ret);
dpa__u_api bool X(dpa_u_list_grow)(dpa_u_list_t** list, unsigned entry_size, size_t count);
dpa__u_api void X(dpa_u_list_shrink)(dpa_u_list_t** list, unsigned entry_size, size_t count);
dpa__u_api bool X(dpa_u_list_append)(dpa_u_list_t** list, unsigned entry_size, size_t count, const void* entries);
dpa__u_api bool X(dpa_u_list_reserve)(dpa_u_list_t** list, unsigned entry_size, size_t count);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef DPA__U_LIST_T
#undef X
#else
#undef DPA_U_LIST_H
#define DPA_U_LIST_H 1000
#endif
#if DPA_U_LIST_H != 1000
#include <dpa/utils/list.h>
#endif

/** @} */
/** @} */
