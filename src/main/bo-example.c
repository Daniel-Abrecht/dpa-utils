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
  fwrite(dpa_u_bo_data(bo), dpa_u_bo_get_size(bo), 1, stdout);
  return puts("");
}
#define my_puts(bo) my_puts_p(dpa_u_v_bo_ro((bo)))

int main(void){
  {
    dpa_u_bo_inline_t my_bo = {
      .type = DPA_U_BO_INLINE,
      .size = sizeof("Hello World!")-1,
      .data = "Hello World!",
    };
    dpa_u_puts(my_bo);
    my_puts(my_bo);
  }
  {
    dpa_u_bo_simple_ro_t my_bo = {
      .type = DPA_U_BO_SIMPLE,
      .size = sizeof("The quick brown fox jumps over the lazy dog")-1,
      .data = "The quick brown fox jumps over the lazy dog",
    };
    dpa_u_puts(my_bo);
    my_puts(my_bo);
  }
}
