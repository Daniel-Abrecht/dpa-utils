#ifndef DPA_U_UNICODE_H
#define DPA_U_UNICODE_H

#include <dpa/utils/common.h>

#include <stdint.h>
#include <stdbool.h>

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */
/**
 * \addtogroup dpa-u-unicode Unicode
 * @{
 */

 /**
 * This is the biggest codepoint that's allowed in unicode.
 * No codepoint bigger than this will ever be defined (or so they say).
 * This is because larger codepoints can't be encoded in UTF-16.
 *
 * As far as this library is concerned, we pretend UTF-16 doesn't exist.
 * If they ever do obsolete utf16 and change this limit, just update this value.
 */
#define UNICODE_CODEPOINT_MAX 0x10FFFF

enum unicode_category_major {
  UC_MAJOR_OTHER       = 0<<3,
  UC_MAJOR_LETTER      = 1<<3,
  UC_MAJOR_MARK        = 2<<3,
  UC_MAJOR_NUMBER      = 3<<3,
  UC_MAJOR_PUNCTUATION = 4<<3,
  UC_MAJOR_SYMBOL      = 5<<3,
  UC_MAJOR_SEPERATOR   = 6<<3,
};

enum unicode_category_minor_other {
  UC_MINOR_OTHER_NOT_ASSIGNED,
  UC_MINOR_OTHER_CONTROL,
  UC_MINOR_OTHER_FORMAT,
  UC_MINOR_OTHER_SURROGATE,
  UC_MINOR_OTHER_PRIVATE_USE,
};

enum unicode_category_minor_letter {
  UC_MINOR_LETTER_UPPERCASE,
  UC_MINOR_LETTER_LOWERCASE,
  UC_MINOR_LETTER_TITLECASE,
  UC_MINOR_LETTER_MODIFIER,
  UC_MINOR_LETTER_OTHER,
};

enum unicode_category_minor_mark {
  UC_MINOR_MARK_NONSPACING,
  UC_MINOR_MARK_SPACING_COMBINING,
  UC_MINOR_MARK_ENCLOSING,
};

enum unicode_category_minor_number {
  UC_MINOR_NUMBER_DECIMAL_DIGIT,
  UC_MINOR_NUMBER_LETTER,
  UC_MINOR_NUMBER_OTHER,
};

enum unicode_category_minor_punctuation {
  UC_MINOR_PUNCTUATION_CONNECTOR,
  UC_MINOR_PUNCTUATION_DASH,
  UC_MINOR_PUNCTUATION_OPEN,
  UC_MINOR_PUNCTUATION_CLOSE,
  UC_MINOR_PUNCTUATION_INLINE_QUOTE,
  UC_MINOR_PUNCTUATION_FINAL_QUOTE,
  UC_MINOR_PUNCTUATION_OTHER,
};

enum unicode_category_minor_symbol {
  UC_MINOR_SYMBOL_MATH,
  UC_MINOR_SYMBOL_CURRENCY,
  UC_MINOR_SYMBOL_MODIFIER,
  UC_MINOR_SYMBOL_OTHER,
};

enum unicode_category_minor_seperator {
  UC_MINOR_SEPERATOR_SPACE,
  UC_MINOR_SEPERATOR_LINE,
  UC_MINOR_SEPERATOR_PARAGRAPH,
};

enum unicode_category {
  UC_OTHER_NOT_ASSIGNED = UC_MINOR_OTHER_NOT_ASSIGNED | UC_MAJOR_OTHER,
  UC_OTHER_CONTROL      = UC_MINOR_OTHER_CONTROL      | UC_MAJOR_OTHER,
  UC_OTHER_FORMAT       = UC_MINOR_OTHER_FORMAT       | UC_MAJOR_OTHER,
  UC_OTHER_SURROGATE    = UC_MINOR_OTHER_SURROGATE    | UC_MAJOR_OTHER,
  UC_OTHER_PRIVATE_USE  = UC_MINOR_OTHER_PRIVATE_USE  | UC_MAJOR_OTHER,

  UC_LETTER_UPPERCASE = UC_MINOR_LETTER_UPPERCASE | UC_MAJOR_LETTER,
  UC_LETTER_LOWERCASE = UC_MINOR_LETTER_LOWERCASE | UC_MAJOR_LETTER,
  UC_LETTER_TITLECASE = UC_MINOR_LETTER_TITLECASE | UC_MAJOR_LETTER,
  UC_LETTER_MODIFIER  = UC_MINOR_LETTER_MODIFIER  | UC_MAJOR_LETTER,
  UC_LETTER_OTHER     = UC_MINOR_LETTER_OTHER     | UC_MAJOR_LETTER,

  UC_MARK_NONSPACING        = UC_MINOR_MARK_NONSPACING        | UC_MAJOR_MARK,
  UC_MARK_SPACING_COMBINING = UC_MINOR_MARK_SPACING_COMBINING | UC_MAJOR_MARK,
  UC_MARK_ENCLOSING         = UC_MINOR_MARK_ENCLOSING         | UC_MAJOR_MARK,

  UC_NUMBER_DECIMAL_DIGIT = UC_MINOR_NUMBER_DECIMAL_DIGIT | UC_MAJOR_NUMBER,
  UC_NUMBER_LETTER        = UC_MINOR_NUMBER_LETTER        | UC_MAJOR_NUMBER,
  UC_NUMBER_OTHER         = UC_MINOR_NUMBER_OTHER         | UC_MAJOR_NUMBER,

