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

// A bo should always have a type set. If that was forgotten, and it was 0 initialised, the type is 0.
// Because of this, we so not define a type 0, and trying to get the data or size of such a bo may abort().
// It could still be useful to chek if a bo has ben set when passing a pointer to it to a function, though.

#define dpa_u_bo_type_list(X) \
  X((DPA_U_BO_INLINE, 1)) \
  X((DPA_U_BO_SIMPLE)) \
  X((DPA_U_BO_UNIQUE_HASHMAP))

DPA_U_ENUM(dpa_u_bo_type)

/**
 * Many compilers have this really nice feature that they can warn you about enums without a case in a switch.
 * Not all types are compatible, so not all of them will need a case. These enums correspond to types with just
 * the possible type constants. The values are the same as in the enum dpa_u_bo_type.
 * @{
 */
enum dpa_u_bo_s_inline_type { DPA_U_BO_INLINE_1 = DPA_U_BO_INLINE };
enum dpa_u_bo_s_simple_type { DPA_U_BO_SIMPLE_2 = DPA_U_BO_SIMPLE };
enum dpa_u_bo_s_unique_hashmap_type { DPA_U_BO_UNIQUE_HASHMAP_3 = DPA_U_BO_UNIQUE_HASHMAP };
enum dpa_u_bo_s_simple_ro_type { DPA_U_BO_SIMPLE_4 = DPA_U_BO_SIMPLE };
enum dpa_u_bo_s_ro_type {
  DPA_U_BO_INLINE_10 = DPA_U_BO_INLINE,
  DPA_U_BO_SIMPLE_10 = DPA_U_BO_SIMPLE,
  DPA_U_BO_UNIQUE_HASHMAP_10 = DPA_U_BO_UNIQUE_HASHMAP,
};
enum dpa_u_bo_s_type {
  DPA_U_BO_INLINE_11 = DPA_U_BO_INLINE,
  DPA_U_BO_SIMPLE_11 = DPA_U_BO_SIMPLE,
};
enum dpa_u_bo_s_unique_type {
  DPA_U_BO_INLINE_12  = DPA_U_BO_INLINE,
  DPA_U_BO_UNIQUE_HASHMAP_12 = DPA_U_BO_UNIQUE_HASHMAP,
};
// @}

// We erase the type information from these enums, because we do not want it to warn if they are assigned to one of the specialized enums above.
#define DPA_U_BO_INLINE ((int)DPA_U_BO_INLINE)
#define DPA_U_BO_SIMPLE ((int)DPA_U_BO_SIMPLE)
#define DPA_U_BO_UNIQUE_HASHMAP ((int)DPA_U_BO_UNIQUE_HASHMAP)

#define case_DPA_U_BO_UNIQUE case DPA_U_BO_INLINE: case DPA_U_BO_UNIQUE_HASHMAP

#define DPA__U_BO_META(...) \
  struct __attribute__((packed)) { \
    enum dpa_u_bo_type type : CHAR_BIT - 4; \
    unsigned __VA_ARGS__ : 4; \
  }

typedef struct dpa__u_bo_a { char all[DPA__U_BO_COMMON_SIZE]; } dpa__u_bo_a_t;

typedef struct dpa_u_bo_inline {
  union {
    struct {
      DPA__U_BO_META(size);
      char data[DPA__U_BO_COMMON_SIZE-1];
    };
    DPA__U_BO_ALIGN dpa__u_bo_a_t all;
  };
} dpa_u_bo_inline_t;
typedef const dpa_u_bo_inline_t dpa_u_bo_inline_ro_t;
static_assert(sizeof(dpa_u_bo_inline_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_inline_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_inline_t,data) == 1, "Expected data to be at byte 1");

#define DPA__U_BO_SIMPLE_MEMBERS(...) \
  union { \
    struct { \
      DPA__U_BO_META(); \
      struct __attribute__((packed)) { \
        size_t size : (sizeof(size_t)-1) * CHAR_BIT; \
      }; \
      __VA_ARGS__ void* data; \
    }; \
    DPA__U_BO_ALIGN dpa__u_bo_a_t all; \
  }

typedef struct dpa_u_bo_simple_ro {
  DPA__U_BO_SIMPLE_MEMBERS(const);
} dpa_u_bo_simple_ro_t;
static_assert(sizeof(dpa_u_bo_simple_ro_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_simple_ro_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_simple_ro_t,data) == sizeof(size_t), "Expected data to be at a different offset");

