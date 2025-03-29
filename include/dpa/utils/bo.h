#ifndef DPA_U_BO_H
#define DPA_U_BO_H

#include <dpa/utils/common.h>
#include <dpa/utils/refcount.h>

#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>
#include <string.h>
#include <assert.h>

#include <endian.h>
#ifndef BYTE_ORDER
#error "BYTE_ORDER undefined. POSIX specifies that it should be defined in endian.h. You may need to define _DEFAULT_SOURCE or _GNU_SOURCE on some platforms (like glibc) to get it."
#endif

#if BYTE_ORDER == LITTLE_ENDIAN
#define DPA_U_TAG(X, T) (((uint64_t)(uintptr_t)(X)<<8) | (T))
#define DPA_U_UNTAG(X) ((void*)(uintptr_t)((X)>>8))
#elif BYTE_ORDER == BIG_ENDIAN
#define DPA_U_TAG(X, T) (((uint64_t)(uintptr_t)(X)) | ((T)<<56))
#define DPA_U_UNTAG(X) ((void*)(uintptr_t)((X) & 0x00FFFFFFFFFFFFFFu))
#else
#error "Unknown endianess"
#endif

typedef struct dpa_u__boptr {
  alignas(uint64_t) char c[8];
} dpa_u__boptr_t;
static_assert(sizeof(dpa_u__boptr_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u__boptr");

typedef struct dpa_u_bo {
  size_t size;
  char* data;
} dpa_u_bo_t;

typedef struct dpa_u_bo_ro {
  // Casting a pointer of struct dpa_u_bo to struct dpa_u_bo_ro would be UB, for this reason,
  // dpa_u_bo_t is usually used internally. The dpa_u_to_bo_ro will create a new object.
  size_t size;
  const char* data;
} dpa_u_bo_ro_t;

typedef struct dpa__u_bo_hashed {
  dpa_u_bo_t bo;
  uint64_t hash;
} dpa__u_bo_hashed_t;

typedef struct dpa_u_p_bo dpa_u_p_bo_t;

typedef struct dpa__u_a_bo_unique { dpa_u__boptr_t p; } dpa_u_a_bo_unique_t;
typedef struct dpa__u_a_bo_any    { dpa_u__boptr_t p; } dpa_u_a_bo_any_t;
typedef struct dpa__u_a_bo_any_ro { dpa_u__boptr_t p; } dpa_u_a_bo_any_ro_t;
typedef struct dpa__u_a_bo_gc     { dpa_u__boptr_t p; } dpa_u_a_bo_gc_t;
typedef struct dpa__u_a_bo_gc_ro  { dpa_u__boptr_t p; } dpa_u_a_bo_gc_ro_t;
typedef struct dpa__u_a_bo_hashed { dpa_u__boptr_t p; } dpa_u_a_bo_hashed_t;

static_assert(sizeof(dpa_u_a_bo_unique_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_any_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_any_ro_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_gc_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_gc_ro_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_hashed_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");

typedef struct dpa_u__noop* dpa_u__noop_t;
#define DPA_U__CHECK_GENERIC(X) static inline \
  void DPA_U_CONCAT_E(dpa_u__sc__, __LINE__)(void){ (void)(X((dpa_u__noop_t)0)); /* A simple sanity check for the generic macros. */ }

enum dpa_u_bo_type_flags {
  DPA_U_BO_IMMORTAL   = 0x80,
  DPA_U_BO_UNIQUE     = 0x40,
  DPA_U_BO_REFCOUNTED = 0x20,
  DPA_U_BO_HASHED     = 0x10,
  DPA_U_BO_SIMPLE     = 0x08,
};

#define dpa_u_bo_is_any_type(X, N) _Generic((X), \
    dpa_u__boptr_t       : (DPA__G(dpa_u__boptr_t,        (X)) .c[0] & (N)), \
    dpa_u__boptr_t*      : (DPA__G(dpa_u__boptr_t*,       (X))->c[0] & (N)), \
    const dpa_u__boptr_t*: (DPA__G(const dpa_u__boptr_t*, (X))->c[0] & (N)), \
    \
    dpa_u_bo_t         : DPA_U_BO_SIMPLE & (N), \
    dpa_u_bo_ro_t      : DPA_U_BO_SIMPLE & (N), \
    dpa_u_p_bo_t*      : DPA_U_BO_SIMPLE & (N), \
    const dpa_u_p_bo_t*: DPA_U_BO_SIMPLE & (N), \
    \
    struct dpa__u_a_bo_unique: (DPA__G(struct dpa__u_a_bo_unique, (X)).p.c[0] & (N)), \
    struct dpa__u_a_bo_any   : (DPA__G(struct dpa__u_a_bo_any,    (X)).p.c[0] & (N)), \
    struct dpa__u_a_bo_any_ro: (DPA__G(struct dpa__u_a_bo_any_ro, (X)).p.c[0] & (N)), \
    struct dpa__u_a_bo_gc    : (DPA__G(struct dpa__u_a_bo_gc,     (X)).p.c[0] & (N)), \
    struct dpa__u_a_bo_gc_ro : (DPA__G(struct dpa__u_a_bo_gc_ro,  (X)).p.c[0] & (N)), \
    struct dpa__u_a_bo_hashed: (DPA__G(struct dpa__u_a_bo_hashed, (X)).p.c[0] & (N)), \
    \
    dpa_u__noop_t: 1 \
  )
// DPA_U__CHECK_GENERIC(dpa_u_bo_is_any_type)

#define dpa_u_bo_is_every_type(X, N) (_Generic((X), \
    dpa_u__boptr_t       : (DPA__G(dpa_u__boptr_t,        (X)) .c[0] & (N)), \
    dpa_u__boptr_t*      : (DPA__G(dpa_u__boptr_t*,       (X))->c[0] & (N)), \
    const dpa_u__boptr_t*: (DPA__G(const dpa_u__boptr_t*, (X))->c[0] & (N)), \
    \
    dpa_u_bo_t         : DPA_U_BO_SIMPLE & (N), \
    dpa_u_bo_ro_t      : DPA_U_BO_SIMPLE & (N), \
    dpa_u_p_bo_t*      : DPA_U_BO_SIMPLE & (N), \
    const dpa_u_p_bo_t*: DPA_U_BO_SIMPLE & (N), \
    \
    struct dpa__u_a_bo_unique: (DPA__G(struct dpa__u_a_bo_unique, (X)).p.c[0] & (N)), \
    struct dpa__u_a_bo_any   : (DPA__G(struct dpa__u_a_bo_any,    (X)).p.c[0] & (N)), \
    struct dpa__u_a_bo_any_ro: (DPA__G(struct dpa__u_a_bo_any_ro, (X)).p.c[0] & (N)), \
    struct dpa__u_a_bo_gc    : (DPA__G(struct dpa__u_a_bo_gc,     (X)).p.c[0] & (N)), \
    struct dpa__u_a_bo_gc_ro : (DPA__G(struct dpa__u_a_bo_gc_ro,  (X)).p.c[0] & (N)), \
    struct dpa__u_a_bo_hashed: (DPA__G(struct dpa__u_a_bo_hashed, (X)).p.c[0] & (N)), \
    \
    dpa_u__noop_t: 1 \
  ) == (N))
// DPA_U__CHECK_GENERIC(dpa_u_bo_is_every_type)

#define DPA_U__BO_TAG(X,T)   (*(const dpa_u__boptr_t*)(const uintptr_t[]){DPA_U_TAG((X),(T))})
#define DPA_U__BO_UNTAG(T,X) ((T)DPA_U_UNTAG(*(uint64_t*)((X).c)))

#define dpa__u_bo_to_p_bo(X) (&(struct{dpa_u_bo_t x;}){(X)}.x)
#define dpa__u_bo_ro_to_p_bo(X) (&(struct{dpa_u_bo_t x;}){dpa__u_bo_ro_to_p_bo_h(X)}.x)

dpa__u_api inline dpa_u_bo_t dpa__u_bo_ro_to_p_bo_h(dpa_u_bo_ro_t bo){
  return (dpa_u_bo_t){
    .size = bo.size,
    .data = (char*)bo.data,
  };
}

dpa__u_api inline dpa_u_bo_ro_t dpa__u_bo_to_bo_ro_h(dpa_u_bo_t bo){
  return (dpa_u_bo_ro_t){
    .size = bo.size,
    .data = bo.data,
  };
}
#define dpa_u_to_bo_ro(X) dpa__u_bo_to_bo_ro_h(dpa_u__to_bo(X))

#define dpa_u_to_bo_any(X) _Generic((X), \
    dpa_u_bo_t         : (dpa_u_a_bo_any_t   ){DPA_U__BO_TAG(dpa__u_bo_to_p_bo(DPA__G(dpa_u_bo_t, (X))), DPA_U_BO_SIMPLE)}, \
    dpa_u_bo_ro_t      : (dpa_u_a_bo_any_ro_t){DPA_U__BO_TAG(dpa__u_bo_ro_to_p_bo(DPA__G(dpa_u_bo_ro_t, (X))), DPA_U_BO_SIMPLE)}, \
    dpa_u_p_bo_t*      : (dpa_u_a_bo_any_t   ){DPA_U__BO_TAG(DPA__G(dpa_u_p_bo_t*, (X)), DPA_U_BO_SIMPLE)}, \
    const dpa_u_p_bo_t*: (dpa_u_a_bo_any_ro_t){DPA_U__BO_TAG(DPA__G(const dpa_u_p_bo_t*, (X)), DPA_U_BO_SIMPLE)}, \
    \
    struct dpa__u_a_bo_unique: (dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any   : (dpa_u_a_bo_any_t   ){DPA__G(struct dpa__u_a_bo_any, (X)).p}, \
    struct dpa__u_a_bo_any_ro: (dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_any_ro, (X)).p}, \
    struct dpa__u_a_bo_gc    : (dpa_u_a_bo_any_t   ){DPA__G(struct dpa__u_a_bo_gc, (X)).p}, \
    struct dpa__u_a_bo_gc_ro : (dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_gc_ro, (X)).p}, \
    struct dpa__u_a_bo_hashed: (dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_hashed, (X)).p}, \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_to_bo_any)

