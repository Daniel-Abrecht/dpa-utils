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

DPA_U_EXPORT const void* dpa__u_bo_unique_get_data(dpa_u_bo_unique_t bo);
DPA_U_EXPORT size_t dpa__u_bo_unique_get_size(dpa_u_bo_unique_t bo);

#define LOAD_FACTOR_EXPAND 2
#define LOAD_FACTOR_SHRINK 0.5

typedef struct dpa_u_bo_unique dpa__u_bo_unique_entry_t;

struct bucket {
  dpa__u_bo_unique_entry_t* next;
};

// The first 2 bucket lists will have 2**BUCKET_BASE entries (usually 256).
// Each bucket will have twice the size of the previous one.
#define BUCKET_BASE CHAR_BIT
#define BUCKET_LIST_COUNT (int)((sizeof(size_t)-1) * CHAR_BIT - BUCKET_BASE)
#define BUCKET_COUNT (((size_t)1)<<(BUCKET_LIST_COUNT+BUCKET_BASE-1))
static_assert(BUCKET_LIST_COUNT > 0, "size_t was smaller than expected");

// Locks are really big. Like, 40 bytes big on m PC!
enum { LOCK_COUNT = 1<<7 };

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

static inline struct bucket* get_bucket(dpa_u_hash_t hash){
  size_t shift_size = atomic_load(&hash_map.shift_size);
  hash = hash & ((((size_t)1)<<shift_size)-1);
  if(hash >= atomic_load(&hash_map.move_pending))
    hash -= ((size_t)1)<<(shift_size-1);
  int i = dpa_u_log2(hash);
  if(hash < (((size_t)1)<<BUCKET_BASE))
    return &atomic_load(&hash_map.bucket[0])[hash];
  return &atomic_load(&hash_map.bucket[i-(BUCKET_BASE-1)])[((size_t)1)<<i];
}

/*static inline size_t entry_get_offset(const dpa__u_bo_unique_entry_t*const e){
  size_t type_offset = e->type_offset;
  switch(type_offset){
    case DPA__U_BO_UNIQUE__ENTRY_TYPE_INLINE: return 0;
    case DPA__U_BO_UNIQUE__ENTRY_TYPE_STATIC: return 0;
    case DPA__U_BO_UNIQUE__ENTRY_TYPE_REFCOUNTED: return ((struct dpa__u_bo_entry_refcounted*)e)->offset;
  }
  return type_offset - 2;
}*/

static inline struct dpa_u_refcount_freeable* entry_get_ext_refcount(const dpa__u_bo_unique_entry_t*const e){
  switch(e->type_offset){
    case DPA__U_BO_UNIQUE__ENTRY_TYPE_INLINE: return 0;
    case DPA__U_BO_UNIQUE__ENTRY_TYPE_STATIC: return 0;
    case DPA__U_BO_UNIQUE__ENTRY_TYPE_REFCOUNTED: return ((struct dpa__u_bo_entry_refcounted*)e)->refcount;
  }
  return ((struct dpa__u_bo_entry_refcounted_2*)e)->refcount;
}

static inline void lock_entry(dpa_u_hash_t hash){
  mtx_lock(&lock_table[hash&(LOCK_COUNT-1)]);
}

static inline void unlock_entry(dpa_u_hash_t hash){
  mtx_unlock(&lock_table[hash&(LOCK_COUNT-1)]);
}

void dpa__u_bo_unique_ref(const dpa__u_bo_unique_entry_t* _bo){
  dpa__u_bo_unique_entry_t* bo = (dpa__u_bo_unique_entry_t*)_bo;
  dpa_u_refcount_ref(&bo->refcount);
}

bool dpa__u_bo_unique_put(const dpa__u_bo_unique_entry_t* _bo){
  dpa__u_bo_unique_entry_t* bo = (dpa__u_bo_unique_entry_t*)_bo;
  return dpa_u_refcount_put(&bo->refcount);
}

static inline void grow(void){
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
  struct bucket*const new_bucket = malloc(sizeof(struct bucket[((size_t)1)<<shift_size]));
  if(!new_bucket){
    // TODO: Log an error
    goto out;
  }
  atomic_store(&hash_map.bucket[shift_size-(BUCKET_BASE-1)], new_bucket);
  size_t i = 0;
  for(int bi = 0; bi < shift_size; bi++){
    struct bucket*const buckets = hash_map.bucket[bi];
    const size_t count = ((size_t)1) << (bi+BUCKET_BASE);
    for(; i < count; i++){
      lock_entry(i);
      for(dpa__u_bo_unique_entry_t*restrict e, **it=&buckets[i-count/2].next; (e=*it); it=&e->next){
        if(!(e->hash & ((size_t)1)<<shift_size))
          continue;
        *it = 0;
        new_bucket->next = e;
        break;
      }
      atomic_store(&hash_map.move_pending, i+1);
      unlock_entry(i);
    }
  }
out:
  mtx_unlock(&resize_lock);
}

