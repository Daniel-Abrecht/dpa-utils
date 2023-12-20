#include <dpa/utils/refcount.h>

dpa__u_api struct dpa_u_refcount dpa_u_refcount_v_static = dpa_u_refcount_i_static;
dpa__u_api struct dpa_u_refcount_freeable dpa_u_refcount_static_v_freeable = dpa_u_refcount_i_static;
dpa__u_api struct dpa_u_refcount_callback dpa_u_refcount_static_v_callback = dpa_u_refcount_i_static;

DPA_U_ENUM_DEF(dpa_u_refcount_type)
