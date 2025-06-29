#ifndef DPA_UTILS_REFCOUNT_H
#define DPA_UTILS_REFCOUNT_H

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-refcount Reference Counting
 * @{
 * Library for reference counting.
 * 
 * Any refcount can be static.
 * A refcount is either freeable or not.
 * If it is freeable, it may have a callback, or it may be part of a unique BO.
 * Otherwise, a freeable BO will be freed with `free()`.
 */

#include <dpa/utils/common.h>

#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef DPA_U_NO_THREADS
#include <stdatomic.h>

#ifdef DPA_U_REFCOUNT_DEBUG
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
pid_t gettid(void);
void flockfile(FILE *filehandle);
void funlockfile(FILE *filehandle);
#endif
#endif

#define dpa_u_refcount_type_list(X) \
  X((DPA_U_REFCOUNT_NONE)) \
  X((DPA_U_REFCOUNT_STATIC)) \
  X((DPA_U_REFCOUNT_FREEABLE)) \
  X((DPA_U_REFCOUNT_CALLBACK)) \
  X((DPA_U_REFCOUNT_BO_UNIQUE)) \
  X((DPA_U_REFCOUNT_BO_UNIQUE_EXTREF))

#define DPA_U_REFCOUNT_NONE             DPA_U_REFCOUNT_NONE             /**< It's not specified what happens when the refcount hits 0, it probably shouldn't be messed with directly. */
#define DPA_U_REFCOUNT_STATIC           DPA_U_REFCOUNT_STATIC            /**< This refcount will never hit 0, it only exists for compatibility. */ 
#define DPA_U_REFCOUNT_FREEABLE         DPA_U_REFCOUNT_FREEABLE          /**< This refcount is at the start of an allocated object and can be freed using free() */ 
#define DPA_U_REFCOUNT_CALLBACK         DPA_U_REFCOUNT_CALLBACK          /**< When this refcount hits 0, it'll call a callback. */ 
#define DPA_U_REFCOUNT_BO_UNIQUE        DPA_U_REFCOUNT_BO_UNIQUE         /**< Refcount of an entry of a dpa_u_a_bo_unique. Because this is an essential internal type, we can special case it here to safe a bit of memory. */
#define DPA_U_REFCOUNT_BO_UNIQUE_EXTREF DPA_U_REFCOUNT_BO_UNIQUE_EXTREF  /**< Refcount of an entry of a dpa_u_a_bo_unique. Because this is an essential internal type, we can special case it here to safe a bit of memory. */

DPA_U_ENUM(dpa_u_refcount_type)

#define DPA__U_REFCOUNT_TYPE_SHIFT_FACTOR 61
#define DPA__U_REFCOUNT_GUARD_BIT (((uint64_t)1)<<(DPA__U_REFCOUNT_TYPE_SHIFT_FACTOR-1))
#define DPA__U_REFCOUNT_MASK (DPA__U_REFCOUNT_GUARD_BIT-1)

typedef struct dpa_u_refcount dpa_u_refcount_t; /** \copydoc dpa_u_refcount */
typedef struct dpa_u_refcount_freeable dpa_u_refcount_freeable_t; /** \copydoc dpa_u_refcount_freeable */
typedef struct dpa_u_refcount_callback dpa_u_refcount_callback_t; /** \copydoc dpa_u_refcount_callback */
typedef struct dpa__u_refcount_bo_unique dpa__u_refcount_bo_unique_t; /** \copydoc dpa__u_refcount_bo_unique */

#ifndef DPA_U_NO_THREADS
typedef atomic_uint_fast64_t dpa__u_refcount_value_t;
#else
typedef uint_fast64_t dpa__u_refcount_value_t;
#endif

/**
 * A simple reference counter. It's value so big it'll never overflow.
 * Using this refcount can be useful if you don't ever expose it, and manually handle the case of it reaching 0.
 * You can also make it so it'll never reach 0.
 * \see DPA_U_REFCOUNT_STATIC
 * \see DPA_U_REFCOUNT_INIT
 * \see dpa_u_refcount_i_static
 */
struct dpa_u_refcount {
  dpa__u_refcount_value_t value;
};
static_assert(offsetof(struct dpa_u_refcount, value) == 0, "Unexpected offset of member .value");

/**
 * When this refcount hits 0, it automatically does some cleanup.  
 * If it is a \ref DPA_U_REFCOUNT_FREEABLE, it'll just call free.  
 * If you have a pointer to this type, it could also be a \ref dpa_u_refcount_callback_t / \ref DPA_U_REFCOUNT_CALLBACK,
 * or one of \ref DPA_U_REFCOUNT_BO_UNIQUE / \ref DPA_U_REFCOUNT_BO_UNIQUE_EXTREF.
 * You can also make it so it'll never reach 0.
 * \see DPA_U_REFCOUNT_STATIC
 * \see DPA_U_REFCOUNT_INIT
 * \see dpa_u_refcount_i_static
 */
struct dpa_u_refcount_freeable {
  union {
    dpa__u_refcount_value_t value;
    struct dpa_u_refcount refcount;
  };
};
static_assert(offsetof(struct dpa_u_refcount_freeable, value) == 0, "Unexpected offset of member .value");
static_assert(offsetof(struct dpa_u_refcount_freeable, refcount) == 0, "Unexpected offset of member .refcount");
static_assert(sizeof(struct dpa_u_refcount_freeable) == sizeof(struct dpa_u_refcount), "Expected dpa_u_refcount_freeable and dpa_u_refcount to have the same size.");

/**
 * This refcount calls its free callback once it reaches 0.
 * It's twice as big as a regular refcount, though.
 * It can be passed to functions expecting a \ref dpa_u_refcount_freeable_t*.
 */
struct dpa_u_refcount_callback {
  union {
    dpa__u_refcount_value_t value;
    struct dpa_u_refcount refcount;
    struct dpa_u_refcount_freeable freeable;
  };
  void(*free)(struct dpa_u_refcount_callback* cb);
};
static_assert(offsetof(struct dpa_u_refcount_callback, value) == 0, "Unexpected offset of member .value");
static_assert(offsetof(struct dpa_u_refcount_callback, refcount) == 0, "Unexpected offset of member .refcount");
static_assert(offsetof(struct dpa_u_refcount_callback, freeable) == 0, "Unexpected offset of member .freeable");

struct dpa__u_refcount_bo_unique {
  union {
    dpa__u_refcount_value_t value;
    struct dpa_u_refcount refcount;
    struct dpa_u_refcount_freeable freeable;
  };
};
static_assert(offsetof(struct dpa_u_refcount_callback, value) == 0, "Unexpected offset of member .value");
static_assert(offsetof(struct dpa_u_refcount_callback, refcount) == 0, "Unexpected offset of member .refcount");
static_assert(offsetof(struct dpa_u_refcount_callback, freeable) == 0, "Unexpected offset of member .freeable");

/**
 * Use this to add a flag to a refcount.
 * The guard bit it adds protects the refcount flags from refcount underflows.
 * \see dpa_u_refcount_type
 */
#define DPA_U_REFCOUNT_INIT(X) ((((uint64_t)(X))<<DPA__U_REFCOUNT_TYPE_SHIFT_FACTOR)|DPA__U_REFCOUNT_GUARD_BIT)

/* Initializer for raw refcounts */
#define dpa_u_refcount_i_none(N)      {N}
/** Initializer for static refcounts. No matter how often it's incremened or decremented, it's never going to hit 0 */
#define dpa_u_refcount_i_static       {.value=DPA_U_REFCOUNT_INIT(DPA_U_REFCOUNT_STATIC)}
/** Initializer for freeable refcounts */
#define dpa_u_refcount_i_freeable(N)  {{(N)+DPA_U_REFCOUNT_INIT(DPA_U_REFCOUNT_FREEABLE)}}
/** Initializer for callback refcounts */
#define dpa_u_refcount_i_callback(N)  {{(N)+DPA_U_REFCOUNT_INIT(DPA_U_REFCOUNT_CALLBACK)}}

/** A \ref dpa_u_refcount_t global refcount which never hits 0. */
dpa__u_api_var extern struct dpa_u_refcount dpa_u_refcount_v_static;
/** A \ref dpa_u_refcount_freeable_t global refcount which never hits 0. */
dpa__u_api_var extern struct dpa_u_refcount_freeable dpa_u_refcount_static_v_freeable;
/** A \ref dpa_u_refcount_callback_t global refcount which never hits 0. */
dpa__u_api_var extern struct dpa_u_refcount_callback dpa_u_refcount_static_v_callback;

/**
 * \see dpa_u_refcount_type
 */
#define dpa_u_refcount_get_type(...) dpa_u_assert_selection(dpa_u_refcount_get_type_g(__VA_ARGS__))
#define dpa_u_refcount_get_type_g(X) dpa_u_generic((X), \
    struct dpa_u_refcount: dpa_u_refcount_get_type_p(&DPA_U_G(struct dpa_u_refcount,(X))), \
    struct dpa_u_refcount_freeable: dpa_u_refcount_get_type_p(&DPA_U_G(struct dpa_u_refcount_freeable,(X)).refcount), \
    struct dpa_u_refcount_callback: dpa_u_refcount_get_type_p(&DPA_U_G(struct dpa_u_refcount_callback,(X)).refcount), \
    struct dpa__u_refcount_bo_unique: dpa_u_refcount_get_type_p(&DPA_U_G(struct dpa__u_refcount_bo_unique,(X)).refcount), \
          struct dpa_u_refcount*: dpa_u_refcount_get_type_p(DPA_U_G(struct dpa_u_refcount*,(X))), \
    const struct dpa_u_refcount*: dpa_u_refcount_get_type_p(DPA_U_G(const struct dpa_u_refcount*,(X))), \
          struct dpa_u_refcount_freeable*: dpa_u_refcount_get_type_p(&DPA_U_G(struct dpa_u_refcount_freeable*,(X))->refcount), \
    const struct dpa_u_refcount_freeable*: dpa_u_refcount_get_type_p(&DPA_U_G(const struct dpa_u_refcount_freeable*,(X))->refcount), \
          struct dpa_u_refcount_callback*: dpa_u_refcount_get_type_p(&DPA_U_G(struct dpa_u_refcount_callback*,(X))->refcount), \
    const struct dpa_u_refcount_callback*: dpa_u_refcount_get_type_p(&DPA_U_G(const struct dpa_u_refcount_callback*,(X))->refcount), \
          struct dpa__u_refcount_bo_unique*: dpa_u_refcount_get_type_p(&DPA_U_G(struct dpa__u_refcount_bo_unique*,(X))->refcount), \
    const struct dpa__u_refcount_bo_unique*: dpa_u_refcount_get_type_p(&DPA_U_G(const struct dpa__u_refcount_bo_unique*,(X))->refcount) \
  )
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline enum dpa_u_refcount_type dpa_u_refcount_get_type_p(const struct dpa_u_refcount*const rc){
  // We only care about the sign bit, and it's not going to change
#ifndef DPA_U_NO_THREADS
  return atomic_load_explicit(&rc->value, memory_order_relaxed) >> DPA__U_REFCOUNT_TYPE_SHIFT_FACTOR;
#else
  return rc->value >> DPA__U_REFCOUNT_TYPE_SHIFT_FACTOR;
#endif
}

