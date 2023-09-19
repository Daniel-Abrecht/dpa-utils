#include <dpa/utils/bo.h>
#include <stdio.h>

void print_bo(dpa_u_bo_t bo){
  printf("%.*s\n", (int)dpa_u_bo_get_size(bo), (char*)dpa_u_bo_data(&bo));
}

void a(void){
  dpa_u_bo_t my_bo = {
    .bo_inline = {
      .type = DPA_U_BO_INLINE,
      .size = sizeof("Hello World!")-1,
      .data = "Hello World!"
    }
  };
  print_bo(my_bo);
}

void b(void){
  dpa_u_bo_t my_bo = {
    .bo_simple = {
      .type = DPA_U_BO_SIMPLE,
      .size = sizeof("The quick brown fox jumps over the lazy dog")-1,
      .data = "The quick brown fox jumps over the lazy dog",
    }
  };
  print_bo(my_bo);
}

int main(void){
  printf("%zu %zu\n", sizeof(dpa_u_bo_t), alignof(dpa_u_bo_t));
  a();
  b();
}
