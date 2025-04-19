#ifndef DPA_U_SET_INT_H
#define DPA_U_SET_INT_H

#include <dpa/utils/common.h>

#define DPA__U_SM_TEMPLATE <dpa/utils/_set-and-map.h.template>
#define DPA__U_SM_KIND DPA__U_SM_KIND_SET
#include <dpa/utils/_set-and-map.generator>
#undef DPA__U_SM_KIND

#endif