typedef struct dpa_u_bo_simple {
  union {
    dpa_u_bo_simple_ro_t ro;
    DPA__U_BO_SIMPLE_MEMBERS();
  };
} dpa_u_bo_simple_t;
static_assert(sizeof(dpa_u_bo_simple_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_simple_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_simple_t,data) == sizeof(size_t), "Expected data to be at a different offset");


////// Unique hashmap string entries, these are not meant to be used directly.
// Just use dpa_u_bo_unique_t instead

// This has, in the best case, the size of 4 size_t. In the worst case, it has the size of 6 size_t
struct dpa__u_bo_unique_hashmap_entry {
  struct dpa__u_bo_unique_hashmap_entry* next;
  dpa_u_hash_t hash;
  struct {
    size_t size : (sizeof(size_t)-1) * CHAR_BIT;
    size_t type_offset : CHAR_BIT; // >=3: entry_refcounted_2. offset is type_offset - 3. <3: see entry_inline..2
  };
  struct dpa_u_refcount_bo_unique refcount; // If the data gets referenced by another entry, the referee probably won't have to store an offset.
};
typedef struct dpa__u_bo_unique_hashmap_entry dpa__u_bo_unique_hashmap_entry_t;

struct dpa__u_bo_entry_inline {
  dpa__u_bo_unique_hashmap_entry_t entry;
  char data[];
};

struct dpa__u_bo_entry_static {
  dpa__u_bo_unique_hashmap_entry_t entry;
  const void* data;
};

struct dpa__u_bo_entry_refcounted {
  dpa__u_bo_unique_hashmap_entry_t entry;
  size_t offset;
  struct dpa_u_refcount_freeable* refcount;
};

struct dpa__u_bo_entry_refcounted_2 {
  dpa__u_bo_unique_hashmap_entry_t entry;
  struct dpa_u_refcount_freeable* refcount;
};


// This is currently just a pointer to a dpa__u_bo_unique_hashmap_entry, but it may be changed to a struct in the future, so don't rely on that.
typedef const struct dpa__u_bo_unique_hashmap_entry* dpa_u_bo_unique_hashmap_t;


enum {
  DPA__U_BO_UNIQUE__ENTRY_TYPE_INLINE,
  DPA__U_BO_UNIQUE__ENTRY_TYPE_STATIC,
  DPA__U_BO_UNIQUE__ENTRY_TYPE_REFCOUNTED,
  DPA__U_BO_UNIQUE__ENTRY_TYPE_REFCOUNTED_2,
};

typedef struct dpa_u_bo_unique {
  union {
    struct { DPA__U_BO_META(); char _[DPA__U_BO_COMMON_SIZE-1]; };
    dpa_u_bo_inline_ro_t bo_inline;
    struct { DPA__U_BO_META() bo_unique_hashmap_meta; dpa_u_bo_unique_hashmap_t bo_unique_hashmap; };
    DPA__U_BO_ALIGN dpa__u_bo_a_t all;
  };
} dpa_u_bo_unique_t;

typedef struct dpa_u_bo_ro {
  union {
    struct { DPA__U_BO_META(); char _[DPA__U_BO_COMMON_SIZE-1]; };
    dpa_u_bo_inline_ro_t bo_inline;
    dpa_u_bo_simple_ro_t bo_simple;
    struct { DPA__U_BO_META() bo_unique_hashmap_meta; dpa_u_bo_unique_hashmap_t bo_unique_hashmap; };
    dpa_u_bo_unique_t bo_unique;
    DPA__U_BO_ALIGN dpa__u_bo_a_t all;
  };
} dpa_u_bo_ro_t;
static_assert(sizeof(dpa_u_bo_ro_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_ro_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_ro_t,_) == 1, "Expected _ to be at a different offset");

typedef struct dpa_u_bo {
  union {
    struct { DPA__U_BO_META(); char _[DPA__U_BO_COMMON_SIZE-1]; };
    dpa_u_bo_ro_t ro;
    dpa_u_bo_inline_t bo_inline;
    dpa_u_bo_simple_t bo_simple;
    DPA__U_BO_ALIGN dpa__u_bo_a_t all;
  };
} dpa_u_bo_t;
static_assert(sizeof(dpa_u_bo_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_t,_) == 1, "Expected _ to be at a different offset");

DPA_U_EXPORT inline void dpa__u_bo_unique_hashmap_ref(dpa_u_bo_unique_hashmap_t bo){
  dpa_u_refcount_ref(&bo->refcount);
}

DPA_U_EXPORT inline bool dpa__u_bo_unique_hashmap_put(dpa_u_bo_unique_hashmap_t bo){
  return dpa_u_refcount_put(&bo->refcount);
}