#define dpa_u_to_bo_any_ro(X) _Generic((X), \
    dpa_u_bo_t         : (dpa_u_a_bo_any_ro_t){DPA_U__BO_TAG(dpa__u_bo_to_p_bo(DPA__G(dpa_u_bo_t, (X))), DPA_U_BO_SIMPLE)}, \
    dpa_u_bo_ro_t      : (dpa_u_a_bo_any_ro_t){DPA_U__BO_TAG(dpa__u_bo_ro_to_p_bo(DPA__G(dpa_u_bo_ro_t, (X))), DPA_U_BO_SIMPLE)}, \
    dpa_u_p_bo_t*      : (dpa_u_a_bo_any_ro_t){DPA_U__BO_TAG(DPA__G(dpa_u_p_bo_t*, (X)), DPA_U_BO_SIMPLE)}, \
    const dpa_u_p_bo_t*: (dpa_u_a_bo_any_ro_t){DPA_U__BO_TAG(DPA__G(const dpa_u_p_bo_t*, (X)), DPA_U_BO_SIMPLE)}, \
    \
    struct dpa__u_a_bo_unique: (dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any   : (dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_any, (X)).p}, \
    struct dpa__u_a_bo_any_ro: (dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_any_ro, (X)).p}, \
    struct dpa__u_a_bo_gc    : (dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_gc, (X)).p}, \
    struct dpa__u_a_bo_gc_ro : (dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_gc_ro, (X)).p}, \
    struct dpa__u_a_bo_hashed: (dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_hashed, (X)).p}, \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_to_bo_any_ro)