/**
 * Increment the dpa_u_refcount
 */
#define dpa_u_refcount_increment(...) dpa_u_assert_selection(dpa_u_refcount_increment_g(__VA_ARGS__))
#define dpa_u_refcount_increment_s dpa_u_refcount_increment_p
#define dpa_u_refcount_increment_g(X) dpa_u_generic((X), \
    struct dpa_u_refcount: dpa_u_refcount_increment_s(&DPA_U_G(struct dpa_u_refcount,(X))), \
    struct dpa_u_refcount_freeable: dpa_u_refcount_increment_s(&DPA_U_G(struct dpa_u_refcount_freeable,(X)).refcount), \
    struct dpa_u_refcount_callback: dpa_u_refcount_increment_s(&DPA_U_G(struct dpa_u_refcount_callback,(X)).refcount), \
    struct dpa__u_refcount_bo_unique: dpa_u_refcount_increment_s(&DPA_U_G(struct dpa__u_refcount_bo_unique,(X)).refcount), \
          struct dpa_u_refcount*: dpa_u_refcount_increment_s(DPA_U_G(struct dpa_u_refcount*,(X))), \
    const struct dpa_u_refcount*: dpa_u_refcount_increment_s(DPA_U_G(const struct dpa_u_refcount*,(X))), \
          struct dpa_u_refcount_freeable*: dpa_u_refcount_increment_s(&DPA_U_G(struct dpa_u_refcount_freeable*,(X))->refcount), \
    const struct dpa_u_refcount_freeable*: dpa_u_refcount_increment_s(&DPA_U_G(const struct dpa_u_refcount_freeable*,(X))->refcount), \
          struct dpa_u_refcount_callback*: dpa_u_refcount_increment_s(&DPA_U_G(struct dpa_u_refcount_callback*,(X))->refcount), \
    const struct dpa_u_refcount_callback*: dpa_u_refcount_increment_s(&DPA_U_G(const struct dpa_u_refcount_callback*,(X))->refcount), \
          struct dpa__u_refcount_bo_unique*: dpa_u_refcount_increment_s(&DPA_U_G(struct dpa__u_refcount_bo_unique*,(X))->refcount), \
    const struct dpa__u_refcount_bo_unique*: dpa_u_refcount_increment_s(&DPA_U_G(const struct dpa__u_refcount_bo_unique*,(X))->refcount) \
  )
