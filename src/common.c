#include <dpa/utils/common.h>
#include <stdnoreturn.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

extern char* dpa__u_compound_printf(size_t s, char c[s], const char* format, ...);

extern noreturn void dpa_u_abort_p(const char* format, ...){
  fflush(stdout);
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fflush(stderr);
  abort();
}
