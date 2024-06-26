////
// In MSVC, dllexport functions need to be declared as such from the beginning
#include <dpa/utils/common.h>
#include <dpa/utils/_bo/typedefs.h>
struct dpa_u_refcount_freeable;
dpa_u_export void dpa__u_bo_unique_hashmap_destroy(const struct dpa_u_refcount_freeable* ref);
dpa_u_export dpa_u_bo_unique_hashmap_t dpa__u_bo_do_intern(dpa_u_any_bo_ro_t*const bo);
////

#include <dpa/utils/bo.h>
#include <dpa/utils/math.h>
#include <dpa/utils/hash.h>
#include <dpa/utils/refcount.h>

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#ifndef DPA_U_NO_THREADS
#include <stdatomic.h>
// c11 has <threads.h>, some platforms have atomics and pthreads, but not c11 threads. In that case, this'll polyfill it.
#include <dpa/utils/threads.h>
#endif

#undef dpa_u_refcount_is_zero_s
#define dpa_u_refcount_is_zero_s dpa_u_refcount_is_zero_p

#ifndef DPA_U_NO_THREADS
#define m_aload(X) atomic_load(&(X))
#define m_astore(X,V) atomic_store(&(X), (V))
#define m_atomic _Atomic
#else
#define m_aload(X) (X)
#define m_astore(X,V) (X) = (V)
#define m_atomic
#endif

// Note: After the expansion, the load factore gets smaller, and vice versa. The amount
// of buckets gets doubled/halved. Be careful never to set DPA_U_LOAD_FACTOR_EXPAND and
// DPA_U_LOAD_FACTOR_SHRINK such that after expension / shrinking, it's above / below
// the other factor, or it'll grow and shrink every time!
// 1 and 0.25 is a bit faster, but wastes a bit more space than 2 0.5.
#ifndef DPA_U_LOAD_FACTOR_EXPAND
#define DPA_U_LOAD_FACTOR_EXPAND 2
#endif
#ifndef DPA_U_LOAD_FACTOR_SHRINK
#define DPA_U_LOAD_FACTOR_SHRINK 0.5
#endif

struct bucket {
  dpa__u_bo_unique_hashmap_entry_t* next;
};

// The first 2 bucket lists will have 2**DPA_U_BUCKET_BASE entries (usually 256).
// Each bucket will have twice the size of the previous one.
#ifndef DPA_U_BUCKET_BASE
#define DPA_U_BUCKET_BASE 9
#endif
static_assert(DPA_U_BUCKET_BASE <= sizeof(dpa_u_hash_t) * CHAR_BIT, "Bucket base can't be larger than the number of bits in dpa_u_hash_t");

#ifndef DPA_U_SINGLE_BUCKET
// Note: It would take many years to insert enough entries to warant more than 2^48 buckets.
// Also, we need to have one bucket list too few, or BUCKET_COUNT will be too large to store in a dpa_u_hash_t / size_t
#define BUCKET_LIST_COUNT (int)((sizeof(dpa_u_hash_t) > 6 ? 6 : sizeof(dpa_u_hash_t)) * CHAR_BIT - DPA_U_BUCKET_BASE - 1)
#define BUCKET_COUNT (((dpa_u_hash_t)1)<<(BUCKET_LIST_COUNT+DPA_U_BUCKET_BASE))
#else
#define BUCKET_LIST_COUNT 1
#define BUCKET_COUNT (1<<DPA_U_BUCKET_BASE)
#endif

#ifndef DPA_U_NO_THREADS
// Locks are really big. Like, 40 bytes big on my PC!
#define DPA_U_LOCK_BIT_COUNT 7
#endif
#define LOCK_COUNT (1llu<<DPA_U_LOCK_BIT_COUNT)

static_assert(BUCKET_LIST_COUNT > 0, "dpa_u_hash_t was smaller than expected");

#ifndef DPA_U_NO_THREADS
static_assert(LOCK_COUNT <= (((size_t)1)<<DPA_U_BUCKET_BASE), "There can't be more locks than buckets in the first bucket list");
static_assert(!(LOCK_COUNT & (LOCK_COUNT-1)), "LOCK_COUNT must be a power of 2");
static mtx_t lock_table[LOCK_COUNT];
static mtx_t resize_lock;
#endif

