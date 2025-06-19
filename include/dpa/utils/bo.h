#ifndef DPA_U_BO_H
#define DPA_U_BO_H

#include <dpa/utils/common.h>
#include <dpa/utils/refcount.h>
#include <dpa/utils/tagged-pointer.h>
#include <dpa/utils/mem.h>
#include <dpa/utils/_bo/bo-type.h>
#include <dpa/utils/_hash/hash.h>

#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>
#include <string.h>
#include <assert.h>


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

union dpa__u_bo_cmem {
  dpa__u_bo_refcounted_hashed_t rh;
  struct {
    dpa_u_refcount_freeable_t* refcount;
    dpa__u_bo_hashed_t hashed;
  } hr;
};

#ifndef DPA_U_BO_NO_HACKS
static_assert(offsetof(union dpa__u_bo_cmem, rh.rbo.bo) == offsetof(union dpa__u_bo_cmem, hr.hashed.bo), "BO offset wasn't aligned");
static_assert(offsetof(union dpa__u_bo_cmem, rh.hash) == offsetof(union dpa__u_bo_cmem, hr.hashed.hash), "hash offset wasn't aligned");
#endif

enum dpa_u_bo_type_flags {
  DPA_U_BO_STATIC     = 0x80,
  DPA_U_BO_REFCOUNTED = 0x40,
  DPA_U_BO_UNIQUE     = 0x20,
  DPA_U_BO_HASHED     = 0x10,
  DPA_U_BO_SIMPLE     = 0x08,
};
#define DPA_U_BO_STATIC DPA_U_BO_STATIC
#define DPA_U_BO_REFCOUNTED DPA_U_BO_REFCOUNTED
#define DPA_U_BO_UNIQUE DPA_U_BO_UNIQUE
#define DPA_U_BO_HASHED DPA_U_BO_HASHED
#define DPA_U_BO_SIMPLE DPA_U_BO_SIMPLE

#define dpa_u_bo_is_error(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_unique,     (X)).p.value[0]) < 8, \
    struct dpa__u_a_bo_any       : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_any,        (X)).p.value[0]) < 8, \
    struct dpa__u_a_bo_gc        : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_gc,         (X)).p.value[0]) < 8, \
    struct dpa__u_a_bo_refcounted: DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p.value[0]) < 8, \
    struct dpa__u_a_bo_hashed    : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_hashed,     (X)).p.value[0]) < 8 \
  )

#define dpa_u_bo_get_type(X) _Generic((X), \
    dpa__u_boptr_t       : DPA_U_GET_TAG(DPA__G(dpa__u_boptr_t,       (X)).value[0]), \
    dpa__u_boptr_t*      : DPA_U_GET_TAG(DPA__G(dpa__u_boptr_t*,      (X))->value[0]), \
    const dpa__u_boptr_t*: DPA_U_GET_TAG(DPA__G(const dpa__u_boptr_t*,(X))->value[0]), \
    \
    struct dpa_u_bo: DPA_U_BO_SIMPLE, \
    struct dpa_u_bo*: DPA_U_BO_SIMPLE, \
    const struct dpa_u_bo*: DPA_U_BO_SIMPLE, \
    \
    struct dpa__u_a_bo_unique    : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_unique,     (X)).p.value[0]), \
    struct dpa__u_a_bo_any       : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_any,        (X)).p.value[0]), \
    struct dpa__u_a_bo_gc        : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_gc,         (X)).p.value[0]), \
    struct dpa__u_a_bo_refcounted: DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p.value[0]), \
    struct dpa__u_a_bo_hashed    : DPA_U_GET_TAG(DPA__G(struct dpa__u_a_bo_hashed,     (X)).p.value[0]) \
  )

#define dpa_u_bo_is_any_type(X, N) (!!(dpa_u_bo_get_type((X)) & (N)))
#define dpa_u_bo_is_every_type(X, N) ((dpa_u_bo_get_type((X)) & (N)) == (N))

#define DPA__U_BO_TAG(X,T)   ((const dpa__u_boptr_t){{DPA_U_TAG((X),(T))}})
#define DPA__U_BO_UNTAG(T,X) ((T)DPA_U_UNTAG((X).value[0]))

#define dpa_u_to_bo(X) _Generic((X), \
    dpa_u_bo_t: DPA__G(dpa_u_bo_t, (X)), \
    \
    struct dpa__u_a_bo_unique    : dpa__u_to_bo_h((const dpa__u_boptr_t*)DPA__G(struct dpa__u_a_bo_unique,     (X)).p.value), \
    struct dpa__u_a_bo_any       : dpa__u_to_bo_h((const dpa__u_boptr_t*)DPA__G(struct dpa__u_a_bo_any,        (X)).p.value), \
    struct dpa__u_a_bo_gc        : dpa__u_to_bo_h((const dpa__u_boptr_t*)DPA__G(struct dpa__u_a_bo_gc,         (X)).p.value), \
    struct dpa__u_a_bo_refcounted: dpa__u_to_bo_h((const dpa__u_boptr_t*)DPA__G(struct dpa__u_a_bo_refcounted, (X)).p.value), \
    struct dpa__u_a_bo_hashed    : dpa__u_to_bo_h((const dpa__u_boptr_t*)DPA__G(struct dpa__u_a_bo_hashed,     (X)).p.value) \
  )

dpa__u_api dpa_u_reproducible inline dpa_u_bo_t dpa__u_to_bo_h(const dpa__u_boptr_t*restrict const boptr){
  if(dpa_u_bo_is_any_type(*boptr, DPA_U_BO_SIMPLE))
    return *DPA__U_BO_UNTAG(dpa_u_bo_t*, *boptr);
  return (const dpa_u_bo_t){ .size=DPA_U_GET_TAG(boptr->value[0])&7, .data=((char*)boptr->value)+1 };
}

#define dpa_u_to_bo_any(X) _Generic((X), \
    dpa_u_bo_t: (dpa_u_a_bo_any_t){DPA__U_BO_TAG(DPA__G(dpa_u_bo_t, (X))._c, DPA_U_BO_SIMPLE)}, \
    \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_unique,     (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_any,        (X)).p}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_gc,         (X)).p}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_refcounted, (X)).p}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_hashed,     (X)).p} \
  )

#define dpa_u_to_bo_any_static(X) _Generic((X), \
    dpa_u_bo_t: (dpa_u_a_bo_any_t){DPA__U_BO_TAG(DPA__G(dpa_u_bo_t, (X))._c, DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)} \
  )

dpa__u_api dpa_u_unsequenced inline dpa__u_boptr_t dpa__u_to_bo_gc_h(dpa__u_boptr_t p){
  if( dpa_u_bo_is_any_type(p, DPA_U_BO_UNIQUE|DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)
   ||!dpa_u_bo_is_any_type(p, DPA_U_BO_SIMPLE)
  ) return p;
  return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
}

