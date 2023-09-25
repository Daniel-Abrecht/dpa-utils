#ifndef DPA_UTILS_BO_H
#define DPA_UTILS_BO_H

#include <dpa/utils/common.h>

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

enum dpa_u_bo_type {
  DPA_U_BO_INLINE,
  DPA_U_BO_SIMPLE,
  DPA_U_BO_UNIQUE,
};

#define DPA__U_BO_META(...) \
  struct __attribute__((packed)) { \
    enum dpa_u_bo_type type : CHAR_BIT - 4; \
    unsigned __VA_ARGS__ : 4; \
  }

typedef struct { char all[DPA__U_BO_COMMON_SIZE]; } dpa__u_bo_a_t;

typedef struct {
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

typedef const struct dpa__u_bo_simple_ro {
  DPA__U_BO_SIMPLE_MEMBERS(const);
} dpa_u_bo_simple_ro_t;
static_assert(sizeof(dpa_u_bo_simple_ro_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_simple_ro_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_simple_ro_t,data) == sizeof(size_t), "Expected data to be at a different offset");

typedef struct {
  union {
    dpa_u_bo_simple_ro_t ro;
    DPA__U_BO_SIMPLE_MEMBERS();
  };
} dpa_u_bo_simple_t;
static_assert(sizeof(dpa_u_bo_simple_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_simple_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_simple_t,data) == sizeof(size_t), "Expected data to be at a different offset");

enum {
  DPA_U_BO_UNIQUE__HASH_BITS = (sizeof(size_t)-1)*CHAR_BIT,
  DPA_U_BO_UNIQUE__ID_BITS = sizeof(void*)*CHAR_BIT / 4,
  DPA_U_BO_UNIQUE__SIZE_BITS = sizeof(void*)*CHAR_BIT - DPA_U_BO_UNIQUE__ID_BITS,
};

typedef const struct dpa__u_bo_unique {
  union {
    struct {
      DPA__U_BO_META();
      struct __attribute__((packed)) {
        size_t hash : DPA_U_BO_UNIQUE__HASH_BITS;
        size_t size : DPA_U_BO_UNIQUE__SIZE_BITS;
        size_t id   : DPA_U_BO_UNIQUE__ID_BITS;
      };
    };
    DPA__U_BO_ALIGN dpa__u_bo_a_t all;
  };
} dpa_u_bo_unique_t;
static_assert(sizeof(dpa_u_bo_unique_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_unique_t has an unexpected size");

DPA_U_EXPORT const void* dpa__u_bo_unique_get_data(dpa_u_bo_unique_t bo);
DPA_U_EXPORT void dpa__u_bo_unique_ref(dpa_u_bo_unique_t bo);
DPA_U_EXPORT bool dpa__u_bo_unique_put(dpa_u_bo_unique_t bo);

typedef const struct dpa__u_bo_any_unique {
  union {
    struct { DPA__U_BO_META(); char _[DPA__U_BO_COMMON_SIZE-1]; };
    const dpa_u_bo_inline_t bo_inline;
    dpa_u_bo_unique_t bo_unique;
    DPA__U_BO_ALIGN dpa__u_bo_a_t all;
  };
} dpa_u_bo_any_unique_t;

typedef const struct dpa__u_bo_ro {
  union {
    struct { DPA__U_BO_META(); char _[DPA__U_BO_COMMON_SIZE-1]; };
    const dpa_u_bo_inline_t bo_inline;
    dpa_u_bo_simple_ro_t bo_simple;
    dpa_u_bo_unique_t bo_unique;
    dpa_u_bo_any_unique_t bo_any_unique;
    DPA__U_BO_ALIGN dpa__u_bo_a_t all;
  };
} dpa_u_bo_ro_t;
static_assert(sizeof(dpa_u_bo_ro_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_ro_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_ro_t,_) == 1, "Expected _ to be at a different offset");

typedef struct {
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


///////////////////////////////////////////////
//////      Member access functions      //////
///////////////////////////////////////////////

#define dpa_u_bo_data(X) _Generic((X), \
    DPA__GS(       dpa_u_bo_inline_t,     (X)).data, \
    DPA__GS(       dpa_u_bo_simple_t,     (X)).data, \
    DPA__GS(struct dpa__u_bo_simple_ro,  (X)).data, \
    dpa_u_bo_t: _Generic(&DPA__G(dpa_u_bo_t,(X)), \
            dpa_u_bo_t*: dpa__u_bo_data(&DPA__G(dpa_u_bo_t,(X))), \
      const dpa_u_bo_t*: dpa__u_cbo_data(&DPA__G(dpa_u_bo_t,(X))) \
    ), \
    struct dpa__u_bo_ro: dpa__u_bo_ro_data(&DPA__G(struct dpa__u_bo_ro,(X))), \
    struct dpa__u_bo_unique: dpa__u_bo_unique_get_data(DPA__G(struct dpa__u_bo_unique,(X))), \
    \
    DPA__GS(      dpa_u_bo_inline_t*,    (X))->data, \
    DPA__GS(const dpa_u_bo_inline_t*,    (X))->data, \
    DPA__GS(      dpa_u_bo_simple_t*,    (X))->data, \
    DPA__GS(const dpa_u_bo_simple_t*,    (X))->data, \
    DPA__GS(      dpa_u_bo_simple_ro_t*, (X))->data, \
          dpa_u_bo_t*: dpa__u_bo_data(DPA__G(dpa_u_bo_t*,(X))), \
    const dpa_u_bo_t*: dpa__u_cbo_data(DPA__G(const dpa_u_bo_t*,(X))), \
          dpa_u_bo_ro_t*: dpa__u_bo_ro_data(DPA__G(dpa_u_bo_ro_t*,(X))), \
          dpa_u_bo_unique_t*: dpa__u_bo_unique_get_data(*DPA__G(dpa_u_bo_unique_t*,(X))) \
  )

#define Y \
  case DPA_U_BO_INLINE: return bo->bo_inline.data; \
  case DPA_U_BO_SIMPLE: return bo->bo_simple.data;
#define X \
  switch(bo->type){ Y case DPA_U_BO_UNIQUE: break; } \
  abort();
static inline void* dpa__u_bo_data(dpa_u_bo_t*restrict const bo){ X }
static inline const void* dpa__u_cbo_data(const dpa_u_bo_t*restrict const bo){ X }
static inline const void* dpa__u_bo_ro_data(dpa_u_bo_ro_t*restrict const bo){
  switch(bo->type){ Y
    case DPA_U_BO_UNIQUE: return dpa__u_bo_unique_get_data(bo->bo_unique);
  }
  abort();
}
#undef X
#undef Y

#define dpa_u_bo_set_size(X,S) ((void)_Generic((X), \
    dpa_u_bo_inline_t   : (assert((S) <= DPA_U_BO_INLINE_MAX_SIZE),(DPA__G(dpa_u_bo_inline_t,(X)).size=(S)&0xF)), \
    dpa_u_bo_simple_t   : (assert((S) <= DPA_U_BO_MAX_SIZE       ),(DPA__G(dpa_u_bo_simple_t,(X)).size=(S))), \
    dpa_u_bo_t: dpa__u_bo_set_size(&DPA__G(dpa_u_bo_t,(X)),(S)), \
    \
    dpa_u_bo_inline_t*   : (assert((S) <= DPA_U_BO_INLINE_MAX_SIZE),(DPA__G(dpa_u_bo_inline_t*,(X)).size=(S)&0xF)), \
    dpa_u_bo_simple_t*   : (assert((S) <= DPA_U_BO_MAX_SIZE       ),(DPA__G(dpa_u_bo_simple_t*,(X)).size=(S))), \
    dpa_u_bo_t*: dpa__u_bo_set_size(DPA__G(dpa_u_bo_t*,(X)),(S)) \
  ))

static inline void dpa__u_bo_set_size(dpa_u_bo_t*restrict const bo, size_t size){
  switch(bo->type){
    case DPA_U_BO_INLINE: {
      assert(size <= DPA_U_BO_INLINE_MAX_SIZE);
      bo->bo_inline.size = size;
    } return;
    case DPA_U_BO_SIMPLE: {
      bo->bo_simple.size = size;
    } return;
    case DPA_U_BO_UNIQUE: break;
  }
  abort();
}

#define dpa_u_bo_get_size(X) ((size_t)_Generic((X), \
    DPA__GS(       dpa_u_bo_inline_t,(X)).size, \
    DPA__GS(       dpa_u_bo_simple_t,(X)).size, \
    DPA__GS(struct dpa__u_bo_simple_ro,(X)).size, \
    DPA__GS(struct dpa__u_bo_unique, (X)).size, \
           dpa_u_bo_t: dpa__u_bo_get_size(DPA__G(dpa_u_bo_t, (X))), \
    struct dpa__u_bo_ro: dpa__u_bo_ro_get_size(DPA__G(struct dpa__u_bo_ro, (X))), \
    \
    DPA__GS(      dpa_u_bo_inline_t*,(X))->size, \
    DPA__GS(const dpa_u_bo_inline_t*,(X))->size, \
    DPA__GS(      dpa_u_bo_simple_t*,(X))->size, \
    DPA__GS(const dpa_u_bo_simple_t*,(X))->size, \
    DPA__GS(      dpa_u_bo_simple_ro_t*,(X))->size, \
    DPA__GS(      dpa_u_bo_unique_t*,(X))->size, \
          dpa_u_bo_t*: dpa__u_bo_get_size(*DPA__G(dpa_u_bo_t*, (X))), \
    const dpa_u_bo_t*: dpa__u_bo_get_size(*DPA__G(const dpa_u_bo_t*, (X))), \
          dpa_u_bo_ro_t*: dpa__u_bo_ro_get_size(*DPA__G(dpa_u_bo_ro_t*, (X))) \
  ))

