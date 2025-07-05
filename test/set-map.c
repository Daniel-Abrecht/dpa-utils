//////////////////////////////////
//// Top section, common code ////
//////////////////////////////////
#ifndef DPA_U_T_SELF
#define DPA_U_T_SELF

#include <dpa/utils/test.h>
#include <dpa/utils/set.h>
#include <dpa/utils/map.h>
#include <errno.h>
#include <stdio.h>

uint_least8_t  ul8 [  0x100]; size_t ul8_count;
uint_least16_t ul16[0x10000]; size_t ul16_count;
uint_least32_t ul32[0x10000]; size_t ul32_count;
uint_least64_t ul64[0x10000]; size_t ul64_count;
#ifdef DPA_HAS_UINT128
dpa_uint128_t ul128[0x10000];
#elif DPA_HAS_UINT256
dpa_uint256_t ul128[0x10000];
#else
dpa_u_giant_unsigned_int_t ul128[0x10000]; // May not actually be 128 big, but is the biggest we've got
#endif
size_t ul128_count;
#ifdef DPA_HAS_UINT256
dpa_uint256_t ul256[0x10000];
#else
dpa_u_giant_unsigned_int_t ul256[0x10000]; // May not actually be 256 big, but is the biggest we've got
#endif
size_t ul256_count;
dpa_u_a_bo_unique_t ustr[0x10000]; size_t ustr_count;

static int hex2bin_digit(const unsigned char x){
  if(x >= '0' && x <= '9'){
    return x - '0';
  }else if(x >= 'A' && x <= 'Z'){
    return x - 'A' + 10;
  }else if(x >= 'A' && x <= 'Z'){
    return x - 'a' + 10;
  }
  return -1;
}

static int hex2bin_byte(const unsigned char x[const 2]){
  int r = (hex2bin_digit(x[0])<<4) | hex2bin_digit(x[1]);
  if(r<0) return -1;
  return r;
}

static void hex2bin(void*const res, size_t n, const unsigned char* x){
  unsigned char* r = res;
  size_t m = strlen((char*)x);
  if(x[m-1] == '\n') m--;
  m /= 2;
  if(m > n) m = n;
  if(1 == *(char*)&(unsigned){1}){ // little endian
    for(size_t i=0; i<m; i++)
      r[m-i-1] = hex2bin_byte(&x[i*2]);
  }else{ // big endian
    for(size_t i=0; i<m; i++)
      r[i] = hex2bin_byte(&x[i*2]);
  }
}

static void to_ustring(dpa_u_a_bo_unique_t*const ret, size_t n, const unsigned char* x){
  (void)n;
  dpa_u_bo_t bo = {
    .size = strlen((const char*)x),
    .data = (char*)x,
  };
  if(bo.size && ((char*)bo.data)[bo.size-1] == '\n')
    bo.size -= 1;
  *ret = dpa_u_bo_intern(bo);
}

