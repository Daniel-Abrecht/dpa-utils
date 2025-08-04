#include <dpa/utils/linked-set.h>
#include <string.h>

#define FIRST v.p[0]
#define LAST  v.p[1]
#define NEXT    p[0]
#define PREV    p[1]

#define NEXT_E(X) ((struct dpa_u_linked_set_s_entry*)((X)->NEXT & ~DPA_U_LINKED_SET_S_TAG_SET))
#define PREV_E(X) ((struct dpa_u_linked_set_s_entry*)((X)->PREV & ~DPA_U_LINKED_SET_S_TAG_SET))

static void u_remove(
  struct dpa_u_linked_set_s_entry* entry
){
  if(!entry->NEXT)
    return;
  if(entry->PREV == entry->NEXT){
    NEXT_E(entry)->PREV = 0;
    NEXT_E(entry)->NEXT = 0;
  }else{
    NEXT_E(entry)->PREV = entry->PREV;
    PREV_E(entry)->NEXT = entry->NEXT;
  }
  entry->NEXT = 0;
  entry->PREV = 0;
}

bool dpa_u_linked_set_s_set(
  struct dpa_u_linked_set_s* set,
  struct dpa_u_linked_set_s_entry* entry,
  struct dpa_u_linked_set_s_entry* before
){
  if(set && !set->FIRST && before)
    return false;
  if((before == entry || (before && (uintptr_t)before == entry->NEXT)) && set)
    return true;
  if(before && !before->NEXT)
    return false;
  u_remove(entry);
  if(!set && !before)
    return true;
  if(before){
    entry->NEXT = (uintptr_t)before;
    PREV_E(before)->NEXT = (uintptr_t)entry;
    entry->PREV = before->PREV;
    before->PREV = (uintptr_t)entry;
    return true;
  }
  const uint64_t setptr = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&set->v;
  if(!set->FIRST){
    set->FIRST = (uintptr_t)entry;
    set->LAST = (uintptr_t)entry;
    entry->NEXT = setptr;
    entry->PREV = setptr;
  }else{
    entry->NEXT = setptr;
    entry->PREV = set->LAST;
    PREV_E(entry)->NEXT = (uintptr_t)entry;
    set->LAST = (uintptr_t)entry;
  }
  return true;
}

bool dpa_u_linked_set_s_move(
  struct dpa_u_linked_set_s* dst,
  struct dpa_u_linked_set_s* src,
  struct dpa_u_linked_set_s_entry* before
){
  if(!src || src == dst)
    return false;
  if(before && !before->NEXT)
    return false;
  if(!src->FIRST)
    return true;
  if(!before && !dst){
    dpa_u_linked_set_s_clear(src);
    return true;
  }else if(before){
    NEXT_E(&src->v)->PREV = before->PREV;
    PREV_E(&src->v)->NEXT = (uintptr_t)before;
    PREV_E(before)->NEXT = src->FIRST;
    before->PREV = src->LAST;
  }else if(dst){
    const uint64_t setptr = DPA_U_LINKED_SET_S_TAG_SET | (uintptr_t)&dst->v;
    PREV_E(&src->v)->NEXT = setptr;
    if(dst->FIRST){
      NEXT_E(&src->v)->PREV = dst->LAST;
      PREV_E(&dst->v)->NEXT = src->FIRST;
      dst->LAST = src->LAST;
    }else{
      NEXT_E(&src->v)->PREV = setptr;
      dst->FIRST = src->FIRST;
      dst->LAST = src->LAST;
    }
  }
  src->FIRST = 0;
  src->LAST = 0;
  return true;
}

void dpa_u_linked_set_s_clear(struct dpa_u_linked_set_s* set){
  if(!set || !set->FIRST) return;
  for(uintptr_t it=set->FIRST; !(it & DPA_U_LINKED_SET_S_TAG_SET); ){
    dpa_u_linked_set_s_entry_t* entry = (dpa_u_linked_set_s_entry_t*)it;
    uintptr_t next = entry->NEXT;
    memset(entry, 0, sizeof(*entry));
    it = next;
  }
  memset(set, 0, sizeof(*set));
}

