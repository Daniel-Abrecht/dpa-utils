#include <dpa/set-map-interface.h>
#include <dpa/benchmark.h>
#include <stdio.h>

#define INSERT_AMOUNT 0x2000000llu
#define POINTS 0x80
#define REPEAT 4

#ifdef __llvm__
__attribute__((optnone))
#elif defined(__GNUC__)
__attribute__((optimize("0")))
#endif
int main(void){
  setvbuf(stdout, 0, _IOLBF, 0);
  puts("#!gnuplot/line-log-rows.gp");
  printf("#title: Reading %llu values, %u times, at various fill-levels, in us\n", (long long unsigned)INSERT_AMOUNT/POINTS, REPEAT);
  printf("#fx:%llu\n", INSERT_AMOUNT/POINTS);
  for(const dpa_if_set_t* it=dpa_set_impl_list; it; it=it->next){
    const char*const name = it->name;
    dpa_g_set_t*const set = dpa_g_set_create(it);
    printf("%s", name);
    for(size_t i=0; i<INSERT_AMOUNT; ){
      long long unsigned start, end;
      start = get_time_us();
      for(size_t r=0; r<REPEAT; r++)
      for(size_t j=0; j<INSERT_AMOUNT/POINTS; j++){
        dpa_g_set_has(set, i);
      }
      end = get_time_us();
      printf("\t%llu", end-start);
      for(size_t j=0; j<INSERT_AMOUNT/POINTS; j++){
        dpa_g_set_add(set, i++);
      }
    }
    dpa_g_set_destroy(set);
    puts("");
  }
  for(const dpa_if_map_t* it=dpa_map_impl_list; it; it=it->next){
    const char*const name = it->name;
    dpa_g_map_t*const map = dpa_g_map_create(it);
    printf("%s", name);
    for(size_t i=0; i<INSERT_AMOUNT; ){
      long long unsigned start, end;
      start = get_time_us();
      for(size_t r=0; r<REPEAT; r++)
      for(size_t j=0; j<INSERT_AMOUNT/POINTS; j++){
        dpa_g_map_get(map, i);
      }
      end = get_time_us();
      printf("\t%llu", end-start);
      for(size_t j=0; j<INSERT_AMOUNT/POINTS; j++){
        dpa_g_map_set(map, i++, 0);
      }
    }
    dpa_g_map_destroy(map);
    puts("");
  }
}
