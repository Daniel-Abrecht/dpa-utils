#include <dpa/set-map-insert.h>
#include <set>
#include <map>
#include <ctime>
#include <cstdio>
#include <cstdint>

#define AMOUNT 0x10000000llu

template<typename T>
static void set_add(const char* name){
  std::set<T> container;
  volatile clock_t start = clock();
  size_t i = 0;
  do {
    container.insert((T)i++);
    if(!(T)(i)){
      start += clock();
      container.clear();
      start -= clock();
    }
  } while(i<AMOUNT);
  volatile const clock_t end = clock();
  container.clear();
  const clock_t result = end - start;
  printf("std set\t%s\t%lf\n", name, (double)result/CLOCKS_PER_SEC);
}

template<typename T>
static void map_add(const char* name){
  std::map<T, void*> container;
  volatile clock_t start = clock();
  size_t i = 0;
  do {
    container[(T)i++] = (void*)0;
    if(!(T)(i)){
      start += clock();
      container.clear();
      start -= clock();
    }
  } while(i<AMOUNT);
  volatile const clock_t end = clock();
  container.clear();
  const clock_t result = end - start;
  printf("std map\t%s\t%lf\n", name, (double)result/CLOCKS_PER_SEC);
}

void cpp_std_set_bench(void){
  set_add<unsigned char>("uc");
  set_add<unsigned short>("us");
  set_add<unsigned>("u");
  set_add<long unsigned>("lu");
  set_add<long long unsigned>("llu");
  set_add<size_t>("z");
  set_add<std::uint8_t>("u8");
  set_add<std::uint16_t>("u16");
  set_add<std::uint32_t>("u32");
  set_add<std::uint64_t>("u64");
  set_add<void*>("pointer");
#ifdef __SIZEOF_INT128__
  set_add<__uint128_t>("u128");
#endif
#ifdef __SIZEOF_INT256__
  set_add<__uint256_t>("u256");
#endif
}

void cpp_std_map_bench(void){
  map_add<unsigned char>("uc");
  map_add<unsigned short>("us");
  map_add<unsigned>("u");
  map_add<long unsigned>("lu");
  map_add<long long unsigned>("llu");
  map_add<size_t>("z");
  map_add<std::uint8_t>("u8");
  map_add<std::uint16_t>("u16");
  map_add<std::uint32_t>("u32");
  map_add<std::uint64_t>("u64");
  map_add<void*>("pointer");
#ifdef __SIZEOF_INT128__
  map_add<__uint128_t>("u128");
#endif
#ifdef __SIZEOF_INT256__
  map_add<__uint256_t>("u256");
#endif
}
