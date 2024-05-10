#ifndef SET_MAP_INTERFACE_H
#define SET_MAP_INTERFACE_H

#include <stdlib.h>
#include <stdbool.h>

#ifndef __cplusplus
#include <dpa/utils/common.h>
#else
typedef struct dpa_u_optional_pointer {
  void* value;
  bool present;
} dpa_u_optional_pointer_t;
#endif

typedef struct dpa_g_set dpa_g_set_t;
typedef struct dpa_g_map dpa_g_map_t;
typedef struct dpa_if_set dpa_if_set_t;
typedef struct dpa_if_map dpa_if_map_t;


typedef bool dpa_g_set_init_t(dpa_g_set_t* set);
typedef void dpa_g_set_destroy_t(dpa_g_set_t* set);
typedef void dpa_g_set_add_t(dpa_g_set_t* set, unsigned x);
typedef void dpa_g_set_remove_t(dpa_g_set_t* set, unsigned x);
typedef bool dpa_g_set_has_t(dpa_g_set_t* set, unsigned x);

typedef bool dpa_g_map_init_t(dpa_g_map_t* map);
typedef void dpa_g_map_destroy_t(dpa_g_map_t* map);
typedef void dpa_g_map_set_t(dpa_g_map_t* map, unsigned key, void* value);
typedef void dpa_g_map_remove_t(dpa_g_map_t* map, unsigned x);
typedef dpa_u_optional_pointer_t dpa_g_map_get_t(dpa_g_map_t* map, unsigned x);


#ifdef __cplusplus
extern "C" {
#endif

struct dpa_if_set {
  dpa_g_set_add_t* add;
  dpa_g_set_remove_t* remove;
  dpa_g_set_has_t* has;
  dpa_g_set_init_t* init;
  dpa_g_set_destroy_t* destroy;
  const char* name;
  size_t size;
  const struct dpa_if_set* next;
};

struct dpa_if_map {
  dpa_g_map_set_t* set;
  dpa_g_map_remove_t* remove;
  dpa_g_map_get_t* get;
  dpa_g_map_init_t* init;
  dpa_g_map_destroy_t* destroy;
  const char* name;
  size_t size;
  const struct dpa_if_map* next;
};

extern const dpa_if_set_t* dpa_set_impl_list;
extern const dpa_if_map_t* dpa_map_impl_list;

#ifdef __cplusplus
}
#endif

static inline dpa_g_set_t* dpa_g_set_create(const dpa_if_set_t*const iface){
  void*const mem = calloc(sizeof(dpa_if_set_t*) + iface->size, 1);
  if(!mem) return 0;
  *(const dpa_if_set_t**)mem = iface;
  dpa_g_set_t*const gset = (dpa_g_set_t*)((const dpa_if_set_t**)gset + 1);
  if(iface->init)
  if(!iface->init(gset)){
    free(mem);
    return 0;
  }
  return gset;
}

static inline void dpa_g_set_destroy(dpa_g_set_t*const set){
  const dpa_if_set_t*const iface = ((const dpa_if_set_t*const*)set)[-1];
  iface->destroy(set);
  free(set);
}

static inline void dpa_g_set_add(dpa_g_set_t* set, unsigned x){
  const dpa_if_set_t*const iface = ((const dpa_if_set_t*const*)set)[-1];
  iface->add(set, x);
}

static inline void dpa_g_set_remove(dpa_g_set_t* set, unsigned x){
  const dpa_if_set_t*const iface = ((const dpa_if_set_t*const*)set)[-1];
  iface->remove(set, x);
}

static inline bool dpa_g_set_has(dpa_g_set_t* set, unsigned x){
  const dpa_if_set_t*const iface = ((const dpa_if_set_t*const*)set)[-1];
  return iface->has(set, x);
}


static inline dpa_g_map_t* dpa_g_map_create(const dpa_if_map_t*const iface){
  void*const mem = calloc(sizeof(dpa_if_map_t*) + iface->size, 1);
  if(!mem) return 0;
  *(const dpa_if_map_t**)mem = iface;
  dpa_g_map_t*const gmap = (dpa_g_map_t*)((const dpa_if_map_t*const*)gmap + 1);
  if(iface->init)
  if(!iface->init(gmap)){
    free(mem);
    return 0;
  }
  return gmap;
}

static inline void dpa_g_map_destroy(dpa_g_map_t* map){
  const dpa_if_map_t*const iface = ((const dpa_if_map_t*const*)map)[-1];
  iface->destroy(map);
}

static inline void dpa_g_map_set(dpa_g_map_t* map, unsigned key, void* value){
  const dpa_if_map_t*const iface = ((const dpa_if_map_t*const*)map)[-1];
  iface->set(map, key, value);
}

static inline void dpa_g_map_remove(dpa_g_map_t* map, unsigned x){
  const dpa_if_map_t*const iface = ((const dpa_if_map_t*const*)map)[-1];
  iface->remove(map, x);
}

static inline dpa_u_optional_pointer_t dpa_g_map_get(dpa_g_map_t* map, unsigned x){
  const dpa_if_map_t*const iface = ((const dpa_if_map_t*const*)map)[-1];
  return iface->get(map, x);
}


#endif
