#include <dpa/utils/bo.h>
#include <dpa/utils/io.h>
#include <stdio.h>

/**
 * This example shows how any bo can be automatically converted and passed
 * to a function as dpa_u_bo_ro_t argument using the dpa_u_v_bo_ro macro.
 * There are many conversion macros besides dpa_u_v_bo_ro, to make it easy to convert to other bo types when possible.
 *
 * The dpa_u_puts macro doesn't do this to allow more optimisations, althoug it'll probably not matter in practice.
 */
static inline size_t my_puts_p(dpa_u_bo_ro_t bo){
  fwrite(dpa_u_bo_get_data(bo), dpa_u_bo_get_size(bo), 1, stdout);
  return puts("");
}
#define my_puts(bo) my_puts_p(dpa_u_to_bo_ro((bo)))

#define S(X) sizeof(X)-1, (X)

int main(void){
  {
    dpa_u_bo_ro_t my_bo = {
      S("The quick brown fox jumps over the lazy dog")
    };
    printf("Type: %s\n", dpa_u_bo_type_to_string(dpa_u_bo_get_type(my_bo)));
    dpa_u_puts(my_bo);
    my_puts(my_bo);
  }
  {
    dpa_u_a_bo_unique_t my_bo = dpa_u_bo_intern(((dpa_u_bo_ro_t){
      S("Meow")
    }));
    printf("Type: %s\n", dpa_u_bo_type_to_string(dpa_u_bo_get_type(my_bo))); // Probably DPA_U_BO_INLINE
    dpa_u_puts(my_bo);
    my_puts(my_bo);
    dpa_u_bo_put(my_bo);
  }
  {
    dpa_u_a_bo_unique_t my_bo = dpa_u_bo_intern(((dpa_u_bo_ro_t){
      S("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.")
    }));
    printf("Type: %s\n", dpa_u_bo_type_to_string(dpa_u_bo_get_type(my_bo))); // Probably DPA_U_BO_UNIQUE_HASHMAP
    dpa_u_puts(my_bo);
    my_puts(my_bo);
    dpa_u_a_bo_unique_t my_bo2 = dpa_u_bo_intern(((dpa_u_bo_ro_t){
      S("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.")
    }));
    printf("dpa_u_bo_compare: %d\n", dpa_u_bo_compare(my_bo, my_bo2));
    dpa_u_bo_put(my_bo);
    dpa_u_bo_put(my_bo2);
  }
}