#define X \
  case DPA_U_BO_INLINE: return bo.bo_inline.size; \
  case DPA_U_BO_SIMPLE: return bo.bo_simple.size;
static inline size_t dpa__u_bo_get_size(const dpa_u_bo_t bo){
  switch(bo.type){ X
    case DPA_U_BO_UNIQUE: break;
  }
  abort();
}
static inline size_t dpa__u_bo_ro_get_size(dpa_u_bo_ro_t bo){
  switch(bo.type){ X
    case DPA_U_BO_UNIQUE: return bo.bo_unique.size;
  }
  abort();
}
#undef X

#define dpa_u_bo_get_type(X) ((const enum dpa_u_bo_type)_Generic((X), \
    DPA__GS(       dpa_u_bo_t, (X)).type, \
    DPA__GS(struct dpa__u_bo_ro, (X)).type, \
    DPA__GS(       dpa_u_bo_inline_t, (X)).type, \
    DPA__GS(       dpa_u_bo_simple_t, (X)).type, \
    DPA__GS(struct dpa__u_bo_simple_ro, (X)).type, \
    \
    DPA__GS(      dpa_u_bo_t*, (X))->type, \
    DPA__GS(const dpa_u_bo_t*, (X))->type, \
    DPA__GS(      dpa_u_bo_ro_t*, (X))->type, \
    DPA__GS(      dpa_u_bo_inline_t*, (X))->type, \
    DPA__GS(const dpa_u_bo_inline_t*, (X))->type, \
    DPA__GS(      dpa_u_bo_simple_t*, (X))->type, \
    DPA__GS(const dpa_u_bo_simple_t*, (X))->type, \
    DPA__GS(      dpa_u_bo_simple_ro_t*, (X))->type \
  ))