///////////////////////////////////////////////
//////      Member access functions      //////
///////////////////////////////////////////////

#define dpa_u_bo_get_type(...) dpa_u_assert_selection(dpa_u_bo_get_type_g(__VA_ARGS__))
#define dpa_u_bo_get_type_g(X) dpa_u_generic((X), \
    dpa_u_bo_t: (enum dpa_u_bo_s_type)DPA__G(dpa_u_bo_t, (X)).type, \
    dpa_u_bo_ro_t: (enum dpa_u_bo_s_ro_type)DPA__G(dpa_u_bo_ro_t, (X)).type, \
    dpa_u_bo_inline_t: DPA_U_BO_INLINE_1, \
    dpa_u_bo_simple_t: DPA_U_BO_SIMPLE_2, \
    dpa_u_bo_simple_ro_t: DPA_U_BO_SIMPLE_2, \
    dpa_u_bo_unique_hashmap_t: DPA_U_BO_UNIQUE_HASHMAP_3, \
    dpa_u_bo_unique_t: (enum dpa_u_bo_s_unique_type)DPA__G(dpa_u_bo_unique_t, (X)).type, \
    \
          dpa_u_bo_t*: (enum dpa_u_bo_s_type)DPA__G(      dpa_u_bo_t*, (X))->type, \
    const dpa_u_bo_t*: (enum dpa_u_bo_s_type)DPA__G(const dpa_u_bo_t*, (X))->type, \
          dpa_u_bo_ro_t*: (enum dpa_u_bo_s_ro_type)DPA__G(      dpa_u_bo_ro_t*, (X))->type, \
    const dpa_u_bo_ro_t*: (enum dpa_u_bo_s_ro_type)DPA__G(const dpa_u_bo_ro_t*, (X))->type, \
          dpa_u_bo_inline_t*: DPA_U_BO_INLINE_1, \
    const dpa_u_bo_inline_t*: DPA_U_BO_INLINE_1, \
          dpa_u_bo_simple_t*: (enum dpa_u_bo_s_simple_type)DPA__G(      dpa_u_bo_simple_t*, (X))->type, \
    const dpa_u_bo_simple_t*: (enum dpa_u_bo_s_simple_type)DPA__G(const dpa_u_bo_simple_t*, (X))->type, \
          dpa_u_bo_simple_ro_t*: (enum dpa_u_bo_s_simple_ro_type)DPA__G(      dpa_u_bo_simple_ro_t*, (X))->type, \
    const dpa_u_bo_simple_ro_t*: (enum dpa_u_bo_s_simple_ro_type)DPA__G(const dpa_u_bo_simple_ro_t*, (X))->type, \
          dpa_u_bo_unique_t*: (enum dpa_u_bo_s_unique_type)DPA__G(      dpa_u_bo_unique_t*, (X))->type, \
    const dpa_u_bo_unique_t*: (enum dpa_u_bo_s_unique_type)DPA__G(const dpa_u_bo_unique_t*, (X))->type \
  )