#define dpa_u_refcount_ref(X) dpa_u_refcount_increment((X))
dpa__u_really_inline dpa__u_api inline void dpa_u_refcount_increment_p(const struct dpa_u_refcount*const _rc){
  struct dpa_u_refcount*const rc = (struct dpa_u_refcount*)_rc;
#ifndef DPA_U_NO_THREADS
  atomic_fetch_add_explicit(&rc->value, 1, memory_order_relaxed);
#else
  rc->value++;
#endif
}

/**
 * Decrement the dpa_u_refcount
 * \returns false if the reference count has hit 0, true otherwise
 */
#define dpa_u_refcount_decrement dpa_u_refcount_decrement_s
#define dpa_u_refcount_decrement_s dpa_u_refcount_decrement_p
dpa__u_really_inline dpa__u_api inline bool dpa_u_refcount_decrement_p(const struct dpa_u_refcount*const _rc){
  struct dpa_u_refcount* rc = (struct dpa_u_refcount*)_rc;
#ifndef DPA_U_NO_THREADS
  return atomic_fetch_sub_explicit(&rc->value, 1, memory_order_acq_rel) - 1;
#else
  return --rc->value;
#endif
}

dpa__u_api inline void dpa__u_refcount_destroy(struct dpa_u_refcount_freeable*const rc){
  void dpa__u_bo_unique_destroy(const struct dpa_u_refcount_freeable*);
  const enum dpa_u_refcount_type type = dpa_u_refcount_get_type(&rc->refcount);
#if defined(__GNUC__) && !defined(__llvm__)
// GCC will get confused about which branchs are reachable and warn. All we can do about it is disable the warning.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfree-nonheap-object"
#endif
  switch(type){
    case DPA_U_REFCOUNT_NONE: break;
    case DPA_U_REFCOUNT_STATIC: return;
    case DPA_U_REFCOUNT_FREEABLE: free(rc); return;
    case DPA_U_REFCOUNT_CALLBACK: ((struct dpa_u_refcount_callback*)rc)->free((struct dpa_u_refcount_callback*)rc); return;
    case DPA_U_REFCOUNT_BO_UNIQUE_EXTREF:
    case DPA_U_REFCOUNT_BO_UNIQUE: dpa__u_bo_unique_destroy(rc); return;
  }
#if defined(__GNUC__) && !defined(__llvm__)
#pragma GCC diagnostic pop
#endif
  dpa_u_unreachable("dpa_u_refcount_freeable can't be of type %s", dpa_u_enum_get_name(dpa_u_refcount_type, type));
}


