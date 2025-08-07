#include <dpa/utils/linked-set.h>


bool dpa_u_linked_set_s_set(
  struct dpa_u_linked_set_s* set,
  struct dpa_u_linked_set_s_entry* entry,
  struct dpa_u_linked_set_s_entry* before
){
  if((!set || !set->v.next) && before)
    return false;
  if((before == entry || (before && before == entry->next)) && set)
    return true;
  if(before && !before->next)
    return false;
  // u_remove(entry);
  if(!set->v.next){
    set->v.next = entry;
    set->v.previous = entry;
    entry->next = &set->v;
    entry->previous = &set->v;
  }else if(before){
    entry->next = before;
    before->previous->next = entry;
    entry->previous = before->previous;
    before->previous = entry;
  }else{
    entry->next = &set->v;
    entry->previous = set->v.next;
    set->v.next = entry;
  }
  return true;
}

bool dpa_u_linked_set_s_move(
  struct dpa_u_linked_set_s* dst,
  struct dpa_u_linked_set_s* src,
  struct dpa_u_linked_set_s_entry* before
){
}

void dpa_u_linked_set_s_clear(struct dpa_u_linked_set_s* set){
  while(set->v.previous)
    dpa_u_linked_set_s_set(0, set->v.previous, 0);
}

