#ifndef DPA_U_BO_H
#define DPA_U_BO_H

#include <dpa/utils/common.h>
#include <dpa/utils/refcount.h>
#include <dpa/utils/tagged-pointer.h>
#include <dpa/utils/mem.h>

#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>
#include <string.h>
#include <assert.h>

typedef struct dpa_u__boptr {
  uint64_t value[1];
} dpa_u__boptr_t;
static_assert(sizeof(dpa_u__boptr_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u__boptr");

typedef struct dpa_u_bo_rw {
  size_t size;
  char* data;
} dpa_u_bo_rw_t;

typedef struct dpa_u_bo {
  union {
    struct {
      size_t size;
      const char* data;
    };
    char _c[1];
  };
} dpa_u_bo_t;

typedef struct dpa_u_bo_hashed {
  dpa_u_bo_t bo;
  uint64_t hash;
} dpa_u_bo_hashed_t;

typedef struct dpa_u_p_bo dpa_u_p_bo_t;

typedef struct dpa__u_a_bo_unique { dpa_u__boptr_t p; } dpa_u_a_bo_unique_t;
typedef struct dpa__u_a_bo_hashed { dpa_u__boptr_t p; } dpa_u_a_bo_hashed_t;
typedef struct dpa__u_a_bo_any    { dpa_u__boptr_t p; } dpa_u_a_bo_any_t;
typedef struct dpa__u_a_bo_gc     { dpa_u__boptr_t p; } dpa_u_a_bo_gc_t;

static_assert(sizeof(dpa_u_a_bo_unique_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_hashed_t) == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_any_t)    == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");
static_assert(sizeof(dpa_u_a_bo_gc_t)     == sizeof(uint64_t), "Unexpected padding in struct dpa_u_a_bo_unique_t");

typedef struct dpa_u__noop* dpa_u__noop_t;
#define DPA_U__CHECK_GENERIC(X) static inline \
  void DPA_U_CONCAT_E(dpa_u__sc__, __LINE__)(void){ (void)(X((dpa_u__noop_t)0)); /* A simple sanity check for the generic macros. */ }
#define DPA_U__CHECK_GENERIC_2(X, ...) static inline \
  void DPA_U_CONCAT_E(dpa_u__sc__, __LINE__)(void){ (void)(X((dpa_u__noop_t)0, __VA_ARGS__)); /* A simple sanity check for the generic macros. */ }

enum dpa_u_bo_type_flags {
  DPA_U_BO_STATIC     = 0x80,
  DPA_U_BO_REFCOUNTED = 0x40,
  DPA_U_BO_UNIQUE     = 0x20,
  DPA_U_BO_HASHED     = 0x10,
  DPA_U_BO_SIMPLE     = 0x08,
};

#define dpa_u_bo_is_any_type(X, N) _Generic((X), \
    dpa_u__boptr_t       : (DPA__G(dpa_u__boptr_t,         (X)).value[0] & DPA_U_MOVE_TAG(N)), \
    dpa_u__boptr_t*      : (DPA__G(dpa_u__boptr_t*,       (X))->value[0] & DPA_U_MOVE_TAG(N)), \
    const dpa_u__boptr_t*: (DPA__G(const dpa_u__boptr_t*, (X))->value[0] & DPA_U_MOVE_TAG(N)), \
    \
    dpa_u_bo_rw_t      : DPA_U_BO_SIMPLE & (N), \
    dpa_u_bo_t         : DPA_U_BO_SIMPLE & (N), \
    dpa_u_bo_hashed_t  : (DPA_U_BO_SIMPLE|DPA_U_BO_HASHED) & (N), \
    dpa_u_p_bo_t*      : DPA_U_BO_SIMPLE & (N), \
    const dpa_u_p_bo_t*: DPA_U_BO_SIMPLE & (N), \
    \
    struct dpa__u_a_bo_unique: (DPA__G(struct dpa__u_a_bo_unique, (X)).p.value[0] & DPA_U_MOVE_TAG(N)), \
    struct dpa__u_a_bo_hashed: (DPA__G(struct dpa__u_a_bo_hashed, (X)).p.value[0] & DPA_U_MOVE_TAG(N)), \
    struct dpa__u_a_bo_any   : (DPA__G(struct dpa__u_a_bo_any,    (X)).p.value[0] & DPA_U_MOVE_TAG(N)), \
    struct dpa__u_a_bo_gc    : (DPA__G(struct dpa__u_a_bo_gc,     (X)).p.value[0] & DPA_U_MOVE_TAG(N)), \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC_2(dpa_u_bo_is_any_type, 0)

#define dpa_u_bo_is_every_type(X, N) (_Generic((X), \
    dpa_u__boptr_t       : (DPA__G(dpa_u__boptr_t,        (X)) .value[0] & DPA_U_MOVE_TAG(N)), \
    dpa_u__boptr_t*      : (DPA__G(dpa_u__boptr_t*,       (X))->value[0] & DPA_U_MOVE_TAG(N)), \
    const dpa_u__boptr_t*: (DPA__G(const dpa_u__boptr_t*, (X))->value[0] & DPA_U_MOVE_TAG(N)), \
    \
    dpa_u_bo_rw_t      : DPA_U_BO_SIMPLE & DPA_U_MOVE_TAG(N), \
    dpa_u_bo_t         : DPA_U_BO_SIMPLE & DPA_U_MOVE_TAG(N), \
    dpa_u_bo_hashed_t  : (DPA_U_BO_SIMPLE|DPA_U_BO_HASHED) & (N), \
    dpa_u_p_bo_t*      : DPA_U_BO_SIMPLE & DPA_U_MOVE_TAG(N), \
    const dpa_u_p_bo_t*: DPA_U_BO_SIMPLE & DPA_U_MOVE_TAG(N), \
    \
    struct dpa__u_a_bo_unique: (DPA__G(struct dpa__u_a_bo_unique, (X)).p.value[0] & DPA_U_MOVE_TAG(N)), \
    struct dpa__u_a_bo_hashed: (DPA__G(struct dpa__u_a_bo_hashed, (X)).p.value[0] & DPA_U_MOVE_TAG(N)), \
    struct dpa__u_a_bo_any   : (DPA__G(struct dpa__u_a_bo_any,    (X)).p.value[0] & DPA_U_MOVE_TAG(N)), \
    struct dpa__u_a_bo_gc    : (DPA__G(struct dpa__u_a_bo_gc,     (X)).p.value[0] & DPA_U_MOVE_TAG(N)), \
    \
    dpa_u__noop_t: 1 \
  ) == DPA_U_MOVE_TAG(N))