/**
 * Decrement the dpa_u_refcount and free the referenced resource when it hits 0.
 * \returns false if the reference count has hit 0, true otherwise
 */
#define dpa_u_refcount_put(...) dpa_u_assert_selection(dpa_u_refcount_put_g(__VA_ARGS__))
#define dpa_u_refcount_put_s dpa_u_refcount_put_p
#define dpa_u_refcount_put_g(X) dpa_u_generic((X), \
    struct dpa_u_refcount_freeable: dpa_u_refcount_put_s(&DPA_U_G(struct dpa_u_refcount_freeable,(X))), \
    struct dpa_u_refcount_callback: dpa_u_refcount_put_s(&DPA_U_G(struct dpa_u_refcount_callback,(X)).freeable), \
    struct dpa__u_refcount_bo_unique: dpa_u_refcount_put_s(&DPA_U_G(struct dpa__u_refcount_bo_unique,(X)).freeable), \
          struct dpa_u_refcount_freeable*: dpa_u_refcount_put_s(DPA_U_G(struct dpa_u_refcount_freeable*,(X))), \
    const struct dpa_u_refcount_freeable*: dpa_u_refcount_put_s(DPA_U_G(const struct dpa_u_refcount_freeable*,(X))), \
          struct dpa_u_refcount_callback*: dpa_u_refcount_put_s(&DPA_U_G(struct dpa_u_refcount_callback*,(X))->freeable), \
    const struct dpa_u_refcount_callback*: dpa_u_refcount_put_s(&DPA_U_G(const struct dpa_u_refcount_callback*,(X))->freeable), \
          struct dpa__u_refcount_bo_unique*: dpa_u_refcount_put_s(&DPA_U_G(struct dpa__u_refcount_bo_unique*,(X))->freeable), \
    const struct dpa__u_refcount_bo_unique*: dpa_u_refcount_put_s(&DPA_U_G(const struct dpa__u_refcount_bo_unique*,(X))->freeable) \
  )
