//////////////////////////////////
//// Top section, common code ////
//////////////////////////////////
#ifndef DPA_U_T_SELF
#define DPA_U_T_SELF

#include <dpa/utils/set.h>
#include <dpa/utils/map.h>
#include <dpa/utils/math.h>
#include <dpa/utils/_math.h>

#define DPA__U_SM_BITMAP_OFFSET(INDEX) ((INDEX)/(sizeof(dpa_u_giant_unsigned_int_t)*CHAR_BIT))
#define DPA__U_SM_BITMAP_BIT(INDEX) (((dpa_u_giant_unsigned_int_t)1)<<((INDEX)%(sizeof(dpa_u_giant_unsigned_int_t)*CHAR_BIT)))

struct lookup_result {
  size_t index;
  bool found;
};

// Ensure there is some free space left 100/8 = 12.5%
#define SET_OVERSIZE_INVERSE_FACTOR 8

static size_t count_to_lbsize(size_t n){
  enum { MIN_SIZE = 32 };
  n += n / SET_OVERSIZE_INVERSE_FACTOR;
  return dpa_u_log2(n|(MIN_SIZE-1))+1;
}

// Note: Not rounded up to dpa_u_giant_unsigned_int_t size.
#define EXPECTED_BITMAP_SIZE(T) ((1ull<<(sizeof(T)*CHAR_BIT)) / CHAR_BIT)
#define LIST_OR_BITMAP_SIZE_THRESHOLD(T) (( \
     (1ull<<DPA_U_CONSTEXPR_LOG2(EXPECTED_BITMAP_SIZE(T) / 2 / sizeof(T))) \
   * SET_OVERSIZE_INVERSE_FACTOR + SET_OVERSIZE_INVERSE_FACTOR \
  ) / (SET_OVERSIZE_INVERSE_FACTOR+1))

#define DPA__U_SM_TEMPLATE <src/set-and-map.c>
#define DPA__U_SM_KIND DPA__U_SM_KIND_SET
#include <dpa/utils/_set-and-map.generator>

#define DPA__U_SM_TEMPLATE <src/set-and-map.c>
#define DPA__U_SM_KIND DPA__U_SM_KIND_MAP
#include <dpa/utils/_set-and-map.generator>

#else
//////////////////////////
//// Template section ////
//////////////////////////

#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
#define DPA__U_SM_PREFIX DPA_U_CONCAT_E(DPA_U_CONCAT_E(dpa_u_, set_), DPA__U_SM_NAME)
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#define DPA__U_SM_PREFIX DPA_U_CONCAT_E(DPA_U_CONCAT_E(dpa_u_, map_), DPA__U_SM_NAME)
#endif
#define DPA__U_SM_TYPE DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _t)

#ifdef DPA__U_SM_KEY_TYPE_U
#define DPA__U_SM_KEY_ENTRY_TYPE DPA__U_SM_KEY_TYPE_U
#else
#define DPA__U_SM_KEY_ENTRY_TYPE DPA__U_SM_KEY_TYPE
#endif

#ifdef DPA__U_SM_BO
#define KEY_ENTRY_HASH(X) (X).hash[0]
#define ENTRY_HASH_TYPE size_t
#else
#define KEY_ENTRY_HASH(X) (X)
#define ENTRY_HASH_TYPE DPA__U_SM_KEY_ENTRY_TYPE
#endif

//////////////////////////////////////////////

#define LOOKUP DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _lookup_sub)
#define INSERT DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _insert_sub)
#define REMOVE DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _remove_sub)
#define HASH DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _hash_sub)
#define UNHASH DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _unhash_sub)

#ifndef DPA__U_SM_BO
dpa_u_unsequenced DPA__U_SM_KEY_ENTRY_TYPE HASH(const DPA__U_SM_KEY_TYPE x){
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-count-overflow"
  return ((DPA__U_SM_KEY_ENTRY_TYPE)x) * dpa__u_choose_prime(DPA__U_SM_KEY_ENTRY_TYPE);
#pragma GCC diagnostic pop
}

