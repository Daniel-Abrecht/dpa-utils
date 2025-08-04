#ifndef DPA__U_PASS
#define DPA__U_PASS 1

#include <dpa/utils/list.h>
#include <dpa/utils/math.h>
#include <string.h>

#ifndef DPA_U_LIST_MIN_LBSIZE
#define DPA_U_LIST_MIN_LBSIZE 5
#endif

#elif DPA__U_PASS < 3
#if DPA__U_PASS == 1
#define DPA__U_LIST_T struct dpa__u_list_maxalign
#define X(NAME) NAME ## _ma_p
#undef DPA__U_PASS
#define DPA__U_PASS 2
#elif DPA__U_PASS == 2
#define DPA__U_LIST_T struct dpa__u_list_small
#define X(NAME) NAME ## _sa_p
#undef DPA__U_PASS
#define DPA__U_PASS 3
#endif


size_t X(dpa_u_list_length)(dpa_u_list_t* list);
void X(dpa_u_list_move)(dpa_u_list_t** dst, dpa_u_list_t** src);
void X(dpa_u_list_clear)(dpa_u_list_t** list);


bool X(dpa_u_list_reserve)(dpa_u_list_t** list, unsigned entry_size, size_t count){
  if(!count)
    return true;
  void* mem = 0;
  DPA__U_LIST_T old = {0};
  if(*list){
    mem = &((DPA__U_LIST_T*)*list)[-1];
    old = *(DPA__U_LIST_T*)mem;
  }
  int new_lbsize = dpa_u_log2((old.count+count)*entry_size+sizeof(DPA__U_LIST_T)-1)+1;
  if(new_lbsize < DPA_U_LIST_MIN_LBSIZE)
    new_lbsize = DPA_U_LIST_MIN_LBSIZE;
  if(old.lbsize >= new_lbsize)
    return true;
  DPA__U_LIST_T*restrict newmem = realloc(mem, (size_t)1<<new_lbsize);
  if(!newmem)
    return false;
  newmem->count = old.count;
  newmem->lbsize = new_lbsize;
  *list = (struct dpa_u_list*)(newmem+1);
  return true;
}

bool X(dpa_u_list_grow)(dpa_u_list_t** list, unsigned entry_size, size_t count){
  if(!count)
    return true;
  if(!X(dpa_u_list_reserve)(list, entry_size, count))
    return false;
  DPA__U_LIST_T*restrict l = (DPA__U_LIST_T*)*list;
  memset((char*)l+l[-1].count*entry_size, 0, count*entry_size);
  l[-1].count += count;
  return true;
}

void X(dpa_u_list_shrink)(dpa_u_list_t** list, unsigned entry_size, size_t count){
  if(!*list) return;
  DPA__U_LIST_T*restrict l = &((DPA__U_LIST_T*)*list)[-1];
  if(l->count <= count){
    free(((DPA__U_LIST_T*)*list)-1);
    *list = 0;
    return;
  }
  const size_t new_count = l->count -= count;
  int new_lbsize = dpa_u_log2(new_count*entry_size+sizeof(DPA__U_LIST_T)-1)+1;
  if(new_lbsize < DPA_U_LIST_MIN_LBSIZE)
    new_lbsize = DPA_U_LIST_MIN_LBSIZE;
  if(l->lbsize+1 <= new_lbsize)
    return;
  l->lbsize = new_lbsize;
  const DPA__U_LIST_T* newmem = realloc(((DPA__U_LIST_T*)*list)-1, (size_t)1<<new_lbsize);
  *list = (dpa_u_list_t*)&newmem[1];
}

bool X(dpa_u_list_append)(dpa_u_list_t** list, unsigned entry_size, size_t count, const void* entries){
  DPA__U_LIST_T start = {0};
  if(*list) start = ((DPA__U_LIST_T*)*list)[-1];
  if(!X(dpa_u_list_grow)(list, entry_size, count))
    return false;
  memcpy(((char*)*list)+start.count*entry_size, entries, entry_size*count);
  return true;
}

bool X(dpa_u_list_pop)(dpa_u_list_t** list, unsigned entry_size, void* ret){
  const size_t count = X(dpa_u_list_length)(*list);
  if(!count)
    return false;
  memcpy(ret, ((char*)*list)+entry_size*(count-1), entry_size);
  X(dpa_u_list_shrink)(list, entry_size, 1);
  return true;
}

#undef X
#undef DPA__U_LIST_T
#else
#undef DPA__U_PASS
#define DPA__U_PASS 1000
#endif
#if DPA__U_PASS != 1000
#include __FILE__
#endif
