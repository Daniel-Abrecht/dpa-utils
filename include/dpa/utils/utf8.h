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
#define dpa_u_utf8_cstr_from_codepoint(X) dpa_u_utf8_cstr_from_codepoint_p((unsigned char[8]){0},(X))

/**
 * Turns a unicode code point into an UTF-8 sequence.
 * In practice, there should never be a sequence longer than 4 bytes / no code points >= U+200000,
 * bt this function will convert any value anyway, including U+FFFFFFFF
 * 
 * This function does not care if a codepoint is actually allowed to appear in UTF-8,
 * it will encode code points such as U+D800.
 * 
 * \param mem The UTF-8 sequence will be written there. Must be at least 8 bytes big
 * \param codepoint The unicode code point
 * \see dpa_u_utf8_from_codepoint
 */
dpa__u_api inline unsigned char* dpa_u_utf8_cstr_from_codepoint_p(unsigned char mem[8], uint32_t codepoint){
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
 * but this function will convert any value anyway, including U+FFFFFFFF.
 * 
 * This function does not care if a codepoint is actually allowed to appear in UTF-8,
 * it will encode code points such as U+D800.
 * 
 * Use \ref dpa_u_is_codepoint_valid if you want to check if a codepoint is valid.
 * 
 * \param codepoint a unicode codepoint
 * \returns The UTF-8 sequence, as an inline unique BO
 */
dpa_u_unsequenced
dpa__u_api inline dpa_u_a_bo_unique_t dpa_u_utf8_from_codepoint(uint32_t codepoint){
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
 * This function validates if a sequence of bytes is valid UTF-8.
 *
 * Please note that some codepoints, such as U+D800 mustn't appearin valid UTF-8, even if they are otherwise correctly
 * encoded. Unlike most other functions in this library, this function will treat those codepoints as invalid.
 * 
 * \param v The validator state
 * \param ch The next character or EOF if the sequence is complete
 * \returns true if everything is OK, false if the sequence wasn't valid.
 */
dpa__u_api bool dpa_u_utf8_validate(struct dpa_u_streaming_utf8_validator*restrict const v, const int ch);
dpa__u_api bool dpa_u_utf8_validate_ext(struct dpa_u_streaming_utf8_validator*restrict const v, const int ch);
dpa__u_api bool dpa_u_utf8_validate_only_unicode(struct dpa_u_streaming_utf8_validator*restrict const v, const int ch);
dpa__u_api bool dpa_u_utf8_validate_only_unicode_no_noncharacters(struct dpa_u_streaming_utf8_validator*restrict const v, const int ch);
dpa__u_api bool dpa_u_utf8_validate_no_noncharacters(struct dpa_u_streaming_utf8_validator*restrict const v, const int ch);
dpa__u_api bool dpa_u_utf8_validate_ext_no_noncharacters(struct dpa_u_streaming_utf8_validator*restrict const v, const int ch);

/**
 * This function can be used to iterate over an UTF-8 string codepoint-by-codepoint. It returns one codepoint every
 * time it's called. In case some data is invalid, a codepoint is invalid, a codepoint is too big to be stored in
 * a 32bit integer, or *it >= end, -1 is returned.
 * 
 * The parameter \ref it points to a pointer to the start of the UTF-8 data to process. This pointer will be incremented
 * to point to the next codepoint, or the end of the data. The parameter \ref end must point to the end of the utf-8 data.
 * 
 * So long as there is data left, this function is guaranteed to make progress, that is, it will eventually consume the
 * entire of the input data if called repetedly, even if the input contains data which is not valid in UTF-8.
 * 
 * UTF-8 sequences, and invalid sequences are dealt with as follows:  
 *  * Any byte NOT starting with 0b10XXXXXX is always considered the start of a new codepoint.  
 *  * A byte in the ascii range is always a valid & complete code point, no matter what came before. The following bytes are part of a new codepoint.  
 *  * After the start of a sequence longer than one byte, all following bytes starting with 0b10XXXXXX are considered part of tha same sequence,
 *    but if the sequence is valid, only at most as many bytes as indicated in the first byte of the sequence.
 *    For example, `C3 84 80` is the sequences `C3 84` and `80`, but `C0 A1 80` is considered a single invalid sequence.
 *  * Some codepoints such as U+D800 are technically considered invalid in UTF-8. However, if it's not an overlong sequence or otherwise
 *    wrongly encoded, those codepoints will still be returned by this function, and are not considered invalid by it.
 *    This differs from \ref dpa_u_utf8_validate, but is not going to change.
 */
dpa__u_api uint32_t dpa_u_next_codepoint(const unsigned char** it, const unsigned char* end);

/** @} */
/** @} */

#endif