void dpa_u_test_setup(void){
  FILE* f = fopen("build/unique-random", "rb");
  if(!f) dpa_u_abort("Failed to open build/unique-random: %d %s", errno, strerror(errno));
  unsigned char line[1024];
#define READ_LINES(L, F) \
  for(L##_count=0; fgets((char*)line, sizeof(line), f) && line[0] != '\n'; L##_count++){ \
    if(L##_count>=sizeof(L)/sizeof(*L)) continue; \
    F(&L[L##_count], sizeof(L[L##_count]), line); \
  }
  READ_LINES(ul8, hex2bin);
  READ_LINES(ul16, hex2bin);
  READ_LINES(ul32, hex2bin);
  READ_LINES(ul64, hex2bin);
  READ_LINES(ul128, hex2bin);
  READ_LINES(ul256, hex2bin);
  READ_LINES(ustr, to_ustring);
#undef READ_NUMBERS
}

DPA_U_TEST_MAIN

#define GET_RAND_ENTRY DPA_U_CONCAT_E(DPA__U_SM_PREFIX, __get_rand)

///////////////////////////////////////////

#define DPA__U_SM_KIND DPA__U_SM_KIND_SET

#define DPA__U_STRING_SETMAP
#define DPA__U_SM_KEY_TYPE dpa_u_a_bo_unique_t
#define DPA__U_SM_PREFIX dpa_u_set_string
#define DPA__U_SM_TYPE dpa_u_set_string_t
#include "set-map.c"
#undef DPA__U_SM_KEY_TYPE
#undef DPA__U_SM_PREFIX
#undef DPA__U_SM_TYPE
#undef DPA__U_STRING_SETMAP

#define DPA__U_SM_TEMPLATE <test/set-map.c>
#include <dpa/utils/_set-and-map.generator>


#define DPA__U_SM_KIND DPA__U_SM_KIND_MAP

#define DPA__U_STRING_SETMAP
#define DPA__U_SM_KEY_TYPE dpa_u_a_bo_unique_t
#define DPA__U_SM_PREFIX dpa_u_map_string
#define DPA__U_SM_TYPE dpa_u_map_string_t
#include "set-map.c"
#undef DPA__U_SM_KEY_TYPE
#undef DPA__U_SM_PREFIX
#undef DPA__U_SM_TYPE
#undef DPA__U_STRING_SETMAP

#define DPA__U_SM_TEMPLATE <test/set-map.c>
#include <dpa/utils/_set-and-map.generator>

///////////////////////////////////////////

#else
//////////////////////////
//// Template section ////
//////////////////////////

#undef DPA_U_TESTCASE_SUFFIX
#define DPA_U_TESTCASE_SUFFIX DPA_U_CONCAT_E(DPA__U_SM_PREFIX, __LINE__)

bool GET_RAND_ENTRY(DPA__U_SM_KEY_TYPE*const ret, size_t i){
#ifdef DPA__U_STRING_SETMAP
  if(i >= ustr_count) return false;
  *ret = ustr[i];
  return true;
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
  if(sizeof(DPA__U_SM_KEY_TYPE) >= 32){
    if(i >= ul256_count) return false;
    *ret = (DPA__U_SM_KEY_TYPE)ul256[i];
    return true;
  }else if(sizeof(DPA__U_SM_KEY_TYPE) >= 16){
    if(i >= ul128_count) return false;
    *ret = (DPA__U_SM_KEY_TYPE)ul128[i];
    return true;
  }else if(sizeof(DPA__U_SM_KEY_TYPE) >= 8){
    if(i >= ul64_count) return false;
    *ret = (DPA__U_SM_KEY_TYPE)ul64[i];
    return true;
  }else if(sizeof(DPA__U_SM_KEY_TYPE) >= 4){
    if(i >= ul32_count) return false;
    *ret = (DPA__U_SM_KEY_TYPE)ul32[i];
    return true;
  }else if(sizeof(DPA__U_SM_KEY_TYPE) >= 2){
    if(i >= ul16_count) return false;
    *ret = (DPA__U_SM_KEY_TYPE)ul16[i];
    return true;
  }else{
    if(i >= ul8_count) return false;
    *ret = (DPA__U_SM_KEY_TYPE)ul8[i];
    return true;
  }
#pragma GCC diagnostic pop
#endif
  return false;
}

DPA_U_TESTCASE((DPA_U_STR_EVAL(DPA__U_SM_TYPE) "\t" "add different")){
  DPA__U_SM_TYPE container = {0};
  DPA__U_SM_KEY_TYPE key;
  size_t j=0, k=0;
  bool done = false;
  while(!done){
    // puts("");
    k = j;
    for(size_t i=0; i<16; i++,j++){
      if(!GET_RAND_ENTRY(&key, j)){
        done = true;
        break;
      }
      {
        size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
        if(count != j){
          fprintf(stderr, "Error 10: Wrong entry count %zu, expected %zu\n", count, j);
          goto error;
        }
      }
#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
      int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _add)(&container, key);
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
      int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _set)(&container, key, (dpa_u_any_value_t){.u64=j});
#endif
      if(result < 0){
        fprintf(stderr, "Error 1: Failed to add entry %zu\n", j);
        goto error;
      }
      if(result){
        fprintf(stderr, "Error 2: Entry %zu was already present, but was never added\n", j);
        goto error;
      }
      if(!DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
        fprintf(stderr, "Error 3: Prevously added entry %zu not found\n", j);
        goto error;
      }
      {
        size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
        if(count != j+1){
          fprintf(stderr, "Error 11: Wrong entry count %zu, expected %zu\n", count, j+1);
          goto error;
        }
      }
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
      const dpa_u_optional_t v = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get)(&container, key);
      if(!v.present){
        fprintf(stderr, "Error 4: failed to get entry %zu, but check if it exists did succeed\n", j);
        goto error;
      }
      if(v.value.u64 != j){
        fprintf(stderr, "Error 5: value retrieved from entry %zu is wrong: %zu\n", j, v.value.u64);
        goto error;
      }
#endif
    }
    j = k;
    for(size_t i=0; i<16; i++,j++){
      if(!GET_RAND_ENTRY(&key, j))
        break;
      if(!DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
        fprintf(stderr, "Error 6: Prevously added entry %zu not found\n", j);
        goto error;
      }
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
      const dpa_u_optional_t v = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get)(&container, key);
      if(!v.present){
        fprintf(stderr, "Error 7: failed to get entry %zu, but check if it exists did succeed\n", j);
        goto error;
      }
      if(v.value.u64 != j){
        fprintf(stderr, "Error 8: value retrieved from entry %zu is wrong: %zu\n", j, v.value.u64);
        goto error;
      }
#endif
    }
    k = j;
    for(size_t i=0; i<16; i++,j++){
      if(!GET_RAND_ENTRY(&key, j))
        break;
      if(DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
        fprintf(stderr, "Error 9: Entry found, but was never added\n");
        goto error;
      }
    }
    j = k;
  }
  // DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _dump_hashmap_key_hashes)(&container); // This is only for debugging
  DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _clear)(&container);
  return 0;
