#ifndef DPA_UTILS_BO_H
#define DPA_UTILS_BO_H

#include <dpa/utils/common.h>
#include <dpa/utils/refcount.h>

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdalign.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

/////////////////////////////////
//////      Constants      //////
/////////////////////////////////

enum { DPA__U_BO_COMMON_SIZE = sizeof(size_t) + sizeof(void*) };
enum { DPA_U_BO_INLINE_MAX_SIZE = DPA__U_BO_COMMON_SIZE-1 };
#define DPA_U_BO_MAX_SIZE (((size_t)1)<<((sizeof(size_t)-1)*CHAR_BIT))
#define DPA__U_BO_ALIGN alignas(struct{size_t a; void* b;})


//////////////////////////////////
//////      Data types      //////
//////////////////////////////////

typedef size_t dpa_u_hash_t;

typedef struct dpa_u_bo_inline dpa_u_bo_inline_t;
typedef const dpa_u_bo_inline_t dpa_u_bo_inline_ro_t;
typedef struct dpa_u_bo_simple_ro dpa_u_bo_simple_ro_t;
typedef struct dpa_u_bo_simple dpa_u_bo_simple_t;
typedef struct dpa__u_bo_unique_hashmap_entry dpa__u_bo_unique_hashmap_entry_t;
typedef const struct dpa__u_bo_unique_hashmap_entry* dpa_u_bo_unique_hashmap_t;
typedef struct dpa_u_bo_unique dpa_u_bo_unique_t;
typedef struct dpa_u_bo_ro dpa_u_bo_ro_t;
typedef struct dpa_u_bo dpa_u_bo_t;
typedef struct dpa_u_bo_refcounted_ro dpa_u_bo_refcounted_ro_t;

typedef struct dpa_u_bo_refcounted_ro dpa_u_bo_refcounted_ro_t;
typedef struct dpa_u_bo_refcounted dpa_u_bo_refcounted_t;
typedef struct dpa_u_bo_hashed_ro dpa_u_bo_hashed_ro_t;
typedef struct dpa_u_bo_hashed dpa_u_bo_hashed_t;
typedef struct dpa_u_bo_refcounted_hashed_ro dpa_u_bo_refcounted_hashed_ro_t;
typedef struct dpa_u_bo_refcounted_hashed dpa_u_bo_refcounted_hashed_t;

typedef const struct dpa_u_any_bo_inline dpa_u_any_bo_inline_t;
typedef dpa_u_any_bo_inline_t dpa_u_any_bo_inline_ro_t;
typedef const struct dpa_u_any_bo_simple_ro dpa_u_any_bo_simple_ro_t;
typedef const struct dpa_u_any_bo_simple dpa_u_any_bo_simple_t;
typedef const struct dpa_u_any_bo_unique_hashmap dpa_u_any_bo_unique_hashmap_t;
typedef const struct dpa_u_any_bo_unique dpa_u_any_bo_unique_t;
typedef const struct dpa_u_any_bo_ro dpa_u_any_bo_ro_t;
typedef const struct dpa_u_any_bo dpa_u_any_bo_t;

typedef const struct dpa_u_any_bo_refcounted_ro dpa_u_any_bo_refcounted_ro_t;
typedef const struct dpa_u_any_bo_refcounted dpa_u_any_bo_refcounted_t;
typedef const struct dpa_u_any_bo_hashed_ro dpa_u_any_bo_hashed_ro_t;
typedef const struct dpa_u_any_bo_hashed dpa_u_any_bo_hashed_t;
typedef const struct dpa_u_any_bo_refcounted_hashed_ro dpa_u_any_bo_refcounted_hashed_ro_t;

typedef const struct dpa_u_bo_gc_ro dpa_u_bo_gc_ro_t;
typedef const struct dpa_u_bo_with_hash_ro dpa_u_bo_with_hash_ro_t;
typedef const struct dpa_u_bo_with_hash dpa_u_bo_with_hash_t;
typedef const struct dpa_u_bo_with_refcount_ro dpa_u_bo_with_refcount_ro_t;
typedef const struct dpa_u_bo_with_refcount dpa_u_bo_with_refcount_t;
typedef const struct dpa_u_bo_with_refcount_and_hash_ro dpa_u_bo_with_refcount_and_hash_ro_t;

typedef struct dpa_u_bo_unique_hashmap_stats_s dpa_u_bo_unique_hashmap_stats_t;
typedef struct dpa__u_bo_a dpa__u_bo_a_t;

// A bo should always have a type set. If that was forgotten, and it was 0 initialised, the type is 0.
// Because of this, we so not define a type 0, and trying to get the data or size of such a bo may abort().
// It could still be useful to chek if a bo has ben set when passing a pointer to it to a function, though.

#define dpa_u_bo_any_type_list(X) \
  X((DPA_U_BO_INLINE, 1)) \
  X((DPA_U_BO_UNIQUE_HASHMAP)) \
  X((DPA_U_BO_SIMPLE)) \
  X((DPA_U_BO_HASHED)) \
  X((DPA_U_BO_REFCOUNTED)) \
  X((DPA_U_BO_REFCOUNTED_HASHED))

DPA_U_ENUM(dpa_u_bo_any_type)

/**
 * Many compilers have this really nice feature that they can warn you about enums without a case in a switch.
 * Not all types are compatible, so not all of them will need a case. These enums correspond to types with just
 * the possible type constants. The values are the same as in the enum dpa_u_bo_any_type.
 * @{
 */
enum dpa_u_bo_inline_type { DPA_U_BO_INLINE_1 = DPA_U_BO_INLINE };
enum dpa_u_any_bo_inline_type { DPA_U_BO_INLINE_A1 = DPA_U_BO_INLINE };
enum dpa_u_bo_simple_type { DPA_U_BO_SIMPLE_2 = DPA_U_BO_SIMPLE };
enum dpa_u_any_bo_simple_type {
  DPA_U_BO_SIMPLE_A2 = DPA_U_BO_SIMPLE
};
enum dpa_u_bo_unique_hashmap_type { DPA_U_BO_UNIQUE_HASHMAP_3 = DPA_U_BO_UNIQUE_HASHMAP };
enum dpa_u_any_bo_unique_hashmap_type { DPA_U_BO_UNIQUE_HASHMAP_A3 = DPA_U_BO_UNIQUE_HASHMAP };
enum dpa_u_bo_simple_ro_type { DPA_U_BO_SIMPLE_4 = DPA_U_BO_SIMPLE };
enum dpa_u_any_bo_simple_ro_type {
  DPA_U_BO_SIMPLE_A4 = DPA_U_BO_SIMPLE
};
enum dpa_u_bo_hashed_type { DPA_U_BO_HASHED_5 = DPA_U_BO_HASHED };
enum dpa_u_any_bo_hashed_type { DPA_U_BO_HASHED_A5 = DPA_U_BO_HASHED };
enum dpa_u_bo_hashed_ro_type { DPA_U_BO_HASHED_6 = DPA_U_BO_HASHED };
enum dpa_u_any_bo_hashed_ro_type { DPA_U_BO_HASHED_A6 = DPA_U_BO_HASHED };
enum dpa_u_bo_refcounted_type { DPA_U_BO_REFCOUNTED_7 = DPA_U_BO_REFCOUNTED };
enum dpa_u_any_bo_refcounted_type { DPA_U_BO_REFCOUNTED_A7 = DPA_U_BO_REFCOUNTED };
enum dpa_u_bo_refcounted_ro_type { DPA_U_BO_REFCOUNTED_8 = DPA_U_BO_REFCOUNTED };
enum dpa_u_any_bo_refcounted_ro_type {
  DPA_U_BO_REFCOUNTED_A8 = DPA_U_BO_REFCOUNTED,
  DPA_U_BO_REFCOUNTED_HASHED_A8 = DPA_U_BO_REFCOUNTED_HASHED,
};
enum dpa_u_bo_refcounted_hashed_ro_type { DPA_U_BO_REFCOUNTED_HASHED_9 = DPA_U_BO_REFCOUNTED_HASHED };
enum dpa_u_any_bo_refcounted_hashed_ro_type { DPA_U_BO_REFCOUNTED_HASHED_A9 = DPA_U_BO_REFCOUNTED_HASHED };
enum dpa_u_bo_ro_type {
  DPA_U_BO_INLINE_10 = DPA_U_BO_INLINE,
  DPA_U_BO_UNIQUE_HASHMAP_10 = DPA_U_BO_UNIQUE_HASHMAP,
  DPA_U_BO_SIMPLE_10 = DPA_U_BO_SIMPLE,
};
enum dpa_u_any_bo_ro_type {
  DPA_U_BO_INLINE_A10 = DPA_U_BO_INLINE,
  DPA_U_BO_UNIQUE_HASHMAP_A10 = DPA_U_BO_UNIQUE_HASHMAP,
  DPA_U_BO_SIMPLE_A10 = DPA_U_BO_SIMPLE,
};
enum dpa_u_bo_type {
  DPA_U_BO_INLINE_11 = DPA_U_BO_INLINE,
  DPA_U_BO_SIMPLE_11 = DPA_U_BO_SIMPLE,
};
enum dpa_u_any_bo_type {
  DPA_U_BO_INLINE_A11 = DPA_U_BO_INLINE,
  DPA_U_BO_SIMPLE_A11 = DPA_U_BO_SIMPLE,
};
enum dpa_u_bo_unique_type {
  DPA_U_BO_INLINE_12 = DPA_U_BO_INLINE,
  DPA_U_BO_UNIQUE_HASHMAP_12 = DPA_U_BO_UNIQUE_HASHMAP,
};
enum dpa_u_any_bo_unique_type {
  DPA_U_BO_INLINE_A12 = DPA_U_BO_INLINE,
  DPA_U_BO_UNIQUE_HASHMAP_A12 = DPA_U_BO_UNIQUE_HASHMAP,
};
enum dpa_u_bo_with_hash_type {
  DPA_U_BO_INLINE_W20 = DPA_U_BO_INLINE,
  DPA_U_BO_HASHED_W20 = DPA_U_BO_HASHED,
};
enum dpa_u_bo_with_hash_ro_type {
  DPA_U_BO_INLINE_W21 = DPA_U_BO_INLINE,
  DPA_U_BO_UNIQUE_HASHMAP_W21 = DPA_U_BO_UNIQUE_HASHMAP,
  DPA_U_BO_HASHED_W21 = DPA_U_BO_HASHED,
  DPA_U_BO_REFCOUNTED_HASHED_W21 = DPA_U_BO_REFCOUNTED_HASHED,
};
enum dpa_u_bo_with_refcount_type {
  DPA_U_BO_REFCOUNTED_W22 = DPA_U_BO_HASHED,
};
enum dpa_u_bo_with_refcount_ro_type {
  DPA_U_BO_UNIQUE_HASHMAP_W23 = DPA_U_BO_UNIQUE_HASHMAP,
  DPA_U_BO_REFCOUNTED_W23 = DPA_U_BO_REFCOUNTED,
  DPA_U_BO_REFCOUNTED_HASHED_W23 = DPA_U_BO_REFCOUNTED_HASHED,
};
enum dpa_u_bo_with_refcount_and_hash_ro_type {
  DPA_U_BO_UNIQUE_HASHMAP_W24 = DPA_U_BO_UNIQUE_HASHMAP,
  DPA_U_BO_REFCOUNTED_HASHED_W24 = DPA_U_BO_REFCOUNTED_HASHED,
};
enum dpa_u_bo_gc_ro_type {
  DPA_U_BO_INLINE_25 = DPA_U_BO_INLINE,
  DPA_U_BO_UNIQUE_HASHMAP_W25 = DPA_U_BO_UNIQUE_HASHMAP,
  DPA_U_BO_REFCOUNTED_W25 = DPA_U_BO_REFCOUNTED,
  DPA_U_BO_REFCOUNTED_HASHED_W25 = DPA_U_BO_REFCOUNTED_HASHED,
};
// @}

// We erase the type information from these enums, because we do not want it to warn if they are assigned to one of the specialized enums above.
#define DPA_U_BO_INLINE ((int)DPA_U_BO_INLINE)
#define DPA_U_BO_SIMPLE ((int)DPA_U_BO_SIMPLE)
#define DPA_U_BO_UNIQUE_HASHMAP ((int)DPA_U_BO_UNIQUE_HASHMAP)
#define DPA_U_BO_HASHED ((int)DPA_U_BO_HASHED)
#define DPA_U_BO_REFCOUNTED ((int)DPA_U_BO_REFCOUNTED)
#define DPA_U_BO_REFCOUNTED_HASHED ((int)DPA_U_BO_REFCOUNTED_HASHED)

#define case_DPA_U_BO_UNIQUE \
  case DPA_U_BO_INLINE: \
  case DPA_U_BO_UNIQUE_HASHMAP
#define case_DPA_U_ANY_BO_UNIQUE case_DPA_U_BO_UNIQUE
#define case_DPA_U_BO \
  case DPA_U_BO_INLINE: \
  case DPA_U_BO_SIMPLE
#define case_DPA_U_ANY_BO \
  case DPA_U_BO_INLINE: \
  case DPA_U_BO_SIMPLE: \
  case DPA_U_BO_HASHED: \
  case DPA_U_BO_REFCOUNTED
#define case_DPA_U_BO_RO \
  case DPA_U_BO_INLINE: \
  case DPA_U_BO_UNIQUE_HASHMAP: \
  case DPA_U_BO_SIMPLE:
#define case_DPA_U_ANY_BO_RO \
  case DPA_U_BO_INLINE: \
  case DPA_U_BO_UNIQUE_HASHMAP: \
  case DPA_U_BO_SIMPLE: \
  case DPA_U_BO_HASHED: \
  case DPA_U_BO_REFCOUNTED: \
  case DPA_U_BO_REFCOUNTED_HASHED
#define case_DPA_U_ANY_BO_SIMPLE \
  case DPA_U_BO_SIMPLE: \
  case DPA_U_BO_HASHED: \
  case DPA_U_BO_REFCOUNTED:
#define case_DPA_U_ANY_BO_SIMPLE_RO \
  case DPA_U_BO_SIMPLE: \
  case DPA_U_BO_UNIQUE_HASHMAP: \
  case DPA_U_BO_HASHED: \
  case DPA_U_BO_REFCOUNTED: \
  case DPA_U_BO_REFCOUNTED_HASHED:
#define case_DPA_U_ANY_BO_HASHED_RO \
  case DPA_U_BO_HASHED: \
  case DPA_U_BO_UNIQUE_HASHMAP: \
  case DPA_U_BO_REFCOUNTED_HASHED:
#define case_DPA_U_BO_WITH_HASH \
  case DPA_U_BO_HASHED: \
  case DPA_U_BO_INLINE:
#define case_DPA_U_BO_WITH_HASH_RO \
  case DPA_U_BO_INLINE: \
  case DPA_U_BO_UNIQUE_HASHMAP: \
  case DPA_U_BO_HASHED: \
  case DPA_U_BO_REFCOUNTED_HASHED:
#define case_DPA_U_BO_WITH_REFCOUNT \
  case DPA_U_BO_REFCOUNTED: \
  case DPA_U_BO_INLINE:
#define case_DPA_U_BO_WITH_REFCOUNT_RO \
  case DPA_U_BO_INLINE: \
  case DPA_U_BO_REFCOUNTED: \
  case DPA_U_BO_UNIQUE_HASHMAP: \
  case DPA_U_BO_REFCOUNTED_HASHED:
#define case_DPA_U_BO_WITH_REFCOUNT_AND_HASH_RO \
  case DPA_U_BO_INLINE: \
  case DPA_U_BO_UNIQUE_HASHMAP: \
  case DPA_U_BO_REFCOUNTED_HASHED:
#define case_DPA_U_BO_GC_RO \
  case DPA_U_BO_INLINE: \
  case DPA_U_BO_UNIQUE_HASHMAP: \
  case DPA_U_BO_REFCOUNTED: \
  case DPA_U_BO_REFCOUNTED_HASHED:

#define DPA__U_BO_META(X) \
  struct DPA_U_PACKED { \
    unsigned type : CHAR_BIT - 4; \
    unsigned X : 4; \
  }

struct dpa__u_bo_a { char all[DPA__U_BO_COMMON_SIZE]; };
typedef DPA__U_BO_META(extra) dpa__u_bo_meta_t;

struct dpa_u_bo_inline {
  union {
    struct {
      DPA__U_BO_META(size);
      char data[DPA__U_BO_COMMON_SIZE-1];
    };
    DPA__U_BO_ALIGN dpa__u_bo_a_t all;
  };
};
static_assert(sizeof(dpa_u_bo_inline_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_inline_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_inline_t,data) == 1, "Expected data to be at byte 1");

#define DPA__U_BO_SIMPLE_MEMBERS(...) \
  union { \
    struct { \
      DPA__U_BO_META(extra); \
      struct DPA_U_PACKED { \
        size_t size : (sizeof(size_t)-1) * CHAR_BIT; \
      }; \
      __VA_ARGS__ void* data; \
    }; \
    DPA__U_BO_ALIGN dpa__u_bo_a_t all; \
  }

struct dpa_u_bo_simple_ro {
  DPA__U_BO_SIMPLE_MEMBERS(const);
};
static_assert(sizeof(dpa_u_bo_simple_ro_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_simple_ro_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_simple_ro_t,data) == sizeof(size_t), "Expected data to be at a different offset");

struct dpa_u_bo_simple {
  union {
    dpa_u_bo_simple_ro_t ro;
    DPA__U_BO_SIMPLE_MEMBERS();
  };
};
static_assert(sizeof(dpa_u_bo_simple_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_simple_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_simple_t,data) == sizeof(size_t), "Expected data to be at a different offset");