struct hash_map {
  m_atomic size_t count;
#ifndef DPA_U_SINGLE_BUCKET
  struct bucket*m_atomic bucket[BUCKET_LIST_COUNT];
#else
  struct bucket* bucket[BUCKET_LIST_COUNT];
#endif
#ifndef DPA_U_SINGLE_BUCKET
  m_atomic int shift_size;
#ifndef DPA_U_NO_THREADS
  m_atomic size_t move_pending;
#endif
#endif
};
static struct hash_map hash_map = {
  .count = 0,
  .bucket[0] = (struct bucket[((size_t)1)<<DPA_U_BUCKET_BASE]){0}, // the first bucket list is pre-allocated & static
#ifndef DPA_U_SINGLE_BUCKET
  .shift_size = DPA_U_BUCKET_BASE,
#ifndef DPA_U_NO_THREADS
  .move_pending = ((size_t)1)<<DPA_U_BUCKET_BASE,
#endif
#endif
};

#ifndef DPA_U_NO_THREADS
dpa_u_init static inline void init(void){
  for(size_t i=0; i<LOCK_COUNT; i++)
    mtx_init(&lock_table[i], mtx_plain);
#ifndef DPA_U_SINGLE_BUCKET
  mtx_init(&resize_lock, mtx_plain);
#endif
}
#endif

struct bucket_index {
  int bi;
  size_t i;
};

static inline struct bucket_index get_bucket_index(size_t hash){
#ifndef DPA_U_SINGLE_BUCKET
  const size_t shift_size = m_aload(hash_map.shift_size);
  const size_t size_mask = (((size_t)1)<<shift_size)-1;
  hash = hash & size_mask;
#ifndef DPA_U_NO_THREADS
  if(hash >= m_aload(hash_map.move_pending))
    hash &= size_mask>>1;
#endif
  int i = dpa_u_log2(hash|1);
  if(hash < (((size_t)1)<<DPA_U_BUCKET_BASE))
    return (struct bucket_index){0, hash};
  return (struct bucket_index){
    i - (DPA_U_BUCKET_BASE-1),
    hash & ((((size_t)1)<<i)-1),
  };
#else
  return (struct bucket_index){
    .i = hash & (BUCKET_COUNT-1)
  };
#endif
}

static inline struct bucket* get_bucket(dpa_u_hash_t hash){
#ifndef DPA_U_SINGLE_BUCKET
  struct bucket_index x = get_bucket_index(hash);
  return &m_aload(hash_map.bucket[x.bi])[x.i];
#else
  return &hash_map.bucket[0][hash & (BUCKET_COUNT-1)];
#endif
}

static inline struct dpa_u_refcount_freeable* entry_get_ext_refcount(const dpa__u_bo_unique_hashmap_entry_t*const e){
  if(e->bo_hashed.bo_simple.extra)
    return ((struct dpa__u_bo_entry_refcounted*)e)->refcount;
  return 0;
}

#ifndef DPA_U_NO_THREADS
dpa__u_really_inline static inline void lock_entry(dpa_u_hash_t hash){
  mtx_lock(&lock_table[hash&(LOCK_COUNT-1)]);
}
dpa__u_really_inline static inline void unlock_entry(dpa_u_hash_t hash){
  mtx_unlock(&lock_table[hash&(LOCK_COUNT-1)]);
}
#endif

#ifndef DPA_U_SINGLE_BUCKET
static void grow(void){
#ifndef DPA_U_NO_THREADS
  {
    const int result = mtx_trylock(&resize_lock);
    if(result == thrd_busy)
      return;
    assert(result == thrd_success);
  }
#endif
  const int shift_size = m_aload(hash_map.shift_size);
  if(shift_size >= BUCKET_LIST_COUNT)
    goto out;
  m_astore(hash_map.shift_size, shift_size + 1);
  // m_astore(hash_map.move_pending, ((size_t)1)<<shift_size); // Should already be set to this
  struct bucket*const new_bucket = calloc(sizeof(struct bucket), ((size_t)1)<<shift_size);
  if(!new_bucket){
    // TODO: Log an error
    goto out;
  }
  m_astore(hash_map.bucket[shift_size-(DPA_U_BUCKET_BASE-1)], new_bucket);
  size_t i = 0;
  for(int bi = 0; bi < shift_size-(DPA_U_BUCKET_BASE-1); bi++){
    struct bucket*const buckets = hash_map.bucket[bi];
    const size_t count = ((size_t)1) << (bi+DPA_U_BUCKET_BASE);
    for(size_t j=0; i < count; i++,j++){
#ifndef DPA_U_NO_THREADS
      lock_entry(i);
#endif
      for(dpa__u_bo_unique_hashmap_entry_t*restrict e, **it=&buckets[j].next; (e=*it); it=&e->next){
        if(!(e->bo_hashed.hash & ((size_t)1)<<shift_size))
          continue;
        new_bucket[i].next = e;
        *it = 0;
        break;
      }
#ifndef DPA_U_NO_THREADS
      m_astore(hash_map.move_pending, (((size_t)1)<<shift_size) + i+1);
      unlock_entry(i);
#endif
    }
  }
out:;
#ifndef DPA_U_NO_THREADS
  mtx_unlock(&resize_lock);
#endif
}

