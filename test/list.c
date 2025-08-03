#include <dpa/utils/list.h>
#include <dpa/utils/test.h>
#include <string.h>

DPA_U_TEST_MAIN

dpa_u_list(int) list;

void dpa_u_test_teardown(void){
  dpa_u_list_clear(&list);
}

DPA_U_TESTCASE("dpa_u_list_move\tempty lists"){
  dpa_u_list(int) a = {0};
  dpa_u_list(int) b = {0};
  dpa_u_list_move(&a, &b);
  if(a.ptr != 0 || b.ptr != 0)
    return 1;
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_move\tempty source list"){
  dpa_u_list(int) a = {0};
  dpa_u_list(int) b = {0};
  dpa_u_list_grow(&a, 10);
  dpa_u_list_move(&a, &b);
  if(a.ptr != 0 || b.ptr != 0)
    return 1;
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_move\tempty destination list"){
  dpa_u_list(int) a = {0};
  dpa_u_list(int) b = {0};
  dpa_u_list_grow(&b, 10);
  dpa_u_list_move(&a, &b);
  if(a.ptr == 0 || b.ptr != 0)
    return 1;
  dpa_u_list_clear(&a);
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_swap"){
  dpa_u_list(int) a = {(int*)0x10};
  dpa_u_list(int) b = {(int*)0x20};
  dpa_u_list_swap(&a, &b);
  if(a.ptr != (int*)0x20 || b.ptr != (int*)0x10)
    return 1;
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_append"){
  dpa_u_list_append(&list, 10, (int[]){ 1, 2, 3, 4, 5, 6, 7, 8, 9,10});
  dpa_u_list_append(&list, 10, (int[]){11,12,13,14,15,16,17,18,19,20});
  if(dpa_u_list_length(&list) != 20)
    dpa_u_abort("dpa_u_list_append: %s", "Expected list to be 20 entries long");
  int* data = dpa_u_list_data(&list);
  if(memcmp(data, (int[]){
     1, 2, 3, 4, 5, 6, 7, 8, 9,10,
    11,12,13,14,15,16,17,18,19,20
  }, sizeof(int[20])))
    dpa_u_abort("dpa_u_list_append: %s", "List didn't contain the expected data");
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_grow\tincreasing the length twice"){
  dpa_u_list_grow(&list, 10);
  if(dpa_u_list_length(&list) != 10)
    dpa_u_abort("dpa_u_list_grow: %s", "unexpected length");
  dpa_u_list_grow(&list, 20);
  if(dpa_u_list_length(&list) != 30)
    dpa_u_abort("dpa_u_list_grow: %s", "unexpected length");
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_grow\tzero initialization"){
  dpa_u_list_append(&list, 2, (int[]){ 1, 2 });
  dpa_u_list_shrink(&list, 1);
  dpa_u_list_grow(&list, 1);
  if(dpa_u_list_length(&list) != 2)
    dpa_u_abort("dpa_u_list_append: %s", "Expected list to be 2 entries long");
  int* data = dpa_u_list_data(&list);
  if(memcmp(data, (int[]){1, 0}, sizeof(int[2])))
    dpa_u_abort("dpa_u_list_append: %s", "List didn't contain the expected data");
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_shrink\tempty list"){
  dpa_u_list_shrink(&list, 10);
  if(list.ptr)
    dpa_u_abort("dpa_u_list_shrink: %s", "list pointer shouldn't be set");
  if(dpa_u_list_length(&list) != 0)
    dpa_u_abort("dpa_u_list_shrink: %s", "unexpected length");
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_shrink\tremove all elements"){
  dpa_u_list_grow(&list, 10);
  dpa_u_list_shrink(&list, 10);
  if(list.ptr)
    dpa_u_abort("dpa_u_list_shrink: %s", "list pointer shouldn't be set");
  if(dpa_u_list_length(&list) != 0)
    dpa_u_abort("dpa_u_list_shrink: %s", "unexpected length");
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_shrink\tremove more then all elements"){
  dpa_u_list_grow(&list, 10);
  dpa_u_list_shrink(&list, 20);
  if(list.ptr)
    dpa_u_abort("dpa_u_list_shrink: %s", "list pointer shouldn't be set");
  if(dpa_u_list_length(&list) != 0)
    dpa_u_abort("dpa_u_list_shrink: %s", "unexpected length");
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_shrink\tremove half the elements"){
  dpa_u_list_grow(&list, 512-sizeof(size_t)/sizeof(int));
  int lbsize_old = ((struct dpa__u_list_small*)dpa_u_list_data(&list))[-1].lbsize;
  dpa_u_list_shrink(&list, 256+128);
  if(dpa_u_list_length(&list) != 128-sizeof(size_t)/sizeof(int))
    dpa_u_abort("dpa_u_list_shrink: %s", "unexpected length");
  int lbsize_new = ((struct dpa__u_list_small*)dpa_u_list_data(&list))[-1].lbsize;
  if(lbsize_new >= lbsize_old)
    dpa_u_abort("dpa_u_list_shrink: %s", "allocated amount of memory wasn't reduced by a factor of 4");
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_clear\tempty list"){
  dpa_u_list_clear(&list);
  if(list.ptr)
    dpa_u_abort("dpa_u_list_shrink: %s", "list pointer shouldn't be set");
  if(dpa_u_list_length(&list) != 0)
    dpa_u_abort("dpa_u_list_shrink: %s", "unexpected length");
  return 0;
}

DPA_U_TESTCASE("dpa_u_list_clear\tnon-empty list"){
  dpa_u_list_grow(&list, 10);
  dpa_u_list_clear(&list);
  if(list.ptr)
    dpa_u_abort("dpa_u_list_shrink: %s", "list pointer shouldn't be set");
  if(dpa_u_list_length(&list) != 0)
    dpa_u_abort("dpa_u_list_shrink: %s", "unexpected length");
  return 0;
}
