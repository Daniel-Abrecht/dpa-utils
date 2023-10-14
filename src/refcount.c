#include <dpa/utils/refcount.h>

extern enum dpa_u_refcount_type dpa_u_refcount_get_type(const struct dpa_u_refcount*const rc);
extern void dpa_u_refcount_increment_p(const struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_decrement(const struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_put_p(const struct dpa_u_refcount_freeable*const rc);
extern bool dpa_u_refcount_is_last(const struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_is_zero(const struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_is_static(const struct dpa_u_refcount* rc);
extern bool dpa_u_refcount_is_freeable(const struct dpa_u_refcount* rc);
extern bool dpa_u_refcount_has_callback(const struct dpa_u_refcount* rc);
extern bool dpa_u_refcount_is_bo_unique(const struct dpa_u_refcount* rc);
extern void dpa__u_refcount_destroy(struct dpa_u_refcount_freeable*const rc);

struct dpa_u_refcount dpa_u_refcount_v_static = dpa_u_refcount_i_static;
struct dpa_u_refcount_freeable dpa_u_refcount_static_v_freeable = dpa_u_refcount_i_static;
struct dpa_u_refcount_callback dpa_u_refcount_static_v_callback = dpa_u_refcount_i_static;

const char*const dpa_u_refcount_type_s[] = { DPA_U_ENUM_STR(dpa_u_refcount_type_list) };
