#ifndef DPA_UTILS_REFCOUNT_H
#define DPA_UTILS_REFCOUNT_H

#include <dpa/utils/common.h>

#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef DPA_UTILS_REFCOUNT_DEBUG
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
pid_t gettid(void);
#endif

// Note: it's absolutely idiotic that there is an __STDC_NO_ATOMICS__ macro instead of a __STDC_ATOMICS__ macro.
// Non conforming compilers per default fail to specify it. Please fire whoever thought a negative feature test macro was a good idea.
#if __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_ATOMICS__)
#include <stdatomic.h>

#define dpa_u_refcount_type_list(X) \
  X((DPA_U_REFCOUNT_NONE))      /* It's not specified what happens when the refcount hits 0, it probably shouldn't be messed with directly. */ \
  X((DPA_U_REFCOUNT_STATIC))    /* This refcount will never hit 0, it only exists for compatibility. */ \
  X((DPA_U_REFCOUNT_FREEABLE))  /* This refcount is at the start of an allocated object and can be freed using free() */ \
  X((DPA_U_REFCOUNT_CALLBACK))  /* When this refcount hits 0, it'll call a callback. */ \
  X((DPA_U_REFCOUNT_BO_UNIQUE_HASHMAP)) /* Refcount of dpa_u_bo_unique. Because this is an essential internal type, we can special case it here to safe a bit of memory. */

DPA_U_ENUM(dpa_u_refcount_type)

#define DPA__U_REFCOUNT_TYPE_SHIFT_FACTOR 61
#define DPA__U_REFCOUNT_GUARD_BIT (((uint64_t)1)<<(DPA__U_REFCOUNT_TYPE_SHIFT_FACTOR-1))
#define DPA__U_REFCOUNT_MASK      (DPA__U_REFCOUNT_GUARD_BIT-1)

struct dpa_u_refcount {
  atomic_uint_fast64_t value;
};
static_assert(offsetof(struct dpa_u_refcount, value) == 0, "Unexpected offset of member .value");

struct dpa_u_refcount_freeable {
  union {
    atomic_uint_fast64_t value;
    struct dpa_u_refcount refcount;
  };
};
static_assert(offsetof(struct dpa_u_refcount_freeable, value) == 0, "Unexpected offset of member .value");
static_assert(offsetof(struct dpa_u_refcount_freeable, refcount) == 0, "Unexpected offset of member .refcount");
static_assert(sizeof(struct dpa_u_refcount_freeable) == sizeof(struct dpa_u_refcount), "Expected dpa_u_refcount_freeable and dpa_u_refcount to have the same size.");

struct dpa_u_refcount_callback {
  union {
    atomic_uint_fast64_t value;
    struct dpa_u_refcount refcount;
    struct dpa_u_refcount_freeable freeable;
  };
  void(*free)(struct dpa_u_refcount_callback* cb);
};
static_assert(offsetof(struct dpa_u_refcount_callback, value) == 0, "Unexpected offset of member .value");
static_assert(offsetof(struct dpa_u_refcount_callback, refcount) == 0, "Unexpected offset of member .refcount");
static_assert(offsetof(struct dpa_u_refcount_callback, freeable) == 0, "Unexpected offset of member .freeable");

struct dpa_u_refcount_bo_unique {
  union {
    atomic_uint_fast64_t value;
    struct dpa_u_refcount refcount;
    struct dpa_u_refcount_freeable freeable;
  };
};
static_assert(offsetof(struct dpa_u_refcount_callback, value) == 0, "Unexpected offset of member .value");
static_assert(offsetof(struct dpa_u_refcount_callback, refcount) == 0, "Unexpected offset of member .refcount");
static_assert(offsetof(struct dpa_u_refcount_callback, freeable) == 0, "Unexpected offset of member .freeable");

#define DPA_U_REFCOUNT_INIT(X) ((((uint64_t)(X))<<DPA__U_REFCOUNT_TYPE_SHIFT_FACTOR)|DPA__U_REFCOUNT_GUARD_BIT)

