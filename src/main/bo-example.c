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
static inline size_t my_puts_p(dpa_u_bo_simple_ro_t bo){
  fwrite(dpa_u_bo_data(bo), dpa_u_bo_get_size(bo), 1, stdout);
  return puts("");
}
#define my_puts(bo) my_puts_p(dpa_u_t_bo_simple_ro((bo)))

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
  {
    dpa_u_bo_simple_ro_t my_bo = {
      .type = DPA_U_BO_SIMPLE,
      .size = sizeof("The quick brown fox jumps over the lazy dog")-1,
      .data = "The quick brown fox jumps over the lazy dog",
    };
    printf("Type: %s\n", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(my_bo)));
    dpa_u_puts(my_bo);
    my_puts(my_bo);
  }
  {
    dpa_u_bo_unique_t my_bo = dpa_u_bo_intern(((dpa_u_bo_simple_ro_t){
      .type = DPA_U_BO_SIMPLE,
      .size = sizeof("Meow")-1,
      .data = "Meow",
    }));
    printf("Type: %s\n", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(my_bo))); // Probably DPA_U_BO_INLINE
    dpa_u_puts(my_bo);
    my_puts(my_bo);
    dpa_u_bo_put(my_bo);
  }
  {
    dpa_u_bo_unique_t my_bo = dpa_u_bo_intern(((dpa_u_bo_simple_ro_t){
      .type = DPA_U_BO_SIMPLE,
      .size = sizeof("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.")-1,
      .data = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.",
    }));
    printf("Type: %s\n", dpa_u_enum_get_name(dpa_u_bo_any_type, dpa_u_bo_get_type(my_bo))); // Probably DPA_U_BO_UNIQUE_HASHMAP
    dpa_u_puts(my_bo);
    my_puts(my_bo);
    dpa_u_bo_unique_t my_bo2 = dpa_u_bo_intern(((dpa_u_bo_simple_ro_t){
      .type = DPA_U_BO_SIMPLE,
      .size = sizeof("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.")-1,
      .data = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.",
    }));
    printf("dpa_u_bo_compare: %d\n", dpa_u_bo_compare(my_bo, my_bo2));
    print_hashmap_stats();
    dpa_u_bo_put(my_bo);
    dpa_u_bo_put(my_bo2);
  }
  print_hashmap_stats();
}