error:
  // DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _dump_hashmap_key_hashes)(&container); // This is only for debugging
  DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _clear)(&container);
  return 1;
}

DPA_U_TESTCASE((DPA_U_STR_EVAL(DPA__U_SM_TYPE) "\t" "add twice")){
  DPA__U_SM_TYPE container = {0};
  size_t j=0;
  for(size_t i=0; i<16; i++,j++){
    DPA__U_SM_KEY_TYPE key;
    if(!GET_RAND_ENTRY(&key, i)){
      fprintf(stderr, "Error 1: not enough test entries\n");
      return false;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != j){
        fprintf(stderr, "Error 12: Wrong entry count %zu, expected %zu\n", count, j);
        goto error;
      }
    }
  #if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
    int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _add)(&container, key);
  #elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _set)(&container, key, (dpa_u_any_value_t){.u64=j});
  #endif
    if(result < 0){
      fprintf(stderr, "Error 2: Failed to add entry %zu\n", i);
      goto error;
    }
    if(result){
      fprintf(stderr, "Error 3: Entry %zu was already present, but was never added\n", i);
      goto error;
    }
    if(!DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
      fprintf(stderr, "Error 4: Prevously added entry %zu not found\n", i);
      goto error;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != j+1){
        fprintf(stderr, "Error 13: Wrong entry count %zu, expected %zu\n", count, j+1);
        goto error;
      }
    }
  }
  for(size_t i=0; i<16; i++){
    DPA__U_SM_KEY_TYPE key;
    if(!GET_RAND_ENTRY(&key, i)){
      fprintf(stderr, "Error 5: not enough test entries\n");
      return false;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != j){
        fprintf(stderr, "Error 14: Wrong entry count %zu, expected %zu\n", count, j);
        goto error;
      }
    }
  #if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
    int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _add)(&container, key);
  #elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _set)(&container, key, (dpa_u_any_value_t){.u64=i+j});
  #endif
    if(result < 0){
      fprintf(stderr, "Error 6: Failed to add entry %zu\n", i);
      goto error;
    }
    if(!result){
      fprintf(stderr, "Error 7: Entry %zu should have been already present, but wasn't\n", i);
      goto error;
    }
    if(!DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
      fprintf(stderr, "Error 8: Prevously added entry %zu not found\n", i);
      goto error;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != j){
        fprintf(stderr, "Error 15: Wrong entry count %zu, expected %zu\n", count, j);
        goto error;
      }
    }
  }
  for(size_t i=0; i<16; i++){
    DPA__U_SM_KEY_TYPE key;
    if(!GET_RAND_ENTRY(&key, i)){
      fprintf(stderr, "Error 9: not enough test entries\n");
      return false;
    }
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    const dpa_u_optional_t v = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get)(&container, key);
    if(!v.present){
      fprintf(stderr, "Error 10: failed to get entry %zu, but check if it exists did succeed\n", i);
      goto error;
    }
    if(v.value.u64 != i+j){
      fprintf(stderr, "Error 11: value retrieved from entry %zu is wrong: %zu\n", i, v.value.u64);
      goto error;
    }