#define dpa_u_to_bo_gc(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_gc_t){DPA__G(struct dpa__u_a_bo_unique,     (X)).p}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_gc_t){DPA__G(struct dpa__u_a_bo_gc,         (X)).p}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_gc_t){DPA__G(struct dpa__u_a_bo_refcounted, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_gc_t){dpa__u_to_bo_gc_h(DPA__G(struct dpa__u_a_bo_any,   (X)).p)}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_gc_t){dpa__u_to_bo_gc_h(DPA__G(struct dpa__u_a_bo_hashed,(X)).p)} \
  )

#define dpa_u_to_bo_gc_static(X) _Generic((X), \
    dpa_u_bo_t: (dpa_u_a_bo_gc_t){DPA__U_BO_TAG(DPA__G(dpa_u_bo_t, (X))._c, DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)} \
  )

dpa__u_api dpa_u_unsequenced inline dpa__u_boptr_t dpa__u_to_bo_refcounted_h(dpa__u_boptr_t p){
  if(dpa_u_bo_is_any_type(p, DPA_U_BO_REFCOUNTED) && !dpa_u_bo_is_any_type(p, DPA_U_BO_UNIQUE))
    return p;
  return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
}
#define dpa_u_to_bo_refcounted(X) _Generic((X), \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_refcounted_t){dpa__u_to_bo_refcounted_h(DPA__G(struct dpa__u_a_bo_gc,     (X)).p)}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_refcounted_t){DPA__G(struct dpa__u_a_bo_refcounted, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_refcounted_t){dpa__u_to_bo_refcounted_h(DPA__G(struct dpa__u_a_bo_any,    (X)).p)}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_refcounted_t){dpa__u_to_bo_refcounted_h(DPA__G(struct dpa__u_a_bo_hashed, (X)).p)} \
  )

dpa__u_api dpa_u_unsequenced inline dpa__u_boptr_t dpa__u_to_bo_hashed_h(dpa__u_boptr_t p){
  if(dpa_u_bo_is_any_type(p, DPA_U_BO_HASHED))
    return p;
  return (dpa__u_boptr_t){DPA__U_INLINE_STRING('E','I','N','V','A','L')};
}
#define dpa_u_to_bo_hashed(X) _Generic((X), \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_hashed_t){dpa__u_to_bo_hashed_h(DPA__G(struct dpa__u_a_bo_gc,     (X)).p)}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_hashed_t){dpa__u_to_bo_hashed_h(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p)}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_hashed_t){dpa__u_to_bo_hashed_h(DPA__G(struct dpa__u_a_bo_any,    (X)).p)}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_hashed_t){DPA__G(struct dpa__u_a_bo_hashed, (X)).p} \
  )

/**
 * This is not a cryptographic hash function.
 * This is meant for things like a hash map.
 * Also, this is randomized un program startup.
 */
#define dpa_u_bo_get_hash(X) _Generic((X), \
    dpa_u_bo_t: dpa__u_bo_hash(DPA__G(dpa_u_bo_t, (X))), \
    \
    struct dpa__u_a_bo_unique    : dpa__u_bo_get_hash(DPA__G(struct dpa__u_a_bo_unique,     (X)).p), \
    struct dpa__u_a_bo_any       : dpa__u_bo_get_hash(DPA__G(struct dpa__u_a_bo_any,        (X)).p), \
    struct dpa__u_a_bo_gc        : dpa__u_bo_get_hash(DPA__G(struct dpa__u_a_bo_gc,         (X)).p), \
    struct dpa__u_a_bo_refcounted: dpa__u_bo_get_hash(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p), \
    struct dpa__u_a_bo_hashed    : dpa__u_bo_get_hash(DPA__G(struct dpa__u_a_bo_hashed,     (X)).p) \
  )

dpa__u_api dpa_u_reproducible inline uint64_t dpa__u_bo_hash(dpa_u_bo_t bo){
  // The commented out hash function is bad, but that makes it useful for testing.
  // uint64_t hash = 0;
  // memcpy(&hash, bo.data, bo.size > 8 ? 8 : bo.size);
  // return hash;
  const uint64_t basis = *(uint64_t*)dpa_u_seed;
  return dpa_u_hash_64_FNV_1a_append_p(bo, basis);
}

dpa__u_api dpa_u_reproducible inline uint64_t dpa__u_bo_get_hash(const dpa__u_boptr_t boptr){
  if(dpa_u_bo_is_any_type(boptr, DPA_U_BO_HASHED)){
    return dpa_u_bo_is_any_type(boptr, DPA_U_BO_REFCOUNTED)
      ? dpa_u_container_of(DPA__U_BO_UNTAG(dpa_u_bo_t*, boptr), dpa__u_bo_refcounted_hashed_t, rbo.bo)->hash
      : DPA__U_BO_UNTAG(dpa__u_bo_hashed_t*, boptr)->hash;
  }
  return dpa__u_bo_hash(dpa__u_to_bo_h(&boptr));
}

#define dpa_u_bo_get_size(X) (dpa_u_to_bo((X)).size)
#define dpa_u_bo_get_data(X) (dpa_u_to_bo((X)).data)

dpa__u_api dpa_u_unsequenced const char* dpa_u_bo_type_to_string(enum dpa_u_bo_type_flags type);

dpa__u_api dpa_u_a_bo_unique_t dpa__u_bo_intern_h(dpa_u_a_bo_any_t bo);
#define dpa_u_bo_intern(X) dpa__u_bo_intern_h(dpa_u_to_bo_any((X)))

#define dpa_u_bo_unique_to_uint(X) _Generic((X), dpa_u_a_bo_unique_t: (X).p.value[0])
#define dpa_u_bo_unique_from_uint(X) ((dpa_u_a_bo_unique_t){.p.value[0]=(X)})

#define dpa_u_bo_compare(A, B) _Generic((A), \
    struct dpa__u_a_bo_unique: _Generic((B), \
        struct dpa__u_a_bo_unique: dpa__u_bo_compare_h1, \
        default: dpa__u_bo_compare_h2 \
      ), \
    default: dpa__u_bo_compare_h2 \
  )(dpa_u_to_bo_any((A)), dpa_u_to_bo_any((B)))

dpa__u_api dpa_u_unsequenced inline int dpa__u_bo_compare_h1(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b){
  return memcmp(&a,&b,sizeof(a));
}

dpa__u_api dpa_u_reproducible inline int dpa__u_bo_compare_h2(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b){
  if(a.p.value[0] & b.p.value[0] & DPA_U_MOVE_TAG(DPA_U_BO_UNIQUE)
   || dpa_u_bo_is_error(a) || dpa_u_bo_is_error(b)
  ) return memcmp(&a,&b,sizeof(a));
  const dpa_u_bo_t sa = dpa_u_to_bo(a);
  const dpa_u_bo_t sb = dpa_u_to_bo(b);
  const int r = (sa.size > sb.size) - (sa.size < sb.size);
  if(r) return r;
  if(sa.data == sb.data)
    return 0;
  return memcmp(sa.data, sb.data, sa.size);
}

