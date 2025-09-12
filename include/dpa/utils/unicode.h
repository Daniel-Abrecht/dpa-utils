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
#define DPA_U_UNICODE_CODEPOINT_MAX 0x10FFFF

#define dpa_u_unicode_category_major_list(X) \
  X((DPA_U_UC_MAJOR_OTHER      , 0<<3)) \
  X((DPA_U_UC_MAJOR_LETTER     , 1<<3)) \
  X((DPA_U_UC_MAJOR_MARK       , 2<<3)) \
  X((DPA_U_UC_MAJOR_NUMBER     , 3<<3)) \
  X((DPA_U_UC_MAJOR_PUNCTUATION, 4<<3)) \
  X((DPA_U_UC_MAJOR_SYMBOL     , 5<<3)) \
  X((DPA_U_UC_MAJOR_SEPERATOR  , 6<<3))
DPA_U_ENUM(dpa_u_unicode_category_major)

#define dpa_u_unicode_category_minor_other_list(X) \
  X((DPA_U_UC_MINOR_OTHER_NOT_ASSIGNED)) \
  X((DPA_U_UC_MINOR_OTHER_CONTROL)) \
  X((DPA_U_UC_MINOR_OTHER_FORMAT)) \
  X((DPA_U_UC_MINOR_OTHER_SURROGATE)) \
  X((DPA_U_UC_MINOR_OTHER_PRIVATE_USE))
DPA_U_ENUM(dpa_u_unicode_category_minor_other)

#define dpa_u_unicode_category_minor_letter_list(X) \
  X((DPA_U_UC_MINOR_LETTER_UPPERCASE)) \
  X((DPA_U_UC_MINOR_LETTER_LOWERCASE)) \
  X((DPA_U_UC_MINOR_LETTER_TITLECASE)) \
  X((DPA_U_UC_MINOR_LETTER_MODIFIER)) \
  X((DPA_U_UC_MINOR_LETTER_OTHER))
DPA_U_ENUM(dpa_u_unicode_category_minor_letter)

#define dpa_u_unicode_category_minor_mark_list(X) \
  X((DPA_U_UC_MINOR_MARK_NONSPACING)) \
  X((DPA_U_UC_MINOR_MARK_SPACING_COMBINING)) \
  X((DPA_U_UC_MINOR_MARK_ENCLOSING))
DPA_U_ENUM(dpa_u_unicode_category_minor_mark)

#define dpa_u_unicode_category_minor_number_list(X) \
  X((DPA_U_UC_MINOR_NUMBER_DECIMAL_DIGIT)) \
  X((DPA_U_UC_MINOR_NUMBER_LETTER)) \
  X((DPA_U_UC_MINOR_NUMBER_OTHER))
DPA_U_ENUM(dpa_u_unicode_category_minor_number)

#define dpa_u_unicode_category_minor_punctuation_list(X) \
  X((DPA_U_UC_MINOR_PUNCTUATION_CONNECTOR)) \
  X((DPA_U_UC_MINOR_PUNCTUATION_DASH)) \
  X((DPA_U_UC_MINOR_PUNCTUATION_OPEN)) \
  X((DPA_U_UC_MINOR_PUNCTUATION_CLOSE)) \
  X((DPA_U_UC_MINOR_PUNCTUATION_INLINE_QUOTE)) \
  X((DPA_U_UC_MINOR_PUNCTUATION_FINAL_QUOTE)) \
  X((DPA_U_UC_MINOR_PUNCTUATION_OTHER))
DPA_U_ENUM(dpa_u_unicode_category_minor_punctuation)

#define dpa_u_unicode_category_minor_symbol_list(X) \
  X((DPA_U_UC_MINOR_SYMBOL_MATH)) \
  X((DPA_U_UC_MINOR_SYMBOL_CURRENCY)) \
  X((DPA_U_UC_MINOR_SYMBOL_MODIFIER)) \
  X((DPA_U_UC_MINOR_SYMBOL_OTHER))
DPA_U_ENUM(dpa_u_unicode_category_minor_symbol)

#define dpa_u_unicode_category_minor_seperator_list(X) \
  X((DPA_U_UC_MINOR_SEPERATOR_SPACE)) \
  X((DPA_U_UC_MINOR_SEPERATOR_LINE)) \
  X((DPA_U_UC_MINOR_SEPERATOR_PARAGRAPH))