// We don't need this yet, but we may need it if we add things like iterating over the keys in a set.
/*
dpa_u_unsequenced DPA__U_SM_KEY_TYPE UNHASH(DPA__U_SM_KEY_ENTRY_TYPE x){
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-count-overflow"
  return (DPA__U_SM_KEY_TYPE)(x * dpa__u_choose_prime_inverse(DPA__U_SM_KEY_ENTRY_TYPE));
#pragma GCC diagnostic pop
}
*/
#else
dpa_u_unsequenced DPA__U_SM_KEY_ENTRY_TYPE HASH(const DPA__U_SM_KEY_TYPE n){
  DPA__U_SM_KEY_ENTRY_TYPE e;
  memcpy(e.hash, n.all.all, sizeof(n));
  for(size_t i=sizeof(e.hash)/sizeof(*e.hash),fh=0; i--; )
    e.hash[i] = fh ^= dpa_u_set_size_t_hash_sub(e.hash[i]);
  return e;
}
/*
dpa_u_unsequenced DPA__U_SM_KEY_TYPE UNHASH(DPA__U_SM_KEY_ENTRY_TYPE e){
  for(size_t i=sizeof(e.hash)/sizeof(*e.hash),fh=0; i--; ){
    size_t hash = e.hash[i];
    e.hash[i] = dpa_u_size_t_set_unhash_sub(hash ^ fh);
    fh = hash;
  }
  DPA__U_SM_KEY_TYPE r;
  memcpy(r.all.all, e.hash, sizeof(r));
  return r;
}*/
#endif

#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
// Note: This is a variant of robin hood hashing, but the entries are sorted a bit more strictly.
// For values with the same PSL, entries are implicitly sorted by the keys values.
static struct lookup_result LOOKUP(
  const DPA__U_SM_TYPE* that,
  const DPA__U_SM_KEY_ENTRY_TYPE key,
  const size_t lbsize
){
  const size_t mask = (((size_t)1)<<lbsize)-1;
  ENTRY_HASH_TYPE hash = KEY_ENTRY_HASH(key);
  size_t i = hash >> (sizeof(size_t)*CHAR_BIT-lbsize);
  if(!that->key_list)
    return (struct lookup_result){i, false};
  for(size_t psl=0,s=mask+1; psl<s; psl++, i=((i+1)&mask)){
    const DPA__U_SM_KEY_ENTRY_TYPE ekey = that->key_list[i];
    ENTRY_HASH_TYPE diff = KEY_ENTRY_HASH(ekey) - hash;
    if(!diff){
#ifdef DPA__U_SM_BO
      const int cmp = memcmp(&key, &ekey, sizeof(key));
      if(!cmp)
        return (struct lookup_result){i, true};
      if(cmp < 0)
        return (struct lookup_result){i, false};
#else
      return (struct lookup_result){i, true};
#endif
    }
    if((ENTRY_HASH_TYPE)(diff >> (sizeof(size_t)*CHAR_BIT-lbsize)) <= psl)
      return (struct lookup_result){i, false};
  }
  dpa_u_unreachable("Hashmap lookup failed: %s", "That neither an entry is found, nor the PSL ever exceeds the one of any of the entries of the hashmap while earching, should not be possible.");
}
#endif

#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
// This subroutine is used after an existing value was already found, so we have the index of where to insert it.
static void INSERT(
  DPA__U_SM_TYPE* that,
  DPA__U_SM_KEY_ENTRY_TYPE key,
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  void* value,
#endif
  size_t i,
  const size_t lbsize
){
  const size_t mask = (((size_t)1)<<lbsize)-1;
  size_t psl = (i - (KEY_ENTRY_HASH(key) >> (sizeof(size_t)*CHAR_BIT-lbsize))) & mask;
  for(size_t s = mask+1; psl<s; psl++, i=((i+1)&mask)){
    const DPA__U_SM_KEY_ENTRY_TYPE ekey = that->key_list[i];
    ENTRY_HASH_TYPE diff = KEY_ENTRY_HASH(ekey) - KEY_ENTRY_HASH(key);
#ifdef DPA__U_SM_BO
    if(!diff && memcmp(&key, &ekey, sizeof(key))<0)
      goto swap;
#endif
    if((ENTRY_HASH_TYPE)(diff >> (sizeof(size_t)*CHAR_BIT-lbsize)) > psl)
      continue;
#ifdef DPA__U_SM_BO
  swap:
#endif
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    {
      void* v = that->value_list[i];
      that->value_list[i] = value;
      value = v;
    }
#endif
    that->key_list[i] = key;
    size_t epsl = (i - (KEY_ENTRY_HASH(ekey) >> (sizeof(size_t)*CHAR_BIT-lbsize))) & mask;
    if(epsl == mask) // Highest calculatable PSL, empty entry, we are done
      return;
    key = ekey;
    psl = epsl;
  }
  dpa_u_unreachable("Hashmap insert failed: %s", "Was the hashmap full? That shouldn't be possible, though...");
}
#endif