#define dpa_u_bo_compare_data(A, B) dpa_u_bo_compare_data_p(dpa_u_to_bo_any((A)), dpa_u_to_bo_any((B)))
dpa__u_api dpa_u_reproducible inline int dpa_u_bo_compare_data_p(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b){
  if(!(a.p.value[0] & b.p.value[0] & DPA_U_MOVE_TAG(DPA_U_BO_SIMPLE)))
    return memcmp(&a,&b,sizeof(a));
  const dpa_u_bo_t sa = dpa_u_to_bo(a);
  const dpa_u_bo_t sb = dpa_u_to_bo(b);
  const int r = (sa.size > sb.size) - (sa.size < sb.size);
  if(r) return r;
  if(sa.data == sb.data)
    return 0;
  return memcmp(sa.data, sb.data, sa.size);
}

#define dpa_u_bo_is_same(A, B) dpa_u_bo_is_same_p(dpa_u_to_bo_any((A)), dpa_u_to_bo_any((B)))
dpa__u_api dpa_u_reproducible inline int dpa_u_bo_is_same_p(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b){
  return (a.p.value[0] & ~DPA_U_MOVE_TAG(DPA_U_BO_STATIC|DPA_U_BO_REFCOUNTED|DPA_U_BO_UNIQUE|DPA_U_BO_HASHED))
      == (b.p.value[0] & ~DPA_U_MOVE_TAG(DPA_U_BO_STATIC|DPA_U_BO_REFCOUNTED|DPA_U_BO_UNIQUE|DPA_U_BO_HASHED));
}

#define dpa_u_bo_is_equal(A, B) _Generic((A), \
    struct dpa__u_a_bo_unique: _Generic((B), \
        struct dpa__u_a_bo_unique: dpa__u_bo_is_equal_h1, \
        default: dpa__u_bo_is_equal_h2 \
      ), \
    default: dpa__u_bo_is_equal_h2 \
  )(dpa_u_to_bo_any((A)), dpa_u_to_bo_any((B)))

dpa__u_api dpa_u_unsequenced inline int dpa__u_bo_is_equal_h1(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b){
  return a.p.value[0] == b.p.value[0];
}

dpa__u_api dpa_u_reproducible inline int dpa__u_bo_is_equal_h2(dpa_u_a_bo_any_t a, dpa_u_a_bo_any_t b){
  if(a.p.value[0] & b.p.value[0] & DPA_U_MOVE_TAG(DPA_U_BO_UNIQUE)
   || dpa_u_bo_is_error(a) || dpa_u_bo_is_error(b)
  ) return a.p.value[0] == b.p.value[0];
  const dpa_u_bo_t sa = dpa_u_to_bo(a);
  const dpa_u_bo_t sb = dpa_u_to_bo(b);
  if(sa.size != sb.size)
    return false;
  if(sa.data == sb.data)
    return true;
  return !memcmp(sa.data, sb.data, sa.size);
}

dpa__u_api dpa_u_unsequenced dpa_u_a_bo_unique_t dpa_u_bo_error(int err);
dpa__u_api dpa_u_unsequenced int dpa_u_bo_error_to_errno(dpa_u_a_bo_unique_t bo);

dpa__u_api inline void dpa__u_bo_ref_h(const dpa__u_boptr_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_bo_t* pbo = DPA__U_BO_UNTAG(dpa_u_bo_t*, bo);
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_UNIQUE)){
    dpa_u_refcount_ref(((dpa_u_refcount_freeable_t*)pbo)-1);
  }else{
    dpa_u_refcount_ref(dpa_u_container_of(pbo, dpa__u_bo_refcounted_t, bo)->refcount);
  }
}

dpa__u_api inline void dpa__u_bo_ref_h2(const dpa__u_boptr_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_SIMPLE))
    return;
  dpa_u_refcount_ref(dpa_u_container_of(DPA__U_BO_UNTAG(dpa_u_bo_t*, bo), dpa__u_bo_refcounted_t, bo)->refcount);
}

dpa__u_api inline void dpa__u_bo_ref_h1(const dpa_u_a_bo_unique_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_refcount_ref(((dpa_u_refcount_freeable_t*)DPA__U_BO_UNTAG(dpa_u_bo_t*, bo.p))-1);
}

dpa__u_api inline void dpa__u_bo_put_h(const dpa__u_boptr_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_bo_t* pbo = DPA__U_BO_UNTAG(dpa_u_bo_t*, bo);
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_UNIQUE)){
    dpa_u_refcount_put(((dpa_u_refcount_freeable_t*)pbo)-1);
  }else{
    dpa_u_refcount_put(dpa_u_container_of(pbo, dpa__u_bo_refcounted_t, bo)->refcount);
  }
}

dpa__u_api inline void dpa__u_bo_put_h2(const dpa__u_boptr_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_SIMPLE))
    return;
  dpa_u_refcount_put(dpa_u_container_of(DPA__U_BO_UNTAG(dpa_u_bo_t*, bo), dpa__u_bo_refcounted_t, bo)->refcount);
}

dpa__u_api inline void dpa__u_bo_put_h1(const dpa_u_a_bo_unique_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return;
  dpa_u_refcount_put(((dpa_u_refcount_freeable_t*)DPA__U_BO_UNTAG(dpa_u_bo_t*, bo.p))-1);
}

dpa__u_api dpa_u_reproducible inline dpa_u_refcount_freeable_t* dpa__u_bo_get_refcount_h(const dpa__u_boptr_t bo){
  dpa_u_bo_t* pbo = DPA__U_BO_UNTAG(dpa_u_bo_t*, bo);
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return &dpa_u_refcount_static_v_freeable;
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_UNIQUE))
    return ((dpa_u_refcount_freeable_t*)pbo) - 1;
  return dpa_u_container_of(pbo, dpa__u_bo_refcounted_t, bo)->refcount;
}

dpa__u_api dpa_u_unsequenced inline dpa_u_refcount_freeable_t* dpa__u_bo_get_refcount_h1(const dpa_u_a_bo_unique_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_SIMPLE))
    return 0;
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    return &dpa_u_refcount_static_v_freeable;
  return ((dpa_u_refcount_freeable_t*)DPA__U_BO_UNTAG(dpa_u_bo_t*, bo.p)) - 1;
}