DPA_U__CHECK_GENERIC_2(dpa_u_bo_is_every_type, 0)

#define DPA_U__BO_TAG(X,T)   ((const dpa_u__boptr_t){DPA_U_TAG((X),(T))})
#define DPA_U__BO_UNTAG(T,X) ((T)DPA_U_UNTAG((X).value[0]))

#define dpa__u_bo_to_p_bo_ro(X) (&(struct{dpa_u_bo_t x;}){dpa__u_bo_to_bo_ro_h(X)}.x)

dpa__u_api inline dpa_u_bo_t dpa__u_bo_to_bo_ro_h(dpa_u_bo_rw_t bo){
  return (dpa_u_bo_t){
    .size = bo.size,
    .data = bo.data,
  };
}
#define dpa_u_to_bo_ro(X) _Generic((X), \
    dpa_u_bo_rw_t      : dpa__u_bo_to_bo_ro_h(DPA__G(dpa_u_bo_rw_t, (X))), \
    dpa_u_bo_t         : DPA__G(dpa_u_bo_t, (X)), \
    dpa_u_bo_hashed_t  : DPA__G(dpa_u_bo_hashed_t, (X)).bo, \
    dpa_u_p_bo_t*      : dpa__u_bo_to_bo_ro_h(*(dpa_u_bo_rw_t*)DPA__G(dpa_u_p_bo_t*, (X))), \
    const dpa_u_p_bo_t*: *(const dpa_u_bo_t*)DPA__G(const dpa_u_p_bo_t*, (X)), \
    \
    struct dpa__u_a_bo_unique: dpa_u_to_bo_ro_h((const dpa_u__boptr_t*)DPA__G(struct dpa__u_a_bo_unique, (X)).p.value), \
    struct dpa__u_a_bo_hashed: dpa_u_to_bo_ro_h((const dpa_u__boptr_t*)DPA__G(struct dpa__u_a_bo_hashed, (X)).p.value), \
    struct dpa__u_a_bo_any   : dpa_u_to_bo_ro_h((const dpa_u__boptr_t*)DPA__G(struct dpa__u_a_bo_any,    (X)).p.value), \
    struct dpa__u_a_bo_gc    : dpa_u_to_bo_ro_h((const dpa_u__boptr_t*)DPA__G(struct dpa__u_a_bo_gc,     (X)).p.value), \
    \
    dpa_u__noop_t: 1 \
  )

