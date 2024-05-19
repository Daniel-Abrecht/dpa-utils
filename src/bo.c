#include <dpa/utils/bo.h>

#undef DPA_U_BO_INLINE
#undef DPA_U_BO_SIMPLE
#undef DPA_U_BO_UNIQUE_HASHMAP
#undef DPA_U_BO_HASHED
#undef DPA_U_BO_REFCOUNTED
#undef DPA_U_BO_REFCOUNTED_HASHED

DPA_U_ENUM_DEF(dpa_u_bo_any_type)

#ifdef DPA_U_BO_UNIQUE_UINT_COMPATIBLE
 extern dpa_u_bo_unique_as_uint_t dpa_u_bo_unique_to_uint(dpa_u_bo_unique_t v);
 extern dpa_u_bo_unique_t dpa_u_bo_unique_from_uint(dpa_u_bo_unique_as_uint_t v);
#endif