DPA_U_ENUM(dpa_u_unicode_category_minor_seperator)

#define dpa_u_unicode_category_list(X) \
  X((DPA_U_UC_OTHER_NOT_ASSIGNED, DPA_U_UC_MINOR_OTHER_NOT_ASSIGNED | DPA_U_UC_MAJOR_OTHER)) \
  X((DPA_U_UC_OTHER_CONTROL     , DPA_U_UC_MINOR_OTHER_CONTROL      | DPA_U_UC_MAJOR_OTHER)) \
  X((DPA_U_UC_OTHER_FORMAT      , DPA_U_UC_MINOR_OTHER_FORMAT       | DPA_U_UC_MAJOR_OTHER)) \
  X((DPA_U_UC_OTHER_SURROGATE   , DPA_U_UC_MINOR_OTHER_SURROGATE    | DPA_U_UC_MAJOR_OTHER)) \
  X((DPA_U_UC_OTHER_PRIVATE_USE , DPA_U_UC_MINOR_OTHER_PRIVATE_USE  | DPA_U_UC_MAJOR_OTHER)) \
  \
  X((DPA_U_UC_LETTER_UPPERCASE, DPA_U_UC_MINOR_LETTER_UPPERCASE | DPA_U_UC_MAJOR_LETTER)) \
  X((DPA_U_UC_LETTER_LOWERCASE, DPA_U_UC_MINOR_LETTER_LOWERCASE | DPA_U_UC_MAJOR_LETTER)) \
  X((DPA_U_UC_LETTER_TITLECASE, DPA_U_UC_MINOR_LETTER_TITLECASE | DPA_U_UC_MAJOR_LETTER)) \
  X((DPA_U_UC_LETTER_MODIFIER , DPA_U_UC_MINOR_LETTER_MODIFIER  | DPA_U_UC_MAJOR_LETTER)) \
  X((DPA_U_UC_LETTER_OTHER    , DPA_U_UC_MINOR_LETTER_OTHER     | DPA_U_UC_MAJOR_LETTER)) \
  \
  X((DPA_U_UC_MARK_NONSPACING       , DPA_U_UC_MINOR_MARK_NONSPACING        | DPA_U_UC_MAJOR_MARK)) \
  X((DPA_U_UC_MARK_SPACING_COMBINING, DPA_U_UC_MINOR_MARK_SPACING_COMBINING | DPA_U_UC_MAJOR_MARK)) \
  X((DPA_U_UC_MARK_ENCLOSING        , DPA_U_UC_MINOR_MARK_ENCLOSING         | DPA_U_UC_MAJOR_MARK)) \
  \
  X((DPA_U_UC_NUMBER_DECIMAL_DIGIT, DPA_U_UC_MINOR_NUMBER_DECIMAL_DIGIT | DPA_U_UC_MAJOR_NUMBER)) \
  X((DPA_U_UC_NUMBER_LETTER       , DPA_U_UC_MINOR_NUMBER_LETTER        | DPA_U_UC_MAJOR_NUMBER)) \
  X((DPA_U_UC_NUMBER_OTHER        , DPA_U_UC_MINOR_NUMBER_OTHER         | DPA_U_UC_MAJOR_NUMBER)) \
  \
  X((DPA_U_UC_PUNCTUATION_CONNECTOR   , DPA_U_UC_MINOR_PUNCTUATION_CONNECTOR    | DPA_U_UC_MAJOR_PUNCTUATION)) \
  X((DPA_U_UC_PUNCTUATION_DASH        , DPA_U_UC_MINOR_PUNCTUATION_DASH         | DPA_U_UC_MAJOR_PUNCTUATION)) \
  X((DPA_U_UC_PUNCTUATION_OPEN        , DPA_U_UC_MINOR_PUNCTUATION_OPEN         | DPA_U_UC_MAJOR_PUNCTUATION)) \
  X((DPA_U_UC_PUNCTUATION_CLOSE       , DPA_U_UC_MINOR_PUNCTUATION_CLOSE        | DPA_U_UC_MAJOR_PUNCTUATION)) \
  X((DPA_U_UC_PUNCTUATION_INLINE_QUOTE, DPA_U_UC_MINOR_PUNCTUATION_INLINE_QUOTE | DPA_U_UC_MAJOR_PUNCTUATION)) \
  X((DPA_U_UC_PUNCTUATION_FINAL_QUOTE , DPA_U_UC_MINOR_PUNCTUATION_FINAL_QUOTE  | DPA_U_UC_MAJOR_PUNCTUATION)) \
  X((DPA_U_UC_PUNCTUATION_OTHER       , DPA_U_UC_MINOR_PUNCTUATION_OTHER        | DPA_U_UC_MAJOR_PUNCTUATION)) \
  \
  X((DPA_U_UC_SYMBOL_MATH    , DPA_U_UC_MINOR_SYMBOL_MATH     | DPA_U_UC_MAJOR_SYMBOL)) \
  X((DPA_U_UC_SYMBOL_CURRENCY, DPA_U_UC_MINOR_SYMBOL_CURRENCY | DPA_U_UC_MAJOR_SYMBOL)) \
  X((DPA_U_UC_SYMBOL_MODIFIER, DPA_U_UC_MINOR_SYMBOL_MODIFIER | DPA_U_UC_MAJOR_SYMBOL)) \
  X((DPA_U_UC_SYMBOL_OTHER   , DPA_U_UC_MINOR_SYMBOL_OTHER    | DPA_U_UC_MAJOR_SYMBOL)) \
  \
  X((DPA_U_UC_SEPERATOR_SPACE    , DPA_U_UC_MINOR_SEPERATOR_SPACE     | DPA_U_UC_MAJOR_SEPERATOR)) \
  X((DPA_U_UC_SEPERATOR_LINE     , DPA_U_UC_MINOR_SEPERATOR_LINE      | DPA_U_UC_MAJOR_SEPERATOR)) \
  X((DPA_U_UC_SEPERATOR_PARAGRAPH, DPA_U_UC_MINOR_SEPERATOR_PARAGRAPH | DPA_U_UC_MAJOR_SEPERATOR))