#define dpa_u_bo_data(...) dpa_u_assert_selection(dpa_u_bo_data_g(__VA_ARGS__))
#define dpa_u_bo_data_g(X) dpa_u_generic((X), \
    DPA__GS(dpa_u_bo_inline_t,     (X)).data, \
    DPA__GS(dpa_u_bo_simple_t,     (X)).data, \
    DPA__GS(dpa_u_bo_simple_ro_t,  (X)).data, \
    dpa_u_bo_t: dpa_u_generic(&DPA__G(dpa_u_bo_t,(X)), \
            dpa_u_bo_t*: dpa__u_bo_data(&DPA__G(dpa_u_bo_t,(X))), \
      const dpa_u_bo_t*: dpa__u_cbo_data(&DPA__G(dpa_u_bo_t,(X))) \
    ), \
    dpa_u_bo_ro_t: dpa__u_bo_ro_data(&DPA__G(dpa_u_bo_ro_t,(X))), \
    dpa_u_bo_unique_hashmap_t: dpa__u_bo_unique_hashmap_get_data(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_bo_unique_t: dpa__u_bo_unique_data(&DPA__G(dpa_u_bo_unique_t,(X))), \
    \
    DPA__GS(      dpa_u_bo_inline_t*,    (X))->data, \
    DPA__GS(const dpa_u_bo_inline_t*,    (X))->data, \
    DPA__GS(      dpa_u_bo_simple_t*,    (X))->data, \
    DPA__GS(const dpa_u_bo_simple_t*,    (X))->data, \
    DPA__GS(      dpa_u_bo_simple_ro_t*, (X))->data, \
    DPA__GS(const dpa_u_bo_simple_ro_t*, (X))->data, \
          dpa_u_bo_t*: dpa__u_bo_data(DPA__G(dpa_u_bo_t*,(X))), \
    const dpa_u_bo_t*: dpa__u_cbo_data(DPA__G(const dpa_u_bo_t*,(X))), \
          dpa_u_bo_ro_t*: dpa__u_bo_ro_data(DPA__G(dpa_u_bo_ro_t*,(X))), \
    const dpa_u_bo_ro_t*: dpa__u_bo_ro_data(DPA__G(const dpa_u_bo_ro_t*,(X))), \
          dpa_u_bo_unique_t*: dpa__u_bo_unique_data(DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: dpa__u_bo_unique_data(DPA__G(const dpa_u_bo_unique_t*,(X))) \
  )

DPA_U_EXPORT inline void* dpa__u_bo_data(dpa_u_bo_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
  }
  dpa_u_abort("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline const void* dpa__u_cbo_data(const dpa_u_bo_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
  }
  dpa_u_abort("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline const void* dpa__u_bo_unique_hashmap_get_data(dpa_u_bo_unique_hashmap_t const e){
  size_t type_offset = e->type_offset;
  switch(type_offset){
    case DPA__U_BO_UNIQUE__ENTRY_TYPE_INLINE: return ((struct dpa__u_bo_entry_inline*)e)->data;
    case DPA__U_BO_UNIQUE__ENTRY_TYPE_STATIC: return ((struct dpa__u_bo_entry_static*)e)->data;
    case DPA__U_BO_UNIQUE__ENTRY_TYPE_REFCOUNTED: {
      const struct dpa__u_bo_entry_refcounted*const t = (const struct dpa__u_bo_entry_refcounted*const)e;
      return ((char*)(t->refcount+1)) + t->offset;
    }
  }
  return ((char*)(((struct dpa__u_bo_entry_refcounted_2*)e)->refcount+1)) + (type_offset - DPA__U_BO_UNIQUE__ENTRY_TYPE_REFCOUNTED_2);
}
DPA_U_EXPORT inline const void* dpa__u_bo_ro_data(const dpa_u_bo_ro_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
    case DPA_U_BO_UNIQUE_HASHMAP: return dpa__u_bo_unique_hashmap_get_data(bo->bo_unique_hashmap);
  }
  dpa_u_abort("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline const void* dpa__u_bo_unique_data(const dpa_u_bo_unique_t*restrict const bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return bo->bo_inline.data;
    case DPA_U_BO_UNIQUE_HASHMAP: return dpa__u_bo_unique_hashmap_get_data(bo->bo_unique_hashmap);
  }
  dpa_u_abort("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

#define dpa_u_bo_set_size(...) dpa_u_assert_selection(dpa_u_bo_set_size_g(__VA_ARGS__))
#define dpa_u_bo_set_size_g(X,S) ((void)dpa_u_generic((X), \
    dpa_u_bo_inline_t   : (assert((S) <= DPA_U_BO_INLINE_MAX_SIZE),(DPA__G(dpa_u_bo_inline_t,(X)).size=(S)&0xF)), \
    dpa_u_bo_simple_t   : (assert((S) <= DPA_U_BO_MAX_SIZE       ),(DPA__G(dpa_u_bo_simple_t,(X)).size=(S))), \
    dpa_u_bo_t: dpa__u_bo_set_size(&DPA__G(dpa_u_bo_t,(X)),(S)), \
    \
    dpa_u_bo_inline_t*   : (assert((S) <= DPA_U_BO_INLINE_MAX_SIZE),(DPA__G(dpa_u_bo_inline_t*,(X)).size=(S)&0xF)), \
    dpa_u_bo_simple_t*   : (assert((S) <= DPA_U_BO_MAX_SIZE       ),(DPA__G(dpa_u_bo_simple_t*,(X)).size=(S))), \
    dpa_u_bo_t*: dpa__u_bo_set_size(DPA__G(dpa_u_bo_t*,(X)),(S)) \
  ))