dpa__u_really_inline dpa__u_api inline bool dpa_u_refcount_put_p(const struct dpa_u_refcount_freeable*const _rc){
  struct dpa_u_refcount_freeable*const rc = (struct dpa_u_refcount_freeable*)_rc;
#ifndef DPA_U_NO_THREADS
  if(dpa_u_likely(((atomic_fetch_sub_explicit(&rc->value, 1, memory_order_acq_rel) - 1) & DPA__U_REFCOUNT_MASK)))
    return true;
#else
  if(dpa_u_likely(--rc->value & DPA__U_REFCOUNT_MASK))
    return true;
#endif
  dpa__u_refcount_destroy(rc);
  return false;
}


/**
 * Checks if the dpa_u_refcount is 1. This usually means we have the only existing reference.
 * \returns true if the dpa_u_refcount is 1, 0 otherwise.
 */
#define dpa_u_refcount_is_last(...) dpa_u_assert_selection(dpa_u_refcount_is_last_g(__VA_ARGS__))
#define dpa_u_refcount_is_last_s dpa_u_refcount_is_last_p
#define dpa_u_refcount_is_last_g(X) dpa_u_generic((X), \
    struct dpa_u_refcount: dpa_u_refcount_is_last_s(&DPA_U_G(struct dpa_u_refcount,(X))), \
    struct dpa_u_refcount_freeable: dpa_u_refcount_is_last_s(&DPA_U_G(struct dpa_u_refcount_freeable,(X)).refcount), \
    struct dpa_u_refcount_callback: dpa_u_refcount_is_last_s(&DPA_U_G(struct dpa_u_refcount_callback,(X)).refcount), \
    struct dpa__u_refcount_bo_unique: dpa_u_refcount_is_last_s(&DPA_U_G(struct dpa__u_refcount_bo_unique,(X)).refcount), \
          struct dpa_u_refcount*: dpa_u_refcount_is_last_s(DPA_U_G(struct dpa_u_refcount*,(X))), \
    const struct dpa_u_refcount*: dpa_u_refcount_is_last_s(DPA_U_G(const struct dpa_u_refcount*,(X))), \
          struct dpa_u_refcount_freeable*: dpa_u_refcount_is_last_s(&DPA_U_G(struct dpa_u_refcount_freeable*,(X))->refcount), \
    const struct dpa_u_refcount_freeable*: dpa_u_refcount_is_last_s(&DPA_U_G(const struct dpa_u_refcount_freeable*,(X))->refcount), \
          struct dpa_u_refcount_callback*: dpa_u_refcount_is_last_s(&DPA_U_G(struct dpa_u_refcount_callback*,(X))->refcount), \
    const struct dpa_u_refcount_callback*: dpa_u_refcount_is_last_s(&DPA_U_G(const struct dpa_u_refcount_callback*,(X))->refcount), \
          struct dpa__u_refcount_bo_unique*: dpa_u_refcount_is_last_s(&DPA_U_G(struct dpa__u_refcount_bo_unique*,(X))->refcount), \
    const struct dpa__u_refcount_bo_unique*: dpa_u_refcount_is_last_s(&DPA_U_G(const struct dpa__u_refcount_bo_unique*,(X))->refcount) \
  )
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline bool dpa_u_refcount_is_last_p(const struct dpa_u_refcount*const rc){
#ifndef DPA_U_NO_THREADS
  return (atomic_load_explicit(&rc->value, memory_order_acquire) & DPA__U_REFCOUNT_MASK) == 1;
#else
  return (rc->value & DPA__U_REFCOUNT_MASK) == 1;
#endif
}

