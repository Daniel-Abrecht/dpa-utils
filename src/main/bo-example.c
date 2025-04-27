#include <dpa/utils/bo.h>
#include <dpa/utils/io.h>
#include <stdio.h>
#include <errno.h>

/**
 * This example shows how any bo can be automatically converted and passed
 * to a function as dpa_u_bo_t argument using the dpa_u_v_bo_ro macro.
 * There are many conversion macros besides dpa_u_v_bo_ro, to make it easy to convert to other bo types when possible.
 *
 * The dpa_u_puts macro doesn't do this to allow more optimisations, althoug it'll probably not matter in practice.
 */
static inline size_t my_puts_p(dpa_u_bo_t bo){
  fwrite(dpa_u_bo_get_data(bo), dpa_u_bo_get_size(bo), 1, stdout);
  return puts("");
}
#define my_puts(bo) my_puts_p(dpa_u_to_bo((bo)))

#define S(X) sizeof(X)-1, (X)

int main(void){
  {
    dpa_u_bo_t my_bo = {
      S("The quick brown fox jumps over the lazy dog")
    };
    printf("Type: %s\n", dpa_u_bo_type_to_string(dpa_u_bo_get_type(my_bo)));
    dpa_u_puts(my_bo);
    my_puts(my_bo);
  }
  {
    dpa_u_a_bo_unique_t my_bo = dpa_u_bo_intern(((dpa_u_bo_t){
      S("Meow")
    }));
    printf("Type: %s\n", dpa_u_bo_type_to_string(dpa_u_bo_get_type(my_bo))); // Probably inline|unique
    dpa_u_puts(my_bo);
    my_puts(my_bo);
    dpa_u_bo_put(my_bo);
  }
  {
    dpa_u_a_bo_unique_t my_bo = dpa_u_bo_intern(((dpa_u_bo_t){
      S("Hello World!")
    }));
    printf("Type: %s\n", dpa_u_bo_type_to_string(dpa_u_bo_get_type(my_bo))); // Probably unique|refcounted|simple
    dpa_u_puts(my_bo);
    my_puts(my_bo);
    dpa_u_bo_put(my_bo);
  }
  {
    dpa_u_a_bo_unique_t my_bo = dpa_u_bo_intern(((dpa_u_bo_t){
      S("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.")
    }));
    printf("Type: %s\n", dpa_u_bo_type_to_string(dpa_u_bo_get_type(my_bo))); // Probably unique|refcounted|simple|hashed
    dpa_u_puts(my_bo);
    my_puts(my_bo);
    dpa_u_a_bo_unique_t my_bo2 = dpa_u_bo_intern(((dpa_u_bo_t){
      S("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.")
    }));
    printf("dpa_u_bo_compare: %d\n", dpa_u_bo_compare(my_bo, my_bo2));
    dpa_u_bo_put(my_bo);
    dpa_u_bo_put(my_bo2);
  }
  {
    printf(
      "Creating a dpa_u_a_bo_unique_t instance with an error value: %.7s %.7s %.7s %.7s %s\n",
      dpa_u_bo_get_data(dpa_u_bo_error(EINVAL)),
      dpa_u_bo_get_data(dpa_u_bo_error(123456)),
      dpa_u_bo_get_data(dpa_u_bo_error(1234568)),
      dpa_u_bo_get_data(dpa_u_bo_intern(dpa_u_bo_error(EPERM))),
      dpa_u_bo_is_error(dpa_u_bo_error(EINVAL)) ? "true" : "false"
    );
  }
}
