#include <dpa/set-map-insert.h>
#include <stdio.h>

int main(){
  setvbuf(stdout, 0, _IOLBF, 0);
  puts("#!gnuplot/bar.gp");
  puts("implementation\ttype\ttotal\twork\tresize");
  dpa_set_bench();
  dpa_map_bench();
  cpp_std_set_bench();
  cpp_std_map_bench();
}