  UC_PUNCTUATION_CONNECTOR    = UC_MINOR_PUNCTUATION_CONNECTOR    | UC_MAJOR_PUNCTUATION,
  UC_PUNCTUATION_DASH         = UC_MINOR_PUNCTUATION_DASH         | UC_MAJOR_PUNCTUATION,
  UC_PUNCTUATION_OPEN         = UC_MINOR_PUNCTUATION_OPEN         | UC_MAJOR_PUNCTUATION,
  UC_PUNCTUATION_CLOSE        = UC_MINOR_PUNCTUATION_CLOSE        | UC_MAJOR_PUNCTUATION,
  UC_PUNCTUATION_INLINE_QUOTE = UC_MINOR_PUNCTUATION_INLINE_QUOTE | UC_MAJOR_PUNCTUATION,
  UC_PUNCTUATION_FINAL_QUOTE  = UC_MINOR_PUNCTUATION_FINAL_QUOTE  | UC_MAJOR_PUNCTUATION,
  UC_PUNCTUATION_OTHER        = UC_MINOR_PUNCTUATION_OTHER        | UC_MAJOR_PUNCTUATION,

  UC_SYMBOL_MATH     = UC_MINOR_SYMBOL_MATH     | UC_MAJOR_SYMBOL,
  UC_SYMBOL_CURRENCY = UC_MINOR_SYMBOL_CURRENCY | UC_MAJOR_SYMBOL,
  UC_SYMBOL_MODIFIER = UC_MINOR_SYMBOL_MODIFIER | UC_MAJOR_SYMBOL,
  UC_SYMBOL_OTHER    = UC_MINOR_SYMBOL_OTHER    | UC_MAJOR_SYMBOL,

  UC_SEPERATOR_SPACE     = UC_MINOR_SEPERATOR_SPACE     | UC_MAJOR_SEPERATOR,
  UC_SEPERATOR_LINE      = UC_MINOR_SEPERATOR_LINE      | UC_MAJOR_SEPERATOR,
  UC_SEPERATOR_PARAGRAPH = UC_MINOR_SEPERATOR_PARAGRAPH | UC_MAJOR_SEPERATOR,
};

#define UNICODE_CATEGORY_MAJOR_MASK 0x38
#define UNICODE_CATEGORY_MINOR_MASK 0x07

struct dpa_u_unicode_info {
  struct {
    // Hopefully, the compilers layout will match the bit shifts in dpa_u_get_codepoint_info,
    // and the compiler will optimize it all away
    enum unicode_category general_category  : 6;
    uint32_t decomposition_type             : 5;
    uint32_t bidi_mirror                    : 1;
    uint32_t numeric_value                  : 4;
    uint32_t numeric_type                   : 2;
    uint32_t bidi                           : 6;
    uint32_t canonical_combining_class      : 8;
  };
};

// # 8 Canonical_Combining_Class
// # 2 bidi major
// # 4 bidi minor
// # 2 numeric type
// # 4 numeric value
// # 1 bidi mirror
// # 5 decomposition type
// # 3 gc major
// # 3 gc minor

dpa__u_api inline struct dpa_u_unicode_info dpa_u_get_codepoint_info(dpa_u_unicode_codepoint_t codepoint){
  extern const dpa_u_unicode_codepoint_t* unicodedata_0;
  extern size_t unicodedata_0_length;
  if((size_t)codepoint > unicodedata_0_length)
    return (struct dpa_u_unicode_info){0};
  const uint32_t x = unicodedata_0[codepoint];
  return (struct dpa_u_unicode_info){
    .general_category   = x & 0x3F,
    .decomposition_type = (x >>  6) & 0x1F,
    .bidi_mirror        = (x >> 11) & 0x01,
    .numeric_value      = (x >> 12) & 0x0F,
    .numeric_type       = (x >> 16) & 0x03,
    .bidi               = (x >> 18) & 0x3F,
    .canonical_combining_class = x >> 24,
  };
}

dpa__u_api inline enum unicode_category dpa_u_get_category_from_codepoint(dpa_u_unicode_codepoint_t codepoint){
  return dpa_u_get_codepoint_info(codepoint).general_category;
}

dpa__u_api inline bool dpa_u_unicode_is_noncharacter(dpa_u_unicode_codepoint_t codepoint_){
  uint32_t codepoint = codepoint_;
  if(codepoint >= 0x0000FDD0 && codepoint <= 0x0000FDEF)
    return true;
  // Note: since codepoints >U+10FFFF are not defined, the unicode standard does not specify them as non-characters.
  // We assume non-characters follow the same pattern for those undefined codepoints.
  if((codepoint & 0xFFFF) >= 0xFFFE)
    return true;
  return false;
}

dpa__u_api inline bool dpa_u_unicode_is_invalid(dpa_u_unicode_codepoint_t codepoint_){
  uint32_t codepoint = codepoint_;
  if(codepoint >= 0x0000D800 && codepoint <= 0x0000DFFF) // UTF-16 surrogate pairs
    return true;
  if(codepoint > UNICODE_CODEPOINT_MAX)
    return true;
  return false;
}

/** @} */
/** @} */

#endif
