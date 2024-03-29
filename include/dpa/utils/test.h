#ifndef DPA_UTILS_TEST_H
#define DPA_UTILS_TEST_H

#include <dpa/utils/common.h>

#include <stdbool.h>

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

/**
 * \addtogroup dpa-u-test Test Utils
 * @{
 */

/**
 * Send a test result to the `testsuite` server program.
 * \param fd Testsuite server fd, set it to -1 to make it use the `TESTSUITE_FD` environment variable.
 * \param name The testcase name, or 0 if none (may be desirable in case of a single testcase).
 * \param result Set this to `"success"` if it was ok, `skipped` if it was skipped.
 *   All other values count as failure, the values `"failed"`, `"unavailable"`, `"unknown"` are
 *   used by the `testsuite` program itself, but any value can be used.
 * \returns true on success, false if sending the result failed
 */
dpa__u_api bool dpa_u_testcase_result(int fd, const char* name, const char* result);

#define DPA_U_TESTCASE_SUFFIX __LINE__
#define DPA_U_TESTCASE(NAME)  \
  static int DPA_U_CONCAT_E(dpa_u_test_f_, DPA_U_TESTCASE_SUFFIX)(void); \
  dpa_u_init static void DPA_U_CONCAT_E(dpa_u_test_c_, DPA_U_TESTCASE_SUFFIX)(void){ \
    static struct dpa__u_testcase entry = { \
      .name = NAME, \
      .run = DPA_U_CONCAT_E(dpa_u_test_f_, DPA_U_TESTCASE_SUFFIX), \
    }; \
    entry.next = dpa__u_testcase_list; \
    dpa__u_testcase_list = &entry; \
  } \
  static int DPA_U_CONCAT_E(dpa_u_test_f_, DPA_U_TESTCASE_SUFFIX)(void)

dpa__u_api int dpa_u_test_main(int argc, const char* argv[]);

#define DPA_U_TEST_MAIN \
  int main(int argc, const char* argv[]){ \
    return dpa_u_test_main(argc, argv); \
  }

/////////////////////////////////
//////      Internals      //////
/////////////////////////////////

struct dpa__u_testcase {
  struct dpa__u_testcase* next;
  const char* name;
  int(*run)(void);
};
dpa__u_api_var extern struct dpa__u_testcase* dpa__u_testcase_list;

dpa__u_api dpa_u_weak void dpa__u_test_setup(void);
dpa__u_api dpa_u_weak void dpa__u_test_teardown(void);

/** @} */
/** @} */

#endif