/**
 * This is not a cryptographc hash function.
 * THis is meant for things like a hash map.
 */
#define dpa_u_bo_get_hash(X) _Generic((X), \
    dpa_u_bo_t         : dpa_u__bo_hash(dpa__u_bo_to_bo_ro_h(DPA__G(dpa_u_bo_t, (X)))), \
    dpa_u_bo_ro_t      : dpa_u__bo_hash(DPA__G(dpa_u_bo_ro_t, (X))), \
    dpa_u_p_bo_t*      : dpa_u__bo_hash(dpa__u_bo_to_bo_ro_h(*(dpa_u_bo_t*)DPA__G(dpa_u_p_bo_t*, (X)))), \
    const dpa_u_p_bo_t*: dpa_u__bo_hash(dpa__u_bo_to_bo_ro_h(*(dpa_u_bo_t*)DPA__G(const dpa_u_p_bo_t*, (X)))), \
    \
    struct dpa__u_a_bo_unique: dpa_u__bo_get_hash(DPA__G(struct dpa__u_a_bo_unique, (X)).p), \
    struct dpa__u_a_bo_any   : dpa_u__bo_get_hash(DPA__G(struct dpa__u_a_bo_any, (X)).p), \
    struct dpa__u_a_bo_any_ro: dpa_u__bo_get_hash(DPA__G(struct dpa__u_a_bo_any_ro, (X)).p), \
    struct dpa__u_a_bo_gc    : dpa_u__bo_get_hash(DPA__G(struct dpa__u_a_bo_gc, (X)).p), \
    struct dpa__u_a_bo_gc_ro : dpa_u__bo_get_hash(DPA__G(struct dpa__u_a_bo_gc_ro, (X)).p), \
    struct dpa__u_a_bo_hashed: dpa_u__bo_get_hash(DPA__G(struct dpa__u_a_bo_hashed, (X)).p), \
    \
    dpa_u__noop_t: 1 \
  )