/**
 * Checks if the dpa_u_refcount is 0. This means there are no references.
 * This may be useful when conditionally allocating datastructures, although such cases usually still need some additional locking.
 * \returns true if the dpa_u_refcount is 1, 0 otherwise.
 */
#define dpa_u_refcount_is_zero(...) dpa_u_assert_selection(dpa_u_refcount_is_zero_g(__VA_ARGS__))
#define dpa_u_refcount_is_zero_s dpa_u_refcount_is_zero_p
#define dpa_u_refcount_is_zero_g(X) dpa_u_generic((X), \
    struct dpa_u_refcount: dpa_u_refcount_is_zero_s(&DPA_U_G(struct dpa_u_refcount,(X))), \
    struct dpa_u_refcount_freeable: dpa_u_refcount_is_zero_s(&DPA_U_G(struct dpa_u_refcount_freeable,(X)).refcount), \
    struct dpa_u_refcount_callback: dpa_u_refcount_is_zero_s(&DPA_U_G(struct dpa_u_refcount_callback,(X)).refcount), \
    struct dpa__u_refcount_bo_unique: dpa_u_refcount_is_zero_s(&DPA_U_G(struct dpa__u_refcount_bo_unique,(X)).refcount), \
          struct dpa_u_refcount*: dpa_u_refcount_is_zero_s(DPA_U_G(struct dpa_u_refcount*,(X))), \
    const struct dpa_u_refcount*: dpa_u_refcount_is_zero_s(DPA_U_G(const struct dpa_u_refcount*,(X))), \
          struct dpa_u_refcount_freeable*: dpa_u_refcount_is_zero_s(&DPA_U_G(struct dpa_u_refcount_freeable*,(X))->refcount), \
    const struct dpa_u_refcount_freeable*: dpa_u_refcount_is_zero_s(&DPA_U_G(const struct dpa_u_refcount_freeable*,(X))->refcount), \
          struct dpa_u_refcount_callback*: dpa_u_refcount_is_zero_s(&DPA_U_G(struct dpa_u_refcount_callback*,(X))->refcount), \
    const struct dpa_u_refcount_callback*: dpa_u_refcount_is_zero_s(&DPA_U_G(const struct dpa_u_refcount_callback*,(X))->refcount), \
          struct dpa__u_refcount_bo_unique*: dpa_u_refcount_is_zero_s(&DPA_U_G(struct dpa__u_refcount_bo_unique*,(X))->refcount), \
    const struct dpa__u_refcount_bo_unique*: dpa_u_refcount_is_zero_s(&DPA_U_G(const struct dpa__u_refcount_bo_unique*,(X))->refcount) \
  )
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline bool dpa_u_refcount_is_zero_p(const struct dpa_u_refcount*const rc){
#ifndef DPA_U_NO_THREADS
  return (atomic_load_explicit(&rc->value, memory_order_acquire) & DPA__U_REFCOUNT_MASK) == 0;
#else
  return (rc->value & DPA__U_REFCOUNT_MASK) == 0;
#endif
}

/**
 * \returns true for a static refcount, false otherwise.
 */
