#include <dpa/utils/bo.h>
#include <dpa/utils/io.h>
#include <dpa/utils/hash.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

int main(int argc, char* argv[]){
  bool echo = false;
  bool nocleanup = false;
  const char* file = "/usr/share/dict/words";
  if(argc > 1){
    char** args = argv + argc;
    int i = -argc;
    while(++i){
      if(!strcmp(args[i], "--print-words")){
        echo = true;
      }else if(!strcmp(args[i], "--nocleanup")){
        nocleanup = true;
      }else if(!strcmp(args[i], "--file") && i <= -2){
        file = args[++i];
      }else{
        fprintf(stderr, "Usage: %s [--print-words] [--file myfile] [--nocleanup]\n", *argv);
        return 1;
      }
    }
  }
  //printf("dpa_hash_offset_basis: %zX\n", dpa_hash_offset_basis);
  FILE* f = fopen(file, "rb");
  if(!f) dpa_u_abort("fopen failed (%d): %s", errno, strerror(errno));
  size_t count = 0;
  size_t list_size = 1;
  dpa_u_a_bo_unique_t* list = malloc(sizeof(*list));
  char buf[256] = {0};
  while(fgets(buf, sizeof(buf), f)){
    dpa_u_bo_ro_t bo = {
      .size = strlen(buf),
      .data = buf,
    };
    if(bo.size && ((char*)bo.data)[bo.size-1] == '\n')
      bo.size -= 1;
    if(!bo.size) continue;
    if(count+1 == list_size){
      void *tmp = realloc(list, sizeof(dpa_u_a_bo_unique_t)*list_size*2);
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
      printf(" - %.*s\n", (int)dpa_u_bo_get_size(list[i]), (const char*)dpa_u_bo_get_data(list[i]));
    puts("");
  }
  printf("word count: %zu\n", count);
  if(!nocleanup){
    for(size_t i=0; i<count; i++)
      dpa_u_bo_put(list[i]);
    free(list);
    fclose(f);
  }
}
