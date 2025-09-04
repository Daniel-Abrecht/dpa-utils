#include <dpa/utils/test.h>
#include <dpa/utils/utf8.h>
#include <dpa/utils/unicode.h>
#include <inttypes.h>

DPA_U_TEST_MAIN


struct dpa_u_utf8_test_data {
  dpa_u_bo_t sequence;
  uint32_t codepoint;
  const char* str;
  int length;
};

#define SBO(X) \
  .sequence = { \
    .size = sizeof(X)-1, \
    .data = X \
  }, \
  .str = #X

bool generate_overlong_codepoint(int length, unsigned char result[length], uint32_t v){
  if(length < 1 || length > 7)
    return false;
  uint32_t smallest_valid_codepoint = (uint32_t)1<<(1+5*(length-1));
  if(length == 1) // Technicaly a continuation byte
    smallest_valid_codepoint = 0x40; // All covered by ascii range
  if(length == 2)
    smallest_valid_codepoint = 0x80; // All covered by ascii range
  if(v >= smallest_valid_codepoint)
    return false;
  for(int i=length; i--; v>>=6)
    result[i] = 0x80 | (v & 0x3F);
  result[0] |= 0xFF00>>length;
  return true;
}

int utf8_validate_strict(size_t length, const unsigned char* data){
  struct dpa_u_streaming_utf8_validator v = {0};
  for(size_t i=0; i<length; i++)
    if(!dpa_u_utf8_validate(&v, data[i]))
      return false;
  if(!dpa_u_utf8_validate(&v, EOF))
    return false;
  return true;
}

