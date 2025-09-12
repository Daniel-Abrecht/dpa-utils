#define DPA__U_GEN_EXPORTS
#include <dpa/utils/unicode.h>

extern bool dpa_u_unicode_is_invalid(dpa_u_unicode_codepoint_t codepoint_);
extern bool dpa_u_unicode_is_noncharacter(dpa_u_unicode_codepoint_t codepoint);
extern bool dpa_u_unicode_is_surrogate(dpa_u_unicode_codepoint_t codepoint);
extern enum dpa_u_unicode_category dpa_u_unicode_get_category(dpa_u_unicode_codepoint_t codepoint);
extern struct dpa_u_unicode_info dpa_u_get_codepoint_info(dpa_u_unicode_codepoint_t codepoint);