/////////////////////////////////////////
//////      Conversion macros      //////
/////////////////////////////////////////

#define dpa_u_v_bo_any_unique(X) _Generic((X), \
    dpa_u_bo_inline_t: (dpa_u_bo_any_unique_t){ .bo_inline = DPA__G(dpa_u_bo_inline_t, (X)) }, \
    struct dpa__u_bo_unique: (dpa_u_bo_any_unique_t){ .bo_unique = DPA__G(struct dpa__u_bo_unique, (X)) }, \
    struct dpa__u_bo_any_unique: (X) \
  )

/**
 * Note: If the source buffer was a DPA_U_BO_INLINE (which can also be the case for dpa_u_bo_t too),
 * then the lifetime will not exceed the source BOs scope! It's fine for passing to other functions,
 * but not for much else.
 */
#define dpa_u_temp_bo_simple(X) _Generic((X), \
    DPA__GS(dpa_u_bo_simple_t, (X)), \
    dpa_u_bo_inline_t: (dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_inline_t,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_inline_t,(X))) }, \
    dpa_u_bo_t: (dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_t,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_t,(X))) }, \
    \
    DPA__GS(dpa_u_bo_simple_t*, (X))[0], \
    DPA__GS(const dpa_u_bo_simple_t*, (X))[0], \
    dpa_u_bo_inline_t*: (dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_inline_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_inline_t*,(X))) }, \
    const dpa_u_bo_inline_t*: (dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(const dpa_u_bo_inline_t*,(X))), .data=dpa_u_bo_data(DPA__G(const dpa_u_bo_inline_t*,(X))) }, \
    dpa_u_bo_t*: (dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_t*,(X))) }, \
    const dpa_u_bo_t*: (dpa_u_bo_simple_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(const dpa_u_bo_t*,(X))), .data=dpa_u_bo_data(DPA__G(const dpa_u_bo_t*,(X))) } \
  )

