#include <dpa/set-map-interface.h>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>


static bool set_init(dpa_g_set_t* set){
  return new (set) std::set<unsigned>();
}

static void set_destroy(dpa_g_set_t* set){
  ((std::set<unsigned>*)set)->~set();
}

static void set_add(dpa_g_set_t* set, unsigned x){
  ((std::set<unsigned>*)set)->insert(x);
}

static void set_remove(dpa_g_set_t* set, unsigned x){
  ((std::set<unsigned>*)set)->erase(x);
}

static bool set_has(dpa_g_set_t* set, unsigned x){
  return ((std::set<unsigned>*)set)->contains(x);
}

static dpa_if_set_t std_set_u_impl = {
  .add = set_add,
  .remove = set_remove,
  .has = set_has,
  .init = set_init,
  .destroy = set_destroy,
  .name = "std::set<unsigned>",
  .size = sizeof(std::set<unsigned>),
};


static bool map_init(dpa_g_map_t* map){
  return new (map) std::map<unsigned,void*>();
}

static void map_destroy(dpa_g_map_t* map){
  ((std::map<unsigned,void*>*)map)->~map();
}

static void map_set(dpa_g_map_t* map, unsigned key, void* value){
  ((std::map<unsigned,void*>*)map)->emplace(key, value);
}

static void map_remove(dpa_g_map_t* map, unsigned x){
  ((std::map<unsigned,void*>*)map)->erase(x);
}

static dpa_u_optional_pointer_t map_get(dpa_g_map_t* gmap, unsigned x){
  auto map = (std::map<unsigned,void*>*)gmap;
  auto r = map->find(x);
  if(r == map->end()){
    const dpa_u_optional_pointer_t res = {
      .present = false,
    };
    return res;
  }else{
    const dpa_u_optional_pointer_t res = {
      .value = r->second,
      .present = true,
    };
    return res;
  }
}

static dpa_if_map_t std_map_u_impl = {
  .set = map_set,
  .remove = map_remove,
  .get = map_get,
  .init = map_init,
  .destroy = map_destroy,
  .name = "std::map<unsigned,void*>",
  .size = sizeof(std::map<unsigned,void*>),
};


static bool uset_init(dpa_g_set_t* set){
  return new (set) std::unordered_set<unsigned>();
}

static void uset_destroy(dpa_g_set_t* set){
  ((std::unordered_set<unsigned>*)set)->~unordered_set();
}

static void uset_add(dpa_g_set_t* set, unsigned x){
  ((std::unordered_set<unsigned>*)set)->insert(x);
}

static void uset_remove(dpa_g_set_t* set, unsigned x){
  ((std::unordered_set<unsigned>*)set)->erase(x);
}

static bool uset_has(dpa_g_set_t* set, unsigned x){
  return ((std::unordered_set<unsigned>*)set)->contains(x);
}

static dpa_if_set_t std_unordered_set_u_impl = {
  .add = uset_add,
  .remove = uset_remove,
  .has = uset_has,
  .init = uset_init,
  .destroy = uset_destroy,
  .name = "std::unordered_set<unsigned>",
  .size = sizeof(std::unordered_set<unsigned>),
};


static bool umap_init(dpa_g_map_t* map){
  return new (map) std::unordered_map<unsigned,void*>();
}

static void umap_destroy(dpa_g_map_t* map){
  ((std::unordered_map<unsigned,void*>*)map)->~unordered_map();
}

static void umap_set(dpa_g_map_t* map, unsigned key, void* value){
  ((std::unordered_map<unsigned,void*>*)map)->emplace(key, value);
}

static void umap_remove(dpa_g_map_t* map, unsigned x){
  ((std::unordered_map<unsigned,void*>*)map)->erase(x);
}

static dpa_u_optional_pointer_t umap_get(dpa_g_map_t* gmap, unsigned x){
  auto map = (std::unordered_map<unsigned,void*>*)gmap;
  auto r = map->find(x);
  if(r == map->end()){
    const dpa_u_optional_pointer_t res = {
      .present = false,
    };
    return res;
  }else{
    const dpa_u_optional_pointer_t res = {
      .value = r->second,
      .present = true,
    };
    return res;
  }
}

static dpa_if_map_t std_unordered_map_u_impl = {
  .set = umap_set,
  .remove = umap_remove,
  .get = umap_get,
  .init = umap_init,
  .destroy = umap_destroy,
  .name = "std::unordered_map<unsigned,void*>",
  .size = sizeof(std::unordered_map<unsigned,void*>),
};


__attribute__((constructor)) static void init(void){
  std_unordered_set_u_impl.next = dpa_set_impl_list;
  dpa_set_impl_list = &std_unordered_set_u_impl;
  std_unordered_map_u_impl.next = dpa_map_impl_list;
  dpa_map_impl_list = &std_unordered_map_u_impl;
  std_set_u_impl.next = dpa_set_impl_list;
  dpa_set_impl_list = &std_set_u_impl;
  std_map_u_impl.next = dpa_map_impl_list;
  dpa_map_impl_list = &std_map_u_impl;
}