struct dpa_u_bo_unique {
  union {
    struct { DPA__U_BO_META(extra); char _[DPA__U_BO_COMMON_SIZE-1]; };
    dpa_u_bo_inline_t bo_inline;
    struct { DPA__U_BO_META(extra) bo_unique_hashmap_meta; dpa_u_bo_unique_hashmap_t bo_unique_hashmap; };
    DPA__U_BO_ALIGN dpa__u_bo_a_t all;
  };
};
static_assert(sizeof(dpa_u_bo_unique_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_unique_t has an unexpected size");

struct dpa_u_bo_ro {
  union {
    struct { DPA__U_BO_META(extra); char _[DPA__U_BO_COMMON_SIZE-1]; };
    dpa_u_bo_inline_t bo_inline;
    dpa_u_bo_simple_ro_t bo_simple;
    struct { DPA__U_BO_META(extra) bo_unique_hashmap_meta; dpa_u_bo_unique_hashmap_t bo_unique_hashmap; };
    dpa_u_bo_unique_t bo_unique;
    DPA__U_BO_ALIGN dpa__u_bo_a_t all;
  };
};
static_assert(sizeof(dpa_u_bo_ro_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_ro_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_ro_t,_) == 1, "Expected _ to be at a different offset");

struct dpa_u_bo {
  union {
    struct { DPA__U_BO_META(extra); char _[DPA__U_BO_COMMON_SIZE-1]; };
    dpa_u_bo_ro_t ro;
    dpa_u_bo_inline_t bo_inline;
    dpa_u_bo_simple_t bo_simple;
    DPA__U_BO_ALIGN dpa__u_bo_a_t all;
  };
};
static_assert(sizeof(dpa_u_bo_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_t,_) == 1, "Expected _ to be at a different offset");

////

struct dpa_u_bo_refcounted_ro {
  union {
    DPA__U_BO_META(extra);
    dpa_u_bo_simple_ro_t bo_simple;
  };
  // The refcount should be allocated with the data, because it shares the lifetime of the data, not of the bo.
  dpa_u_refcount_freeable_t* refcount;
};

struct dpa_u_bo_refcounted {
  union {
    DPA__U_BO_META(extra);
    struct dpa_u_bo_refcounted_ro ro;
    dpa_u_bo_simple_t bo_simple;
  };
  // The refcount should be allocated with the data, because it shares the lifetime of the data, not of the bo.
  dpa_u_refcount_freeable_t* refcount;
};

struct dpa_u_bo_hashed_ro {
  union {
    DPA__U_BO_META(extra);
    dpa_u_bo_simple_ro_t bo_simple;
  };
  dpa_u_hash_t hash;
};

struct dpa_u_bo_hashed {
  union {
    DPA__U_BO_META(extra);
    dpa_u_bo_simple_t bo_simple;
  };
  dpa_u_hash_t hash;
};

struct dpa_u_bo_refcounted_hashed_ro {
  union {
    DPA__U_BO_META(extra);
    dpa_u_bo_simple_ro_t bo_simple;
    dpa_u_bo_refcounted_ro_t bo_refcounted;
  };
  dpa_u_hash_t hash;
};

// Note: There will be no dpa_u_bo_refcounted_hashed type. The hash and refcount depends on the data.
// The refcount is stored with the data, but the hash is not. Therefore, modifying a refcounted hashed buffer
// is always wrong.

////

struct dpa__u_bo_unique_hashmap_entry {
  dpa_u_bo_hashed_ro_t base;
  struct dpa__u_refcount_bo_unique refcount;
  struct dpa__u_bo_unique_hashmap_entry* next;
};

struct dpa__u_bo_entry_refcounted {
  dpa__u_bo_unique_hashmap_entry_t entry;
  dpa_u_refcount_freeable_t* refcount;
};

struct dpa_u_bo_unique_hashmap_stats_s {
  size_t empty_count;
  size_t collision_count;
  size_t total_buckets;
  size_t entry_count;
  double load_factor;
};

////////////////////////////////////////////
//////      Special helper macro      //////
////////////////////////////////////////////

#define dpa__u_helper_g(T,P,S,X) \
    T: dpa__u_ ## P ## __ ## S(DPA__G(T,(X)))

#define dpa__u_helper_v_g(T,S,X) \
    dpa__u_helper_g(dpa_u_ ## T ## _t, v_ ## T, S, (X)), \
    dpa__u_helper_g(dpa_u_ ## T ## _t*, p_ ## T, S, (X)), \
    dpa__u_helper_g(const dpa_u_ ## T ## _t*, cp_ ## T, S, (X)), \
    dpa_u_any_ ## T ## _t*: dpa__u_any_ ## T ## __ ## S(DPA__G(dpa_u_any_ ## T ## _t*,(X)))

#define dpa__u_helper_all_g(S,X) \
    dpa__u_helper_v_g(bo_inline, S, (X)), \
    dpa__u_helper_g(dpa_u_bo_unique_hashmap_t, v_bo_unique_hashmap, S, (X)), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__ ## S((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    dpa__u_helper_v_g(bo_unique, S, (X)), \
    dpa__u_helper_v_g(bo_simple, S, (X)), \
    dpa__u_helper_v_g(bo_simple_ro, S, (X)), \
    dpa__u_helper_v_g(bo, S, (X)), \
    dpa__u_helper_v_g(bo_ro, S, (X)), \
    dpa__u_helper_v_g(bo_hashed, S, (X)), \
    dpa__u_helper_v_g(bo_hashed_ro, S, (X)), \
    dpa__u_helper_v_g(bo_refcounted, S, (X)), \
    dpa__u_helper_v_g(bo_refcounted_ro, S, (X)), \
    dpa__u_helper_v_g(bo_refcounted_hashed_ro, S, (X)), \
    dpa_u_bo_gc_ro_t*: dpa__u_bo_gc_ro__ ## S(DPA__G(dpa_u_bo_gc_ro_t*,(X))), \
    dpa_u_bo_with_hash_t*: dpa__u_bo_with_hash__ ## S(DPA__G(dpa_u_bo_with_hash_t*,(X))), \
    dpa_u_bo_with_hash_ro_t*: dpa__u_bo_with_hash_ro__ ## S(DPA__G(dpa_u_bo_with_hash_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__ ## S(DPA__G(dpa_u_bo_with_refcount_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount_ro__ ## S(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__ ## S(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X)))

////

#define dpa__u_sort__priority_g(X) _Generic((X), \
    dpa_u_bo_inline_t: 0x10, \
    dpa_u_bo_inline_t*: 0x11, \
    const dpa_u_bo_inline_t*: 0x12, \
    dpa_u_any_bo_inline_t*: 0x14, \
    dpa_u_bo_unique_hashmap_t: 0x20, \
    dpa_u_any_bo_unique_hashmap_t*: 0x24, \
    dpa_u_bo_unique_t: 0x30, \
    dpa_u_bo_unique_t*: 0x31, \
    const dpa_u_bo_unique_t*: 0x32, \
    dpa_u_any_bo_unique_t*: 0x34, \
    dpa_u_bo_simple_t: 0x40, \
    dpa_u_bo_simple_t*: 0x41, \
    const dpa_u_bo_simple_t*: 0x42, \
    dpa_u_any_bo_simple_t*: 0x44, \
    dpa_u_bo_simple_ro_t: 0x50, \
    dpa_u_bo_simple_ro_t*: 0x51, \
    const dpa_u_bo_simple_ro_t*: 0x52, \
    dpa_u_any_bo_simple_ro_t*: 0x54, \
    dpa_u_bo_t: 0x60, \
    dpa_u_bo_t*: 0x61, \
    const dpa_u_bo_t*: 0x62, \
    dpa_u_any_bo_t*: 0x64, \
    dpa_u_bo_hashed_t: 0x70, \
    dpa_u_bo_hashed_t*: 0x71, \
    const dpa_u_bo_hashed_t*: 0x72, \
    dpa_u_any_bo_hashed_t*: 0x74, \
    dpa_u_bo_refcounted_t: 0x80, \
    dpa_u_bo_refcounted_t*: 0x81, \
    const dpa_u_bo_refcounted_t*: 0x82, \
    dpa_u_any_bo_refcounted_t*: 0x84, \
    dpa_u_bo_refcounted_ro_t: 0x90, \
    dpa_u_bo_refcounted_ro_t*: 0x91, \
    const dpa_u_bo_refcounted_ro_t*: 0x92, \
    dpa_u_any_bo_refcounted_ro_t*: 0x94, \
    dpa_u_bo_refcounted_hashed_ro_t: 0xA0, \
    dpa_u_bo_refcounted_hashed_ro_t*: 0xA1, \
    const dpa_u_bo_refcounted_hashed_ro_t*: 0xA2, \
    dpa_u_any_bo_refcounted_hashed_ro_t*: 0xA4, \
    dpa_u_bo_with_refcount_t*: 0xB4, \
    dpa_u_bo_with_refcount_ro_t*: 0xB5, \
    dpa_u_bo_with_refcount_and_hash_ro_t*: 0xB6, \
    dpa_u_bo_ro_t: 0xF0, \
    dpa_u_bo_ro_t*: 0xF1, \
    const dpa_u_bo_ro_t*: 0xF2, \
    dpa_u_any_bo_ro_t*: 0xF4, \
    default: 0xFFF \
  )

// This cuts down the number of type combinations I need to handle.
// For any type in the first argument, only the preceeding or same types in dpa__u_sort__priority_g are possible to appear in the second.
// Because otherwise, the arguments are swapped
// This means we can't rely on argument order anymore, but we only have to deal with each type combination once.
#define dpa__u_sort_param_by_type_g(F,X,Y) _Generic((char(*)[1+(dpa__u_sort__priority_g((X))<dpa__u_sort__priority_g((Y)))]){0}, \
    char(*)[1]: F((X),(Y), 1), \
    char(*)[2]: F((Y),(X),-1) \
  )


///////////////////////////////////////////////
//////      Member access functions      //////
///////////////////////////////////////////////


/**
 * The dpa_u_any_* types are const opaque types. They are to be passed to functions expecting a variant or derived type of the corresponding dpa_u_* type.
 * Some of the dpa_u_any_ typs may not have a correspondng true type, and may just be there to indicate a refcountable bo, or a bo with a (trivially / quickly obtainable) hash.
 * If a pointer to an dpa_u_ is passed to a function, that usually means the function is to return a bo of that type.
 * If a pointer to an dpa_u_any_ is passed to a function, that usually means the function will just use, but not change, the bo in question.
 * This is to make sure pointers to dpa_u_ won't point to derived types. That way, a = *b will be a safe operation for dpa_u_ pointers.
 * Some of these types may not be very useful and are just provided for consistency / completeness.
 * 
 * This macro will not check the type fields for types where only 1 type is possible, it'll just return that type constant.
 * The type returned is always an enum, but which enum depends on the bo in question. This is so that when it's used in a switch,
 * te compiler only warns about the possible type values if they haveno case. It's always safe to cast to (enum dpa_u_bo_any_type),
 * and it's recommended to always use the constants in that struct.
 */
#define dpa_u_bo_get_type(...) dpa_u_assert_selection(dpa_u_bo_get_type_g(__VA_ARGS__))
#define dpa_u_bo_get_type_g(X) dpa_u_generic((X),dpa__u_helper_all_g(get_type,(X)))

#define dpa__u_v_bo_unique_hashmap__get_type(X)   DPA_U_BO_UNIQUE_HASHMAP_3
#define dpa__u_p_bo_unique_hashmap__get_type(X)   DPA_U_BO_UNIQUE_HASHMAP_3
#define dpa__u_cp_bo_unique_hashmap__get_type(X)  DPA_U_BO_UNIQUE_HASHMAP_3
#define dpa__u_any_bo_unique_hashmap__get_type(X) DPA_U_BO_UNIQUE_HASHMAP_A3

#define dpa__u_v_bo_inline__get_type(X)   DPA_U_BO_INLINE_1
#define dpa__u_p_bo_inline__get_type(X)   DPA_U_BO_INLINE_1
#define dpa__u_cp_bo_inline__get_type(X)  DPA_U_BO_INLINE_1
#define dpa__u_any_bo_inline__get_type(X) DPA_U_BO_INLINE_A1

#define dpa__u_v_bo_simple__get_type(X)   DPA_U_BO_SIMPLE_2
#define dpa__u_p_bo_simple__get_type(X)   DPA_U_BO_SIMPLE_2
#define dpa__u_cp_bo_simple__get_type(X)  DPA_U_BO_SIMPLE_2
#define dpa__u_any_bo_simple__get_type(X) ((enum dpa_u_any_bo_simple_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_simple_ro__get_type(X)   DPA_U_BO_SIMPLE_4
#define dpa__u_p_bo_simple_ro__get_type(X)   DPA_U_BO_SIMPLE_4
#define dpa__u_cp_bo_simple_ro__get_type(X)  DPA_U_BO_SIMPLE_4
#define dpa__u_any_bo_simple_ro__get_type(X) ((enum dpa_u_any_bo_simple_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_unique__get_type(X)   ((enum dpa_u_bo_unique_type)((X).type))
#define dpa__u_p_bo_unique__get_type(X)   ((enum dpa_u_bo_unique_type)((X)->type))
#define dpa__u_cp_bo_unique__get_type(X)  ((enum dpa_u_bo_unique_type)((X)->type))
#define dpa__u_any_bo_unique__get_type(X) ((enum dpa_u_any_bo_unique_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo__get_type(X)   ((enum dpa_u_bo_type)((X).type))
#define dpa__u_p_bo__get_type(X)   ((enum dpa_u_bo_type)((X)->type))
#define dpa__u_cp_bo__get_type(X)  ((enum dpa_u_bo_type)((X)->type))
#define dpa__u_any_bo__get_type(X) ((enum dpa_u_any_bo_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_ro__get_type(X)   ((enum dpa_u_bo_ro_type)((X).type))
#define dpa__u_p_bo_ro__get_type(X)   ((enum dpa_u_bo_ro_type)((X)->type))
#define dpa__u_cp_bo_ro__get_type(X)  ((enum dpa_u_bo_ro_type)((X)->type))
#define dpa__u_any_bo_ro__get_type(X) ((enum dpa_u_any_bo_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_hashed_ro__get_type(X)   DPA_U_BO_HASHED_6
#define dpa__u_p_bo_hashed_ro__get_type(X)   DPA_U_BO_HASHED_6
#define dpa__u_cp_bo_hashed_ro__get_type(X)  DPA_U_BO_HASHED_6
#define dpa__u_any_bo_hashed_ro__get_type(X) DPA_U_BO_HASHED_A6

#define dpa__u_v_bo_hashed__get_type(X)   DPA_U_BO_HASHED_5
#define dpa__u_p_bo_hashed__get_type(X)   DPA_U_BO_HASHED_5
#define dpa__u_cp_bo_hashed__get_type(X)  DPA_U_BO_HASHED_5
#define dpa__u_any_bo_hashed__get_type(X) DPA_U_BO_HASHED_A5

#define dpa__u_v_bo_refcounted__get_type(X)   DPA_U_BO_REFCOUNTED_7
#define dpa__u_p_bo_refcounted__get_type(X)   DPA_U_BO_REFCOUNTED_7
#define dpa__u_cp_bo_refcounted__get_type(X)  DPA_U_BO_REFCOUNTED_7
#define dpa__u_any_bo_refcounted__get_type(X) ((enum dpa_u_any_bo_refcounted_type)(((const dpa_u_bo_refcounted_t*)(X))->type))

#define dpa__u_v_bo_refcounted_ro__get_type(X)   DPA_U_BO_REFCOUNTED_8
#define dpa__u_p_bo_refcounted_ro__get_type(X)   DPA_U_BO_REFCOUNTED_8
#define dpa__u_cp_bo_refcounted_ro__get_type(X)  DPA_U_BO_REFCOUNTED_8
#define dpa__u_any_bo_refcounted_ro__get_type(X) ((enum dpa_u_any_bo_refcounted_ro_type)(((const dpa_u_bo_refcounted_ro_t*)(X))->type))

#define dpa__u_v_bo_refcounted_hashed_ro__get_type(X)   DPA_U_BO_REFCOUNTED_HASHED_9
#define dpa__u_p_bo_refcounted_hashed_ro__get_type(X)   DPA_U_BO_REFCOUNTED_HASHED_9
#define dpa__u_cp_bo_refcounted_hashed_ro__get_type(X)  DPA_U_BO_REFCOUNTED_HASHED_9
#define dpa__u_any_bo_refcounted_hashed_ro__get_type(X) DPA_U_BO_REFCOUNTED_HASHED_A9

#define dpa__u_bo_gc_ro__get_type(X) ((enum dpa_u_bo_gc_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))
#define dpa__u_bo_with_hash_ro__get_type(X) ((enum dpa_u_bo_with_hash_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))
#define dpa__u_bo_with_hash__get_type(X) ((enum dpa_u_bo_with_hash_type)(((const dpa__u_bo_meta_t*)(X))->type))
#define dpa__u_bo_with_refcount_ro__get_type(X) ((enum dpa_u_bo_with_refcount_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))
#define dpa__u_bo_with_refcount__get_type(X) ((enum dpa_u_bo_with_refcount_type)(((const dpa__u_bo_meta_t*)(X))->type))
#define dpa__u_bo_with_refcount_and_hash_ro__get_type(X) ((enum dpa_u_bo_with_refcount_and_hash_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))

////

#define dpa_u_bo_data(...) dpa_u_assert_selection(dpa_u_bo_data_g(__VA_ARGS__))
#define dpa_u_bo_data_g(X) dpa_u_generic((X),dpa__u_helper_all_g(data,(X)))

#define dpa__u_v_bo_unique_hashmap__data(X)   ((X)->base.bo_simple.data)
#define dpa__u_p_bo_unique_hashmap__data(X)   ((X)->base.bo_simple.data)
#define dpa__u_cp_bo_unique_hashmap__data(X)  ((X)->base.bo_simple.data)
#define dpa__u_any_bo_unique_hashmap__data(X) ((X)->base.bo_simple.data)

#define dpa__u_v_bo_inline__data(X)   ((X).data)
#define dpa__u_p_bo_inline__data(X)   ((X)->data)
#define dpa__u_cp_bo_inline__data(X)  ((X)->data)
#define dpa__u_any_bo_inline__data(X) (((const dpa_u_bo_inline_t*)(X))->data)

#define dpa__u_v_bo_simple__data(X)   ((X).data)
#define dpa__u_p_bo_simple__data(X)   ((X)->data)
#define dpa__u_cp_bo_simple__data(X)  ((X)->data)
#define dpa__u_any_bo_simple__data(X) (((const dpa_u_bo_simple_t*)(X))->data)

#define dpa__u_v_bo_simple_ro__data(X)   ((X).data)
#define dpa__u_p_bo_simple_ro__data(X)   ((X)->data)
#define dpa__u_cp_bo_simple_ro__data(X)  ((X)->data)
#define dpa__u_any_bo_simple_ro__data(X) (((const dpa_u_bo_simple_ro_t*)(X))->data)

#define dpa__u_v_bo_hashed_ro__data(X)   ((X).bo_simple.data)
#define dpa__u_p_bo_hashed_ro__data(X)   ((X)->bo_simple.data)
#define dpa__u_cp_bo_hashed_ro__data(X)  ((X)->bo_simple.data)
#define dpa__u_any_bo_hashed_ro__data(X) (((const dpa_u_bo_hashed_ro_t*)(X))->bo_simple.data)

#define dpa__u_v_bo_hashed__data(X)   ((X).bo_simple.data)
#define dpa__u_p_bo_hashed__data(X)   ((X)->bo_simple.data)
#define dpa__u_cp_bo_hashed__data(X)  ((X)->bo_simple.data)
#define dpa__u_any_bo_hashed__data(X) (((const dpa_u_bo_hashed_t*)(X))->bo_simple.data)

#define dpa__u_v_bo_refcounted__data(X)   ((X).bo_simple.data)
#define dpa__u_p_bo_refcounted__data(X)   ((X)->bo_simple.data)
#define dpa__u_cp_bo_refcounted__data(X)  ((X)->bo_simple.data)
#define dpa__u_any_bo_refcounted__data(X) (((const dpa_u_bo_refcounted_t*)(X))->bo_simple.data)

#define dpa__u_v_bo_refcounted_ro__data(X)   ((X).bo_simple.data)
#define dpa__u_p_bo_refcounted_ro__data(X)   ((X)->bo_simple.data)
#define dpa__u_cp_bo_refcounted_ro__data(X)  ((X)->bo_simple.data)
#define dpa__u_any_bo_refcounted_ro__data(X) (((const dpa_u_bo_refcounted_ro_t*)(X))->bo_simple.data)

#define dpa__u_v_bo_refcounted_hashed_ro__data(X)   ((X).bo_refcounted.bo_simple.data)
#define dpa__u_p_bo_refcounted_hashed_ro__data(X)   ((X)->bo_refcounted.bo_simple.data)
#define dpa__u_cp_bo_refcounted_hashed_ro__data(X)  ((X)->bo_refcounted.bo_simple.data)
#define dpa__u_any_bo_refcounted_hashed_ro__data(X) (((const dpa_u_bo_refcounted_hashed_ro_t*)(X))->bo_refcounted.bo_simple.data)

DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_bo_gc_ro__data(const dpa_u_bo_gc_ro_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_ro_t*)bo)->data;
    case DPA_U_BO_UNIQUE_HASHMAP:
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED: return ((const dpa_u_bo_simple_ro_t*)bo)->data;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_bo_with_hash_ro__data(const dpa_u_bo_with_hash_ro_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_ro_t*)bo)->data;
    case DPA_U_BO_UNIQUE_HASHMAP:
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED_HASHED: return ((const dpa_u_bo_simple_ro_t*)bo)->data;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_bo_with_hash__data(const dpa_u_bo_with_hash_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((dpa_u_bo_inline_ro_t*)bo)->data;
    case DPA_U_BO_HASHED: return ((const dpa_u_bo_simple_ro_t*)bo)->data;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount_ro__data(X) (((const dpa_u_bo_simple_ro_t*)(X))->data)
#define dpa__u_bo_with_refcount__data(X) (((const dpa_u_bo_simple_ro_t*)(X))->data)
#define dpa__u_bo_with_refcount_and_hash_ro__data(X) (((const dpa_u_bo_simple_ro_t*)(X))->data)

// bo_unique could contain bo_inline. Copying a bo_inline would mean copying it's data.
// This is why we reference it. This also means we need an lvalue here.
#define dpa__u_v_bo_unique__data(X)   dpa__u_cp_bo_unique__data(&(X))
#define dpa__u_p_bo_unique__data(X)   dpa__u_cp_bo_unique__data((X))
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_cp_bo_unique__data(const dpa_u_bo_unique_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo->bo_unique_hashmap->base.bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_any_bo_unique__data(const dpa_u_any_bo_unique_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->data;
    case DPA_U_BO_UNIQUE_HASHMAP: return ((dpa_u_bo_unique_hashmap_t)bo)->base.bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo__data(X) dpa_u_generic(&(X), \
          dpa_u_bo_t*: dpa__u_p_bo__data(&(X)), \
    const dpa_u_bo_t*: dpa__u_cp_bo__data(&(X)) \
  )
DPA_U_EXPORT inline dpa__u_really_inline void* dpa__u_p_bo__data(dpa_u_bo_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_cp_bo__data(const dpa_u_bo_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_any_bo__data(const dpa_u_any_bo_t* const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->data;
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->data;
  }
  dpa_u_unreachable("dpa_u_any_bo_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

// bo_unique could contain bo_inline. Copying a bo_inline would mean copying it's data.
// This is why we reference it. This also means we need an lvalue here.
#define dpa__u_v_bo_ro__data(X)   dpa__u_cp_bo_ro__data(&(X))
#define dpa__u_p_bo_ro__data(X)   dpa__u_cp_bo_ro__data((X))
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_cp_bo_ro__data(const dpa_u_bo_ro_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo->bo_unique_hashmap->base.bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_any_bo_ro__data(const dpa_u_any_bo_ro_t* const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->data;
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->data;
    case DPA_U_BO_UNIQUE_HASHMAP: return ((dpa_u_bo_unique_hashmap_t)bo)->base.bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_any_bo_ro_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

////

#define dpa_u_bo_set_size(...) dpa_u_assert_selection(dpa_u_bo_set_size_g(__VA_ARGS__))
#define dpa_u_bo_set_size_g(X,S) ((void)dpa_u_generic((X), \
    dpa_u_bo_inline_t: dpa__u_v_bo_inline__set_size(DPA__G(dpa_u_bo_inline_t,(X)), (S)), \
    dpa_u_bo_simple_t: dpa__u_v_bo_simple__set_size(DPA__G(dpa_u_bo_simple_t,(X)), (S)), \
    dpa_u_bo_simple_ro_t: dpa__u_v_bo_simple_ro__set_size(DPA__G(dpa_u_bo_simple_ro_t,(X)), (S)), \
    dpa_u_bo_t: dpa__u_v_bo__set_size(DPA__G(dpa_u_bo_t,(X)),(S)), \
    dpa_u_bo_refcounted_t: dpa__u_v_bo_refcounted__set_size(DPA__G(dpa_u_bo_refcounted_t,(X)),(S)), \
    dpa_u_bo_refcounted_ro_t: dpa__u_v_bo_refcounted_ro__set_size(DPA__G(dpa_u_bo_refcounted_ro_t,(X)),(S)), \
    dpa_u_bo_refcounted_hashed_ro_t: dpa__u_v_bo_refcounted_hashed_ro__set_size(DPA__G(dpa_u_bo_refcounted_hashed_ro_t,(X)),(S)) \
    \
    dpa_u_bo_inline_t*: dpa__u_p_bo_inline__set_size(DPA__G(dpa_u_bo_inline_t*,(X)), (S)), \
    dpa_u_bo_simple_t*: dpa__u_p_bo_simple__set_size(&DPA__G(dpa_u_bo_simple_t*,(X)), (S)), \
    dpa_u_bo_simple_ro_t*: dpa__u_p_bo_simple_ro__set_size(&DPA__G(dpa_u_bo_simple_ro_t*,(X)), (S)), \
    dpa_u_bo_t*: dpa__u_p_bo__set_size(DPA__G(dpa_u_bo_t*,(X)),(S)), \
    dpa_u_bo_refcounted_t*: dpa__u_p_bo_refcounted__set_size(DPA__G(dpa_u_bo_refcounted_t*,(X)),(S)), \
    dpa_u_bo_refcounted_ro_t*: dpa__u_p_bo_refcounted_ro__set_size(DPA__G(dpa_u_bo_refcounted_ro_t*,(X)),(S)), \
    dpa_u_bo_refcounted_hashed_ro_t*: dpa__u_p_bo_refcounted_hashed_ro__set_size(DPA__G(dpa_u_bo_refcounted_hashed_ro_t*,(X)),(S)) \
  ))

#define dpa__u_v_bo_inline__set_size(X,S) dpa__u_p_bo_inline__set_size(&(X),(S))
#define dpa__u_p_bo_inline__set_size(X,S) (assert((S) <= DPA_U_BO_INLINE_MAX_SIZE),((X)->size=(S)&0xF))

#define dpa__u_v_bo_simple__set_size(X,S) dpa__u_p_bo_simple__set_size(&(X),(S))
#define dpa__u_p_bo_simple__set_size(X,S) (assert((S) <= DPA_U_BO_MAX_SIZE       ),((X)->size=(S)))

#define dpa__u_v_bo_simple_ro__set_size(X,S) dpa__u_p_bo_simple_ro__set_size(&(X),(S))
#define dpa__u_p_bo_simple_ro__set_size(X,S) (assert((S) <= DPA_U_BO_MAX_SIZE       ),((X)->size=(S)))

#define dpa__u_v_bo_refcounted__set_size(X,S) dpa__u_p_bo_refcounted__set_size(&(X),(S))
#define dpa__u_p_bo_refcounted__set_size(X,S) (assert((S) <= DPA_U_BO_MAX_SIZE       ),((X)->size=(S)))

#define dpa__u_v_bo_refcounted_ro__set_size(X,S) dpa__u_p_bo_refcounted_ro__set_size(&(X),(S))
#define dpa__u_p_bo_refcounted_ro__set_size(X,S) (assert((S) <= DPA_U_BO_MAX_SIZE       ),((X)->size=(S)))

#define dpa__u_v_bo_refcounted_hashed_ro__set_size(X,S) dpa__u_p_bo_refcounted_hashed_ro__set_size(&(X),(S))
#define dpa__u_p_bo_refcounted_hashed_ro__set_size(X,S) (assert((S) <= DPA_U_BO_MAX_SIZE       ),((X)->size=(S)))

#define dpa__u_v_bo__set_size(X,S) dpa__u_p_bo__set_size(&(X),(S))
DPA_U_EXPORT inline dpa__u_really_inline void dpa__u_p_bo__set_size(dpa_u_bo_t*restrict const bo, size_t size){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: {
      assert(size <= DPA_U_BO_INLINE_MAX_SIZE);
      bo->bo_inline.size = size;
    } return;
    case DPA_U_BO_SIMPLE: {
      bo->bo_simple.size = size;
    } return;
  }
  dpa_u_unreachable("Can't set size on bo of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

///

#define dpa_u_bo_get_size(...) dpa_u_assert_selection(dpa_u_bo_get_size_g(__VA_ARGS__))
#define dpa_u_bo_get_size_g(X) dpa_u_generic((X),dpa__u_helper_all_g(get_size,(X)))

#define dpa__u_v_bo_unique_hashmap__get_size(X) ((X)->base.bo_simple.size)
#define dpa__u_p_bo_unique_hashmap__get_size(X) ((X)->base.bo_simple.size)
#define dpa__u_cp_bo_unique_hashmap__get_size(X) ((X)->base.bo_simple.size)
#define dpa__u_any_bo_unique_hashmap__get_size(X) ((X)->base.bo_simple.size)

#define dpa__u_v_bo_inline__get_size(X) ((X).size)
#define dpa__u_p_bo_inline__get_size(X) ((X)->size)
#define dpa__u_cp_bo_inline__get_size(X) ((X)->size)
#define dpa__u_any_bo_inline__get_size(X) (((const dpa_u_bo_inline_t*)(X))->size)

#define dpa__u_v_bo_simple__get_size(X) ((X).size)
#define dpa__u_p_bo_simple__get_size(X) ((X)->size)
#define dpa__u_cp_bo_simple__get_size(X) ((X)->size)
#define dpa__u_any_bo_simple__get_size(X) (((const dpa_u_bo_simple_t*)(X))->size)

#define dpa__u_v_bo_simple_ro__get_size(X) ((X).size)
#define dpa__u_p_bo_simple_ro__get_size(X) ((X)->size)
#define dpa__u_cp_bo_simple_ro__get_size(X) ((X)->size)
#define dpa__u_any_bo_simple_ro__get_size(X) (((const dpa_u_bo_simple_ro_t*)(X))->size)

#define dpa__u_v_bo_hashed__get_size(X) ((X).bo_simple.size)
#define dpa__u_p_bo_hashed__get_size(X) ((X)->bo_simple.size)
#define dpa__u_cp_bo_hashed__get_size(X) ((X)->bo_simple.size)
#define dpa__u_any_bo_hashed__get_size(X) (((const dpa_u_bo_hashed_t*)(X))->bo_simple.size)

#define dpa__u_v_bo_hashed_ro__get_size(X) ((X).bo_simple.size)
#define dpa__u_p_bo_hashed_ro__get_size(X) ((X)->bo_simple.size)
#define dpa__u_cp_bo_hashed_ro__get_size(X) ((X)->bo_simple.size)
#define dpa__u_any_bo_hashed_ro__get_size(X) (((const dpa_u_bo_hashed_ro_t*)(X))->bo_simple.size)

#define dpa__u_v_bo_refcounted__get_size(X) ((X).bo_simple.size)
#define dpa__u_p_bo_refcounted__get_size(X) ((X)->bo_simple.size)
#define dpa__u_cp_bo_refcounted__get_size(X) ((X)->bo_simple.size)
#define dpa__u_any_bo_refcounted__get_size(X) (((const dpa_u_bo_refcounted_t*)(X))->bo_simple.size)

#define dpa__u_v_bo_refcounted_ro__get_size(X) ((X).bo_simple.size)
#define dpa__u_p_bo_refcounted_ro__get_size(X) ((X)->bo_simple.size)
#define dpa__u_cp_bo_refcounted_ro__get_size(X) ((X)->bo_simple.size)
#define dpa__u_any_bo_refcounted_ro__get_size(X) (((const dpa_u_bo_refcounted_ro_t*)(X))->bo_simple.size)

#define dpa__u_v_bo_refcounted_hashed_ro__get_size(X) ((X).bo_refcounted.bo_simple.size)
#define dpa__u_p_bo_refcounted_hashed_ro__get_size(X) ((X)->bo_refcounted.bo_simple.size)
#define dpa__u_cp_bo_refcounted_hashed_ro__get_size(X) ((X)->bo_refcounted.bo_simple.size)
#define dpa__u_any_bo_refcounted_hashed_ro__get_size(X) (((const dpa_u_bo_refcounted_hashed_ro_t*)(X))->bo_refcounted.bo_simple.size)

DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_bo_gc_ro__get_size(const dpa_u_bo_gc_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((dpa_u_bo_inline_ro_t*)bo)->size;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED:
    case DPA_U_BO_UNIQUE_HASHMAP: return ((const dpa_u_bo_simple_ro_t*)bo)->size;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_bo_with_hash_ro__get_size(const dpa_u_bo_with_hash_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((dpa_u_bo_inline_ro_t*)bo)->size;
    case DPA_U_BO_HASHED:
    case DPA_U_BO_REFCOUNTED_HASHED:
    case DPA_U_BO_UNIQUE_HASHMAP: return ((const dpa_u_bo_simple_ro_t*)bo)->size;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_bo_with_hash__get_size(const dpa_u_bo_with_hash_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((dpa_u_bo_inline_ro_t*)bo)->size;
    case DPA_U_BO_HASHED: return ((const dpa_u_bo_simple_ro_t*)bo)->size;
  }
  dpa_u_unreachable("dpa_u_bo_with_hash_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount_ro__get_size(X) (((const dpa_u_bo_simple_ro_t*)(X))->size)
#define dpa__u_bo_with_refcount__get_size(X) (((const dpa_u_bo_simple_ro_t*)(X))->size)
#define dpa__u_bo_with_refcount_and_hash_ro__get_size(X) (((const dpa_u_bo_simple_ro_t*)(X))->size)


DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_v_bo_unique__get_size(const dpa_u_bo_unique_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo.bo_unique_hashmap->base.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo_unique__get_size(X) dpa__u_v_bo_unique__get_size(*(X))
#define dpa__u_cp_bo_unique__get_size(X) dpa__u_v_bo_unique__get_size(*(X))
DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_any_bo_unique__get_size(const dpa_u_any_bo_unique_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->size;
    case DPA_U_BO_UNIQUE_HASHMAP: return ((dpa_u_bo_unique_hashmap_t)bo)->base.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_v_bo__get_size(const dpa_u_bo_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_SIMPLE: return bo.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo__get_size(X) dpa__u_v_bo__get_size(*(X))
#define dpa__u_cp_bo__get_size(X) dpa__u_v_bo__get_size(*(X))
DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_any_bo__get_size(const dpa_u_any_bo_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->size;
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->size;
  }
  dpa_u_unreachable("dpa_u_any_bo_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_v_bo_ro__get_size(const dpa_u_bo_ro_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_SIMPLE: return bo.bo_simple.size;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo.bo_unique_hashmap->base.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo_ro__get_size(X) dpa__u_v_bo_ro__get_size(*(X))
#define dpa__u_cp_bo_ro__get_size(X) dpa__u_v_bo_ro__get_size(*(X))
DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_any_bo_ro__get_size(const dpa_u_any_bo_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->size;
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->size;
    case DPA_U_BO_UNIQUE_HASHMAP: return ((dpa_u_bo_unique_hashmap_t)bo)->base.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_any_bo_ro_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

////

/**
 * Increments the refcount of the buffer. The refcount acts on the data of the buffer
 * rather than the buffer itself. For dpa_u_bo_inline_t, this is a noop, because
 * the buffer contains the data directly instead of referencing it, therefore, having
 * an instance of a dpa_u_bo_inline_t means having the data.
 */
#define dpa_u_bo_ref(...) dpa_u_assert_selection(dpa_u_bo_ref_g(__VA_ARGS__))
#define dpa_u_bo_ref_g(X) dpa_u_generic((X), \
          dpa_u_bo_inline_t : dpa__u_v_bo_inline__ref(DPA__G(dpa_u_bo_inline_t,(X))), \
          dpa_u_bo_inline_t*: dpa__u_p_bo_inline__ref(DPA__G(dpa_u_bo_inline_t*,(X))), \
    const dpa_u_bo_inline_t*: dpa__u_cp_bo_inline__ref(DPA__G(const dpa_u_bo_inline_t*,(X))), \
      dpa_u_any_bo_inline_t*: dpa__u_any_bo_inline__ref(DPA__G(dpa_u_any_bo_inline_t*,(X))), \
    \
          dpa_u_bo_unique_t : dpa__u_v_bo_unique__ref(DPA__G(dpa_u_bo_unique_t,(X))), \
          dpa_u_bo_unique_t*: dpa__u_p_bo_unique__ref(DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: dpa__u_cp_bo_unique__ref(DPA__G(const dpa_u_bo_unique_t*,(X))), \
      dpa_u_any_bo_unique_t*: dpa__u_any_bo_unique__ref(DPA__G(dpa_u_any_bo_unique_t*,(X))), \
    \
        dpa_u_bo_unique_hashmap_t : dpa__u_v_bo_unique_hashmap__ref(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__ref(DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    \
          dpa_u_bo_refcounted_t : dpa__u_v_bo_refcounted__ref(DPA__G(dpa_u_bo_refcounted_t,(X))), \
          dpa_u_bo_refcounted_t*: dpa__u_p_bo_refcounted__ref(DPA__G(dpa_u_bo_refcounted_t*,(X))), \
    const dpa_u_bo_refcounted_t*: dpa__u_cp_bo_refcounted__ref(DPA__G(const dpa_u_bo_refcounted_t*,(X))), \
      dpa_u_any_bo_refcounted_t*: dpa__u_any_bo_refcounted__ref(DPA__G(dpa_u_any_bo_refcounted_t*,(X))), \
    \
          dpa_u_bo_refcounted_ro_t : dpa__u_v_bo_refcounted_ro__ref(DPA__G(dpa_u_bo_refcounted_ro_t,(X))), \
          dpa_u_bo_refcounted_ro_t*: dpa__u_p_bo_refcounted_ro__ref(DPA__G(dpa_u_bo_refcounted_ro_t*,(X))), \
    const dpa_u_bo_refcounted_ro_t*: dpa__u_cp_bo_refcounted_ro__ref(DPA__G(const dpa_u_bo_refcounted_ro_t*,(X))), \
      dpa_u_any_bo_refcounted_ro_t*: dpa__u_any_bo_refcounted_ro__ref(DPA__G(dpa_u_any_bo_refcounted_ro_t*,(X))), \
    \
          dpa_u_bo_refcounted_hashed_ro_t : dpa__u_v_bo_refcounted_hashed_ro__ref(DPA__G(dpa_u_bo_refcounted_hashed_ro_t,(X))), \
          dpa_u_bo_refcounted_hashed_ro_t*: dpa__u_p_bo_refcounted_hashed_ro__ref(DPA__G(dpa_u_bo_refcounted_hashed_ro_t*,(X))), \
    const dpa_u_bo_refcounted_hashed_ro_t*: dpa__u_cp_bo_refcounted_hashed_ro__ref(DPA__G(const dpa_u_bo_refcounted_hashed_ro_t*,(X))), \
      dpa_u_any_bo_refcounted_hashed_ro_t*: dpa__u_any_bo_refcounted_hashed_ro__ref(DPA__G(dpa_u_any_bo_refcounted_hashed_ro_t*,(X))), \
    \
    dpa_u_bo_gc_ro_t*: dpa__u_bo_gc_ro__ref(DPA__G(dpa_u_bo_gc_ro_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount_ro__ref(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__ref(DPA__G(dpa_u_bo_with_refcount_t*,(X))), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__ref(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))) \
  )

#define dpa__u_v_bo_inline__ref(X)   (void)0
#define dpa__u_p_bo_inline__ref(X)   (void)0
#define dpa__u_cp_bo_inline__ref(X)  (void)0
#define dpa__u_any_bo_inline__ref(X) (void)0

#define dpa__u_v_bo_unique_hashmap__ref(X)   dpa_u_refcount_increment_p(&(X)->refcount.freeable.refcount)
#define dpa__u_p_bo_unique_hashmap__ref(X)   dpa_u_refcount_increment_p(&(X)->refcount.freeable.refcount)
#define dpa__u_cp_bo_unique_hashmap__ref(X)  dpa_u_refcount_increment_p(&(X)->refcount.freeable.refcount)
#define dpa__u_any_bo_unique_hashmap__ref(X) dpa_u_refcount_increment_p(&((dpa_u_bo_unique_hashmap_t)(X))->refcount.freeable.refcount)

DPA_U_EXPORT inline dpa__u_really_inline void dpa__u_v_bo_unique__ref(dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__ref(ubo.bo_unique_hashmap); return;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(ubo)));
}
#define dpa__u_p_bo_unique__ref(X)   dpa__u_v_bo_unique__ref(*(X))
#define dpa__u_cp_bo_unique__ref(X)  dpa__u_v_bo_unique__ref(*(X))
DPA_U_EXPORT inline dpa__u_really_inline void dpa__u_any_bo_unique__ref(dpa_u_any_bo_unique_t* ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__ref((dpa_u_bo_unique_hashmap_t)ubo); return;
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(ubo)));
}

#define dpa__u_v_bo_refcounted__ref(X)   dpa_u_refcount_increment_p(&(X).refcount->refcount)
#define dpa__u_p_bo_refcounted__ref(X)   dpa_u_refcount_increment_p(&(X)->refcount->refcount)
#define dpa__u_cp_bo_refcounted__ref(X)  dpa_u_refcount_increment_p(&(X)->refcount->refcount)
#define dpa__u_any_bo_refcounted__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_t*)(X))->refcount->refcount)

#define dpa__u_v_bo_refcounted_ro__ref(X)   dpa_u_refcount_increment_p(&(X).refcount->refcount)
#define dpa__u_p_bo_refcounted_ro__ref(X)   dpa_u_refcount_increment_p(&(X)->refcount->refcount)
#define dpa__u_cp_bo_refcounted_ro__ref(X)  dpa_u_refcount_increment_p(&(X)->refcount->refcount)
#define dpa__u_any_bo_refcounted_ro__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_ro_t*)(X))->refcount->refcount)

#define dpa__u_v_bo_refcounted_hashed_ro__ref(X)   dpa_u_refcount_increment_p(&(X).bo_refcounted.refcount->refcount)
#define dpa__u_p_bo_refcounted_hashed_ro__ref(X)   dpa_u_refcount_increment_p(&(X)->bo_refcounted.refcount->refcount)
#define dpa__u_cp_bo_refcounted_hashed_ro__ref(X)  dpa_u_refcount_increment_p(&(X)->bo_refcounted.refcount->refcount)
#define dpa__u_any_bo_refcounted_hashed_ro__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_hashed_ro_t*)(X))->bo_refcounted.refcount->refcount)

DPA_U_EXPORT inline dpa__u_really_inline void dpa__u_bo_gc_ro__ref(dpa_u_bo_gc_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__ref((dpa_u_bo_unique_hashmap_t)bo); return;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED: dpa_u_refcount_ref(((const dpa_u_bo_refcounted_ro_t*)bo)->refcount); return;
  }
  dpa_u_unreachable("dpa_u_bo_gc_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount_ro__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_ro_t*)(X))->refcount->refcount)
#define dpa__u_bo_with_refcount__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_ro_t*)(X))->refcount->refcount)
#define dpa__u_bo_with_refcount_and_hash_ro__ref(X) dpa_u_refcount_increment_p(&((const dpa_u_bo_refcounted_ro_t*)(X))->refcount->refcount)

////

#define dpa_u_bo_put(...) dpa_u_assert_selection(dpa_u_bo_put_g(__VA_ARGS__))
#define dpa_u_bo_put_g(X) dpa_u_generic((X), \
          dpa_u_bo_inline_t : dpa__u_v_bo_inline__put(DPA__G(dpa_u_bo_inline_t,(X))), \
          dpa_u_bo_inline_t*: dpa__u_p_bo_inline__put(DPA__G(dpa_u_bo_inline_t*,(X))), \
    const dpa_u_bo_inline_t*: dpa__u_cp_bo_inline__put(DPA__G(const dpa_u_bo_inline_t*,(X))), \
      dpa_u_any_bo_inline_t*: dpa__u_any_bo_inline__put(DPA__G(dpa_u_any_bo_inline_t*,(X))), \
    \
          dpa_u_bo_unique_t : dpa__u_v_bo_unique__put(DPA__G(dpa_u_bo_unique_t,(X))), \
          dpa_u_bo_unique_t*: dpa__u_p_bo_unique__put(DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: dpa__u_cp_bo_unique__put(DPA__G(const dpa_u_bo_unique_t*,(X))), \
      dpa_u_any_bo_unique_t*: dpa__u_any_bo_unique__put(DPA__G(dpa_u_any_bo_unique_t*,(X))), \
    \
        dpa_u_bo_unique_hashmap_t : dpa__u_v_bo_unique_hashmap__put(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__put(DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    \
          dpa_u_bo_refcounted_t : dpa__u_v_bo_refcounted__put(DPA__G(dpa_u_bo_refcounted_t,(X))), \
          dpa_u_bo_refcounted_t*: dpa__u_p_bo_refcounted__put(DPA__G(dpa_u_bo_refcounted_t*,(X))), \
    const dpa_u_bo_refcounted_t*: dpa__u_cp_bo_refcounted__put(DPA__G(const dpa_u_bo_refcounted_t*,(X))), \
      dpa_u_any_bo_refcounted_t*: dpa__u_any_bo_refcounted__put(DPA__G(dpa_u_any_bo_refcounted_t*,(X))), \
    \
          dpa_u_bo_refcounted_ro_t : dpa__u_v_bo_refcounted_ro__put(DPA__G(dpa_u_bo_refcounted_ro_t,(X))), \
          dpa_u_bo_refcounted_ro_t*: dpa__u_p_bo_refcounted_ro__put(DPA__G(dpa_u_bo_refcounted_ro_t*,(X))), \
    const dpa_u_bo_refcounted_ro_t*: dpa__u_cp_bo_refcounted_ro__put(DPA__G(const dpa_u_bo_refcounted_ro_t*,(X))), \
      dpa_u_any_bo_refcounted_ro_t*: dpa__u_any_bo_refcounted_ro__put(DPA__G(dpa_u_any_bo_refcounted_ro_t*,(X))), \
    \
          dpa_u_bo_refcounted_hashed_ro_t : dpa__u_v_bo_refcounted_hashed_ro__put(DPA__G(dpa_u_bo_refcounted_hashed_ro_t,(X))), \
          dpa_u_bo_refcounted_hashed_ro_t*: dpa__u_p_bo_refcounted_hashed_ro__put(DPA__G(dpa_u_bo_refcounted_hashed_ro_t*,(X))), \
    const dpa_u_bo_refcounted_hashed_ro_t*: dpa__u_cp_bo_refcounted_hashed_ro__put(DPA__G(const dpa_u_bo_refcounted_hashed_ro_t*,(X))), \
      dpa_u_any_bo_refcounted_hashed_ro_t*: dpa__u_any_bo_refcounted_hashed_ro__put(DPA__G(dpa_u_any_bo_refcounted_hashed_ro_t*,(X))), \
    \
    dpa_u_bo_gc_ro_t*: dpa__u_bo_gc_ro__put(DPA__G(dpa_u_bo_gc_ro_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount_ro__put(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__put(DPA__G(dpa_u_bo_with_refcount_t*,(X))), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__put(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))) \
  )

#define dpa__u_v_bo_inline__put(X)   (void)0
#define dpa__u_p_bo_inline__put(X)   (void)0
#define dpa__u_cp_bo_inline__put(X)  (void)0
#define dpa__u_any_bo_inline__put(X) (void)0

#define dpa__u_v_bo_unique_hashmap__put(X)   dpa_u_refcount_put_p(&(X)->refcount.freeable)
#define dpa__u_p_bo_unique_hashmap__put(X)   dpa_u_refcount_put_p(&(X)->refcount.freeable)
#define dpa__u_cp_bo_unique_hashmap__put(X)  dpa_u_refcount_put_p(&(X)->refcount.freeable)
#define dpa__u_any_bo_unique_hashmap__put(X) dpa_u_refcount_put_p(&((dpa_u_bo_unique_hashmap_t)(X))->refcount.freeable)

DPA_U_EXPORT inline dpa__u_really_inline void dpa__u_v_bo_unique__put(dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__put(ubo.bo_unique_hashmap); return;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(ubo)));
}
#define dpa__u_p_bo_unique__put(X)   dpa__u_v_bo_unique__put(*(X))
#define dpa__u_cp_bo_unique__put(X)  dpa__u_v_bo_unique__put(*(X))
DPA_U_EXPORT inline dpa__u_really_inline void dpa__u_any_bo_unique__put(dpa_u_any_bo_unique_t* ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__put((dpa_u_bo_unique_hashmap_t)ubo); return;
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(ubo)));
}

#define dpa__u_v_bo_refcounted__put(X)   dpa_u_refcount_put_p((X).refcount)
#define dpa__u_p_bo_refcounted__put(X)   dpa_u_refcount_put_p((X)->refcount)
#define dpa__u_cp_bo_refcounted__put(X)  dpa_u_refcount_put_p((X)->refcount)
#define dpa__u_any_bo_refcounted__put(X) dpa_u_refcount_put_p(((const dpa_u_bo_refcounted_t*)(X))->refcount)

#define dpa__u_v_bo_refcounted_ro__put(X)   dpa_u_refcount_put_p((X).refcount)
#define dpa__u_p_bo_refcounted_ro__put(X)   dpa_u_refcount_put_p((X)->refcount)
#define dpa__u_cp_bo_refcounted_ro__put(X)  dpa_u_refcount_put_p((X)->refcount)
#define dpa__u_any_bo_refcounted_ro__put(X) dpa_u_refcount_put_p(((const dpa_u_bo_refcounted_ro_t*)(X))->refcount)

#define dpa__u_v_bo_refcounted_hashed_ro__put(X)   dpa_u_refcount_put_p((X).bo_refcounted.refcount)
#define dpa__u_p_bo_refcounted_hashed_ro__put(X)   dpa_u_refcount_put_p((X)->bo_refcounted.refcount)
#define dpa__u_cp_bo_refcounted_hashed_ro__put(X)  dpa_u_refcount_put_p((X)->bo_refcounted.refcount)
#define dpa__u_any_bo_refcounted_hashed_ro__put(X) dpa_u_refcount_put_p(((const dpa_u_bo_refcounted_hashed_ro_t*)(X))->bo_refcounted.refcount)

DPA_U_EXPORT inline dpa__u_really_inline void dpa__u_bo_gc_ro__put(dpa_u_bo_gc_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return;
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_cp_bo_unique_hashmap__put((dpa_u_bo_unique_hashmap_t)bo); return;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED: dpa_u_refcount_put(((const dpa_u_bo_refcounted_ro_t*)bo)->refcount); return;
  }
  dpa_u_unreachable("dpa_u_bo_gc_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_bo_with_refcount_ro__put(X) dpa_u_refcount_put_p(((const dpa_u_bo_refcounted_ro_t*)(X))->refcount)
#define dpa__u_bo_with_refcount__put(X) dpa_u_refcount_put_p(((const dpa_u_bo_refcounted_ro_t*)(X))->refcount)
#define dpa__u_bo_with_refcount_and_hash_ro__put(X) dpa_u_refcount_put_p(((const dpa_u_bo_refcounted_ro_t*)(X))->refcount)

////

#define dpa_u_bo_get_refcount(...) dpa_u_assert_selection(dpa_u_bo_get_refcount_g(__VA_ARGS__))
#define dpa_u_bo_get_refcount_g(X) dpa_u_generic((X), \
          dpa_u_bo_ro_t : dpa__u_v_bo_ro__get_refcount(DPA__G(dpa_u_bo_ro_t,(X))), \
          dpa_u_bo_ro_t*: dpa__u_p_bo_ro__get_refcount(DPA__G(dpa_u_bo_ro_t*,(X))), \
    const dpa_u_bo_ro_t*: dpa__u_cp_bo_ro__get_refcount(DPA__G(const dpa_u_bo_ro_t*,(X))), \
      dpa_u_any_bo_ro_t*: dpa__u_any_bo_ro__get_refcount(DPA__G(dpa_u_any_bo_ro_t*,(X))), \
    \
          dpa_u_bo_unique_t : dpa__u_v_bo_unique__get_refcount(DPA__G(dpa_u_bo_unique_t,(X))), \
          dpa_u_bo_unique_t*: dpa__u_p_bo_unique__get_refcount(DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: dpa__u_cp_bo_unique__get_refcount(DPA__G(const dpa_u_bo_unique_t*,(X))), \
      dpa_u_any_bo_unique_t*: dpa__u_any_bo_unique__get_refcount(DPA__G(dpa_u_any_bo_unique_t*,(X))), \
    \
        dpa_u_bo_unique_hashmap_t : dpa__u_v_bo_unique_hashmap__get_refcount(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap__get_refcount(DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    \
          dpa_u_bo_refcounted_t : dpa__u_v_bo_refcounted__get_refcount(DPA__G(dpa_u_bo_refcounted_t,(X))), \
          dpa_u_bo_refcounted_t*: dpa__u_p_bo_refcounted__get_refcount(DPA__G(dpa_u_bo_refcounted_t*,(X))), \
    const dpa_u_bo_refcounted_t*: dpa__u_cp_bo_refcounted__get_refcount(DPA__G(const dpa_u_bo_refcounted_t*,(X))), \
      dpa_u_any_bo_refcounted_t*: dpa__u_any_bo_refcounted__get_refcount(DPA__G(dpa_u_any_bo_refcounted_t*,(X))), \
    \
          dpa_u_bo_refcounted_ro_t : dpa__u_v_bo_refcounted_ro__get_refcount(DPA__G(dpa_u_bo_refcounted_ro_t,(X))), \
          dpa_u_bo_refcounted_ro_t*: dpa__u_p_bo_refcounted_ro__get_refcount(DPA__G(dpa_u_bo_refcounted_ro_t*,(X))), \
    const dpa_u_bo_refcounted_ro_t*: dpa__u_cp_bo_refcounted_ro__get_refcount(DPA__G(const dpa_u_bo_refcounted_ro_t*,(X))), \
      dpa_u_any_bo_refcounted_ro_t*: dpa__u_any_bo_refcounted_ro__get_refcount(DPA__G(dpa_u_any_bo_refcounted_ro_t*,(X))), \
    \
          dpa_u_bo_refcounted_hashed_ro_t : dpa__u_v_bo_refcounted_hashed_ro__get_refcount(DPA__G(dpa_u_bo_refcounted_hashed_ro_t,(X))), \
          dpa_u_bo_refcounted_hashed_ro_t*: dpa__u_p_bo_refcounted_hashed_ro__get_refcount(DPA__G(dpa_u_bo_refcounted_hashed_ro_t*,(X))), \
    const dpa_u_bo_refcounted_hashed_ro_t*: dpa__u_cp_bo_refcounted_hashed_ro__get_refcount(DPA__G(const dpa_u_bo_refcounted_hashed_ro_t*,(X))), \
      dpa_u_any_bo_refcounted_hashed_ro_t*: dpa__u_any_bo_refcounted_hashed_ro__get_refcount(DPA__G(dpa_u_any_bo_refcounted_hashed_ro_t*,(X))), \
    \
    dpa_u_bo_gc_ro_t*: dpa__u_bo_gc_ro__get_refcount(DPA__G(dpa_u_bo_gc_ro_t*,(X))), \
    dpa_u_bo_with_refcount_ro_t*: dpa__u_bo_with_refcount_ro__get_refcount(DPA__G(dpa_u_bo_with_refcount_ro_t*,(X))), \
    dpa_u_bo_with_refcount_t*: dpa__u_bo_with_refcount__get_refcount(DPA__G(dpa_u_bo_with_refcount_t*,(X))), \
    dpa_u_bo_with_refcount_and_hash_ro_t*: dpa__u_bo_with_refcount_and_hash_ro__get_refcount(DPA__G(dpa_u_bo_with_refcount_and_hash_ro_t*,(X))) \
  )

#define dpa__u_bo_with_refcount__get_refcount(X) dpa__u_cp_bo_refcounted__get_refcount((const dpa_u_bo_refcounted_t*)(X))
DPA_U_EXPORT inline dpa__u_really_inline dpa_u_refcount_freeable_t* dpa__u_bo_gc_ro__get_refcount(const dpa_u_bo_gc_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return 0;
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_unique_hashmap_t)bo)->refcount.freeable;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_refcounted_ro_t*)bo)->refcount;
  }
  dpa_u_unreachable("dpa_u_bo_gc_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline dpa_u_refcount_freeable_t* dpa__u_bo_with_refcount_ro__get_refcount(const dpa_u_bo_with_refcount_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_unique_hashmap_t)bo)->refcount.freeable;
    case DPA_U_BO_REFCOUNTED:
    case DPA_U_BO_REFCOUNTED_HASHED: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_refcounted_ro_t*)bo)->refcount;
  }
  dpa_u_unreachable("dpa_u_bo_with_refcount_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline dpa_u_refcount_freeable_t* dpa__u_bo_with_refcount_and_hash_ro__get_refcount(const dpa_u_bo_with_refcount_and_hash_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_unique_hashmap_t)bo)->refcount.freeable;
    case DPA_U_BO_REFCOUNTED_HASHED: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_refcounted_ro_t*)bo)->refcount;
  }
  dpa_u_unreachable("dpa_u_bo_with_refcount_and_hash_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline dpa_u_refcount_freeable_t* dpa__u_v_bo_unique__get_refcount(const dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_INLINE: return 0;
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&ubo.bo_unique_hashmap->refcount.freeable;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(ubo)));
}
#define dpa__u_p_bo_unique__get_refcount(X) dpa__u_v_bo_unique__get_refcount(*(X))
#define dpa__u_cp_bo_unique__get_refcount(X) dpa__u_v_bo_unique__get_refcount(*(X))
#define dpa__u_any_bo_unique__get_refcount(X) dpa__u_v_bo_unique__get_refcount(*(const dpa_u_bo_unique_t*)(X))

DPA_U_EXPORT inline dpa__u_really_inline dpa_u_refcount_freeable_t* dpa__u_v_bo_ro__get_refcount(const dpa_u_bo_ro_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
    case DPA_U_BO_SIMPLE: return 0;
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&bo.bo_unique_hashmap->refcount.freeable;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo_ro__get_refcount(X) dpa__u_cp_bo_ro__get_refcount(X)
DPA_U_EXPORT inline dpa__u_really_inline dpa_u_refcount_freeable_t* dpa__u_cp_bo_ro__get_refcount(const dpa_u_bo_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
    case DPA_U_BO_SIMPLE: return 0;
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&bo->bo_unique_hashmap->refcount.freeable;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline dpa_u_refcount_freeable_t* dpa__u_any_bo_ro__get_refcount(dpa_u_any_bo_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
    case DPA_U_BO_SIMPLE: return 0;
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&((dpa_u_bo_unique_hashmap_t)bo)->refcount.freeable;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_unique_hashmap__get_refcount(X) ((dpa_u_refcount_freeable_t*)&(X)->refcount.freeable)
#define dpa__u_p_bo_unique_hashmap__get_refcount(X) ((dpa_u_refcount_freeable_t*)&((X))->refcount.freeable)
#define dpa__u_cp_bo_unique_hashmap__get_refcount(X) ((dpa_u_refcount_freeable_t*)&((X))->refcount.freeable)
#define dpa__u_any_bo_unique_hashmap__get_refcount(X) ((dpa_u_refcount_freeable_t*)&((dpa_u_bo_unique_hashmap_t)(X))->refcount.freeable)

#define dpa__u_v_bo_refcounted__get_refcount(X) ((X).refcount)
#define dpa__u_p_bo_refcounted__get_refcount(X) ((X)->refcount)
#define dpa__u_cp_bo_refcounted__get_refcount(X) ((dpa_u_refcount_freeable_t*)((X)->refcount))
#define dpa__u_any_bo_refcounted__get_refcount(X) ((dpa_u_refcount_freeable_t*)(((const dpa_u_bo_refcounted_t*)(X))->refcount))

#define dpa__u_v_bo_refcounted_ro__get_refcount(X) ((X).refcount)
#define dpa__u_p_bo_refcounted_ro__get_refcount(X) ((X)->refcount)
#define dpa__u_cp_bo_refcounted_ro__get_refcount(X) ((dpa_u_refcount_freeable_t*)((X)->refcount))
#define dpa__u_any_bo_refcounted_ro__get_refcount(X) ((dpa_u_refcount_freeable_t*)(((const dpa_u_bo_refcounted_ro_t*)(X))->refcount))

#define dpa__u_v_bo_refcounted_hashed_ro__get_refcount(X) ((X).bo_refcounted.refcount)
#define dpa__u_p_bo_refcounted_hashed_ro__get_refcount(X) ((X)->bo_refcounted.refcount)
#define dpa__u_cp_bo_refcounted_hashed_ro__get_refcount(X) ((dpa_u_refcount_freeable_t*)((X)->bo_refcounted.refcount))
#define dpa__u_any_bo_refcounted_hashed_ro__get_refcount(X) ((dpa_u_refcount_freeable_t*)(((const dpa_u_bo_refcounted_hashed_ro_t*)(X))->bo_refcounted.refcount))

/////////////////////////////////////////
//////      Conversion macros      //////
/////////////////////////////////////////

#define dpa_u_v_bo_unique(...) dpa_u_assert_selection(dpa_u_v_bo_unique_g(__VA_ARGS__))
#define dpa_u_v_bo_unique_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: (const dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = DPA__G(dpa_u_bo_unique_hashmap_t, (X)) }, \
    dpa_u_any_bo_unique_hashmap_t*: (const dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*, (X)) }, \
    DPA__GS(dpa_u_bo_unique_t, (X)), \
    dpa_u_bo_inline_t*: (const dpa_u_bo_unique_t){ .bo_inline = *DPA__G(dpa_u_bo_inline_t*, (X)) }, \
    const dpa_u_bo_inline_t*: (const dpa_u_bo_unique_t){ .bo_inline = *DPA__G(const dpa_u_bo_inline_t*, (X)) }, \
      dpa_u_any_bo_inline_t*: (const dpa_u_bo_unique_t){ .bo_inline = *(dpa_u_bo_inline_t*)DPA__G(dpa_u_any_bo_inline_t*, (X)) }, \
    DPA__GS(dpa_u_bo_unique_t*, (X))[0], \
    DPA__GS(const dpa_u_bo_unique_t*, (X))[0], \
    dpa_u_any_bo_unique_t*: *(const dpa_u_bo_unique_t*)DPA__G(dpa_u_any_bo_unique_t*, (X)) \
  )

/**
 * Note: If the source buffer was a DPA_U_BO_INLINE (which can also be the case for dpa_u_bo_t too),
 * then the lifetime will not exceed the source BOs scope! It's fine for passing to other functions,
 * but not for much else.
 */
#define dpa_u_temp_bo_simple(...) dpa_u_assert_selection(dpa_u_temp_bo_simple_g(__VA_ARGS__))
#define dpa_u_temp_bo_simple_g(X) dpa_u_generic((X), \
    DPA__GS(dpa_u_bo_simple_t, (X)), \
    dpa_u_bo_inline_t: (const dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_inline_t,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_inline_t,(X))) }, \
    dpa_u_bo_t: (const dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_t,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_t,(X))) }, \
    \
    DPA__GS(dpa_u_bo_simple_t*, (X))[0], \
    DPA__GS(const dpa_u_bo_simple_t*, (X))[0], \
    dpa_u_bo_inline_t*: (const dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_inline_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_inline_t*,(X))) }, \
    dpa_u_bo_t*: (const dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_t*,(X))) }, \
    const dpa_u_bo_t*: (const dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(const dpa_u_bo_t*,(X))), .data=dpa_u_bo_data(DPA__G(const dpa_u_bo_t*,(X))) } \
  )

