#include <dpa/utils/linked-set.h>


static void u_remove(
  struct dpa_u_linked_set_p_entry* entry
){
  if(!entry->set)
    return;
  if(entry->next)
    entry->next->previous = entry->previous;
  if(entry->previous)
    entry->previous->next = entry->next;
  if(entry->set->first == entry)
    entry->set->first = entry->next;
  if(entry->set->last == entry)
    entry->set->last = entry->previous;
  if(entry->set->size > 0)
    entry->set->size -= 1;
  entry->set = 0;
  entry->next = 0;
  entry->previous = 0;
}

bool dpa_u_linked_set_p_set(
  struct dpa_u_linked_set_p* set,
  struct dpa_u_linked_set_p_entry* entry,
  struct dpa_u_linked_set_p_entry* before
){
  if(before && set && before->set != set)
    return false;
  if((before == entry || (before && before == entry->next)) && set)
    return true;
  u_remove(entry);
  if(!set)
    return true;
  if(before)
    set = before->set;
  set->size += 1;
  entry->set = set;
  if(!set->first){
    set->first = entry;
    set->last  = entry;
    return true;
  }
  entry->next = before;
  if(!before){
    entry->previous = set->last;
    if(set->last)
      set->last->next = entry;
  }else{
    entry->previous = before->previous;
    if(before->previous)
      before->previous->next = entry;
    before->previous = entry;
  }
  if(!entry->previous)
    set->first = entry;
  if(!entry->next)
    set->last = entry;
  return true;
}

bool dpa_u_linked_set_p_move(
  struct dpa_u_linked_set_p* dst,
  struct dpa_u_linked_set_p* src,
  struct dpa_u_linked_set_p_entry* before
){
  while(src->first)
    if(!dpa_u_linked_set_p_set(dst, src->first, before))
      return false;
  return true;
}

void dpa_u_linked_set_p_clear(struct dpa_u_linked_set_p* set){
  while(set->first)
    dpa_u_linked_set_p_set(0, set->first, 0);
}
