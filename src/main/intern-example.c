#define _DEFAULT_SOURCE
#include <dpa/utils/bo.h>
#include <dpa/utils/io.h>
#include <inttypes.h>
#include <stdio.h>
#include <errno.h>

struct interned {
  dpa_u_bo_unique_t interned;
};

static void print_hashmap_stats(){
  const dpa_u_bo_unique_hashmap_stats_t stats = dpa_u_bo_unique_hashmap_stats();
  printf(
    "\n"
    "count: %zu\n"
    "collisions: %zu\n"
    "empty: %zu\n"
    "buckets: %zu\n"
    "load_factor: %.2lf%%\n"
    "\n",
    stats.entry_count,
    stats.collision_count,
    stats.empty_count,
    stats.total_buckets,
    stats.load_factor * 100
  );
}

int main(void){
  FILE* f = fopen("/usr/share/dict/words", "rb");
  struct dpa_u_bo_simple bo = {
    .type = DPA_U_BO_SIMPLE,
    .size = 0,
    .data = (char[256]){0},
  };
  size_t count = 0;
  dpa_u_bo_unique_t* interned = 0;
  while(fgets(bo.data, 256, f)){
    bo.size = strnlen(bo.data, 256);
    if(bo.size) bo.size -= 1; // Remove newline
    {
      void *tmp = realloc(interned, sizeof(dpa_u_bo_unique_t[++count]));
      if(!tmp)
        dpa_u_abort("realloc failed (%d): %s\n", errno, strerror(errno));
      interned = tmp;
    }
    interned[count-1] = dpa_u_bo_intern(bo);
  }
  printf("lines: %zu\n", count);
  print_hashmap_stats();
  dpa_u_bo_unique_verify();
  for(size_t i=0; i<count; i++)
    dpa_u_bo_put(interned[i]);
  free(interned);
  print_hashmap_stats();
  dpa_u_bo_unique_verify();
  fclose(f);
}
