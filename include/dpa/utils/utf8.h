#ifndef DPA_U_UTF8_H
#define DPA_U_UTF8_H

#include <dpa/utils/common.h>
#include <dpa/utils/bo.h>
#include <stdint.h>

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-utf8 UTF-8 Utils
 * @{
 * Utilities for working with UTF-8 data.
 */

/**
 * Turns a unicode code point into an UTF-8 sequence.
 * In practice, there should never be a sequence longer than 4 bytes / no code points >= U+200000,
 * bt this function will convert any value anyway, including U+FFFFFFFF
 * 
 * \param X A unicode code point
 * \returns The corresponding UTF-8 sequence, 0 terminated. Up to 8 bytes long. Beware of codepoint 0, which is a 0 byte in UTF-8.
 */
#define dpa_u_utf8_cstr_from_code_point(X) dpa_u_utf8_cstr_from_code_point_p((char[8]){0},(X))

/**
 * Turns a unicode code point into an UTF-8 sequence.
 * In practice, there should never be a sequence longer than 4 bytes / no code points >= U+200000,
 * bt this function will convert any value anyway, including U+FFFFFFFF
 * 
 * \param mem The UTF-8 sequence will be written there. Must be at least 8 bytes big
 * \param codepoint The unicode code point
 * \see dpa_u_utf8_from_code_point
 */
dpa__u_api inline unsigned char* dpa_u_utf8_cstr_from_code_point_p(unsigned char mem[8], uint32_t codepoint){
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

/**
 * Converts a unicode code point to an UTF-8 inline unique BO.
 * In practice, there should never be a sequence longer than 4 bytes / no code points >= U+200000,
 * bt this function will convert any value anyway, including U+FFFFFFFF
 * 
 * \param codepoint a unicode codepoint
 * \returns The UTF-8 sequence, as an inline unique BO
 */
dpa_u_unsequenced
dpa__u_api inline dpa_u_a_bo_unique_t dpa_u_utf8_from_code_point(uint32_t codepoint){
  if(codepoint < 0x80u){
    return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING((codepoint))|DPA_U_MOVE_TAG(DPA_U_BO_UNIQUE)}}};
  }else if(codepoint < 0x800u){
    return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING(
      (0xC0 | (codepoint >> 6)),
      (0x80 | (codepoint & 0x3F))
    )|DPA_U_MOVE_TAG(DPA_U_BO_UNIQUE)}}};
  }else if(codepoint < 0x10000u){
    return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING(
      (0xE0 | ( codepoint >> 12)),
      (0x80 | ((codepoint >> 6 ) & 0x3F)),
      (0x80 | ( codepoint        & 0x3F))
    )|DPA_U_MOVE_TAG(DPA_U_BO_UNIQUE)}}};
  }else if(codepoint < 0x200000u){
    return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING(
      (0xF0 | ( codepoint >> 18)),
      (0x80 | ((codepoint >> 12) & 0x3F)),
      (0x80 | ((codepoint >> 6 ) & 0x3F)),
      (0x80 | ( codepoint        & 0x3F))
    )|DPA_U_MOVE_TAG(DPA_U_BO_UNIQUE)}}};
  }else if(codepoint < 0x4000000u){
    return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING(
      (0xF8 | ( codepoint >> 24)),
      (0x80 | ((codepoint >> 18) & 0x3F)),
      (0x80 | ((codepoint >> 12) & 0x3F)),
      (0x80 | ((codepoint >> 6 ) & 0x3F)),
      (0x80 | ( codepoint        & 0x3F))
    )|DPA_U_MOVE_TAG(DPA_U_BO_UNIQUE)}}};
  }else if(codepoint < 0x80000000u){
    return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING(
      (0xFC | ( codepoint >> 30)),
      (0x80 | ((codepoint >> 24) & 0x3F)),
      (0x80 | ((codepoint >> 18) & 0x3F)),
      (0x80 | ((codepoint >> 12) & 0x3F)),
      (0x80 | ((codepoint >> 6 ) & 0x3F)),
      (0x80 | ( codepoint        & 0x3F))
    )|DPA_U_MOVE_TAG(DPA_U_BO_UNIQUE)}}};
  } // codepoint < 0x1000000000u
  return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING(
    (0xFE),
    (0x80 | ( codepoint >> 30)),
    (0x80 | ((codepoint >> 24) & 0x3F)),
    (0x80 | ((codepoint >> 18) & 0x3F)),
    (0x80 | ((codepoint >> 12) & 0x3F)),
    (0x80 | ((codepoint >> 6 ) & 0x3F)),
    (0x80 | ( codepoint        & 0x3F))
  )|DPA_U_MOVE_TAG(DPA_U_BO_UNIQUE)}}};
}

/**
 * This stores the current state for the \ref dpa_u_utf8_validate function.
 * To initialise or reset it, just make sure it's zeroed out.
 */
struct dpa_u_streaming_utf8_validator {
  uint_least8_t index : 3;
  uint_least8_t state : 4;
};

/**
 * For validating if a sequence of bytes is valid UTF-8.
 * \param v The validator state
 * \param ch The next character or EOF if the sequence is complete
 * \returns true if everything is OK, false if the sequence wasn't valid.
 */
dpa__u_api bool dpa_u_utf8_validate(struct dpa_u_streaming_utf8_validator*restrict const v, const int ch);
/** @} */

/** @} */
/** @} */

#endif
