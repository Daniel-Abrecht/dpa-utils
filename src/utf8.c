#include <dpa/utils/utf8.h>

bool dpa_u_utf8_validate(struct dpa_u_streaming_utf8_validator*restrict const v, const int _ch){
  const uint_least8_t ch = _ch & 0xFF;
  if(_ch == EOF){
    if(v->index)
      goto bad;
    return true;
  }
  if(!v->index){
    v->state = 0;
    if(ch < 0x80)
      return true;
    if(ch < 0xC2)
      goto bad;
    if(ch >= 0xFE) // Not yet defined
      goto bad;
    if(ch >= 0xF5) // Sequences above this value are defined, but not (yet?) allowed.
      goto bad;    // If you remove this condition, make sure to check for the overlong characters for those longer sequeces
    unsigned length = 1 + (ch >= 0xE0) + (ch >= 0xF0) + (ch >= 0xF8) + (ch >= 0xFC);
    v->index = length;
    if(length == 2){
      switch(ch){
        case 0xE0: v->state = 1; break; // Overlong
        case 0xED: v->state = 2; break; // CESU-8
        case 0xEF: v->state = 3; break; // noncharacter U+FFFE U+FFFF
      }
    }
    if(length == 3){
      switch(ch){
        case 0xF0: v->state = 5; break; // noncharacter
        case 0xF1: v->state = 8; break; // noncharacter
        case 0xF2: v->state = 8; break; // noncharacter
        case 0xF3: v->state = 8; break; // noncharacter
        case 0xF4: v->state = 6; break; // U+110000 - U+13FFFF, not yet used / allowed
      }
    }
    return true;
  }
  if((ch & 0xC0) != 0x80)
    goto bad;
  unsigned state = v->state;
  v->state = 0;
  switch(state){
    case  1: if(ch >= 0x80 && ch <= 0x9F) goto bad; break;
    case  2: if(ch >= 0xA0 && ch <= 0xBF) goto bad; break;
    case  3: {
      if(ch == 0xBF)
        v->state = 4;
      if(ch == 0xB7)
        v->state = 7;
    } break;
    case  4: if(ch == 0xBE || ch == 0xBF) goto bad; break;
    case  5: {
      if(ch < 0x90 || ch > 0xBF)
        goto bad;
      if(ch == 0x9F || ch == 0xAF || ch == 0xBF)
        v->state = 9;
    } break;
    case  6: {
      if(ch < 0x80 || ch > 0x8F)
        goto bad;
      if(ch == 0x8F)
        v->state = 9;
    } break;
    case  7: if(ch >= 0x90 && ch <= 0xAF) goto bad; break;
    case  8: if(ch == 0x8F || ch == 0x9F || ch == 0xAF || ch == 0xBF) v->state = 9; break;
    case  9: if(ch == 0xBF) v->state = 4; break;
  }
  v->index -= 1;
  return true;
bad:
  v->index = 0;
  return false;
}

uint32_t dpa_u_next_codepoint(const unsigned char** pit, const unsigned char* end){
  const unsigned char*const start = *pit;
  const unsigned char* it = start;
  if(it == end)
    return -1;
  unsigned char ch = *(it++);
  int length = 0;
  for(; ch & 0x80; ch<<=1)
    length++;
  if(length == 1 || length > 7)
    goto error;
  if(start+length >= end)
    goto error;
  end = start+length;
  uint32_t codepoint = ch>>length;
  for(; it<end; it++){
    ch = *it;
    if((ch & 0xC0) != 0x80)
      goto error;
    codepoint = (codepoint << 6) | (ch & 0x3F);
  }
  if(length > 1 && codepoint < (uint64_t)0x40<<((length-2)*5))
    goto error; // overlong sequence
  *pit = it;
  return codepoint;
error:
  while((*it & 0xC0) == 0x80)
    it++;
  *pit = it;
  return -1;
}
