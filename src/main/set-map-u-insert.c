#include <dpa/set-map-interface.h>
#include <stdio.h>

int main(){
  setvbuf(stdout, 0, _IOLBF, 0);
  puts("#!gnuplot/line-log-rows.gp");
  for(const dpa_if_set_t* it=dpa_set_impl_list; it; it=it->next){
    const char*const name = it->name;
    dpa_g_set_t*const set = dpa_g_set_create(it);
    printf("%s\t", name);
    dpa_g_set_destroy(set);
    puts("");
  }
  for(const dpa_if_map_t* it=dpa_map_impl_list; it; it=it->next){
    const char*const name = it->name;
    dpa_g_map_t*const map = dpa_g_map_create(it);
    printf("%s\t", name);
    dpa_g_map_destroy(map);
    puts("");
  }
}