static void shrink(void){
#ifndef DPA_U_NO_THREADS
  {
    const int result = mtx_trylock(&resize_lock);
    if(result == thrd_busy)
      return;
    assert(result == thrd_success);
  }
#endif
  const int shift_size = m_aload(hash_map.shift_size) - 1;
  if(shift_size < DPA_U_BUCKET_BASE){
#ifndef DPA_U_NO_THREADS
    mtx_unlock(&resize_lock);
#endif
    return;
  }
  struct bucket*const old_bucket = hash_map.bucket[shift_size-(DPA_U_BUCKET_BASE-1)];
  const size_t old_size = ((size_t)1)<<shift_size;
  size_t i = old_size;
  for(int bi = shift_size-(DPA_U_BUCKET_BASE-1); bi--; ){
    struct bucket*const buckets = hash_map.bucket[bi];
    const size_t start = bi ? ((size_t)1) << (bi+DPA_U_BUCKET_BASE-1) : 0;
    for(size_t j=i-start; j--; ){
      i -= 1;
#ifndef DPA_U_NO_THREADS
      lock_entry(i);
      m_astore(hash_map.move_pending, i + old_size);
#endif
      dpa__u_bo_unique_hashmap_entry_t** it=&buckets[j].next;
      while(*it) it=&(*it)->next;
      *it = old_bucket[i].next;
#ifndef DPA_U_NO_THREADS
      unlock_entry(i);
#endif
    }
  }
  m_astore(hash_map.shift_size, shift_size);
  m_astore(hash_map.bucket[shift_size-(DPA_U_BUCKET_BASE-1)], 0);
#ifndef DPA_U_NO_THREADS
  mtx_unlock(&resize_lock);
#endif
  free(old_bucket);
}
#endif

void dpa__u_bo_unique_hashmap_destroy(const struct dpa_u_refcount_freeable* ref){
  const dpa__u_bo_unique_hashmap_entry_t* bo = dpa_u_container_of(ref, const dpa__u_bo_unique_hashmap_entry_t, refcount.freeable);
  const dpa_u_hash_t hash = bo->bo_hashed.hash;
#ifndef DPA_U_NO_THREADS
  lock_entry(hash);
  if(!dpa_u_refcount_is_zero(&bo->refcount)){
    // Someone else picked up the entry before we got to remove it.
    unlock_entry(hash);
    // dpa__u_bo_do_intern also incremented the refcount for dpa__u_bo_unique_hashmap_destroy, it knows we wanted to free it.
    dpa_u_refcount_put(&bo->refcount);
    return;
  }
#endif
  for(dpa__u_bo_unique_hashmap_entry_t **it=&get_bucket(hash)->next, *e; (e=*it); it=&e->next){
    if(e != bo)
      continue;
    *it = e->next;
#ifndef DPA_U_NO_THREADS
    unlock_entry(hash);
#endif
    struct dpa_u_refcount_freeable* rc = entry_get_ext_refcount(e);
    free(e);
    if(rc) dpa_u_refcount_put(rc);
#ifndef DPA_U_NO_THREADS
    const size_t count = atomic_fetch_sub(&hash_map.count, 1) - 1;
#else
    const size_t count = --hash_map.count;
#endif
#ifndef DPA_U_SINGLE_BUCKET
    const size_t total_buckets = ((size_t)1) << m_aload(hash_map.shift_size);
    if( total_buckets > (((size_t)1) << DPA_U_BUCKET_BASE) && (float)count / total_buckets <= DPA_U_LOAD_FACTOR_SHRINK )
      shrink();
#else
    (void)count;
#endif
    return;
  }
  dpa_u_abort("%s", "The dpa_u_bo_unique_hashmap_t to be destroyed could not be found");
}

