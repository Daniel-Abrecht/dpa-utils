#ifndef DPA_U_HASH_H
#define DPA_U_HASH_H

#include <dpa/utils/bo.h>
#include <stdint.h>
#include <string.h>

#define DPA_U_FNV_PRIME        ((uint64_t)0x100000001B3llu)      ///< This is the FNV Prime used for 64 bit hashs by the FNV algorithm
#define DPA_U_FNV_OFFSET_BASIS ((uint64_t)0xCBF29CE484222325llu) ///< This is the initial hash value used when calculating the 64 bit FNV hash

/**
 * Updates the hash using the new data in bo
 * \param bo The buffer with the new data
 * \param hash The old hash to be updated
 * \returns the new Hash
 */
static inline uint64_t dpa_u_hash_FNV_1a_append(dpa_u_bo_ro_t bo, uint_fast64_t hash){
  const uint8_t* data = dpa_u_bo_data(bo);
  for(size_t i=0, n=dpa_u_bo_get_size(bo); i<n; i++)
    hash = (hash ^ data[i]) * DPA_U_FNV_PRIME;
  return hash;
}

static inline uint64_t dpa_u_hash_FNV_1a(dpa_u_bo_ro_t bo){
  return dpa_u_hash_FNV_1a_append(bo, DPA_U_FNV_OFFSET_BASIS);
}

static inline uint64_t dpa__u_default_hash(dpa_u_bo_ro_t bo, uint_fast64_t hash){
  // The xor is to allow an initial hash of 0.
  return dpa_u_hash_FNV_1a_append(bo, hash ^ DPA_U_FNV_OFFSET_BASIS) ^ DPA_U_FNV_OFFSET_BASIS;
}

static inline uint64_t dpa__u_bo_inline_get_hash(const dpa_u_bo_inline_t bo, uint_fast64_t old_hash){
  // TODO: Surely there should be some good way to take advantage of this 16 byte aligned buffer to generate a hash really fast.
  // You could use compiler intrinsics and vectorisations, and you can use it like a u128 number.
  // In practice, I haven't found anything good yet, so this doesn't do anything fancy...
  return dpa__u_default_hash(dpa_u_v_bo_ro(bo), old_hash);
}

static inline uint64_t dpa__u_bo_ro_get_hash(const dpa_u_bo_ro_t bo, uint_fast64_t old_hash){
  if(dpa_u_bo_get_size(bo) > DPA_U_BO_INLINE_MAX_SIZE){
    return dpa__u_default_hash(bo, old_hash);
  }else{
    // To make sure the hashes will be consistent between bo types.
    dpa_u_bo_inline_t ibo = {
      .type = DPA_U_BO_INLINE,
      .size = dpa_u_bo_get_size(bo),
    };
    memcpy(ibo.data, dpa_u_bo_data(bo), ibo.size);
    return dpa__u_bo_inline_get_hash(ibo, old_hash);
  }
}

#define dpa__u_bo_get_hash(bo, old_hash, ...) _Generic((bo), \
    dpa_u_bo_inline_t: dpa__u_bo_inline_get_hash(DPA__G(dpa_u_bo_inline_t, (bo)), (old_hash)), \
    default: dpa__u_bo_ro_get_hash(dpa_u_v_bo_ro((bo)), (old_hash)) \
  )

/**
 * This function returns a platform dependent, non-cryptografic hash, intended for use in hash maps and similar datastructures.
 * The hash is not guaranteed to be consistent between program executions (it currently is, but that may change in future versions).
 * The old hash can be passed as the second argument.
 */
#define dpa_u_bo_get_hash(...) dpa__u_bo_get_hash(__VA_ARGS__, 0, 0);

#endif