dpa__u_api inline dpa_u_bo_t dpa_u_to_bo_ro_h(const dpa_u__boptr_t*restrict const boptr){
  if(dpa_u_bo_is_any_type(*boptr, DPA_U_BO_SIMPLE))
    return *DPA_U__BO_UNTAG(dpa_u_bo_t*, *boptr);
  return (const dpa_u_bo_t){ .size=DPA_U_GET_TAG(boptr->value[0])&7, .data=((char*)boptr->value)+1 };
}
DPA_U__CHECK_GENERIC(dpa_u_to_bo_ro)

#define dpa_u_to_bo_any(X) _Generic((X), \
    dpa_u_bo_rw_t      : (dpa_u_a_bo_any_t){DPA_U__BO_TAG(dpa__u_bo_to_p_bo_ro(DPA__G(dpa_u_bo_rw_t, (X))), DPA_U_BO_SIMPLE)}, \
    dpa_u_bo_t         : (dpa_u_a_bo_any_t){DPA_U__BO_TAG(DPA__G(dpa_u_bo_t, (X))._c, DPA_U_BO_SIMPLE)}, \
    dpa_u_bo_hashed_t  : (dpa_u_a_bo_any_t){DPA_U__BO_TAG(DPA__G(dpa_u_bo_hashed_t, (X)).bo._c, DPA_U_BO_SIMPLE)}, \
    dpa_u_p_bo_t*      : (dpa_u_a_bo_any_t){DPA_U__BO_TAG(dpa__u_bo_to_p_bo_ro(*(dpa_u_bo_rw_t*)DPA__G(dpa_u_p_bo_t*, (X))), DPA_U_BO_SIMPLE)}, \
    const dpa_u_p_bo_t*: (dpa_u_a_bo_any_t){DPA_U__BO_TAG(DPA__G(const dpa_u_p_bo_t*, (X)), DPA_U_BO_SIMPLE)}, \
    \
    struct dpa__u_a_bo_unique: (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_hashed: (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_hashed, (X)).p}, \
    struct dpa__u_a_bo_any   : (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_any,    (X)).p}, \
    struct dpa__u_a_bo_gc    : (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_gc,     (X)).p}, \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_to_bo_any)

#define dpa_u_to_bo_i_any(X) _Generic((X), \
    dpa_u_bo_rw_t      : (dpa_u_a_bo_any_t){DPA_U__BO_TAG(dpa__u_bo_to_p_bo_ro(DPA__G(dpa_u_bo_rw_t, (X))), DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)}, \
    dpa_u_bo_t         : (dpa_u_a_bo_any_t){DPA_U__BO_TAG(DPA__G(dpa_u_bo_t, (X))._c, DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)}, \
    dpa_u_bo_hashed_t  : (dpa_u_a_bo_any_t){DPA_U__BO_TAG(DPA__G(dpa_u_bo_hashed_t, (X)).bo._c, DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)}, \
    dpa_u_p_bo_t*      : (dpa_u_a_bo_any_t){DPA_U__BO_TAG(dpa__u_bo_to_p_bo_ro(*(dpa_u_bo_rw_t*)DPA__G(dpa_u_p_bo_t*, (X))), DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)}, \
    const dpa_u_p_bo_t*: (dpa_u_a_bo_any_t){DPA_U__BO_TAG(DPA__G(const dpa_u_p_bo_t*, (X)), DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)}, \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_to_bo_i_any)

dpa__u_api inline dpa_u__boptr_t dpa_u__to_bo_r_any__from_p_bo_ro(const dpa_u_bo_t* bo){
  uint64_t tag = DPA_U_BO_SIMPLE|DPA_U_BO_REFCOUNTED;
  if(dpa_u_refcount_is_static(dpa_u_container_of((char(*)[])bo->data, struct dpa_u_refcount_freeable_data, data)->refcount))
    tag |= DPA_U_BO_STATIC;
  return DPA_U__BO_TAG(bo, tag);
}

dpa__u_api inline dpa_u__boptr_t dpa_u__to_bo_r_any__from_p_bo_hashed(const dpa_u_bo_hashed_t* hbo){
  uint64_t tag = DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_REFCOUNTED;
  if(dpa_u_refcount_is_static(dpa_u_container_of((char(*)[])hbo->bo.data, struct dpa_u_refcount_freeable_data, data)->refcount))
    tag |= DPA_U_BO_STATIC;
  return DPA_U__BO_TAG(hbo, tag);
}

