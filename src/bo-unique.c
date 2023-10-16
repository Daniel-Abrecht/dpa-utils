#include <dpa/utils/bo.h>
#include <dpa/utils/math.h>
#include <dpa/utils/hash.h>
#include <dpa/utils/refcount.h>

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <stdatomic.h>
#include <threads.h>

extern void dpa__u_bo_unique_hashmap_ref(dpa_u_bo_unique_hashmap_t);
extern bool dpa__u_bo_unique_hashmap_put(dpa_u_bo_unique_hashmap_t);

#define LOAD_FACTOR_EXPAND 2
#define LOAD_FACTOR_SHRINK 0.5

struct bucket {
  dpa__u_bo_unique_hashmap_entry_t* next;
};

// The first 2 bucket lists will have 2**BUCKET_BASE entries (usually 256).
// Each bucket will have twice the size of the previous one.
#define BUCKET_BASE (9)
#define BUCKET_LIST_COUNT (int)((sizeof(dpa_u_hash_t)-1) * CHAR_BIT - BUCKET_BASE)
#define BUCKET_COUNT (((dpa_u_hash_t)1)<<(BUCKET_LIST_COUNT+BUCKET_BASE))

// Locks are really big. Like, 40 bytes big on my PC!
enum { LOCK_BIT_COUNT = 7 };
enum { LOCK_COUNT = 1llu<<LOCK_BIT_COUNT };

static_assert(BUCKET_LIST_COUNT > 0, "dpa_u_hash_t was smaller than expected");
static_assert(LOCK_COUNT <= (((size_t)1)<<BUCKET_BASE), "There can't be more locks than buckets in the first bucket list");
static_assert(!(LOCK_COUNT & (LOCK_COUNT-1)), "LOCK_COUNT must be a power of 2");

static mtx_t lock_table[LOCK_COUNT];
static mtx_t resize_lock;

struct hash_map {
  _Atomic size_t move_pending;
  _Atomic size_t count;
  _Atomic int shift_size;
  struct bucket*_Atomic bucket[BUCKET_LIST_COUNT];
};
static struct hash_map hash_map = {
  .shift_size = BUCKET_BASE,
  .move_pending = ((size_t)1)<<BUCKET_BASE,
  .count = 0,
  .bucket[0] = (struct bucket[((size_t)1)<<BUCKET_BASE]){0}, // the first bucket list is pre-allocated & static
};

__attribute__((used,constructor(101)))
static inline void init(void){
  for(int i=0; i<LOCK_COUNT; i++)
    mtx_init(&lock_table[i], mtx_plain);
  mtx_init(&resize_lock, mtx_plain);
}

struct bucket_index {
  int bi;
  size_t i;
};

static inline struct bucket_index get_bucket_index(size_t hash){
  int shift_size = atomic_load(&hash_map.shift_size);
  hash >>= 64 - shift_size;
  if(shift_size > BUCKET_BASE && (hash & 1) && (hash>>1) >= atomic_load(&hash_map.move_pending)-(((size_t)1)<<(shift_size-1))){
    hash >>= 1;
    shift_size -= 1;
  }
  int i = dpa_u_ctzll(hash);
  if(i > shift_size - BUCKET_BASE)
    i = shift_size - BUCKET_BASE;
  int j = (shift_size - BUCKET_BASE) - i;
  hash >>= i + !!j;
  return (struct bucket_index){ j, hash };
}

static inline struct bucket* get_bucket(dpa_u_hash_t hash){
  struct bucket_index x = get_bucket_index(hash);
  return &atomic_load(&hash_map.bucket[x.bi])[x.i];
}

static inline struct dpa_u_refcount_freeable* entry_get_ext_refcount(const dpa__u_bo_unique_hashmap_entry_t*const e){
  if(e->base.extra)
    return ((struct dpa__u_bo_entry_refcounted*)e)->refcount;
  return 0;
}

static inline void lock_entry(dpa_u_hash_t hash){
  mtx_lock(&lock_table[hash>>(64-LOCK_BIT_COUNT)]);
}

static inline void unlock_entry(dpa_u_hash_t hash){
  mtx_unlock(&lock_table[hash>>(64-LOCK_BIT_COUNT)]);
}