/**
 * Note: If the source buffer was a DPA_U_BO_INLINE (which can also be the case for dpa_u_bo_t and dpa_u_bo_ro_t too),
 * then the lifetime of the data will not exceed the current blocks scope! If you pass in a pointer, it'll at least match the source BOs lifetime.
 * This is fine for passing to other functions, but not for much else. Don't try to return such a pointer.
 */
#define dpa_u_temp_bo_simple_ro(...) dpa_u_assert_selection(dpa_u_temp_bo_simple_ro_g(__VA_ARGS__))
#define dpa_u_temp_bo_simple_ro_g(X) dpa_u_generic((X),dpa__u_helper_all_g(temp_bo_simple_ro,(X)))

#define dpa__u_temp_bo_simple_ro__helper(P,X) (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa__u_ ## P ## __get_size((X)), .data=dpa__u_ ## P ## __data((X)) }

#define dpa__u_v_bo_unique_hashmap__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(v_bo_unique_hashmap,(X))
#define dpa__u_p_bo_unique_hashmap__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(p_bo_unique_hashmap,(X))
#define dpa__u_cp_bo_unique_hashmap__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(cp_bo_unique_hashmap,(X))
#define dpa__u_any_bo_unique_hashmap__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(any_bo_unique_hashmap,(X))

