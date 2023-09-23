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
static inline uint64_t dpa_u_hash_FNV_1a_append_p(dpa_u_bo_ro_t bo, uint_fast64_t hash){
  const uint8_t* data = dpa_u_bo_data(bo);
  for(size_t i=0, n=dpa_u_bo_get_size(bo); i<n; i++)
    hash = (hash ^ data[i]) * DPA_U_FNV_PRIME;
  return hash;
}
#define dpa_u_hash_FNV_1a_append(bo, old_hash) dpa_u_hash_FNV_1a_append_p(dpa_u_v_bo_ro((bo)), (old_hash))

static inline uint64_t dpa_u_hash_FNV_1a_p(dpa_u_bo_ro_t bo){
  return dpa_u_hash_FNV_1a_append(bo, DPA_U_FNV_OFFSET_BASIS);
}
#define dpa_u_hash_FNV_1a(bo) dpa_u_hash_FNV_1a_p(dpa_u_v_bo_ro((bo)))

DPA_U_EXPORT extern uint_fast64_t dpa_hash_offset_basis;

struct dpa__u_default_hash_args {
  dpa_u_bo_ro_t bo;
  uint_fast64_t old_hash;
};
static inline uint64_t dpa_u_bo_get_hash_p(const struct dpa__u_default_hash_args args){
  // The xor is to allow an initial old_hash of 0.
  const uint_fast64_t basis = dpa_hash_offset_basis;
  return dpa_u_hash_FNV_1a_append(args.bo, args.old_hash ^ basis) ^ basis;
}

#define dpa__u_bo_get_hash(bo,...) dpa_u_bo_get_hash_p((const struct dpa__u_default_hash_args){dpa_u_v_bo_ro((bo)),__VA_ARGS__});
/**
 * This function returns a platform dependent, non-cryptografic hash, intended for use in hash maps and similar datastructures.
 * The hash will change between program executions, this is intended to make it harder to pre-compute colliding hashed.
 * The old hash can be passed as the second argument.
 */
#define dpa_u_bo_get_hash(...) dpa__u_bo_get_hash(__VA_ARGS__,)

#endif
