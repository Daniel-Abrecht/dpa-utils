
#include <stddef.h>
#include <limits.h>

#ifdef DPA_U_BO_NOT_PACKED
#define dpa__u_bo_packed
#define DPA__U_BO_META(X) \
  struct dpa__u_bo_packed { \
    unsigned char type; \
    unsigned char X; \
  }
#else
#define dpa__u_bo_packed dpa__u_packed
#define DPA__U_BO_META(X) \
  struct dpa__u_bo_packed { \
    unsigned char type : CHAR_BIT - 4; \
    unsigned char X : 4; \
  }
#endif

struct dpa__u_gcc_struct dpa__u_bo_a { alignas(DPA__U_BO_ALIGNMENT) char all[DPA__U_BO_COMMON_SIZE]; };
typedef DPA__U_BO_META(extra) dpa__u_bo_meta_t;

struct dpa_u_bo_inline {
  union {
    struct {
      DPA__U_BO_META(size);
      char data[DPA_U_BO_INLINE_MAX_SIZE];
    };
    dpa__u_bo_a_t all;
  };
};
static_assert(sizeof(dpa_u_bo_inline_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_inline_t has an unexpected size");

#define DPA__U_BO_SIMPLE_MEMBERS(...) \
  union { \
    struct { \
      DPA__U_BO_META(extra); \
      struct dpa__u_bo_packed { \
        size_t size : (sizeof(size_t)-1) * CHAR_BIT; \
      }; \
      __VA_ARGS__ void* data; \
    }; \
    dpa__u_bo_a_t all; \
  }

struct dpa__u_gcc_struct dpa_u_bo_simple_ro {
  DPA__U_BO_SIMPLE_MEMBERS(const);
};
static_assert(sizeof(dpa_u_bo_simple_ro_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_simple_ro_t has an unexpected size");

struct dpa__u_gcc_struct dpa_u_bo_simple {
  union {
    dpa_u_bo_simple_ro_t ro;
    DPA__U_BO_SIMPLE_MEMBERS();
  };
};
static_assert(sizeof(dpa_u_bo_simple_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_simple_t has an unexpected size");

struct dpa__u_gcc_struct dpa_u_bo_unique {
  union {
    DPA__U_BO_META(extra);
    dpa_u_bo_inline_t bo_inline;
    struct { DPA__U_BO_META(extra) bo_unique_hashmap_meta; dpa_u_bo_unique_hashmap_t bo_unique_hashmap; };
    dpa__u_bo_a_t all;
  };
};
static_assert(sizeof(dpa_u_bo_unique_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_unique_t has an unexpected size");

typedef struct dpa__u_gcc_struct dpa__u_bo_unique_reversible_hash {
  size_t hash[(DPA__U_BO_COMMON_SIZE+sizeof(size_t)-1)/sizeof(size_t)];
} dpa__u_bo_unique_reversible_hash_t;
static_assert(sizeof(dpa__u_bo_unique_reversible_hash_t) >= DPA__U_BO_COMMON_SIZE, "dpa__u_bo_unique_reversible_hash_t is too small!");

struct dpa__u_gcc_struct dpa_u_bo_ro {
  union {
    DPA__U_BO_META(extra);
    dpa_u_bo_inline_t bo_inline;
    dpa_u_bo_simple_ro_t bo_simple;
    struct { DPA__U_BO_META(extra) bo_unique_hashmap_meta; dpa_u_bo_unique_hashmap_t bo_unique_hashmap; };
    dpa_u_bo_unique_t bo_unique;
    dpa__u_bo_a_t all;
  };
};
static_assert(sizeof(dpa_u_bo_ro_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_ro_t has an unexpected size");

struct dpa__u_gcc_struct dpa_u_bo {
  union {
    DPA__U_BO_META(extra);
    dpa_u_bo_ro_t ro;
    dpa_u_bo_inline_t bo_inline;
    dpa_u_bo_simple_t bo_simple;
    dpa__u_bo_a_t all;
  };
};
static_assert(sizeof(dpa_u_bo_t) == DPA__U_BO_COMMON_SIZE, "dpa_u_bo_t has an unexpected size");

////

struct dpa__u_gcc_struct dpa_u_bo_refcounted_ro {
  union {
    DPA__U_BO_META(extra);
    dpa_u_bo_simple_ro_t bo_simple;
  };
  // The refcount should be allocated with the data, because it shares the lifetime of the data, not of the bo.
  dpa_u_refcount_freeable_t* refcount;
};

struct dpa__u_gcc_struct dpa_u_bo_refcounted {
  union {
    struct {
      union {
        DPA__U_BO_META(extra);
        dpa_u_bo_simple_t bo_simple;
      };
      // The refcount should be allocated with the data, because it shares the lifetime of the data, not of the bo.
      dpa_u_refcount_freeable_t* refcount;
    };
    struct dpa_u_bo_refcounted_ro ro;
  };
};
static_assert(sizeof(dpa_u_bo_refcounted_ro_t) == sizeof(dpa_u_bo_refcounted_t), "dpa_u_bo_hashed_t and dpa_u_bo_hashedro_t should have the same size");
static_assert(offsetof(dpa_u_bo_refcounted_ro_t, bo_simple) == offsetof(dpa_u_bo_refcounted_t, bo_simple), "Member 'bo_simple' at wrong offset");
static_assert(offsetof(dpa_u_bo_refcounted_ro_t, refcount) == offsetof(dpa_u_bo_refcounted_t, refcount), "Member 'refcount' at wrong offset");
static_assert(offsetof(dpa_u_bo_refcounted_t, ro) == 0, "Member 'ro' at wrong offset");

struct dpa__u_gcc_struct dpa_u_bo_hashed_ro {
  union {
    DPA__U_BO_META(extra);
    dpa_u_bo_simple_ro_t bo_simple;
  };
  dpa_u_hash_t hash;
};

struct dpa__u_gcc_struct dpa_u_bo_hashed {
  union {
    struct {
      union {
        DPA__U_BO_META(extra);
        dpa_u_bo_simple_t bo_simple;
      };
      dpa_u_hash_t hash;
    };
    dpa_u_bo_hashed_ro_t ro;
  };
};
static_assert(sizeof(dpa_u_bo_hashed_ro_t) == sizeof(dpa_u_bo_hashed_t), "dpa_u_bo_hashed_t and dpa_u_bo_hashedro_t should have the same size");
static_assert(offsetof(dpa_u_bo_hashed_ro_t, bo_simple) == offsetof(dpa_u_bo_hashed_t, bo_simple), "Member 'bo_simple' at wrong offset");
static_assert(offsetof(dpa_u_bo_hashed_ro_t, hash) == offsetof(dpa_u_bo_hashed_t, hash), "Member 'hash' at wrong offset");
static_assert(offsetof(dpa_u_bo_hashed_t, ro) == 0, "Member 'ro' at wrong offset");

struct dpa__u_gcc_struct dpa_u_bo_refcounted_hashed_ro {
  union {
    DPA__U_BO_META(extra);
    dpa_u_bo_simple_ro_t bo_simple;
    dpa_u_bo_refcounted_ro_t bo_refcounted;
  };
  dpa_u_hash_t hash;
};

// Note: There will be no dpa_u_bo_refcounted_hashed_ro type. The hash and refcount depends on the data.
// The refcount is stored with the data, but the hash is not. Therefore, modifying a refcounted hashed buffer
// is always wrong.

////

struct dpa__u_gcc_struct dpa__u_bo_unique_hashmap_entry {
  dpa_u_bo_hashed_ro_t bo_hashed;
  struct dpa__u_refcount_bo_unique refcount;
  struct dpa__u_bo_unique_hashmap_entry* next;
};
static_assert(offsetof(struct dpa__u_bo_unique_hashmap_entry, bo_hashed) == 0, "Expected first member to be of dpa_u_bo_hashed_ro_t type");

struct dpa__u_gcc_struct dpa__u_bo_entry_refcounted {
  dpa__u_bo_unique_hashmap_entry_t entry;
  dpa_u_refcount_freeable_t* refcount;
};
static_assert(offsetof(struct dpa__u_bo_unique_hashmap_entry, bo_hashed) == 0, "Expected first member to be of dpa__u_bo_unique_hashmap_entry_t type");

////

static_assert(alignof(struct dpa_u_bo_ro) == alignof(struct dpa_u_bo_simple_ro), "dpa_u_bo_simple_ro has wrong alignment");
static_assert(alignof(struct dpa_u_bo_ro) == alignof(struct dpa_u_bo_simple), "dpa_u_bo_simple has wrong alignment");
static_assert(alignof(struct dpa_u_bo_ro) == alignof(struct dpa_u_bo), "dpa_u_bo has wrong alignment");
static_assert(alignof(struct dpa_u_bo_ro) == alignof(struct dpa_u_bo_unique), "dpa_u_bo_unique has wrong alignment");
static_assert(alignof(struct dpa_u_bo_ro) == alignof(struct dpa_u_bo_inline), "dpa_u_bo_inline has wrong alignment");

////

// This is an internal type used by some dpa_u_t_bo* conversion macros to change the storage duration & lifetime of
// inline BOs to the current block scope, while retaining enough memory for the hash of a hashed bo.
union dpa__u_gcc_struct dpa__u_hashed_conv_helper {
  dpa__u_bo_meta_t meta;
  dpa_u_bo_inline_t bo_inline;
  dpa_u_bo_hashed_ro_t bo_hashed_ro;
  dpa_u_bo_hashed_t bo_hashed;
};
static_assert(sizeof(union dpa__u_hashed_conv_helper) == sizeof(dpa_u_bo_hashed_ro_t), "union dpa__u_hashed_conv_helper has an unexpected size");

union dpa__u_gcc_struct dpa__u_any_helper {
  dpa__u_bo_meta_t meta;
  dpa_u_bo_t bo;
  dpa_u_bo_hashed_t bo_hashed;
  dpa_u_bo_refcounted_t bo_refcounted;
};

union dpa__u_gcc_struct dpa__u_any_ro_helper {
  dpa__u_bo_meta_t meta;
  dpa_u_bo_ro_t bo;
  dpa_u_bo_hashed_ro_t bo_hashed;
  dpa_u_bo_refcounted_ro_t bo_refcounted;
};

union dpa__u_gcc_struct dpa__u_any_ro_helper_2 {
  dpa__u_bo_meta_t meta;
  dpa_u_bo_ro_t bo;
  dpa_u_bo_hashed_ro_t bo_hashed;
  dpa_u_bo_refcounted_ro_t bo_refcounted;
  dpa_u_bo_refcounted_hashed_ro_t bo_refcounted_hashed;
};

union dpa__u_gcc_struct dpa__u_bo_ptr_helper {
  struct {
    dpa__u_bo_meta_t meta;
    const void* ptr;
  };
  dpa_u_bo_inline_t bo_inline;
};

// dpa_u_bo_unique_t is designed to be the size of 2 size_t (unless DPA_U_BO_NOT_PACKED is set), that's still fairly small.
// If there is an DPA_HAS_UINT128, it may be big enough to hold it. Otherwise, we assume long long unsigned is the biggest integer.
// Actually checking if 2 size_t fit in long long unsigned is a bit tricky though. The _WIDTH macros aren't available before c11,
// and we can't just check SIZE_MAX*2 <= ULLONG_MAX, because that may overflow.
#if ( defined(DPA_HAS_UINT128) && !defined(DPA_U_BO_NOT_PACKED) ) || (ULLONG_MAX/SIZE_MAX >= 2llu && ULLONG_MAX/SIZE_MAX-2llu >= SIZE_MAX)
#if UINT_MAX/SIZE_MAX >= 2llu && UINT_MAX/SIZE_MAX-2llu >= SIZE_MAX
typedef unsigned dpa_u_bo_unique_as_uint_t;
#define DPA_U_BO_UNIQUE_UINT_COMPATIBLE u
#elif ULONG_MAX/SIZE_MAX >= 2llu && ULONG_MAX/SIZE_MAX-2llu >= SIZE_MAX
typedef unsigned long dpa_u_bo_unique_as_uint_t;
#define DPA_U_BO_UNIQUE_UINT_COMPATIBLE lu
#elif ULLONG_MAX/SIZE_MAX >= 2llu && ULLONG_MAX/SIZE_MAX-2llu >= SIZE_MAX
typedef unsigned long long dpa_u_bo_unique_as_uint_t;
#define DPA_U_BO_UNIQUE_UINT_COMPATIBLE llu
#else
typedef dpa_uint128_t dpa_u_bo_unique_as_uint_t;
#define DPA_U_BO_UNIQUE_UINT_COMPATIBLE u128
#endif
static_assert(sizeof(dpa_u_bo_unique_as_uint_t) >= sizeof(dpa_u_bo_unique_t));
#endif