#define dpa__u_v_bo_inline__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(v_bo_inline,(X))
#define dpa__u_p_bo_inline__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(p_bo_inline,(X))
#define dpa__u_cp_bo_inline__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(cp_bo_inline,(X))
#define dpa__u_any_bo_inline__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(any_bo_inline,(X))

#define dpa__u_v_bo_simple__temp_bo_simple_ro(X) (X).ro
#define dpa__u_p_bo_simple__temp_bo_simple_ro(X) (X)->ro
#define dpa__u_cp_bo_simple__temp_bo_simple_ro(X) (X)->ro
#define dpa__u_any_bo_simple__temp_bo_simple_ro(X) ((const dpa_u_bo_simple_t*)(X))->ro

#define dpa__u_v_bo_simple_ro__temp_bo_simple_ro(X) (X)
#define dpa__u_p_bo_simple_ro__temp_bo_simple_ro(X) (*(X))
#define dpa__u_cp_bo_simple_ro__temp_bo_simple_ro(X) (*(X))
#define dpa__u_any_bo_simple_ro__temp_bo_simple_ro(X) (*(const dpa_u_bo_simple_ro_t*)(X))

#define dpa__u_v_bo_hashed__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(v_bo_hashed,(X))
#define dpa__u_p_bo_hashed__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(p_bo_hashed,(X))
#define dpa__u_cp_bo_hashed__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(cp_bo_hashed,(X))
#define dpa__u_any_bo_hashed__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(any_bo_hashed,(X))

