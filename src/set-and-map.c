#include <dpa/utils/set.h>
#include <dpa/utils/map.h>
#include <dpa/utils/math.h>

#define DPA__U_SM_BITMAP_OFFSET(INDEX) ((INDEX)/(sizeof(dpa_u_giant_unsigned_int_t)*CHAR_BIT))
#define DPA__U_SM_BITMAP_BIT(INDEX) (((dpa_u_giant_unsigned_int_t)1)<<((INDEX)%(sizeof(dpa_u_giant_unsigned_int_t)*CHAR_BIT)))

struct lookup_result {
  size_t index;
  bool found;
};

// TODO: Move that to another file
uintptr_t dpa_u_hash_pointer(const void* pointer){
  uintptr_t num = (uintptr_t)pointer;
  return ((num >> 2) ^ (num >> 6) ^ (num >> 10) ^ (num >> 14));
}

static size_t count_to_size(size_t n){
  enum { MIN_SIZE = 32 };
  n += n / 8; // Ensure there is some free space left 100/8 = 12.5%
  return (((size_t)2)<<dpa_u_log2(n|(MIN_SIZE-1)));
}

#define DPA__U_SM_HASH_KEY(X) _Generic((X), \
    void*: dpa_u_hash_pointer(DPA__G(void*,(X))), \
    const void*: dpa_u_hash_pointer(DPA__G(const void*,(X))), \
    dpa_u_bo_unique_t: dpa_u_bo_get_hash(DPA__G(dpa_u_bo_unique_t,(X))), \
    default: (X) /* TODO */ \
  )

#define GDH(X) _Generic((X), \
    void*: 0, \
    const void*: 0, \
    dpa_u_bo_unique_t: 0, \
    default: (X) \
  )

#define DPA__U_SM_CMP(A,B) _Generic((A), \
    void*: dpa_u_ptr_compare(DPA__G(const void*,(A)), DPA__G(const void*,(B))), \
    const void*: dpa_u_ptr_compare(DPA__G(const void*,(A)), DPA__G(const void*,(B))), \
    dpa_u_bo_unique_t: dpa_u_bo_compare(DPA__G(dpa_u_bo_unique_t,(A)), DPA__G(dpa_u_bo_unique_t,(B))), \
    default: (GDH(A) < GDH(B) ? -1 : GDH(B) < GDH(A) ? 1 : 0) \
  )

#define DPA__U_SM_TEMPLATE <dpa/utils/set-and-map.c.template>
#define DPA__U_SM_KIND DPA__U_SM_KIND_SET
#include <dpa/utils/_set-and-map.generator>

#define DPA__U_SM_TEMPLATE <dpa/utils/set-and-map.c.template>
#define DPA__U_SM_KIND DPA__U_SM_KIND_MAP
#include <dpa/utils/_set-and-map.generator>
