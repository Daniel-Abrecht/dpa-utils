#ifndef DPA_UTILS_BO_SIMPLE_H
#define DPA_UTILS_BO_SIMPLE_H

#include <dpa/utils/common.h>

#include <stddef.h>
#include <stdlib.h>
#include <stdalign.h>
#include <limits.h>
#include <assert.h>

enum dpa_u_bo_type {
  DPA_U_BO_INLINE,
  DPA_U_BO_SIMPLE,
//  DPA_U_BO_UNIQUE,
};

enum { DPA__U_BO_COMMON_SIZE = sizeof(size_t) + sizeof(void*) };
enum { DPA_U_BO_INLINE_MAX_SIZE = DPA__U_BO_COMMON_SIZE-1 };
#define DPA_U_BO_MAX_SIZE (((size_t)1)<<((sizeof(size_t)-1)*CHAR_BIT))
#define DPA__U_BO_ALIGN alignas(DPA__U_BO_COMMON_SIZE)

#define DPA__U_BO_META(...) \
  struct __attribute__((packed)) { \
    enum dpa_u_bo_type type : CHAR_BIT - 4; \
    unsigned __VA_ARGS__ : 4; \
  }

// Note: There is no `dpa_u_bo_inline_t`. Just use const `dpa_u_bo_inline_t` instead.
typedef struct {
  union {
    struct {
      DPA__U_BO_META(size);
      char data[DPA__U_BO_COMMON_SIZE-1];
    };
    DPA__U_BO_ALIGN struct { char all[DPA__U_BO_COMMON_SIZE]; } all;
  };
} dpa_u_bo_inline_t;
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
    DPA__U_BO_ALIGN struct { char all[DPA__U_BO_COMMON_SIZE]; } all; \
  }

typedef const struct {
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

typedef const struct {
  union {
    struct { DPA__U_BO_META(); char _[DPA__U_BO_COMMON_SIZE-1]; };
    const dpa_u_bo_inline_t bo_inline;
    dpa_u_bo_simple_ro_t bo_simple;
    DPA__U_BO_ALIGN struct { char all[DPA__U_BO_COMMON_SIZE]; } all;
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
    DPA__U_BO_ALIGN struct { char all[DPA__U_BO_COMMON_SIZE]; } all;
  };
} dpa_u_bo_t;
static_assert(sizeof(dpa_u_bo_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_t has an unexpected size");
static_assert(offsetof(dpa_u_bo_t,_) == 1, "Expected _ to be at a different offset");

#define dpa_u_bo_data(X) _Generic((X), \
    DPA__GS(      dpa_u_bo_inline_t,     (X)).data, \
    DPA__GS(const dpa_u_bo_inline_t,     (X)).data, \
    DPA__GS(      dpa_u_bo_simple_t,     (X)).data, \
    DPA__GS(const dpa_u_bo_simple_t,     (X)).data, \
    DPA__GS(      dpa_u_bo_simple_ro_t,  (X)).data, \
          dpa_u_bo_t: dpa__u_bo_data(&DPA__G(dpa_u_bo_t,(X))), \
    const dpa_u_bo_t: dpa__u_cbo_data(&DPA__G(const dpa_u_bo_t,(X))), \
          dpa_u_bo_ro_t: dpa__u_bo_ro_data(&DPA__G(dpa_u_bo_ro_t,(X))), \
    \
    DPA__GS(      dpa_u_bo_inline_t*,    (X))->data, \
    DPA__GS(const dpa_u_bo_inline_t*,    (X))->data, \
    DPA__GS(      dpa_u_bo_simple_t*,    (X))->data, \
    DPA__GS(const dpa_u_bo_simple_t*,    (X))->data, \
    DPA__GS(      dpa_u_bo_simple_ro_t*, (X))->data, \
          dpa_u_bo_t*: dpa__u_bo_data(DPA__G(dpa_u_bo_t*,(X))), \
    const dpa_u_bo_t*: dpa__u_cbo_data(DPA__G(const dpa_u_bo_t*,(X))), \
          dpa_u_bo_ro_t*: dpa__u_bo_ro_data(DPA__G(dpa_u_bo_ro_t*,(X))) \
  )

#define X \
  switch(bo->type){ \
    case DPA_U_BO_INLINE: return bo->bo_inline.data; \
    case DPA_U_BO_SIMPLE: return bo->bo_simple.data; \
  } \
  abort();
static inline void* dpa__u_bo_data(dpa_u_bo_t*restrict const bo){ X }
static inline const void* dpa__u_cbo_data(const dpa_u_bo_t*restrict const bo){ X }
static inline const void* dpa__u_bo_ro_data(dpa_u_bo_ro_t*restrict const bo){ X }
#undef X

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
  }
  abort();
}

#define dpa_u_bo_get_size(X) ((size_t)_Generic((X), \
    DPA__GS(      dpa_u_bo_inline_t,(X)).size, \
    DPA__GS(const dpa_u_bo_inline_t,(X)).size, \
    DPA__GS(      dpa_u_bo_simple_t,(X)).size, \
    DPA__GS(const dpa_u_bo_simple_t,(X)).size, \
    DPA__GS(      dpa_u_bo_simple_ro_t,(X)).size, \
          dpa_u_bo_t: dpa__u_bo_get_size(DPA__G(dpa_u_bo_t, (X))), \
    const dpa_u_bo_t: dpa__u_bo_get_size(DPA__G(const dpa_u_bo_t, (X))), \
          dpa_u_bo_ro_t: dpa__u_bo_ro_get_size(DPA__G(dpa_u_bo_ro_t, (X))) \
  ))

#define X \
  switch(bo.type){ \
    case DPA_U_BO_INLINE: return bo.bo_inline.size; \
    case DPA_U_BO_SIMPLE: return bo.bo_simple.size; \
  } \
  abort();
static inline size_t dpa__u_bo_get_size(const dpa_u_bo_t bo){ X }
static inline size_t dpa__u_bo_ro_get_size(dpa_u_bo_ro_t bo){ X }
#undef X

#define dpa_u_bo_get_type(X) ((const enum dpa_u_bo_type)_Generic((X), \
    DPA__GS(      dpa_u_bo_t, (X)).type, \
    DPA__GS(const dpa_u_bo_t, (X)).type, \
    DPA__GS(      dpa_u_bo_ro_t, (X)).type, \
    DPA__GS(      dpa_u_bo_inline_t, (X)).type, \
    DPA__GS(const dpa_u_bo_inline_t, (X)).type, \
    DPA__GS(      dpa_u_bo_simple_t, (X)).type, \
    DPA__GS(const dpa_u_bo_simple_t, (X)).type, \
    DPA__GS(      dpa_u_bo_simple_ro_t, (X)).type, \
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

#endif