dpa__u_api inline uint64_t dpa_u__bo_hash(dpa_u_bo_ro_t bo){
  // The commented out hash function is bad, but that makes it useful for testing.
  // uint64_t hash = 0;
  // memcpy(&hash, bo.data, bo.size > 8 ? 8 : bo.size);
  // return hash;
  inline
  uint64_t dpa_u_hash_64_FNV_1a_append_p(dpa_u_bo_ro_t bo, uint_fast64_t hash);
  const uint64_t basis = *(uint64_t*)dpa_u_seed;
  return dpa_u_hash_64_FNV_1a_append_p(bo, basis);
}

dpa__u_api inline uint64_t dpa_u__bo_get_hash(dpa_u__boptr_t boptr){
  if(dpa_u_bo_is_any_type(boptr, DPA_U_BO_HASHED))
    return DPA_U__BO_UNTAG(dpa__u_bo_hashed_t*, boptr)->hash;
  return dpa_u__bo_hash(dpa__u_bo_to_bo_ro_h(*DPA_U__BO_UNTAG(dpa_u_bo_t*, boptr)));
}
DPA_U__CHECK_GENERIC(dpa_u_bo_get_hash)

#define dpa_u__to_bo(X) _Generic((X), \
    dpa_u_bo_t         : *(const dpa_u_bo_t*)dpa__u_bo_to_p_bo(DPA__G(dpa_u_bo_t, (X))), \
    dpa_u_bo_ro_t      : *(const dpa_u_bo_t*)dpa__u_bo_ro_to_p_bo(DPA__G(dpa_u_bo_ro_t, (X))), \
    dpa_u_p_bo_t*      : *(const dpa_u_bo_t*)DPA__G(dpa_u_p_bo_t*, (X)), \
    const dpa_u_p_bo_t*: *(const dpa_u_bo_t*)DPA__G(const dpa_u_p_bo_t*, (X)), \
    \
    struct dpa__u_a_bo_unique: dpa_u__to_bo_h((const dpa_u__boptr_t*)DPA__G(struct dpa__u_a_bo_unique, (X)).p.c), \
    struct dpa__u_a_bo_any   : dpa_u__to_bo_h((const dpa_u__boptr_t*)DPA__G(struct dpa__u_a_bo_any, (X)).p.c), \
    struct dpa__u_a_bo_any_ro: dpa_u__to_bo_h((const dpa_u__boptr_t*)DPA__G(struct dpa__u_a_bo_any_ro, (X)).p.c), \
    struct dpa__u_a_bo_gc    : dpa_u__to_bo_h((const dpa_u__boptr_t*)DPA__G(struct dpa__u_a_bo_gc, (X)).p.c), \
    struct dpa__u_a_bo_gc_ro : dpa_u__to_bo_h((const dpa_u__boptr_t*)DPA__G(struct dpa__u_a_bo_gc_ro, (X)).p.c), \
    struct dpa__u_a_bo_hashed: dpa_u__to_bo_h((const dpa_u__boptr_t*)DPA__G(struct dpa__u_a_bo_hashed, (X)).p.c), \
    \
    dpa_u__noop_t: 1 \
  )

dpa__u_api inline dpa_u_bo_t dpa_u__to_bo_h(const dpa_u__boptr_t*restrict const boptr){
  if(dpa_u_bo_is_any_type(boptr, DPA_U_BO_SIMPLE))
    return *DPA_U__BO_UNTAG(dpa_u_bo_t*, *boptr);
  return (const dpa_u_bo_t){ .size=boptr->c[0]&7, .data=(char*)boptr->c+1 };
}
dpa__u_api inline dpa_u_bo_t dpa_u__inline_to_bo_h(const char*restrict const c){
  return (const dpa_u_bo_t){ .size=c[0]&7, .data=(char*)c+1 };
}
DPA_U__CHECK_GENERIC(dpa_u__to_bo)

