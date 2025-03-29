#ifndef DPA_U_HASH_H
#define DPA_U_HASH_H

#include <dpa/utils/common.h>
#include <dpa/utils/bo.h>
#include <stdint.h>
#include <string.h>

typedef uint64_t dpa_u_hash_t;

#define DPA_U_FNV_64_PRIME        UINT64_C(0x100000001B3)      ///< This is the FNV Prime used for 64 bit hashs by the FNV algorithm
#define DPA_U_FNV_64_OFFSET_BASIS UINT64_C(0xCBF29CE484222325) ///< This is the initial hash value used when calculating the 64 bit FNV hash

#define DPA_U_FNV_32_PRIME        UINT32_C(0x01000193) ///< This is the FNV Prime used for 32 bit hashs by the FNV algorithm
#define DPA_U_FNV_32_OFFSET_BASIS UINT32_C(0x811c9dc5) ///< This is the initial hash value used when calculating the 32 bit FNV hash

/**
 * Updates the hash using the new data in bo
 * \param bo The buffer with the new data
 * \param hash The old hash to be updated
 * \returns the new Hash
 */
dpa__u_api inline uint64_t dpa_u_hash_64_FNV_1a_append_p(dpa_u_bo_ro_t bo, uint_fast64_t hash){
  const uint8_t* data = (uint8_t*)dpa_u_bo_get_data(bo);
  for(size_t i=0, n=dpa_u_bo_get_size(bo); i<n; i++)
    hash = (hash ^ data[i]) * DPA_U_FNV_64_PRIME;
  return hash;
}
#define dpa_u_hash_64_FNV_1a_append(bo, old_hash) dpa_u_hash_64_FNV_1a_append_p(dpa_u_to_bo_ro((bo)), (old_hash))

dpa__u_api inline uint64_t dpa_u_hash_64_FNV_1a_p(dpa_u_bo_ro_t bo){
  return dpa_u_hash_64_FNV_1a_append(bo, DPA_U_FNV_64_OFFSET_BASIS);
}
#define dpa_u_hash_64_FNV_1a(bo) dpa_u_hash_64_FNV_1a_p(dpa_u_to_bo_ro((bo)))

dpa__u_api inline uint32_t dpa_u_hash_32_FNV_1a_append_p(dpa_u_bo_ro_t bo, uint_fast32_t hash){
  const uint8_t* data = (uint8_t*)dpa_u_bo_get_data(bo);
  for(size_t i=0, n=dpa_u_bo_get_size(bo); i<n; i++)
    hash = (hash ^ data[i]) * DPA_U_FNV_32_PRIME;
  return hash;
}
#define dpa_u_hash_32_FNV_1a_append(bo, old_hash) dpa_u_hash_32_FNV_1a_append_p(dpa_u_to_bo_ro((bo)), (old_hash))

dpa__u_api inline uint32_t dpa_u_hash_32_FNV_1a_p(dpa_u_bo_ro_t bo){
  return dpa_u_hash_32_FNV_1a_append(bo, DPA_U_FNV_32_OFFSET_BASIS);
}
#define dpa_u_hash_32_FNV_1a(bo) dpa_u_hash_32_FNV_1a_p(dpa_u_to_bo_ro((bo)))


dpa__u_api inline uint16_t dpa_u_hash_16_append_p(dpa_u_bo_ro_t bo, uint_fast32_t hash){
  const uint8_t* data = (uint8_t*)dpa_u_bo_get_data(bo);
  for(size_t i=0, n=dpa_u_bo_get_size(bo); i<n; i++){
    hash = (hash ^ data[i]) * DPA_U_FNV_32_PRIME;
    hash = (hash >> 16) ^ hash;
  }
  return hash & 0xFFFF;
}
#define dpa_u_hash_16_append(bo, old_hash) dpa_u_hash_16_append_p(dpa_u_to_bo_ro((bo)), (old_hash))

dpa__u_api inline uint16_t dpa_u_hash_16_p(dpa_u_bo_ro_t bo){
  return dpa_u_hash_16_append(bo, DPA_U_FNV_32_OFFSET_BASIS);
}
#define dpa_u_hash_16(bo) dpa_u_hash_16_p(dpa_u_to_bo_ro((bo)))

dpa__u_api void dpa_u_getrandom(void* buf, size_t buflen);
dpa__u_api void dpa_u_init_seed(void);

#endif