#define dpa_u_refcount_i_none     {0}
/**
 * No matter how often it's incremened or decremented, it's never going to hit positive numbers
 */
#define dpa_u_refcount_i_static       {.value=DPA_U_REFCOUNT_INIT(DPA_U_REFCOUNT_STATIC)}
#define dpa_u_refcount_i_freeable(N)  {{(N)+DPA_U_REFCOUNT_INIT(DPA_U_REFCOUNT_FREEABLE)}}
#define dpa_u_refcount_i_callback(N)  {{(N)+DPA_U_REFCOUNT_INIT(DPA_U_REFCOUNT_CALLBACK)}}
#define dpa_u_refcount_i_bo_unique(N) {{(N)+DPA_U_REFCOUNT_INIT(DPA_U_REFCOUNT_BO_UNIQUE_HASHMAP)}}

extern struct dpa_u_refcount dpa_u_refcount_v_static;
extern struct dpa_u_refcount_freeable dpa_u_refcount_static_v_freeable;
extern struct dpa_u_refcount_callback dpa_u_refcount_static_v_callback;

/**
 * \see dpa_u_refcount_type
 */
DPA_U_EXPORT inline enum dpa_u_refcount_type dpa_u_refcount_get_type(const struct dpa_u_refcount*const rc){
  // We only care about the sign bit, and it's not going to change
  return atomic_load_explicit(&rc->value, memory_order_relaxed) >> DPA__U_REFCOUNT_TYPE_SHIFT_FACTOR;
}

/**
 * Increment the dpa_u_refcount
 */
DPA_U_EXPORT inline void dpa_u_refcount_increment_p(const struct dpa_u_refcount*const _rc){
  struct dpa_u_refcount*const rc = (struct dpa_u_refcount*)_rc;
  if(rc) atomic_fetch_add_explicit(&rc->value, 1, memory_order_relaxed);
}

#define dpa_u_refcount_increment_s(X) _Generic((X), \
    struct dpa_u_refcount: dpa_u_refcount_increment_p(&DPA__G(struct dpa_u_refcount,(X))), \
    struct dpa_u_refcount_freeable: dpa_u_refcount_increment_p(&DPA__G(struct dpa_u_refcount_freeable,(X)).refcount), \
    struct dpa_u_refcount_callback: dpa_u_refcount_increment_p(&DPA__G(struct dpa_u_refcount_callback,(X)).refcount), \
    struct dpa_u_refcount_bo_unique: dpa_u_refcount_increment_p(&DPA__G(struct dpa_u_refcount_bo_unique,(X)).refcount), \
          struct dpa_u_refcount*: dpa_u_refcount_increment_p(DPA__G(struct dpa_u_refcount*,(X))), \
    const struct dpa_u_refcount*: dpa_u_refcount_increment_p(DPA__G(const struct dpa_u_refcount*,(X))), \
          struct dpa_u_refcount_freeable*: dpa_u_refcount_increment_p(&DPA__G(struct dpa_u_refcount_freeable*,(X))->refcount), \
    const struct dpa_u_refcount_freeable*: dpa_u_refcount_increment_p(&DPA__G(const struct dpa_u_refcount_freeable*,(X))->refcount), \
          struct dpa_u_refcount_callback*: dpa_u_refcount_increment_p(&DPA__G(struct dpa_u_refcount_callback*,(X))->refcount), \
    const struct dpa_u_refcount_callback*: dpa_u_refcount_increment_p(&DPA__G(const struct dpa_u_refcount_callback*,(X))->refcount), \
          struct dpa_u_refcount_bo_unique*: dpa_u_refcount_increment_p(&DPA__G(struct dpa_u_refcount_bo_unique*,(X))->refcount), \
    const struct dpa_u_refcount_bo_unique*: dpa_u_refcount_increment_p(&DPA__G(const struct dpa_u_refcount_bo_unique*,(X))->refcount) \
  )

#define dpa_u_refcount_increment(X) dpa_u_refcount_increment_s((X))
#define dpa_u_refcount_ref(X) dpa_u_refcount_increment((X))

/**
 * Decrement the dpa_u_refcount
 * \returns false if the reference count has hit 0, true otherwise
 */