#define dpa_u_bo_get_size(X) (dpa_u__to_bo((X)).size)
#define dpa_u_bo_get_data(X) (dpa_u__to_bo((X)).data)

#define dpa_u_bo_get_type(X) _Generic((X), \
    dpa_u_bo_t         : DPA_U_BO_SIMPLE, \
    dpa_u_bo_ro_t      : DPA_U_BO_SIMPLE, \
    dpa_u_p_bo_t*      : DPA_U_BO_SIMPLE, \
    const dpa_u_p_bo_t*: DPA_U_BO_SIMPLE, \
    \
    struct dpa__u_a_bo_unique: DPA__G(struct dpa__u_a_bo_unique, (X)).p.c[0], \
    struct dpa__u_a_bo_any   : DPA__G(struct dpa__u_a_bo_any, (X)).p.c[0], \
    struct dpa__u_a_bo_any_ro: DPA__G(struct dpa__u_a_bo_any_ro, (X)).p.c[0], \
    struct dpa__u_a_bo_gc    : DPA__G(struct dpa__u_a_bo_gc, (X)).p.c[0], \
    struct dpa__u_a_bo_gc_ro : DPA__G(struct dpa__u_a_bo_gc_ro, (X)).p.c[0], \
    struct dpa__u_a_bo_hashed: DPA__G(struct dpa__u_a_bo_hashed, (X)).p.c[0], \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_bo_get_type)

dpa__u_api const char* dpa_u_bo_type_to_string(enum dpa_u_bo_type_flags type);

dpa__u_api dpa_u_a_bo_unique_t dpa__u_bo_intern_h(dpa_u_a_bo_any_ro_t bo);
#define dpa_u_bo_intern(X) dpa__u_bo_intern_h(dpa_u_to_bo_any_ro((X)));

#define dpa_u_a_bo_unique_to_uint(X) (*(uint64_t*)(X).p.c)
//#define dpa_u_bo_unique_from_uint(X) (*(dpa_u_a_bo_unique_t*)(const uint64_t[]){(X)})

dpa__u_api inline dpa_u_a_bo_unique_t dpa_u_bo_unique_from_uint(const uint64_t x){
  dpa_u_a_bo_unique_t bo;
  memcpy(bo.p.c, &x, 8);
  return bo;
}

#define dpa_u_bo_compare(A, B) _Generic((A), \
    struct dpa__u_a_bo_unique: _Generic((B), \
        struct dpa__u_a_bo_unique: dpa__u_bo_compare_h1, \
        default: dpa__u_bo_compare_h2 \
      ), \
    default: dpa__u_bo_compare_h2 \
  )(dpa_u_to_bo_any_ro((A)), dpa_u_to_bo_any_ro((B)))

dpa__u_api inline int dpa__u_bo_compare_h1(dpa_u_a_bo_any_ro_t a, dpa_u_a_bo_any_ro_t b){
  return memcmp(&a,&b,sizeof(a));
}

dpa__u_api inline int dpa__u_bo_compare_h2(dpa_u_a_bo_any_ro_t a, dpa_u_a_bo_any_ro_t b){
  if(a.p.c[0] & b.p.c[0] & DPA_U_BO_UNIQUE)
    return memcmp(&a,&b,sizeof(a));
  const dpa_u_bo_ro_t sa = dpa_u_to_bo_ro(a);
  const dpa_u_bo_ro_t sb = dpa_u_to_bo_ro(b);
  const int r = (sa.size > sb.size) - (sa.size < sb.size);
  if(r) return r;
  if(sa.data == sb.data)
    return 0;
  return memcmp(sa.data, sb.data, sa.size);
}

dpa__u_api dpa_u_a_bo_unique_t dpa_u_bo_error(int err);
dpa__u_api int dpa_u_bo_error_to_errno(dpa_u_a_bo_unique_t bo);

