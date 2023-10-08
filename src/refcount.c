#include <dpa/utils/refcount.h>

extern enum dpa_u_refcount_type dpa_u_refcount_get_type(const struct dpa_u_refcount*const rc);
extern void dpa_u_refcount_increment_p(struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_decrement(struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_put_p(struct dpa_u_refcount_freeable*const rc);
extern bool dpa_u_refcount_is_last(const struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_is_zero(const struct dpa_u_refcount*const rc);
extern bool dpa_u_refcount_is_static(struct dpa_u_refcount* rc);
extern bool dpa_u_refcount_is_freeable(struct dpa_u_refcount* rc);
extern bool dpa_u_refcount_has_callback(struct dpa_u_refcount* rc);
extern bool dpa_u_refcount_is_bo_unique(struct dpa_u_refcount* rc);
