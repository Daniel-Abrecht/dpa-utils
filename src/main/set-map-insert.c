#include <dpa/set-map-insert.h>
#include <stdio.h>

int main(void){
  setvbuf(stdout, 0, _IOLBF, 0);
  puts("#!script/barchart");
  printf("#title: Insert of %llu entries in seconds\n", (long long unsigned)INSERT_AMOUNT);
  puts("implementation\ttype\ttotal\twork\tresize");
  dpa_set_bench();
  dpa_map_bench();
  cpp_std_unordered_set_bench();
  cpp_std_unordered_map_bench();
  cpp_std_set_bench();
  cpp_std_map_bench();
}
