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
 * Some hash functions.
 */

#include <dpa/utils/_hash/hash.h>

/**
 * Implements 64-bit FNV 1a. Takes the data to be appended and the old hash, and returns the new hash.
 * This way, the hash can be calculated in a streaming fashion.
 * If there was no prior data / hash, the \ref DPA_U_FNV_64_OFFSET_BASIS is usually used to seed the old hash.
 * This is not a cryptographic hash function.
 * 
 * \param BO the bo containing the new data
 * \param old_hash The old hash value
 */
#define dpa_u_hash_64_FNV_1a_append(bo, old_hash) dpa_u_hash_64_FNV_1a_append_p(dpa_u_to_bo((bo)), (old_hash))

/**
 * Implements 64-bit FNV 1a. Takes a BO, returns it's hash.
 * This is not a cryptographic hash function.
 * 
 * \param bo The BO to be hashed
 * \returns the hash
 */
#define dpa_u_hash_64_FNV_1a(bo) dpa_u_hash_64_FNV_1a_p(dpa_u_to_bo((bo)))
dpa__u_api inline uint64_t dpa_u_hash_64_FNV_1a_p(dpa_u_bo_t bo){
  return dpa_u_hash_64_FNV_1a_append(bo, DPA_U_FNV_64_OFFSET_BASIS);
}

/**
 * Implements 32-bit FNV 1a. Takes the data to be appended and the old hash, and returns the new hash.
 * This way, the hash can be calculated in a streaming fashion.
 * If there was no prior data / hash, the \ref DPA_U_FNV_32_OFFSET_BASIS is usually used to seed the old hash.
 * This is not a cryptographic hash function.
 * 
 * \param BO the bo containing the new data
 * \param old_hash The old hash value
 */
#define dpa_u_hash_32_FNV_1a_append(bo, old_hash) dpa_u_hash_32_FNV_1a_append_p(dpa_u_to_bo((bo)), (old_hash))
dpa__u_api inline uint32_t dpa_u_hash_32_FNV_1a_append_p(dpa_u_bo_t bo, uint_fast32_t hash){
  const uint8_t* data = bo.data;
  for(size_t i=0, n=bo.size; i<n; i++)
    hash = (hash ^ data[i]) * DPA_U_FNV_32_PRIME;
  return hash;
}

/**
 * Implements 32-bit FNV 1a. Takes a BO, returns it's hash.
 * This is not a cryptographic hash function.
 * 
 * \param bo The BO to be hashed
 * \returns the hash
 */
#define dpa_u_hash_32_FNV_1a(bo) dpa_u_hash_32_FNV_1a_p(dpa_u_to_bo((bo)))
dpa__u_api inline uint32_t dpa_u_hash_32_FNV_1a_p(dpa_u_bo_t bo){
  return dpa_u_hash_32_FNV_1a_append(bo, DPA_U_FNV_32_OFFSET_BASIS);
}

/**
 * A 16-bit hash function currently based on 32-bit FNV 1a.
 * Takes the data to be appended and the old hash, and returns the new hash.
 * This way, the hash can be calculated in a streaming fashion.
 * If there was no prior data / hash, the \ref DPA_U_FNV_32_OFFSET_BASIS is usually used to seed the old hash.
 * This is not a cryptographic hash function.
 * 
 * \param BO the bo containing the new data
 * \param old_hash The old hash value
 */
#define dpa_u_hash_16_append(bo, old_hash) dpa_u_hash_16_append_p(dpa_u_to_bo((bo)), (old_hash))
dpa__u_api inline uint16_t dpa_u_hash_16_append_p(dpa_u_bo_t bo, uint_fast32_t hash){
  const uint8_t* data = bo.data;
  for(size_t i=0, n=bo.size; i<n; i++){
    hash = (hash ^ data[i]) * DPA_U_FNV_32_PRIME;
    hash = ((hash >> 16) ^ hash)  & 0xFFFF;
  }
  return hash;
}

/**
 * Takes a BO, returns a 16-bit hash.
 * This is not a cryptographic hash function.
 */
#define dpa_u_hash_16(bo) dpa_u_hash_16_p(dpa_u_to_bo((bo)))
dpa__u_api inline uint16_t dpa_u_hash_16_p(dpa_u_bo_t bo){
  return dpa_u_hash_16_append(bo, DPA_U_FNV_32_OFFSET_BASIS);
}

/**
 * Fills a buffer with really random data.
 */
dpa__u_api void dpa_u_getrandom(void* buf, size_t buflen);

/**
 * Initializes the \ref dpa_u_seed value, should only be called once on startup.
 * This usually happens automatically on startup, manually calling this function isn't usually necessary.
 */
dpa__u_api void dpa_u_init_seed(void);

/** @} */
/** @} */

#endif
