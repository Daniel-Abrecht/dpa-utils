#ifndef DPA_U_UTF8_H
#define DPA_U_UTF8_H

#include <dpa/utils/common.h>
#include <stdint.h>

#define dpa_u_utf8_from_code_point(X) dpa_u_utf8_from_code_point_p((char[8]){0},(X))
dpa__u_api inline unsigned char* dpa_u_utf8_from_code_point_p(unsigned char mem[8], uint32_t codepoint){
  if(codepoint < 0x80u){
    mem[0] = codepoint;
    mem[1] = 0;
  }else if(codepoint < 0x800u){
    mem[0] = 0xC0 | (codepoint >> 6);
    mem[1] = 0x80 | (codepoint & 0x3F);
    mem[2] = 0;
  }else if(codepoint < 0x10000u){
    mem[0] = 0xE0 | ( codepoint >> 12);
    mem[1] = 0x80 | ((codepoint >> 6 ) & 0x3F);
    mem[2] = 0x80 | ( codepoint        & 0x3F);
    mem[3] = 0;
  }else if(codepoint < 0x200000u){
    mem[0] = 0xF0 | ( codepoint >> 18);
    mem[1] = 0x80 | ((codepoint >> 12) & 0x3F);
    mem[2] = 0x80 | ((codepoint >> 6 ) & 0x3F);
    mem[3] = 0x80 | ( codepoint        & 0x3F);
    mem[4] = 0;
  }else if(codepoint < 0x4000000u){
    mem[0] = 0xF8 | ( codepoint >> 24);
    mem[1] = 0x80 | ((codepoint >> 18) & 0x3F);
    mem[2] = 0x80 | ((codepoint >> 12) & 0x3F);
    mem[3] = 0x80 | ((codepoint >> 6 ) & 0x3F);
    mem[4] = 0x80 | ( codepoint        & 0x3F);
    mem[5] = 0;
  }else if(codepoint < 0x80000000u){
    mem[0] = 0xFC | ( codepoint >> 30);
    mem[1] = 0x80 | ((codepoint >> 24) & 0x3F);
    mem[2] = 0x80 | ((codepoint >> 18) & 0x3F);
    mem[3] = 0x80 | ((codepoint >> 12) & 0x3F);
    mem[4] = 0x80 | ((codepoint >> 6 ) & 0x3F);
    mem[5] = 0x80 | ( codepoint        & 0x3F);
    mem[6] = 0;
  }else{ // codepoint < 0x1000000000u
    mem[0] = 0xFE;
    mem[1] = 0x80 | ( codepoint >> 30);
    mem[2] = 0x80 | ((codepoint >> 24) & 0x3F);
    mem[3] = 0x80 | ((codepoint >> 18) & 0x3F);
    mem[4] = 0x80 | ((codepoint >> 12) & 0x3F);
    mem[5] = 0x80 | ((codepoint >> 6 ) & 0x3F);
    mem[6] = 0x80 | ( codepoint        & 0x3F);
    mem[7] = 0;
  }
  return mem;
}

#endif