dpa__u_api dpa_u_unsequenced inline dpa_u_refcount_freeable_t* dpa__u_bo_get_refcount_h2(const dpa__u_boptr_t bo){
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_SIMPLE))
    return 0;
  return dpa_u_container_of(DPA__U_BO_UNTAG(dpa_u_bo_t*, bo), dpa__u_bo_refcounted_t, bo)->refcount;
}

#define dpa_u_bo_ref(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : dpa__u_bo_ref_h1(DPA__G(struct dpa__u_a_bo_unique,     (X))), \
    struct dpa__u_a_bo_any       : dpa__u_bo_ref_h (DPA__G(struct dpa__u_a_bo_any,        (X)).p), \
    struct dpa__u_a_bo_gc        : dpa__u_bo_ref_h (DPA__G(struct dpa__u_a_bo_gc,         (X)).p), \
    struct dpa__u_a_bo_hashed    : dpa__u_bo_ref_h (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p), \
    struct dpa__u_a_bo_refcounted: dpa__u_bo_ref_h2(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p) \
  )

#define dpa_u_bo_put(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : dpa__u_bo_put_h1(DPA__G(struct dpa__u_a_bo_unique,    (X))), \
    struct dpa__u_a_bo_any       : dpa__u_bo_put_h (DPA__G(struct dpa__u_a_bo_any,       (X)).p), \
    struct dpa__u_a_bo_gc        : dpa__u_bo_put_h (DPA__G(struct dpa__u_a_bo_gc,        (X)).p), \
    struct dpa__u_a_bo_hashed    : dpa__u_bo_put_h (DPA__G(struct dpa__u_a_bo_hashed,    (X)).p), \
    struct dpa__u_a_bo_refcounted: dpa__u_bo_put_h2(DPA__G(struct dpa__u_a_bo_refcounted,(X)).p) \
  )

#define dpa_u_bo_get_refcount(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : dpa__u_bo_get_refcount_h1(DPA__G(struct dpa__u_a_bo_unique,     (X))), \
    struct dpa__u_a_bo_any       : dpa__u_bo_get_refcount_h (DPA__G(struct dpa__u_a_bo_any,        (X)).p), \
    struct dpa__u_a_bo_gc        : dpa__u_bo_get_refcount_h (DPA__G(struct dpa__u_a_bo_gc,         (X)).p), \
    struct dpa__u_a_bo_hashed    : dpa__u_bo_get_refcount_h (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p), \
    struct dpa__u_a_bo_refcounted: dpa__u_bo_get_refcount_h2(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p) \
  )

dpa__u_api inline void dpa__u_bo_free_h(const dpa__u_boptr_t bo){
  if( dpa_u_bo_is_any_type(bo, DPA_U_BO_UNIQUE)
   ||!dpa_u_bo_is_every_type(bo, DPA_U_BO_SIMPLE)
  ) return;
  void* pbo = DPA__U_BO_UNTAG(dpa_u_bo_t*, bo);
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED))
    pbo = dpa_u_container_of(pbo, dpa__u_bo_refcounted_t, bo);
  free(pbo);
}

dpa__u_api inline void dpa__u_bo_free_h2(const dpa__u_boptr_t bo){
  if(!dpa_u_bo_is_every_type(bo, DPA_U_BO_SIMPLE))
    return;
  dpa__u_bo_refcounted_t* pbo = dpa_u_container_of(DPA__U_BO_UNTAG(dpa_u_bo_t*, bo), dpa__u_bo_refcounted_t, bo);
  free(pbo);
}

#define dpa_u_bo_free(X) _Generic((X), \
    struct dpa_u_bo*: free(DPA__G(struct dpa_u_bo*, (X))) \
    const struct dpa_u_bo*: free((void*)DPA__G(const struct dpa_u_bo*, (X))) \
    \
    struct dpa__u_a_bo_unique    : (void)0, \
    struct dpa__u_a_bo_any       : dpa__u_bo_free_h (DPA__G(struct dpa__u_a_bo_any,        (X)).p), \
    struct dpa__u_a_bo_gc        : dpa__u_bo_free_h (DPA__G(struct dpa__u_a_bo_gc,         (X)).p), \
    struct dpa__u_a_bo_hashed    : dpa__u_bo_free_h (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p), \
    struct dpa__u_a_bo_refcounted: dpa__u_bo_free_h2(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p) \
  )

dpa__u_api dpa_u_unsequenced inline dpa__u_boptr_t dpa__u_bo_needs_copy_h(const dpa__u_boptr_t bo){
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_UNIQUE))
    return bo;
  return (dpa__u_boptr_t){bo.value[0] & ~DPA_U_MOVE_TAG(DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)};
}

#define dpa_u_bo_needs_copy(X) _Generic((X), \
    struct dpa_u_bo: (dpa_u_a_bo_any_t){DPA__U_BO_TAG(DPA__G(struct dpa_u_bo, (X))._c, DPA_U_BO_SIMPLE)}, \
    struct dpa_u_bo*: (dpa_u_a_bo_any_t){DPA__U_BO_TAG(DPA__G(struct dpa_u_bo*, (X)), DPA_U_BO_SIMPLE)}, \
    const struct dpa_u_bo*: (dpa_u_a_bo_any_t){DPA__U_BO_TAG(DPA__G(const struct dpa_u_bo*, (X)), DPA_U_BO_SIMPLE)}, \
    \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_any_t){dpa__u_bo_needs_copy_h(DPA__G(struct dpa__u_a_bo_any,        (X)).p)}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_any_t){dpa__u_bo_needs_copy_h(DPA__G(struct dpa__u_a_bo_gc,         (X)).p)}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_any_t){dpa__u_bo_needs_copy_h(DPA__G(struct dpa__u_a_bo_hashed,     (X)).p)}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_any_t){dpa__u_bo_needs_copy_h(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p)} \
  )

