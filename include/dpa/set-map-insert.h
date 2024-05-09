#ifndef SET_MAP_INSERT_H
#define SET_MAP_INSERT_H

#define INSERT_AMOUNT 0x2000000llu

#ifdef __cplusplus
extern "C" {
#endif

void dpa_set_bench(void);
void dpa_map_bench(void);
void cpp_std_unordered_set_bench(void);
void cpp_std_unordered_map_bench(void);
void cpp_std_set_bench(void);
void cpp_std_map_bench(void);

#ifdef __cplusplus
}
#endif

#endif