dpa_u_bo_unique_hashmap_t dpa__u_bo_do_intern(dpa_u_any_bo_ro_t*const bo){
  const dpa_u_hash_t hash = dpa_u_bo_hash(bo);
  const size_t size = dpa_u_bo_get_size(bo);
  const void*const data = dpa_u_bo_data(bo);
#ifndef DPA_U_NO_THREADS
  lock_entry(hash);
#endif
  struct bucket* bucket = get_bucket(hash);
  dpa__u_bo_unique_hashmap_entry_t** it = &bucket->next;
  for(dpa__u_bo_unique_hashmap_entry_t*restrict e; (e=*it); it=&e->next){
    const dpa_u_hash_t e_hash = e->bo_hashed.hash;
    // The hash has to be the first thing the entries are soted by.
    // It is sorted bit inversed (10 < 01)
    if(e_hash != hash){
      if(dpa_u_rbit_less_than_unsigned(e_hash, hash))
        continue; else break;
    }
    const size_t e_size = e->bo_hashed.bo_simple.size;
    if(e_size > size) continue;
    if(e_size < size) break;
    const void*const e_data = e->bo_hashed.bo_simple.data;
    if(e_data != data){
      int diff = memcmp(e_data, data, size);
      if(diff < 0) continue;
      if(diff > 0) break;
    }
#ifndef DPA_U_NO_THREADS
    if(dpa_u_refcount_is_zero(&e->refcount)) // We grabbed it before dpa__u_bo_unique_hashmap_destroy managed to remove it.
      dpa_u_refcount_ref(&e->refcount);      // This reference is on behalf of dpa__u_bo_unique_hashmap_destroy, which will drop it again.
#endif
    dpa_u_refcount_ref(&e->refcount);
#ifndef DPA_U_NO_THREADS
    unlock_entry(hash);
#endif
    return e;
  }
  dpa__u_bo_unique_hashmap_entry_t* new_entry;
  if(dpa_u_bo_get_type(bo) == DPA_U_BO_UNIQUE_HASHMAP)
    return (dpa_u_bo_unique_hashmap_t)bo; // See the DPA_U_DEFINE_UNIQUE_CSTRING, it can only come from there.
  struct dpa_u_refcount_freeable* refcount = dpa_u_bo_get_refcount(bo);
  if(refcount){
    enum dpa_u_refcount_type type = dpa_u_refcount_get_type(&refcount->refcount);
    if(type == DPA_U_REFCOUNT_BO_UNIQUE_HASHMAP){
      dpa__u_bo_unique_hashmap_entry_t* old = dpa_u_container_of(refcount, dpa__u_bo_unique_hashmap_entry_t, refcount.freeable);
      struct dpa_u_refcount_freeable*const true_refcount = entry_get_ext_refcount(old);
      if(true_refcount)
        refcount = true_refcount;
    }
    dpa_u_refcount_ref(refcount);
    if(type == DPA_U_REFCOUNT_STATIC){
      struct dpa__u_bo_unique_hashmap_entry*const new = malloc(sizeof(*new));
      *new = (struct dpa__u_bo_unique_hashmap_entry){
        .bo_hashed = {
          .bo_simple = {
            .type = DPA_U_BO_UNIQUE_HASHMAP,
            .extra = false,
            .size = size,
            .data = data,
          },
          .hash = hash,
        },
        // dpa_u_refcount_i_static means the entry will never be freed again.
        // This isn't necessary, but seams sensible for data that will never be freed either.
        .refcount = dpa_u_refcount_i_static,
        .next = *it,
      };
      new_entry = new;
    }else{
      struct dpa__u_bo_entry_refcounted*const new = malloc(sizeof(*new));
      *new = (struct dpa__u_bo_entry_refcounted){
        .entry = {
          .bo_hashed = {
            .bo_simple = {
              .type = DPA_U_BO_UNIQUE_HASHMAP,
              .extra = true,
              .size = size,
              .data = data,
            },
            .hash = hash,
          },
          .refcount = dpa_u_refcount_i_bo_unique(1),
          .next = *it,
        },
        .refcount = refcount,
      };
      new_entry = &new->entry;
    }
  }else{
    struct dpa__u_bo_unique_hashmap_entry*const new = malloc(sizeof(*new) + size);
    *new = (struct dpa__u_bo_unique_hashmap_entry){
      .bo_hashed = {
        .bo_simple = {
          .type = DPA_U_BO_UNIQUE_HASHMAP,
          .extra = false,
          .size = size,
          .data = new+1,
        },
        .hash = hash,
      },
      .refcount = dpa_u_refcount_i_bo_unique(1),
      .next = *it,
    };
    memcpy(new+1, data, size);
    new_entry = new;
  }
  *it = new_entry;
#ifndef DPA_U_NO_THREADS
  unlock_entry(hash);
  // Note: this isn't an exact science
  const size_t count = atomic_fetch_add(&hash_map.count, 1) + 1;
#else
  const size_t count = ++hash_map.count;
#endif
#ifndef DPA_U_SINGLE_BUCKET
  const size_t total_buckets = ((size_t)1) << m_aload(hash_map.shift_size);
  if( total_buckets < BUCKET_COUNT && (float)count / total_buckets >= DPA_U_LOAD_FACTOR_EXPAND )
    grow();
#else
    (void)count;
#endif
  return new_entry;
}