dpa__u_api inline dpa_u_a_bo_unique_t dpa__u_bo_copy_maybe_h1(const dpa_u_a_bo_unique_t bo){
  dpa__u_bo_ref_h1(bo);
  return bo;
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo_copy_bo_maybe_h(const dpa__u_boptr_t bo){
  const unsigned type = dpa_u_bo_get_type(bo);
  if(!(type & DPA_U_BO_SIMPLE))
    return bo;
  const char*restrict src = (const char*)DPA__U_BO_UNTAG(dpa_u_bo_t*, bo);
  if(type & DPA_U_BO_UNIQUE){
    dpa_u_refcount_ref(((dpa_u_refcount_freeable_t*)src)-1);
    return bo;
  }
  unsigned size = sizeof(dpa_u_bo_t);
  if(type & DPA_U_BO_REFCOUNTED){
    src = (const char*)dpa_u_container_of((dpa_u_bo_t*)src, dpa__u_bo_refcounted_t, bo);
    size = sizeof(dpa__u_bo_refcounted_t);
  }
  if(type & DPA_U_BO_HASHED)
    size += sizeof(uint64_t);
  void*restrict dest = dpa_u_copy_p(src, size);
  if(type & DPA_U_BO_REFCOUNTED)
    dest = &((dpa__u_bo_refcounted_t*)dest)->bo;
  return DPA__U_BO_TAG(dest, type);
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo_copy_bo_maybe_h2(const dpa__u_boptr_t bo){
  const unsigned type = dpa_u_bo_get_type(bo);
  if(!(type & DPA_U_BO_SIMPLE))
    return bo;
  const dpa__u_bo_refcounted_t*restrict src = dpa_u_container_of(DPA__U_BO_UNTAG(dpa_u_bo_t*, bo), dpa__u_bo_refcounted_t, bo);
  dpa__u_bo_refcounted_t*restrict dest = dpa_u_copy_p(src, type & DPA_U_BO_HASHED ? sizeof(dpa__u_bo_refcounted_hashed_t) : sizeof(dpa__u_bo_refcounted_t));
  return DPA__U_BO_TAG(&dest->bo, type);
}

#define dpa_u_bo_copy_bo_maybe(X) _Generic((X), \
    struct dpa_u_bo*: dpa_u_copy_p(DPA__G(struct dpa_u_bo*, (X)), sizeof(struct dpa_u_bo)), \
    const struct dpa_u_bo*: dpa_u_copy_p(DPA__G(const struct dpa_u_bo*, (X)), sizeof(struct dpa_u_bo)), \
    \
    struct dpa__u_a_bo_unique    : dpa__u_bo_copy_maybe_h1(DPA__G(struct dpa__u_a_bo_unique, (X))), \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_any_t){dpa__u_bo_copy_bo_maybe_h (DPA__G(struct dpa__u_a_bo_any,        (X)).p)}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_any_t){dpa__u_bo_copy_bo_maybe_h (DPA__G(struct dpa__u_a_bo_gc,         (X)).p)}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_any_t){dpa__u_bo_copy_bo_maybe_h (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p)}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_any_t){dpa__u_bo_copy_bo_maybe_h2(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p)} \
  )

dpa__u_api inline dpa__u_boptr_t dpa__u_bo_copy_maybe_h(const dpa__u_boptr_t bo){
  const unsigned type = dpa_u_bo_get_type(bo);
  if(!(type & DPA_U_BO_SIMPLE))
    return bo;
  const char*restrict src = (const char*)DPA__U_BO_UNTAG(dpa_u_bo_t*, bo);
  if(type & DPA_U_BO_UNIQUE){
    dpa_u_refcount_ref(((dpa_u_refcount_freeable_t*)src)-1);
    return bo;
  }
  unsigned size = sizeof(dpa_u_bo_t);
  if(type & DPA_U_BO_REFCOUNTED){
    src = (const char*)dpa_u_container_of((dpa_u_bo_t*)src, dpa__u_bo_refcounted_t, bo);
    size = sizeof(dpa__u_bo_refcounted_t);
  }
  if(type & DPA_U_BO_HASHED)
    size += sizeof(uint64_t);
  void*restrict dest = dpa_u_copy_p(src, size);
  if(type & DPA_U_BO_REFCOUNTED)
    dest = &((dpa__u_bo_refcounted_t*)dest)->bo;
  dpa_u_bo_t*const ret = (dpa_u_bo_t*)dest;
  if(!(type & (DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)))
    ret->data = dpa_u_copy_p(ret->data, ret->size);
  return DPA__U_BO_TAG(ret, type);
}

dpa__u_api inline dpa_u_bo_t* dpa__u_bo_copy_maybe_h2(const dpa_u_bo_t bo){
  dpa_u_bo_t*restrict copy = malloc(sizeof(bo));
  copy->data = dpa_u_copy_p(bo.data, bo.size);
  copy->size = bo.size;
  return copy;
}

dpa__u_api inline dpa__u_boptr_t dpa__u_bo_copy_bo_maybe_h3(const dpa__u_boptr_t bo){
  const unsigned type = dpa_u_bo_get_type(bo);
  if(!(type & DPA_U_BO_SIMPLE))
    return bo;
  const dpa__u_bo_refcounted_t*restrict src = dpa_u_container_of(DPA__U_BO_UNTAG(dpa_u_bo_t*, bo), dpa__u_bo_refcounted_t, bo);
  dpa__u_bo_refcounted_t*restrict dest = dpa_u_copy_p(src, type & DPA_U_BO_HASHED ? sizeof(dpa__u_bo_refcounted_hashed_t) : sizeof(dpa__u_bo_refcounted_t));
  dest->bo.data = dpa_u_copy_p(dest->bo.data, dest->bo.size);
  return DPA__U_BO_TAG(&dest->bo, type);
}

#define dpa_u_bo_copy_maybe(X) _Generic((X), \
    struct dpa_u_bo*: dpa__u_bo_copy_maybe_h2(*DPA__G(struct dpa_u_bo*, (X))), \
    const struct dpa_u_bo*: dpa__u_bo_copy_maybe_h2(*DPA__G(const struct dpa_u_bo*, (X))), \
    \
    struct dpa__u_a_bo_unique    : dpa__u_bo_copy_maybe_h1(DPA__G(struct dpa__u_a_bo_unique, (X))), \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_any_t){dpa__u_bo_copy_maybe_h(DPA__G(struct dpa__u_a_bo_any,        (X)).p)}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_any_t){dpa__u_bo_copy_maybe_h(DPA__G(struct dpa__u_a_bo_gc,         (X)).p)}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_any_t){dpa__u_bo_copy_maybe_h(DPA__G(struct dpa__u_a_bo_hashed,     (X)).p)}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_any_t){dpa__u_bo_copy_bo_maybe_h3(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p)} \
  )


#ifdef DPA_U_BO_NO_HACKS
// TODO
#else
#include <dpa/utils/_bo/bo-conv-1.h>
#endif

#define dpa_u_make_a_bo_any(X) _Generic((X), \
    struct dpa_u_bo: (dpa_u_a_bo_any_t){DPA__U_BO_TAG(&dpa_u_rescope(struct dpa_u_bo, DPA__G(struct dpa_u_bo, (X))), DPA_U_BO_SIMPLE)}, \
    \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_any       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, &(union dpa__u_bo_cmem){0})}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_gc        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, &(union dpa__u_bo_cmem){0})}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_hashed    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, &(union dpa__u_bo_cmem){0})}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_refcounted(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})} \
  )

#define dpa_u_make_a_bo_any_do_hash(X) _Generic((X), \
    struct dpa_u_bo: (dpa_u_a_bo_any_t){DPA__U_BO_TAG(&dpa_u_rescope(struct dpa__u_bo_hashed, dpa__u_bo__alloc_p_any_bo_do_hash(DPA__G(struct dpa_u_bo, (X)))), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED)}, \
    \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_any_do_hash       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, &(union dpa__u_bo_cmem){0})}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_gc_do_hash        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, &(union dpa__u_bo_cmem){0})}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_hashed_do_hash    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, &(union dpa__u_bo_cmem){0})}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_refcounted_do_hash(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})} \
  )

