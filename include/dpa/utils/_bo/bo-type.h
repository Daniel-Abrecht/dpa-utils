#ifndef DPA_U_BO_TYPES_H
#define DPA_U_BO_TYPES_H

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-bo Buffer Objects
 **/

typedef struct dpa__u_boptr {
  uint64_t value[1];
} dpa__u_boptr_t;
static_assert(sizeof(dpa__u_boptr_t) == sizeof(uint64_t), "Unexpected padding in struct dpa__u_boptr");

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

typedef struct dpa__u_a_bo_unique     { dpa__u_boptr_t p; } dpa_u_a_bo_unique_t;
typedef struct dpa__u_a_bo_any        { dpa__u_boptr_t p; } dpa_u_a_bo_any_t;
typedef struct dpa__u_a_bo_gc         { dpa__u_boptr_t p; } dpa_u_a_bo_gc_t;
typedef struct dpa__u_a_bo_refcounted { dpa__u_boptr_t p; } dpa_u_a_bo_refcounted_t;
typedef struct dpa__u_a_bo_hashed     { dpa__u_boptr_t p; } dpa_u_a_bo_hashed_t;

static_assert(sizeof(dpa_u_a_bo_unique_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_any_t)    == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_gc_t)     == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");

/** @} */
/** @} */

#endif
