#include <dpa/utils/set.h>
#include <dpa/utils/map.h>

int main(void){
  {
    dpa_u_set_u_t myset = {0};
    dpa_u_set_u_add(&myset, 42);
    dpa_u_set_u_add(&myset, 1234);
    dpa_u_set_u_add(&myset, 666);
    dpa_u_set_u_add(&myset, 999);
    printf("u set:");
    for(dpa_u_set_u_it_fast_t it={0}; dpa_u_set_u_it_fast_next(&myset, &it); ){
      unsigned v = dpa_u_set_u_it_fast_get_key(&myset, &it);
      printf(" %u", v);
    }
    puts("");
  }

  {
    dpa_u_set_uc_t myset = {0};
    dpa_u_set_uc_add(&myset, 'c');
    dpa_u_set_uc_add(&myset, 'a');
    dpa_u_set_uc_add(&myset, 'b');
    printf("u set:");
    for(dpa_u_set_uc_it_fast_t it={0}; dpa_u_set_uc_it_fast_next(&myset, &it); ){
      unsigned v = dpa_u_set_uc_it_fast_get_key(&myset, &it);
      printf(" %c", v);
    }
    puts("");
  }

}