#define dpa_u_to_bo_r_any(X) _Generic((X), \
    dpa_u_bo_rw_t      : (dpa_u_a_bo_any_t){dpa_u__to_bo_r_any__from_p_bo_ro(dpa__u_bo_to_p_bo_ro(DPA__G(dpa_u_bo_rw_t, (X))))}, \
    dpa_u_bo_t         : (dpa_u_a_bo_any_t){dpa_u__to_bo_r_any__from_p_bo_ro((const dpa_u_bo_t*)DPA__G(dpa_u_bo_t, (X))._c)}, \
    dpa_u_bo_hashed_t  : (dpa_u_a_bo_any_t){dpa_u__to_bo_r_any__from_p_bo_hashed((const dpa_u_bo_hashed_t*)DPA__G(dpa_u_bo_hashed_t, (X)).bo._c)}, \
    dpa_u_p_bo_t*      : (dpa_u_a_bo_any_t){dpa_u__to_bo_r_any__from_p_bo_ro(dpa__u_bo_to_p_bo_ro(*(dpa_u_bo_rw_t*)DPA__G(dpa_u_p_bo_t*, (X))))}, \
    const dpa_u_p_bo_t*: (dpa_u_a_bo_any_t){dpa_u__to_bo_r_any__from_p_bo_ro((const dpa_u_bo_t*)DPA__G(const dpa_u_p_bo_t*, (X)))}, \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_to_bo_r_any)

/**
 * This is not a cryptographc hash function.
 * This is meant for things like a hash map.
 * Also, this is randomized un program startup.
 */
#define dpa_u_bo_get_hash(X) _Generic((X), \
    dpa_u_bo_rw_t      : dpa_u__bo_hash(dpa__u_bo_to_bo_ro_h(DPA__G(dpa_u_bo_rw_t, (X)))), \
    dpa_u_bo_t         : dpa_u__bo_hash(DPA__G(dpa_u_bo_t, (X))), \
    dpa_u_bo_hashed_t  : DPA__G(dpa_u_bo_hashed_t, (X)).hash, \
    dpa_u_p_bo_t*      : dpa_u__bo_hash(dpa__u_bo_to_bo_ro_h(*(dpa_u_bo_rw_t*)DPA__G(dpa_u_p_bo_t*, (X)))), \
    const dpa_u_p_bo_t*: dpa_u__bo_hash(*(dpa_u_bo_t*)DPA__G(const dpa_u_p_bo_t*, (X))), \
    \
    struct dpa__u_a_bo_unique: dpa_u__bo_get_hash(DPA__G(struct dpa__u_a_bo_unique, (X)).p), \
    struct dpa__u_a_bo_hashed: dpa_u__bo_get_hash(DPA__G(struct dpa__u_a_bo_hashed, (X)).p), \
    struct dpa__u_a_bo_any   : dpa_u__bo_get_hash(DPA__G(struct dpa__u_a_bo_any,    (X)).p), \
    struct dpa__u_a_bo_gc    : dpa_u__bo_get_hash(DPA__G(struct dpa__u_a_bo_gc,     (X)).p), \
    \
    dpa_u__noop_t: 1 \
  )

dpa__u_api inline uint64_t dpa_u__bo_hash(dpa_u_bo_t bo){
  // The commented out hash function is bad, but that makes it useful for testing.
  // uint64_t hash = 0;
  // memcpy(&hash, bo.data, bo.size > 8 ? 8 : bo.size);
  // return hash;
#ifdef __llvm__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundefined-inline"
#endif
  inline
  uint64_t dpa_u_hash_64_FNV_1a_append_p(dpa_u_bo_t bo, uint_fast64_t hash);
#ifdef __llvm__
#pragma clang diagnostic pop
#endif
  const uint64_t basis = *(uint64_t*)dpa_u_seed;
  return dpa_u_hash_64_FNV_1a_append_p(bo, basis);
}

dpa__u_api inline uint64_t dpa_u__bo_get_hash(dpa_u__boptr_t boptr){
  if(dpa_u_bo_is_any_type(boptr, DPA_U_BO_HASHED))
    return DPA_U__BO_UNTAG(dpa_u_bo_hashed_t*, boptr)->hash;
  return dpa_u__bo_hash(*DPA_U__BO_UNTAG(dpa_u_bo_t*, boptr));
}
DPA_U__CHECK_GENERIC(dpa_u_bo_get_hash)