#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
// This subroutine is used after an existing value was already found, so we have the index of the entry to be removed already.
static void REMOVE(
  DPA__U_SM_TYPE* that,
  const size_t index,
  const size_t lbsize // Always a power of 2
){
  const size_t mask = (((size_t)1)<<lbsize)-1;
  size_t i = index;
  do {
    size_t j = (i+1) & mask;
    // If the PSL is 0 (entry present, optimal position) or -1 (no entry), we are done.
    if((((KEY_ENTRY_HASH(that->key_list[j])>>(sizeof(size_t)*CHAR_BIT-lbsize))+1-j) & mask) <= 1){
      KEY_ENTRY_HASH(that->key_list[i]) = j<<(sizeof(size_t)*CHAR_BIT-lbsize);
      return;
    }
    that->key_list[i] = that->key_list[j];
    i = j;
  } while(i != index);
}
#endif

#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
dpa__u_api int DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _add)(DPA__U_SM_TYPE* that, DPA__U_SM_KEY_TYPE key){
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
dpa__u_api int DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _exchange)(DPA__U_SM_TYPE* that, DPA__U_SM_KEY_TYPE key, void** value){
#endif
#ifndef DPA__U_SM_NO_BITSET
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  if(that->lbsize == sizeof(DPA__U_SM_KEY_TYPE)*CHAR_BIT) insert_bitfield: {
#endif
    dpa_u_giant_unsigned_int_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(key)];
    dpa_u_giant_unsigned_int_t s = DPA__U_SM_BITMAP_BIT(key);
    bool r = *m & s;
    *m |= s;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    void**restrict o = &that->value_list[key];
    void* v = *value;
    *value = *o;
    *o = v;
#endif
    return r;
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  }
#endif
#endif
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  DPA__U_SM_KEY_ENTRY_TYPE entry = HASH(key);
  struct lookup_result result = LOOKUP(that, entry, that->lbsize);
  if(result.found){
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    void**restrict pv = &that->value_list[result.index];
    void* v = *pv;
    *pv = *value;
    *value = v;
#endif
    return true;
  }
#ifndef DPA__U_SM_NO_BITSET
  that->count += 1;
  const size_t lobst = LIST_OR_BITMAP_SIZE_THRESHOLD(DPA__U_SM_KEY_TYPE);
  if(that->count >= lobst){
    // TODO: convert list to bitfield
    that->lbsize = sizeof(DPA__U_SM_KEY_TYPE)*CHAR_BIT;
    goto insert_bitfield;
  }
  const size_t lbsize = count_to_lbsize(that->count);
  if(lbsize > that->lbsize || !that->key_list){
    //printf("Old size: %zu, new size: %zu\n", ((size_t)1)<<that->lbsize, ((size_t)1)<<lbsize);
    DPA__U_SM_KEY_ENTRY_TYPE*const key_list = malloc((((size_t)1)<<lbsize)*sizeof(*key_list));
    if(!key_list){
      that->count -= 1;
      return -1;
    }
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    void*const value_list = malloc((((size_t)1)<<lbsize)*sizeof(*that->value_list));
    if(!value_list){
      free(key_list);
      that->count -= 1;
      return -1;
    }
#endif
    size_t lbsize = count_to_lbsize(that->count);
    if(that->key_list){
      size_t i, n;
      for(i=0,n=(((size_t)1)<<lbsize)*sizeof(*that->key_list); i<n; n++)
        if(!(KEY_ENTRY_HASH(that->key_list[i]) >> (sizeof(size_t)*CHAR_BIT-that->lbsize)))
          break;
/*      const size_t m2 = (((size_t)1)<<lbsize)-1;
      const size_t m1 = m2>>1;
      const int s = (sizeof(size_t)*CHAR_BIT-lbsize);
      size_t j=i, k=i*2;
      do {
        const size_t hk = KEY_ENTRY_HASH(that->key_list[i]) >> (sizeof(size_t)*CHAR_BIT-lbsize);
        const size_t psl = (j - (k>>1)) & m1;
        if(psl == m1){
          key_list[k++] = (i-1)<<s;
          j++;
          continue;
        }
        const size_t npsl = (k - hk) & m2;
        if(!psl && hk & 1)
          key_list[k++] = (i-1)<<s;
        key_list
        j++;
      } while(i != j);*/
      // TODO
    }else{
      const int s = (sizeof(size_t)*CHAR_BIT-lbsize);
      for(size_t i=0,n=((size_t)1)<<lbsize; i<n; i++)
        key_list[i] = (i-1)<<s;
    }
    free(that->key_list);
    that->key_list = key_list;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    free(that->value_list);
    that->value_list = value_list;
#endif
    that->lbsize = lbsize;
  }
#endif
#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
  INSERT(that, entry, result.index, that->lbsize);
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  INSERT(that, entry, *value, result.index, that->lbsize);
  *value = 0;
#endif
  return false;
#endif
}