dpa_u_bo_unique_t dpa__u_bo_do_intern(const dpa_u_bo_simple_ro_t bo){
  const dpa_u_hash_t hash = dpa_u_bo_hash(bo);
  const size_t size = dpa_u_bo_get_size(bo);
  const void*const data = dpa_u_bo_data(bo);
  struct dpa_u_refcount_freeable* refcount = 0; // dpa_u_bo_get_refcount(bo);
  lock_entry(hash);
  struct bucket* bucket = get_bucket(hash);
  dpa__u_bo_unique_entry_t** it = &bucket->next;
  for(dpa__u_bo_unique_entry_t*restrict e; (e=*it); it=&e->next){
    const dpa_u_hash_t e_hash = e->hash;
    const size_t e_size = e->size;
    if(e_hash < hash) continue;
    if(e_size > size) continue;
    if(e_hash > hash) break;
    if(e_size < size) break;
    const void*const e_data = dpa__u_bo_unique_get_data(e);
    if(e_data != data){
      int diff = memcmp(e_data, data, size);
      if(diff < 0) continue;
      if(diff > 0) break;
    }
    dpa_u_refcount_ref(&e->refcount);
    unlock_entry(hash);
    return e;
  }
  dpa__u_bo_unique_entry_t* new_entry;
  if(refcount){
    enum dpa_u_refcount_type type = dpa_u_refcount_get_type(&refcount->refcount);
    if(type == DPA_U_REFCOUNT_BO_UNIQUE){
      dpa__u_bo_unique_entry_t* old = dpa_u_container_of(refcount, dpa__u_bo_unique_entry_t, refcount.freeable);
      struct dpa_u_refcount_freeable*const true_refcount = entry_get_ext_refcount(old);
      if(old->type_offset >= DPA__U_BO_UNIQUE__ENTRY_TYPE_REFCOUNTED)
        refcount = true_refcount;
    }
    dpa_u_refcount_ref(refcount);
    if(type == DPA_U_REFCOUNT_STATIC){
      struct dpa__u_bo_entry_static*const new = malloc(sizeof(*new));
      *new = (struct dpa__u_bo_entry_static){
        .entry = {
          .next = *it,
          .hash = hash,
          .size = size,
          .type_offset = DPA__U_BO_UNIQUE__ENTRY_TYPE_STATIC,
          // dpa_u_refcount_i_static means the entry will never be freed again.
          // This isn't necessary, but seams sensible for data that will never be freed either.
          .refcount = dpa_u_refcount_i_static,
        },
        .data = data,
      };
      new_entry = &new->entry;
    }else{
      const size_t offset = (const char*)data - (const char*)(refcount + 1);
      if(offset < (((size_t)1)<<CHAR_BIT) - DPA__U_BO_UNIQUE__ENTRY_TYPE_REFCOUNTED_2){
        struct dpa__u_bo_entry_refcounted_2*const new = malloc(sizeof(*new));
        *new = (struct dpa__u_bo_entry_refcounted_2){
          .entry = {
            .next = *it,
            .hash = hash,
            .size = size,
            .type_offset = DPA__U_BO_UNIQUE__ENTRY_TYPE_REFCOUNTED_2 + offset,
            .refcount = dpa_u_refcount_i_bo_unique(1),
          },
          .refcount = refcount,
        };
        new_entry = &new->entry;
      }else{
        struct dpa__u_bo_entry_refcounted*const new = malloc(sizeof(*new));
        *new = (struct dpa__u_bo_entry_refcounted){
          .entry = {
            .next = *it,
            .hash = hash,
            .size = size,
            .type_offset = DPA__U_BO_UNIQUE__ENTRY_TYPE_REFCOUNTED,
            .refcount = dpa_u_refcount_i_bo_unique(1),
          },
          .offset = offset,
          .refcount = refcount,
        };
        new_entry = &new->entry;
      }
    }
  }else{
    struct dpa__u_bo_entry_inline*const new = malloc(sizeof(*new) + size);
    *new = (struct dpa__u_bo_entry_inline){
      .entry = {
        .next = *it,
        .hash = hash,
        .size = size,
        .type_offset = DPA__U_BO_UNIQUE__ENTRY_TYPE_INLINE,
        .refcount = dpa_u_refcount_i_bo_unique(1),
      },
    };
    memcpy(new->data, data, size);
    new_entry = &new->entry;
  }
  *it = new_entry;
  const size_t count = atomic_fetch_add(&hash_map.count, 1) + 1;
  unlock_entry(hash);
  const size_t total_buckets = ((size_t)1) << atomic_load(&hash_map.shift_size);
  if( total_buckets < BUCKET_COUNT && (float)count / total_buckets >= LOAD_FACTOR_EXPAND )
    grow();
  return new_entry;
}
