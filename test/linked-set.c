#ifndef PASS
#define PASS 1

#include <dpa/utils/linked-set.h>
#include <dpa/utils/test.h>

DPA_U_TEST_MAIN

#define expect(COND) \
  if(!(COND)) \
    dpa_u_abort("%s", #COND)

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
  expect(set.v.previous == &e);
  expect(set.v.next == &e);
  expect_p(set.length == 1);
  expect_p(e.set == &set);
  expect_s(e.previous == &set.v);
  expect_s(e.next == &set.v);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadd 3 entries to end of set"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  expect(dpa_u_linked_set_set(&set, &e[0], 0) == true);
  expect_p(e[0].set == &set);
  expect(set.v.previous == &e[0]);
  expect(set.v.next == &e[0]);
  expect_p(set.length == 1);
  expect_s(e[0].previous == &set.v);
  expect_s(e[0].next == &set.v);
  expect(dpa_u_linked_set_set(&set, &e[1], 0) == true);
  expect_p(e[1].set == &set);
  expect(set.v.previous == &e[0]);
  expect(set.v.next == &e[1]);
  expect_p(set.length == 2);
  expect_s(e[1].next == &set.v);
  expect(e[1].previous == &e[0]);
  expect(e[0].next == &e[1]);
  expect(dpa_u_linked_set_set(&set, &e[2], 0) == true);
  expect_p(e[2].set == &set);
  expect(set.v.previous == &e[0]);
  expect(set.v.next == &e[2]);
  expect_p(set.length == 3);
  expect(e[2].previous == &e[1]);
  expect(e[1].next == &e[2]);
  expect_s(e[0].previous == &set.v);
  expect_s(e[2].next == &set.v);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadd 3 entries to beginning of set"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  expect(dpa_u_linked_set_set(&set, &e[2], set.v.previous) == true);
  expect(dpa_u_linked_set_set(&set, &e[1], set.v.previous) == true);
  expect(dpa_u_linked_set_set(&set, &e[0], set.v.previous) == true);
  expect(set.v.previous == &e[0]);
  expect(set.v.next == &e[2]);
  expect_p(set.length == 3);
  expect_p(e[0].set == &set);
  expect_p(e[1].set == &set);
  expect_p(e[2].set == &set);
  expect_s(e[0].previous == &set.v);
  expect_s(e[2].next == &set.v);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tremove only entry from set"){
  T_SET set = {0};
  T_ENTRY e = {0};
  set.v.previous = &e;
  set.v.next = &e;
  only_p(set.length = 1);
  only_p(e.set = &set);
  only_s(e.next = &set.v);
  only_s(e.previous = &set.v);
  expect(dpa_u_linked_set_set(0, &e, 0) == true);
  expect(set.v.previous == 0);
  expect(set.v.next == 0);
  expect_p(set.length == 0);
  expect_p(e.set == 0);
  expect(e.next == 0);
  expect(e.previous == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tremove all 3 entries from set, starting with the first"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.v.previous = &e[0];
  set.v.next = &e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].next = &e[1];
  only_s(e[0].previous = &set.v);
  only_p(e[1].set = &set);
  e[1].next = &e[2];
  e[1].previous = &e[0];
  only_p(e[2].set = &set);
  only_s(e[2].next = &set.v);
  e[2].previous = &e[1];
  expect(dpa_u_linked_set_set(0, &e[0], 0) == true);
  expect_p(e[0].set == 0);
  expect(e[0].next == 0);
  expect(e[0].previous == 0);
  expect(set.v.previous == &e[1]);
  expect(set.v.next == &e[2]);
  expect_p(set.length == 2);
  expect_p(e[1].previous == 0);
  expect_s(e[1].previous == &set.v);
  expect(dpa_u_linked_set_set(0, &e[1], 0) == true);
  expect_p(e[1].set == 0);
  expect(e[1].next == 0);
  expect(e[1].previous == 0);
  expect(set.v.previous == &e[2]);
  expect(set.v.next == &e[2]);
  expect_p(set.length == 1);
  expect_p(e[2].previous == 0);
  expect_s(e[2].previous == &set.v);
  expect(dpa_u_linked_set_set(0, &e[2], 0) == true);
  expect_p(e[2].set == 0);
  expect(e[2].next == 0);
  expect(e[2].previous == 0);
  expect(set.v.previous == 0);
  expect(set.v.next == 0);
  expect_p(set.length == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tremove all 3 entries from set, starting with last"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.v.previous = &e[0];
  set.v.next = &e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].next = &e[1];
  only_s(e[0].previous = &set.v);
  only_p(e[1].set = &set);
  e[1].next = &e[2];
  e[1].previous = &e[0];
  only_p(e[2].set = &set);
  only_s(e[2].next = &set.v);
  e[2].previous = &e[1];
  expect(dpa_u_linked_set_set(0, &e[2], 0) == true);
  expect_p(e[2].set == 0);
  expect(e[2].next == 0);
  expect(e[2].previous == 0);
  expect_p(e[1].next == 0);
  expect_s(e[1].next == &set.v);
  expect(set.v.previous == &e[0]);
  expect(set.v.next == &e[1]);
  expect_p(set.length == 2);
  expect(dpa_u_linked_set_set(0, &e[1], 0) == true);
  expect_p(e[1].set == 0);
  expect(e[1].next == 0);
  expect(e[1].previous == 0);
  expect(set.v.previous == &e[0]);
  expect(set.v.next == &e[0]);
  expect_p(set.length == 1);
  expect_p(e[0].next == 0);
  expect_s(e[0].next == &set.v);
  expect(dpa_u_linked_set_set(0, &e[0], 0) == true);
  expect_p(e[0].set == 0);
  expect(e[0].next == 0);
  expect(e[0].previous == 0);
  expect(set.v.previous == 0);
  expect(set.v.next == 0);
  expect_p(set.length == 0);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tof 3 entries, remove the middle one"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.v.previous = &e[0];
  set.v.next = &e[2];
  only_p(set.length = 3);
  only_p(e[0].set = &set);
  e[0].next = &e[1];
  only_s(e[0].previous = &set.v);
  only_p(e[1].set = &set);
  e[1].next = &e[2];
  e[1].previous = &e[0];
  only_p(e[2].set = &set);
  only_s(e[2].next = &set.v);
  e[2].previous = &e[1];
  expect(dpa_u_linked_set_set(0, &e[1], 0) == true);
  expect_p(e[1].set == 0);
  expect(e[1].next == 0);
  expect(e[1].previous == 0);
  expect(set.v.previous == &e[0]);
  expect(set.v.next == &e[2]);
  expect_p(set.length == 2);
  expect(e[0].next == &e[2]);
  expect(e[2].previous == &e[0]);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadd entry between 2 other entries, set implicit"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.v.previous = &e[0];
  set.v.next = &e[2];
  only_p(set.length = 2);
  only_p(e[0].set = &set);
  e[0].next = &e[2];
  only_s(e[0].previous = &set.v);
  only_p(e[2].set = &set);
  only_s(e[2].next = &set.v);
  e[2].previous = &e[0];
  expect(dpa_u_linked_set_set(0, &e[1], &e[2]) == true);
  expect_p(e[1].set == &set);
  expect(e[1].next == &e[2]);
  expect(e[1].previous == &e[0]);
  expect(e[0].next == &e[1]);
  expect(e[2].previous == &e[1]);
  expect(set.v.previous == &e[0]);
  expect(set.v.next == &e[2]);
  expect_p(set.length == 3);
  return 0;
}

DPA_U_TESTCASE(DPA_U_STR_E(T_SET) "\tdpa_u_linked_set_set\tadd entry between 2 other entries, set explicit"){
  T_SET set = {0};
  T_ENTRY e[3] = {0};
  set.v.previous = &e[0];
  set.v.next = &e[2];
  only_p(set.length = 2);
  only_p(e[0].set = &set);
  e[0].next = &e[2];
  only_s(e[0].previous = &set.v);
  only_p(e[2].set = &set);
  only_s(e[2].next = &set.v);
  e[2].previous = &e[0];
  expect(dpa_u_linked_set_set(&set, &e[1], &e[2]) == true);
  expect_p(e[1].set == &set);
  expect(e[1].next == &e[2]);
  expect(e[1].previous == &e[0]);
  expect(e[0].next == &e[1]);
  expect(e[2].previous == &e[1]);
  expect(set.v.previous == &e[0]);
  expect(set.v.next == &e[2]);
  expect_p(set.length == 3);
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