DPA_U_ENUM(dpa_u_unicode_category)


#define DPA_U_UNICODE_CATEGORY_MAJOR_MASK 0x38
#define DPA_U_UNICODE_CATEGORY_MINOR_MASK 0x07

#define dpa_u_unicode_bidi_type_list(X) \
  X((DPA_U_UNICODE_BIDI_TYPE_STRONG             , 0<<4)) \
  X((DPA_U_UNICODE_BIDI_TYPE_WEAK               , 1<<4)) \
  X((DPA_U_UNICODE_BIDI_TYPE_NEUTRAL            , 2<<4)) \
  X((DPA_U_UNICODE_BIDI_TYPE_EXPLICIT_FORMATTING, 3<<4))
DPA_U_ENUM(dpa_u_unicode_bidi_type)

#define dpa_u_unicode_bidi_class_list(X) \
  X((DPA_U_UNICODE_BIDI_CLASS_LEFT_TO_RIGHT, 0 | DPA_U_UNICODE_BIDI_TYPE_STRONG)) /* L */ \
  X((DPA_U_UNICODE_BIDI_CLASS_RIGHT_TO_LEFT, 1 | DPA_U_UNICODE_BIDI_TYPE_STRONG)) /* R */ \
  X((DPA_U_UNICODE_BIDI_CLASS_ARABIC_LETTER, 2 | DPA_U_UNICODE_BIDI_TYPE_STRONG)) /* AL */ \
  \
  X((DPA_U_UNICODE_BIDI_CLASS_EUROPEAN_NUMBER    , 0 | DPA_U_UNICODE_BIDI_TYPE_WEAK)) /* EN */ \
  X((DPA_U_UNICODE_BIDI_CLASS_EUROPEAN_SEPARATOR , 1 | DPA_U_UNICODE_BIDI_TYPE_WEAK)) /* ES */ \
  X((DPA_U_UNICODE_BIDI_CLASS_EUROPEAN_TERMINATOR, 2 | DPA_U_UNICODE_BIDI_TYPE_WEAK)) /* ET */ \
  X((DPA_U_UNICODE_BIDI_CLASS_ARABIC_NUMBER      , 3 | DPA_U_UNICODE_BIDI_TYPE_WEAK)) /* AN */ \
  X((DPA_U_UNICODE_BIDI_CLASS_COMMON_SEPARATOR   , 4 | DPA_U_UNICODE_BIDI_TYPE_WEAK)) /* CS */ \
  X((DPA_U_UNICODE_BIDI_CLASS_NONSPACING_MARK    , 5 | DPA_U_UNICODE_BIDI_TYPE_WEAK)) /* NSM */ \
  X((DPA_U_UNICODE_BIDI_CLASS_BOUNDARY_NEUTRAL   , 6 | DPA_U_UNICODE_BIDI_TYPE_WEAK)) /* BN */ \
  \
  X((DPA_U_UNICODE_BIDI_CLASS_PARAGRAPH_SEPARATOR, 0 | DPA_U_UNICODE_BIDI_TYPE_NEUTRAL)) /* B */ \
  X((DPA_U_UNICODE_BIDI_CLASS_SEGMENT_SEPARATOR  , 1 | DPA_U_UNICODE_BIDI_TYPE_NEUTRAL)) /* S */ \
  X((DPA_U_UNICODE_BIDI_CLASS_WHITE_SPACE        , 2 | DPA_U_UNICODE_BIDI_TYPE_NEUTRAL)) /* WS */ \
  X((DPA_U_UNICODE_BIDI_CLASS_OTHER_NEUTRAL      , 3 | DPA_U_UNICODE_BIDI_TYPE_NEUTRAL)) /* ON */ \
  \
  X((DPA_U_UNICODE_BIDI_CLASS_LEFT_TO_RIGHT_EMBEDDING, 0 | DPA_U_UNICODE_BIDI_TYPE_EXPLICIT_FORMATTING)) /* LRE */ \
  X((DPA_U_UNICODE_BIDI_CLASS_LEFT_TO_RIGHT_OVERRIDE , 1 | DPA_U_UNICODE_BIDI_TYPE_EXPLICIT_FORMATTING)) /* LRO */ \
  X((DPA_U_UNICODE_BIDI_CLASS_RIGHT_TO_LEFT_EMBEDDING, 2 | DPA_U_UNICODE_BIDI_TYPE_EXPLICIT_FORMATTING)) /* RLE */ \
  X((DPA_U_UNICODE_BIDI_CLASS_RIGHT_TO_LEFT_OVERRIDE , 3 | DPA_U_UNICODE_BIDI_TYPE_EXPLICIT_FORMATTING)) /* RLO */ \
  X((DPA_U_UNICODE_BIDI_CLASS_POP_DIRECTIONAL_FORMAT , 4 | DPA_U_UNICODE_BIDI_TYPE_EXPLICIT_FORMATTING)) /* PDF */ \
  X((DPA_U_UNICODE_BIDI_CLASS_LEFT_TO_RIGHT_ISOLATE  , 5 | DPA_U_UNICODE_BIDI_TYPE_EXPLICIT_FORMATTING)) /* LRI */ \
  X((DPA_U_UNICODE_BIDI_CLASS_RIGHT_TO_LEFT_ISOLATE  , 6 | DPA_U_UNICODE_BIDI_TYPE_EXPLICIT_FORMATTING)) /* RLI */ \
  X((DPA_U_UNICODE_BIDI_CLASS_FIRST_STRONG_ISOLATE   , 7 | DPA_U_UNICODE_BIDI_TYPE_EXPLICIT_FORMATTING)) /* FSI */ \
  X((DPA_U_UNICODE_BIDI_CLASS_POP_DIRECTIONAL_ISOLATE, 8 | DPA_U_UNICODE_BIDI_TYPE_EXPLICIT_FORMATTING)) /* PDI */

