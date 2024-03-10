// Included by _set-and-map.generator. Internal header.

#ifndef DPA__U_SET_AND_MAP_TEMPLATE
#define DPA__U_SET_AND_MAP_TEMPLATE
#define DPA__U_SM_KIND_SET 1
#define DPA__U_SM_KIND_MAP 2
#endif

#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
#define DPA__U_SM_PREFIX DPA_U_CONCAT_E(DPA_U_CONCAT_E(dpa_u_, set_), DPA__U_SM_NAME)
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#define DPA__U_SM_PREFIX DPA_U_CONCAT_E(DPA_U_CONCAT_E(dpa_u_, map_), DPA__U_SM_NAME)
#endif
#define DPA__U_SM_TYPE DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _t)

#ifdef DPA__U_SM_KEY_TYPE_U
#define DPA__U_SM_KEY_ENTRY_TYPE DPA__U_SM_KEY_TYPE_U
#else
#define DPA__U_SM_KEY_ENTRY_TYPE DPA__U_SM_KEY_TYPE
#endif

#ifdef DPA__U_SM_BO
#define KEY_ENTRY_HASH(X) (X).hash[0]
#define ENTRY_HASH_TYPE size_t
#else
#define KEY_ENTRY_HASH(X) (X)
#define ENTRY_HASH_TYPE DPA__U_SM_KEY_ENTRY_TYPE
#endif

#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
#define LIST_OR_BITMAP_SIZE_THRESHOLD LIST_OR_BITMAP_SIZE_THRESHOLD_SET(DPA__U_SM_KEY_TYPE)
#define IF_MAP(...)
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#define LIST_OR_BITMAP_SIZE_THRESHOLD LIST_OR_BITMAP_SIZE_THRESHOLD_MAP(DPA__U_SM_KEY_TYPE)
#define IF_MAP(...) __VA_ARGS__
#endif

///////////////////////////////////////////

#include DPA__U_SM_TEMPLATE

///////////////////////////////////////////

#undef DPA__U_SM_KEY_ENTRY_TYPE
#undef DPA__U_SM_TYPE
#undef DPA__U_SM_KEY_TYPE
#undef DPA__U_SM_NAME
#undef DPA__U_SM_PREFIX

#undef KEY_ENTRY_HASH
#undef ENTRY_HASH_TYPE
#undef IF_MAP
#undef LIST_OR_BITMAP_SIZE_THRESHOLD

#ifdef DPA__U_SM_NO_BITSET
#undef DPA__U_SM_NO_BITSET
#endif
#ifdef DPA__U_SM_KEY_TYPE_U
#undef DPA__U_SM_KEY_TYPE_U
#endif
#ifdef DPA__U_SM_MICRO_SET
#undef DPA__U_SM_MICRO_SET
#endif
#ifdef DPA__U_SM_BO
#undef DPA__U_SM_BO
#endif
