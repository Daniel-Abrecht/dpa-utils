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

#define dpa_u_bo_type_list(X) \
  X((DPA_U_BO_INLINE, 1)) \
  X((DPA_U_BO_UNIQUE_HASHMAP)) \
  X((DPA_U_BO_SIMPLE)) \
  X((DPA_U_BO_HASHED)) \
  X((DPA_U_BO_REFCOUNTED)) \
  X((DPA_U_BO_REFCOUNTED_HASHED))

DPA_U_ENUM(dpa_u_bo_type)

/**
 * Many compilers have this really nice feature that they can warn you about enums without a case in a switch.
 * Not all types are compatible, so not all of them will need a case. These enums correspond to types with just
 * the possible type constants. The values are the same as in the enum dpa_u_bo_type.
 * @{
 */
enum dpa_u_bo_s_inline_type { DPA_U_BO_INLINE_1 = DPA_U_BO_INLINE };
enum dpa_u_any_bo_s_inline_type { DPA_U_BO_INLINE_A1 = DPA_U_BO_INLINE };
enum dpa_u_bo_s_simple_type { DPA_U_BO_SIMPLE_2 = DPA_U_BO_SIMPLE };
enum dpa_u_any_bo_s_simple_type { DPA_U_BO_SIMPLE_A2 = DPA_U_BO_SIMPLE };
enum dpa_u_bo_s_unique_hashmap_type { DPA_U_BO_UNIQUE_HASHMAP_3 = DPA_U_BO_UNIQUE_HASHMAP };
enum dpa_u_any_bo_s_unique_hashmap_type { DPA_U_BO_UNIQUE_HASHMAP_A3 = DPA_U_BO_UNIQUE_HASHMAP };
enum dpa_u_bo_s_simple_ro_type { DPA_U_BO_SIMPLE_4 = DPA_U_BO_SIMPLE };
enum dpa_u_any_bo_s_simple_ro_type { DPA_U_BO_SIMPLE_A4 = DPA_U_BO_SIMPLE };
enum dpa_u_bo_s_ro_type {
  DPA_U_BO_INLINE_10 = DPA_U_BO_INLINE,
  DPA_U_BO_UNIQUE_HASHMAP_10 = DPA_U_BO_UNIQUE_HASHMAP,
  DPA_U_BO_SIMPLE_10 = DPA_U_BO_SIMPLE,
};
enum dpa_u_any_bo_s_ro_type {
  DPA_U_BO_INLINE_A10 = DPA_U_BO_INLINE,
  DPA_U_BO_UNIQUE_HASHMAP_A10 = DPA_U_BO_UNIQUE_HASHMAP,
  DPA_U_BO_SIMPLE_A10 = DPA_U_BO_SIMPLE,
};
enum dpa_u_bo_s_type {
  DPA_U_BO_INLINE_11 = DPA_U_BO_INLINE,
  DPA_U_BO_SIMPLE_11 = DPA_U_BO_SIMPLE,
};
enum dpa_u_any_bo_s_type {
  DPA_U_BO_INLINE_A11 = DPA_U_BO_INLINE,
  DPA_U_BO_SIMPLE_A11 = DPA_U_BO_SIMPLE,
};
enum dpa_u_bo_s_unique_type {
  DPA_U_BO_INLINE_12  = DPA_U_BO_INLINE,
  DPA_U_BO_UNIQUE_HASHMAP_12 = DPA_U_BO_UNIQUE_HASHMAP,
};
enum dpa_u_any_bo_s_unique_type {
  DPA_U_BO_INLINE_A12  = DPA_U_BO_INLINE,
  DPA_U_BO_UNIQUE_HASHMAP_A12 = DPA_U_BO_UNIQUE_HASHMAP,
};
// @}

// We erase the type information from these enums, because we do not want it to warn if they are assigned to one of the specialized enums above.
#define DPA_U_BO_INLINE ((int)DPA_U_BO_INLINE)
#define DPA_U_BO_SIMPLE ((int)DPA_U_BO_SIMPLE)
#define DPA_U_BO_UNIQUE_HASHMAP ((int)DPA_U_BO_UNIQUE_HASHMAP)

#define case_DPA_U_BO_UNIQUE case DPA_U_BO_INLINE: case DPA_U_BO_UNIQUE_HASHMAP

#define DPA__U_BO_META(X) \
  struct __attribute__((packed)) { \
    unsigned type : CHAR_BIT - 4; \
    unsigned X : 4; \
  }

