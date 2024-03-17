#include <dpa/utils/set.h>
#include <dpa/utils/map.h>
#include <dpa/utils/math.h>

#define DPA__U_SM_BITMAP_OFFSET(INDEX) ((INDEX)/(sizeof(dpa_u_giant_unsigned_int_t)*CHAR_BIT))
#define DPA__U_SM_BITMAP_BIT(INDEX) (((dpa_u_giant_unsigned_int_t)1)<<((INDEX)%(sizeof(dpa_u_giant_unsigned_int_t)*CHAR_BIT)))

struct lookup_result {
  size_t index;
  bool found;
};

static size_t count_to_lbsize(size_t n){
  enum { MIN_SIZE = 32 };
  n += n / 8; // Ensure there is some free space left 100/8 = 12.5%
  return dpa_u_log2(n|(MIN_SIZE-1))+1;
}

#define DPA__U_SM_TEMPLATE <dpa/utils/set-and-map.c.template>
#define DPA__U_SM_KIND DPA__U_SM_KIND_SET
#include <dpa/utils/_set-and-map.generator>

#define DPA__U_SM_TEMPLATE <dpa/utils/set-and-map.c.template>
#define DPA__U_SM_KIND DPA__U_SM_KIND_MAP
#include <dpa/utils/_set-and-map.generator>