DPA_U_EXPORT inline bool dpa_u_refcount_decrement(const struct dpa_u_refcount*const _rc){
  struct dpa_u_refcount* rc = (struct dpa_u_refcount*)_rc;
  return atomic_fetch_sub_explicit(&rc->value, 1, memory_order_acq_rel) - 1;
}

/**
 * Decrement the dpa_u_refcount and free the referenced resource when it hits 0.
 * \returns false if the reference count has hit 0, true otherwise
 */
DPA_U_EXPORT inline bool dpa_u_refcount_put_p(const struct dpa_u_refcount_freeable*const _rc){
  void dpa__u_bo_unique_hashmap_destroy(const struct dpa_u_refcount_freeable*);
  struct dpa_u_refcount_freeable*const rc = (struct dpa_u_refcount_freeable*)_rc;
  if(!((atomic_fetch_sub_explicit(&rc->value, 1, memory_order_acq_rel) - 1) & DPA__U_REFCOUNT_MASK)){
    const enum dpa_u_refcount_type type = dpa_u_refcount_get_type(&rc->refcount);
    switch(type){
      case DPA_U_REFCOUNT_NONE: break;
      case DPA_U_REFCOUNT_STATIC: return false;
      case DPA_U_REFCOUNT_FREEABLE: free(rc); return false;
      case DPA_U_REFCOUNT_CALLBACK: ((struct dpa_u_refcount_callback*)rc)->free((struct dpa_u_refcount_callback*)rc); return false;
      case DPA_U_REFCOUNT_BO_UNIQUE_HASHMAP: dpa__u_bo_unique_hashmap_destroy(rc); return false;
    }
    dpa_u_abort("dpa_u_refcount_freeable can't be of type %s", dpa_u_enum_get_name(dpa_u_refcount_type, type));
  }
  return true;
}

#define dpa_u_refcount_put_s(X) _Generic((X), \
    struct dpa_u_refcount_freeable: dpa_u_refcount_put_p(&DPA__G(struct dpa_u_refcount_freeable,(X))), \
    struct dpa_u_refcount_callback: dpa_u_refcount_put_p(&DPA__G(struct dpa_u_refcount_callback,(X)).freeable), \
    struct dpa_u_refcount_bo_unique: dpa_u_refcount_put_p(&DPA__G(struct dpa_u_refcount_bo_unique,(X)).freeable), \
          struct dpa_u_refcount_freeable*: dpa_u_refcount_put_p(DPA__G(struct dpa_u_refcount_freeable*,(X))), \
    const struct dpa_u_refcount_freeable*: dpa_u_refcount_put_p(DPA__G(const struct dpa_u_refcount_freeable*,(X))), \
          struct dpa_u_refcount_callback*: dpa_u_refcount_put_p(&DPA__G(struct dpa_u_refcount_callback*,(X))->freeable), \
    const struct dpa_u_refcount_callback*: dpa_u_refcount_put_p(&DPA__G(const struct dpa_u_refcount_callback*,(X))->freeable), \
          struct dpa_u_refcount_bo_unique*: dpa_u_refcount_put_p(&DPA__G(struct dpa_u_refcount_bo_unique*,(X))->freeable), \
    const struct dpa_u_refcount_bo_unique*: dpa_u_refcount_put_p(&DPA__G(const struct dpa_u_refcount_bo_unique*,(X))->freeable) \
  )

#define dpa_u_refcount_put(X) dpa_u_refcount_put_s((X))


/**
 * Checks if the dpa_u_refcount is 1. This usually means we have the only existing reference.
 * \returns true if the dpa_u_refcount is 1, 0 otherwise.
 */
DPA_U_EXPORT inline bool dpa_u_refcount_is_last(const struct dpa_u_refcount*const rc){
  return (atomic_load_explicit(&rc->value, memory_order_acquire) & DPA__U_REFCOUNT_MASK) == 1;
}

/**
 * Checks if the dpa_u_refcount is 0. This means there are no references.
 * This may be useful when conditionally allocating datastructures, although such cases usually still need some additional locking.
 * \returns true if the dpa_u_refcount is 1, 0 otherwise.
 */
