#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <time.h>

static inline long long unsigned get_time_us(){
  struct timespec ts;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
  return ts.tv_nsec / 1000 + ts.tv_sec * 1000000;
}

#endif
