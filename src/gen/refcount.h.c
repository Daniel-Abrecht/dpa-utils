#define DPA__U_GEN_EXPORTS
#include <dpa/utils/refcount.h>

extern bool dpa_u_refcount_decrement_p(const struct dpa_u_refcount*const _rc);
extern bool dpa_u_refcount_has_callback_p(const struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_is_bo_unique_p(const struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_is_last_p(const struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_is_static_p(const struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_is_zero_p(const struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_put_p(const struct dpa_u_refcount_freeable*const _rc);
extern enum dpa_u_refcount_type dpa_u_refcount_get_type_p(const struct dpa_u_refcount*const rc);
extern void dpa__u_refcount_destroy(struct dpa_u_refcount_freeable*const rc);
extern void dpa_u_refcount_increment_p(const struct dpa_u_refcount*const _rc);