#define dpa_u_bo_is_error(X) _Generic((X), \
    dpa_u_p_bo_t*: !DPA__G(dpa_u_p_bo_t*, (X)), \
    const dpa_u_p_bo_t*: !DPA__G(const dpa_u_p_bo_t*, (X)), \
    \
    struct dpa__u_a_bo_unique: DPA__G(struct dpa__u_a_bo_unique, (X)).p.c[0] > 7, \
    struct dpa__u_a_bo_any   : DPA__G(struct dpa__u_a_bo_any, (X)).p.c[0] > 7, \
    struct dpa__u_a_bo_any_ro: DPA__G(struct dpa__u_a_bo_any_ro, (X)).p.c[0] > 7, \
    struct dpa__u_a_bo_gc    : DPA__G(struct dpa__u_a_bo_gc, (X)).p.c[0] > 7, \
    struct dpa__u_a_bo_gc_ro : DPA__G(struct dpa__u_a_bo_gc_ro, (X)).p.c[0] > 7, \
    struct dpa__u_a_bo_hashed: DPA__G(struct dpa__u_a_bo_hashed, (X)).p.c[0] > 7, \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_bo_is_error)

dpa__u_api inline void dpa_u_bo_ref_h(dpa_u_a_bo_any_ro_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_bo_t* pbo = DPA_U__BO_UNTAG(dpa_u_bo_t*, bo.p);
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_UNIQUE)){
    dpa_u_refcount_ref(((dpa_u_refcount_freeable_t*)pbo)-1);
  }else{
    dpa_u_refcount_ref(((dpa_u_refcount_freeable_t*)(pbo->data))-1);
  }
}

dpa__u_api inline void dpa_u_bo_ref_h1(dpa_u_a_bo_unique_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_refcount_ref(((dpa_u_refcount_freeable_t*)DPA_U__BO_UNTAG(dpa_u_bo_t*, bo.p))-1);
}

dpa__u_api inline void dpa_u_bo_put_h(dpa_u_a_bo_any_ro_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_bo_t* pbo = DPA_U__BO_UNTAG(dpa_u_bo_t*, bo.p);
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_UNIQUE)){
    dpa_u_refcount_put(((dpa_u_refcount_freeable_t*)pbo)-1);
  }else{
    dpa_u_refcount_put(((dpa_u_refcount_freeable_t*)(pbo->data))-1);
  }
}

dpa__u_api inline void dpa_u_bo_put_h1(dpa_u_a_bo_unique_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_refcount_put(((dpa_u_refcount_freeable_t*)DPA_U__BO_UNTAG(dpa_u_bo_t*, bo.p))-1);
}

#define dpa_u_bo_ref(X) _Generic((X), \
    struct dpa__u_a_bo_unique: dpa_u_bo_ref_h1(DPA__G(struct dpa__u_a_bo_unique, (X))), \
    struct dpa__u_a_bo_any   : dpa_u_bo_ref_h((dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_any, (X)).p}), \
    struct dpa__u_a_bo_any_ro: dpa_u_bo_ref_h(DPA__G(struct dpa__u_a_bo_any_ro, (X))), \
    struct dpa__u_a_bo_gc    : dpa_u_bo_ref_h((dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_gc, (X)).p}), \
    struct dpa__u_a_bo_gc_ro : dpa_u_bo_ref_h((dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_gc_ro, (X)).p}), \
    struct dpa__u_a_bo_hashed: dpa_u_bo_ref_h((dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_hashed, (X)).p}), \
    \
    dpa_u__noop_t: 1 \
  )

#define dpa_u_bo_put(X) _Generic((X), \
    struct dpa__u_a_bo_unique: dpa_u_bo_put_h1(DPA__G(struct dpa__u_a_bo_unique, (X))), \
    struct dpa__u_a_bo_any   : dpa_u_bo_put_h((dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_any, (X)).p}), \
    struct dpa__u_a_bo_any_ro: dpa_u_bo_put_h(DPA__G(struct dpa__u_a_bo_any_ro, (X))), \
    struct dpa__u_a_bo_gc    : dpa_u_bo_put_h((dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_gc, (X)).p}), \
    struct dpa__u_a_bo_gc_ro : dpa_u_bo_put_h((dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_gc_ro, (X)).p}), \
    struct dpa__u_a_bo_hashed: dpa_u_bo_put_h((dpa_u_a_bo_any_ro_t){DPA__G(struct dpa__u_a_bo_hashed, (X)).p}), \
    \
    dpa_u__noop_t: 1 \
  )

#endif
