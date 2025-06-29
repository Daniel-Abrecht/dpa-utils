#ifndef DPA_U_BO_TYPES_2_H
#define DPA_U_BO_TYPES_2_H

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-bo Buffer Objects
 * @{
 **/

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

/** @} */
/** @} */

#endif
