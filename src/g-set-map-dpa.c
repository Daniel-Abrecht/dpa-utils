#include <dpa/set-map-interface.h>
#include <dpa/utils/set.h>
#include <dpa/utils/map.h>

static void set_destroy(dpa_g_set_t* set){
  dpa_u_set_u_clear((dpa_u_set_u_t*)set);
}

static void set_add(dpa_g_set_t* set, unsigned x){
  dpa_u_set_u_add((dpa_u_set_u_t*)set, x);
}

static void set_remove(dpa_g_set_t* set, unsigned x){
  dpa_u_set_u_remove((dpa_u_set_u_t*)set, x);
}

static bool set_has(dpa_g_set_t* set, unsigned x){
  return dpa_u_set_u_has((dpa_u_set_u_t*)set, x);
}

static dpa_if_set_t dpa_set_u_impl = {
  .size = sizeof(dpa_u_set_u_t),
  .add = set_add,
  .has = set_has,
  .remove = set_remove,
  .destroy = set_destroy,
};

static void map_destroy(dpa_g_map_t* map){
  dpa_u_map_u_clear((dpa_u_map_u_t*)map);
}

static void map_set(dpa_g_map_t* map, unsigned key, void* value){
  dpa_u_map_u_set((dpa_u_map_u_t*)map, key, value);
}

static void map_remove(dpa_g_map_t* map, unsigned x){
  dpa_u_map_u_remove((dpa_u_map_u_t*)map, x);
}

static dpa_u_optional_pointer_t map_get(dpa_g_map_t* map, unsigned x){
  return dpa_u_map_u_get((dpa_u_map_u_t*)map, x);
}

static dpa_if_map_t dpa_map_u_impl = {
  .size = sizeof(dpa_u_map_u_t),
  .destroy = map_destroy,
  .set = map_set,
  .remove = map_remove,
  .get = map_get,
};

dpa_u_init static void init(void){
  dpa_set_u_impl.next = dpa_set_impl_list;
  dpa_set_impl_list = &dpa_set_u_impl;
  dpa_map_u_impl.next = dpa_map_impl_list;
  dpa_map_impl_list = &dpa_map_u_impl;
}