struct dpa__u_bo_a { char all[DPA__U_BO_COMMON_SIZE]; };
typedef DPA__U_BO_META(size) dpa__u_bo_meta_t;

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
      struct __attribute__((packed)) { \
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

struct dpa_u_bo_ro {
  union {
    struct { DPA__U_BO_META(extra); char _[DPA__U_BO_COMMON_SIZE-1]; };
    dpa_u_bo_inline_ro_t bo_inline;
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
  dpa_u_bo_simple_ro_t bo_simple;
  // The refcount should be allocated with the data, because it shares the lifetime of the data, not of the bo.
  dpa_u_refcount_freeable_t* refcount;
};

struct dpa_u_bo_refcounted {
  dpa_u_bo_simple_t bo_simple;
  // The refcount should be allocated with the data, because it shares the lifetime of the data, not of the bo.
  dpa_u_refcount_freeable_t* refcount;
};

struct dpa_u_bo_hashed_ro {
  dpa_u_bo_simple_ro_t bo_simple;
  dpa_u_hash_t hash;
};

struct dpa_u_bo_hashed {
  dpa_u_bo_simple_t bo_simple;
  dpa_u_hash_t hash;
};

struct dpa_u_bo_refcounted_hashed_ro {
  dpa_u_bo_refcounted_ro_t bo_refcounted;
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
    T: dpa__u_ ## P ## _ ## S(DPA__G(T,(X)))

#define dpa__u_helper_v_g(T,S,X) \
    dpa__u_helper_g(dpa_u_ ## T ## _t, v_ ## T, S, (X)), \
    dpa__u_helper_g(dpa_u_ ## T ## _t*, p_ ## T, S, (X)), \
    dpa__u_helper_g(const dpa_u_ ## T ## _t*, cp_ ## T, S, (X)), \
    dpa_u_any_ ## T ## _t*: dpa__u_any_ ## T ## _ ## S(DPA__G(dpa_u_any_ ## T ## _t*,(X)))

#define dpa__u_helper_all_g(S,X) \
    dpa__u_helper_v_g(bo_inline, S, (X)), \
    dpa__u_helper_g(dpa_u_bo_unique_hashmap_t, v_bo_unique_hashmap, S, (X)), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_any_bo_unique_hashmap_ ## S((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    dpa__u_helper_v_g(bo_unique, S, (X)), \
    dpa__u_helper_v_g(bo_simple, S, (X)), \
    dpa__u_helper_v_g(bo_simple_ro, S, (X)), \
    dpa__u_helper_v_g(bo, S, (X)), \
    dpa__u_helper_v_g(bo_ro, S, (X))

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
    dpa_u_bo_ro_t: 0x70, \
    dpa_u_bo_ro_t*: 0x71, \
    const dpa_u_bo_ro_t*: 0x72, \
    dpa_u_any_bo_ro_t*: 0x74, \
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
 * te compiler only warns about the possible type values if they haveno case. It's always safe to cast to (enum dpa_u_bo_type),
 * and it's recommended to always use the constants in that struct.
 */
#define dpa_u_bo_get_type(...) dpa_u_assert_selection(dpa_u_bo_get_type_g(__VA_ARGS__))
#define dpa_u_bo_get_type_g(X) dpa_u_generic((X),dpa__u_helper_all_g(get_type,(X)))

#define dpa__u_v_bo_unique_hashmap_get_type(X)   DPA_U_BO_UNIQUE_HASHMAP_3
#define dpa__u_p_bo_unique_hashmap_get_type(X)   DPA_U_BO_UNIQUE_HASHMAP_3
#define dpa__u_cp_bo_unique_hashmap_get_type(X)  DPA_U_BO_UNIQUE_HASHMAP_3
#define dpa__u_any_bo_unique_hashmap_get_type(X) DPA_U_BO_UNIQUE_HASHMAP_A3

#define dpa__u_v_bo_inline_get_type(X)   DPA_U_BO_INLINE_1
#define dpa__u_p_bo_inline_get_type(X)   DPA_U_BO_INLINE_1
#define dpa__u_cp_bo_inline_get_type(X)  DPA_U_BO_INLINE_1
#define dpa__u_any_bo_inline_get_type(X) DPA_U_BO_INLINE_A1

#define dpa__u_v_bo_simple_get_type(X)   DPA_U_BO_SIMPLE_2
#define dpa__u_p_bo_simple_get_type(X)   DPA_U_BO_SIMPLE_2
#define dpa__u_cp_bo_simple_get_type(X)  DPA_U_BO_SIMPLE_2
#define dpa__u_any_bo_simple_get_type(X) ((enum dpa_u_any_bo_s_simple_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_simple_ro_get_type(X)   DPA_U_BO_SIMPLE_4
#define dpa__u_p_bo_simple_ro_get_type(X)   DPA_U_BO_SIMPLE_4
#define dpa__u_cp_bo_simple_ro_get_type(X)  DPA_U_BO_SIMPLE_4
#define dpa__u_any_bo_simple_ro_get_type(X) ((enum dpa_u_any_bo_s_simple_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_unique_get_type(X)   ((enum dpa_u_bo_s_unique_type)((X).type))
#define dpa__u_p_bo_unique_get_type(X)   ((enum dpa_u_bo_s_unique_type)((X)->type))
#define dpa__u_cp_bo_unique_get_type(X)  ((enum dpa_u_bo_s_unique_type)((X)->type))
#define dpa__u_any_bo_unique_get_type(X) ((enum dpa_u_any_bo_s_unique_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_get_type(X)   ((enum dpa_u_bo_s_type)((X).type))
#define dpa__u_p_bo_get_type(X)   ((enum dpa_u_bo_s_type)((X)->type))
#define dpa__u_cp_bo_get_type(X)  ((enum dpa_u_bo_s_type)((X)->type))
#define dpa__u_any_bo_get_type(X) ((enum dpa_u_any_bo_s_type)(((const dpa__u_bo_meta_t*)(X))->type))

#define dpa__u_v_bo_ro_get_type(X)   ((enum dpa_u_bo_s_ro_type)((X).type))
#define dpa__u_p_bo_ro_get_type(X)   ((enum dpa_u_bo_s_ro_type)((X)->type))
#define dpa__u_cp_bo_ro_get_type(X)  ((enum dpa_u_bo_s_ro_type)((X)->type))
#define dpa__u_any_bo_ro_get_type(X) ((enum dpa_u_any_bo_s_ro_type)(((const dpa__u_bo_meta_t*)(X))->type))

////

#define dpa_u_bo_data(...) dpa_u_assert_selection(dpa_u_bo_data_g(__VA_ARGS__))
#define dpa_u_bo_data_g(X) dpa_u_generic((X),dpa__u_helper_all_g(data,(X)))

#define dpa__u_v_bo_unique_hashmap_data(X)   ((X)->base.bo_simple.data)
#define dpa__u_p_bo_unique_hashmap_data(X)   ((X)->base.bo_simple.data)
#define dpa__u_cp_bo_unique_hashmap_data(X)  ((X)->base.bo_simple.data)
#define dpa__u_any_bo_unique_hashmap_data(X) ((X)->base.bo_simple.data)

#define dpa__u_v_bo_inline_data(X)   ((X).data)
#define dpa__u_p_bo_inline_data(X)   ((X)->data)
#define dpa__u_cp_bo_inline_data(X)  ((X)->data)
#define dpa__u_any_bo_inline_data(X) (((const dpa_u_bo_inline_t*)(X))->data)

#define dpa__u_v_bo_simple_data(X)   ((X).data)
#define dpa__u_p_bo_simple_data(X)   ((X)->data)
#define dpa__u_cp_bo_simple_data(X)  ((X)->data)
#define dpa__u_any_bo_simple_data(X) (((const dpa_u_bo_simple_t*)(X))->data)

#define dpa__u_v_bo_simple_ro_data(X)   ((X).data)
#define dpa__u_p_bo_simple_ro_data(X)   ((X)->data)
#define dpa__u_cp_bo_simple_ro_data(X)  ((X)->data)
#define dpa__u_any_bo_simple_ro_data(X) (((const dpa_u_bo_simple_ro_t*)(X))->data)

// bo_unique could contain bo_inline. Copying a bo_inline would mean copying it's data.
// This is why we reference it. This also means we need an lvalue here.
#define dpa__u_v_bo_unique_data(X)   dpa__u_cp_bo_unique_data(&(X))
#define dpa__u_p_bo_unique_data(X)   dpa__u_cp_bo_unique_data((X))
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_cp_bo_unique_data(const dpa_u_bo_unique_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo->bo_unique_hashmap->base.bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_any_bo_unique_data(const dpa_u_any_bo_unique_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->data;
    case DPA_U_BO_UNIQUE_HASHMAP: return ((dpa_u_bo_unique_hashmap_t)bo)->base.bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_v_bo_data(X) dpa_u_generic(&(X), \
          dpa_u_bo_t*: dpa__u_p_bo_data(&(X)), \
    const dpa_u_bo_t*: dpa__u_cp_bo_data(&(X)) \
  )
DPA_U_EXPORT inline dpa__u_really_inline void* dpa__u_p_bo_data(dpa_u_bo_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_cp_bo_data(const dpa_u_bo_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_any_bo_data(const dpa_u_any_bo_t* const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->data;
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->data;
  }
  dpa_u_unreachable("dpa_u_any_bo_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

// bo_unique could contain bo_inline. Copying a bo_inline would mean copying it's data.
// This is why we reference it. This also means we need an lvalue here.
#define dpa__u_v_bo_ro_data(X)   dpa__u_cp_bo_ro_data(&(X))
#define dpa__u_p_bo_ro_data(X)   dpa__u_cp_bo_ro_data((X))
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_cp_bo_ro_data(const dpa_u_bo_ro_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo->bo_unique_hashmap->base.bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline dpa__u_really_inline const void* dpa__u_any_bo_ro_data(const dpa_u_any_bo_ro_t* const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->data;
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->data;
    case DPA_U_BO_UNIQUE_HASHMAP: return ((dpa_u_bo_unique_hashmap_t)bo)->base.bo_simple.data;
  }
  dpa_u_unreachable("dpa_u_any_bo_ro_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}


////

#define dpa_u_bo_set_size(...) dpa_u_assert_selection(dpa_u_bo_set_size_g(__VA_ARGS__))
#define dpa_u_bo_set_size_g(X,S) ((void)dpa_u_generic((X), \
    dpa_u_bo_inline_t: (assert((S) <= DPA_U_BO_INLINE_MAX_SIZE),(DPA__G(dpa_u_bo_inline_t,(X)).size=(S)&0xF)), \
    dpa_u_bo_simple_t: (assert((S) <= DPA_U_BO_MAX_SIZE       ),(DPA__G(dpa_u_bo_simple_t,(X)).size=(S))), \
    dpa_u_bo_simple_ro_t: (assert((S) <= DPA_U_BO_MAX_SIZE    ),(DPA__G(dpa_u_bo_simple_ro_t,(X)).size=(S))), \
    dpa_u_bo_t: dpa__u_bo_set_size(&DPA__G(dpa_u_bo_t,(X)),(S)), \
    \
    dpa_u_bo_inline_t*: (assert((S) <= DPA_U_BO_INLINE_MAX_SIZE),(DPA__G(dpa_u_bo_inline_t*,(X)).size=(S)&0xF)), \
    dpa_u_bo_simple_t*: (assert((S) <= DPA_U_BO_MAX_SIZE       ),(DPA__G(dpa_u_bo_simple_t*,(X)).size=(S))), \
    dpa_u_bo_simple_ro_t*: (assert((S) <= DPA_U_BO_MAX_SIZE    ),(DPA__G(dpa_u_bo_simple_ro_t*,(X)).size=(S))), \
    dpa_u_bo_t*: dpa__u_bo_set_size(DPA__G(dpa_u_bo_t*,(X)),(S)) \
  ))

DPA_U_EXPORT inline dpa__u_really_inline void dpa__u_bo_set_size(dpa_u_bo_t*restrict const bo, size_t size){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: {
      assert(size <= DPA_U_BO_INLINE_MAX_SIZE);
      bo->bo_inline.size = size;
    } return;
    case DPA_U_BO_SIMPLE: {
      bo->bo_simple.size = size;
    } return;
  }
  dpa_u_unreachable("Can't set size on bo of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

///

#define dpa_u_bo_get_size(...) dpa_u_assert_selection(dpa_u_bo_get_size_g(__VA_ARGS__))
#define dpa_u_bo_get_size_g(X) dpa_u_generic((X),dpa__u_helper_all_g(get_size,(X)))

#define dpa__u_v_bo_unique_hashmap_get_size(X) ((X)->base.bo_simple.size)
#define dpa__u_p_bo_unique_hashmap_get_size(X) ((X)->base.bo_simple.size)
#define dpa__u_cp_bo_unique_hashmap_get_size(X) ((X)->base.bo_simple.size)
#define dpa__u_any_bo_unique_hashmap_get_size(X) ((X)->base.bo_simple.size)

#define dpa__u_v_bo_inline_get_size(X) ((X).size)
#define dpa__u_p_bo_inline_get_size(X) ((X)->size)
#define dpa__u_cp_bo_inline_get_size(X) ((X)->size)
#define dpa__u_any_bo_inline_get_size(X) (((const dpa_u_bo_inline_t*)(X))->size)

#define dpa__u_v_bo_simple_get_size(X) ((X).size)
#define dpa__u_p_bo_simple_get_size(X) ((X)->size)
#define dpa__u_cp_bo_simple_get_size(X) ((X)->size)
#define dpa__u_any_bo_simple_get_size(X) (((const dpa_u_bo_simple_t*)(X))->size)

#define dpa__u_v_bo_simple_ro_get_size(X) ((X).size)
#define dpa__u_p_bo_simple_ro_get_size(X) ((X)->size)
#define dpa__u_cp_bo_simple_ro_get_size(X) ((X)->size)
#define dpa__u_any_bo_simple_ro_get_size(X) (((const dpa_u_bo_simple_ro_t*)(X))->size)

DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_v_bo_unique_get_size(const dpa_u_bo_unique_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo.bo_unique_hashmap->base.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo_unique_get_size(X) dpa__u_v_bo_unique_get_size(*(X))
#define dpa__u_cp_bo_unique_get_size(X) dpa__u_v_bo_unique_get_size(*(X))
DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_any_bo_unique_get_size(const dpa_u_any_bo_unique_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->size;
    case DPA_U_BO_UNIQUE_HASHMAP: return ((dpa_u_bo_unique_hashmap_t)bo)->base.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_any_bo_unique_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_v_bo_get_size(const dpa_u_bo_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_SIMPLE: return bo.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo_get_size(X) dpa__u_v_bo_get_size(*(X))
#define dpa__u_cp_bo_get_size(X) dpa__u_v_bo_get_size(*(X))
DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_any_bo_get_size(const dpa_u_any_bo_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->size;
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->size;
  }
  dpa_u_unreachable("dpa_u_any_bo_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_v_bo_ro_get_size(const dpa_u_bo_ro_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_SIMPLE: return bo.bo_simple.size;
    case DPA_U_BO_UNIQUE_HASHMAP: return bo.bo_unique_hashmap->base.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
#define dpa__u_p_bo_ro_get_size(X) dpa__u_v_bo_ro_get_size(*(X))
#define dpa__u_cp_bo_ro_get_size(X) dpa__u_v_bo_ro_get_size(*(X))
DPA_U_EXPORT inline dpa__u_really_inline size_t dpa__u_any_bo_ro_get_size(const dpa_u_any_bo_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return ((const dpa_u_bo_inline_t*)bo)->size;
    case DPA_U_BO_SIMPLE: return ((const dpa_u_bo_simple_t*)bo)->size;
    case DPA_U_BO_UNIQUE_HASHMAP: return ((dpa_u_bo_unique_hashmap_t)bo)->base.bo_simple.size;
  }
  dpa_u_unreachable("dpa_u_any_bo_ro_t* can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

///

DPA_U_EXPORT inline dpa__u_really_inline void dpa__u_bo_unique_hashmap_ref(dpa_u_bo_unique_hashmap_t bo){
  dpa_u_refcount_ref(&bo->refcount);
}

DPA_U_EXPORT inline dpa__u_really_inline bool dpa__u_bo_unique_hashmap_put(dpa_u_bo_unique_hashmap_t bo){
  return dpa_u_refcount_put(&bo->refcount);
}

DPA_U_EXPORT inline dpa__u_really_inline void dpa__u_bo_unique_ref(dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_bo_unique_hashmap_ref(ubo.bo_unique_hashmap); return;
    case DPA_U_BO_INLINE: return;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(ubo)));
}

DPA_U_EXPORT inline dpa__u_really_inline bool dpa__u_bo_unique_put(dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return dpa__u_bo_unique_hashmap_put(ubo.bo_unique_hashmap);
    case DPA_U_BO_INLINE: return false;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(ubo)));
}

/**
 * Increments the refcount of the buffer. The refcount acts on the data of the buffer
 * rather than the buffer itself. For dpa_u_bo_inline_t, this is a noop, because
 * the buffer contains the data directly instead of referencing it, therefore, having
 * an instance of a dpa_u_bo_inline_t means having the data.
 */
#define dpa_u_bo_ref(...) dpa_u_assert_selection(dpa_u_bo_ref_g(__VA_ARGS__))
#define dpa_u_bo_ref_g(X) dpa_u_generic((X), \
    dpa_u_bo_inline_t: (void)0, \
    dpa_u_bo_inline_t*: (void)0, \
    const dpa_u_bo_inline_t*: (void)0, \
    const dpa_u_any_bo_inline_t*: (void)0, \
    \
    dpa_u_bo_unique_hashmap_t: dpa__u_bo_unique_hashmap_ref(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_bo_unique_hashmap_ref((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    \
    dpa_u_bo_unique_t: dpa__u_bo_unique_ref(DPA__G(dpa_u_bo_unique_t,(X))), \
    dpa_u_bo_unique_t*: dpa__u_bo_unique_ref(*DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: dpa__u_bo_unique_ref(*DPA__G(const dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: dpa__u_bo_unique_ref(*DPA__G(const dpa_u_bo_unique_t*,(X))), \
        dpa_u_any_bo_unique_t*: dpa__u_bo_unique_ref(*(dpa_u_bo_unique_t*)DPA__G(dpa_u_any_bo_unique_t*,(X))) \
  )

#define dpa_u_bo_put(...) dpa_u_assert_selection(dpa_u_bo_put_g(__VA_ARGS__))
#define dpa_u_bo_put_g(X) dpa_u_generic((X), \
    dpa_u_bo_inline_t: (void)0, \
    dpa_u_bo_inline_t*: (void)0, \
    const dpa_u_bo_inline_t*: (void)0, \
    const dpa_u_any_bo_inline_t*: (void)0, \
    \
    dpa_u_bo_unique_hashmap_t: dpa__u_bo_unique_hashmap_put(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_bo_unique_hashmap_put((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    \
    dpa_u_bo_unique_t: dpa__u_bo_unique_put(DPA__G(dpa_u_bo_unique_t,(X))), \
    dpa_u_bo_unique_t*: dpa__u_bo_unique_put(*DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: dpa__u_bo_unique_put(*DPA__G(const dpa_u_bo_unique_t*,(X))), \
        dpa_u_any_bo_unique_t*: dpa__u_bo_unique_put(*(dpa_u_bo_unique_t*)DPA__G(dpa_u_any_bo_unique_t*,(X))) \
  )

DPA_U_EXPORT inline dpa__u_really_inline dpa_u_refcount_freeable_t* dpa__u_bo_unique_get_refcount(const dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&ubo.bo_unique_hashmap->refcount.freeable;
    case DPA_U_BO_INLINE: return &dpa_u_refcount_static_v_freeable;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(ubo)));
}

DPA_U_EXPORT inline dpa__u_really_inline dpa_u_refcount_freeable_t* dpa__u_bo_ro_p_get_refcount(const dpa_u_bo_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&bo->bo_unique_hashmap->refcount.freeable;
    case DPA_U_BO_INLINE: return &dpa_u_refcount_static_v_freeable;
    case DPA_U_BO_SIMPLE: return 0;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

DPA_U_EXPORT inline dpa__u_really_inline dpa_u_refcount_freeable_t* dpa__u_bo_ro_get_refcount(const dpa_u_bo_ro_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (dpa_u_refcount_freeable_t*)&bo.bo_unique_hashmap->refcount.freeable;
    case DPA_U_BO_INLINE: return &dpa_u_refcount_static_v_freeable;
    case DPA_U_BO_SIMPLE: return 0;
  }
  dpa_u_unreachable("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

DPA_U_EXPORT inline dpa__u_really_inline dpa_u_refcount_freeable_t* dpa__u_bo_p_get_refcount(const dpa_u_bo_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return &dpa_u_refcount_static_v_freeable;
    case DPA_U_BO_SIMPLE: return 0;
  }
  dpa_u_unreachable("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_bo_unique_hashmap_get_refcount(X) ((dpa_u_refcount_freeable_t*)&(X)->refcount.freeable)

#define dpa_u_bo_get_refcount(...) dpa_u_assert_selection(dpa_u_bo_get_refcount_g(__VA_ARGS__))
#define dpa_u_bo_get_refcount_g(X) dpa_u_generic((X), \
    dpa_u_bo_ro_t: dpa__u_bo_ro_get_refcount(DPA__G(dpa_u_bo_ro_t,(X))), \
    dpa_u_bo_inline_t: &dpa_u_refcount_static_v_freeable, \
    dpa_u_bo_unique_t: dpa__u_bo_unique_get_refcount(DPA__G(dpa_u_bo_unique_t,(X))), \
    \
    dpa_u_bo_unique_hashmap_t: dpa__u_bo_unique_hashmap_get_refcount(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_any_bo_unique_hashmap_t*: dpa__u_bo_unique_hashmap_get_refcount((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))), \
    \
          dpa_u_bo_unique_t*: dpa__u_bo_unique_get_refcount(*DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: dpa__u_bo_unique_get_refcount(*DPA__G(const dpa_u_bo_unique_t*,(X))), \
        dpa_u_any_bo_unique_t*: dpa__u_bo_unique_get_refcount(*(const dpa_u_bo_unique_t*)DPA__G(dpa_u_any_bo_unique_t*,(X))), \
          dpa_u_bo_inline_t*: &dpa_u_refcount_static_v_freeable, \
    const dpa_u_bo_inline_t*: &dpa_u_refcount_static_v_freeable, \
        dpa_u_any_bo_inline_t*: &dpa_u_refcount_static_v_freeable, \
          dpa_u_bo_ro_t*: dpa__u_bo_ro_p_get_refcount(DPA__G(dpa_u_bo_ro_t*,(X))), \
    const dpa_u_bo_ro_t*: dpa__u_bo_ro_p_get_refcount(DPA__G(const dpa_u_bo_ro_t*,(X))), \
          dpa_u_bo_t*: dpa__u_bo_p_get_refcount(DPA__G(dpa_u_bo_t*,(X))), \
    const dpa_u_bo_t*: dpa__u_bo_p_get_refcount(DPA__G(const dpa_u_bo_t*,(X))) \
  )

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
#define dpa_u_temp_bo_simple_ro_g(X) dpa_u_generic((X),dpa__u_helper_all_g(_temp_bo_simple_ro,(X)))

#define dpa__u_temp_bo_simple_ro__helper(P,X) (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa__u_ ## P ## _get_size((X)), .data=dpa__u_ ## P ## _data((X)) }

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

#define dpa_u_bo_ptr(...) dpa_u_assert_selection(dpa_u_bo_ptr_g(__VA_ARGS__))
#define dpa_u_bo_ptr_g(X) dpa_u_generic((X), \
    dpa_u_any_bo_inline_t*: (X), \
    dpa_u_any_bo_unique_hashmap_t*: (X), \
    dpa_u_any_bo_unique_t*: (X), \
    dpa_u_any_bo_simple_t*: (X), \
    dpa_u_any_bo_simple_ro_t*: (X), \
    dpa_u_any_bo_t*: (X), \
    dpa_u_any_bo_ro_t*: (X), \
    \
    dpa_u_bo_inline_t: (dpa_u_any_bo_inline_t*)&DPA__G(dpa_u_bo_inline_t,(X)), \
    dpa_u_bo_unique_hashmap_t: (dpa_u_any_bo_unique_hashmap_t*)DPA__G(dpa_u_bo_unique_hashmap_t,(X)), \
    dpa_u_bo_unique_t: (dpa_u_any_bo_unique_t*)&DPA__G(dpa_u_bo_unique_t,(X)), \
    dpa_u_bo_simple_t: (dpa_u_any_bo_simple_t*)&DPA__G(dpa_u_bo_simple_t,(X)), \
    dpa_u_bo_simple_ro_t: (dpa_u_any_bo_simple_ro_t*)&DPA__G(dpa_u_bo_simple_ro_t,(X)), \
    dpa_u_bo_t: (dpa_u_any_bo_t*)&DPA__G(dpa_u_bo_t,(X)), \
    dpa_u_bo_ro_t: (dpa_u_any_bo_ro_t*)&DPA__G(dpa_u_bo_ro_t,(X)), \
    \
    dpa_u_bo_inline_t*: (dpa_u_any_bo_inline_t*)DPA__G(dpa_u_bo_inline_t*,(X)), \
    dpa_u_bo_unique_t*: (dpa_u_any_bo_unique_t*)DPA__G(dpa_u_bo_unique_t*,(X)), \
    dpa_u_bo_simple_t*: (dpa_u_any_bo_simple_t*)DPA__G(dpa_u_bo_simple_t*,(X)), \
    dpa_u_bo_simple_ro_t*: (dpa_u_any_bo_simple_ro_t*)DPA__G(dpa_u_bo_simple_ro_t*,(X)), \
    dpa_u_bo_t*: (dpa_u_any_bo_t*)DPA__G(dpa_u_bo_t*,(X)), \
    dpa_u_bo_ro_t*: (dpa_u_any_bo_ro_t*)DPA__G(dpa_u_bo_ro_t*,(X)), \
    \
    const dpa_u_bo_inline_t*: (dpa_u_any_bo_inline_t*)DPA__G(const dpa_u_bo_inline_t*,(X)), \
    const dpa_u_bo_unique_t*: (dpa_u_any_bo_unique_t*)DPA__G(const dpa_u_bo_unique_t*,(X)), \
    const dpa_u_bo_simple_t*: (dpa_u_any_bo_simple_t*)DPA__G(const dpa_u_bo_simple_t*,(X)), \
    const dpa_u_bo_simple_ro_t*: (dpa_u_any_bo_simple_ro_t*)DPA__G(const dpa_u_bo_simple_ro_t*,(X)), \
    const dpa_u_bo_t*: (dpa_u_any_bo_t*)DPA__G(const dpa_u_bo_t*,(X)), \
    const dpa_u_bo_ro_t*: (dpa_u_any_bo_ro_t*)DPA__G(const dpa_u_bo_ro_t*,(X)) \
  )

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
      dpa__u_bo_unique_hashmap_ref(ubo);
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
#define dpa_u_any_bo_ro_g(X) _Generic((X), \
    dpa_u_bo_unique_hashmap_t: (dpa_u_any_bo_ro_t*)&(dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = DPA__G(dpa_u_bo_unique_hashmap_t, (X)) }, \
    dpa_u_any_bo_unique_hashmap_t*: (dpa_u_any_bo_ro_t*)&(dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*, (X)) }, \
    default: dpa_u_generic_if_selection(dpa_u_bo_ptr_g(X), (dpa_u_any_bo_ro_t*)dpa_u_bo_ptr((X))) \
  )

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
    dpa_u_bo_unique_hashmap_t: (dpa__u_bo_unique_hashmap_ref(DPA__G(dpa_u_bo_unique_hashmap_t,(X))),(const dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = DPA__G(dpa_u_bo_unique_hashmap_t,(X)) }), \
    dpa_u_any_bo_unique_hashmap_t*: (dpa__u_bo_unique_hashmap_ref((dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X))),(const dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = (dpa_u_bo_unique_hashmap_t)DPA__G(dpa_u_any_bo_unique_hashmap_t*,(X)) }), \
    \
    dpa_u_bo_unique_t: (dpa__u_bo_unique_ref(DPA__G(dpa_u_bo_unique_t,(X))),(X)), \
    dpa_u_bo_unique_t*: (dpa__u_bo_unique_ref(*DPA__G(dpa_u_bo_unique_t*,(X))),*DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: (dpa__u_bo_unique_ref(*DPA__G(const dpa_u_bo_unique_t*,(X))),*DPA__G(const dpa_u_bo_unique_t*,(X))), \
    dpa_u_any_bo_unique_t*: (dpa__u_bo_unique_ref(*(const dpa_u_bo_unique_t*)DPA__G(dpa_u_any_bo_unique_t*,(X))),*(const dpa_u_bo_unique_t*)DPA__G(dpa_u_any_bo_unique_t*,(X))), \
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
  const enum dpa_u_bo_s_unique_type a_type = dpa_u_bo_get_type(a);
  const enum dpa_u_bo_s_unique_type b_type = dpa_u_bo_get_type(b);
  if(a_type != b_type)
    return a_type - b_type;
  switch(a_type){
    case DPA_U_BO_INLINE: return dpa__u_bo_compare_inline(a.bo_inline, b.bo_inline);
    case DPA_U_BO_UNIQUE_HASHMAP: return a.bo_unique_hashmap - b.bo_unique_hashmap;
  }
  dpa_u_unreachable("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(a)));
}

DPA_U_EXPORT extern dpa_u_bo_unique_hashmap_stats_t dpa_u_bo_unique_hashmap_stats(void);
DPA_U_EXPORT extern void dpa_u_bo_unique_verify(void);

#endif