#define dpa_u_bo_get_size(X) (dpa_u_to_bo_ro((X)).size)
#define dpa_u_bo_get_data(X) (dpa_u_to_bo_ro((X)).data)

#define dpa_u_bo_get_type(X) _Generic((X), \
    dpa_u_bo_rw_t      : DPA_U_BO_SIMPLE, \
    dpa_u_bo_t         : DPA_U_BO_SIMPLE, \
    dpa_u_bo_hashed_t  : DPA_U_BO_SIMPLE|DPA_U_BO_HASHED, \
    dpa_u_p_bo_t*      : DPA_U_BO_SIMPLE, \
    const dpa_u_p_bo_t*: DPA_U_BO_SIMPLE, \
    \
    struct dpa__u_a_bo_unique: DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_unique, (X)).p.value[0]), \
    struct dpa__u_a_bo_hashed: DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_hashed, (X)).p.value[0]), \
    struct dpa__u_a_bo_any   : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_any,    (X)).p.value[0]), \
    struct dpa__u_a_bo_gc    : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_gc,     (X)).p.value[0]), \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_bo_get_type)

dpa__u_api const char* dpa_u_bo_type_to_string(enum dpa_u_bo_type_flags type);

dpa__u_api dpa_u_a_bo_unique_t dpa__u_bo_intern_h(dpa_u_a_bo_any_t bo);
#define dpa_u_bo_intern(X) dpa__u_bo_intern_h(dpa_u_to_bo_any((X)))

#define dpa_u_a_bo_unique_to_uint(X) _Generic((X), dpa_u_a_bo_unique_t: (X).p.value[0])
#define dpa_u_bo_unique_from_uint(X) ((dpa_u_a_bo_unique_t){.p.value[0]=(X)})

#define dpa_u_bo_compare(A, B) _Generic((A), \
    struct dpa__u_a_bo_unique: _Generic((B), \
        struct dpa__u_a_bo_unique: dpa__u_bo_compare_h1, \
        default: dpa__u_bo_compare_h2 \
      ), \
    default: dpa__u_bo_compare_h2 \
  )(dpa_u_to_bo_any((A)), dpa_u_to_bo_any((B)))

dpa__u_api inline int dpa__u_bo_compare_h1(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b){
  return memcmp(&a,&b,sizeof(a));
}

dpa__u_api inline int dpa__u_bo_compare_h2(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b){
  if(a.p.value[0] & b.p.value[0] & DPA_U_MOVE_TAG(DPA_U_BO_UNIQUE))
    return memcmp(&a,&b,sizeof(a));
  const dpa_u_bo_t sa = dpa_u_to_bo_ro(a);
  const dpa_u_bo_t sb = dpa_u_to_bo_ro(b);
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
    struct dpa__u_a_bo_unique: DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_unique, (X)).p.value[0]) < 8, \
    struct dpa__u_a_bo_hashed: DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_hashed, (X)).p.value[0]) < 8, \
    struct dpa__u_a_bo_any   : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_any,    (X)).p.value[0]) < 8, \
    struct dpa__u_a_bo_gc    : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_gc,     (X)).p.value[0]) < 8, \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_bo_is_error)

dpa__u_api inline void dpa_u_bo_ref_h(dpa_u_a_bo_any_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_bo_rw_t* pbo = DPA_U__BO_UNTAG(dpa_u_bo_rw_t*, bo.p);
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_UNIQUE)){
    dpa_u_refcount_ref(((dpa_u_refcount_freeable_t*)pbo)-1);
  }else{
    dpa_u_refcount_ref(((dpa_u_refcount_freeable_t*)(pbo->data))-1);
  }
}

dpa__u_api inline void dpa_u_bo_ref_h1(dpa_u_a_bo_unique_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_refcount_ref(((dpa_u_refcount_freeable_t*)DPA_U__BO_UNTAG(dpa_u_bo_rw_t*, bo.p))-1);
}

dpa__u_api inline void dpa_u_bo_put_h(dpa_u_a_bo_any_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_bo_rw_t* pbo = DPA_U__BO_UNTAG(dpa_u_bo_rw_t*, bo.p);
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_UNIQUE)){
    dpa_u_refcount_put(((dpa_u_refcount_freeable_t*)pbo)-1);
  }else{
    dpa_u_refcount_put(((dpa_u_refcount_freeable_t*)(pbo->data))-1);
  }
}

dpa__u_api inline void dpa_u_bo_put_h1(dpa_u_a_bo_unique_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_refcount_put(((dpa_u_refcount_freeable_t*)DPA_U__BO_UNTAG(dpa_u_bo_rw_t*, bo.p))-1);
}

