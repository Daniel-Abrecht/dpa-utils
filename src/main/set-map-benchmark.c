#include <dpa/utils/set.h>
#include <dpa/utils/map.h>
#include <limits.h>
#include <stddef.h>
#include <time.h>

#define AMOUNT 0x10000000llu

#define IDENTITY(X) X

static inline dpa_u_bo_unique_t i2e_ubo(size_t i){
  dpa_u_bo_unique_t ubo = { .bo_inline={ .size=sizeof(size_t) } };
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

#define GENERATE(X) \
  X(uc, unsigned char, (unsigned char), IDENTITY) \
  X(us, unsigned short, (unsigned short), IDENTITY) \
  X(u, unsigned, (unsigned), IDENTITY) \
  X(lu, long unsigned, (long unsigned), IDENTITY) \
  X(llu, long long unsigned, (long long unsigned), IDENTITY) \
  X(z, size_t, (size_t), IDENTITY) \
  X(u8, uint8_t, (uint8_t), IDENTITY) \
  X(u16, uint16_t, (uint16_t), IDENTITY) \
  IF_u24(X(u24, uint24_t, (uint24_t), IDENTITY)) \
  X(u32, uint32_t, (uint32_t), IDENTITY) \
  X(u64, uint64_t, (uint64_t), IDENTITY) \
  IF_u128(X(u128, dpa_uint128_t, (dpa_uint128_t), IDENTITY)) \
  IF_u256(X(u256, dpa_uint256_t, (dpa_uint256_t), IDENTITY)) \
  X(pointer, void*, IDENTITY, (void*)) \
  X(string, dpa_u_bo_unique_t, IDENTITY, i2e_ubo)

int main(void){
#define B_SET_ADD(T,U,C,P) \
  { \
    dpa_u_total_resize_time = 0; \
    dpa_u_set_##T##_t container = {0}; \
    volatile clock_t start = clock(); \
    size_t i = 0; \
    do { \
      dpa_u_set_##T##_add(&container, P(i++)); \
      if(!C(i)){ \
        start += clock(); \
        dpa_u_set_##T##_clear(&container); \
        start -= clock(); \
      } \
    } while(i<AMOUNT); \
    volatile const clock_t end = clock(); \
    dpa_u_set_##T##_clear(&container); \
    const clock_t result = end - start; \
    printf("%21s | %6.3lfs | %6.3lfs | %6.3lfs\n", "dpa_u_set_"#T"_add", (double)result/CLOCKS_PER_SEC, (double)(result-dpa_u_total_resize_time)/CLOCKS_PER_SEC, (double)dpa_u_total_resize_time/CLOCKS_PER_SEC); \
  }
  printf("%21s | %7s | %7s | %7s\n", "Function","total","work","resize");
  GENERATE(B_SET_ADD)
  puts("");
#define B_MAP_SET(T,U,C,P) \
  { \
    dpa_u_total_resize_time = 0; \
    dpa_u_map_##T##_t container = {0}; \
    volatile clock_t start = clock(); \
    size_t i = 0; \
    do { \
      dpa_u_map_##T##_set(&container, P(i++), 0); \
      if(!C(i)){ \
        start += clock(); \
        dpa_u_map_##T##_clear(&container); \
        start -= clock(); \
      } \
    } while(i<AMOUNT); \
    volatile const clock_t end = clock(); \
    dpa_u_map_##T##_clear(&container); \
    const clock_t result = end - start; \
    printf("%21s | %6.3lfs | %6.3lfs | %6.3lfs\n", "dpa_u_map_"#T"_set", (double)result/CLOCKS_PER_SEC, (double)(result-dpa_u_total_resize_time)/CLOCKS_PER_SEC, (double)dpa_u_total_resize_time/CLOCKS_PER_SEC); \
  }
  printf("%21s | %7s | %7s | %7s\n", "Function","total","work","resize");
  GENERATE(B_MAP_SET)
  puts("");
}
