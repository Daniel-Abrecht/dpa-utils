#ifndef DPA_U_HASH_H
#define DPA_U_HASH_H

#include <dpa/utils/common.h>
#include <dpa/utils/bo.h>
#include <stdint.h>
#include <string.h>

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
DPA_U_EXPORT inline uint64_t dpa_u_hash_64_FNV_1a_append_p(dpa_u_bo_ro_t bo, uint_fast64_t hash){
  const uint8_t* data = dpa_u_bo_data(bo);
  for(size_t i=0, n=dpa_u_bo_get_size(bo); i<n; i++)
    hash = (hash ^ data[i]) * DPA_U_FNV_64_PRIME;
  return hash;
}
#define dpa_u_hash_64_FNV_1a_append(bo, old_hash) dpa_u_hash_64_FNV_1a_append_p(dpa_u_v_bo_ro((bo)), (old_hash))

DPA_U_EXPORT inline uint64_t dpa_u_hash_64_FNV_1a_p(dpa_u_bo_ro_t bo){
  return dpa_u_hash_64_FNV_1a_append(bo, DPA_U_FNV_64_OFFSET_BASIS);
}
#define dpa_u_hash_64_FNV_1a(bo) dpa_u_hash_64_FNV_1a_p(dpa_u_v_bo_ro((bo)))

DPA_U_EXPORT inline uint32_t dpa_u_hash_32_FNV_1a_append_p(dpa_u_bo_ro_t bo, uint_fast32_t hash){
  const uint8_t* data = dpa_u_bo_data(bo);
  for(size_t i=0, n=dpa_u_bo_get_size(bo); i<n; i++)
    hash = (hash ^ data[i]) * DPA_U_FNV_32_PRIME;
  return hash;
}
#define dpa_u_hash_32_FNV_1a_append(bo, old_hash) dpa_u_hash_32_FNV_1a_append_p(dpa_u_v_bo_ro((bo)), (old_hash))

DPA_U_EXPORT inline uint32_t dpa_u_hash_32_FNV_1a_p(dpa_u_bo_ro_t bo){
  return dpa_u_hash_32_FNV_1a_append(bo, DPA_U_FNV_32_OFFSET_BASIS);
}
#define dpa_u_hash_32_FNV_1a(bo) dpa_u_hash_32_FNV_1a_p(dpa_u_v_bo_ro((bo)))


DPA_U_EXPORT inline uint16_t dpa_u_hash_16_append_p(dpa_u_bo_ro_t bo, uint_fast32_t hash){
  const uint8_t* data = dpa_u_bo_data(bo);
  for(size_t i=0, n=dpa_u_bo_get_size(bo); i<n; i++){
    hash = (hash ^ data[i]) * DPA_U_FNV_32_PRIME;
    hash = (hash >> 16) ^ hash;
  }
  return hash & 0xFFFF;
}
#define dpa_u_hash_16_append(bo, old_hash) dpa_u_hash_16_append_p(dpa_u_v_bo_ro((bo)), (old_hash))

DPA_U_EXPORT inline uint16_t dpa_u_hash_16_p(dpa_u_bo_ro_t bo){
  return dpa_u_hash_16_append(bo, DPA_U_FNV_32_OFFSET_BASIS);
}
#define dpa_u_hash_16(bo) dpa_u_hash_16_p(dpa_u_v_bo_ro((bo)))

typedef size_t dpa_u_hash_t;

#define DPA_U_FNV_PRIME _Generic( \
    (char(*)[sizeof(dpa_u_hash_t)]){0}, \
    char(*)[sizeof(uint64_t)]: DPA_U_FNV_64_PRIME, \
    char(*)[sizeof(uint32_t)]: DPA_U_FNV_32_PRIME, \
    char(*)[sizeof(uint16_t)]: DPA_U_FNV_32_PRIME \
  )
#define DPA_U_FNV_OFFSET_BASIS _Generic( \
    (char(*)[sizeof(dpa_u_hash_t)]){0}, \
    char(*)[sizeof(uint64_t)]: DPA_U_FNV_64_OFFSET_BASIS, \
    char(*)[sizeof(uint32_t)]: DPA_U_FNV_32_OFFSET_BASIS, \
    char(*)[sizeof(uint16_t)]: DPA_U_FNV_32_OFFSET_BASIS \
  )

#define dpa_u_hash_FNV_1a_append_p _Generic( \
    (char(*)[sizeof(dpa_u_hash_t)]){0}, \
    char(*)[sizeof(uint64_t)]: dpa_u_hash_64_FNV_1a_append_p, \
    char(*)[sizeof(uint32_t)]: dpa_u_hash_32_FNV_1a_append_p, \
    char(*)[sizeof(uint16_t)]: dpa_u_hash_16_append_p \
  )
#define dpa_u_hash_FNV_1a_append(bo, old_hash) dpa_u_hash_FNV_1a_append_p(dpa_u_v_bo_ro((bo)), (old_hash))

#define dpa_u_hash_FNV_1a_p _Generic( \
    (char(*)[sizeof(dpa_u_hash_t)]){0}, \
    char(*)[sizeof(uint64_t)]: dpa_u_hash_64_FNV_1a_p, \
    char(*)[sizeof(uint32_t)]: dpa_u_hash_32_FNV_1a_p, \
    char(*)[sizeof(uint16_t)]: dpa_u_hash_16_p \
  )
#define dpa_u_hash_FNV_1a(bo) dpa_u_hash_FNV_1a_p(dpa_u_v_bo_ro((bo)))

DPA_U_EXPORT extern dpa_u_hash_t dpa_hash_offset_basis;

struct dpa__u_default_hash_args {
  dpa_u_bo_ro_t bo;
  dpa_u_hash_t old_hash;
};
DPA_U_EXPORT inline dpa_u_hash_t dpa_u_bo_hash_p(const struct dpa__u_default_hash_args args){
  // The xor is to allow an initial old_hash of 0.
  const dpa_u_hash_t basis = dpa_hash_offset_basis;
  return dpa_u_hash_FNV_1a_append(args.bo, args.old_hash ^ basis) ^ basis;
}

#define dpa__u_bo_hash(bo,...) dpa_u_bo_hash_p((const struct dpa__u_default_hash_args){dpa_u_v_bo_ro((bo)),__VA_ARGS__});
/**
 * This function returns a platform dependent, non-cryptografic hash, intended for use in hash maps and similar datastructures.
 * The hash will change between program executions, this is intended to make it harder to pre-compute colliding hashes.
 * The old hash can be passed as the second argument.
 */
#define dpa_u_bo_hash(...) dpa__u_bo_hash(__VA_ARGS__,)

#endif
