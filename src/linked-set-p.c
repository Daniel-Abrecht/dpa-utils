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
  if(entry->set->v.previous == entry)
    entry->set->v.previous = entry->next;
  if(entry->set->v.next == entry)
    entry->set->v.next = entry->previous;
  if(entry->set->length > 0)
    entry->set->length -= 1;
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
  if(before)
    set = before->set;
  if(!set)
    return true;
  set->length += 1;
  entry->set = set;
  if(!set->v.previous){
    set->v.previous = entry;
    set->v.next  = entry;
    return true;
  }
  entry->next = before;
  if(!before){
    entry->previous = set->v.next;
    if(set->v.next)
      set->v.next->next = entry;
  }else{
    entry->previous = before->previous;
    if(before->previous)
      before->previous->next = entry;
    before->previous = entry;
  }
  if(!entry->previous)
    set->v.previous = entry;
  if(!entry->next)
    set->v.next = entry;
  return true;
}

bool dpa_u_linked_set_p_move(
  struct dpa_u_linked_set_p* dst,
  struct dpa_u_linked_set_p* src,
  struct dpa_u_linked_set_p_entry* before
){
  while(src->v.previous)
    if(!dpa_u_linked_set_p_set(dst, src->v.previous, before))
      return false;
  return true;
}

void dpa_u_linked_set_p_clear(struct dpa_u_linked_set_p* set){
  while(set->v.previous)
    dpa_u_linked_set_p_set(0, set->v.previous, 0);
}
