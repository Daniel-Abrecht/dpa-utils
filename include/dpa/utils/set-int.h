#ifndef DPA_U_SET_INT_H
#define DPA_U_SET_INT_H

#include <dpa/utils/common.h>

#define DPA__U_SM_TEMPLATE <dpa/utils/_set-and-map.h.template>
#define DPA__U_SM_KIND DPA__U_SM_KIND_SET
#include <dpa/utils/_set-and-map.generator>
#undef DPA__U_SM_KIND


/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-set Set
 * @{
 */

/////////////////////////////////////////////////////////////////////////////
// The following typedefs are for documentation purposes,                  //
// they are already defined by the template, but doxygen doesn't see them. //
/////////////////////////////////////////////////////////////////////////////

typedef struct dpa_u_set_pointer dpa_u_set_pointer_t;
typedef struct dpa_u_set_uc dpa_u_set_uc_t;
typedef struct dpa_u_set_us dpa_u_set_us_t;
typedef struct dpa_u_set_u dpa_u_set_u_t;
typedef struct dpa_u_set_lu dpa_u_set_lu_t;
typedef struct dpa_u_set_llu dpa_u_set_llu_t;
typedef struct dpa_u_set_z dpa_u_set_z_t;
typedef struct dpa_u_set_u8 dpa_u_set_u8_t;
typedef struct dpa_u_set_u16 dpa_u_set_u16_t;
typedef struct dpa_u_set_u24 dpa_u_set_u24_t;
typedef struct dpa_u_set_u32 dpa_u_set_u32_t;
typedef struct dpa_u_set_u64 dpa_u_set_u64_t;
typedef struct dpa_u_set_u128 dpa_u_set_u128_t;
typedef struct dpa_u_set_u256 dpa_u_set_u256_t;

typedef struct dpa_u_set_pointer_it_safe dpa_u_set_pointer_it_safe_t;
typedef struct dpa_u_set_uc_it_safe dpa_u_set_uc_it_safe_t;
typedef struct dpa_u_set_us_it_safe dpa_u_set_us_it_safe_t;
typedef struct dpa_u_set_u_it_safe dpa_u_set_u_it_safe_t;
typedef struct dpa_u_set_lu_it_safe dpa_u_set_lu_it_safe_t;
typedef struct dpa_u_set_llu_it_safe dpa_u_set_llu_it_safe_t;
typedef struct dpa_u_set_z_it_safe dpa_u_set_z_it_safe_t;
typedef struct dpa_u_set_u8_it_safe dpa_u_set_u8_it_safe_t;
typedef struct dpa_u_set_u16_it_safe dpa_u_set_u16_it_safe_t;
typedef struct dpa_u_set_u24_it_safe dpa_u_set_u24_it_safe_t;
typedef struct dpa_u_set_u32_it_safe dpa_u_set_u32_it_safe_t;
typedef struct dpa_u_set_u64_it_safe dpa_u_set_u64_it_safe_t;
typedef struct dpa_u_set_u128_it_safe dpa_u_set_u128_it_safe_t;
typedef struct dpa_u_set_u256_it_safe dpa_u_set_u256_it_safe_t;

typedef struct dpa_u_set_pointer_it_fast dpa_u_set_pointer_it_fast_t;
typedef struct dpa_u_set_uc_it_fast dpa_u_set_uc_it_fast_t;
typedef struct dpa_u_set_us_it_fast dpa_u_set_us_it_fast_t;
typedef struct dpa_u_set_u_it_fast dpa_u_set_u_it_fast_t;
typedef struct dpa_u_set_lu_it_fast dpa_u_set_lu_it_fast_t;
typedef struct dpa_u_set_llu_it_fast dpa_u_set_llu_it_fast_t;
typedef struct dpa_u_set_z_it_fast dpa_u_set_z_it_fast_t;
typedef struct dpa_u_set_u8_it_fast dpa_u_set_u8_it_fast_t;
typedef struct dpa_u_set_u16_it_fast dpa_u_set_u16_it_fast_t;
typedef struct dpa_u_set_u24_it_fast dpa_u_set_u24_it_fast_t;
typedef struct dpa_u_set_u32_it_fast dpa_u_set_u32_it_fast_t;
typedef struct dpa_u_set_u64_it_fast dpa_u_set_u64_it_fast_t;
typedef struct dpa_u_set_u128_it_fast dpa_u_set_u128_it_fast_t;
typedef struct dpa_u_set_u256_it_fast dpa_u_set_u256_it_fast_t;

/////////////////////////////////////////////////////////////////////////////

/** @} */
/** @} */

#endif