DPA_U_EXPORT inline bool dpa_u_refcount_is_zero(const struct dpa_u_refcount*const rc){
  return (atomic_load_explicit(&rc->value, memory_order_acquire) & DPA__U_REFCOUNT_MASK) == 0;
}

/**
 * If something takes a refcounted object, but it's actually statically allocated
 */
DPA_U_EXPORT inline bool dpa_u_refcount_is_static(const struct dpa_u_refcount* rc){
  return dpa_u_refcount_get_type(rc) == DPA_U_REFCOUNT_STATIC;
}

/**
 * This object will be freed with free() when the refcount hits 0.
 */
DPA_U_EXPORT inline bool dpa_u_refcount_is_freeable(const struct dpa_u_refcount* rc){
  return dpa_u_refcount_get_type(rc) == DPA_U_REFCOUNT_FREEABLE;
}

/**
 * This object can be freed with a callback when the refcount hits 0.
 */
DPA_U_EXPORT inline bool dpa_u_refcount_has_callback(const struct dpa_u_refcount* rc){
  return dpa_u_refcount_get_type(rc) == DPA_U_REFCOUNT_CALLBACK;
}

/**
 * This object is a dpa_u_bo_unique.
 */
DPA_U_EXPORT inline bool dpa_u_refcount_is_bo_unique(const struct dpa_u_refcount* rc){
  return dpa_u_refcount_get_type(rc) == DPA_U_REFCOUNT_BO_UNIQUE_HASHMAP;
}

#else
#error "This file currently absolutely needs C11 atomic support. But feel free to add a fallback here."
#endif

#ifdef DPA_U_REFCOUNT_DEBUG
#undef dpa_u_refcount_increment
#define dpa_u_refcount_increment(R) \
  do { \
    struct dpa_u_refcount* _dpa_u_refcount = (R); \
    fprintf(stderr, "%ld> %s:%d: %s: dpa_u_refcount_increment(%p: %s)\n", (long)gettid(), __FILE__, __LINE__, __func__, (void*)_dpa_u_refcount, #R); \
    dpa_u_refcount_increment_s(_dpa_u_refcount); \
  } while(0)

#define dpa_u_refcount_decrement(R) \
  ( \
    fprintf(stderr, "%ld> %s:%d: %s: dpa_u_refcount_decrement(%p: %s) = ", (long)gettid(), __FILE__, __LINE__, __func__, (void*)(R), #R), \
    dpa_u_refcount_decrement((R)) \
     ? (fprintf(stderr, "true\n" ), true ) \
     : (fprintf(stderr, "false\n"), false) \
  )

#undef dpa_u_refcount_put
#define dpa_u_refcount_put(R) \
  ( \
    fprintf(stderr, "%ld> %s:%d: %s: dpa_u_refcount_put(%p: %s) = " , (long)gettid(), __FILE__, __LINE__, __func__, (void*)(R), #R), \
    dpa_u_refcount_put_s((R)) \
     ? (fprintf(stderr, "true\n" ), true ) \
     : (fprintf(stderr, "false\n"), false) \
  )

#define dpa_u_refcount_is_last(R) \
  ( \
    fprintf(stderr, "%ld> %s:%d: %s: dpa_u_refcount_is_last(%p: %s) = " , (long)gettid(), __FILE__, __LINE__, __func__, (void*)(R), #R), \
    dpa_u_refcount_is_last((R)) \
     ? (fprintf(stderr, "true\n" ), true ) \
     : (fprintf(stderr, "false\n"), false) \
  )

#define dpa_u_refcount_is_zero(R) \
  ( \
    fprintf(stderr, "%ld> %s:%d: %s: dpa_u_refcount_is_zero(%p: %s) = " , (long)gettid(), __FILE__, __LINE__, __func__, (void*)(R), #R), \
    dpa_u_refcount_is_zero((R)) \
     ? (fprintf(stderr, "true\n" ), true ) \
     : (fprintf(stderr, "false\n"), false) \
  )

#endif

#endif