static void grow(void){
  {
    const int result = mtx_trylock(&resize_lock);
    if(result == thrd_busy)
      return;
    assert(result == thrd_success);
  }
  const int shift_size = atomic_load(&hash_map.shift_size);
  if(shift_size >= BUCKET_LIST_COUNT)
    goto out;
  atomic_store(&hash_map.shift_size, shift_size + 1);
  // atomic_store(&hash_map.move_pending, ((size_t)1)<<shift_size); // Should already be set to this
  const size_t size = ((size_t)1)<<shift_size;
  struct bucket*const new_bucket = calloc(size, sizeof(struct bucket));
  if(!new_bucket){
    // TODO: Log an error
    goto out;
  }
  atomic_store(&hash_map.bucket[shift_size-(BUCKET_BASE-1)], new_bucket);
  for(size_t i=0; i<size; i++){
    const size_t key = (((i<<1)|1)<<(63-shift_size));
    lock_entry(key);
    struct bucket*const bucket = get_bucket(key);
    for(dpa__u_bo_unique_hashmap_entry_t* e, **it=&bucket->next; (e=*it); it=&e->next){
      size_t hk = e->hash >> (63-shift_size);
      if(!(1&hk))
        continue;
      assert((hk>>1) == i);
      new_bucket[i].next = e;
      *it = 0;
      break;
    }
    atomic_store(&hash_map.move_pending, size + i+1);
    unlock_entry(key);
  }
out:
  mtx_unlock(&resize_lock);
}

static void shrink(void){
  {
    const int result = mtx_trylock(&resize_lock);
    if(result == thrd_busy)
      return;
    assert(result == thrd_success);
  }
  const int shift_size = atomic_load(&hash_map.shift_size) - 1;
  if(shift_size < BUCKET_BASE){
    mtx_unlock(&resize_lock);
    return;
  }
  struct bucket*const old_bucket = hash_map.bucket[shift_size-(BUCKET_BASE-1)];
  const size_t size = ((size_t)1)<<shift_size;
  for(size_t i=size; i--; ){
    const size_t key = (((i<<1)|1)<<(63-shift_size));
    lock_entry(key);
    atomic_store(&hash_map.move_pending, i + size);
    struct bucket*const bucket = get_bucket(key);
    dpa__u_bo_unique_hashmap_entry_t** it = &bucket->next;
    while(*it) it=&(*it)->next;
    *it = old_bucket[i].next;
    unlock_entry(key);
  }
  atomic_store(&hash_map.shift_size, shift_size);
  atomic_store(&hash_map.bucket[shift_size-(BUCKET_BASE-1)], 0);
  mtx_unlock(&resize_lock);
  free(old_bucket);
}

DPA_U_EXPORT void dpa__u_bo_unique_hashmap_destroy(const struct dpa_u_refcount_freeable* _bo){
  const dpa__u_bo_unique_hashmap_entry_t* bo = dpa_u_container_of(_bo, const dpa__u_bo_unique_hashmap_entry_t, refcount.freeable);
  const dpa_u_hash_t hash = bo->hash;
  lock_entry(hash);
  if(!dpa_u_refcount_is_zero(&bo->refcount.refcount)){
    // Someone else picked up the entry before we got to remove it.
    unlock_entry(hash);
    return;
  }
  for(dpa__u_bo_unique_hashmap_entry_t **it=&get_bucket(hash)->next, *e; (e=*it); it=&e->next){
    if(e != bo)
      continue;
    *it = e->next;
    unlock_entry(hash);
    struct dpa_u_refcount_freeable* rc = entry_get_ext_refcount(e);
    free(e);
    if(rc) dpa_u_refcount_put(rc);
    const size_t count = atomic_fetch_sub(&hash_map.count, 1) - 1;
    const size_t total_buckets = ((size_t)1) << atomic_load(&hash_map.shift_size);
    if( total_buckets > (((size_t)1) << BUCKET_BASE) && (float)count / total_buckets <= LOAD_FACTOR_SHRINK )
      shrink();
    return;
  }
  dpa_u_abort("%s", "The dpa_u_bo_unique_hashmap_t to be destroyed could not be found");
}