#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
dpa__u_api int DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _set)(DPA__U_SM_TYPE* that, DPA__U_SM_KEY_TYPE key, void* value){
  return DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _exchange)(that, key, &value);
}
#endif

dpa__u_api bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _remove)(DPA__U_SM_TYPE* that, DPA__U_SM_KEY_TYPE key){
#ifndef DPA__U_SM_NO_BITSET
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  const size_t lobst = LIST_OR_BITMAP_SIZE_THRESHOLD(DPA__U_SM_KEY_TYPE);
  if(that->count >= lobst){
#endif
    dpa_u_giant_unsigned_int_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(key)];
    dpa_u_giant_unsigned_int_t s = DPA__U_SM_BITMAP_BIT(key);
    bool r = *m & s;
    *m &= ~s;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    that->value_list[key] = 0;
#endif
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    that->count -= 1;
    if(that->count >= lobst)
      return r;
    // TODO: Convert to list
  }
#else
  return r;
#endif
#endif
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  DPA__U_SM_KEY_ENTRY_TYPE entry = HASH(key);
  const size_t lbsize = count_to_lbsize(that->count);
  struct lookup_result result = LOOKUP(that, entry, lbsize);
  if(!result.found)
    return false;
  REMOVE(that, result.index, lbsize);
#endif
  return true;
}

dpa__u_api bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(const DPA__U_SM_TYPE* that, DPA__U_SM_KEY_TYPE key){
#ifndef DPA__U_SM_NO_BITSET
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  const size_t lobst = LIST_OR_BITMAP_SIZE_THRESHOLD(DPA__U_SM_KEY_TYPE);
  if(that->count >= lobst){
#endif
    const dpa_u_giant_unsigned_int_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(key)];
    dpa_u_giant_unsigned_int_t s = DPA__U_SM_BITMAP_BIT(key);
    return *m & s;
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  }
#endif
#endif
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  DPA__U_SM_KEY_ENTRY_TYPE entry = HASH(key);
  const size_t lbsize = count_to_lbsize(that->count);
  return LOOKUP(that, entry, lbsize).found;
#endif
}

#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
dpa__u_api bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get)(const DPA__U_SM_TYPE* that, DPA__U_SM_KEY_TYPE key, void** value){
#ifndef DPA__U_SM_NO_BITSET
  const size_t lobst = LIST_OR_BITMAP_SIZE_THRESHOLD(DPA__U_SM_KEY_TYPE);
  if(that->count >= lobst){
    const dpa_u_giant_unsigned_int_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(key)];
    dpa_u_giant_unsigned_int_t s = DPA__U_SM_BITMAP_BIT(key);
    *value = that->value_list[key];
    return *m & s;
  }
#endif
  DPA__U_SM_KEY_ENTRY_TYPE entry = HASH(key);
  const size_t lbsize = count_to_lbsize(that->count);
  struct lookup_result result = LOOKUP(that, entry, lbsize);
  if(!result.found){
    *value = 0;
    return false;
  }
  *value = that->value_list[result.index];
  return true;
}
dpa__u_api bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get_and_remove)(DPA__U_SM_TYPE* that, DPA__U_SM_KEY_TYPE key, void** value){
#ifndef DPA__U_SM_NO_BITSET
  const size_t lobst = LIST_OR_BITMAP_SIZE_THRESHOLD(DPA__U_SM_KEY_TYPE);
  if(that->count >= lobst){
    dpa_u_giant_unsigned_int_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(key)];
    dpa_u_giant_unsigned_int_t s = DPA__U_SM_BITMAP_BIT(key);
    bool r = *m & s;
    *m &= ~s;
    *value = that->value_list[key];
    that->value_list[key] = 0;
    that->count -= 1;
    if(that->count >= lobst)
      return r;
    // TODO: Convert to list
  }
#endif
  DPA__U_SM_KEY_ENTRY_TYPE entry = HASH(key);
  const size_t lbsize = count_to_lbsize(that->count);
  struct lookup_result result = LOOKUP(that, entry, lbsize);
  if(!result.found){
    *value = 0;
    return false;
  }
  *value = that->value_list[result.index];
  REMOVE(that, result.index, lbsize);
  return true;
}
#endif

#undef HASH
#undef UNHASH

#undef LOOKUP
#undef INSERT
#undef REMOVE

//////////////////////////////////////////////
#undef KEY_ENTRY_HASH
#undef ENTRY_HASH_TYPE
#undef DPA__U_SM_KEY_ENTRY_TYPE
#undef DPA__U_SM_TYPE
#undef DPA__U_SM_KEY_TYPE
#undef DPA__U_SM_NAME
#undef DPA__U_SM_PREFIX

#endif
