
#define DPA_U_BO_DECLARE_UNIQUE_CSTRING(name, ...) \
  dpa_u_unsequenced dpa__u_really_inline dpa_u_export inline dpa_u_bo_unique_t name (void){ \
    if((sizeof((const char[]){__VA_ARGS__})-1) <= DPA_U_BO_INLINE_MAX_SIZE){ \
      dpa_u_bo_unique_t ubo = { \
        .bo_inline = { \
          .type = DPA_U_BO_INLINE, \
          .size = (sizeof((const char[]){__VA_ARGS__})-1) & 0xF, \
        } \
      }; \
      memcpy(ubo.bo_inline.data, (const char[]){__VA_ARGS__}, sizeof((const char[]){__VA_ARGS__})-1); \
      return ubo; \
    }else{ \
      extern dpa_u_bo_unique_hashmap_t dpa__u_sucstrp__ ## name; \
      return (const dpa_u_bo_unique_t){ \
        .bo_unique_hashmap_meta.type = DPA_U_BO_UNIQUE_HASHMAP, \
        .bo_unique_hashmap = dpa__u_sucstrp__ ## name, \
      }; \
    } \
  }
#define DPA_U_BO_DEFINE_UNIQUE_CSTRING(name, ...) \
  extern dpa_u_bo_unique_t name (void); \
  dpa_u_bo_unique_hashmap_t dpa__u_sucstrp__ ## name; \
  dpa_u_init static void dpa__u_sucstri__ ## name(void){ \
    if((sizeof((const char[]){__VA_ARGS__})-1) > DPA_U_BO_INLINE_MAX_SIZE){ \
      static const char cstr[] = {__VA_ARGS__}; \
      static dpa__u_bo_unique_hashmap_entry_t uhe = { \
        .bo_hashed.bo_simple = { \
          .type = DPA_U_BO_UNIQUE_HASHMAP, \
          .size = sizeof(cstr)-1, \
          .data = cstr, \
        }, \
        .refcount = dpa_u_refcount_i_static, \
      }; \
      extern dpa_u_bo_unique_hashmap_t dpa__u_bo_do_intern_early(dpa_u_any_bo_ro_t*const bo); \
      dpa__u_sucstrp__ ## name = dpa__u_bo_do_intern_early((dpa_u_any_bo_ro_t*)&uhe); \
    } \
  }

#ifdef DPA_U_GEN_DEF
#define DPA_U_BO_UNIQUE_CSTRING(...) \
  DPA_U_BO_DECLARE_UNIQUE_CSTRING(__VA_ARGS__) \
  DPA_U_BO_DEFINE_UNIQUE_CSTRING(__VA_ARGS__)
#else
#define DPA_U_BO_UNIQUE_CSTRING(...) DPA_U_BO_DECLARE_UNIQUE_CSTRING(__VA_ARGS__)
#endif
