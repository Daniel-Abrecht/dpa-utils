#include <dpa/utils/bo.h>

#define BO_DS(S) \
  .size = sizeof(S)-1, \
  .data = (char[]){S} \

#define BO_SIMPLE_H(S) \
  (dpa_u_bo_simple_t){ \
    .type = DPA_U_BO_SIMPLE, \
    BO_DS(S) \
  }

#define BO_INLINE_H(S) \
  (dpa_u_bo_simple_t){ \
    .type = DPA_U_BO_INLINE, \
    BO_DS(S) \
  }

#define BO_HASHED_H(S) \
  (dpa_u_bo_hashed_t){ \
    .bo_simple = { \
      .type = DPA_U_BO_HASHED, \
      BO_DS(S) \
    } \
    .hash = dpa_u_bo_hash_p((const struct dpa__u_default_hash_args){BO_SIMPLE_H(S)}) \
  }

#define BO_REFCOUNTED_H(S) \
  (dpa_u_bo_refcounted_t){ \
    .bo_simple = { \
      .type = DPA_U_BO_REFCOUNETD, \
      BO_DS(S) \
    } \
  }

#define BO_REFCOUNTED_HASHED_H(S) \
  (dpa_u_bo_refcounted_hashed_ro_t){ \
    .bo_refcounted = { \
      .bo_simple = { \
        .type = DPA_U_BO_REFCOUNETD_HASHED, \
        BO_DS(S) \
      } \
    } \
    .hash = dpa_u_bo_hash_p((const struct dpa__u_default_hash_args){BO_SIMPLE_H(S)}) \
  }

#define P_BO_SIMPLE &BO_SIMPLE_H("What did the fox say? Bark!")
#define P_BO_INLINE &BO_INLINE_H("Meow")
#define P_BO_UNIQUE &dpa_u_bo_intern_p((void*)&BO_SIMPLE_H("The quick brown fox jumps over the lazy dog"))
#define P_BO_UNIQUE_HASHMAP (P_BO_UNIQUE->bo_unique_hashmap)
#define P_BO_HASHED &BO_HASHED_H("Why did the chicken cross the road? To get to the other side.")
#define P_BO_REFCOUNTED &BO_REFCOUNTED_H("Dunkel war’s, der Mond schien helle, schneebedeckt die grüne Flur, als ein Wagen blitzesschnelle, langsam um die Ecke fuhr.")
#define P_BO_REFCOUNTED_HASHED &BO_REFCOUNTED_HASHED_H("Breeding rabbits is a hare raising experience.")
