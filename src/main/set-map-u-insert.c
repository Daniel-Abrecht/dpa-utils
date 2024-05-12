#include <dpa/set-map-interface.h>
#include <stdio.h>
#include <time.h>

#define INSERT_AMOUNT 0x2000000llu
#define POINTS 0x80

int main(void){
  setvbuf(stdout, 0, _IOLBF, 0);
  puts("#!gnuplot/line-log-rows.gp");
  printf("#title: Reading %llu values, at various fill-levels, in us\n", (long long unsigned)INSERT_AMOUNT);
  printf("#fx:%llu\n", INSERT_AMOUNT/POINTS);
  for(const dpa_if_set_t* it=dpa_set_impl_list; it; it=it->next){
    const char*const name = it->name;
    dpa_g_set_t*const set = dpa_g_set_create(it);
    printf("%s", name);
    for(size_t i=0; i<INSERT_AMOUNT; ){
      volatile clock_t start = clock();
      for(size_t j=0; j<INSERT_AMOUNT/POINTS; j++,i++){
        dpa_g_set_add(set, i);
      }
      volatile clock_t end = clock();
      printf("\t%lf", (double)(end-start)/CLOCKS_PER_SEC*1000000);
    }
    dpa_g_set_destroy(set);
    puts("");
  }
  for(const dpa_if_map_t* it=dpa_map_impl_list; it; it=it->next){
    const char*const name = it->name;
    dpa_g_map_t*const map = dpa_g_map_create(it);
    printf("%s", name);
    for(size_t i=0; i<INSERT_AMOUNT; ){
      volatile clock_t start = clock();
      for(size_t j=0; j<INSERT_AMOUNT/POINTS; j++,i++){
        dpa_g_map_set(map, i, 0);
      }
      volatile clock_t end = clock();
      printf("\t%lf", (double)(end-start)/CLOCKS_PER_SEC*1000000);
    }
    dpa_g_map_destroy(map);
    puts("");
  }
}