DPA_U_EXPORT inline void dpa__u_bo_set_size(dpa_u_bo_t*restrict const bo, size_t size){
  switch(bo->type){
    case DPA_U_BO_INLINE: {
      assert(size <= DPA_U_BO_INLINE_MAX_SIZE);
      bo->bo_inline.size = size;
    } return;
    case DPA_U_BO_SIMPLE: {
      bo->bo_simple.size = size;
    } return;
    case DPA_U_BO_UNIQUE_HASHMAP: break;
  }
  dpa_u_abort("Can't set size on bo of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

DPA_U_EXPORT inline size_t dpa__u_bo_unique_hashmap_get_size(dpa_u_bo_unique_hashmap_t  bo){
  return bo->size;
}

#define dpa_u_bo_get_size(...) dpa_u_assert_selection(dpa_u_bo_get_size_g(__VA_ARGS__))
#define dpa_u_bo_get_size_g(X) ((size_t)dpa_u_generic((X), \
    DPA__GS(dpa_u_bo_inline_t,(X)).size, \
    DPA__GS(dpa_u_bo_simple_t,(X)).size, \
    DPA__GS(dpa_u_bo_simple_ro_t,(X)).size, \
    dpa_u_bo_t: dpa__u_bo_get_size(DPA__G(dpa_u_bo_t, (X))), \
    dpa_u_bo_ro_t: dpa__u_bo_ro_get_size(DPA__G(dpa_u_bo_ro_t, (X))), \
    dpa_u_bo_unique_hashmap_t: dpa__u_bo_unique_hashmap_get_size(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    dpa_u_bo_unique_t: dpa__u_bo_unique_get_size(DPA__G(dpa_u_bo_unique_t, (X))), \
    \
    DPA__GS(      dpa_u_bo_inline_t*,(X))->size, \
    DPA__GS(const dpa_u_bo_inline_t*,(X))->size, \
    DPA__GS(      dpa_u_bo_simple_t*,(X))->size, \
    DPA__GS(const dpa_u_bo_simple_t*,(X))->size, \
    DPA__GS(      dpa_u_bo_simple_ro_t*,(X))->size, \
    DPA__GS(const dpa_u_bo_simple_ro_t*,(X))->size, \
          dpa_u_bo_t*: dpa__u_bo_get_size(*DPA__G(dpa_u_bo_t*, (X))), \
    const dpa_u_bo_t*: dpa__u_bo_get_size(*DPA__G(const dpa_u_bo_t*, (X))), \
          dpa_u_bo_ro_t*: dpa__u_bo_ro_get_size(*DPA__G(dpa_u_bo_ro_t*, (X))), \
    const dpa_u_bo_ro_t*: dpa__u_bo_ro_get_size(*DPA__G(const dpa_u_bo_ro_t*, (X))), \
          dpa_u_bo_unique_t*: dpa__u_bo_unique_get_size(*DPA__G(dpa_u_bo_unique_t*, (X))), \
    const dpa_u_bo_unique_t*: dpa__u_bo_unique_get_size(*DPA__G(const dpa_u_bo_unique_t*, (X))) \
  ))

DPA_U_EXPORT inline size_t dpa__u_bo_get_size(const dpa_u_bo_t bo){
  switch(bo.type){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_SIMPLE: return bo.bo_simple.size;
    case DPA_U_BO_UNIQUE_HASHMAP: break;
  }
  dpa_u_abort("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline size_t dpa__u_bo_ro_get_size(const dpa_u_bo_ro_t bo){
  switch(bo.type){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_SIMPLE: return bo.bo_simple.size;
    case DPA_U_BO_UNIQUE_HASHMAP: return dpa__u_bo_unique_hashmap_get_size(bo.bo_unique_hashmap);
  }
  dpa_u_abort("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
DPA_U_EXPORT inline size_t dpa__u_bo_unique_get_size(const dpa_u_bo_unique_t bo){
  switch(bo.type){
    case DPA_U_BO_INLINE: return bo.bo_inline.size;
    case DPA_U_BO_SIMPLE: break;
    case DPA_U_BO_UNIQUE_HASHMAP: return dpa__u_bo_unique_hashmap_get_size(bo.bo_unique_hashmap);
  }
  dpa_u_abort("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}
#undef X

/////////////////////////////////////////
//////      Conversion macros      //////
/////////////////////////////////////////

#define dpa_u_v_bo_unique(...) dpa_u_assert_selection(dpa_u_v_bo_unique_g(__VA_ARGS__))
#define dpa_u_v_bo_unique_g(X) dpa_u_generic((X), \
    dpa_u_bo_unique_hashmap_t: (const dpa_u_bo_unique_t){ .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, .bo_unique_hashmap = DPA__G(dpa_u_bo_unique_hashmap_t, (X)) }, \
    DPA__GS(dpa_u_bo_unique_t, (X)), \
    dpa_u_bo_inline_t*: (const dpa_u_bo_unique_t){ .bo_inline = *DPA__G(dpa_u_bo_inline_t*, (X)) }, \
    const dpa_u_bo_inline_t*: (const dpa_u_bo_unique_t){ .bo_inline = *DPA__G(const dpa_u_bo_inline_t*, (X)) }, \
    DPA__GS(dpa_u_bo_unique_t*, (X))[0], \
    DPA__GS(const dpa_u_bo_unique_t*, (X))[0] \
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
    const dpa_u_bo_inline_t*: (const dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(const dpa_u_bo_inline_t*,(X))), .data=dpa_u_bo_data(DPA__G(const dpa_u_bo_inline_t*,(X))) }, \
    dpa_u_bo_t*: (const dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_t*,(X))) }, \
    const dpa_u_bo_t*: (const dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(const dpa_u_bo_t*,(X))), .data=dpa_u_bo_data(DPA__G(const dpa_u_bo_t*,(X))) } \
  )

/**
 * Note: If the source buffer was a DPA_U_BO_INLINE (which can also be the case for dpa_u_bo_t and dpa_u_bo_ro_t too),
 * then the lifetime will not exceed the source BOs scope! It's fine for passing to other functions, but not for much else.
 */
#define dpa_u_temp_bo_simple_ro(...) dpa_u_assert_selection(dpa_u_temp_bo_simple_ro_g(__VA_ARGS__))
#define dpa_u_temp_bo_simple_ro_g(X) dpa_u_generic((X), \
    DPA__GS(dpa_u_bo_simple_t, (X)).ro, \
    DPA__GS(dpa_u_bo_simple_ro_t, (X)), \
    dpa_u_bo_inline_t: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_inline_t,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_inline_t,(X))) }, \
    dpa_u_bo_t: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_t,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_t,(X))) }, \
    dpa_u_bo_ro_t: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_ro_t,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_ro_t,(X))) }, \
    dpa_u_bo_unique_hashmap_t: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_unique_hashmap_t,(X))) }, \
    dpa_u_bo_unique_t: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_unique_t,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_unique_t,(X))) }, \
    \
    DPA__GS(dpa_u_bo_simple_t*, (X))->ro, \
    DPA__GS(const dpa_u_bo_simple_t*, (X))->ro, \
    DPA__GS(dpa_u_bo_simple_ro_t*, (X))[0], \
    DPA__GS(const dpa_u_bo_simple_ro_t*, (X))[0], \
    dpa_u_bo_inline_t*: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_inline_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_inline_t*,(X))) }, \
    const dpa_u_bo_inline_t*: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(const dpa_u_bo_inline_t*,(X))), .data=dpa_u_bo_data(DPA__G(const dpa_u_bo_inline_t*,(X))) }, \
    dpa_u_bo_t*: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_t*,(X))) }, \
    const dpa_u_bo_t*: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(const dpa_u_bo_t*,(X))), .data=dpa_u_bo_data(DPA__G(const dpa_u_bo_t*,(X))) }, \
    dpa_u_bo_ro_t*: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_ro_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_ro_t*,(X))) }, \
    const dpa_u_bo_ro_t*: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(const dpa_u_bo_ro_t*,(X))), .data=dpa_u_bo_data(DPA__G(const dpa_u_bo_ro_t*,(X))) }, \
    dpa_u_bo_unique_t*: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_unique_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_unique_t*,(X))) }, \
    const dpa_u_bo_unique_t*: (const dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(const dpa_u_bo_unique_t*,(X))), .data=dpa_u_bo_data(DPA__G(const dpa_u_bo_unique_t*,(X))) } \
  )

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
    dpa_u_bo_simple_t*: (const dpa_u_bo_ro_t){ .bo_simple = DPA__G(dpa_u_bo_simple_t*, (X))->ro }, \
    const dpa_u_bo_simple_t*: (const dpa_u_bo_ro_t){ .bo_simple = DPA__G(const dpa_u_bo_simple_t*, (X))->ro }, \
    dpa_u_bo_simple_ro_t*: (const dpa_u_bo_ro_t){ .bo_simple = *DPA__G(dpa_u_bo_simple_ro_t*, (X)) }, \
    const dpa_u_bo_simple_ro_t*: (const dpa_u_bo_ro_t){ .bo_simple = *DPA__G(const dpa_u_bo_simple_ro_t*, (X)) }, \
    dpa_u_bo_unique_t*: (const dpa_u_bo_ro_t){ .bo_unique = *DPA__G(dpa_u_bo_unique_t*, (X)) }, \
    const dpa_u_bo_unique_t*: (const dpa_u_bo_ro_t){ .bo_unique = *DPA__G(const dpa_u_bo_unique_t*, (X)) } \
  )

