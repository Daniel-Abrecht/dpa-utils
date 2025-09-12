#include <dpa/utils/unicode.h>
#include <dpa/utils/utf8.h>
#include <dpa/utils/io.h>
#include <stdio.h>
#include <inttypes.h>

#define S(X) .size=sizeof(X)-1, .data=(X)

int main(void){
  {
    puts("Printing some unicode characters using their codepoint number:");
    dpa_u_puts(dpa_u_utf8_from_codepoint(0x41)); // U+0041 "A" "\x41"
    dpa_u_puts(dpa_u_utf8_from_codepoint(0xC4)); // U+00C4 "Ä" "\xC3\x84"
    dpa_u_puts(dpa_u_utf8_from_codepoint(0x2603)); // U+2603 "☃" "0xE2\x98\x83"
    dpa_u_puts(dpa_u_utf8_from_codepoint(0x1F63A)); // U+1F63A "😺" "\xF0\x9F\x98\xBA"
  }

  {
    puts("Iterating over a utf-8 string codepoint-by-codepoint");
    dpa_u_bo_t bo = { S("A""\xC3\x84""\xE2\x98\x83""\xF0\x9F\x98\xBA"" ""👪""👩‍👩‍👧‍👧") };
    dpa_u_puts(bo);
    for(const unsigned char *it=bo.data, *const end=it+bo.size; it<end; ){
      const unsigned char*const start = it;
      dpa_u_unicode_codepoint_t codepoint = dpa_u_utf8_next_codepoint(&it, end);
      enum dpa_u_unicode_category category = dpa_u_unicode_get_category(codepoint);
      printf("  '%.*s'\tU+%08"PRIX32" %s\n", (int)(it-start), start, codepoint, dpa_u_enum_get_name(dpa_u_unicode_category, category));
    }
  }
}
