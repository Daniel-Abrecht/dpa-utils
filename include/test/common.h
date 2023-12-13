#include <dpa/utils/bo.h>
#include <dpa/utils/hash.h>

#define BO_DS(...) \
  .size = sizeof(__VA_ARGS__)-1, \
  .data = (char[]){__VA_ARGS__} \

#define BO_SIMPLE_H(...) \
  (dpa_u_bo_simple_t){ \
    .type = DPA_U_BO_SIMPLE, \
    BO_DS(__VA_ARGS__) \
  }

#define BO_INLINE_H(...) \
  (dpa_u_bo_inline_t){ \
    .type = DPA_U_BO_INLINE, \
    .size = sizeof(__VA_ARGS__)-1, \
    .data = __VA_ARGS__ \
  }

#define BO_HASHED_H(...) \
  (dpa_u_bo_hashed_t){ \
    .bo_simple = { \
      .type = DPA_U_BO_HASHED, \
      BO_DS(__VA_ARGS__) \
    }, \
    .hash = dpa_u_bo_hash_p((const struct dpa__u_default_hash_args){BO_SIMPLE_H(__VA_ARGS__).ro}) \
  }

#define BO_REFCOUNTED_H(...) \
  (dpa_u_bo_refcounted_t){ \
    .bo_simple = { \
      .type = DPA_U_BO_REFCOUNTED, \
      BO_DS(__VA_ARGS__) \
    } \
  }

#define BO_REFCOUNTED_HASHED_H(...) \
  (dpa_u_bo_refcounted_hashed_ro_t){ \
    .bo_refcounted = { \
      .bo_simple = { \
        .type = DPA_U_BO_REFCOUNTED_HASHED, \
        BO_DS(__VA_ARGS__) \
      } \
    }, \
    .hash = dpa_u_bo_hash_p((const struct dpa__u_default_hash_args){BO_SIMPLE_H(__VA_ARGS__).ro}) \
  }

#define P_BO_SIMPLE_DATA "What did the fox say? Bark!"
#define P_BO_SIMPLE &BO_SIMPLE_H(P_BO_SIMPLE_DATA)
#define P_BO_INLINE_DATA "Meow"
#define P_BO_INLINE &BO_INLINE_H(P_BO_INLINE_DATA)
#define P_BO_UNIQUE_DATA "The quick brown fox jumps over the lazy dog"
#define P_BO_UNIQUE &dpa_u_rescope(doa_u_bo_unique_t, dpa_u_bo_intern_p((void*)&BO_SIMPLE_H(P_BO_UNIQUE_DATA)))
#define P_BO_UNIQUE_HASHMAP_DATA P_BO_UNIQUE_DATA
#define P_BO_UNIQUE_HASHMAP (P_BO_UNIQUE->bo_unique_hashmap)
#define P_BO_HASHED_DATA "Why did the chicken cross the road? To get to the other side."
#define P_BO_HASHED &BO_HASHED_H(P_BO_HASHED_DATA)
#define P_BO_REFCOUNTED_DATA "Dunkel war’s, der Mond schien helle, schneebedeckt die grüne Flur, als ein Wagen blitzesschnelle, langsam um die Ecke fuhr."
#define P_BO_REFCOUNTED &BO_REFCOUNTED_H(P_BO_REFCOUNTED_DATA)
#define P_BO_REFCOUNTED_HASHED_DATA "Breeding rabbits is a hare raising experience."
#define P_BO_REFCOUNTED_HASHED &BO_REFCOUNTED_HASHED_H(P_BO_REFCOUNTED_HASHED_DATA)
