#include <dpa/utils/linked-set.h>
#include <string.h>

#define FIRST v.p[0]
#define LAST  v.p[1]
#define NEXT    p[0]
#define PREV    p[1]

#define NEXT_E(X) ((struct dpa_u_linked_set_p_entry*)(X)->NEXT)
#define PREV_E(X) ((struct dpa_u_linked_set_p_entry*)(X)->PREV)

static void u_remove(
  struct dpa_u_linked_set_p_entry* entry
){
  if(!entry->set)
    return;
  if(entry->NEXT)
    NEXT_E(entry)->PREV = entry->PREV;
  if(entry->PREV)
    PREV_E(entry)->NEXT = entry->NEXT;
  if(NEXT_E(&entry->set->v) == entry)
    entry->set->FIRST = entry->NEXT;
  if(PREV_E(&entry->set->v) == entry)
    entry->set->LAST = entry->PREV;
  if(entry->set->length > 0)
    entry->set->length -= 1;
  entry->set = 0;
  entry->NEXT = 0;
  entry->PREV = 0;
}

bool dpa_u_linked_set_p_set(
  struct dpa_u_linked_set_p* set,
  struct dpa_u_linked_set_p_entry* entry,
  struct dpa_u_linked_set_p_entry* before
){
  if((before && !before->set) || (before && set && before->set != set))
    return false;
  if((before == entry || (before && before == NEXT_E(entry))) && set)
    return true;
  if((!set && !before) || (entry->set && set != entry->set))
    u_remove(entry);
  if(!set && !before)
    return true;
  if(before)
    set = before->set;
  set->length += 1;
  entry->set = set;
  if(!set->FIRST){
    set->FIRST = (uintptr_t)entry;
    set->LAST  = (uintptr_t)entry;
    return true;
  }
  entry->NEXT = (uintptr_t)before;
  if(!before){
    entry->PREV = set->LAST;
    if(set->LAST)
      PREV_E(&set->v)->NEXT = (uintptr_t)entry;
  }else{
    entry->PREV = before->PREV;
    if(before->PREV)
      PREV_E(before)->NEXT = (uintptr_t)entry;
    before->PREV = (uintptr_t)entry;
  }
  if(!entry->PREV)
    set->FIRST = (uintptr_t)entry;
  if(!entry->NEXT)
    set->LAST = (uintptr_t)entry;
  return true;
}

bool dpa_u_linked_set_p_move(
  struct dpa_u_linked_set_p* dst,
  struct dpa_u_linked_set_p* src,
  struct dpa_u_linked_set_p_entry* before
){
  if(!dst && before)
    dst = before->set;
  if(!src || src == dst)
    return false;
  if(before && before->set != dst)
    return false;
  if(!src->FIRST)
    return true;
  for(
    dpa_u_linked_set_p_entry_t* it = (dpa_u_linked_set_p_entry_t*)src->FIRST;
    it; it = (dpa_u_linked_set_p_entry_t*)it->NEXT
  ) it->set = dst;
  if(!before && !dst){
    dpa_u_linked_set_p_clear(src);
    return true;
  }else if(before){
    NEXT_E(&src->v)->PREV = before->PREV;
    PREV_E(&src->v)->NEXT = (uintptr_t)before;
    if(PREV_E(before)){
      PREV_E(before)->NEXT = src->FIRST;
    }else{
      dst->FIRST = src->FIRST;
    }
    before->PREV = src->LAST;
  }else if(dst){
    PREV_E(&src->v)->NEXT = 0;
    if(dst->FIRST){
      NEXT_E(&src->v)->PREV = dst->LAST;
      PREV_E(&dst->v)->NEXT = src->FIRST;
      dst->LAST = src->LAST;
    }else{
      NEXT_E(&src->v)->PREV = 0;
      dst->FIRST = src->FIRST;
      dst->LAST = src->LAST;
    }
  }
  dst->length += src->length;
  memset(src, 0, sizeof(*src));
  return true;
}

void dpa_u_linked_set_p_clear(struct dpa_u_linked_set_p* set){
  if(!set) return;
  for(uintptr_t it=set->FIRST; it; ){
    dpa_u_linked_set_p_entry_t* entry = (dpa_u_linked_set_p_entry_t*)it;
    uintptr_t next = entry->NEXT;
    memset(entry, 0, sizeof(*entry));
    it = next;
  }
  memset(set, 0, sizeof(*set));
}
