#ifndef DPA_U_HASH_COMMON_H
#define DPA_U_HASH_COMMON_H

#define DPA_U_FNV_64_PRIME        UINT64_C(0x100000001B3)      ///< This is the FNV Prime used for 64 bit hashs by the FNV algorithm
#define DPA_U_FNV_64_OFFSET_BASIS UINT64_C(0xCBF29CE484222325) ///< This is the initial hash value used when calculating the 64 bit FNV hash

#define DPA_U_FNV_32_PRIME        UINT32_C(0x01000193) ///< This is the FNV Prime used for 32 bit hashs by the FNV algorithm
#define DPA_U_FNV_32_OFFSET_BASIS UINT32_C(0x811c9dc5) ///< This is the initial hash value used when calculating the 32 bit FNV hash

#include <dpa/utils/_bo/bo-type.h>

/**
 * Updates the hash using the new data in bo
 * \param bo The buffer with the new data
 * \param hash The old hash to be updated
 * \returns the new Hash
 */
dpa__u_api inline uint64_t dpa_u_hash_64_FNV_1a_append_p(dpa_u_bo_t bo, uint_fast64_t hash){
  const uint8_t* data = bo.data;
  for(size_t i=0, n=bo.size; i<n; i++)
    hash = (hash ^ data[i]) * DPA_U_FNV_64_PRIME;
  return hash;
}

#endif
