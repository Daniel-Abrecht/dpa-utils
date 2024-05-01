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
    for(dpa_u_set_u_it_fast_t it={0}; dpa_u_set_u_it_fast_next(&myset, &it); )
      printf(" %u", dpa_u_set_u_it_fast_get_key(&myset, &it));
    puts("");

    printf("u set reversed:");
    for(dpa_u_set_u_it_fast_t it={0}; dpa_u_set_u_it_fast_prev(&myset, &it); )
      printf(" %u", dpa_u_set_u_it_fast_get_key(&myset, &it));
    puts("");

    {
      dpa_u_set_u_it_fast_t it={0};
      printf("u set mixed:");
      dpa_u_set_u_it_fast_next(&myset, &it);
      printf(" n:%u", dpa_u_set_u_it_fast_get_key(&myset, &it));
      dpa_u_set_u_it_fast_next(&myset, &it);
      printf(" n:%u", dpa_u_set_u_it_fast_get_key(&myset, &it));
      dpa_u_set_u_it_fast_prev(&myset, &it);
      printf(" p:%u p:eof", dpa_u_set_u_it_fast_get_key(&myset, &it));
      assert(dpa_u_set_u_it_fast_prev(&myset, &it) == false); // EOF

      dpa_u_set_u_it_fast_prev(&myset, &it);
      printf(" p:%u", dpa_u_set_u_it_fast_get_key(&myset, &it));
      dpa_u_set_u_it_fast_prev(&myset, &it);
      printf(" p:%u", dpa_u_set_u_it_fast_get_key(&myset, &it));
      dpa_u_set_u_it_fast_next(&myset, &it);
      printf(" n:%u n:eof\n", dpa_u_set_u_it_fast_get_key(&myset, &it));
      assert(dpa_u_set_u_it_fast_next(&myset, &it) == false); // EOF
    }
  }

  {
    dpa_u_set_uc_t myset = {0};
    dpa_u_set_uc_add(&myset, 'c');
    dpa_u_set_uc_add(&myset, 'a');
    dpa_u_set_uc_add(&myset, 'b');

    printf("uc set:");
    for(dpa_u_set_uc_it_fast_t it={0}; dpa_u_set_uc_it_fast_next(&myset, &it); )
      printf(" %c", dpa_u_set_uc_it_fast_get_key(&myset, &it));
    puts("");

    printf("uc set reversed:");
    for(dpa_u_set_uc_it_fast_t it={0}; dpa_u_set_uc_it_fast_prev(&myset, &it); )
      printf(" %c", dpa_u_set_uc_it_fast_get_key(&myset, &it));
    puts("");

    {
      dpa_u_set_uc_it_fast_t it={0};
      printf("uc set mixed:");
      dpa_u_set_uc_it_fast_next(&myset, &it);
      printf(" n:%c", dpa_u_set_uc_it_fast_get_key(&myset, &it));
      dpa_u_set_uc_it_fast_next(&myset, &it);
      printf(" n:%c", dpa_u_set_uc_it_fast_get_key(&myset, &it));
      dpa_u_set_uc_it_fast_prev(&myset, &it);
      printf(" p:%c p:eof", dpa_u_set_uc_it_fast_get_key(&myset, &it));
      assert(dpa_u_set_uc_it_fast_prev(&myset, &it) == false); // EOF

      dpa_u_set_uc_it_fast_prev(&myset, &it);
      printf(" p:%c", dpa_u_set_uc_it_fast_get_key(&myset, &it));
      dpa_u_set_uc_it_fast_prev(&myset, &it);
      printf(" p:%c", dpa_u_set_uc_it_fast_get_key(&myset, &it));
      dpa_u_set_uc_it_fast_next(&myset, &it);
      printf(" n:%c n:eof\n", dpa_u_set_uc_it_fast_get_key(&myset, &it));
      assert(dpa_u_set_uc_it_fast_next(&myset, &it) == false); // EOF
    }
  }

}