#define dpa_u_make_a_bo_gc(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_gc_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_any       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_gc        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_hashed    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_refcounted(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})} \
  )

#define dpa_u_make_a_bo_gc_do_hash(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_gc_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_any_do_hash       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_gc_do_hash        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_hashed_do_hash    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_refcounted_do_hash(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})} \
  )

#define dpa_u_make_a_bo_refcounted(X) _Generic((X), \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_any       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_gc        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_hashed    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_refcounted(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})} \
  )

#define dpa_u_make_a_bo_refcounted_do_hash(X) _Generic((X), \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_any_do_hash       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_gc_do_hash        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_hashed_do_hash    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_refcounted_do_hash(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})} \
  )

#define dpa_u_make_a_bo_hashed_do_hash(X) _Generic((X), \
    struct dpa_u_bo: (dpa_u_a_bo_hashed_t){DPA__U_BO_TAG(&dpa_u_rescope(struct dpa__u_bo_hashed, dpa__u_bo__alloc_p_any_bo_do_hash(DPA__G(struct dpa_u_bo, (X)))), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED)}, \
    \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_any_do_hash       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, &(union dpa__u_bo_cmem){0})}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_gc_do_hash        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, &(union dpa__u_bo_cmem){0})}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_hashed_do_hash    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, &(union dpa__u_bo_cmem){0})}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_refcounted_do_hash(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, &(dpa__u_bo_refcounted_hashed_t){0})} \
  )
#define dpa_u_make_a_bo_hashed dpa_u_make_a_bo_hashed_do_hash

#define dpa_u_make_a_bo_unique(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_unique_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_unique_t){dpa__u_bo__alloc_p_unique_any(DPA__G(struct dpa__u_a_bo_any, (X)).p)}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_unique_t){dpa__u_bo__alloc_p_unique_gc (DPA__G(struct dpa__u_a_bo_gc,  (X)).p)} \
  )

#define dpa_u_make_a_bo_unique_do_hash(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_unique_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_unique_t){dpa__u_bo__alloc_p_unique_any_do_hash(DPA__G(struct dpa__u_a_bo_any, (X)).p)}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_unique_t){dpa__u_bo__alloc_p_unique_gc_do_hash (DPA__G(struct dpa__u_a_bo_gc,  (X)).p)} \
  )


#define dpa_u_make_a_bo_any_static(X) \
  ((dpa_u_a_bo_any_t){DPA__U_BO_TAG(&dpa_u_rescope(dpa_u_bo_t, (X)), DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)})

#define dpa_u_make_a_bo_any_static_do_hash(X) \
  ((dpa_u_a_bo_any_t){DPA__U_BO_TAG(&dpa_u_rescope(struct dpa__u_bo_hashed, dpa__u_bo__alloc_p_any_bo_do_hash((X))), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_make_a_bo_gc_static(X) \
  ((dpa_u_a_bo_gc_t){DPA__U_BO_TAG(&dpa_u_rescope(dpa_u_bo_t, (X)), DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)})

#define dpa_u_make_a_bo_gc_static_do_hash(X) \
  ((dpa_u_a_bo_gc_t){DPA__U_BO_TAG(&dpa_u_rescope(struct dpa__u_bo_hashed, dpa__u_bo__alloc_p_any_bo_do_hash((X))), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_make_a_bo_hashed_static_do_hash(X) \
  ((dpa_u_a_bo_hashed_t){DPA__U_BO_TAG(&dpa_u_rescope(struct dpa__u_bo_hashed, dpa__u_bo__alloc_p_any_bo_do_hash((X))), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_make_a_bo_any_static_with_hash(X, H) \
  ((dpa_u_a_bo_any_t){DPA__U_BO_TAG((&(dpa__u_bo_hashed_t){.bo=(X), .hash=(H)}), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_make_a_bo_hashed_static_with_hash(X, H) \
  ((dpa_u_a_bo_hashed_t){DPA__U_BO_TAG((&(dpa__u_bo_hashed_t){.bo=(X), .hash=(H)}), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_make_a_bo_refcounted_static(X) \
  ((dpa_u_a_bo_refcounted_t){DPA__U_BO_TAG((&(dpa__u_bo_refcounted_t){ .refcount=&dpa_u_refcount_static_v_freeable, .bo=(X) }.bo), DPA_U_BO_SIMPLE|DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)})

#define dpa_u_make_a_bo_refcounted_static_do_hash(X) \
  ((dpa_u_a_bo_refcounted_t){DPA__U_BO_TAG(&dpa_u_rescope(struct dpa__u_bo_refcounted_hashed, dpa__u_bo__alloc_p_refcounted_static_bo_do_hash((X))).rbo.bo, DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)})

#define dpa_u_make_a_bo_refcounted_static_with_hash(X, H) \
  ((dpa_u_a_bo_refcounted_t){DPA__U_BO_TAG((&(dpa__u_bo_refcounted_hashed_t){ .rbo={ .refcount=&dpa_u_refcount_static_v_freeable, .bo=(X) }, .hash=(H)}.rbo.bo), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)})

#define dpa_u_make_a_bo_any_with_hash(X, H) \
  ((dpa_u_a_bo_any_t){DPA__U_BO_TAG((&(dpa__u_bo_hashed_t){.bo=(X), .hash=(H)}), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED)})

#define dpa_u_make_a_bo_hashed_with_hash(X, H) \
  ((dpa_u_a_bo_hashed_t){DPA__U_BO_TAG((&(dpa__u_bo_hashed_t){.bo=(X), .hash=(H)}), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED)})

#define dpa_u_make_a_bo_gc_static_with_hash(X, H) \
  ((dpa_u_a_bo_gc_t){DPA__U_BO_TAG((&(dpa__u_bo_hashed_t){.bo=(X), .hash=(H)}.bo), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_make_a_bo_any_with_refcount_do_hash(X, R) \
  ((dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_bo_with_refcount_do_hash((X), (R), &(dpa__u_bo_refcounted_hashed_t){0})})

#define dpa_u_make_a_bo_any_with_refcount_hash(X, R, H) \
  ((dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_bo_with_refcount_hash((X), (R), (H), &(dpa__u_bo_refcounted_hashed_t){0})})

#define dpa_u_make_a_bo_gc_with_refcount_do_hash(X, R) \
  ((dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_bo_with_refcount_do_hash((X), (R), &(dpa__u_bo_refcounted_hashed_t){0})})

#define dpa_u_make_a_bo_gc_with_refcount_hash(X, R, H) \
  ((dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_bo_with_refcount_hash((X), (R), (H), &(dpa__u_bo_refcounted_hashed_t){0})})

#define dpa_u_make_a_bo_refcounted_with_refcount_do_hash(X, R) \
  ((dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_bo_with_refcount_do_hash((X), (R), &(dpa__u_bo_refcounted_hashed_t){0})})

#define dpa_u_make_a_bo_refcounted_with_refcount_hash(X, R, H) \
  ((dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_bo_with_refcount_hash((X), (R), (H), &(dpa__u_bo_refcounted_hashed_t){0})})

#define dpa_u_make_a_bo_hashed_with_refcount_do_hash(X, R) \
  ((dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_bo_with_refcount_do_hash((X), (R), &(dpa__u_bo_refcounted_hashed_t){0})})

#define dpa_u_make_a_bo_hashed_with_refcount_hash(X, R, H) \
  ((dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_bo_with_refcount_hash((X), (R), (H), &(dpa__u_bo_refcounted_hashed_t){0})})

#define dpa_u_make_a_bo_any_with_refcount(X, R) \
  ((dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_bo_with_refcount((X), (R), &(dpa__u_bo_refcounted_t){0})})

#define dpa_u_make_a_bo_gc_with_refcount(X, R) \
  ((dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_bo_with_refcount((X), (R), &(dpa__u_bo_refcounted_t){0})})

#define dpa_u_make_a_bo_refcounted_with_refcount(X, R) \
  ((dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_bo_with_refcount((X), (R), &(dpa__u_bo_refcounted_t){0})})



#define dpa_u_alloc_a_bo_any(X) _Generic((X), \
    struct dpa_u_bo: (dpa_u_a_bo_any_t){DPA__U_BO_TAG(&dpa_u_rescope(struct dpa_u_bo, DPA__G(struct dpa_u_bo, (X))), DPA_U_BO_SIMPLE)}, \
    \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_any       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, (union dpa__u_bo_cmem*)calloc(1, sizeof(union dpa__u_bo_cmem)))}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_gc        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, (union dpa__u_bo_cmem*)calloc(1, sizeof(union dpa__u_bo_cmem)))}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_hashed    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, (union dpa__u_bo_cmem*)calloc(1, sizeof(union dpa__u_bo_cmem)))}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_refcounted(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))} \
  )

#define dpa_u_alloc_a_bo_any_do_hash(X) _Generic((X), \
    struct dpa_u_bo: (dpa_u_a_bo_any_t){DPA__U_BO_TAG(dpa_u_copy_p(dpa__u_bo__alloc_p_any_bo_do_hash(DPA__G(struct dpa_u_bo, (X))).bo._c, sizeof(dpa__u_bo_hashed_t)), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED)}, \
    \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_any_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_any_do_hash       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, (union dpa__u_bo_cmem*)calloc(1, sizeof(union dpa__u_bo_cmem)))}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_gc_do_hash        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, (union dpa__u_bo_cmem*)calloc(1, sizeof(union dpa__u_bo_cmem)))}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_hashed_do_hash    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, (union dpa__u_bo_cmem*)calloc(1, sizeof(union dpa__u_bo_cmem)))}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_refcounted_do_hash(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))} \
  )

