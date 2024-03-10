#include <dpa/utils/set.h>
#include <dpa/utils/map.h>

#define DPA__U_SM_BITMAP_OFFSET(INDEX) ((INDEX)/(sizeof(dpa_u_giant_unsigned_int_t)*CHAR_BIT))
#define DPA__U_SM_BITMAP_BIT(INDEX) (((dpa_u_giant_unsigned_int_t)1)<<((INDEX)%(sizeof(dpa_u_giant_unsigned_int_t)*CHAR_BIT)))

struct lookup_result {
  size_t index;
  bool found;
};

#define DPA__U_SM_TEMPLATE <dpa/utils/set-and-map.c.template>
#define DPA__U_SM_KIND DPA__U_SM_KIND_SET
#include <dpa/utils/_set-and-map.generator>

#define DPA__U_SM_TEMPLATE <dpa/utils/set-and-map.c.template>
#define DPA__U_SM_KIND DPA__U_SM_KIND_MAP
#include <dpa/utils/_set-and-map.generator>
