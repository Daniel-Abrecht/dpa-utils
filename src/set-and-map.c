//////////////////////////////////
//// Top section, common code ////
//////////////////////////////////
#ifndef DPA_U_T_SELF
#define DPA_U_T_SELF

#include <dpa/utils/set.h>
#include <dpa/utils/map.h>
#include <dpa/utils/math.h>
#include <dpa/utils/_math.h>

#define DPA__U_SM_BITMAP_OFFSET(INDEX) ((INDEX)/(sizeof(dpa_u_bitmap_entry_t)*CHAR_BIT))
#define DPA__U_SM_BITMAP_BIT(INDEX) (((dpa_u_bitmap_entry_t)1)<<((INDEX)%(sizeof(dpa_u_bitmap_entry_t)*CHAR_BIT)))

struct lookup_result {
  size_t index;
  bool found;
};

// Ensure there is some free space left 100/8 = 12.5%
#define SET_OVERSIZE_INVERSE_FACTOR 8

enum { MIN_LBSIZE = 5 };
enum { MIN_SIZE = 1u<<MIN_LBSIZE };
static size_t count_to_lbsize(size_t n){
  n += n / SET_OVERSIZE_INVERSE_FACTOR;
  return dpa_u_log2(n|(MIN_SIZE-1))+1;
}

