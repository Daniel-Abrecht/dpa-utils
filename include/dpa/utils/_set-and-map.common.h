#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
#define DPA__U_SM_PREFIX DPA_U_CONCAT_E(dpa_u_set_, DPA__U_SM_NAME)
#define DPA___U_SM_PREFIX DPA_U_CONCAT_E(dpa__u_set_, DPA__U_SM_NAME)
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#define DPA__U_SM_PREFIX DPA_U_CONCAT_E(dpa_u_map_, DPA__U_SM_NAME)
#define DPA___U_SM_PREFIX DPA_U_CONCAT_E(dpa__u_map_, DPA__U_SM_NAME)
#endif
#define DPA__U_SM_TYPE DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _t)

#ifdef DPA__U_SM_KEY_TYPE_U
#define DPA__U_SM_KEY_ENTRY_TYPE DPA__U_SM_KEY_TYPE_U
#else
#define DPA__U_SM_KEY_ENTRY_TYPE DPA__U_SM_KEY_TYPE
#endif

#define DPA__U_SM_KEY_ENTRY_HASH(X) (X)
#define DPA__U_SM_ENTRY_HASH_TYPE DPA__U_SM_KEY_ENTRY_TYPE

#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
#define DPA__U_SM_LIST_OR_BITMAP_SIZE_THRESHOLD DPA__U_SM_LIST_OR_BITMAP_SIZE_THRESHOLD_SET(DPA__U_SM_KEY_TYPE)
#define DPA__U_SM_IF_MAP(...)
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#define DPA__U_SM_LIST_OR_BITMAP_SIZE_THRESHOLD DPA__U_SM_LIST_OR_BITMAP_SIZE_THRESHOLD_MAP(DPA__U_SM_KEY_TYPE)
#define DPA__U_SM_IF_MAP(...) __VA_ARGS__
#endif

#define DPA__U_SM_TYPE_IT_S DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _it_safe_t)
#define DPA__U_SM_TYPE_IT_F DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _it_fast_t)

#define DPA__U_SM_HASH DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _hash_sub)
#define DPA__U_SM_UNHASH DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _unhash_sub)

///////////////////////////////////////////

#include DPA__U_SM_TEMPLATE

///////////////////////////////////////////

#undef DPA__U_SM_TYPE_IT

#undef DPA__U_SM_KEY_ENTRY_TYPE
#undef DPA__U_SM_TYPE
#undef DPA__U_SM_KEY_TYPE
#undef DPA__U_SM_NAME
#undef DPA__U_SM_PREFIX
#undef DPA___U_SM_PREFIX
#undef DPA__U_SM_HASH
#undef DPA__U_SM_UNHASH

#undef DPA__U_SM_KEY_ENTRY_HASH
#undef DPA__U_SM_ENTRY_HASH_TYPE
#undef DPA__U_SM_IF_MAP
#undef DPA__U_SM_LIST_OR_BITMAP_SIZE_THRESHOLD

#ifdef DPA__U_SM_NO_BITSET
#undef DPA__U_SM_NO_BITSET
#endif
#ifdef DPA__U_SM_KEY_TYPE_U
#undef DPA__U_SM_KEY_TYPE_U
#endif
#ifdef DPA__U_SM_MICRO_SET
#undef DPA__U_SM_MICRO_SET
#endif