#define dpa__u_v_bo_hashed_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(v_bo_hashed_ro,(X))
#define dpa__u_p_bo_hashed_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(p_bo_hashed_ro,(X))
#define dpa__u_cp_bo_hashed_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(cp_bo_hashed_ro,(X))
#define dpa__u_any_bo_hashed_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(any_bo_hashed_ro,(X))

#define dpa__u_v_bo_refcounted__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(v_bo_refcounted,(X))
#define dpa__u_p_bo_refcounted__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(p_bo_refcounted,(X))
#define dpa__u_cp_bo_refcounted__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(cp_bo_refcounted,(X))
#define dpa__u_any_bo_refcounted__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(any_bo_refcounted,(X))

#define dpa__u_v_bo_refcounted_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(v_bo_refcounted_ro,(X))
#define dpa__u_p_bo_refcounted_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(p_bo_refcounted_ro,(X))
#define dpa__u_cp_bo_refcounted_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(cp_bo_refcounted_ro,(X))
#define dpa__u_any_bo_refcounted_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(any_bo_refcounted_ro,(X))

#define dpa__u_v_bo_refcounted_hashed_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(v_bo_refcounted_hashed_ro,(X))
#define dpa__u_p_bo_refcounted_hashed_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(p_bo_refcounted_hashed_ro,(X))
#define dpa__u_cp_bo_refcounted_hashed_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(cp_bo_refcounted_hashed_ro,(X))
#define dpa__u_any_bo_refcounted_hashed_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(any_bo_refcounted_hashed_ro,(X))