// Note: Not rounded up to dpa_u_bitmap_entry_t size.
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
  return ((DPA__U_SM_KEY_ENTRY_TYPE)x);
  //return ((DPA__U_SM_KEY_ENTRY_TYPE)x) * dpa__u_choose_prime(DPA__U_SM_KEY_ENTRY_TYPE);
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
  DPA__U_SM_KEY_ENTRY_TYPE key,
  const size_t lbsize
){
  const size_t mask = (((size_t)1)<<lbsize)-1;
  const int shift = sizeof(ENTRY_HASH_TYPE)*CHAR_BIT-lbsize;
  size_t i = KEY_ENTRY_HASH(key) >> shift;
  if(!that->key_list)
    return (struct lookup_result){i, false};
  // The actual PSL is psl>>shift. We take the difference of our current hash with the entries hash,
  // instead of considering it's psl (the difference to it's index), so the entries PSL will have an offset.
  // On the other hand, we don't need to compare entries with the same psl to get a higher total order.
  const ENTRY_HASH_TYPE I = 1<<shift;
  KEY_ENTRY_HASH(key) -= I;
  ENTRY_HASH_TYPE hash = KEY_ENTRY_HASH(key);
  ENTRY_HASH_TYPE psl = hash - ((ENTRY_HASH_TYPE)i<<shift);
  while(1){
    const DPA__U_SM_KEY_ENTRY_TYPE ekey = that->key_list[i];
    ENTRY_HASH_TYPE diff = KEY_ENTRY_HASH(ekey) - ((ENTRY_HASH_TYPE)i<<shift);
    // printf("L d: %zX %zX %zX %zX %zX\n", (size_t)psl, (size_t)diff, (size_t)(psl-diff), (size_t)(ENTRY_HASH_TYPE)((psl-diff) >> shift), i);
    if(diff == psl){
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
    //printf("L a:%zX b:%zX d:%zX, p:%zX, d-p:%zX psl:%zX=%zX, i=%zX\n" , (size_t)hash, (size_t)KEY_ENTRY_HASH(ekey), (size_t)diff, (size_t)psl, (size_t)(diff-psl), (size_t)((i-(KEY_ENTRY_HASH(ekey)>>shift))&mask), (size_t)(((diff-psl)>>shift)&mask), i);
    if(psl <= (diff-1)) // We use the highest possible PSL for the empty entry. The highest PSL always wins! For an empty entry, diff is going to be 0, we subtract 1 to force an overflow.
      return (struct lookup_result){i, false};
    psl -= I;
    i = (i+1) & mask;
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
  const int shift = sizeof(ENTRY_HASH_TYPE)*CHAR_BIT-lbsize;
  const size_t mask = (((size_t)1)<<lbsize)-1;
  // The actual PSL is psl>>shift. We take the difference of our current hash with the entries hash,
  // instead of considering it's psl (the difference to it's index), so the entries PSL will have an offset.
  // On the other hand, we don't need to compare entries with the same psl to get a higher total order.
  const ENTRY_HASH_TYPE I = 1<<shift;
  KEY_ENTRY_HASH(key) -= I;
  ENTRY_HASH_TYPE psl = KEY_ENTRY_HASH(key) - ((ENTRY_HASH_TYPE)i<<shift);
  for(;; psl -= I, i=((i+1)&mask)){
    const DPA__U_SM_KEY_ENTRY_TYPE ekey = that->key_list[i];
    ENTRY_HASH_TYPE diff = KEY_ENTRY_HASH(ekey) - ((ENTRY_HASH_TYPE)i<<shift);
    //printf("i a:%zX b:%zX d-p:%zX psl:%zX=%zX, i=%zX\n" , (size_t)KEY_ENTRY_HASH(key), (size_t)KEY_ENTRY_HASH(ekey),(size_t)(diff-psl), (size_t)((i-(KEY_ENTRY_HASH(ekey)>>shift))&mask), (size_t)(((diff-psl)>>shift)&mask), i);
    // printf("i d: %zX %zX %zX %zX %zX\n", (size_t)psl, (size_t)diff, (size_t)(psl-diff), (size_t)(ENTRY_HASH_TYPE)((psl-diff) >> shift), i);
#ifdef DPA__U_SM_BO
    if(diff == psl && memcmp(&key, &ekey, sizeof(key))<0)
      goto swap;
#endif
    // Allow diff == 0
    if(psl > (diff-1))
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
    // printf("swap: %zX %zX %zX %zX %zX\n", i, (size_t)KEY_ENTRY_HASH(ekey)>>shift, (size_t)KEY_ENTRY_HASH(key)>>shift, (size_t)KEY_ENTRY_HASH(ekey), (size_t)KEY_ENTRY_HASH(key));
    that->key_list[i] = key;
    // printf("%zX %zX\n",(size_t)diff,(size_t)psl);
    if(!diff) // Highest calculatable PSL, empty entry, we are done
      return;
    key = ekey;
    psl = KEY_ENTRY_HASH(ekey) - ((ENTRY_HASH_TYPE)i<<shift);
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
    if((((KEY_ENTRY_HASH(that->key_list[j])>>(sizeof(ENTRY_HASH_TYPE)*CHAR_BIT-lbsize))+1-j) & mask) <= 1){
      KEY_ENTRY_HASH(that->key_list[i]) = j<<(sizeof(ENTRY_HASH_TYPE)*CHAR_BIT-lbsize);
      return;
    }
    that->key_list[i] = that->key_list[j];
    i = j;
  } while(i != index);
}
#endif

dpa__u_api void DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _clear)(DPA__U_SM_TYPE* that){
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  free(that->key_list);
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  free(that->value_list);
#endif
  memset(that, 0, sizeof(*that));
#else
  (void)that;
#endif
}

#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
dpa__u_api int DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _add)(DPA__U_SM_TYPE* that, DPA__U_SM_KEY_TYPE key){
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
dpa__u_api int DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _exchange)(DPA__U_SM_TYPE* that, DPA__U_SM_KEY_TYPE key, void** value){
#endif
#ifndef DPA__U_SM_NO_BITSET
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  if(that->lbsize == sizeof(DPA__U_SM_KEY_TYPE)*CHAR_BIT) insert_bitfield: {
#endif
    dpa_u_bitmap_entry_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(key)];
    dpa_u_bitmap_entry_t s = DPA__U_SM_BITMAP_BIT(key);
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
  if(!that->lbsize)
    that->lbsize = MIN_LBSIZE;
  DPA__U_SM_KEY_ENTRY_TYPE entry = HASH(key);
// lt:;
  struct lookup_result result = LOOKUP(that, entry, that->lbsize);
  printf("add: lookup 0x%zX, 0x%zX: %c 0x%zX\n", (size_t)KEY_ENTRY_HASH(entry), (size_t)(KEY_ENTRY_HASH(entry)>>(sizeof(ENTRY_HASH_TYPE)*CHAR_BIT-that->lbsize)), result.found ? 'Y' : 'N', result.index);
  if(result.found){
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    void**restrict pv = &that->value_list[result.index];
    void* v = *pv;
    *pv = *value;
    *value = v;
#endif
    return true;
  }
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  that->count += 1;
#ifndef DPA__U_SM_NO_BITSET
  const size_t lobst = LIST_OR_BITMAP_SIZE_THRESHOLD(DPA__U_SM_KEY_TYPE);
  if(that->count >= lobst){
    // TODO: convert list to bitfield
    dpa_u_abort("TODO: %s", "convert list to bitfield");
    that->lbsize = sizeof(DPA__U_SM_KEY_TYPE)*CHAR_BIT;
    goto insert_bitfield;
  }
#endif
  const size_t lbsize = count_to_lbsize(that->count);
  const int s = sizeof(ENTRY_HASH_TYPE)*CHAR_BIT - lbsize;
  if(lbsize > that->lbsize || !that->key_list){
    printf("Old size: %zu, new size: %zu\n", ((size_t)1)<<that->lbsize, ((size_t)1)<<lbsize);
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
    if(that->key_list){
      DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _dump_hashmap_key_hashes)(that);
      size_t i, n;
      for(i=0,n=(((size_t)1)<<that->lbsize)*sizeof(*that->key_list); i<n; i++)
        if(i == (size_t)((KEY_ENTRY_HASH(that->key_list[i])+(((ENTRY_HASH_TYPE)1)<<(s+1))) >> (s+1)))
          break;
      const size_t m2 = (((size_t)1)<<lbsize)-1;
      const size_t m1 = m2>>1;
      size_t j=i, k=i*2, o=0;
      do {
        // FIXME: For convenience, the PSL bits are pre-subtracted with 1, I haven't updated this loop to deal with that yet!
        const size_t hk = ((KEY_ENTRY_HASH(that->key_list[j]) >> s) + 2) & m2;
        const size_t psl = (j-(hk>>1)) & m1;
        const size_t psl2 = (k-hk) & m2;
        printf("%zX,%zX: %zX %zX %zX %zX\n", j,k, psl, psl2, o, hk);
        if(psl < o){
          // Consecutive entries
          printf("Copying consecutive entry old[%zX] -> new[%zX]\n",j,k);
          key_list[k] = that->key_list[j];
          KEY_ENTRY_HASH(key_list[k]) += (ENTRY_HASH_TYPE)1<<s;
          k = (k+1) & m2;
          goto next;
        }
        for(; k!=hk; k=(k+1)&m2){
          printf("Entry %zX empty\n", k);
          key_list[k] = (DPA__U_SM_KEY_ENTRY_TYPE){k<<s}; // Empty entries
        }
        // End of consecutive entry without PSL=0. Next entry either PSL=0, or empty
        if(psl == m1){
          // Empty entry
          /*printf("One more empty entry at %zX\n",k);
          key_list[k] = (DPA__U_SM_KEY_ENTRY_TYPE){k<<s};
          o = -1;*/
          o = -1;
        }else{
          printf("Copying entry old[%zX] -> new[%zX]\n",j,k);
          key_list[k] = that->key_list[j];
          KEY_ENTRY_HASH(key_list[k]) += (ENTRY_HASH_TYPE)1<<s;
          o = -1;
          k = (k+1) & m2;
        }
      next:
        o++;
        j = (j+1) & m1;
      } while(i != j);
    }else{
      for(size_t i=0,n=((size_t)1)<<lbsize; i<n; i++)
        key_list[i] = (DPA__U_SM_KEY_ENTRY_TYPE){(ENTRY_HASH_TYPE)i<<s};
       // that->key_list = key_list;
       // goto lt;
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
    dpa_u_bitmap_entry_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(key)];
    dpa_u_bitmap_entry_t s = DPA__U_SM_BITMAP_BIT(key);
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
    const dpa_u_bitmap_entry_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(key)];
    dpa_u_bitmap_entry_t s = DPA__U_SM_BITMAP_BIT(key);
    return *m & s;
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  }
#endif
#endif
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  DPA__U_SM_KEY_ENTRY_TYPE entry = HASH(key);
//  return LOOKUP(that, entry, that->lbsize).found;
  struct lookup_result result = LOOKUP(that, entry, that->lbsize);
  printf("has: lookup 0x%zX, 0x%zX: %c 0x%zX\n", (size_t)KEY_ENTRY_HASH(entry), (size_t)(KEY_ENTRY_HASH(entry)>>(sizeof(ENTRY_HASH_TYPE)*CHAR_BIT-that->lbsize)), result.found ? 'Y' : 'N', result.index);
  return result.found;
