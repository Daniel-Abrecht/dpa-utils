#!/usr/bin/env python3

import sys

ucd_base="/usr/share/unicode"
dest="."

if len(sys.argv) >= 2:
  ucd_base=sys.argv[1]
if len(sys.argv) >= 3:
  dest=sys.argv[2]

def read_UnicodeData():
  fields=(
    'Codepoint',
    'Name',
    'General_Category',
    'Canonical_Combining_Class',
    'Bidi_Class',
    'Decomposition',
    'Numeric_Decimal',
    'Numeric_Digit',
    'Numeric_Numeric',
    'Bidi_Mirrored',
    'Unicode_1_Name',
    'ISO_Comment',
    'Simple_Uppercase_Mapping',
    'Simple_Lowercase_Mapping',
    'Simple_Titlecase_Mapping',
  )

  with open(ucd_base+"/UnicodeData.txt", "r") as file:
    for line in file:
      entry = [x.strip() if x else None for x in line.split(';')]
      entry = dict(zip(fields, entry))
      if '..' in entry['Codepoint']:
        first_codepoint, last_codepoint = entry['Codepoint'].split('..')
      else:
        first_codepoint = entry['Codepoint']
        last_codepoint = first_codepoint
      first_codepoint = int(first_codepoint, 16)
      last_codepoint  = int(last_codepoint, 16)
      del entry['Codepoint']
      if entry['Canonical_Combining_Class']:
        entry['Canonical_Combining_Class'] = int(entry['Canonical_Combining_Class'])
      entry['Numeric_Type'] = 0
      if entry['Numeric_Decimal']:
        entry['Numeric_Decimal'] = int(entry['Numeric_Decimal'])
        entry['Numeric_Type'] = 1
      if entry['Numeric_Digit']:
        entry['Numeric_Digit'] = int(entry['Numeric_Digit'])
        entry['Numeric_Type'] = 2
      if entry['Numeric_Numeric']:
        entry['Numeric_Type'] = 3
      entry['Bidi_Mirrored'] = entry['Bidi_Mirrored'] == 'Y'
      if entry['Name'].endswith(', First>'):
        entry['Name'] = entry['Name'][1:-8]
        entry2 = [x.strip() for x in next(file).split(';')]
        entry2 = dict(zip(fields, entry2))
        if not entry2['Name'].endswith(', Last>'):
          raise Exception("Expected last entry of range")
        last_codepoint = int(entry2['Codepoint'], 16)
      if last_codepoint < first_codepoint:
        raise Exception("Bad codepoint range")
      yield first_codepoint, last_codepoint, entry

general_category={
  'Cn': (0, 0, "OTHER_NOT_ASSIGNED"),
  'Cc': (0, 1, "OTHER_CONTROL"),
  'Cf': (0, 2, "OTHER_FORMAT"),
  'Cs': (0, 3, "OTHER_SURROGATE"),
  'Co': (0, 4, "OTHER_PRIVATE_USE"),
  'Lu': (1, 0, "LETTER_UPPERCASE"),
  'Ll': (1, 1, "LETTER_LOWERCASE"),
  'Lt': (1, 2, "LETTER_TITLECASE"),
  'Lm': (1, 3, "LETTER_MODIFIER"),
  'Lo': (1, 4, "LETTER_OTHER"),
  'Mn': (2, 0, "MARK_NONSPACING"),
  'Mc': (2, 1, "MARK_SPACING_COMBINING"),
  'Me': (2, 2, "MARK_ENCLOSING"),
  'Nd': (3, 0, "NUMBER_DECIMAL_DIGIT"),
  'Nl': (3, 1, "NUMBER_LETTER"),
  'No': (3, 2, "NUMBER_OTHER"),
  'Pc': (4, 0, "PUNCTUATION_CONNECTOR"),
  'Pd': (4, 1, "PUNCTUATION_DASH"),
  'Ps': (4, 2, "PUNCTUATION_OPEN"),
  'Pe': (4, 3, "PUNCTUATION_CLOSE"),
  'Pi': (4, 4, "PUNCTUATION_INLINE_QUOTE"),
  'Pf': (4, 5, "PUNCTUATION_FINAL_QUOTE"),
  'Po': (4, 6, "PUNCTUATION_OTHER"),
  'Sm': (5, 0, "SYMBOL_MATH"),
  'Sc': (5, 1, "SYMBOL_CURRENCY"),
  'Sk': (5, 2, "SYMBOL_MODIFIER"),
  'So': (5, 3, "SYMBOL_OTHER"),
  'Zs': (6, 0, "SEPERATOR_SPACE"),
  'Zl': (6, 1, "SEPERATOR_LINE"),
  'Zp': (6, 2, "SEPERATOR_PARAGRAPH"),
}

