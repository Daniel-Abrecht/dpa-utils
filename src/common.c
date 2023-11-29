#include <dpa/utils/common.h>
#include <stdnoreturn.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

noreturn void dpa_u_abort_p(const char* format, ...){
  fflush(stdout);
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fflush(stderr);
  abort();
}