/**
 * Note: If the source buffer was a DPA_U_BO_INLINE (which can also be the case for dpa_u_bo_t and dpa_u_bo_ro_t too),
 * then the lifetime will not exceed the source BOs scope! It's fine for passing to other functions, but not for much else.
 */
#define dpa_u_temp_bo_simple_ro(X) _Generic((X), \
    DPA__GS(dpa_u_bo_simple_t, (X)).ro, \
    DPA__GS(dpa_u_bo_simple_ro_t, (X)), \
    dpa_u_bo_inline_t: (dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_inline_t,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_inline_t,(X))) }, \
    dpa_u_bo_t: (dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_t,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_t,(X))) }, \
    struct dpa__u_bo_ro: (dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(struct dpa__u_bo_ro,(X))), .data=dpa_u_bo_data(DPA__G(struct dpa__u_bo_ro,(X))) }, \
    struct dpa__u_bo_unique: (dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(struct dpa__u_bo_unique,(X))), .data=dpa_u_bo_data(DPA__G(struct dpa__u_bo_unique,(X))) }, \
    \
    DPA__GS(dpa_u_bo_simple_t*, (X))->ro, \
    DPA__GS(const dpa_u_bo_simple_t*, (X))->ro, \
    DPA__GS(dpa_u_bo_simple_ro_t*, (X))[0], \
    dpa_u_bo_inline_t*: (dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_inline_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_inline_t*,(X))) }, \
    const dpa_u_bo_inline_t*: (dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(const dpa_u_bo_inline_t*,(X))), .data=dpa_u_bo_data(DPA__G(const dpa_u_bo_inline_t*,(X))) }, \
    dpa_u_bo_t*: (dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_t*,(X))) }, \
    const dpa_u_bo_t*: (dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(const dpa_u_bo_t*,(X))), .data=dpa_u_bo_data(DPA__G(const dpa_u_bo_t*,(X))) }, \
    dpa_u_bo_ro_t*: (dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_ro_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_ro_t*,(X))) }, \
    dpa_u_bo_unique_t*: (dpa_u_bo_simple_ro_t){ .type = DPA_U_BO_SIMPLE, .size=dpa_u_bo_get_size(DPA__G(dpa_u_bo_unique_t*,(X))), .data=dpa_u_bo_data(DPA__G(dpa_u_bo_unique_t*,(X))) } \
  )