Bidi_Class={
# STRONG TYPES
  'L'  : (0, 0, 'LEFT_TO_RIGHT'),
  'R'  : (0, 1, 'RIGHT_TO_LEFT'),
  'AL' : (0, 2, 'ARABIC_LETTER'),
# WEAK TYPES
  'EN' : (1, 0, 'EUROPEAN_NUMBER'),
  'ES' : (1, 1, 'EUROPEAN_SEPARATOR'),
  'ET' : (1, 2, 'EUROPEAN_TERMINATOR'),
  'AN' : (1, 3, 'ARABIC_NUMBER'),
  'CS' : (1, 4, 'COMMON_SEPARATOR'),
  'NSM': (1, 5, 'NONSPACING_MARK'),
  'BN' : (1, 6, 'BOUNDARY_NEUTRAL'),
# NEUTRAL TYPES
  'B'  : (2, 0, 'PARAGRAPH_SEPARATOR'),
  'S'  : (2, 1, 'SEGMENT_SEPARATOR'),
  'WS' : (2, 2, 'WHITE_SPACE'),
  'ON' : (2, 3, 'OTHER_NEUTRAL'),
# EXPLICIT FORMATTING
  'LRE': (3, 0, 'LEFT_TO_RIGHT_EMBEDDING'),
  'LRO': (3, 1, 'LEFT_TO_RIGHT_OVERRIDE'),
  'RLE': (3, 2, 'RIGHT_TO_LEFT_EMBEDDING'),
  'RLO': (3, 3, 'RIGHT_TO_LEFT_OVERRIDE'),
  'PDF': (3, 4, 'POP_DIRECTIONAL_FORMAT'),
  'LRI': (3, 5, 'LEFT_TO_RIGHT_ISOLATE'),
  'RLI': (3, 6, 'RIGHT_TO_LEFT_ISOLATE'),
  'FSI': (3, 7, 'FIRST_STRONG_ISOLATE'),
  'PDI': (3, 8, 'POP_DIRECTIONAL_ISOLATE')
}

decomposition_type={
  "canonical": 1,
  "font": 2,
  "noBreak": 3,
  "initial": 4,
  "medial": 5,
  "final": 6,
  "isolated": 7,
  "circle": 8,
  "super": 9,
  "sub": 10,
  "vertical": 11,
  "wide": 12,
  "narrow": 13,
  "small": 14,
  "square": 15,
  "fraction": 16,
  "compat": 17,
}

# 8 Canonical_Combining_Class
# 2 bidi major
# 4 bidi minor
# 2 numeric type
# 4 numeric value
# 1 bidi mirror
# 5 decomposition type
# 3 gc major
# 3 gc minor

data = [*read_UnicodeData()]
result=bytearray(data[-1][1]*4)
for first, last, entry in data:
  for codepoint in range(first, last+1):
    gc_major, gc_minor, gc_name = general_category[entry['General_Category']]
    gc = (gc_major<<3) | gc_minor
    numeric_digit = entry['Numeric_Digit'] or 0
    d = entry['Decomposition']
    if d:
      if d[0] == '<':
        d = decomposition_type[d[1:d.find('>')]]
      else:
        d = 1
    else:
      d = 0
    value  = 0
    value |= gc_minor
    value |= gc_major<<3
    value |= d<<6
    value |= entry['Bidi_Mirrored']<<11
    value |= numeric_digit<<12
    value |= entry['Numeric_Type']<<16
    if entry['Bidi_Class']:
      bidi_major, bidi_minor, bidi_name = Bidi_Class[entry['Bidi_Class']]
      value |= bidi_minor<<18
      value |= bidi_minor<<22
    value |= entry['Canonical_Combining_Class']<<24
    result[codepoint*4:codepoint*4+4] = value.to_bytes(4, 'little')

with open(dest+"/UnicodeData.0.bin", "wb") as binary_file:
  binary_file.write(result)
