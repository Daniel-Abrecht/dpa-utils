#include <dpa/utils/utf8.h>
#include <dpa/utils/io.h>
#include <stdio.h>

int main(void){
  dpa_u_puts(dpa_u_utf8_from_code_point(0x41)); // U+0041 "A" "\x41"
  dpa_u_puts(dpa_u_utf8_from_code_point(0xC4)); // U+00C4 "Ä" "\xC3\x84"
  dpa_u_puts(dpa_u_utf8_from_code_point(0x2603)); // U+2603 "☃" "0xE2\x98\x83"
  dpa_u_puts(dpa_u_utf8_from_code_point(0x1F63A)); // U+1F63A "😺" "\xF0\x9F\x98\xBA"
}