DPA_U_ENUM(dpa_u_unicode_bidi_class)


#define dpa_u_unicode_decomposition_type_list(X) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_NONE)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_CANONICAL)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_FONT)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_NOBREAK)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_INITIAL)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_MEDIAL)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_FINAL)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_ISOLATED)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_CIRCLE)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_SUPER)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_SUB)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_VERTICAL)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_WIDE)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_NARROW)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_SMALL)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_SQUARE)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_FRACTION)) \
  X((DPA_U_UNICODE_DECOMPOSITION_TYPE_COMPAT))
DPA_U_ENUM(dpa_u_unicode_decomposition_type)

#define dpa_u_unicode_numeric_type_list(X) \
  X((DPA_U_UNICODE_NUMERIC_TYPE_NONE))    /* This is not a number */ \
  X((DPA_U_UNICODE_NUMERIC_TYPE_DECIMAL)) /* This is a normal number in a base 10 system */ \
  X((DPA_U_UNICODE_NUMERIC_TYPE_DIGIT))   /* This is a symbol containing a decimal number. Things like super/sub-script, circled numbers, etc. */ \
  X((DPA_U_UNICODE_NUMERIC_TYPE_NUMERIC)) /* This is a symbol representing a special number. Things like ratios, roman numerals, etc. */