#define dpa__u_v_bo_unique__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(v_bo_unique,(X))
#define dpa__u_p_bo_unique__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(p_bo_unique,(X))
#define dpa__u_cp_bo_unique__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(cp_bo_unique,(X))
#define dpa__u_any_bo_unique__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(any_bo_unique,(X))

#define dpa__u_v_bo__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(v_bo,(X))
#define dpa__u_p_bo__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(p_bo,(X))
#define dpa__u_cp_bo__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(cp_bo,(X))
#define dpa__u_any_bo__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(any_bo,(X))

#define dpa__u_v_bo_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(v_bo_ro,(X))
#define dpa__u_p_bo_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(p_bo_ro,(X))
#define dpa__u_cp_bo_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(cp_bo_ro,(X))
#define dpa__u_any_bo_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(any_bo_ro,(X))

#define dpa__u_bo_gc_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(bo_gc_ro,(X))
#define dpa__u_bo_with_hash_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(bo_with_hash_ro,(X))
#define dpa__u_bo_with_hash__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(bo_with_hash,(X))
#define dpa__u_bo_with_refcount_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(bo_with_refcount_ro,(X))
#define dpa__u_bo_with_refcount__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(bo_with_refcount,(X))
#define dpa__u_bo_with_refcount_and_hash_ro__temp_bo_simple_ro(X) dpa__u_temp_bo_simple_ro__helper(bo_with_refcount_and_hash_ro,(X))

////

#define dpa_u_v_bo_ro(...) dpa_u_assert_selection(dpa_u_v_bo_ro_g(__VA_ARGS__))
#define dpa_u_v_bo_ro_g(X) dpa_u_generic((X), \
    DPA__GS(dpa_u_bo_t, (X)).ro, \
    DPA__GS(dpa_u_bo_ro_t, (X)), \
    dpa_u_bo_inline_t: (const dpa_u_bo_ro_t){ .bo_inline = DPA__G(dpa_u_bo_inline_t, (X)) }, \
    dpa_u_bo_simple_t: (const dpa_u_bo_ro_t){ .bo_simple = DPA__G(dpa_u_bo_simple_t, (X)).ro }, \
    dpa_u_bo_simple_ro_t: (const dpa_u_bo_ro_t){ .bo_simple = DPA__G(dpa_u_bo_simple_ro_t, (X)) }, \
    dpa_u_bo_unique_hashmap_t: (const dpa_u_bo_ro_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = DPA__G(dpa_u_bo_unique_hashmap_t, (X)) }, \
    dpa_u_bo_unique_t: (const dpa_u_bo_ro_t){ .bo_unique = DPA__G(dpa_u_bo_unique_t, (X)) }, \
    \
    DPA__GS(dpa_u_bo_t*, (X))->ro, \
    DPA__GS(const dpa_u_bo_t*, (X))->ro, \
    DPA__GS(dpa_u_bo_ro_t*, (X))[0], \
    DPA__GS(const dpa_u_bo_ro_t*, (X))[0], \
    dpa_u_bo_inline_t*: (const dpa_u_bo_ro_t){ .bo_inline = *DPA__G(dpa_u_bo_inline_t*, (X)) }, \
    const dpa_u_bo_inline_t*: (const dpa_u_bo_ro_t){ .bo_inline = *DPA__G(const dpa_u_bo_inline_t*, (X)) }, \
    dpa_u_any_bo_inline_t*: (const dpa_u_bo_ro_t){ .bo_inline = *(const dpa_u_bo_inline_t*)DPA__G(dpa_u_any_bo_inline_t*, (X)) }, \
    dpa_u_bo_simple_t*: (const dpa_u_bo_ro_t){ .bo_simple = DPA__G(dpa_u_bo_simple_t*, (X))->ro }, \
    const dpa_u_bo_simple_t*: (const dpa_u_bo_ro_t){ .bo_simple = DPA__G(const dpa_u_bo_simple_t*, (X))->ro }, \
    dpa_u_bo_simple_ro_t*: (const dpa_u_bo_ro_t){ .bo_simple = *DPA__G(dpa_u_bo_simple_ro_t*, (X)) }, \
    const dpa_u_bo_simple_ro_t*: (const dpa_u_bo_ro_t){ .bo_simple = *DPA__G(const dpa_u_bo_simple_ro_t*, (X)) }, \
    dpa_u_bo_unique_t*: (const dpa_u_bo_ro_t){ .bo_unique = *DPA__G(dpa_u_bo_unique_t*, (X)) }, \
    const dpa_u_bo_unique_t*: (const dpa_u_bo_ro_t){ .bo_unique = *DPA__G(const dpa_u_bo_unique_t*, (X)) }, \
    dpa_u_any_bo_unique_t*: (const dpa_u_bo_ro_t){ .bo_unique = *(const dpa_u_bo_unique_t*)DPA__G(dpa_u_any_bo_unique_t*, (X)) } \
  )

////

#define dpa_u_bo_ptr(...) dpa_u_assert_selection(dpa_u_bo_ptr_g(__VA_ARGS__))
#define dpa_u_bo_ptr_g(X) dpa_u_generic((X),dpa__u_helper_all_g(ptr,(X)))

#define dpa__u_any_bo_inline__ptr(X) (X)
#define dpa__u_any_bo_unique_hashmap__ptr(X) (X)
#define dpa__u_any_bo_unique__ptr(X) (X)
#define dpa__u_any_bo_simple__ptr(X) (X)
#define dpa__u_any_bo_simple_ro__ptr(X) (X)
#define dpa__u_any_bo__ptr(X) (X)
#define dpa__u_any_bo_ro__ptr(X) (X)
#define dpa__u_any_bo_hashed_ro__ptr(X) (X)
#define dpa__u_any_bo_hashed__ptr(X) (X)
#define dpa__u_any_bo_refcounted_ro__ptr(X) (X)
#define dpa__u_any_bo_refcounted__ptr(X) (X)
#define dpa__u_any_bo_refcounted_hashed_ro__ptr(X) (X)
#define dpa__u_any_bo_refcounted_hashed__ptr(X) (X)

#define dpa__u_bo_with_hash_ro__ptr(X) (X)
#define dpa__u_bo_with_hash__ptr(X) (X)
#define dpa__u_bo_with_refcount_ro__ptr(X) (X)
#define dpa__u_bo_with_refcount__ptr(X) (X)
#define dpa__u_bo_with_refcount_and_hash_ro__ptr(X) (X)
#define dpa__u_bo_gc_ro__ptr(X) (X)

#define dpa__u_v_bo_inline__ptr(X) (dpa_u_any_bo_inline_t*)&(X)
#define dpa__u_v_bo_unique_hashmap__ptr(X) (dpa_u_any_bo_unique_hashmap_t*)(X)
#define dpa__u_v_bo_unique__ptr(X) (dpa_u_any_bo_unique_t*)&(X)
#define dpa__u_v_bo_simple__ptr(X) (dpa_u_any_bo_simple_t*)&(X)
#define dpa__u_v_bo_simple_ro__ptr(X) (dpa_u_any_bo_simple_ro_t*)&(X)
#define dpa__u_v_bo__ptr(X) (dpa_u_any_bo_t*)&(X)
#define dpa__u_v_bo_ro__ptr(X) (dpa_u_any_bo_ro_t*)&(X)
#define dpa__u_v_bo_hashed_ro__ptr(X) (dpa_u_any_bo_hashed_ro_t*)&(X)
#define dpa__u_v_bo_hashed__ptr(X) (dpa_u_any_bo_hashed_t*)&(X)
#define dpa__u_v_bo_refcounted_ro__ptr(X) (dpa_u_any_bo_refcounted_ro_t*)&(X)
#define dpa__u_v_bo_refcounted__ptr(X) (dpa_u_any_bo_refcounted_t*)&(X)
#define dpa__u_v_bo_refcounted_hashed_ro__ptr(X) (dpa_u_any_bo_refcounted_hashed_ro_t*)&(X)
#define dpa__u_v_bo_refcounted_hashed__ptr(X) (dpa_u_any_bo_refcounted_hashed_t*)&(X)

#define dpa__u_p_bo_inline__ptr(X) (dpa_u_any_bo_inline_t*)(X)
#define dpa__u_p_bo_unique__ptr(X) (dpa_u_any_bo_unique_t*)(X)
#define dpa__u_p_bo_simple__ptr(X) (dpa_u_any_bo_simple_t*)(X)
#define dpa__u_p_bo_simple_ro__ptr(X) (dpa_u_any_bo_simple_ro_t*)(X)
#define dpa__u_p_bo__ptr(X) (dpa_u_any_bo_t*)(X)
#define dpa__u_p_bo_ro__ptr(X) (dpa_u_any_bo_ro_t*)(X)
#define dpa__u_p_bo_hashed_ro__ptr(X) (dpa_u_any_bo_hashed_ro_t*)(X)
#define dpa__u_p_bo_hashed__ptr(X) (dpa_u_any_bo_hashed_t*)(X)
#define dpa__u_p_bo_refcounted_ro__ptr(X) (dpa_u_any_bo_refcounted_ro_t*)(X)
#define dpa__u_p_bo_refcounted__ptr(X) (dpa_u_any_bo_refcounted_t*)(X)
#define dpa__u_p_bo_refcounted_hashed_ro__ptr(X) (dpa_u_any_bo_refcounted_hashed_ro_t*)(X)
#define dpa__u_p_bo_refcounted_hashed__ptr(X) (dpa_u_any_bo_refcounted_hashed_t*)(X)