DPA_U_EXPORT dpa_u_bo_unique_t dpa__u_bo_do_intern(dpa_u_bo_simple_ro_t bo);

static inline dpa_u_bo_any_unique_t dpa__u_bo_intern(dpa_u_bo_ro_t bo){
  switch(dpa_u_bo_get_type(bo)){
    case DPA_U_BO_INLINE: return (dpa_u_bo_any_unique_t){ .bo_inline = bo.bo_inline };
    case DPA_U_BO_UNIQUE: return (dpa_u_bo_any_unique_t){ .bo_unique = bo.bo_unique };
    default: {
      if(dpa_u_bo_get_size(bo) <= DPA_U_BO_INLINE_MAX_SIZE){
        dpa_u_bo_inline_t boi = {
          .type = DPA_U_BO_INLINE,
          .size = dpa_u_bo_get_size(bo),
        };
        memcpy(boi.data, dpa_u_bo_data(bo), dpa_u_bo_get_size(bo));
        return (dpa_u_bo_any_unique_t){ .bo_inline = boi };
      }
      return (dpa_u_bo_any_unique_t){ .bo_unique = dpa__u_bo_do_intern(dpa_u_temp_bo_simple_ro(bo)) };
    }
  }
}

#define dpa_u_v_bo_ro(X) _Generic((X), \
    DPA__GS(dpa_u_bo_t, (X)).ro, \
    DPA__GS(struct dpa__u_bo_ro, (X)), \
    dpa_u_bo_inline_t: (dpa_u_bo_ro_t){ .bo_inline = DPA__G(dpa_u_bo_inline_t, (X)) }, \
    dpa_u_bo_simple_t: (dpa_u_bo_ro_t){ .bo_simple = DPA__G(dpa_u_bo_simple_t, (X)).ro }, \
    struct dpa__u_bo_simple_ro: (dpa_u_bo_ro_t){ .bo_simple = DPA__G(struct dpa__u_bo_simple_ro, (X)) }, \
    struct dpa__u_bo_unique: (dpa_u_bo_ro_t){ .bo_unique = DPA__G(struct dpa__u_bo_unique, (X)) }, \
    struct dpa__u_bo_any_unique: (dpa_u_bo_ro_t){ .bo_any_unique = DPA__G(struct dpa__u_bo_any_unique, (X)) }, \
    \
    DPA__GS(dpa_u_bo_t*, (X))->ro, \
    DPA__GS(const dpa_u_bo_t*, (X))->ro, \
    DPA__GS(dpa_u_bo_ro_t*, (X))[0], \
    dpa_u_bo_inline_t*: (dpa_u_bo_ro_t){ .bo_inline = *DPA__G(dpa_u_bo_inline_t*, (X)) }, \
    const dpa_u_bo_inline_t*: (dpa_u_bo_ro_t){ .bo_inline = *DPA__G(const dpa_u_bo_inline_t*, (X)) }, \
    dpa_u_bo_simple_t*: (dpa_u_bo_ro_t){ .bo_simple = DPA__G(dpa_u_bo_simple_t*, (X))->ro }, \
    const dpa_u_bo_simple_t*: (dpa_u_bo_ro_t){ .bo_simple = DPA__G(const dpa_u_bo_simple_t*, (X))->ro }, \
    dpa_u_bo_simple_ro_t*: (dpa_u_bo_ro_t){ .bo_simple = *DPA__G(dpa_u_bo_simple_ro_t*, (X)) }, \
    dpa_u_bo_unique_t*: (dpa_u_bo_ro_t){ .bo_unique = *DPA__G(dpa_u_bo_unique_t*, (X)) }, \
    dpa_u_bo_any_unique_t*: (dpa_u_bo_ro_t){ .bo_any_unique = *DPA__G(dpa_u_bo_any_unique_t*, (X)) } \
  )

#endif
