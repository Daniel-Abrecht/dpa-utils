#define _DEFAULT_SOURCE
#include <dpa/utils/bo.h>
#include <dpa/utils/io.h>
#include <dpa/utils/hash.h>
#include <inttypes.h>
#include <stdio.h>
#include <errno.h>
#include <tgmath.h>

static void print_hashmap_stats(){
  const dpa_u_bo_unique_hashmap_stats_t stats = dpa_u_bo_unique_hashmap_stats();
  printf(
    "\n"
    "count: %zu\n"
    "collisions: %zu\n"
    "statistically expected collisions: %llu\n"
    "unavoidable collisions: %llu\n"
    "empty: %zu\n"
    "buckets: %zu\n"
    "load_factor: %.2lf%%\n"
    "\n",
    stats.entry_count,
    stats.collision_count,
    (long long unsigned)(stats.entry_count - stats.total_buckets * (1. - pow((1.-1./stats.total_buckets), stats.entry_count))),
    DPA_U_MAX(0,(long long)stats.entry_count-(long long)stats.total_buckets),
    stats.empty_count,
    stats.total_buckets,
    stats.load_factor * 100
  );
}

int main(int argc, char* argv[]){
  bool echo = false;
  const char* file = "/usr/share/dict/words";
  if(argc > 1){
    char** args = argv + argc;
    int i = -argc;
    while(++i){
      if(!strcmp(args[i], "--print-words")){
        echo = true;
      }else if(!strcmp(args[i], "--file") && i <= -2){
        file = args[++i];
      }else{
        fprintf(stderr, "Usage: %s [--print-words] [--file myfile]\n", *argv);
        return 1;
      }
    }
  }
  printf("dpa_hash_offset_basis: %zX\n", dpa_hash_offset_basis);
  FILE* f = fopen(file, "rb");
  size_t count = 0;
  size_t list_size = 1;
  dpa_u_bo_unique_t* list = malloc(sizeof(*list));
  char buf[256] = {0};
  while(fgets(buf, sizeof(buf), f)){
    struct dpa_u_bo_simple bo = {
      .type = DPA_U_BO_SIMPLE,
      .size = strlen(buf),
      .data = buf,
    };
    if(bo.size && ((char*)bo.data)[bo.size-1] == '\n')
      bo.size -= 1;
    if(!bo.size) continue;
    if(count+1 == list_size){
      void *tmp = realloc(list, sizeof(dpa_u_bo_unique_t[list_size*2]));
      if(!tmp)
        dpa_u_abort("realloc failed (%d): %s\n", errno, strerror(errno));
      list = tmp;
      list_size *= 2;
    }
    list[count++] = dpa_u_bo_intern(bo);
  }
  if(echo){
    puts("words: ");
    for(size_t i=0; i<count; i++)
      printf(" - %.*s\n", (int)dpa_u_bo_get_size(list[i]), (const char*)dpa_u_bo_data(list[i]));
    puts("");
  }
  printf("word count: %zu\n", count);
  print_hashmap_stats();
  dpa_u_bo_unique_verify();
  for(size_t i=0; i<count; i++)
    dpa_u_bo_put(list[i]);
  free(list);
  print_hashmap_stats();
  dpa_u_bo_unique_verify();
  fclose(f);
}
