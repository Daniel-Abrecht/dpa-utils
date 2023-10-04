#include <dpa/utils/bo.h>
#include <dpa/utils/refcount.h>
#include <stdatomic.h>
#include <threads.h>

struct bucket {
  struct dpa__hash_entry*_Atomic next;
};

// This has, in the best case, the size of 4 size_t. In the worst case, it has the size of 6 size_t
struct dpa__hash_entry {
  struct dpa__hash_entry*_Atomic next;
  size_t hash;
  struct {
    size_t size : (sizeof(size_t)-1) * CHAR_BIT;
    size_t hoff : CHAR_BIT-1;
    size_t has_ext_refcount : 1;
  };
  struct dpa_u_refcount_freeable refcount; // If the data gets referenced by another entry, the referee probably won't have to store an offset.
};

// The first 2 bucket lists will have 2**BUCKET_BASE entries (usually 256).
// Each bucket will have twice the size of the previous one.
#define BUCKET_BASE CHAR_BIT
#define BUCKET_LIST_COUNT ((sizeof(size_t)-1) * CHAR_BIT - BUCKET_BASE)
#define BUCKET_COUNT (((size_t)1)<<(BUCKET_LIST_COUNT+BUCKET_BASE-1)
static_assert(BUCKET_LIST_COUNT > 0, "size_t was smaller than expected");

struct hash_map {
  mtx_t lock;
  size_t size;
  struct bucket*_Atomic restrict bucket[BUCKET_LIST_COUNT];
};
static struct hash_map hash_map;

__attribute__((used,constructor(101)))
static inline void init(void){
  mtx_init(&hash_map.lock, mtx_plain);
}

static inline size_t entry_get_offset(const struct dpa__hash_entry*restrict const e){
  size_t offset = e->hoff;
  if(offset != 0x7F)
    return offset;
  return *(size_t*)(e + 1);
}

static inline struct dpa_u_refcount_freeable* entry_get_refcount(struct dpa__hash_entry*restrict const e){
  if(!e->has_ext_refcount)
    return 0;
  if(e->hoff != 0x7F)
    return (struct dpa_u_refcount_freeable*)(e+1);
  return (struct dpa_u_refcount_freeable*)((size_t*)(e+1)+1);
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
  (void)bo;
  // TODO
  return (dpa_u_bo_unique_t){0};
}