DPA_U_ENUM(dpa_u_unicode_numeric_type)

/**
 * \see dpa_u_get_codepoint_info
 */
struct dpa_u_unicode_info {
  struct {
    // Hopefully, the compilers layout will match the bit shifts in dpa_u_get_codepoint_info,
    // and the compiler will optimize it all away
    enum dpa_u_unicode_category general_category             : 6; //< \ref dpa_u_unicode_get_category
    enum dpa_u_unicode_decomposition_type decomposition_type : 5;
    uint32_t bidi_mirror                                     : 1;
    uint32_t numeric_value                                   : 4; //< A number between 0 and 10. Only set if numeric type is decimal or digit.
    enum dpa_u_unicode_numeric_type numeric_type             : 2;
    enum dpa_u_unicode_bidi_class bidi                       : 6;
    uint32_t canonical_combining_class                       : 8;
  };
};

/**
 * Returns some information about a codepoint. This is just what we could squeeze into a uint32_t,
 * we've got a giant lookup table, loaded / memory mapped from a file when the program starts.
 * The unicode database contains a lot more information than this function can provide.
 */
dpa__u_api dpa_u_unsequenced inline struct dpa_u_unicode_info dpa_u_get_codepoint_info(dpa_u_unicode_codepoint_t codepoint){
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

/**
 * This function returns the unicode general category of a codepoint. This is useful if you want to know if something
 * is a letter, a number, a space, and so on. Beware that CR LF TAB count as control characters, not space characters.
 * 
 * If you only need the major general category, and it with the \ref DPA_U_UNICODE_CATEGORY_MAJOR_MASK bitmask.  
 * If you only need the minor general category, and it with the \ref DPA_U_UNICODE_CATEGORY_MINOR_MASK bitmask.
 * 
 * \see dpa_u_unicode_category
 * \see dpa_u_unicode_category_major
 * \see dpa_u_get_codepoint_info
 * \see dpa_u_unicode_category_minor_*
 */
dpa__u_api dpa_u_unsequenced inline enum dpa_u_unicode_category dpa_u_unicode_get_category(dpa_u_unicode_codepoint_t codepoint){
  return dpa_u_get_codepoint_info(codepoint).general_category;
}

/**
 * Returns true, if the codepoint is a non-character.
 * Unicode defines 66 codepoints, that includes any codepoints ending in FFFE and FFFF.
 * This function also treats such codepoints outside the valid unicode range (>U+10FFFF) as non-characters.
 */
dpa__u_api dpa_u_unsequenced inline bool dpa_u_unicode_is_noncharacter(dpa_u_unicode_codepoint_t codepoint){
  if(codepoint >= 0x0000FDD0 && codepoint <= 0x0000FDEF)
    return true;
  // Note: since codepoints >U+10FFFF are not defined, the unicode standard does not specify them as non-characters.
  // We assume non-characters follow the same pattern for those undefined codepoints.
  if((codepoint & 0xFFFF) >= 0xFFFE)
    return true;
  return false;
}

/**
 * Returns true if the codepoint is a UTF-16 surrogate.
 * Those codepoints are only meant to encode other codepoints in UTF-16.
 * They are a valid codepoint, and can be encoded in UTF-8, but they should never appear anywhere in theory,
 * although they will in practice.
 */
dpa__u_api dpa_u_unsequenced inline bool dpa_u_unicode_is_surrogate(dpa_u_unicode_codepoint_t codepoint){
  return codepoint >= 0x0000D800 && codepoint <= 0x0000DFFF;
}

/**
 * Returns true if the unicode codepointis invalid.  
 * That is any codepoint > U+10FFFF (DPA_U_UNICODE_CODEPOINT_MAX), and all the UTF-16 surrogates (U+D800 .. U+DFFF).
 */
dpa__u_api dpa_u_unsequenced inline bool dpa_u_unicode_is_invalid(dpa_u_unicode_codepoint_t codepoint_){
  uint32_t codepoint = codepoint_;
  if(codepoint >= 0x0000D800 && codepoint <= 0x0000DFFF) // UTF-16 surrogate pairs
    return true;
  if(codepoint > DPA_U_UNICODE_CODEPOINT_MAX)
    return true;
  return false;
}

/** @} */
/** @} */

#endif
