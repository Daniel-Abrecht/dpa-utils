#include <dpa/utils/utf8.h>

extern dpa_u_a_bo_unique_t dpa_u_utf8_from_code_point(uint32_t codepoint);
extern unsigned char* dpa_u_utf8_cstr_from_code_point_p(unsigned char mem[8], uint32_t codepoint);