#define dpa_u_alloc_a_bo_gc(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_gc_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_any       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_gc        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_hashed    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_refcounted(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))} \
  )

#define dpa_u_alloc_a_bo_gc_do_hash(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_gc_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_any_do_hash       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_gc_do_hash        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_hashed_do_hash    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_refcounted_do_hash(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))} \
  )

#define dpa_u_alloc_a_bo_refcounted(X) _Generic((X), \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_any       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_gc        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_hashed    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_refcounted(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))} \
  )

#define dpa_u_alloc_a_bo_refcounted_do_hash(X) _Generic((X), \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_any_do_hash       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_gc_do_hash        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_hashed_do_hash    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_refcounted_do_hash(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))} \
  )

#define dpa_u_alloc_a_bo_hashed_do_hash(X) _Generic((X), \
    struct dpa_u_bo: (dpa_u_a_bo_hashed_t){DPA__U_BO_TAG(dpa_u_copy_p(dpa__u_bo__alloc_p_any_bo_do_hash(DPA__G(struct dpa_u_bo, (X))).bo._c, sizeof(dpa__u_bo_hashed_t)), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED)}, \
    \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_any_do_hash       (DPA__G(struct dpa__u_a_bo_any,        (X)).p, (union dpa__u_bo_cmem*)calloc(1, sizeof(union dpa__u_bo_cmem)))}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_gc_do_hash        (DPA__G(struct dpa__u_a_bo_gc,         (X)).p, (union dpa__u_bo_cmem*)calloc(1, sizeof(union dpa__u_bo_cmem)))}, \
    struct dpa__u_a_bo_hashed    : (dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_hashed_do_hash    (DPA__G(struct dpa__u_a_bo_hashed,     (X)).p, (union dpa__u_bo_cmem*)calloc(1, sizeof(union dpa__u_bo_cmem)))}, \
    struct dpa__u_a_bo_refcounted: (dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_refcounted_do_hash(DPA__G(struct dpa__u_a_bo_refcounted, (X)).p, (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))} \
  )

#define dpa_u_alloc_a_bo_hashed dpa_u_alloc_a_bo_hashed_do_hash

#define dpa_u_alloc_a_bo_unique(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_unique_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_unique_t){dpa__u_bo__alloc_p_unique_any(DPA__G(struct dpa__u_a_bo_any, (X)).p)}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_unique_t){dpa__u_bo__alloc_p_unique_gc (DPA__G(struct dpa__u_a_bo_gc,  (X)).p)} \
  )

#define dpa_u_alloc_a_bo_unique_do_hash(X) _Generic((X), \
    struct dpa__u_a_bo_unique    : (dpa_u_a_bo_unique_t){DPA__G(struct dpa__u_a_bo_unique, (X)).p}, \
    struct dpa__u_a_bo_any       : (dpa_u_a_bo_unique_t){dpa__u_bo__alloc_p_unique_any_do_hash(DPA__G(struct dpa__u_a_bo_any, (X)).p)}, \
    struct dpa__u_a_bo_gc        : (dpa_u_a_bo_unique_t){dpa__u_bo__alloc_p_unique_gc_do_hash (DPA__G(struct dpa__u_a_bo_gc,  (X)).p)} \
  )



#define dpa_u_alloc_a_bo_any_static(X) \
  ((dpa_u_a_bo_any_t){DPA__U_BO_TAG(dpa_u_copy_p((X)._c, sizeof(dpa_u_bo_t)), DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)})