#endif
}

#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
dpa__u_api bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get)(const DPA__U_SM_TYPE* that, DPA__U_SM_KEY_TYPE key, void** value){
#ifndef DPA__U_SM_NO_BITSET
  const size_t lobst = LIST_OR_BITMAP_SIZE_THRESHOLD(DPA__U_SM_KEY_TYPE);
  if(that->count >= lobst){
    const dpa_u_bitmap_entry_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(key)];
    dpa_u_bitmap_entry_t s = DPA__U_SM_BITMAP_BIT(key);
    *value = that->value_list[key];
    return *m & s;
  }
#endif
  DPA__U_SM_KEY_ENTRY_TYPE entry = HASH(key);
  struct lookup_result result = LOOKUP(that, entry, that->lbsize);
  printf("get: lookup 0x%zX, 0x%zX: %c 0x%zX\n", (size_t)KEY_ENTRY_HASH(entry), (size_t)(KEY_ENTRY_HASH(entry)>>(sizeof(ENTRY_HASH_TYPE)*CHAR_BIT-that->lbsize)), result.found ? 'Y' : 'N', result.index);
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
    dpa_u_bitmap_entry_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(key)];
    dpa_u_bitmap_entry_t s = DPA__U_SM_BITMAP_BIT(key);
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

dpa__u_api void DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _dump_hashmap_key_hashes)(DPA__U_SM_TYPE* that){
  (void)that;
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#ifndef DPA__U_SM_NO_BITSET
  const size_t lobst = LIST_OR_BITMAP_SIZE_THRESHOLD(DPA__U_SM_KEY_TYPE);
  if(that->count >= lobst)
    return;
#endif
  printf("%8s: %8s %4s %8s\n", "index", "hash idx", "PSL", "hash");
  dpa_u_bitmap_entry_t s = sizeof(ENTRY_HASH_TYPE)*CHAR_BIT - that->lbsize;
  dpa_u_bitmap_entry_t i_mask = ((size_t)1<<that->lbsize)-1;
  for(size_t i=0,n=(size_t)1<<that->lbsize; i<n; i++){
    ENTRY_HASH_TYPE h = KEY_ENTRY_HASH(that->key_list[i]);
    h += (ENTRY_HASH_TYPE)1 << s;
    size_t hindex = h >> s;
    size_t PSL = (i - hindex) & i_mask;
    printf("%8zX: %8zX %4zX ", i, hindex, PSL);
    for(unsigned i=(sizeof(ENTRY_HASH_TYPE)*CHAR_BIT);i;i-=4)
      printf("%01X",(unsigned)((h>>(i-4))&0xF));
    puts("");
  }
#endif
}


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