#define dpa_u_refcount_is_static(...) dpa_u_assert_selection(dpa_u_refcount_is_static_g(__VA_ARGS__))
#define dpa_u_refcount_is_static_g(X) dpa_u_generic((X), \
    struct dpa_u_refcount: dpa_u_refcount_is_static_p(&DPA_U_G(struct dpa_u_refcount,(X))), \
    struct dpa_u_refcount_freeable: dpa_u_refcount_is_static_p(&DPA_U_G(struct dpa_u_refcount_freeable,(X)).refcount), \
    struct dpa_u_refcount_callback: dpa_u_refcount_is_static_p(&DPA_U_G(struct dpa_u_refcount_callback,(X)).refcount), \
    struct dpa__u_refcount_bo_unique: dpa_u_refcount_is_static_p(&DPA_U_G(struct dpa__u_refcount_bo_unique,(X)).refcount), \
          struct dpa_u_refcount*: dpa_u_refcount_is_static_p(DPA_U_G(struct dpa_u_refcount*,(X))), \
    const struct dpa_u_refcount*: dpa_u_refcount_is_static_p(DPA_U_G(const struct dpa_u_refcount*,(X))), \
          struct dpa_u_refcount_freeable*: dpa_u_refcount_is_static_p(&DPA_U_G(struct dpa_u_refcount_freeable*,(X))->refcount), \
    const struct dpa_u_refcount_freeable*: dpa_u_refcount_is_static_p(&DPA_U_G(const struct dpa_u_refcount_freeable*,(X))->refcount), \
          struct dpa_u_refcount_callback*: dpa_u_refcount_is_static_p(&DPA_U_G(struct dpa_u_refcount_callback*,(X))->refcount), \
    const struct dpa_u_refcount_callback*: dpa_u_refcount_is_static_p(&DPA_U_G(const struct dpa_u_refcount_callback*,(X))->refcount), \
          struct dpa__u_refcount_bo_unique*: dpa_u_refcount_is_static_p(&DPA_U_G(struct dpa__u_refcount_bo_unique*,(X))->refcount), \
    const struct dpa__u_refcount_bo_unique*: dpa_u_refcount_is_static_p(&DPA_U_G(const struct dpa__u_refcount_bo_unique*,(X))->refcount) \
  )

dpa_u_reproducible dpa__u_really_inline dpa__u_api inline bool dpa_u_refcount_is_static_p(const struct dpa_u_refcount*const rc){
  return dpa_u_refcount_get_type(rc) == DPA_U_REFCOUNT_STATIC;
}


/**
 * This object will be freed with free() when the refcount hits 0.
 */
#define dpa_u_refcount_is_freeable(...) dpa_u_assert_selection(dpa_u_refcount_is_freeable_g(__VA_ARGS__))
#define dpa_u_refcount_is_freeable_g(X) dpa_u_generic((X), \
    struct dpa_u_refcount: false, \
    struct dpa_u_refcount_freeable: true, \
    struct dpa_u_refcount_callback: true, \
    struct dpa__u_refcount_bo_unique: true, \
          struct dpa_u_refcount*: false, \
    const struct dpa_u_refcount*: false, \
          struct dpa_u_refcount_freeable*: true, \
    const struct dpa_u_refcount_freeable*: true, \
          struct dpa_u_refcount_callback*: true, \
    const struct dpa_u_refcount_callback*: true, \
          struct dpa__u_refcount_bo_unique*: true, \
    const struct dpa__u_refcount_bo_unique*: true \
  )

/**
 * This object can be freed with a callback when the refcount hits 0.
 */
#define dpa_u_refcount_has_callback(...) dpa_u_assert_selection(dpa_u_refcount_has_callback_g(__VA_ARGS__))
#define dpa_u_refcount_has_callback_g(X) dpa_u_generic((X), \
    struct dpa_u_refcount: false, \
    struct dpa_u_refcount_freeable: dpa_u_refcount_has_callback_p(&DPA_U_G(struct dpa_u_refcount_freeable,(X)).refcount), \
    struct dpa_u_refcount_callback: true, \
    struct dpa__u_refcount_bo_unique: false, \
          struct dpa_u_refcount*: false, \
    const struct dpa_u_refcount*: false, \
          struct dpa_u_refcount_freeable*: dpa_u_refcount_has_callback_p(&DPA_U_G(struct dpa_u_refcount_freeable*,(X))->refcount), \
    const struct dpa_u_refcount_freeable*: dpa_u_refcount_has_callback_p(&DPA_U_G(const struct dpa_u_refcount_freeable*,(X))->refcount), \
          struct dpa_u_refcount_callback*: true, \
    const struct dpa_u_refcount_callback*: true, \
          struct dpa__u_refcount_bo_unique*: false, \
    const struct dpa__u_refcount_bo_unique*: false \
  )
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline bool dpa_u_refcount_has_callback_p(const struct dpa_u_refcount*const rc){
  return dpa_u_refcount_get_type(rc) == DPA_U_REFCOUNT_CALLBACK;
}

/**
 * This object is a dpa_u_bo_unique.
 */
