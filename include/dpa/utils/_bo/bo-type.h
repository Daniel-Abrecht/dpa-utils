#ifndef DPA_U_BO_TYPES_H
#define DPA_U_BO_TYPES_H

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-bo Buffer Objects
 * @{
 **/

typedef struct dpa__u_boptr {
  uint64_t value[1];
} dpa__u_boptr_t;
static_assert(sizeof(dpa__u_boptr_t) == sizeof(uint64_t), "Unexpected padding in struct dpa__u_boptr");

/**
 * A simple buffer object.
 * All it does is store a pointer to some data and it's size.
 */
typedef struct dpa_u_bo {
  union {
    struct {
      size_t size;
      const void* data;
    };
    char _c[1];
  };
} dpa_u_bo_t;

typedef struct dpa__u_bo_refcounted {
  dpa_u_refcount_freeable_t* refcount;
  dpa_u_bo_t bo;
} dpa__u_bo_refcounted_t;

typedef struct dpa__u_bo_hashed {
  dpa_u_bo_t bo;
  uint64_t hash;
} dpa__u_bo_hashed_t;

typedef struct dpa__u_bo_refcounted_hashed {
  dpa__u_bo_refcounted_t rbo;
  uint64_t hash;
} dpa__u_bo_refcounted_hashed_t;

/**
 * A tagged pointer for a unique BO, or an unique BO with inlined data.
 * Those BOs can only be created using \ref dpa_u_bo_intern.
 * This tagged pointer has the property of being unique. If two \ref dpa_u_a_bo_unique_t have the same data,
 * then they also have the same value.
 * A unique BO has a refcount, but it is not a refcounted BO. A refcounted BO points to the refcount of it's data only,
 * whereas a unique BO has a refcount that applies to the BO object itself. The lifetime of a unique BOs data may exceed
 * the lifetime of the unique BO, since it's data can be refcounted or static, but it doesn't have to be.
 * The data of a unique BO is immutable. This BO always has the \ref DPA_U_BO_UNIQUE tag set.
 */
typedef struct dpa__u_a_bo_unique     { dpa__u_boptr_t p; } dpa_u_a_bo_unique_t;

/**
 * A tagged pointer. All tags are valid for this BO. See \ref dpa_u_bo_type_flags for a list of possible tags.
 */
typedef struct dpa__u_a_bo_any        { dpa__u_boptr_t p; } dpa_u_a_bo_any_t;

/**
 * A tagged pointer.
 * It will have at least one of the tags \ref DPA_U_BO_REFCOUNTED, \ref DPA_U_BO_UNIQUE, \ref DPA_U_BO_STATIC.
 * Unless it is an error BO, those are inline BOs without any tags.
 */
typedef struct dpa__u_a_bo_gc         { dpa__u_boptr_t p; } dpa_u_a_bo_gc_t;

/**
 * A tagged pointer.
 * It must have the \ref DPA_U_BO_REFCOUNTED and \ref DPA_U_BO_SIMPLE tag set.
 * It can't be a \ref DPA_U_BO_UNIQUE, because those can be inline BOs, which are not refcounted.
 * Unless it is an error BO, those are inline BOs without any tags.
 * This BO always has a poiner to a refcount, which controls the lifetime of it's data.
 */
typedef struct dpa__u_a_bo_refcounted { dpa__u_boptr_t p; } dpa_u_a_bo_refcounted_t;

/**
 * A tagged pointer.
 * It must have the \ref DPA_U_BO_HASHED and \ref DPA_U_BO_SIMPLE tag set. It can't be a \ref DPA_U_BO_UNIQUE.
 * Unless it is an error BO, those are inline BOs without any tags.
 * This BO is pre-hashed. You can get it's hash in O(1).
 *
 * You can also get the hash of a unique BO in O(1), but they are only pre-hashed if they exceed a certain size.
 * The decision not to allow unique BOs in \ref dpa_u_a_bo_hashed_t is somewhat arbitrary, and may be changed
 * in the future, but that'd be a major change.
 */
typedef struct dpa__u_a_bo_hashed     { dpa__u_boptr_t p; } dpa_u_a_bo_hashed_t;

static_assert(sizeof(dpa_u_a_bo_unique_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_any_t)    == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_gc_t)     == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");

/** @} */
/** @} */

#endif
