#include <dpa/set-map-insert.h>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <ctime>
#include <cstdio>
#include <cstdint>

template<typename T, typename C>
static void set_add(const char* name){
  C container;
  volatile clock_t start = clock();
  size_t i = 0;
  do {
    container.insert((T)i++);
    if(!(T)(i)){
      start += clock();
      container.clear();
      start -= clock();
    }
  } while(i<INSERT_AMOUNT);
  volatile const clock_t end = clock();
  container.clear();
  const clock_t result = end - start;
  printf("%s\t%lf\n", name, (double)result/CLOCKS_PER_SEC);
}

template<typename T, typename C>
static void map_add(const char* name){
  C container;
  volatile clock_t start = clock();
  size_t i = 0;
  do {
    container[(T)i++] = (void*)0;
    if(!(T)(i)){
      start += clock();
      container.clear();
      start -= clock();
    }
  } while(i<INSERT_AMOUNT);
  volatile const clock_t end = clock();
  container.clear();
  const clock_t result = end - start;
  printf("%s\t%lf\n", name, (double)result/CLOCKS_PER_SEC);
}

void cpp_std_set_bench(void){
  set_add<unsigned char,std::set<unsigned char>>("std set\tuc");
  set_add<unsigned short,std::set<unsigned short>>("std set\tus");
  set_add<unsigned,std::set<unsigned>>("std set\tu");
  set_add<long unsigned,std::set<long unsigned>>("std set\tlu");
  set_add<long long unsigned,std::set<long long unsigned>>("std set\tllu");
  set_add<size_t,std::set<size_t>>("std set\tz");
  set_add<std::uint8_t,std::set<std::uint8_t>>("std set\tu8");
  set_add<std::uint16_t,std::set<std::uint16_t>>("std set\tu16");
  set_add<std::uint32_t,std::set<std::uint32_t>>("std set\tu32");
  set_add<std::uint64_t,std::set<std::uint64_t>>("std set\tu64");
  set_add<void*,std::set<void*>>("std set\tpointer");
#ifdef __SIZEOF_INT128__
  set_add<__uint128_t,std::set<__uint128_t>>("std set\tu128");
#endif
#ifdef __SIZEOF_INT256__
  set_add<__uint256_t,std::set<__uint256_t>>("std set\tu256");
#endif
}

void cpp_std_map_bench(void){
  map_add<unsigned char,std::map<unsigned char,void*>>("std map\tuc");
  map_add<unsigned short,std::map<unsigned short,void*>>("std map\tus");
  map_add<unsigned,std::map<unsigned,void*>>("std map\tu");
  map_add<long unsigned,std::map<long unsigned,void*>>("std map\tlu");
  map_add<long long unsigned,std::map<long long unsigned,void*>>("std map\tllu");
  map_add<size_t,std::map<size_t,void*>>("std map\tz");
  map_add<std::uint8_t,std::map<std::uint8_t,void*>>("std map\tu8");
  map_add<std::uint16_t,std::map<std::uint16_t,void*>>("std map\tu16");
  map_add<std::uint32_t,std::map<std::uint32_t,void*>>("std map\tu32");
  map_add<std::uint64_t,std::map<std::uint64_t,void*>>("std map\tu64");
  map_add<void*,std::map<void*,void*>>("std map\tpointer");
#ifdef __SIZEOF_INT128__
  map_add<__uint128_t,std::map<__uint128_t,void*>>("std map\tu128");
#endif
#ifdef __SIZEOF_INT256__
  map_add<__uint256_t,std::map<__uint256_t,void*>>("std map\tu256");
#endif
}

void cpp_std_unordered_set_bench(void){
  set_add<unsigned char,std::unordered_set<unsigned char>>("std unordered set\tuc");
  set_add<unsigned short,std::unordered_set<unsigned short>>("std unordered set\tus");
  set_add<unsigned,std::unordered_set<unsigned>>("std unordered set\tu");
  set_add<long unsigned,std::unordered_set<long unsigned>>("std unordered set\tlu");
  set_add<long long unsigned,std::unordered_set<long long unsigned>>("std unordered set\tllu");
  set_add<size_t,std::unordered_set<size_t>>("std unordered set\tz");
  set_add<std::uint8_t,std::unordered_set<std::uint8_t>>("std unordered set\tu8");
  set_add<std::uint16_t,std::unordered_set<std::uint16_t>>("std unordered set\tu16");
  set_add<std::uint32_t,std::unordered_set<std::uint32_t>>("std unordered set\tu32");
  set_add<std::uint64_t,std::unordered_set<std::uint64_t>>("std unordered set\tu64");
  set_add<void*,std::unordered_set<void*>>("std unordered set\tpointer");
#ifdef __SIZEOF_INT128__
  set_add<__uint128_t,std::unordered_set<__uint128_t>>("std unordered set\tu128");
#endif
#ifdef __SIZEOF_INT256__
  set_add<__uint256_t,std::unordered_set<__uint256_t>>("std unordered set\tu256");
#endif
}

void cpp_std_unordered_map_bench(void){
  map_add<unsigned char,std::unordered_map<unsigned char,void*>>("std unordered map\tuc");
  map_add<unsigned short,std::unordered_map<unsigned short,void*>>("std unordered map\tus");
  map_add<unsigned,std::unordered_map<unsigned,void*>>("std unordered map\tu");
  map_add<long unsigned,std::unordered_map<long unsigned,void*>>("std unordered map\tlu");
  map_add<long long unsigned,std::unordered_map<long long unsigned,void*>>("std unordered map\tllu");
  map_add<size_t,std::unordered_map<size_t,void*>>("std unordered map\tz");
  map_add<std::uint8_t,std::unordered_map<std::uint8_t,void*>>("std unordered map\tu8");
  map_add<std::uint16_t,std::unordered_map<std::uint16_t,void*>>("std unordered map\tu16");
  map_add<std::uint32_t,std::unordered_map<std::uint32_t,void*>>("std unordered map\tu32");
  map_add<std::uint64_t,std::unordered_map<std::uint64_t,void*>>("std unordered map\tu64");
  map_add<void*,std::unordered_map<void*,void*>>("std unordered map\tpointer");
#ifdef __SIZEOF_INT128__
  map_add<__uint128_t,std::unordered_map<__uint128_t,void*>>("std unordered map\tu128");
#endif
#ifdef __SIZEOF_INT256__
  map_add<__uint256_t,std::unordered_map<__uint256_t,void*>>("std unordered map\tu256");
#endif
}