dpa_u_export dpa_u_bo_unique_hashmap_t dpa__u_bo_do_intern_early(dpa_u_any_bo_ro_t*const bo){
  dpa_u_init_seed();
  return dpa__u_bo_do_intern(bo);
}

dpa_u_bo_unique_hashmap_stats_t dpa_u_bo_unique_hashmap_stats(void){
#ifndef DPA_U_NO_THREADS
  mtx_lock(&resize_lock);
#endif
  size_t empty_count = 0;
  size_t i = 0;
#ifndef DPA_U_SINGLE_BUCKET
  const int shift_size = m_aload(hash_map.shift_size);
#else
  const int shift_size = DPA_U_BUCKET_BASE;
#endif
  const size_t total_buckets = ((size_t)1) << shift_size;
  for(int bi = 0; bi < shift_size-(DPA_U_BUCKET_BASE-1); bi++){
    const struct bucket*const buckets = hash_map.bucket[bi];
    const size_t count = ((size_t)1) << (bi+DPA_U_BUCKET_BASE);
    for(size_t j=0; i < count; i++,j++)
      if(!buckets[j].next)
        empty_count += 1;
  }
  size_t collision_count = 0;
  const size_t count = m_aload(hash_map.count);
  if(count > total_buckets - empty_count)
    collision_count = count - (total_buckets - empty_count);
  const double load_factor = (double)count / total_buckets;
#ifndef DPA_U_NO_THREADS
  mtx_unlock(&resize_lock);
#endif
  return (dpa_u_bo_unique_hashmap_stats_t){
    .empty_count = empty_count,
    .collision_count = collision_count,
    .total_buckets = total_buckets,
    .entry_count = count,
    .load_factor = load_factor,
  };
}

void dpa_u_bo_unique_verify(void){
#ifndef DPA_U_NO_THREADS
  mtx_lock(&resize_lock);
#endif
  size_t wrong = 0;
  size_t i = 0;
#ifndef DPA_U_SINGLE_BUCKET
  const int shift_size = m_aload(hash_map.shift_size);
#else
  const int shift_size = DPA_U_BUCKET_BASE;
#endif
  for(int bi = 0; bi < shift_size-(DPA_U_BUCKET_BASE-1); bi++){
    const struct bucket*const buckets = hash_map.bucket[bi];
    const size_t count = ((size_t)1) << (bi+DPA_U_BUCKET_BASE);
    for(size_t j=0; i < count; i++,j++){
#ifndef DPA_U_NO_THREADS
      lock_entry(i);
#endif
      for(dpa__u_bo_unique_hashmap_entry_t*restrict e, *const*it=&buckets[j].next; (e=*it); it=&e->next){
        struct bucket_index x = get_bucket_index(e->bo_hashed.hash);
        if(x.bi != bi || x.i != j){
          fprintf(stderr, "Entry %016zX expected at %X,%zX but found at %X,%zX\n", e->bo_hashed.hash, x.bi, x.i, bi, j);
          wrong += 1;
        }
      }
#ifndef DPA_U_NO_THREADS
      unlock_entry(i);
#endif
    }
  }
#ifndef DPA_U_NO_THREADS
  mtx_unlock(&resize_lock);
#endif
  if(wrong){
    fprintf(stderr, "%zu entries are at the wrong place!\n", wrong);
    abort();
  }
}