static const struct dpa_u_utf8_test_data edgecases[] = {

  /************************************************************
    **   Sequences treated as valid when encoding / decoding  **
    ************************************************************/

  { SBO(""                                ), .codepoint =         -1, .length = 0 },

  { SBO("\x00"                            ), .codepoint = 0x00000000, .length = 1 },
  { SBO("\x01"                            ), .codepoint = 0x00000001, .length = 1 },
  { SBO("\x7F"                            ), .codepoint = 0x0000007F, .length = 1 },
  { SBO("\xC2\x80"                        ), .codepoint = 0x00000080, .length = 2 },
  { SBO("\xDF\xBF"                        ), .codepoint = 0x000007FF, .length = 2 },
  { SBO("\xE0\xA0\x80"                    ), .codepoint = 0x00000800, .length = 3 },
  { SBO("\xEF\xBF\xBF"                    ), .codepoint = 0x0000FFFF, .length = 3 },
  { SBO("\xF0\x90\x80\x80"                ), .codepoint = 0x00010000, .length = 4 },
  /* 7 byte sequences have never been defined for unicode. This is an extension. */
  { SBO("\xF7\xBF\xBF\xBF"                ), .codepoint = 0x001FFFFF, .length = 4 },
  { SBO("\xF8\x88\x80\x80\x80"            ), .codepoint = 0x00200000, .length = 5 },
  { SBO("\xFB\xBF\xBF\xBF\xBF"            ), .codepoint = 0x03FFFFFF, .length = 5 },
  { SBO("\xFC\x84\x80\x80\x80\x80"        ), .codepoint = 0x04000000, .length = 6 },
  { SBO("\xFD\xBF\xBF\xBF\xBF\xBF"        ), .codepoint = 0x7FFFFFFF, .length = 6 },
  { SBO("\xFE\x82\x80\x80\x80\x80\x80"    ), .codepoint = 0x80000000, .length = 7 },
  /* 7 byte sequences have never been defined for unicode. This is an extension. */
  { SBO("\xFE\x83\xBF\xBF\xBF\xBF\xBE"    ), .codepoint = 0xFFFFFFFE, .length = 7 },
  { SBO("\xFE\x83\xBF\xBF\xBF\xBF\xBF"    ), .codepoint = 0xFFFFFFFF, .length = 7 },

  /* Same as above, but with a continuation byte following */
  { SBO("\x00\x80"                        ), .codepoint = 0x00000000, .length = 1 },
  { SBO("\x01\x80"                        ), .codepoint = 0x00000001, .length = 1 },
  { SBO("\x7F\x80"                        ), .codepoint = 0x0000007F, .length = 1 },
  { SBO("\xC2\x80\x80"                    ), .codepoint = 0x00000080, .length = 2 },
  { SBO("\xDF\xBF\x80"                    ), .codepoint = 0x000007FF, .length = 2 },
  { SBO("\xE0\xA0\x80\x80"                ), .codepoint = 0x00000800, .length = 3 },
  { SBO("\xEF\xBF\xBF\x80"                ), .codepoint = 0x0000FFFF, .length = 3 },
  { SBO("\xF0\x90\x80\x80\x80"            ), .codepoint = 0x00010000, .length = 4 },
  /* 7 byte sequences have never been defined for unicode. This is an extension. */
  { SBO("\xF7\xBF\xBF\xBF\x80"            ), .codepoint = 0x001FFFFF, .length = 4 },
  { SBO("\xF8\x88\x80\x80\x80\x80"        ), .codepoint = 0x00200000, .length = 5 },
  { SBO("\xFB\xBF\xBF\xBF\xBF\x80"        ), .codepoint = 0x03FFFFFF, .length = 5 },
  { SBO("\xFC\x84\x80\x80\x80\x80\x80"    ), .codepoint = 0x04000000, .length = 6 },
  { SBO("\xFD\xBF\xBF\xBF\xBF\xBF\x80"    ), .codepoint = 0x7FFFFFFF, .length = 6 },
  { SBO("\xFE\x82\x80\x80\x80\x80\x80\x80"), .codepoint = 0x80000000, .length = 7 },
  /* 7 byte sequences have never been defined for unicode. This is an extension. */
  { SBO("\xFE\x83\xBF\xBF\xBF\xBF\xBE\x80"), .codepoint = 0xFFFFFFFE, .length = 7 },
  { SBO("\xFE\x83\xBF\xBF\xBF\xBF\xBF\x80"), .codepoint = 0xFFFFFFFF, .length = 7 },

  /* Same as above, but with a null byte following */
  { SBO("\x00\x00"                        ), .codepoint = 0x00000000, .length = 1 },
  { SBO("\x01\x00"                        ), .codepoint = 0x00000001, .length = 1 },
  { SBO("\x7F\x00"                        ), .codepoint = 0x0000007F, .length = 1 },
  { SBO("\xC2\x80\x00"                    ), .codepoint = 0x00000080, .length = 2 },
  { SBO("\xDF\xBF\x00"                    ), .codepoint = 0x000007FF, .length = 2 },
  { SBO("\xE0\xA0\x80\x00"                ), .codepoint = 0x00000800, .length = 3 },
  { SBO("\xEF\xBF\xBF\x00"                ), .codepoint = 0x0000FFFF, .length = 3 },
  { SBO("\xF0\x90\x80\x80\x00"            ), .codepoint = 0x00010000, .length = 4 },
  /* 7 byte sequences have never been defined for unicode. This is an extension. */
  { SBO("\xF7\xBF\xBF\xBF\x00"            ), .codepoint = 0x001FFFFF, .length = 4 },
  { SBO("\xF8\x88\x80\x80\x80\x00"        ), .codepoint = 0x00200000, .length = 5 },
  { SBO("\xFB\xBF\xBF\xBF\xBF\x00"        ), .codepoint = 0x03FFFFFF, .length = 5 },
  { SBO("\xFC\x84\x80\x80\x80\x80\x00"    ), .codepoint = 0x04000000, .length = 6 },
  { SBO("\xFD\xBF\xBF\xBF\xBF\xBF\x00"    ), .codepoint = 0x7FFFFFFF, .length = 6 },
  { SBO("\xFE\x82\x80\x80\x80\x80\x80\x00"), .codepoint = 0x80000000, .length = 7 },
  /* 7 byte sequences have never been defined for unicode. This is an extension. */
  { SBO("\xFE\x83\xBF\xBF\xBF\xBF\xBE\x00"), .codepoint = 0xFFFFFFFE, .length = 7 },
  { SBO("\xFE\x83\xBF\xBF\xBF\xBF\xBF\x00"), .codepoint = 0xFFFFFFFF, .length = 7 },

  /* Same as above, but with another 2 byte sequence following  */
  { SBO("\x00\xC2\x80"                        ), .codepoint = 0x00000000, .length = 1 },
  { SBO("\x01\xC2\x80"                        ), .codepoint = 0x00000001, .length = 1 },
  { SBO("\x7F\xC2\x80"                        ), .codepoint = 0x0000007F, .length = 1 },
  { SBO("\xC2\x80\xC2\x80"                    ), .codepoint = 0x00000080, .length = 2 },
  { SBO("\xDF\xBF\xC2\x80"                    ), .codepoint = 0x000007FF, .length = 2 },
  { SBO("\xE0\xA0\x80\xC2\x80"                ), .codepoint = 0x00000800, .length = 3 },
  { SBO("\xEF\xBF\xBF\xC2\x80"                ), .codepoint = 0x0000FFFF, .length = 3 },
  { SBO("\xF0\x90\x80\x80\xC2\x80"            ), .codepoint = 0x00010000, .length = 4 },
  /* 7 byte sequences have never been defined for unicode. This is an extension. */
  { SBO("\xF7\xBF\xBF\xBF\xC2\x80"            ), .codepoint = 0x001FFFFF, .length = 4 },
  { SBO("\xF8\x88\x80\x80\x80\xC2\x80"        ), .codepoint = 0x00200000, .length = 5 },
  { SBO("\xFB\xBF\xBF\xBF\xBF\xC2\x80"        ), .codepoint = 0x03FFFFFF, .length = 5 },
  { SBO("\xFC\x84\x80\x80\x80\x80\xC2\x80"    ), .codepoint = 0x04000000, .length = 6 },
  { SBO("\xFD\xBF\xBF\xBF\xBF\xBF\xC2\x80"    ), .codepoint = 0x7FFFFFFF, .length = 6 },
  { SBO("\xFE\x82\x80\x80\x80\x80\x80\xC2\x80"), .codepoint = 0x80000000, .length = 7 },
  /* 7 byte sequences have never been defined for unicode. This is an extension. */
  { SBO("\xFE\x83\xBF\xBF\xBF\xBF\xBE\xC2\x80"), .codepoint = 0xFFFFFFFE, .length = 7 },
  { SBO("\xFE\x83\xBF\xBF\xBF\xBF\xBF\xC2\x80"), .codepoint = 0xFFFFFFFF, .length = 7 },

  /***************************
    **   Invalid sequences   **
    ***************************/

  { SBO("\xC0\x80"                        ), .codepoint = -1, .length = 2 }, // Overlong sequence for U+00000000
  { SBO("\xC1\xBF"                        ), .codepoint = -1, .length = 2 }, // Overlong sequence for U+0000007F
  { SBO("\xE0\x9F\xBF"                    ), .codepoint = -1, .length = 3 }, // Overlong sequence for U+000007FF
  { SBO("\xF0\x8F\xBF\xBF"                ), .codepoint = -1, .length = 4 }, // Overlong sequence for U+0000FFFF
  { SBO("\xF8\x87\xBF\xBF\xBF"            ), .codepoint = -1, .length = 5 }, // Overlong sequence for U+001FFFFF
  { SBO("\xFC\x83\xBF\xBF\xBF\xBF"        ), .codepoint = -1, .length = 6 }, // Overlong sequence for U+03FFFFFF
  { SBO("\xFE\x81\xBF\xBF\xBF\xBF\xBF"    ), .codepoint = -1, .length = 7 }, // Overlong sequence for U+7FFFFFFF
  { SBO("\xFE\x84\x80\x80\x80\x80\x80"    ), .codepoint = -1, .length = 7 }, // > U+FFFFFFFF 
  { SBO("\xFF\xBF\xBF\xBF\xBF\xBF\xBF\xBF"), .codepoint = -1, .length = 8 }, // 8 byte sequence

  { SBO("\x80"), .codepoint = -1, .length = 1 }, // smallest continuation byte
  { SBO("\xBF"), .codepoint = -1, .length = 1 }, // biggest continuation byte
  { SBO("\x99\xae\x81\xb4\x99\xa2\x90\x85\xa0\x89\xaf\x88\x98\xa2\x90\x98\xad\x82\xbd\xb4"), .codepoint = -1, .length = 20 }, // 20 random continuation bytes


  /* Same as above, but with a continuation byte following */
  { SBO("\xC0\x80\x80"                        ), .codepoint = -1, .length = 3 }, // Overlong sequence for U+00000000
  { SBO("\xC1\xBF\x80"                        ), .codepoint = -1, .length = 3 }, // Overlong sequence for U+0000007F
  { SBO("\xE0\x9F\xBF\x80"                    ), .codepoint = -1, .length = 4 }, // Overlong sequence for U+000007FF
  { SBO("\xF0\x8F\xBF\xBF\x80"                ), .codepoint = -1, .length = 5 }, // Overlong sequence for U+0000FFFF
  { SBO("\xF8\x87\xBF\xBF\xBF\x80"            ), .codepoint = -1, .length = 6 }, // Overlong sequence for U+001FFFFF
  { SBO("\xFC\x83\xBF\xBF\xBF\xBF\x80"        ), .codepoint = -1, .length = 7 }, // Overlong sequence for U+03FFFFFF
  { SBO("\xFE\x81\xBF\xBF\xBF\xBF\xBF\x80"    ), .codepoint = -1, .length = 8 }, // Overlong sequence for U+7FFFFFFF
  { SBO("\xFE\x84\x80\x80\x80\x80\x80\x80"    ), .codepoint = -1, .length = 8 }, // > U+FFFFFFFF 
  { SBO("\xFF\xBF\xBF\xBF\xBF\xBF\xBF\xBF\x80"), .codepoint = -1, .length = 9 }, // 8 byte sequence

  /* Same as above, but with a null byte following */
  { SBO("\xC0\x80\x00"                        ), .codepoint = -1, .length = 2 }, // Overlong sequence for U+00000000
  { SBO("\xC1\xBF\x00"                        ), .codepoint = -1, .length = 2 }, // Overlong sequence for U+0000007F
  { SBO("\xE0\x9F\xBF\x00"                    ), .codepoint = -1, .length = 3 }, // Overlong sequence for U+000007FF
  { SBO("\xF0\x8F\xBF\xBF\x00"                ), .codepoint = -1, .length = 4 }, // Overlong sequence for U+0000FFFF
  { SBO("\xF8\x87\xBF\xBF\xBF\x00"            ), .codepoint = -1, .length = 5 }, // Overlong sequence for U+001FFFFF
  { SBO("\xFC\x83\xBF\xBF\xBF\xBF\x00"        ), .codepoint = -1, .length = 6 }, // Overlong sequence for U+03FFFFFF
  { SBO("\xFE\x81\xBF\xBF\xBF\xBF\xBF\x00"    ), .codepoint = -1, .length = 7 }, // Overlong sequence for U+7FFFFFFF
  { SBO("\xFE\x84\x80\x80\x80\x80\x80\x00"    ), .codepoint = -1, .length = 7 }, // > U+FFFFFFFF 
  { SBO("\xFF\xBF\xBF\xBF\xBF\xBF\xBF\xBF\x00"), .codepoint = -1, .length = 8 }, // 8 byte sequence

  /* Same as above, but with another 2 byte sequence following  */
  { SBO("\xC0\x80\xC2\x80"                        ), .codepoint = -1, .length = 2 }, // Overlong sequence for U+00000000
  { SBO("\xC1\xBF\xC2\x80"                        ), .codepoint = -1, .length = 2 }, // Overlong sequence for U+0000007F
  { SBO("\xE0\x9F\xBF\xC2\x80"                    ), .codepoint = -1, .length = 3 }, // Overlong sequence for U+000007FF
  { SBO("\xF0\x8F\xBF\xBF\xC2\x80"                ), .codepoint = -1, .length = 4 }, // Overlong sequence for U+0000FFFF
  { SBO("\xF8\x87\xBF\xBF\xBF\xC2\x80"            ), .codepoint = -1, .length = 5 }, // Overlong sequence for U+001FFFFF
  { SBO("\xFC\x83\xBF\xBF\xBF\xBF\xC2\x80"        ), .codepoint = -1, .length = 6 }, // Overlong sequence for U+03FFFFFF
  { SBO("\xFE\x81\xBF\xBF\xBF\xBF\xBF\xC2\x80"    ), .codepoint = -1, .length = 7 }, // Overlong sequence for U+7FFFFFFF
  { SBO("\xFE\x84\x80\x80\x80\x80\x80\xC2\x80"    ), .codepoint = -1, .length = 7 }, // > U+FFFFFFFF 
  { SBO("\xFF\xBF\xBF\xBF\xBF\xBF\xBF\xBF\xC2\x80"), .codepoint = -1, .length = 8 }, // 8 byte sequence

};