DPA_U_EXPORT dpa_u_bo_unique_hashmap_t dpa__u_bo_do_intern(const dpa_u_bo_ro_t* bo);

DPA_U_EXPORT inline dpa_u_bo_unique_t dpa__u_bo_intern(const dpa_u_bo_ro_t*const bo){
  // We allow the simple cases to be inlined, and the complicated one is handled in dpa__u_bo_do_intern instead
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE:
      return (dpa_u_bo_unique_t){ .bo_inline = bo->bo_inline };
    case DPA_U_BO_UNIQUE_HASHMAP:
      dpa__u_bo_unique_hashmap_ref(bo->bo_unique_hashmap);
      return bo->bo_unique;
    default: {
      if(dpa_u_bo_get_size(bo) <= DPA_U_BO_INLINE_MAX_SIZE){
        dpa_u_bo_inline_t boi = {
          .type = DPA_U_BO_INLINE,
          .size = dpa_u_bo_get_size(bo),
        };
        memcpy(boi.data, dpa_u_bo_data(bo), dpa_u_bo_get_size(bo));
        return (dpa_u_bo_unique_t){ .bo_inline = boi };
      }
      return (dpa_u_bo_unique_t){
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP,
        .bo_unique_hashmap = dpa__u_bo_do_intern(bo),
      };
    }
  }
}