#define dpa__u_cp_bo_inline__ptr(X) (dpa_u_any_bo_inline_t*)(X)
#define dpa__u_cp_bo_unique__ptr(X) (dpa_u_any_bo_unique_t*)(X)
#define dpa__u_cp_bo_simple__ptr(X) (dpa_u_any_bo_simple_t*)(X)
#define dpa__u_cp_bo_simple_ro__ptr(X) (dpa_u_any_bo_simple_ro_t*)(X)
#define dpa__u_cp_bo__ptr(X) (dpa_u_any_bo_t*)(X)
#define dpa__u_cp_bo_ro__ptr(X) (dpa_u_any_bo_ro_t*)(X)
#define dpa__u_cp_bo_hashed_ro__ptr(X) (dpa_u_any_bo_hashed_ro_t*)(X)
#define dpa__u_cp_bo_hashed__ptr(X) (dpa_u_any_bo_hashed_t*)(X)
#define dpa__u_cp_bo_refcounted_ro__ptr(X) (dpa_u_any_bo_refcounted_ro_t*)(X)
#define dpa__u_cp_bo_refcounted__ptr(X) (dpa_u_any_bo_refcounted_t*)(X)
#define dpa__u_cp_bo_refcounted_hashed_ro__ptr(X) (dpa_u_any_bo_refcounted_hashed_ro_t*)(X)
#define dpa__u_cp_bo_refcounted_hashed__ptr(X) (dpa_u_any_bo_refcounted_hashed_t*)(X)

////

DPA_U_EXPORT inline dpa_u_bo_unique_t dpa__u_bo_intern(dpa_u_any_bo_ro_t*const bo){
  // We allow the simple cases to be inlined, and the complicated one is handled in dpa__u_bo_do_intern instead
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (dpa_u_bo_unique_t){ .bo_inline = *(dpa_u_bo_inline_t*)bo };
    case DPA_U_BO_UNIQUE_HASHMAP: {
      dpa_u_bo_unique_hashmap_t ubo = (dpa_u_bo_unique_hashmap_t)bo;
#if defined(__GNUC__) && !defined(__llvm__)
// GCC will get confused about which branchs are reachable and warn. All we can do about it is disable the warning.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#endif
      dpa_u_bo_ref(ubo);
#if defined(__GNUC__) && !defined(__llvm__)
#pragma GCC diagnostic pop
#endif
      return (dpa_u_bo_unique_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = ubo,
      };
    }
    default: {
      if(dpa_u_bo_get_size(bo) <= DPA_U_BO_INLINE_MAX_SIZE){
        dpa_u_bo_inline_t boi = {
          .type = DPA_U_BO_INLINE,
          .size = dpa_u_bo_get_size(bo),
        };
        memcpy(boi.data, dpa_u_bo_data(bo), dpa_u_bo_get_size(bo));
        return (dpa_u_bo_unique_t){ .bo_inline = boi };
      }
      extern dpa_u_bo_unique_hashmap_t dpa__u_bo_do_intern(dpa_u_any_bo_ro_t* bo);
      return (dpa_u_bo_unique_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = dpa__u_bo_do_intern(bo),
      };
    }
  }
}

#define dpa_u_any_bo_ro(...) dpa_u_assert_selection(dpa_u_any_bo_ro_g(__VA_ARGS__))
#define dpa_u_any_bo_ro_g(X) dpa_u_generic_if_selection(dpa_u_bo_ptr_g(X), (dpa_u_any_bo_ro_t*)dpa_u_bo_ptr((X)))

/**
 * Interns a buffer. The refcount of the buffer will be increased.
 * \returns dpa_u_bo_unique_t
 */
#define dpa_u_bo_intern(...) dpa_u_assert_selection(dpa_u_bo_intern_g(__VA_ARGS__))
#define dpa_u_bo_intern_g(X) _Generic((X), \
    dpa_u_bo_inline_t: (const dpa_u_bo_unique_t){ .bo_inline = DPA__G(dpa_u_bo_inline_t, (X)) }, \
    dpa_u_bo_inline_t*: (const dpa_u_bo_unique_t){ .bo_inline = *DPA__G(dpa_u_bo_inline_t*, (X)) }, \
    const dpa_u_bo_inline_t*: (const dpa_u_bo_unique_t){ .bo_inline = *DPA__G(const dpa_u_bo_inline_t*, (X)) }, \
    dpa_u_any_bo_inline_t*: (const dpa_u_bo_unique_t){ .bo_inline = *(const dpa_u_bo_inline_t*)DPA__G(dpa_u_any_bo_inline_t*, (X)) }, \
    \
    dpa_u_bo_unique_hashmap_t: (dpa__u_v_bo_unique_hashmap__ref(DPA__G(dpa_u_bo_unique_hashmap_t,(X))),(const dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = DPA__G(dpa_u_bo_unique_hashmap_t,(X)) }), \
    dpa_u_any_bo_unique_hashmap_t*: (dpa__u_any_bo_unique_hashmap__ref(DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))),(const dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X)) }), \
    \
    dpa_u_bo_unique_t: (dpa__u_v_bo_unique__ref(DPA__G(dpa_u_bo_unique_t,(X))),(X)), \
    dpa_u_bo_unique_t*: (dpa__u_p_bo_unique__ref(DPA__G(dpa_u_bo_unique_t*,(X))),*DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: (dpa__u_cp_bo_unique__ref(DPA__G(const dpa_u_bo_unique_t*,(X))),*DPA__G(const dpa_u_bo_unique_t*,(X))), \
    dpa_u_any_bo_unique_t*: (dpa__u_any_bo_unique__ref(DPA__G(dpa_u_any_bo_unique_t*,(X))),*(const dpa_u_bo_unique_t*)DPA__G(dpa_u_any_bo_unique_t*,(X))), \
    \
    default: dpa_u_generic_if_selection( dpa_u_any_bo_ro_g(X), dpa__u_bo_intern((dpa_u_any_bo_ro_t*)dpa_u_any_bo_ro_g(X)) ) \
  )

/////////////////////////////////////////
//////      Utility functions      //////
/////////////////////////////////////////

#define DPA__U_BOCVHV(T,F,X,...) \
  dpa_u_ ## T ## _t: F(DPA__G(dpa_u_ ## T ## _t,(X)), __VA_ARGS__), \
  dpa_u_ ## T ## _t*: F(*DPA__G(dpa_u_ ## T ## _t*,(X)), __VA_ARGS__), \
  const dpa_u_ ## T ## _t*: F(*DPA__G(const dpa_u_ ## T ## _t*,(X)), __VA_ARGS__), \
  dpa_u_any_ ## T ## _t*: F(*(dpa_u_ ## T ## _t*)DPA__G(dpa_u_any_ ## T ## _t*,(X)), __VA_ARGS__)

// This is the same as DPA__U_BOCVHV. It's a copy because I need to nest it, once, and the C preprocessor will not allow recursion.
#define DPA__U_BOCVHV2(T,F,X,...) \
  dpa_u_ ## T ## _t: F(DPA__G(dpa_u_ ## T ## _t,(X)), __VA_ARGS__), \
  dpa_u_ ## T ## _t*: F(*DPA__G(dpa_u_ ## T ## _t*,(X)), __VA_ARGS__), \
  const dpa_u_ ## T ## _t*: F(*DPA__G(const dpa_u_ ## T ## _t*,(X)), __VA_ARGS__), \
  dpa_u_any_ ## T ## _t*: F(*(dpa_u_ ## T ## _t*)DPA__G(dpa_u_any_ ## T ## _t*,(X)), __VA_ARGS__)

#define dpa_u_bo_compare(...) dpa_u_assert_selection(dpa_u_bo_compare_g(__VA_ARGS__))
#define dpa_u_bo_compare_g(X, Y) dpa__u_sort_param_by_type_g(dpa__u_bo_compare_g, (X), (Y))
#define dpa__u_bo_compare_g(X, Y, S) \
  _Generic((X), \
    DPA__U_BOCVHV(bo_inline, dpa__u_bo_compare_inline_g, (X), (Y), (S)), \
    dpa_u_bo_unique_hashmap_t: dpa__u_bo_compare_unique_hashmap_g(DPA__G(dpa_u_bo_unique_hashmap_t,(X)),(Y),(S)), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_bo_compare_unique_hashmap_g((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X)),(Y),(S)), \
    DPA__U_BOCVHV(bo_unique, dpa__u_bo_compare_unique_g, (X), (Y), (S)), \
    default: dpa_u_generic_if_selection(dpa_u_temp_bo_simple_ro(X), \
      dpa_u_generic_if_selection(dpa_u_temp_bo_simple_ro(Y), \
        dpa__u_bo_compare_default(dpa_u_temp_bo_simple_ro(X), dpa_u_temp_bo_simple_ro(Y)) \
      ) \
    ) \
  )

DPA_U_EXPORT inline int dpa__u_bo_compare_default(const dpa_u_bo_simple_ro_t a, const dpa_u_bo_simple_ro_t b){
  const size_t a_size = dpa_u_bo_get_size(a);
  const size_t b_size = dpa_u_bo_get_size(b);
  if(a_size < b_size) return -1;
  if(a_size > b_size) return 1;
  const void*const a_data = dpa_u_bo_data(a);
  const void*const b_data = dpa_u_bo_data(b);
  if(a_data == b_data)
    return 0;
  return memcmp(a_data, b_data, a_size);
}

// Note: S is always 1
#define dpa__u_bo_compare_inline_g(X,Y,S) dpa_u_generic((Y), DPA__U_BOCVHV2(bo_inline, (-S) * dpa__u_bo_compare_inline, (Y), (X)))
DPA_U_EXPORT inline int dpa__u_bo_compare_inline(const dpa_u_bo_inline_t a, const dpa_u_bo_inline_t b){
  if(a.size != b.size)
    return (int)a.size - b.size;
  return memcmp(a.data, b.data, a.size);
}

// Note: dpa_u_bo_intern will always return an inline bo if the string fits into it. Therefore, if we have an inline bo, it can not match a unique_hashmap bo.
#define dpa__u_bo_compare_unique_hashmap_g(X,Y,S) \
  dpa_u_generic((Y), \
    dpa_u_bo_inline_t: -S, \
    dpa_u_any_bo_inline_t*: -S, \
    dpa_u_bo_unique_hashmap_t: S * ((X) - DPA__G(dpa_u_bo_unique_hashmap_t,(Y))), \
    dpa_u_any_bo_unique_hashmap_t*: S * ((X) - (dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(Y))) \
  )

#define dpa__u_bo_compare_unique_g(X,Y,S) \
  dpa_u_generic((Y), \
    dpa_u_bo_inline_t: -S, \
    dpa_u_any_bo_inline_t*: -S, \
    dpa_u_bo_unique_hashmap_t: (X).type == DPA_U_BO_UNIQUE_HASHMAP ? (S * ((X).bo_unique_hashmap - (dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_bo_unique_hashmap_t,(Y)))) : -S, \
    dpa_u_any_bo_unique_hashmap_t*: (X).type == DPA_U_BO_UNIQUE_HASHMAP ? (S * ((X).bo_unique_hashmap - (dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(Y)))) : -S, \
    DPA__U_BOCVHV2(bo_unique, (-S) * dpa__u_bo_compare_unique, (Y), (X)) \
  )
DPA_U_EXPORT inline int dpa__u_bo_compare_unique(const dpa_u_bo_unique_t a, const dpa_u_bo_unique_t b){
  const enum dpa_u_bo_unique_type a_type = dpa_u_bo_get_type(a);
  const enum dpa_u_bo_unique_type b_type = dpa_u_bo_get_type(b);
  if(a_type != b_type)
    return a_type - b_type;
  switch(a_type){
    case DPA_U_BO_INLINE: return dpa__u_bo_compare_inline(a.bo_inline, b.bo_inline);
    case DPA_U_BO_UNIQUE_HASHMAP: return a.bo_unique_hashmap - b.bo_unique_hashmap;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(a)));
}

DPA_U_EXPORT extern dpa_u_bo_unique_hashmap_stats_t dpa_u_bo_unique_hashmap_stats(void);
DPA_U_EXPORT extern void dpa_u_bo_unique_verify(void);

#define DPA_U_DECLARE_UNIQUE_CSTRING(name, ...) \
  dpa_u_unsequenced dpa__u_really_inline DPA_U_EXPORT inline dpa_u_bo_unique_t name (void){ \
    if((sizeof((const char[]){__VA_ARGS__})-1) <= DPA_U_BO_INLINE_MAX_SIZE){ \
      dpa_u_bo_unique_t ubo = { \
        .bo_inline = { \
          .type = DPA_U_BO_INLINE, \
          .size = (sizeof((const char[]){__VA_ARGS__})-1) & 0xF, \
        } \
      }; \
      memcpy(ubo.bo_inline.data, (const char[]){__VA_ARGS__}, sizeof((const char[]){__VA_ARGS__})-1); \
      return ubo; \
    }else{ \
      extern dpa_u_bo_unique_hashmap_t dpa__u_sucstrp__ ## name; \
      return (const dpa_u_bo_unique_t){ \
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, \
        .bo_unique_hashmap = dpa__u_sucstrp__ ## name, \
      }; \
    } \
  }
#define DPA_U_DEFINE_UNIQUE_CSTRING(name, ...) \
  extern dpa_u_bo_unique_t name (void); \
  dpa_u_bo_unique_hashmap_t dpa__u_sucstrp__ ## name; \
  __attribute__((constructor,used)) \
  static void dpa__u_sucstri__ ## name(void){ \
    if((sizeof((const char[]){__VA_ARGS__})-1) > DPA_U_BO_INLINE_MAX_SIZE){ \
      static const char cstr[] = {__VA_ARGS__}; \
      static dpa__u_bo_unique_hashmap_entry_t uhe = { \
        .base.bo_simple = { \
          .type = DPA_U_BO_UNIQUE_HASHMAP, \
          .size = sizeof(cstr)-1, \
          .data = cstr, \
        }, \
        .refcount = dpa_u_refcount_i_static, \
      }; \
      extern dpa_u_bo_unique_hashmap_t dpa__u_bo_do_intern(dpa_u_any_bo_ro_t* bo); \
      dpa__u_sucstrp__ ## name = dpa__u_bo_do_intern((dpa_u_any_bo_ro_t*)&uhe); \
    } \
  }

#endif
