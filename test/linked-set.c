#ifndef PASS
#define PASS 1

#include <dpa/utils/linked-set.h>
#include <dpa/utils/tagged-pointer.h>
#include <dpa/utils/test.h>


DPA_U_TEST_MAIN

#define expect(COND) \
  if(!(COND)) \
    dpa_u_abort("%s", #COND)

#define FIRST v.p[0]
#define LAST  v.p[1]
#define NEXT    p[0]
#define PREV    p[1]


#elif PASS < 3

#if PASS == 1
#undef PASS
#define PASS 2

#define only_s(EXPR)
#define only_p(EXPR) EXPR
#define expect_s(COND)
#define expect_p(COND) expect(COND)

#define T_SET   dpa_u_linked_set_p_t
#define T_ENTRY dpa_u_linked_set_p_entry_t

#undef DPA_U_TESTCASE_SUFFIX
#define DPA_U_TESTCASE_SUFFIX DPA_U_CONCAT_E(p_, __LINE__)

#elif PASS == 2
#undef PASS
#define PASS 3

#define only_s(EXPR) EXPR
#define only_p(EXPR)
#define expect_s(COND) expect(COND)
#define expect_p(COND)

#define T_SET   dpa_u_linked_set_s_t
#define T_ENTRY dpa_u_linked_set_s_entry_t

#undef DPA_U_TESTCASE_SUFFIX
#define DPA_U_TESTCASE_SUFFIX DPA_U_CONCAT_E(s_, __LINE__)

#endif

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadd one entry to set"){
  T_SET set = {0};
  T_ENTRY e = {0};
  expect(dpa_u_linked_set_set(&set, &e, 0) == true);
  expect(set.FIRST == (uintptr_t)&e);
  expect(set.LAST == (uintptr_t)&e);
  expect_p(set.length == 1);
  expect_p(e.set == &set);
  expect_s(e.PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect_s(e.NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadd 3 entries to end of set"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  expect(dpa_u_linked_set_set(&set, &e[0], 0) == true);
  expect_p(e[0].set == &set);
  expect(set.FIRST == (uintptr_t)&e[0]);
  expect(set.LAST == (uintptr_t)&e[0]);
  expect_p(set.length == 1);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect_s(e[0].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect(dpa_u_linked_set_set(&set, &e[1], 0) == true);
  expect_p(e[1].set == &set);
  expect(set.FIRST == (uintptr_t)&e[0]);
  expect(set.LAST == (uintptr_t)&e[1]);
  expect_p(set.length == 2);
  expect_s(e[1].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(dpa_u_linked_set_set(&set, &e[2], 0) == true);
  expect_p(e[2].set == &set);
  expect(set.FIRST == (uintptr_t)&e[0]);
  expect(set.LAST == (uintptr_t)&e[2]);
  expect_p(set.length == 3);
  expect(e[2].PREV == (uintptr_t)&e[1]);
  expect(e[1].NEXT == (uintptr_t)&e[2]);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect_s(e[2].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadd 3 entries to beginning of set"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  expect(dpa_u_linked_set_set(&set, &e[2], dpa_u_linked_set_get_first(set)) == true);
  expect(dpa_u_linked_set_set(&set, &e[1], dpa_u_linked_set_get_first(set)) == true);
  expect(dpa_u_linked_set_set(&set, &e[0], dpa_u_linked_set_get_first(set)) == true);
  expect(set.FIRST == (uintptr_t)&e[0]);
  expect(set.LAST == (uintptr_t)&e[2]);
  expect_p(set.length == 3);
  expect_p(e[0].set == &set);
  expect_p(e[1].set == &set);
  expect_p(e[2].set == &set);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect_s(e[2].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tremove only entry from set"){
  T_SET set = {0};
  T_ENTRY e = {0};
  set.FIRST = (uintptr_t)&e;
  set.LAST = (uintptr_t)&e;
  only_p(set.length = 1);
  only_p(e.set = &set);
  only_s(e.NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_s(e.PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  expect(dpa_u_linked_set_set(0, &e, 0) == true);
  expect(set.FIRST == 0);
  expect(set.LAST == 0);
  expect_p(set.length == 0);
  expect_p(e.set == 0);
  expect(e.NEXT == 0);
  expect(e.PREV == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tmove only entry from one set to another"){
  T_SET set = {0};
  T_SET set2 = {0};
  T_ENTRY e = {0};
  set.FIRST = (uintptr_t)&e;
  set.LAST = (uintptr_t)&e;
  only_p(set.length = 1);
  only_p(e.set = &set);
  only_s(e.NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_s(e.PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  expect(dpa_u_linked_set_set(&set2, &e, 0) == true);
  expect(set.FIRST == 0);
  expect(set.LAST == 0);
  expect_p(set.length == 0);
  expect_p(set2.length == 1);
  expect_p(e.set == &set2);
  expect(set2.FIRST == (uintptr_t)&e);
  expect(set2.LAST == (uintptr_t)&e);
  expect_s(e.NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set2.v));
  expect_s(e.PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set2.v));
  expect_p(e.NEXT == 0);
  expect_p(e.PREV == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tmove first entry from one set to another"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];

  T_SET set2 = {0};
  expect(dpa_u_linked_set_set(&set2, &e[0], 0) == true);
  expect(set.FIRST == (uintptr_t)&e[1]);
  expect(set.LAST == (uintptr_t)&e[2]);
  expect_p(set.length == 2);
  expect_p(set2.length == 1);
  expect_p(e[0].set == &set2);
  expect_p(e[1].set == &set);
  expect_p(e[2].set == &set);
  expect(set2.FIRST == (uintptr_t)&e[0]);
  expect(set2.LAST == (uintptr_t)&e[0]);
  expect_s(e[0].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set2.v));
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set2.v));
  expect_p(e[0].NEXT == 0);
  expect_p(e[0].PREV == 0);
  expect_s(e[1].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect_p(e[0].PREV == 0);
  expect(e[1].NEXT == (uintptr_t)&e[2]);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tmove last entry from one set to another"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];

  T_SET set2 = {0};
  expect(dpa_u_linked_set_set(&set2, &e[2], 0) == true);
  expect(set.FIRST == (uintptr_t)&e[0]);
  expect(set.LAST == (uintptr_t)&e[1]);
  expect_p(set.length == 2);
  expect_p(set2.length == 1);
  expect_p(e[0].set == &set);
  expect_p(e[1].set == &set);
  expect_p(e[2].set == &set2);
  expect(set2.FIRST == (uintptr_t)&e[2]);
  expect(set2.LAST == (uintptr_t)&e[2]);
  expect_s(e[2].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set2.v));
  expect_s(e[2].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set2.v));
  expect_p(e[2].NEXT == 0);
  expect_p(e[2].PREV == 0);
  expect_s(e[1].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect_p(e[1].NEXT == 0);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  return 0;
}


DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tmove middle entry from one set to another"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];

  T_SET set2 = {0};
  expect(dpa_u_linked_set_set(&set2, &e[1], 0) == true);
  expect(set.FIRST == (uintptr_t)&e[0]);
  expect(set.LAST == (uintptr_t)&e[2]);
  expect_p(set.length == 2);
  expect_p(set2.length == 1);
  expect_p(e[0].set == &set);
  expect_p(e[1].set == &set2);
  expect_p(e[2].set == &set);
  expect(set2.FIRST == (uintptr_t)&e[1]);
  expect(set2.LAST == (uintptr_t)&e[1]);
  expect_s(e[1].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set2.v));
  expect_s(e[1].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set2.v));
  expect_p(e[1].NEXT == 0);
  expect_p(e[1].PREV == 0);
  expect_s(e[2].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect_p(e[2].NEXT == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect_p(e[0].PREV == 0);
  expect(e[0].NEXT == (uintptr_t)&e[2]);
  expect(e[2].PREV == (uintptr_t)&e[0]);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadding an entry before a detached one with no set specified must fail, and the entry must stay unmodified"){
  T_SET set = {0};
  T_ENTRY e = {0};
  set.FIRST = (uintptr_t)&e;
  set.LAST = (uintptr_t)&e;
  only_p(set.length = 1);
  only_p(e.set = &set);
  only_s(e.NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_s(e.PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  expect(dpa_u_linked_set_set(0, &e, &(T_ENTRY){0}) == false);
  expect(set.FIRST == (uintptr_t)&e);
  expect(set.LAST == (uintptr_t)&e);
  expect_p(set.length == 1);
  expect_p(e.set == &set);
  expect_s(e.NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect_s(e.PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadding an entry before a detached one with a set specified must fail, and the entry must stay unmodified"){
  T_SET set = {0};
  T_ENTRY e = {0};
  set.FIRST = (uintptr_t)&e;
  set.LAST = (uintptr_t)&e;
  only_p(set.length = 1);
  only_p(e.set = &set);
  only_s(e.NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_s(e.PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  expect(dpa_u_linked_set_set(&set, &e, &(T_ENTRY){0}) == false);
  expect(set.FIRST == (uintptr_t)&e);
  expect(set.LAST == (uintptr_t)&e);
  expect_p(set.length == 1);
  expect_p(e.set == &set);
  expect_s(e.NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect_s(e.PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadding an entry before one from a different set must fail if the former set is empty"){
  T_SET set = {0};
  T_ENTRY e = {0};
  set.FIRST = (uintptr_t)&e;
  set.LAST = (uintptr_t)&e;
  only_p(set.length = 1);
  only_p(e.set = &set);
  only_s(e.NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_s(e.PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  expect(dpa_u_linked_set_set(&(T_SET){0}, &(T_ENTRY){0}, &e) == false);
  return 0;
}

#if PASS == 2
// Note: this will fail for dpa_u_linked_set_s_t. Checking this would require traversing the whole list until the list head is found, which would be inefficient.
DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadding an entry before one from a different set must fail if the former set is not empty"){
  T_SET sa = {0};
  T_ENTRY a = {0};
  sa.FIRST = (uintptr_t)&a;
  sa.LAST = (uintptr_t)&a;
  only_p(sa.length = 1);
  only_p(a.set = &sa);
  only_s(a.NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&sa.v);
  only_s(a.PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&sa.v);

  T_SET sb = {0};
  T_ENTRY b = {0};
  sb.FIRST = (uintptr_t)&b;
  sb.LAST = (uintptr_t)&b;
  only_p(sb.length = 1);
  only_p(b.set = &sb);
  only_s(b.NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&sb.v);
  only_s(b.PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&sb.v);

  expect(dpa_u_linked_set_set(&sa, &a, &b) == false);
  return 0;
}
#endif

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tremove all 3 entries from set, starting with the first"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];
  expect(dpa_u_linked_set_set(0, &e[0], 0) == true);
  expect_p(e[0].set == 0);
  expect(e[0].NEXT == 0);
  expect(e[0].PREV == 0);
  expect(set.FIRST == (uintptr_t)&e[1]);
  expect(set.LAST == (uintptr_t)&e[2]);
  expect_p(set.length == 2);
  expect_p(e[1].PREV == 0);
  expect_s(e[1].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect(dpa_u_linked_set_set(0, &e[1], 0) == true);
  expect_p(e[1].set == 0);
  expect(e[1].NEXT == 0);
  expect(e[1].PREV == 0);
  expect(set.FIRST == (uintptr_t)&e[2]);
  expect(set.LAST == (uintptr_t)&e[2]);
  expect_p(set.length == 1);
  expect_p(e[2].PREV == 0);
  expect_s(e[2].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect(dpa_u_linked_set_set(0, &e[2], 0) == true);
  expect_p(e[2].set == 0);
  expect(e[2].NEXT == 0);
  expect(e[2].PREV == 0);
  expect(set.FIRST == 0);
  expect(set.LAST == 0);
  expect_p(set.length == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tremove all 3 entries from set, starting with last"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];
  expect(dpa_u_linked_set_set(0, &e[2], 0) == true);
  expect_p(e[2].set == 0);
  expect(e[2].NEXT == 0);
  expect(e[2].PREV == 0);
  expect_p(e[1].NEXT == 0);
  expect_s(e[1].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect(set.FIRST == (uintptr_t)&e[0]);
  expect(set.LAST == (uintptr_t)&e[1]);
  expect_p(set.length == 2);
  expect(dpa_u_linked_set_set(0, &e[1], 0) == true);
  expect_p(e[1].set == 0);
  expect(e[1].NEXT == 0);
  expect(e[1].PREV == 0);
  expect(set.FIRST == (uintptr_t)&e[0]);
  expect(set.LAST == (uintptr_t)&e[0]);
  expect_p(set.length == 1);
  expect_p(e[0].NEXT == 0);
  expect_s(e[0].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v));
  expect(dpa_u_linked_set_set(0, &e[0], 0) == true);
  expect_p(e[0].set == 0);
  expect(e[0].NEXT == 0);
  expect(e[0].PREV == 0);
  expect(set.FIRST == 0);
  expect(set.LAST == 0);
  expect_p(set.length == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tof 3 entries, remove the middle one"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];
  expect(dpa_u_linked_set_set(0, &e[1], 0) == true);
  expect_p(e[1].set == 0);
  expect(e[1].NEXT == 0);
  expect(e[1].PREV == 0);
  expect(set.FIRST == (uintptr_t)&e[0]);
  expect(set.LAST == (uintptr_t)&e[2]);
  expect_p(set.length == 2);
  expect(e[0].NEXT == (uintptr_t)&e[2]);
  expect(e[2].PREV == (uintptr_t)&e[0]);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadd entry between 2 other entries, set implicit"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 2);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[2];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[0];
  expect(dpa_u_linked_set_set(0, &e[1], &e[2]) == true);
  expect_p(e[1].set == &set);
  expect(e[1].NEXT == (uintptr_t)&e[2]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[2].PREV == (uintptr_t)&e[1]);
  expect(set.FIRST == (uintptr_t)&e[0]);
  expect(set.LAST == (uintptr_t)&e[2]);
  expect_p(set.length == 3);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadd entry between 2 other entries, set explicit"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 2);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[2];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[0];
  expect(dpa_u_linked_set_set(&set, &e[1], &e[2]) == true);
  expect_p(e[1].set == &set);
  expect(e[1].NEXT == (uintptr_t)&e[2]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[2].PREV == (uintptr_t)&e[1]);
  expect(set.FIRST == (uintptr_t)&e[0]);
  expect(set.LAST == (uintptr_t)&e[2]);
  expect_p(set.length == 3);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_first\tset with entries"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];
  expect(dpa_u_linked_set_get_first(&set) == &e[0]);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_last\tset with entries"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];
  expect(dpa_u_linked_set_get_last(&set) == &e[2]);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_next\tentries other than the last one"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];
  expect(dpa_u_linked_set_get_next(e[0]) == &e[1]);
  expect(dpa_u_linked_set_get_next(&e[1]) == &e[2]);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_next\tlast entry"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];
  expect(dpa_u_linked_set_get_next(e[2]) == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_next\tdisconnected entry"){
  expect(dpa_u_linked_set_get_next((T_ENTRY){0}) == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_previous\tentries other than the first one"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];
  expect(dpa_u_linked_set_get_previous(&e[2]) == &e[1]);
  expect(dpa_u_linked_set_get_previous(e[1]) == &e[0]);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_previous\tfirst entry"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];
  expect(dpa_u_linked_set_get_previous(e[0]) == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_previous\tdisconnected entry"){
  expect(dpa_u_linked_set_get_previous((T_ENTRY){0}) == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_first\tempty set"){
  T_SET set = {0};
  expect(dpa_u_linked_set_get_first(&set) == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_last\tempty set"){
  T_SET set = {0};
  expect(dpa_u_linked_set_get_last(&set) == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_first\tconst set -> const entry"){
  expect(_Generic(dpa_u_linked_set_get_first((T_SET){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 2);
  expect(_Generic(dpa_u_linked_set_get_first((const T_SET){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 1);
  expect(_Generic(dpa_u_linked_set_get_first(&(T_SET){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 2);
  expect(_Generic(dpa_u_linked_set_get_first(&(const T_SET){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 1);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_last\tconst set -> const entry"){
  expect(_Generic(dpa_u_linked_set_get_last((T_SET){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 2);
  expect(_Generic(dpa_u_linked_set_get_last((const T_SET){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 1);
  expect(_Generic(dpa_u_linked_set_get_last(&(T_SET){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 2);
  expect(_Generic(dpa_u_linked_set_get_last(&(const T_SET){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 1);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_previous\tconst -> const"){
  expect(_Generic(dpa_u_linked_set_get_previous((T_ENTRY){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 2);
  expect(_Generic(dpa_u_linked_set_get_previous((const T_ENTRY){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 1);
  expect(_Generic(dpa_u_linked_set_get_previous(&(T_ENTRY){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 2);
  expect(_Generic(dpa_u_linked_set_get_previous(&(const T_ENTRY){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 1);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_get_next\tconst -> const"){
  expect(_Generic(dpa_u_linked_set_get_next((T_ENTRY){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 2);
  expect(_Generic(dpa_u_linked_set_get_next((const T_ENTRY){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 1);
  expect(_Generic(dpa_u_linked_set_get_next(&(T_ENTRY){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 2);
  expect(_Generic(dpa_u_linked_set_get_next(&(const T_ENTRY){0}), const T_ENTRY*: 1, T_ENTRY*: 2) == 1);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_clear\tset already clear"){
  T_SET set = {0};
  dpa_u_linked_set_clear(&set);
  expect(set.FIRST == 0);
  expect(set.LAST == 0);
  expect_p(set.length == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_clear\tset has 1 entry"){
  T_SET set = {0};
  T_ENTRY e = {0};
  set.FIRST = (uintptr_t)&e;
  set.LAST = (uintptr_t)&e;
  only_p(set.length = 1);
  only_p(e.set = &set);
  only_s(e.NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_s(e.PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  dpa_u_linked_set_clear(&set);
  expect(set.FIRST == 0);
  expect(set.LAST == 0);
  expect_p(set.length == 0);
  expect_p(e.set == 0);
  expect(e.NEXT == 0);
  expect(e.PREV == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_clear\tset has 3 entries"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];
  dpa_u_linked_set_clear(&set);
  expect(set.FIRST == 0);
  expect(set.LAST == 0);
  expect_p(set.length == 0);
  expect_p(e[0].set == 0);
  expect(e[0].NEXT == 0);
  expect(e[0].PREV == 0);
  expect_p(e[1].set == 0);
  expect(e[1].NEXT == 0);
  expect(e[1].PREV == 0);
  expect_p(e[2].set == 0);
  expect(e[2].NEXT == 0);
  expect(e[2].PREV == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tclear entries: set already clear"){
  T_SET set = {0};
  expect(dpa_u_linked_set_move(0, &set, 0) == true);
  expect(set.FIRST == 0);
  expect(set.LAST == 0);
  expect_p(set.length == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tclear entries: set has 1 entry"){
  T_SET set = {0};
  T_ENTRY e = {0};
  set.FIRST = (uintptr_t)&e;
  set.LAST = (uintptr_t)&e;
  only_p(set.length = 1);
  only_p(e.set = &set);
  only_s(e.NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_s(e.PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  expect(dpa_u_linked_set_move(0, &set, 0) == true);
  expect(set.FIRST == 0);
  expect(set.LAST == 0);
  expect_p(set.length == 0);
  expect_p(e.set == 0);
  expect(e.NEXT == 0);
  expect(e.PREV == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tclear entries: set has 3 entries"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.FIRST = (uintptr_t)&e[0];
  set.LAST = (uintptr_t)&e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  only_p(e[1].set = &set);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &set);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set.v);
  e[2].PREV = (uintptr_t)&e[1];
  expect(dpa_u_linked_set_move(0, &set, 0) == true);
  expect(set.FIRST == 0);
  expect(set.LAST == 0);
  expect_p(set.length == 0);
  expect_p(e[0].set == 0);
  expect(e[0].NEXT == 0);
  expect(e[0].PREV == 0);
  expect_p(e[1].set == 0);
  expect(e[1].NEXT == 0);
  expect(e[1].PREV == 0);
  expect_p(e[2].set == 0);
  expect(e[2].NEXT == 0);
  expect(e[2].PREV == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove empty set to empty set"){
  T_SET src = {0};
  T_SET dst = {0};
  expect(dpa_u_linked_set_move(&dst, &src, 0) == true);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  expect_p(src.length == 0);
  expect(dst.FIRST == 0);
  expect(dst.LAST == 0);
  expect_p(dst.length == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove empty set to empty set, before entry from neither set, should fail"){
  T_SET src = {0};
  T_SET dst = {0};
  expect(dpa_u_linked_set_move(&dst, &src, &(T_ENTRY){0}) == false);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  expect_p(src.length == 0);
  expect(dst.FIRST == 0);
  expect(dst.LAST == 0);
  expect_p(dst.length == 0);
  return 0;
}


DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove source set with 1 entry to empty set"){
  T_SET dst = {0};
  T_ENTRY e = {0};

  T_SET src = {0};
  only_s(e.PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(e.set = &src);
  only_s(e.NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(src.length = 1);
  src.FIRST = (uintptr_t)&e;
  src.LAST = (uintptr_t)&e;

  expect(dpa_u_linked_set_move(&dst, &src, 0) == true);
  expect_p(e.set == &dst);
  expect_p(e.PREV == 0);
  expect_s(e.PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_s(e.NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e.NEXT == 0);
  expect(dst.FIRST == (uintptr_t)&e);
  expect(dst.LAST == (uintptr_t)&e);
  expect_p(dst.length == 1);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}


DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove source set with 3 entries to empty set"){
  T_SET dst = {0};
  T_ENTRY e[3] = {0};

  T_SET src = {0};
  src.FIRST = (uintptr_t)&e[0];
  src.LAST = (uintptr_t)&e[2];
  only_p(src.length = 3);
  only_p(e[0].set = &src);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(e[1].set = &src);
  e[1].NEXT = (uintptr_t)&e[2];
  e[1].PREV = (uintptr_t)&e[0];
  only_p(e[2].set = &src);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  e[2].PREV = (uintptr_t)&e[1];

  expect(dpa_u_linked_set_move(&dst, &src, 0) == true);
  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[2].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(e[1].NEXT == (uintptr_t)&e[2]);
  expect(e[2].PREV == (uintptr_t)&e[1]);
  expect_s(e[2].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[2].NEXT == 0);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[2]);
  expect_p(dst.length == 3);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}


DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove source set with 3 entries to middle of destination set, destination set explicit"){
  T_SET dst = {0};
  T_ENTRY e[5] = {0};
  dst.FIRST = (uintptr_t)&e[0];
  dst.LAST = (uintptr_t)&e[4];
  only_p(dst.length = 2);
  only_p(e[0].set = &dst);
  e[0].NEXT = (uintptr_t)&e[4];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  only_p(e[4].set = &dst);
  only_s(e[4].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  e[4].PREV = (uintptr_t)&e[0];

  T_SET src = {0};
  src.FIRST = (uintptr_t)&e[1];
  src.LAST = (uintptr_t)&e[3];
  only_p(src.length = 3);
  only_p(e[1].set = &src);
  e[1].NEXT = (uintptr_t)&e[2];
  only_s(e[1].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(e[2].set = &src);
  e[2].NEXT = (uintptr_t)&e[3];
  e[2].PREV = (uintptr_t)&e[1];
  only_p(e[3].set = &src);
  only_s(e[3].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  e[3].PREV = (uintptr_t)&e[2];

  expect(dpa_u_linked_set_move(&dst, &src, &e[4]) == true);
  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[2].set == &dst);
  expect_p(e[3].set == &dst);
  expect_p(e[4].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(e[1].NEXT == (uintptr_t)&e[2]);
  expect(e[2].PREV == (uintptr_t)&e[1]);
  expect(e[2].NEXT == (uintptr_t)&e[3]);
  expect(e[3].PREV == (uintptr_t)&e[2]);
  expect(e[3].NEXT == (uintptr_t)&e[4]);
  expect(e[4].PREV == (uintptr_t)&e[3]);
  expect_s(e[4].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[4].NEXT == 0);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[4]);
  expect_p(dst.length == 5);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}


DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove source set with 1 entry to middle of destination set, destination set implicit"){
  T_SET dst = {0};
  T_ENTRY e[3] = {0};
  dst.FIRST = (uintptr_t)&e[0];
  dst.LAST = (uintptr_t)&e[2];
  only_p(dst.length = 2);
  only_p(e[0].set = &dst);
  e[0].NEXT = (uintptr_t)&e[2];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  only_p(e[2].set = &dst);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  e[2].PREV = (uintptr_t)&e[0];

  T_SET src = {0};
  only_s(e[1].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(e[1].set = &src);
  only_s(e[1].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(src.length = 1);
  src.FIRST = (uintptr_t)&e[1];
  src.LAST = (uintptr_t)&e[1];

  expect(dpa_u_linked_set_move(0, &src, &e[2]) == true);
  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[2].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(e[1].NEXT == (uintptr_t)&e[2]);
  expect(e[2].PREV == (uintptr_t)&e[1]);
  expect_s(e[2].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[2].NEXT == 0);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[2]);
  expect_p(dst.length == 3);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}


DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove source set with 1 entry to middle of destination set, destination set explicit"){
  T_SET dst = {0};
  T_ENTRY e[3] = {0};
  dst.FIRST = (uintptr_t)&e[0];
  dst.LAST = (uintptr_t)&e[2];
  only_p(dst.length = 2);
  only_p(e[0].set = &dst);
  e[0].NEXT = (uintptr_t)&e[2];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  only_p(e[2].set = &dst);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  e[2].PREV = (uintptr_t)&e[0];

  T_SET src = {0};
  only_s(e[1].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(e[1].set = &src);
  only_s(e[1].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(src.length = 1);
  src.FIRST = (uintptr_t)&e[1];
  src.LAST = (uintptr_t)&e[1];

  expect(dpa_u_linked_set_move(&dst, &src, &e[2]) == true);
  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[2].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(e[1].NEXT == (uintptr_t)&e[2]);
  expect(e[2].PREV == (uintptr_t)&e[1]);
  expect_s(e[2].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[2].NEXT == 0);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[2]);
  expect_p(dst.length == 3);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove source set with 1 entry to start of destination set, destination set explicit"){
  T_SET dst = {0};
  T_ENTRY e[3] = {0};
  dst.FIRST = (uintptr_t)&e[1];
  dst.LAST = (uintptr_t)&e[2];
  only_p(dst.length = 2);
  only_p(e[1].set = &dst);
  e[1].NEXT = (uintptr_t)&e[2];
  only_s(e[1].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  only_p(e[2].set = &dst);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  e[2].PREV = (uintptr_t)&e[1];

  T_SET src = {0};
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(e[0].set = &src);
  only_s(e[0].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(src.length = 1);
  src.FIRST = (uintptr_t)&e[0];
  src.LAST = (uintptr_t)&e[0];

  expect(dpa_u_linked_set_move(&dst, &src, &e[1]) == true);

  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[2].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(e[1].NEXT == (uintptr_t)&e[2]);
  expect(e[2].PREV == (uintptr_t)&e[1]);
  expect_s(e[2].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[2].NEXT == 0);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[2]);
  expect_p(dst.length == 3);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}


DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove source set with 1 entry to start of destination set, destination set implicit"){
  T_SET dst = {0};
  T_ENTRY e[3] = {0};
  dst.FIRST = (uintptr_t)&e[1];
  dst.LAST = (uintptr_t)&e[2];
  only_p(dst.length = 2);
  only_p(e[1].set = &dst);
  e[1].NEXT = (uintptr_t)&e[2];
  only_s(e[1].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  only_p(e[2].set = &dst);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  e[2].PREV = (uintptr_t)&e[1];

  T_SET src = {0};
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(e[0].set = &src);
  only_s(e[0].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(src.length = 1);
  src.FIRST = (uintptr_t)&e[0];
  src.LAST = (uintptr_t)&e[0];

  expect(dpa_u_linked_set_move(0, &src, &e[1]) == true);

  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[2].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(e[1].NEXT == (uintptr_t)&e[2]);
  expect(e[2].PREV == (uintptr_t)&e[1]);
  expect_s(e[2].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[2].NEXT == 0);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[2]);
  expect_p(dst.length == 3);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}


DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove source set with 1 entry to end of destination set"){
  T_SET dst = {0};
  T_ENTRY e[3] = {0};
  dst.FIRST = (uintptr_t)&e[0];
  dst.LAST = (uintptr_t)&e[1];
  only_p(dst.length = 2);
  only_p(e[0].set = &dst);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  only_p(e[1].set = &dst);
  only_s(e[1].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  e[1].PREV = (uintptr_t)&e[0];

  T_SET src = {0};
  only_s(e[2].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(e[2].set = &src);
  only_s(e[2].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&src.v);
  only_p(src.length = 1);
  src.FIRST = (uintptr_t)&e[2];
  src.LAST = (uintptr_t)&e[2];

  expect(dpa_u_linked_set_move(&dst, &src, 0) == true);

  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[2].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(e[1].NEXT == (uintptr_t)&e[2]);
  expect(e[2].PREV == (uintptr_t)&e[1]);
  expect_s(e[2].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[2].NEXT == 0);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[2]);
  expect_p(dst.length == 3);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}


DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove empty source set entries to start of destination set, destination set explicit"){
  T_SET dst = {0};
  T_ENTRY e[2] = {0};
  dst.FIRST = (uintptr_t)&e[0];
  dst.LAST = (uintptr_t)&e[1];
  only_p(dst.length = 2);
  only_p(e[0].set = &dst);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  only_p(e[1].set = &dst);
  only_s(e[1].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  e[1].PREV = (uintptr_t)&e[0];
  T_SET src = {0};
  expect(dpa_u_linked_set_move(&dst, &src, &e[0]) == true);
  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_s(e[1].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[1].NEXT == 0);
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[1]);
  expect_p(dst.length == 2);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove empty source set entries to start of destination set, destination set implicit"){
  T_SET dst = {0};
  T_ENTRY e[2] = {0};
  dst.FIRST = (uintptr_t)&e[0];
  dst.LAST = (uintptr_t)&e[1];
  only_p(dst.length = 2);
  only_p(e[0].set = &dst);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  only_p(e[1].set = &dst);
  only_s(e[1].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  e[1].PREV = (uintptr_t)&e[0];
  T_SET src = {0};
  expect(dpa_u_linked_set_move(0, &src, &e[0]) == true);
  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_s(e[1].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[1].NEXT == 0);
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[1]);
  expect_p(dst.length == 2);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove empty source set entries to middle of destination set, destination set explicit"){
  T_SET dst = {0};
  T_ENTRY e[2] = {0};
  dst.FIRST = (uintptr_t)&e[0];
  dst.LAST = (uintptr_t)&e[1];
  only_p(dst.length = 2);
  only_p(e[0].set = &dst);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  only_p(e[1].set = &dst);
  only_s(e[1].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  e[1].PREV = (uintptr_t)&e[0];
  T_SET src = {0};
  expect(dpa_u_linked_set_move(&dst, &src, &e[0]) == true);
  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_s(e[1].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[1].NEXT == 0);
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[1]);
  expect_p(dst.length == 2);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove empty source set entries to middle of destination set, destination set implicit"){
  T_SET dst = {0};
  T_ENTRY e[2] = {0};
  dst.FIRST = (uintptr_t)&e[0];
  dst.LAST = (uintptr_t)&e[1];
  only_p(dst.length = 2);
  only_p(e[0].set = &dst);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  only_p(e[1].set = &dst);
  only_s(e[1].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  e[1].PREV = (uintptr_t)&e[0];
  T_SET src = {0};
  expect(dpa_u_linked_set_move(0, &src, &e[1]) == true);
  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_s(e[1].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[1].NEXT == 0);
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[1]);
  expect_p(dst.length == 2);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}


DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_move\tmove empty source set entries to end of destination set"){
  T_SET dst = {0};
  T_ENTRY e[2] = {0};
  dst.FIRST = (uintptr_t)&e[0];
  dst.LAST = (uintptr_t)&e[1];
  only_p(dst.length = 2);
  only_p(e[0].set = &dst);
  e[0].NEXT = (uintptr_t)&e[1];
  only_s(e[0].PREV = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  only_p(e[1].set = &dst);
  only_s(e[1].NEXT = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v);
  e[1].PREV = (uintptr_t)&e[0];
  T_SET src = {0};
  expect(dpa_u_linked_set_move(&dst, &src, 0) == true);
  expect_p(e[0].set == &dst);
  expect_p(e[1].set == &dst);
  expect_p(e[0].PREV == 0);
  expect_s(e[0].PREV == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_s(e[1].NEXT == (DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst.v));
  expect_p(e[1].NEXT == 0);
  expect(e[0].NEXT == (uintptr_t)&e[1]);
  expect(e[1].PREV == (uintptr_t)&e[0]);
  expect(dst.FIRST == (uintptr_t)&e[0]);
  expect(dst.LAST == (uintptr_t)&e[1]);
  expect_p(dst.length == 2);
  expect_p(src.length == 0);
  expect(src.FIRST == 0);
  expect(src.LAST == 0);
  return 0;
}




#undef only_s
#undef only_p
#undef expect_s
#undef expect_p
#undef T_SET
#undef T_ENTRY

#else
#undef PASS
#define PASS 1000
#endif
#if PASS < 1000
#include __FILE__
#endif