dpa__u_api inline dpa_u_refcount_freeable_t* dpa_u_bo_get_refcount_h(dpa_u_a_bo_any_t bo){
  dpa_u_bo_rw_t* pbo = DPA_U__BO_UNTAG(dpa_u_bo_rw_t*, bo.p);
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_STATIC))
    return &dpa_u_refcount_static_v_freeable;
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_UNIQUE))
    return ((dpa_u_refcount_freeable_t*)pbo) - 1;
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return &dpa_u_container_of((char(*)[])pbo->data, dpa_u_refcount_freeable_data_t, data)->refcount;
  return 0;
}

dpa__u_api inline dpa_u_refcount_freeable_t* dpa_u_bo_get_refcount_h1(dpa_u_a_bo_unique_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return &dpa_u_refcount_static_v_freeable;
  return ((dpa_u_refcount_freeable_t*)DPA_U__BO_UNTAG(dpa_u_bo_rw_t*, bo.p)) - 1;
}

#define dpa_u_bo_ref(X) _Generic((X), \
    struct dpa__u_a_bo_unique: dpa_u_bo_ref_h1(DPA__G(struct dpa__u_a_bo_unique, (X))), \
    struct dpa__u_a_bo_hashed: dpa_u_bo_ref_h((dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_hashed, (X)).p}), \
    struct dpa__u_a_bo_any   : dpa_u_bo_ref_h(DPA__G(struct dpa__u_a_bo_any, (X))), \
    struct dpa__u_a_bo_gc    : dpa_u_bo_ref_h((dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_gc, (X)).p}), \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_bo_ref)

#define dpa_u_bo_put(X) _Generic((X), \
    struct dpa__u_a_bo_unique: dpa_u_bo_put_h1(DPA__G(struct dpa__u_a_bo_unique, (X))), \
    struct dpa__u_a_bo_hashed: dpa_u_bo_put_h((dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_hashed, (X)).p}), \
    struct dpa__u_a_bo_any   : dpa_u_bo_put_h(DPA__G(struct dpa__u_a_bo_any, (X))), \
    struct dpa__u_a_bo_gc    : dpa_u_bo_put_h((dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_gc, (X)).p}), \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_bo_put)

#define dpa_u_bo_get_refcount(X) _Generic((X), \
    struct dpa__u_a_bo_unique: dpa_u_bo_get_refcount_h1(DPA__G(struct dpa__u_a_bo_unique, (X))), \
    struct dpa__u_a_bo_hashed: dpa_u_bo_get_refcount_h((dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_hashed, (X)).p}), \
    struct dpa__u_a_bo_any   : dpa_u_bo_get_refcount_h(DPA__G(struct dpa__u_a_bo_any, (X))), \
    struct dpa__u_a_bo_gc    : dpa_u_bo_get_refcount_h((dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_gc, (X)).p}), \
    \
    dpa_u__noop_t: 1 \
  )
DPA_U__CHECK_GENERIC(dpa_u_bo_get_refcount)

#define DPA__U_INLINE_STRING(...) DPA__U_INLINE_STRING_2(__VA_ARGS__ +0,0,0,0,0,0,0,0,7,6,5,4,3,2,1)

#if BYTE_ORDER == LITTLE_ENDIAN
#define DPA__U_INLINE_STRING_2(x1,x2,x3,x4,x5,x6,x7,_1,_2,_3,_4,_5,_6,_7,n,...) \
  ((uint64_t)(n )      | ((uint64_t)(x1)<< 8) | ((uint64_t)(x2)<<16) | ((uint64_t)(x3)<<24) | \
  ((uint64_t)(x4)<<32) | ((uint64_t)(x5)<<40) | ((uint64_t)(x6)<<48) | ((uint64_t)(x7)<<56) )
#elif BYTE_ORDER == BIG_ENDIAN
#define DPA__U_INLINE_STRING_2(x1,x2,x3,x4,x5,x6,x7,_1,_2,_3,_4,_5,_6,_7,n,...) \
  ((uint64_t)(n )>>56  | ((uint64_t)(x1)>>48) | ((uint64_t)(x2)>>40) | ((uint64_t)(x3)>>32) | \
  ((uint64_t)(x4)>>24) | ((uint64_t)(x5)<<40) | ((uint64_t)(x6)<<48) | ((uint64_t)(x7)<<56) )
#endif

#endif
