//////////////////////////////////
//// Top section, common code ////
//////////////////////////////////
#ifndef DPA_U_T_SELF
#define DPA_U_T_SELF

#include <dpa/utils/test.h>
#include <dpa/utils/set.h>
#include <errno.h>
#include <stdio.h>

#define DPA__U_SM_TEMPLATE <test/set/add.c>
#define DPA__U_SM_KIND DPA__U_SM_KIND_SET
#include <dpa/utils/_set-and-map.generator>

#define DPA__U_SM_TEMPLATE <test/set/add.c>
#define DPA__U_SM_KIND DPA__U_SM_KIND_MAP
#include <dpa/utils/_set-and-map.generator>

uint_least8_t ul8[0x100];
uint_least16_t ul16[0x10000];
uint_least32_t ul32[0x10000];
uint_least64_t ul64[0x10000];

dpa_u_init static void init(void){
  FILE* f = fopen("build/unique-random", "rb");
  if(!f) dpa_u_abort("Failed to open build/unique-random: %d %s", errno, strerror(errno));
  fclose(f);
}

DPA_U_TEST_MAIN

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

DPA_U_TESTCASE((DPA_U_STR_EVAL(DPA__U_SM_TYPE) "\t" "add different")){
  return 1; // TODO
}

DPA_U_TESTCASE((DPA_U_STR_EVAL(DPA__U_SM_TYPE) "\t" "add twice")){
  return 1; // TODO
}

//////////////////////////////////////////////
#undef DPA__U_SM_TYPE
#undef DPA__U_SM_KEY_TYPE
#undef DPA__U_SM_NAME
#undef DPA__U_SM_PREFIX

#endif