#define dpa_u_alloc_a_bo_any_static_do_hash(X) \
  ((dpa_u_a_bo_any_t){DPA__U_BO_TAG(dpa_u_copy_p(dpa__u_bo__alloc_p_any_bo_do_hash((X)).bo._c, sizeof(struct dpa__u_bo_hashed)), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_alloc_a_bo_gc_static(X) \
  ((dpa_u_a_bo_gc_t){DPA__U_BO_TAG(dpa_u_copy_p((X)._c, sizeof(dpa_u_bo_t)), DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)})

#define dpa_u_alloc_a_bo_gc_static_do_hash(X) \
  ((dpa_u_a_bo_gc_t){DPA__U_BO_TAG(dpa_u_copy_p(dpa__u_bo__alloc_p_any_bo_do_hash((X)).bo._c, sizeof(struct dpa__u_bo_hashed)), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_alloc_a_bo_hashed_static_do_hash(X) \
  ((dpa_u_a_bo_hashed_t){DPA__U_BO_TAG(dpa_u_copy_p(dpa__u_bo__alloc_p_any_bo_do_hash((X)).bo._c, sizeof(struct dpa__u_bo_hashed)), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_alloc_a_bo_any_static_with_hash(X, H) \
  ((dpa_u_a_bo_any_t){DPA__U_BO_TAG(dpa_u_copy_p(&(dpa__u_bo_hashed_t){.bo=(X), .hash=(H)}, sizeof(dpa__u_bo_hashed_t)), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_alloc_a_bo_hashed_static_with_hash(X, H) \
  ((dpa_u_a_bo_hashed_t){DPA__U_BO_TAG(dpa_u_copy_p(&(dpa__u_bo_hashed_t){.bo=(X), .hash=(H)}, sizeof(dpa__u_bo_hashed_t)), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_alloc_a_bo_refcounted_static(X) \
  ((dpa_u_a_bo_refcounted_t){DPA__U_BO_TAG(&((dpa__u_bo_refcounted_t*)dpa_u_copy_p(&(dpa__u_bo_refcounted_t){ .refcount=&dpa_u_refcount_static_v_freeable, .bo=(X) }, sizeof(dpa__u_bo_refcounted_t)))->bo, DPA_U_BO_SIMPLE|DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)})

#define dpa_u_alloc_a_bo_refcounted_static_do_hash(X) \
  ((dpa_u_a_bo_refcounted_t){DPA__U_BO_TAG(&((struct dpa__u_bo_refcounted_hashed*)dpa_u_copy_p(dpa__u_bo__alloc_p_refcounted_static_bo_do_hash((X)).rbo.bo._c-offsetof(dpa__u_bo_refcounted_hashed_t, rbo.bo._c), sizeof(struct dpa__u_bo_refcounted_hashed)))->rbo.bo, DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)})

#define dpa_u_alloc_a_bo_refcounted_static_with_hash(X, H) \
  ((dpa_u_a_bo_refcounted_t){DPA__U_BO_TAG(&((dpa__u_bo_refcounted_hashed_t*)dpa_u_copy_p(&(dpa__u_bo_refcounted_hashed_t){ .rbo={ .refcount=&dpa_u_refcount_static_v_freeable, .bo=(X) }, .hash=(H)}, sizeof(dpa__u_bo_refcounted_hashed_t)))->rbo.bo, DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)})

#define dpa_u_alloc_a_bo_any_with_hash(X, H) \
  ((dpa_u_a_bo_any_t){DPA__U_BO_TAG(dpa_u_copy_p(&(dpa__u_bo_hashed_t){.bo=(X), .hash=(H)}, sizeof(dpa__u_bo_hashed_t)), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED)})

#define dpa_u_alloc_a_bo_hashed_with_hash(X, H) \
  ((dpa_u_a_bo_hashed_t){DPA__U_BO_TAG(dpa_u_copy_p(&(dpa__u_bo_hashed_t){.bo=(X), .hash=(H)}, sizeof(dpa__u_bo_hashed_t)), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED)})

#define dpa_u_alloc_a_bo_gc_static_with_hash(X, H) \
  ((dpa_u_a_bo_gc_t){DPA__U_BO_TAG(dpa_u_copy_p(&(dpa__u_bo_hashed_t){.bo=(X), .hash=(H)}, sizeof(dpa__u_bo_hashed_t)), DPA_U_BO_SIMPLE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)})

#define dpa_u_alloc_a_bo_any_with_refcount_do_hash(X, R) \
  ((dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_bo_with_refcount_do_hash((X), (R), (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))})

#define dpa_u_alloc_a_bo_any_with_refcount_hash(X, R, H) \
  ((dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_bo_with_refcount_hash((X), (R), (H), (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))})

#define dpa_u_alloc_a_bo_gc_with_refcount_do_hash(X, R) \
  ((dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_bo_with_refcount_do_hash((X), (R), (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))})

#define dpa_u_alloc_a_bo_gc_with_refcount_hash(X, R, H) \
  ((dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_bo_with_refcount_hash((X), (R), (H), (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))})

#define dpa_u_alloc_a_bo_refcounted_with_refcount_do_hash(X, R) \
  ((dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_bo_with_refcount_do_hash((X), (R), (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))})

#define dpa_u_alloc_a_bo_refcounted_with_refcount_hash(X, R, H) \
  ((dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_bo_with_refcount_hash((X), (R), (H), (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))})

#define dpa_u_alloc_a_bo_hashed_with_refcount_do_hash(X, R) \
  ((dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_bo_with_refcount_do_hash((X), (R), (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))})

#define dpa_u_alloc_a_bo_hashed_with_refcount_hash(X, R, H) \
  ((dpa_u_a_bo_hashed_t){dpa__u_bo__alloc_p_hashed_bo_with_refcount_hash((X), (R), (H), (dpa__u_bo_refcounted_hashed_t*)calloc(1, sizeof(dpa__u_bo_refcounted_hashed_t)))})

#define dpa_u_alloc_a_bo_any_with_refcount(X, R) \
  ((dpa_u_a_bo_any_t){dpa__u_bo__alloc_p_any_bo_with_refcount((X), (R), (dpa__u_bo_refcounted_t*)calloc(1, sizeof(dpa__u_bo_refcounted_t)))})

#define dpa_u_alloc_a_bo_gc_with_refcount(X, R) \
  ((dpa_u_a_bo_gc_t){dpa__u_bo__alloc_p_gc_bo_with_refcount((X), (R), (dpa__u_bo_refcounted_t*)calloc(1, sizeof(dpa__u_bo_refcounted_t)))})

#define dpa_u_alloc_a_bo_refcounted_with_refcount(X, R) \
  ((dpa_u_a_bo_refcounted_t){dpa__u_bo__alloc_p_refcounted_bo_with_refcount((X), (R), (dpa__u_bo_refcounted_t*)calloc(1, sizeof(dpa__u_bo_refcounted_t)))})


#endif
