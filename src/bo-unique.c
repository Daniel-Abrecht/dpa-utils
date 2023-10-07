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

struct bucket {
  struct dpa__hash_entry* next;
};

enum {
  ENTRY_TYPE_INLINE,
  ENTRY_TYPE_STATIC,
  ENTRY_TYPE_REFCOUNTED,
  ENTRY_TYPE_REFCOUNTED_2,
};

// This has, in the best case, the size of 4 size_t. In the worst case, it has the size of 6 size_t
struct dpa__hash_entry {
  struct dpa__hash_entry* next;
  dpa_u_hash_t hash;
  struct {
    size_t size : (sizeof(size_t)-1) * CHAR_BIT;
    size_t type_offset : CHAR_BIT; // >=3: entry_refcounted_2. offset is type_offset - 3. <3: see entry_inline..2
  };
  struct dpa_u_refcount_bo_unique refcount; // If the data gets referenced by another entry, the referee probably won't have to store an offset.
};

struct entry_inline {
  struct dpa__hash_entry entry;
  char data[];
};

struct entry_static {
  struct dpa__hash_entry entry;
  const void* data;
};

struct entry_refcounted {
  struct dpa__hash_entry entry;
  size_t offset;
  struct dpa_u_refcount_freeable* refcount;
};

struct entry_refcounted_2 {
  struct dpa__hash_entry entry;
  struct dpa_u_refcount_freeable* refcount;
};


// The first 2 bucket lists will have 2**BUCKET_BASE entries (usually 256).
// Each bucket will have twice the size of the previous one.
#define BUCKET_BASE CHAR_BIT
#define BUCKET_LIST_COUNT ((sizeof(size_t)-1) * CHAR_BIT - BUCKET_BASE)
#define BUCKET_COUNT (((size_t)1)<<(BUCKET_LIST_COUNT+BUCKET_BASE-1)
static_assert(BUCKET_LIST_COUNT > 0, "size_t was smaller than expected");

// Locks are really big. Like, 40 bytes big on m PC! Let's use about 4k of them
enum { LOCK_COUNT = 0x1000 / sizeof(mtx_t) };
mtx_t lock_table[LOCK_COUNT];

struct hash_map {
  _Atomic size_t bmask;
  struct bucket*_Atomic restrict bucket[BUCKET_LIST_COUNT];
};
static struct hash_map hash_map;

__attribute__((used,constructor(101)))
static inline void init(void){
  for(int i=0; i<LOCK_COUNT; i++)
    mtx_init(&lock_table[i], mtx_plain);
}

static inline struct bucket* get_bucket(dpa_u_hash_t hash){
  hash = hash & atomic_load(&hash_map.bmask);
  int i = dpa_u_log2(hash);
  if(hash < (((size_t)1)<<BUCKET_BASE))
    return &atomic_load(&hash_map.bucket[0])[hash];
  return &atomic_load(&hash_map.bucket[i-(BUCKET_BASE-1)])[((size_t)1)<<i];
}

static inline size_t entry_get_offset(const struct dpa__hash_entry*const e){
  size_t type_offset = e->type_offset;
  switch(type_offset){
    case ENTRY_TYPE_INLINE: return 0;
    case ENTRY_TYPE_STATIC: return 0;
    case ENTRY_TYPE_REFCOUNTED: return ((struct entry_refcounted*)e)->offset;
  }
  return type_offset - 2;
}

static inline struct dpa_u_refcount_freeable* entry_get_ext_refcount(const struct dpa__hash_entry*const e){
  switch(e->type_offset){
    case ENTRY_TYPE_INLINE: return 0;
    case ENTRY_TYPE_STATIC: return 0;
    case ENTRY_TYPE_REFCOUNTED: return ((struct entry_refcounted*)e)->refcount;
  }
  return ((struct entry_refcounted_2*)e)->refcount;
}

static inline const void* entry_get_data(const struct dpa__hash_entry*const e){
  size_t type_offset = e->type_offset;
  switch(type_offset){
    case ENTRY_TYPE_INLINE: return ((struct entry_inline*)e)->data;
    case ENTRY_TYPE_STATIC: return ((struct entry_static*)e)->data;
    case ENTRY_TYPE_REFCOUNTED: {
      const struct entry_refcounted*const t = (const struct entry_refcounted*const)e;
      return ((char*)(t->refcount+1)) + t->offset;
    }
  }
  return ((char*)(((struct entry_refcounted_2*)e)->refcount+1)) + (type_offset - ENTRY_TYPE_REFCOUNTED_2);
}

static inline void lock_entry(dpa_u_hash_t hash){
  mtx_lock(&lock_table[hash&(LOCK_COUNT)]);
}

static inline void unlock_entry(dpa_u_hash_t hash){
  mtx_unlock(&lock_table[hash&(LOCK_COUNT)]);
}