DPA_U_EXPORT inline void dpa__u_bo_unique_ref(dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_UNIQUE_HASHMAP: dpa__u_bo_unique_hashmap_ref(ubo.bo_unique_hashmap); return;
    case DPA_U_BO_INLINE: return;
  }
  dpa_u_abort("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(ubo)));
}

DPA_U_EXPORT inline bool dpa__u_bo_unique_put(dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return dpa__u_bo_unique_hashmap_put(ubo.bo_unique_hashmap);
    case DPA_U_BO_INLINE: return false;
  }
  dpa_u_abort("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(ubo)));
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
    \
    dpa_u_bo_unique_hashmap_t: dpa__u_bo_unique_hashmap_ref(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    \
    dpa_u_bo_unique_t: dpa__u_bo_unique_ref(DPA__G(dpa_u_bo_unique_t,(X))), \
    dpa_u_bo_unique_t*: dpa__u_bo_unique_ref(*DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: dpa__u_bo_unique_ref(*DPA__G(const dpa_u_bo_unique_t*,(X))) \
  )

#define dpa_u_bo_put(...) dpa_u_assert_selection(dpa_u_bo_put_g(__VA_ARGS__))
#define dpa_u_bo_put_g(X) dpa_u_generic((X), \
    dpa_u_bo_inline_t: (void)0, \
    dpa_u_bo_inline_t*: (void)0, \
    const dpa_u_bo_inline_t*: (void)0, \
    \
    dpa_u_bo_unique_hashmap_t: dpa__u_bo_unique_hashmap_put(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    \
    dpa_u_bo_unique_t: dpa__u_bo_unique_put(DPA__G(dpa_u_bo_unique_t,(X))), \
    dpa_u_bo_unique_t*: dpa__u_bo_unique_put(*DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: dpa__u_bo_unique_put(*DPA__G(const dpa_u_bo_unique_t*,(X))) \
  )

DPA_U_EXPORT inline struct dpa_u_refcount_freeable* dpa__u_bo_unique_get_refcount(const dpa_u_bo_unique_t ubo){
  switch(dpa_u_bo_get_type(ubo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (struct dpa_u_refcount_freeable*)&ubo.bo_unique_hashmap->refcount.freeable;
    case DPA_U_BO_INLINE: return &dpa_u_refcount_static_v_freeable;
  }
  dpa_u_abort("dpa_u_bo_unique_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(ubo)));
}

DPA_U_EXPORT inline struct dpa_u_refcount_freeable* dpa__u_bo_ro_p_get_refcount(const dpa_u_bo_ro_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (struct dpa_u_refcount_freeable*)&bo->bo_unique_hashmap->refcount.freeable;
    case DPA_U_BO_INLINE: return &dpa_u_refcount_static_v_freeable;
    case DPA_U_BO_SIMPLE: return 0;
  }
  dpa_u_abort("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

DPA_U_EXPORT inline struct dpa_u_refcount_freeable* dpa__u_bo_ro_get_refcount(const dpa_u_bo_ro_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_UNIQUE_HASHMAP: return (struct dpa_u_refcount_freeable*)&bo.bo_unique_hashmap->refcount.freeable;
    case DPA_U_BO_INLINE: return &dpa_u_refcount_static_v_freeable;
    case DPA_U_BO_SIMPLE: return 0;
  }
  dpa_u_abort("dpa_u_bo_ro_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

DPA_U_EXPORT inline struct dpa_u_refcount_freeable* dpa__u_bo_p_get_refcount(const dpa_u_bo_t* bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return &dpa_u_refcount_static_v_freeable;
    case DPA_U_BO_SIMPLE: return 0;
  }
  dpa_u_abort("dpa_u_bo_t can't be of type %s", dpa_u_enum_get_name(dpa_u_bo_type, dpa_u_bo_get_type(bo)));
}

#define dpa__u_bo_unique_hashmap_get_refcount(X) ((struct dpa_u_refcount_freeable*)&(X)->refcount.freeable)

#define dpa_u_bo_get_refcount(...) dpa_u_assert_selection(dpa_u_bo_get_refcount_g(__VA_ARGS__))
#define dpa_u_bo_get_refcount_g(X) dpa_u_generic((X), \
    dpa_u_bo_ro_t: dpa__u_bo_ro_get_refcount(DPA__G(dpa_u_bo_ro_t,(X))), \
    dpa_u_bo_inline_t: &dpa_u_refcount_static_v_freeable, \
    dpa_u_bo_unique_t: dpa__u_bo_unique_get_refcount(DPA__G(dpa_u_bo_unique_t,(X))), \
    dpa_u_bo_unique_hashmap_t: dpa__u_bo_unique_hashmap_get_refcount(DPA__G(dpa_u_bo_unique_hashmap_t,(X))), \
    \
          dpa_u_bo_unique_t*: dpa__u_bo_unique_get_refcount(*DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: dpa__u_bo_unique_get_refcount(*DPA__G(const dpa_u_bo_unique_t*,(X))), \
          dpa_u_bo_inline_t*: &dpa_u_refcount_static_v_freeable, \
    const dpa_u_bo_inline_t*: &dpa_u_refcount_static_v_freeable, \
          dpa_u_bo_ro_t*: dpa__u_bo_ro_p_get_refcount(DPA__G(dpa_u_bo_ro_t*,(X))), \
    const dpa_u_bo_ro_t*: dpa__u_bo_ro_p_get_refcount(DPA__G(const dpa_u_bo_ro_t*,(X))), \
          dpa_u_bo_t*: dpa__u_bo_p_get_refcount(DPA__G(dpa_u_bo_t*,(X))), \
    const dpa_u_bo_t*: dpa__u_bo_p_get_refcount(DPA__G(const dpa_u_bo_t*,(X))) \
  )

/**
 * Interns a buffer. The refcount of the buffer will be increased.
 * \returns dpa_u_bo_unique_t
 */
#define dpa_u_bo_intern(...) dpa_u_assert_selection(dpa_u_bo_intern_g(__VA_ARGS__))
#define dpa_u_bo_intern_g(X) _Generic((X), \
    dpa_u_bo_inline_t: (const dpa_u_bo_unique_t){ .bo_inline = DPA__G(dpa_u_bo_inline_t, (X)) }, \
    dpa_u_bo_inline_t*: (const dpa_u_bo_unique_t){ .bo_inline = DPA__G(dpa_u_bo_inline_t, (X)) }, \
    const dpa_u_bo_inline_t*: (const dpa_u_bo_unique_t){ .bo_inline = DPA__G(dpa_u_bo_inline_t, (X)) }, \
    \
    dpa_u_bo_unique_hashmap_t: (dpa__u_bo_unique_hashmap_ref(DPA__G(dpa_u_bo_unique_hashmap_t,(X))),(const dpa_u_bo_unique_t){ .bo_unique_hashmap = DPA__G(dpa_u_bo_unique_hashmap_t,(X)) }), \
    \
    dpa_u_bo_unique_t: (dpa__u_bo_unique_ref(DPA__G(dpa_u_bo_unique_t,(X))),(X)), \
    dpa_u_bo_unique_t*: (dpa__u_bo_unique_ref(*DPA__G(dpa_u_bo_unique_t*,(X))),*DPA__G(dpa_u_bo_unique_t*,(X))), \
    const dpa_u_bo_unique_t*: (dpa__u_bo_unique_ref(*DPA__G(const dpa_u_bo_unique_t*,(X))),*DPA__G(const dpa_u_bo_unique_t*,(X))), \
    \
    default: dpa_u_generic_if_selection( dpa_u_p_bo_ro_g(X), dpa__u_bo_intern(DPA__G(dpa_u_bo_ro_t,dpa_u_v_bo_ro_g(X))) ) \
  )

#endif
