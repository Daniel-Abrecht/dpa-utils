#include <dpa/utils/bo.h>
#include <dpa/utils/refcount.h>

static const char*const dpa_u_bo_type[32] = {
  "inline",
  "simple",
  "INVALID<inline|hashed>",
  "hashed|simple",
  "INVALID<inline|refcounted>",
  "refcounted|simple",
  "INVALID<inline|refcounted|hashed>",
  "refcounted|hashed|simple",
  "inline|unique",
  "INVALID<unique|simple>",
  "INVALID<inline|unique|hashed>",
  "INVALID<unique|hashed|simple>",
  "INVALID<inline|unique|refcounted>",
  "INVALID<unique|refcounted|simple>",
  "INVALID<inline|unique|refcounted|hashed>",
  "unique|refcounted|hashed|simple",
  "INVALID<inline|immortal>",
  "simple|immortal",
  "INVALID<inline|hashed|immortal>",
  "hashed|simple|immortal",
  "INVALID<inline|refcounted|immortal>",
  "refcounted|simple|immortal",
  "INVALID<inline|refcounted|hashed|immortal>",
  "refcounted|hashed|simple|immortal",
  "INVALID<inline|unique|immortal>",
  "INVALID<unique|simple|immortal>",
  "INVALID<inline|unique|hashed|immortal>",
  "INVALID<unique|hashed|simple|immortal>",
  "INVALID<inline|unique|refcounted|immortal>",
  "INVALID<unique|refcounted|simple|immortal>",
  "INVALID<inline|unique|refcounted|hashed|immortal>",
  "unique|refcounted|hashed|simple|immortal",
};

dpa__u_api const char* dpa_u_bo_type_to_string(enum dpa_u_bo_type_flags type){
  if(type >= 0x20)
    return "INVALID";
  return dpa_u_bo_type[type>>3];
}

dpa__u_api void dpa__u_bo_unique_hashmap_destroy(const struct dpa_u_refcount_freeable* bo){
  (void)bo;
  // TODO
}

dpa__u_api dpa_u_a_bo_unique_t dpa__u_bo_intern_h(dpa_u_a_bo_any_ro_t bo){
  (void)bo;
  // TODO
}