#endif
  }
  // DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _dump_hashmap_key_hashes)(&container); // This is only for debugging
  DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _clear)(&container);
  return 0;
error:
  // DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _dump_hashmap_key_hashes)(&container); // This is only for debugging
  DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _clear)(&container);
  return 1;
}


#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
DPA_U_TESTCASE((DPA_U_STR_EVAL(DPA__U_SM_TYPE) "\t" "exchange value")){
  DPA__U_SM_TYPE container = {0};
  size_t j=0;
  for(size_t i=0; i<16; i++,j++){
    DPA__U_SM_KEY_TYPE key;
    if(!GET_RAND_ENTRY(&key, i)){
      fprintf(stderr, "Error 1: not enough test entries\n");
      return false;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != j){
        fprintf(stderr, "Error 14: Wrong entry count %zu, expected %zu\n", count, j);
        goto error;
      }
    }
    dpa_u_any_value_t p = (dpa_u_any_value_t){.u64=j};
    int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _exchange)(&container, key, &p);
    if(result < 0){
      fprintf(stderr, "Error 2: Failed to add entry %zu\n", i);
      goto error;
    }
    if(result){
      fprintf(stderr, "Error 3: Entry %zu was already present, but was never added\n", i);
      goto error;
    }
    if(!DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
      fprintf(stderr, "Error 4: Prevously added entry %zu not found\n", i);
      goto error;
    }
    if(p.u64 != j){
      fprintf(stderr, "Error 5: return parameter was modified\n");
      goto error;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != j+1){
        fprintf(stderr, "Error 15: Wrong entry count %zu, expected %zu\n", count, j+1);
        goto error;
      }
    }
  }
  for(size_t i=0; i<16; i++){
    DPA__U_SM_KEY_TYPE key;
    if(!GET_RAND_ENTRY(&key, i)){
      fprintf(stderr, "Error 6: not enough test entries\n");
      return false;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != j){
        fprintf(stderr, "Error 16: Wrong entry count %zu, expected %zu\n", count, j);
        goto error;
      }
    }
    dpa_u_any_value_t p = {.u64=i+j};
    int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _exchange)(&container, key, &p);
    if(result < 0){
      fprintf(stderr, "Error 7: Failed to add entry %zu\n", i);
      goto error;
    }
    if(!result){
      fprintf(stderr, "Error 8: Entry %zu should have been already present, but wasn't\n", i);
      goto error;
    }
    if(!DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
      fprintf(stderr, "Error 9: Prevously added entry %zu not found\n", i);
      goto error;
    }
    if(p.u64 != i){
      fprintf(stderr, "Error 10: wrong value was returned\n");
      goto error;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != j){
        fprintf(stderr, "Error 17: Wrong entry count %zu, expected %zu\n", count, j);
        goto error;
      }
    }
  }
  for(size_t i=0; i<16; i++){
    DPA__U_SM_KEY_TYPE key;
    if(!GET_RAND_ENTRY(&key, i)){
      fprintf(stderr, "Error 11: not enough test entries\n");
      return false;
    }
    const dpa_u_optional_t v = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get)(&container, key);
    if(!v.present){
      fprintf(stderr, "Error 12: failed to get entry %zu, but check if it exists did succeed\n", i);
      goto error;
    }
    if(v.value.u64 != i+j){
      fprintf(stderr, "Error 13: value retrieved from entry %zu is wrong: %zu\n", i, v.value.u64);
      goto error;
    }
  }
  // DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _dump_hashmap_key_hashes)(&container); // This is only for debugging
  DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _clear)(&container);
  return 0;
error:
  // DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _dump_hashmap_key_hashes)(&container); // This is only for debugging
  DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _clear)(&container);
  return 1;
}
#endif


