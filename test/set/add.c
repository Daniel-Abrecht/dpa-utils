//////////////////////////////////
//// Top section, common code ////
//////////////////////////////////
#ifndef DPA_U_T_SELF
#define DPA_U_T_SELF

#include <dpa/utils/test.h>
#include <dpa/utils/set.h>
#include <errno.h>
#include <stdio.h>

uint_least8_t ul8[0x100];
uint_least16_t ul16[0x10000];
uint_least32_t ul32[0x10000];
uint_least64_t ul64[0x10000];

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
  for(size_t i=0; i<m; i++)
    r[i] = hex2bin_byte(&x[i*2]);
}

void dpa__u_test_setup(void){
  FILE* f = fopen("build/unique-random", "rb");
  if(!f) dpa_u_abort("Failed to open build/unique-random: %d %s", errno, strerror(errno));
  unsigned char line[1024];
#define READ_NUMBERS(L) \
  for(size_t i=0; fgets((char*)line, sizeof(line), f) && line[0] != '\n'; i++){ \
    if(i>=sizeof(L)/sizeof(*L)) continue; \
    hex2bin(&L[i], sizeof(L[i]), line); \
  }
  READ_NUMBERS(ul8);
  READ_NUMBERS(ul16);
  READ_NUMBERS(ul32);
  READ_NUMBERS(ul64);
#undef READ_NUMBERS
}

DPA_U_TEST_MAIN

#define GET_RAND_ENTRY DPA_U_CONCAT_E(DPA__U_SM_PREFIX, __get_rand)

//////////////////////////////////////////////

#define DPA__U_SM_TEMPLATE <test/set/add.c>
#define DPA__U_SM_KIND DPA__U_SM_KIND_SET
#include <dpa/utils/_set-and-map.generator>

#define DPA__U_SM_TEMPLATE <test/set/add.c>
#define DPA__U_SM_KIND DPA__U_SM_KIND_MAP
#include <dpa/utils/_set-and-map.generator>

#else
//////////////////////////
//// Template section ////
//////////////////////////

#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
#define DPA__U_SM_PREFIX DPA_U_CONCAT_E(DPA_U_CONCAT_E(dpa_u_, DPA__U_SM_NAME), _set)
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#define DPA__U_SM_PREFIX DPA_U_CONCAT_E(DPA_U_CONCAT_E(dpa_u_, DPA__U_SM_NAME), _map)
#endif
#define DPA__U_SM_TYPE DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _t)
#undef DPA_U_TESTCASE_SUFFIX
#define DPA_U_TESTCASE_SUFFIX DPA_U_CONCAT_E(DPA__U_SM_PREFIX, __LINE__)

//////////////////////////////////////////////

#ifndef DPA__U_SM_BO
bool GET_RAND_ENTRY(DPA__U_SM_KEY_TYPE*const ret, size_t i){
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
  if(sizeof(DPA__U_SM_KEY_TYPE) >= sizeof(*ul64)){
    if(i >= sizeof(ul64)/sizeof(*ul64)) return false;
    *ret = (DPA__U_SM_KEY_TYPE)ul64[i];
    return true;
  }else if(sizeof(DPA__U_SM_KEY_TYPE) >= sizeof(*ul32)){
    if(i >= sizeof(ul32)/sizeof(*ul32)) return false;
    *ret = (DPA__U_SM_KEY_TYPE)ul32[i];
    return true;
  }else if(sizeof(DPA__U_SM_KEY_TYPE) >= sizeof(*ul16)){
    if(i >= sizeof(ul16)/sizeof(*ul16)) return false;
    *ret = (DPA__U_SM_KEY_TYPE)ul16[i];
    return true;
  }else{
    if(i >= sizeof(ul8)/sizeof(*ul8)) return false;
    *ret = (DPA__U_SM_KEY_TYPE)ul8[i];
    return true;
  }
#pragma GCC diagnostic pop
}

#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
DPA_U_TESTCASE((DPA_U_STR_EVAL(DPA__U_SM_TYPE) "\t" "add different")){
  DPA__U_SM_TYPE container = {0};
  DPA__U_SM_KEY_TYPE key;
  size_t j=0, k=0;
  bool done = false;
  while(!done){
    k = j;
    for(size_t i=0; i<50; i++,j++){
      if(!GET_RAND_ENTRY(&key, j)){
        done = true;
        break;
      }
      int result = DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _add)(&container, key);
      if(result < 0){
        fprintf(stderr, "Error: Failed to add entry\n");
        return 1;
      }
      if(result){
        fprintf(stderr, "Error: Entry was already present, but was never added\n");
        return 1;
      }
    }
    j = k;
    for(size_t i=0; i<50; i++,j++){
      if(!GET_RAND_ENTRY(&key, j))
        break;
      if(!DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
        fprintf(stderr, "Error: Prevously added entry not found\n");
        return 1;
      }
    }
    k = j;
    for(size_t i=0; i<50; i++,j++){
      if(!GET_RAND_ENTRY(&key, j))
        break;
      if(DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(&container, key)){
        fprintf(stderr, "Error: Entry found, but was never added\n");
        return 1;
      }
    }
    j = k;
  }
  return 0;
}
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#endif
#endif

/*
DPA_U_TESTCASE((DPA_U_STR_EVAL(DPA__U_SM_TYPE) "\t" "add twice")){
  return 1; // TODO
}*/

//////////////////////////////////////////////
#undef DPA__U_SM_TYPE
#undef DPA__U_SM_KEY_TYPE
#undef DPA__U_SM_NAME
#undef DPA__U_SM_PREFIX

#endif