const void* dpa__u_bo_unique_get_data(dpa_u_bo_unique_t bo){
  (void)bo;
  // TODO
  return 0;
}

size_t dpa__u_bo_unique_get_size(dpa_u_bo_unique_t bo){
  (void)bo;
  // TODO
  return 0;
}

void dpa__u_bo_unique_ref(dpa_u_bo_unique_t bo){
  (void)bo;
  // TODO
}

bool dpa__u_bo_unique_put(dpa_u_bo_unique_t bo){
  (void)bo;
  // TODO
  return false;
}

dpa_u_bo_unique_t dpa__u_bo_do_intern(const dpa_u_bo_simple_ro_t bo){
  const dpa_u_hash_t hash = dpa_u_bo_hash(bo);
  const size_t size = dpa_u_bo_get_size(bo);
  const void*const data = dpa_u_bo_data(bo);
  struct dpa_u_refcount_freeable* refcount = 0; // dpa_u_bo_get_refcount(bo);
  lock_entry(hash);
  struct bucket* bucket = get_bucket(hash);
  struct dpa__hash_entry** it = &bucket->next;
  for(struct dpa__hash_entry*restrict e; (e=*it); it=&e->next){
    const dpa_u_hash_t e_hash = e->hash;
    const size_t e_size = e->size;
    if(e_hash < hash) continue;
    if(e_size > size) continue;
    if(e_hash > hash) break;
    if(e_size < size) break;
    const void*const e_data = entry_get_data(e);
    if(e_data != data){
      int diff = memcmp(e_data, data, size);
      if(diff < 0) continue;
      if(diff > 0) break;
    }
    dpa_u_refcount_ref(&e->refcount);
    unlock_entry(hash);
    return (dpa_u_bo_unique_t){
      .type = DPA_U_BO_UNIQUE,
      .entry = e,
    };
  }
  struct dpa__hash_entry* new_entry;
  if(refcount){
    enum dpa_u_refcount_type type = dpa_u_refcount_get_type(&refcount->refcount);
    if(type == DPA_U_REFCOUNT_BO_UNIQUE){
      struct dpa__hash_entry* old = dpa_u_container_of(refcount, struct dpa__hash_entry, refcount.freeable);
      struct dpa_u_refcount_freeable*const true_refcount = entry_get_ext_refcount(old);
      if(old->type_offset >= ENTRY_TYPE_REFCOUNTED)
        refcount = true_refcount;
    }
    dpa_u_refcount_ref(refcount);
    if(type == DPA_U_REFCOUNT_STATIC){
      struct entry_static*const new = malloc(sizeof(*new));
      *new = (struct entry_static){
        .entry = {
          .next = *it,
          .hash = hash,
          .size = size,
          .type_offset = ENTRY_TYPE_STATIC,
          // dpa_u_refcount_i_static means the entry will never be freed again.
          // This isn't necessary, but seams sensible for data that will never be freed either.
          .refcount = dpa_u_refcount_i_static,
        },
        .data = data,
      };
      new_entry = &new->entry;
    }else{
      const size_t offset = (const char*)data - (const char*)(refcount + 1);
      if(offset < (((size_t)1)<<CHAR_BIT) - ENTRY_TYPE_REFCOUNTED_2){
        struct entry_refcounted_2*const new = malloc(sizeof(*new));
        *new = (struct entry_refcounted_2){
          .entry = {
            .next = *it,
            .hash = hash,
            .size = size,
            .type_offset = ENTRY_TYPE_REFCOUNTED_2 + offset,
            .refcount = dpa_u_refcount_i_bo_unique(1),
          },
          .refcount = refcount,
        };
        new_entry = &new->entry;
      }else{
        struct entry_refcounted*const new = malloc(sizeof(*new));
        *new = (struct entry_refcounted){
          .entry = {
            .next = *it,
            .hash = hash,
            .size = size,
            .type_offset = ENTRY_TYPE_REFCOUNTED,
            .refcount = dpa_u_refcount_i_bo_unique(1),
          },
          .offset = offset,
          .refcount = refcount,
        };
        new_entry = &new->entry;
      }
    }
  }else{
    struct entry_inline*const new = malloc(sizeof(*new) + size);
    *new = (struct entry_inline){
      .entry = {
        .next = *it,
        .hash = hash,
        .size = size,
        .type_offset = ENTRY_TYPE_INLINE,
        .refcount = dpa_u_refcount_i_bo_unique(1),
      },
    };
    memcpy(new->data, data, size);
    new_entry = &new->entry;
  }
  *it = new_entry;
  unlock_entry(hash);
  return (dpa_u_bo_unique_t){
    .type = DPA_U_BO_UNIQUE,
    .entry = new_entry,
  };
}
