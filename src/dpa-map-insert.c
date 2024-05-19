#include <dpa/set-map-insert.h>
#include <dpa/utils/set.h>
#include <dpa/utils/map.h>
#include <limits.h>
#include <stddef.h>
#include <time.h>

#define IDENTITY(X) X

static inline dpa_u_bo_unique_t i2e_ubo(size_t i){
  dpa_u_bo_unique_t ubo = {
    .bo_inline = {
      .type = DPA_U_BO_INLINE,
      .size = sizeof(size_t),
    }
  };
  memcpy(ubo.bo_inline.data, &i, sizeof(i));
  return ubo;
}

#ifdef DPA_HAS_UINT128
#define IF_u128(...) __VA_ARGS__
#else
#define IF_u128(...)
#endif

#ifdef DPA_HAS_UINT256
#define IF_u256(...) __VA_ARGS__
#else
#define IF_u256(...)
#endif

#ifdef UINT24_MAX
#define IF_u24(...) __VA_ARGS__
#else
#define IF_u24(...)
#endif

#define GENERATE(S,X) \
  X(S,uc, unsigned char, (unsigned char), IDENTITY) \
  X(S,us, unsigned short, (unsigned short), IDENTITY) \
  X(S,u, unsigned, (unsigned), IDENTITY) \
  X(S,lu, long unsigned, (long unsigned), IDENTITY) \
  X(S,llu, long long unsigned, (long long unsigned), IDENTITY) \
  X(S,z, size_t, (size_t), IDENTITY) \
  X(S,u8, uint8_t, (uint8_t), IDENTITY) \
  X(S,u16, uint16_t, (uint16_t), IDENTITY) \
  IF_u24(X(S,u24, uint24_t, (uint24_t), IDENTITY)) \
  X(S,u32, uint32_t, (uint32_t), IDENTITY) \
  X(S,u64, uint64_t, (uint64_t), IDENTITY) \
  IF_u128(X(S,u128, dpa_uint128_t, (dpa_uint128_t), IDENTITY)) \
  IF_u256(X(S,u256, dpa_uint256_t, (dpa_uint256_t), IDENTITY)) \
  X(S,pointer, void*, IDENTITY, (void*)) \
  X(S,string, dpa_u_bo_unique_t, IDENTITY, i2e_ubo)

#define BENCH(S,T,U,C,P) \
  { \
    dpa_u_total_resize_time = 0; \
    dpa_u_##S##_##T##_t container = {0}; \
    volatile clock_t start = clock(); \
    size_t i = 0; \
    do { \
      F(T,P); \
      if(!C(i)){ \
        start += clock(); \
        dpa_u_##S##_##T##_clear(&container); \
        start -= clock(); \
      } \
    } while(i<INSERT_AMOUNT); \
    volatile const clock_t end = clock(); \
    dpa_u_##S##_##T##_clear(&container); \
    const clock_t result = end - start; \
    printf("%s\t%s\t%lf\t%lf\t%lf\n", NAME, #T, (double)result/CLOCKS_PER_SEC, (double)(result-dpa_u_total_resize_time)/CLOCKS_PER_SEC, (double)dpa_u_total_resize_time/CLOCKS_PER_SEC); \
  }

void dpa_nop_bench(void){
#define NAME "nop"
#define F(T,P) f_nop(&container, P(i++), 0)
  GENERATE(set,BENCH)
#undef F
#undef NAME
}

void dpa_set_bench(void){
#define NAME "dpa set"
#define F(T,P) dpa_u_set_##T##_add(&container, P(i++))
  GENERATE(set,BENCH)
#undef F
#undef NAME
}

void dpa_map_bench(void){
#define NAME "dpa map"
#define F(T,P) dpa_u_map_##T##_set(&container, P(i++), 0)
  GENERATE(map,BENCH)
#undef F
#undef NAME
}