#define dpa_u_refcount_is_bo_unique(...) dpa_u_assert_selection(dpa_u_refcount_is_bo_unique_g(__VA_ARGS__))
#define dpa_u_refcount_is_bo_unique_g(X) dpa_u_generic((X), \
    struct dpa_u_refcount: false, \
    struct dpa_u_refcount_freeable: dpa_u_refcount_is_bo_unique_p(&DPA_U_G(struct dpa_u_refcount_freeable,(X)).refcount), \
    struct dpa_u_refcount_callback: false, \
    struct dpa__u_refcount_bo_unique: true, \
          struct dpa_u_refcount*: false, \
    const struct dpa_u_refcount*: false, \
          struct dpa_u_refcount_freeable*: dpa_u_refcount_is_bo_unique_p(&DPA_U_G(struct dpa_u_refcount_freeable*,(X))->refcount), \
    const struct dpa_u_refcount_freeable*: dpa_u_refcount_is_bo_unique_p(&DPA_U_G(const struct dpa_u_refcount_freeable*,(X))->refcount), \
          struct dpa_u_refcount_callback*: false, \
    const struct dpa_u_refcount_callback*: false, \
          struct dpa__u_refcount_bo_unique*: true, \
    const struct dpa__u_refcount_bo_unique*: true \
  )
dpa_u_reproducible dpa__u_really_inline dpa__u_api inline bool dpa_u_refcount_is_bo_unique_p(const struct dpa_u_refcount*const rc){
  const enum dpa_u_refcount_type type = dpa_u_refcount_get_type(rc);
  return type == DPA_U_REFCOUNT_BO_UNIQUE || type == DPA_U_REFCOUNT_BO_UNIQUE_EXTREF;
}

#ifdef DPA_U_REFCOUNT_DEBUG
#undef dpa_u_refcount_increment_s
#define dpa_u_refcount_increment_s(R) \
  ( \
    flockfile(stderr), \
    fprintf(stderr, "%ld> %s:%d: %s: dpa_u_refcount_increment(%p: %s)\n", (long)gettid(), __FILE__, __LINE__, __func__, (void*)(R), #R), \
    funlockfile(stderr), \
    dpa_u_refcount_increment_p((R)) \
  )

#undef dpa_u_refcount_decrement_s
#define dpa_u_refcount_decrement_s(R) \
  ( \
    flockfile(stderr), \
    fprintf(stderr, "%ld> %s:%d: %s: dpa_u_refcount_decrement(%p: %s) = ", (long)gettid(), __FILE__, __LINE__, __func__, (void*)(R), #R), \
    dpa_u_refcount_decrement_p((R)) \
     ? (fprintf(stderr, "true\n" ), funlockfile(stderr), true ) \
     : (fprintf(stderr, "false\n"), funlockfile(stderr), false) \
  )

#undef dpa_u_refcount_put_s
#define dpa_u_refcount_put_s(R) \
  ( \
    flockfile(stderr), \
    fprintf(stderr, "%ld> %s:%d: %s: dpa_u_refcount_put(%p: %s) = " , (long)gettid(), __FILE__, __LINE__, __func__, (void*)(R), #R), \
    dpa_u_refcount_put_p((R)) \
     ? (fprintf(stderr, "true\n" ), funlockfile(stderr), true ) \
     : (fprintf(stderr, "false\n"), funlockfile(stderr), false) \
  )

#undef dpa_u_refcount_is_last_s
#define dpa_u_refcount_is_last_s(R) \
  ( \
    flockfile(stderr), \
    fprintf(stderr, "%ld> %s:%d: %s: dpa_u_refcount_is_last(%p: %s) = " , (long)gettid(), __FILE__, __LINE__, __func__, (void*)(R), #R), \
    dpa_u_refcount_is_last_p((R)) \
     ? (fprintf(stderr, "true\n" ), funlockfile(stderr), true ) \
     : (fprintf(stderr, "false\n"), funlockfile(stderr), false) \
  )

#undef dpa_u_refcount_is_zero_s
#define dpa_u_refcount_is_zero_s(R) \
  ( \
    flockfile(stderr), \
    fprintf(stderr, "%ld> %s:%d: %s: dpa_u_refcount_is_zero(%p: %s) = " , (long)gettid(), __FILE__, __LINE__, __func__, (void*)(R), #R), \
    dpa_u_refcount_is_zero_p((R)) \
     ? (fprintf(stderr, "true\n" ), funlockfile(stderr), true ) \
     : (fprintf(stderr, "false\n"), funlockfile(stderr), false) \
  )

#endif

/** @} */
/** @} */

#endif