DPA_U_EXPORT dpa_u_bo_unique_hashmap_t dpa__u_bo_do_intern(dpa_u_any_bo_ro_t* _bo){
  const dpa_u_bo_ro_t*const bo = (const dpa_u_bo_ro_t*)_bo;
  const dpa_u_hash_t hash = dpa_u_bo_hash(bo);
  const size_t size = dpa_u_bo_get_size(bo);
  const void*const data = dpa_u_bo_data(bo);
  struct dpa_u_refcount_freeable* refcount = dpa_u_bo_get_refcount(bo);
  lock_entry(hash);
  struct bucket* bucket = get_bucket(hash);
  dpa__u_bo_unique_hashmap_entry_t** it = &bucket->next;
  for(dpa__u_bo_unique_hashmap_entry_t*restrict e; (e=*it); it=&e->next){
    const dpa_u_hash_t e_hash = e->hash;
    const size_t e_size = e->base.size;
    if(e_hash < hash) continue;
    if(e_size > size) continue;
    if(e_hash > hash) break;
    if(e_size < size) break;
    const void*const e_data = e->base.data;
    if(e_data != data){
      int diff = memcmp(e_data, data, size);
      if(diff < 0) continue;
      if(diff > 0) break;
    }
    dpa_u_refcount_ref(&e->refcount);
    unlock_entry(hash);
    return e;
  }
  dpa__u_bo_unique_hashmap_entry_t* new_entry;
  if(refcount){
    enum dpa_u_refcount_type type = dpa_u_refcount_get_type(&refcount->refcount);
    if(type == DPA_U_REFCOUNT_BO_UNIQUE_HASHMAP){
      dpa__u_bo_unique_hashmap_entry_t* old = dpa_u_container_of(refcount, dpa__u_bo_unique_hashmap_entry_t, refcount.freeable);
      struct dpa_u_refcount_freeable*const true_refcount = entry_get_ext_refcount(old);
      if(old->base.extra)
        refcount = true_refcount;
    }
    dpa_u_refcount_ref(refcount);
    if(type == DPA_U_REFCOUNT_STATIC){
      struct dpa__u_bo_unique_hashmap_entry*const new = malloc(sizeof(*new));
      *new = (struct dpa__u_bo_unique_hashmap_entry){
        .base = {
          .type = DPA_U_BO_SIMPLE,
          .extra = false,
          .size = size,
          .data = data,
        },
        // dpa_u_refcount_i_static means the entry will never be freed again.
        // This isn't necessary, but seams sensible for data that will never be freed either.
        .refcount = dpa_u_refcount_i_static,
        .next = *it,
        .hash = hash,
      };
      new_entry = new;
    }else{
      struct dpa__u_bo_entry_refcounted*const new = malloc(sizeof(*new));
      *new = (struct dpa__u_bo_entry_refcounted){
        .entry = {
          .base = {
            .type = DPA_U_BO_SIMPLE,
            .extra = true,
            .size = size,
            .data = data,
          },
          .refcount = dpa_u_refcount_i_bo_unique(1),
          .next = *it,
          .hash = hash,
        },
        .refcount = refcount,
      };
      new_entry = &new->entry;
    }
  }else{
    struct dpa__u_bo_unique_hashmap_entry*const new = malloc(sizeof(*new) + size);
    *new = (struct dpa__u_bo_unique_hashmap_entry){
      .base = {
        .type = DPA_U_BO_SIMPLE,
        .extra = false,
        .size = size,
        .data = new+1,
      },
      .refcount = dpa_u_refcount_i_bo_unique(1),
      .next = *it,
      .hash = hash,
    };
    memcpy(new+1, data, size);
    new_entry = new;
  }
  *it = new_entry;
  unlock_entry(hash);
  // Note: this isn't an exact science
  const size_t count = atomic_fetch_add(&hash_map.count, 1) + 1;
  const size_t total_buckets = ((size_t)1) << atomic_load(&hash_map.shift_size);
  if( total_buckets < BUCKET_COUNT && (float)count / total_buckets >= LOAD_FACTOR_EXPAND )
    grow();
  return new_entry;
}

dpa_u_bo_unique_hashmap_stats_t dpa_u_bo_unique_hashmap_stats(void){
  mtx_lock(&resize_lock);
  size_t empty_count = 0;
  size_t i = 0;
  const int shift_size = atomic_load(&hash_map.shift_size);
  const size_t total_buckets = ((size_t)1) << shift_size;
  for(int bi = 0; bi < shift_size-(BUCKET_BASE-1); bi++){
    const struct bucket*const buckets = hash_map.bucket[bi];
    const size_t count = ((size_t)1) << (bi+BUCKET_BASE);
    for(size_t j=0; i < count; i++,j++)
      if(!buckets[j].next)
        empty_count += 1;
  }
  size_t collision_count = 0;
  const size_t count = atomic_load(&hash_map.count);
  if(count > total_buckets - empty_count)
    collision_count = count - (total_buckets - empty_count);
  const double load_factor = (double)count / total_buckets;
  mtx_unlock(&resize_lock);
  return (dpa_u_bo_unique_hashmap_stats_t){
    .empty_count = empty_count,
    .collision_count = collision_count,
    .total_buckets = total_buckets,
    .entry_count = count,
    .load_factor = load_factor,
  };
}

void dpa_u_bo_unique_verify(void){
  mtx_lock(&resize_lock);
  size_t wrong = 0;
  size_t i = 0;
  const int shift_size = atomic_load(&hash_map.shift_size);
  for(int bi = 0; bi < shift_size-(BUCKET_BASE-1); bi++){
    const struct bucket*const buckets = hash_map.bucket[bi];
    const size_t count = ((size_t)1) << (bi+BUCKET_BASE);
    for(size_t j=0; i < count; i++,j++){
      lock_entry(i);
      for(dpa__u_bo_unique_hashmap_entry_t*restrict e, *const*it=&buckets[j].next; (e=*it); it=&e->next){
        struct bucket_index x = get_bucket_index(e->hash);
        if(x.bi != bi || x.i != j){
          fprintf(stderr, "Entry %016zX expected at %X,%zX but found at %X,%zX\n", e->hash, x.bi, x.i, bi, j);
          wrong += 1;
        }
      }
      unlock_entry(i);
    }
  }
  mtx_unlock(&resize_lock);
  if(wrong){
    fprintf(stderr, "%zu entries are at the wrong place!\n", wrong);
    abort();
  }
}
