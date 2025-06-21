#ifndef DPA_U_HASH_H
#define DPA_U_HASH_H

#include <dpa/utils/common.h>
#include <dpa/utils/bo.h>
#include <stdint.h>
#include <string.h>

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-hash Hash functions
 * @{
 */

#include <dpa/utils/_hash/hash.h>

#define dpa_u_hash_64_FNV_1a_append(bo, old_hash) dpa_u_hash_64_FNV_1a_append_p(dpa_u_to_bo((bo)), (old_hash))

dpa__u_api inline uint64_t dpa_u_hash_64_FNV_1a_p(dpa_u_bo_t bo){
  return dpa_u_hash_64_FNV_1a_append(bo, DPA_U_FNV_64_OFFSET_BASIS);
}
#define dpa_u_hash_64_FNV_1a(bo) dpa_u_hash_64_FNV_1a_p(dpa_u_to_bo((bo)))

dpa__u_api inline uint32_t dpa_u_hash_32_FNV_1a_append_p(dpa_u_bo_t bo, uint_fast32_t hash){
  const uint8_t* data = bo.data;
  for(size_t i=0, n=bo.size; i<n; i++)
    hash = (hash ^ data[i]) * DPA_U_FNV_32_PRIME;
  return hash;
}
#define dpa_u_hash_32_FNV_1a_append(bo, old_hash) dpa_u_hash_32_FNV_1a_append_p(dpa_u_to_bo((bo)), (old_hash))

dpa__u_api inline uint32_t dpa_u_hash_32_FNV_1a_p(dpa_u_bo_t bo){
  return dpa_u_hash_32_FNV_1a_append(bo, DPA_U_FNV_32_OFFSET_BASIS);
}
#define dpa_u_hash_32_FNV_1a(bo) dpa_u_hash_32_FNV_1a_p(dpa_u_to_bo((bo)))


dpa__u_api inline uint16_t dpa_u_hash_16_append_p(dpa_u_bo_t bo, uint_fast32_t hash){
  const uint8_t* data = bo.data;
  for(size_t i=0, n=bo.size; i<n; i++){
    hash = (hash ^ data[i]) * DPA_U_FNV_32_PRIME;
    hash = (hash >> 16) ^ hash;
  }
  return hash & 0xFFFF;
}
#define dpa_u_hash_16_append(bo, old_hash) dpa_u_hash_16_append_p(dpa_u_to_bo((bo)), (old_hash))

dpa__u_api inline uint16_t dpa_u_hash_16_p(dpa_u_bo_t bo){
  return dpa_u_hash_16_append(bo, DPA_U_FNV_32_OFFSET_BASIS);
}
#define dpa_u_hash_16(bo) dpa_u_hash_16_p(dpa_u_to_bo((bo)))

dpa__u_api void dpa_u_getrandom(void* buf, size_t buflen);
dpa__u_api void dpa_u_init_seed(void);

/** @} */
/** @} */

#endif