DPA_U_TESTCASE("dpa_u_next_codepoint\tCheck edge cases"){
  bool all_ok = true;
  for(size_t i=0; i<sizeof(edgecases)/sizeof(*edgecases); i++){
    const unsigned char* it = edgecases[i].sequence.data;
    uint32_t result = dpa_u_next_codepoint(&it, (unsigned char*)edgecases[i].sequence.data + edgecases[i].sequence.size);
    if(result != edgecases[i].codepoint || (int)(it-(const unsigned char*)edgecases[i].sequence.data) != edgecases[i].length){
      fprintf(
        stderr,
        "dpa_u_next_codepoint: test for sequence %zu failed: sequence: %s, bytes in first sequence: %d, bytes processed: %d, expected result: %08"PRIX32" result: %08"PRIX32"\n",
        i, edgecases[i].str, edgecases[i].length, (int)(it-(const unsigned char*)edgecases[i].sequence.data), edgecases[i].codepoint, result
      );
      all_ok = false;
    }
  }
  return !all_ok;
}

DPA_U_TESTCASE("dpa_u_next_codepoint\tVerify all possible overlong sequences are handled properly"){
  unsigned char overlong_sequence[9];
  for(int length=1; length<=7; length++)
  for(uint32_t codepoint=0; ; codepoint++){
    if(!generate_overlong_codepoint(length, overlong_sequence, codepoint))
      break;
    {
      const unsigned char* it = overlong_sequence;
      uint32_t result = dpa_u_next_codepoint(&it, overlong_sequence+length);
      if(result != 0xFFFFFFFF || it != overlong_sequence+length){
        fprintf(stderr, "dpa_u_next_codepoint: 1: Overlong sequence of length %d codepoint %08"PRIX32" was not handled properly\n", length, codepoint);
        fprintf(stderr, "%08"PRIX32" %d %02X%02X%02X%02X\n", result, (int)(it-overlong_sequence), overlong_sequence[0], overlong_sequence[1], overlong_sequence[2], overlong_sequence[3]);
        return 1;
      }
    }
    {
      overlong_sequence[length] = 0x00;
      const unsigned char* it = overlong_sequence;
      uint32_t result = dpa_u_next_codepoint(&it, overlong_sequence+length+1);
      if(result != 0xFFFFFFFF || it != overlong_sequence+length){
        fprintf(stderr, "dpa_u_next_codepoint: 2: Overlong sequence of length %d codepoint %08"PRIX32" was not handled properly\n", length, codepoint);
        fprintf(stderr, "%08"PRIX32" %d %02X%02X%02X%02X\n", result, (int)(it-overlong_sequence), overlong_sequence[0], overlong_sequence[1], overlong_sequence[2], overlong_sequence[3]);
        return 1;
      }
    }
    {
      overlong_sequence[length] = 0x80;
      const unsigned char* it = overlong_sequence;
      uint32_t result = dpa_u_next_codepoint(&it, overlong_sequence+length+1);
      if(result != 0xFFFFFFFF || it != overlong_sequence+length+1){
        fprintf(stderr, "dpa_u_next_codepoint: 3: Overlong sequence of length %d codepoint %08"PRIX32" was not handled properly\n", length, codepoint);
        fprintf(stderr, "%08"PRIX32" %d %02X%02X%02X%02X\n", result, (int)(it-overlong_sequence), overlong_sequence[0], overlong_sequence[1], overlong_sequence[2], overlong_sequence[3]);
        return 1;
      }
    }
    {
      overlong_sequence[length] = 0xC2;
      overlong_sequence[length+1] = 0x80;
      const unsigned char* it = overlong_sequence;
      uint32_t result = dpa_u_next_codepoint(&it, overlong_sequence+length+2);
      if(result != 0xFFFFFFFF || it != overlong_sequence+length){
        fprintf(stderr, "dpa_u_next_codepoint: 4: Overlong sequence of length %d codepoint %08"PRIX32" was not handled properly\n", length, codepoint);
        fprintf(stderr, "%08"PRIX32" %d %02X%02X%02X%02X\n", result, (int)(it-overlong_sequence), overlong_sequence[0], overlong_sequence[1], overlong_sequence[2], overlong_sequence[3]);
        return 1;
      }
    }
  }
  return 0;
}