DPA_U_TESTCASE((DPA_U_STR_EVAL(DPA__U_SM_TYPE) "\t" "remove")){
  DPA__U_SM_TYPE container = {0};
  DPA__U_SM_KEY_TYPE key;
  size_t n = 0;
  for(size_t i=0; GET_RAND_ENTRY(&key, i); i++,n++){
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != i){
        fprintf(stderr, "Error 5: Wrong entry count %zu, expected %zu\n", count, i);
        goto error;
      }
    }
#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
    int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _add)(&container, key);
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _set)(&container, key, (dpa_u_any_value_t){.u64=i});
#endif
    if(result < 0){
      fprintf(stderr, "Error 1: Failed to add entry %zu\n", i);
      goto error;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != i+1){
        fprintf(stderr, "Error 6: Wrong entry count %zu, expected %zu\n", count, i+1);
        goto error;
      }
    }
  }
  for(size_t i=0; GET_RAND_ENTRY(&key, i); i++){
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != n-i){
        fprintf(stderr, "Error 6: Wrong entry count %zu, expected %zu\n", count, n-i);
        goto error;
      }
    }
    if(!DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
      fprintf(stderr, "Error 2: Prevously added entry %zu not found\n", i);
      goto error;
    }
    if(!DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _remove)(&container, key)){
      fprintf(stderr, "Error 3: Failed to remove entry %zu!\n", i);
      goto error;
    }
    if(DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
      fprintf(stderr, "Error 4: Entry %zu still present\n", i);
      goto error;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != n-i-1){
        fprintf(stderr, "Error 6: Wrong entry count %zu, expected %zu\n", count, n-i-1);
        goto error;
      }
    }
  }
  {
    size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
    if(count != 0){
      fprintf(stderr, "Error 7: Wrong entry count %zu, expected 0\n", count);
      goto error;
    }
  }
  return 0;
error:
  // DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _dump_hashmap_key_hashes)(&container); // This is only for debugging
  DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _clear)(&container);
  return 1;
}


#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
DPA_U_TESTCASE((DPA_U_STR_EVAL(DPA__U_SM_TYPE) "\t" "get and remove")){
  DPA__U_SM_TYPE container = {0};
  DPA__U_SM_KEY_TYPE key;
  size_t n = 0;
  for(size_t i=0; GET_RAND_ENTRY(&key, i); i++,n++){
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != i){
        fprintf(stderr, "Error 5: Wrong entry count %zu, expected %zu\n", count, i);
        goto error;
      }
    }
    int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _set)(&container, key, (dpa_u_any_value_t){.u64=i});
    if(result < 0){
      fprintf(stderr, "Error 1: Failed to add entry %zu\n", i);
      goto error;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != i+1){
        fprintf(stderr, "Error 6: Wrong entry count %zu, expected %zu\n", count, i+1);
        goto error;
      }
    }
  }
  for(size_t i=0; GET_RAND_ENTRY(&key, i); i++){
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != n-i){
        fprintf(stderr, "Error 6: Wrong entry count %zu, expected %zu\n", count, n-i);
        goto error;
      }
    }
    if(!DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
      fprintf(stderr, "Error 2: Prevously added entry %zu not found\n", i);
      goto error;
    }
    {
      const dpa_u_optional_t v = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get_and_remove)(&container, key);
      if(!v.present){
        fprintf(stderr, "Error 3: failed to get entry %zu, but check if it exists did succeed\n", i);
        goto error;
      }
      if(v.value.u64 != i){
        fprintf(stderr, "Error 4: value retrieved from entry %zu is wrong: %zu\n", i, v.value.u64);
        goto error;
      }
    }
    if(DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
      fprintf(stderr, "Error 5: Entry %zu still present\n", i);
      goto error;
    }
    {
      size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
      if(count != n-i-1){
        fprintf(stderr, "Error 6: Wrong entry count %zu, expected %zu\n", count, n-i-1);
        goto error;
      }
    }
  }
  {
    size_t count = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(&container);
    if(count != 0){
      fprintf(stderr, "Error 7: Wrong entry count %zu, expected 0\n", count);
      goto error;
    }
  }
  return 0;
error:
  // DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _dump_hashmap_key_hashes)(&container); // This is only for debugging
  DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _clear)(&container);
  return 1;
}
#endif

#endif
