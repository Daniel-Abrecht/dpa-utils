#ifndef DPA_U_MAP_INT_H
#define DPA_U_MAP_INT_H

#include <dpa/utils/common.h>

#define DPA__U_SM_TEMPLATE <dpa/utils/_set-and-map.h.template>
#define DPA__U_SM_KIND DPA__U_SM_KIND_MAP
#include <dpa/utils/_set-and-map.generator>
#undef DPA__U_SM_KIND


/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-map Map
 * @{
 */

/////////////////////////////////////////////////////////////////////////////
// The following typedefs are for documentation purposes,                  //
// they are already defined by the template, but doxygen doesn't see them. //
/////////////////////////////////////////////////////////////////////////////

typedef struct dpa_u_map_pointer dpa_u_map_pointer_t;
typedef struct dpa_u_map_uc dpa_u_map_uc_t;
typedef struct dpa_u_map_us dpa_u_map_us_t;
typedef struct dpa_u_map_u dpa_u_map_u_t;
typedef struct dpa_u_map_lu dpa_u_map_lu_t;
typedef struct dpa_u_map_llu dpa_u_map_llu_t;
typedef struct dpa_u_map_z dpa_u_map_z_t;
typedef struct dpa_u_map_u8 dpa_u_map_u8_t;
typedef struct dpa_u_map_u16 dpa_u_map_u16_t;
typedef struct dpa_u_map_u24 dpa_u_map_u24_t;
typedef struct dpa_u_map_u32 dpa_u_map_u32_t;
typedef struct dpa_u_map_u64 dpa_u_map_u64_t;
typedef struct dpa_u_map_u128 dpa_u_map_u128_t;
typedef struct dpa_u_map_u256 dpa_u_map_u256_t;

typedef struct dpa_u_map_pointer_it_safe dpa_u_map_pointer_it_safe_t;
typedef struct dpa_u_map_uc_it_safe dpa_u_map_uc_it_safe_t;
typedef struct dpa_u_map_us_it_safe dpa_u_map_us_it_safe_t;
typedef struct dpa_u_map_u_it_safe dpa_u_map_u_it_safe_t;
typedef struct dpa_u_map_lu_it_safe dpa_u_map_lu_it_safe_t;
typedef struct dpa_u_map_llu_it_safe dpa_u_map_llu_it_safe_t;
typedef struct dpa_u_map_z_it_safe dpa_u_map_z_it_safe_t;
typedef struct dpa_u_map_u8_it_safe dpa_u_map_u8_it_safe_t;
typedef struct dpa_u_map_u16_it_safe dpa_u_map_u16_it_safe_t;
typedef struct dpa_u_map_u24_it_safe dpa_u_map_u24_it_safe_t;
typedef struct dpa_u_map_u32_it_safe dpa_u_map_u32_it_safe_t;
typedef struct dpa_u_map_u64_it_safe dpa_u_map_u64_it_safe_t;
typedef struct dpa_u_map_u128_it_safe dpa_u_map_u128_it_safe_t;
typedef struct dpa_u_map_u256_it_safe dpa_u_map_u256_it_safe_t;

typedef struct dpa_u_map_pointer_it_fast dpa_u_map_pointer_it_fast_t;
typedef struct dpa_u_map_uc_it_fast dpa_u_map_uc_it_fast_t;
typedef struct dpa_u_map_us_it_fast dpa_u_map_us_it_fast_t;
typedef struct dpa_u_map_u_it_fast dpa_u_map_u_it_fast_t;
typedef struct dpa_u_map_lu_it_fast dpa_u_map_lu_it_fast_t;
typedef struct dpa_u_map_llu_it_fast dpa_u_map_llu_it_fast_t;
typedef struct dpa_u_map_z_it_fast dpa_u_map_z_it_fast_t;
typedef struct dpa_u_map_u8_it_fast dpa_u_map_u8_it_fast_t;
typedef struct dpa_u_map_u16_it_fast dpa_u_map_u16_it_fast_t;
typedef struct dpa_u_map_u24_it_fast dpa_u_map_u24_it_fast_t;
typedef struct dpa_u_map_u32_it_fast dpa_u_map_u32_it_fast_t;
typedef struct dpa_u_map_u64_it_fast dpa_u_map_u64_it_fast_t;
typedef struct dpa_u_map_u128_it_fast dpa_u_map_u128_it_fast_t;
typedef struct dpa_u_map_u256_it_fast dpa_u_map_u256_it_fast_t;

/////////////////////////////////////////////////////////////////////////////

/** @} */
/** @} */

#endif
