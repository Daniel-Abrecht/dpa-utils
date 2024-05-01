///////////////////////////////////////////////////////////////////////////////////////////////////////
// Note: This is a variant of robin hood hashing, but the entries are sorted a bit more strictly.    //
// For values with the same PSL, entries are implicitly sorted by the keys values.                   //
//                                                                                                   //
// In regular robin hood hashing, you check if the new entries PSL is larger than the current one    //
// and if so, swap it. The PSL is a piece of the hash, usually extracted using modulo, minus the     //
// current index, modulo again, in other words the distance from the position to where it hashes to. //
// We use the top bits and take advantage of overflow, so (pseudocode, assuming all unsigned)        //
// `if( i-(a>>s) > i-(b>>s) || ( (a>>s) == (b>>s) && a<b ) )` then swap the entries.                 //
// This is equivalent to: `( (a>>s)-i-1 < (b>>s)-i-1 || ( (a>>s) == (b>>s) && a<b ) )`               //
// This can be simplified: `( a-((i+1)<<s) < b-((i+1)<<s) ) )`                                       //
//                                                                                                   //
// We could store the entries with 1<<s subtracted in advance, to get rid of the +1. But instead,    //
// We just shift the whole list over by one. So instead of entries hashing to `i0=hash>>s`, they     //
// hash to `i0=(hash>>s)+1`                                                                          //
//                                                                                                   //
// This leaves us with: `if( a-(i<<s) < b-(i<<s) )` then swap                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////
//// Top section, common code ////
//////////////////////////////////
#ifndef DPA_U_T_SELF
#define DPA_U_T_SELF

#include <dpa/utils/set.h>
#include <dpa/utils/map.h>
#include <dpa/utils/math.h>
#include <time.h>

struct lookup_result {
  size_t index;
  bool found;
};

static size_t count_to_lbsize(size_t n){
  n += n / DPA__U_SM_SET_OVERSIZE_INVERSE_FACTOR;
  return dpa_u_log2(n|(DPA__U_SM_MIN_SIZE-1))+1;
}

dpa__u_api long dpa_u_total_resize_time;

#define LOOKUP DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _lookup_sub)
#define INSERT DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _insert_sub)
#define REMOVE DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _remove_sub)
#define GROW DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _grow_sub)
#define SHRINK DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _shrink_sub)
#define ALLOCATE_HMS DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _allocate_hms_sub)
#define CONVERT_TO_BITFIELD DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _convert_to_bitfield_sub)
#define CONVERT_TO_LIST DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _convert_to_list_sub)

////////////////////////////////////////////////////////////

#define DPA__U_SM_TEMPLATE <src/set-and-map.c>
#define DPA__U_SM_KIND DPA__U_SM_KIND_SET
#include <dpa/utils/_set-and-map.generator>

#define DPA__U_SM_TEMPLATE <src/set-and-map.c>
#define DPA__U_SM_KIND DPA__U_SM_KIND_MAP
#include <dpa/utils/_set-and-map.generator>

////////////////////////////////////////////////////////////

#else
//////////////////////////
//// Template section ////
//////////////////////////

#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#define BITMAP_KEY entry
#else
#define BITMAP_KEY key
#endif

 extern DPA__U_SM_KEY_ENTRY_TYPE DPA__U_SM_HASH(const DPA__U_SM_KEY_TYPE n);
 extern DPA__U_SM_KEY_TYPE DPA__U_SM_UNHASH(DPA__U_SM_KEY_ENTRY_TYPE e);
 extern DPA__U_SM_KEY_TYPE DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _it_safe_get_key)(const DPA__U_SM_TYPE_IT_S*const it);
 extern DPA__U_SM_KEY_TYPE DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _it_fast_get_key)(const DPA__U_SM_TYPE* that, const DPA__U_SM_TYPE_IT_F*const it);
 extern bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _it_fast_next)(const DPA__U_SM_TYPE* that, DPA__U_SM_TYPE_IT_F* it);
 extern bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _it_fast_prev)(const DPA__U_SM_TYPE* that, DPA__U_SM_TYPE_IT_F* it);
 extern void* DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _it_fast_get_value)(const DPA__U_SM_TYPE* that, const DPA__U_SM_TYPE_IT_F*const it);

#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
static struct lookup_result LOOKUP(
  const DPA__U_SM_TYPE*restrict const that,
  const DPA__U_SM_KEY_ENTRY_TYPE key,
  const size_t lbsize
){
  const int shift = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT-lbsize;
  const DPA__U_SM_ENTRY_HASH_TYPE I = (DPA__U_SM_ENTRY_HASH_TYPE)1<<shift;
  DPA__U_SM_ENTRY_HASH_TYPE i = DPA__U_SM_KEY_ENTRY_HASH(key)+I;
  DPA__U_SM_ENTRY_HASH_TYPE psl_a, psl_b;
// #if defined(__GNUC__) && !defined(__llvm__)
// #pragma GCC ivdep
// #endif
  for(psl_a=-I-1; psl_a > (psl_b=DPA__U_SM_KEY_ENTRY_HASH(that->key_list[i>>shift])-i-1); psl_a-=I,i+=I)
#ifdef DPA__U_SM_BO
    false_match:
#endif
    ;
#ifdef DPA__U_SM_BO
  if(psl_b == psl_a){
    const int cmp = memcmp(&key, &that->key_list[i>>shift], sizeof(key));
    if(!cmp)
      return (struct lookup_result){i>>shift, true};
    if(cmp > 0)
      goto false_match;
  }
  return (struct lookup_result){i>>shift, false};
#else
  return (struct lookup_result){i>>shift, psl_b == psl_a};
#endif
}
#endif

#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
// This subroutine is used after an existing value was already found, so we have the index of where to insert it.
dpa__u_really_inline static inline void INSERT(
  DPA__U_SM_TYPE*restrict const that,
  DPA__U_SM_KEY_ENTRY_TYPE key,
  DPA__U_SM_IF_MAP(void* value,)
  size_t index,
  const size_t lbsize
){
  const int shift = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT-lbsize;
  const DPA__U_SM_ENTRY_HASH_TYPE I = (DPA__U_SM_ENTRY_HASH_TYPE)1<<shift;
  DPA__U_SM_ENTRY_HASH_TYPE i = (DPA__U_SM_ENTRY_HASH_TYPE)index << shift;
  for(;; i+=I){
    const size_t j = i>>shift;
    const DPA__U_SM_KEY_ENTRY_TYPE ekey = that->key_list[j];
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    {
      void* v = that->value_list[j];
      that->value_list[j] = value;
      value = v;
    }
#endif
    that->key_list[j] = key;
    if(DPA__U_SM_KEY_ENTRY_HASH(ekey) == i) // Highest calculatable PSL, empty entry, we are done
      return;
    key = ekey;
  }
}
#endif

#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
// This subroutine is used after an existing value was already found, so we have the index of the entry to be removed already.
static void REMOVE(
  DPA__U_SM_TYPE*restrict const that,
  const size_t index,
  const size_t lbsize // Always a power of 2
){
  const int shift = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT-lbsize;
  const size_t mask = (((size_t)1)<<lbsize)-1;
  size_t i = index;
  do {
    size_t j = (i+1) & mask;
    // If the PSL is 0 (entry present, optimal position) or -1 (no entry), we are done.
    if(((j-(DPA__U_SM_KEY_ENTRY_HASH(that->key_list[j])>>shift)) & mask) <= 1){
      DPA__U_SM_KEY_ENTRY_HASH(that->key_list[i]) = (DPA__U_SM_ENTRY_HASH_TYPE)i<<shift;
      return;
    }
    that->key_list[i] = that->key_list[j];
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    that->value_list[i] = that->value_list[j];
#endif
    i = j;
  } while(i != index);
}
#endif

#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
static bool ALLOCATE_HMS(
  DPA__U_SM_TYPE*restrict const that,
  const size_t lbsize,
  bool init // If GROW() is used to populate the set, it'll fill in the empty keys too, no need to initialize it.
){
  const volatile clock_t start = clock();
  DPA__U_SM_KEY_ENTRY_TYPE*const key_list = malloc((((size_t)1)<<lbsize)*sizeof(*key_list));
  if(!key_list) return false;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  void**const value_list = malloc((((size_t)1)<<lbsize)*sizeof(*value_list));
  if(!value_list){
    free(key_list);
    return false;
  }
#endif
  if(init){
    const int s = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT - lbsize;
    for(size_t i=0,n=((size_t)1)<<lbsize; i<n; i++)
      key_list[i] = (DPA__U_SM_KEY_ENTRY_TYPE){(DPA__U_SM_ENTRY_HASH_TYPE)i<<s};
  }
  that->key_list = key_list;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  that->value_list = value_list;
#endif
  that->lbsize = lbsize;
  that->mode = DPA__U_SM_LIST;
  const volatile clock_t end = clock();
  dpa_u_total_resize_time += end - start;
  return true;
}
#endif


#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
static void GROW(
  DPA__U_SM_TYPE*restrict const old,
  DPA__U_SM_TYPE*restrict const new
){
  const volatile clock_t start = clock();
  DPA__U_SM_KEY_ENTRY_TYPE*restrict const old_key_list = old->key_list;
  DPA__U_SM_KEY_ENTRY_TYPE*restrict const new_key_list = new->key_list;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  void**restrict const old_value_list = old->value_list;
  void**restrict const new_value_list = new->value_list;
#endif
  const size_t olbsize = old->lbsize;
  const size_t lbsize = new->lbsize;
  // Arbitrary growth may be implement in the future, currently only supports growing by 1 lbsize.
  assert(olbsize+1 == lbsize);
  const int s = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT - lbsize;
  size_t i, n;
  for(i=0,n=(((size_t)1)<<olbsize)*sizeof(*old_key_list); i<n; i++)
    if(i == (size_t)((DPA__U_SM_ENTRY_HASH_TYPE)(DPA__U_SM_KEY_ENTRY_HASH(old_key_list[i])+(((DPA__U_SM_ENTRY_HASH_TYPE)1)<<(s+1))) >> (s+1)))
      break;
#ifdef DPA_U_DEBUG
  if(i >= n)
    dpa_u_abort("Bad state: %s\n", "No entry with PSL 0 found!");
#endif
  const size_t m2 = (((size_t)1)<<lbsize)-1;
  const size_t m1 = m2>>1;
  size_t j=i, k=(i*2-1) & m2;
#ifdef DPA_U_DEBUG
  size_t si = 0;
#endif
  do {
    const size_t hk = DPA__U_SM_KEY_ENTRY_HASH(old_key_list[j]) >> s;
    const size_t psl = (j-(hk>>1)-1) & m1;
    for(size_t l=(hk-k+1)&m2; l--; k=(k+1)&m2)
      new_key_list[k] = (DPA__U_SM_KEY_ENTRY_TYPE){(DPA__U_SM_ENTRY_HASH_TYPE)k<<s}; // Empty entries
    if(psl == m1){
      j = (j+1) & m1;
      if(j == i) break;
#ifdef DPA_U_DEBUG
      si++;
#endif
    }
    for(size_t l=1; ((k - ((DPA__U_SM_KEY_ENTRY_HASH(old_key_list[j]) >> s) + 1)) & m2) < l; l++){
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
      new_value_list[k] = old_value_list[j];
#endif
      new_key_list[k] = old_key_list[j];
      k = (k+1) & m2;
      j = (j+1) & m1;
      if(j == i) break;
#ifdef DPA_U_DEBUG
      si++;
#endif
    }
#ifdef DPA_U_DEBUG
    if(si > m1+1)
      dpa_u_abort("Error: %s", "Resize loop did not terminate!");
#endif
  } while(i != j);
  for(const size_t hk = ((DPA__U_SM_KEY_ENTRY_HASH(old_key_list[j]) >> s) + 1) & m2; k!=hk; k=(k+1)&m2)
    new_key_list[k] = (DPA__U_SM_KEY_ENTRY_TYPE){(DPA__U_SM_ENTRY_HASH_TYPE)k<<s}; // Empty entries
  const volatile clock_t end = clock();
  dpa_u_total_resize_time += end - start;
}

/*
// The following version is a little bit slower, except for dpa_uint128_t and dpa_u_bo_unique_t, for those it's faster.
static void GROW(
  DPA__U_SM_TYPE*restrict const old,
  DPA__U_SM_TYPE*restrict const new
){
  const volatile clock_t start = clock();
  DPA__U_SM_KEY_ENTRY_TYPE*restrict const old_key_list = old->key_list;
  DPA__U_SM_KEY_ENTRY_TYPE*restrict const new_key_list = new->key_list;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  void**restrict const old_value_list = old->value_list;
  void**restrict const new_value_list = new->value_list;
#endif
  const size_t olbsize = old->lbsize;
  const size_t lbsize = new->lbsize;
  // Arbitrary growth may be implement in the future, currently only supports growing by 1 lbsize.
  assert(olbsize+1 == lbsize);
  const int j_shift = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT - olbsize;
  const int k_shift = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT - lbsize;
  const DPA__U_SM_ENTRY_HASH_TYPE J = (DPA__U_SM_ENTRY_HASH_TYPE)1<<j_shift;
  const DPA__U_SM_ENTRY_HASH_TYPE K = (DPA__U_SM_ENTRY_HASH_TYPE)1<<k_shift;
  DPA__U_SM_ENTRY_HASH_TYPE i=0;
  do if(i>>j_shift == (DPA__U_SM_KEY_ENTRY_HASH(old_key_list[i>>j_shift])+J)>>j_shift){
    break;
  } while(i+=J);
  DPA__U_SM_ENTRY_HASH_TYPE j=i, k=i-K;
  do {
    const DPA__U_SM_ENTRY_HASH_TYPE hash = DPA__U_SM_KEY_ENTRY_HASH(old_key_list[j>>j_shift]);
    for(size_t l=(DPA__U_SM_ENTRY_HASH_TYPE)(hash-k+K)>>k_shift; l--; k+=K)
      new_key_list[k>>k_shift] = (DPA__U_SM_KEY_ENTRY_TYPE){k}; // Empty entries
    if(j == hash){
      j += J;
      if(j == i) break;
    }
    for(DPA__U_SM_ENTRY_HASH_TYPE l=K; (DPA__U_SM_ENTRY_HASH_TYPE)(k-DPA__U_SM_KEY_ENTRY_HASH(old_key_list[j>>j_shift])-1) < l; l+=K){
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
      new_value_list[k>>k_shift] = old_value_list[j>>j_shift];
#endif
      new_key_list[k>>k_shift] = old_key_list[j>>j_shift];
      k += K;
      j += J;
      if(j == i) break;
    }
  } while(j != i);
  for(const DPA__U_SM_ENTRY_HASH_TYPE hash = DPA__U_SM_KEY_ENTRY_HASH(old_key_list[j>>j_shift])+K; (DPA__U_SM_ENTRY_HASH_TYPE)(hash-k)>>k_shift; k+=K)
    new_key_list[k>>k_shift] = (DPA__U_SM_KEY_ENTRY_TYPE){k}; // Empty entries
  const volatile clock_t end = clock();
  dpa_u_total_resize_time += end - start;
}
*/

#endif

#if !defined(DPA__U_SM_NO_BITSET) && (!defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP)
static bool CONVERT_TO_BITFIELD(DPA__U_SM_TYPE*restrict const that){
  const volatile clock_t start = clock();
  dpa_u_bitmap_entry_t*const restrict bitmask = calloc((((size_t)1<<(sizeof(DPA__U_SM_KEY_TYPE)*CHAR_BIT)) + (sizeof(dpa_u_bitmap_entry_t)*CHAR_BIT-1)) / (sizeof(dpa_u_bitmap_entry_t)*CHAR_BIT), sizeof(dpa_u_bitmap_entry_t));
  if(!bitmask){
    return false;
  }
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  void**const restrict value_list = malloc((((size_t)1)<<(sizeof(DPA__U_SM_KEY_TYPE)*CHAR_BIT))*sizeof(*that->value_list));
  if(!value_list){
    free(bitmask);
    return false;
  }
#endif
  const int s = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT - that->lbsize;
  for(size_t i=0,n=(size_t)1<<that->lbsize; i<n; i++){
    const DPA__U_SM_ENTRY_HASH_TYPE entry = that->key_list[i];
    if(entry == i<<s) // empty entry
      continue;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    value_list[entry] = that->value_list[i];
#endif
    bitmask[DPA__U_SM_BITMAP_OFFSET(entry)] |= DPA__U_SM_BITMAP_BIT(entry);
  }
  free(that->key_list);
  that->bitmask = bitmask;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  free(that->value_list);
  that->value_list = value_list;
#endif
  that->lbsize = sizeof(DPA__U_SM_KEY_TYPE)*CHAR_BIT;
  that->mode = DPA__U_SM_BITMAP;
  const volatile clock_t end = clock();
  dpa_u_total_resize_time += end - start;
  return true;
}
#endif

#if !defined(DPA__U_SM_NO_BITSET) && (!defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP)
static void CONVERT_TO_LIST(DPA__U_SM_TYPE*const restrict that){
  const volatile clock_t start = clock();
  // +1 means it's twice as big as it needs to be. But it also means adding an entry won't expand it immediately.
  int lbsize = count_to_lbsize(that->count)+1;
  const size_t mask = (((size_t)1)<<lbsize)-1;
  const int shift = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT-lbsize;
  DPA__U_SM_TYPE new;
  if(!ALLOCATE_HMS(&new, lbsize, false)){
    // TODO: log warning
    return;
  }
  new.count = that->count;
  new.mode = DPA__U_SM_LIST;
  size_t j=0;
  DPA__U_SM_ENTRY_HASH_TYPE i=0;
  // Add all the entries
  do {
    if( that->bitmask[DPA__U_SM_BITMAP_OFFSET(i)] & DPA__U_SM_BITMAP_BIT(i) ){
      j = (j+1) & mask;
      new.key_list[j] = i;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
      new.value_list[j] = that->value_list[i];
#endif
    }else{
      if((j<<shift)+((1<<shift)-1) == i){
        j = (j+1) & mask;
        new.key_list[j] = j<<shift;
      }
    }
  } while((i=i+1));
  // j may have overflowed, we need to re-add / move the following entries.
  do {
    if((j<<shift)+((1<<shift)-1) == i)
      break; // Empty or same entry, nothing to move anymore, we are done.
    if(!( that->bitmask[DPA__U_SM_BITMAP_OFFSET(i)] & DPA__U_SM_BITMAP_BIT(i) ))
      continue;
    j = (j+1) & mask;
    new.key_list[j] = i;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    new.value_list[j] = that->value_list[i];
#endif
  } while((i=i+1));
  free(that->bitmask);
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  free(that->value_list);
#endif
  *that = new;
  const volatile clock_t end = clock();
  dpa_u_total_resize_time += end - start;
}
#endif

#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
static void SHRINK(DPA__U_SM_TYPE*const restrict that){
  const volatile clock_t start = clock();
  int lbsize = count_to_lbsize(that->count)+1;
  const int i_shift = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT-that->lbsize;
  const int j_shift = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT-lbsize;
  const DPA__U_SM_ENTRY_HASH_TYPE I = (DPA__U_SM_ENTRY_HASH_TYPE)1<<i_shift;
  const DPA__U_SM_ENTRY_HASH_TYPE J = (DPA__U_SM_ENTRY_HASH_TYPE)1<<j_shift;
  DPA__U_SM_TYPE new;
  if(!ALLOCATE_HMS(&new, lbsize, false)){
    // TODO: log warning
    return;
  }
  new.count = that->count;
  DPA__U_SM_ENTRY_HASH_TYPE j=0, i=0;
  do {
    const size_t l = j>>j_shift;
    const size_t k = i>>i_shift;
    if( DPA__U_SM_KEY_ENTRY_HASH(that->key_list[k]) != i ){
      new.key_list[l] = that->key_list[k];
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
      new.value_list[l] = that->value_list[k];
#endif
      j += J;
    }else{
      if(j == i){
        new.key_list[l] = (DPA__U_SM_KEY_ENTRY_TYPE){j};
        j += J;
      }
    }
    i += I;
  } while(i);
  do {
    if(j == i)
      break; // Empty or same entry, nothing to move anymore, we are done.
    const size_t k = i>>i_shift;
    if( DPA__U_SM_KEY_ENTRY_HASH(that->key_list[k]) != i ){
      const size_t l = j>>j_shift;
      new.key_list[l] = that->key_list[k];
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
      new.value_list[l] = that->value_list[k];
#endif
      j += J;
    }
    i += I;
  } while(i);
  free(that->key_list);
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  free(that->value_list);
#endif
  *that = new;
  const volatile clock_t end = clock();
  dpa_u_total_resize_time += end - start;
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

#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
extern int DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _exchange)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key, void*restrict*const value);

dpa__u_api int DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _list_exchange)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key, void*restrict* value){
  const int lbsize = count_to_lbsize(that->count);
  if(dpa_u_unlikely(lbsize > that->lbsize)){
#ifndef DPA__U_SM_NO_BITSET
    if(that->count >= DPA__U_SM_LIST_OR_BITMAP_SIZE_THRESHOLD){
      if(!CONVERT_TO_BITFIELD(that))
        return -1;
      return DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _bitmap_exchange)(that, key, value);
    }
#endif
    DPA__U_SM_TYPE new;
    if(!ALLOCATE_HMS(&new, lbsize, false))
      return -1;
    new.count = that->count;
    GROW(that, &new);
    free(that->key_list);
    free(that->value_list);
    *that = new;
  }
  const DPA__U_SM_KEY_ENTRY_TYPE entry = DPA__U_SM_HASH(key);
  struct lookup_result result = LOOKUP(that, entry, lbsize);
  if(result.found){
    void*const v = *value;
    *value = that->value_list[result.index];
    that->value_list[result.index] = v;
    return true;
  }
  INSERT(that, entry, DPA__U_SM_IF_MAP(*value,) result.index, lbsize);
  that->count++;
  return false;
}

#ifndef DPA__U_SM_NO_BITSET
dpa__u_api int DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _bitmap_exchange)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key, void*restrict* value){
  const DPA__U_SM_ENTRY_HASH_TYPE hash = DPA__U_SM_HASH(key);
  dpa_u_bitmap_entry_t*restrict const b = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(hash)];
  const dpa_u_bitmap_entry_t m = DPA__U_SM_BITMAP_BIT(hash);
  const bool r = *b & m;
  *b |= m;
  if(r){
    void*const v = *value;
    *value = that->value_list[hash];
    that->value_list[hash] = v;
    return true;
  }
  that->count++;
  return false;
}
#endif

#endif

#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
extern int DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _add)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key);
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
extern int DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _set)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key, void*restrict value);
#endif

#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
dpa__u_api int DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _list_add_first)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
dpa__u_api int DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _list_set_first)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key, void*restrict value){
#endif
  const int lbsize = count_to_lbsize(1);
  if(!ALLOCATE_HMS(that, lbsize, true))
    return -1;
  that->count = 1;
  const int shift = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT-lbsize;
  const DPA__U_SM_ENTRY_HASH_TYPE I = (DPA__U_SM_ENTRY_HASH_TYPE)1<<shift;
  const DPA__U_SM_KEY_ENTRY_TYPE entry = DPA__U_SM_HASH(key);
  size_t i = (DPA__U_SM_ENTRY_HASH_TYPE)(DPA__U_SM_KEY_ENTRY_HASH(entry)+I)>>shift;
  that->key_list[i] = entry;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  that->value_list[i] = value;
#endif
  return false;
}
#endif

#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
dpa__u_api int DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _list_add)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
dpa__u_api int DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _list_set)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key, void*restrict value){
#endif
  const int lbsize = count_to_lbsize(that->count);
  if(dpa_u_unlikely(lbsize > that->lbsize)){
#ifndef DPA__U_SM_NO_BITSET
    if(that->count >= DPA__U_SM_LIST_OR_BITMAP_SIZE_THRESHOLD){
      if(!CONVERT_TO_BITFIELD(that))
        return -1;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
      return DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _bitmap_add)(that, key);
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
      return DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _bitmap_set)(that, key, value);
#endif
    }
#endif
    DPA__U_SM_TYPE new;
    if(!ALLOCATE_HMS(&new, lbsize, false))
      return -1;
    new.count = that->count;
    GROW(that, &new);
    free(that->key_list);
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    free(that->value_list);
#endif
    *that = new;
  }
  const DPA__U_SM_KEY_ENTRY_TYPE entry = DPA__U_SM_HASH(key);
  struct lookup_result result = LOOKUP(that, entry, lbsize);
  if(result.found){
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
    that->value_list[result.index] = value;
#endif
    return true;
  }
  INSERT(that, entry, DPA__U_SM_IF_MAP(value,) result.index, lbsize);
  that->count++;
  return false;
}
#endif

#ifndef DPA__U_SM_NO_BITSET
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#if DPA__U_SM_KIND == DPA__U_SM_KIND_SET
dpa__u_api int DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _bitmap_add)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
#elif DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
dpa__u_api int DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _bitmap_set)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key, void*restrict value){
#endif
  const DPA__U_SM_ENTRY_HASH_TYPE hash = DPA__U_SM_HASH(key);
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  that->value_list[hash] = value;
#endif
  dpa_u_bitmap_entry_t*restrict const b = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(hash)];
  const dpa_u_bitmap_entry_t m = DPA__U_SM_BITMAP_BIT(hash);
  const bool r = *b & m;
  *b |= m;
  if(!r) that->count++;
  return r;
}
#endif
#endif


#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#ifndef DPA__U_SM_NO_BITSET
dpa__u_api bool DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _remove_bitmap)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
  const DPA__U_SM_KEY_ENTRY_TYPE entry = DPA__U_SM_HASH(key);
  dpa_u_bitmap_entry_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(entry)];
  const dpa_u_bitmap_entry_t s = DPA__U_SM_BITMAP_BIT(entry);
  bool r = *m & s;
  *m &= ~s;
  if(r && --that->count < DPA__U_SM_LIST_OR_BITMAP_SIZE_THRESHOLD/2)
    CONVERT_TO_LIST(that);
  return r;
}
#endif

#ifdef DPA__U_SM_NO_BITSET
dpa__u_api bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _remove)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
  if(!that->count)
    return false;
#else
extern bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _remove)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key);
dpa__u_api bool DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _remove_list)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
#endif
  const DPA__U_SM_KEY_ENTRY_TYPE entry = DPA__U_SM_HASH(key);
  struct lookup_result result = LOOKUP(that, entry, that->lbsize);
  if(!result.found)
    return false;
  REMOVE(that, result.index, that->lbsize);
  const size_t count = --that->count;
  if(dpa_u_unlikely(!count))
    DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _clear)(that);
  const int lbsize = count_to_lbsize(count);
  if(that->lbsize-lbsize >= 2)
    SHRINK(that);
  return true;
}
#endif


#ifndef DPA__U_SM_NO_BITSET
extern bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(const DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key);
#endif
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#ifdef DPA__U_SM_NO_BITSET
dpa__u_api bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _has)(const DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
  if(!that->count)
    return false;
#else
dpa__u_api bool DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _list_has)(const DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
#endif
  return LOOKUP(that, DPA__U_SM_HASH(key), that->lbsize).found;
}
#endif


#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP

#ifndef DPA__U_SM_NO_BITSET
extern dpa_u_optional_pointer_t DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get)(const DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key);
#endif

#ifdef DPA__U_SM_NO_BITSET
dpa__u_api dpa_u_optional_pointer_t DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get)(const DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
  if(!that->count)
    return (dpa_u_optional_pointer_t){0};
#else
dpa__u_api dpa_u_optional_pointer_t DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _list_get)(const DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
#endif
  const struct lookup_result result = LOOKUP(that, DPA__U_SM_HASH(key), that->lbsize);
  if(!result.found)
    return (dpa_u_optional_pointer_t){0};
  return (dpa_u_optional_pointer_t){
    .value = that->value_list[result.index],
    .present = true
  };
}

#endif


#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#ifndef DPA__U_SM_NO_BITSET
dpa__u_api dpa_u_optional_pointer_t DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _get_and_remove_bitmap)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
  const DPA__U_SM_KEY_ENTRY_TYPE entry = DPA__U_SM_HASH(key);
  dpa_u_bitmap_entry_t*restrict const m = &that->bitmask[DPA__U_SM_BITMAP_OFFSET(entry)];
  const dpa_u_bitmap_entry_t s = DPA__U_SM_BITMAP_BIT(entry);
  bool r = *m & s;
  *m &= ~s;
  if(!r)
    return (dpa_u_optional_pointer_t){0};
  const dpa_u_optional_pointer_t result = {
    .value = that->value_list[entry],
    .present = true,
  };
  if(--that->count < DPA__U_SM_LIST_OR_BITMAP_SIZE_THRESHOLD/2)
    CONVERT_TO_LIST(that);
  return result;
}
#endif

#ifdef DPA__U_SM_NO_BITSET
dpa__u_api dpa_u_optional_pointer_t DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get_and_remove)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
  if(!that->count)
    return (dpa_u_optional_pointer_t){0};
#else
extern dpa_u_optional_pointer_t DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _get_and_remove)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key);
dpa__u_api dpa_u_optional_pointer_t DPA_U_CONCAT_E(DPA___U_SM_PREFIX, _get_and_remove_list)(DPA__U_SM_TYPE*restrict that, DPA__U_SM_KEY_TYPE key){
#endif
  const DPA__U_SM_KEY_ENTRY_TYPE entry = DPA__U_SM_HASH(key);
  struct lookup_result result = LOOKUP(that, entry, that->lbsize);
  if(!result.found)
    return (dpa_u_optional_pointer_t){0};
  const dpa_u_optional_pointer_t ret = {
    .value = that->value_list[result.index],
    .present = true,
  };
  REMOVE(that, result.index, that->lbsize);
  const size_t count = --that->count;
  if(dpa_u_unlikely(!count))
    DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _clear)(that);
  const int lbsize = count_to_lbsize(count);
  if(that->lbsize-lbsize >= 2)
    SHRINK(that);
  return ret;
}
#endif
#endif


#if defined(DPA__U_SM_MICRO_SET) && DPA__U_SM_KIND == DPA__U_SM_KIND_SET
 extern bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _copy)(DPA__U_SM_TYPE*restrict dst, const DPA__U_SM_TYPE*restrict src);
#else
dpa__u_api bool DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _copy)(DPA__U_SM_TYPE*restrict dst, const DPA__U_SM_TYPE*restrict src){
  if(src->mode == DPA__U_SM_EMPTY){
    memset(dst, 0, sizeof(*dst));
    return true;
  }
  const size_t lbsize = src->lbsize;
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  void**const value_list = malloc((((size_t)1)<<lbsize)*sizeof(*value_list));
  if(!value_list)
    goto error;
#endif
  switch(src->mode){
    case DPA__U_SM_LIST: {
      DPA__U_SM_KEY_ENTRY_TYPE*const key_list = malloc((((size_t)1)<<lbsize)*sizeof(*key_list));
      if(!key_list)
        goto error_1;
      *dst = *src;
      memcpy(key_list, src->key_list, (((size_t)1)<<lbsize)*sizeof(*key_list));
      dst->key_list = key_list;
    } break;
#ifndef DPA__U_SM_NO_BITSET
    case DPA__U_SM_BITMAP: {
      const size_t size = ((((size_t)1<<(sizeof(DPA__U_SM_KEY_TYPE)*CHAR_BIT)) + (sizeof(dpa_u_bitmap_entry_t)*CHAR_BIT-1)) / (sizeof(dpa_u_bitmap_entry_t)*CHAR_BIT)) * sizeof(dpa_u_bitmap_entry_t);
      dpa_u_bitmap_entry_t*const bitmask = malloc(size);
      if(!bitmask)
        goto error_1;
      *dst = *src;
      memcpy(bitmask, src->bitmask, size);
      dst->bitmask = bitmask;
    } break;
#endif
  }
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  memcpy(value_list, src->value_list, (((size_t)1)<<lbsize)*sizeof(*value_list));
  dst->value_list = value_list;
#endif
  return true;
error_1:
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
  free(value_list);
#endif
#if DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
error:
#endif
  return false;
}
#endif


dpa__u_api void DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _dump_hashmap_key_hashes)(DPA__U_SM_TYPE* that){
  (void)that;
#if !defined(DPA__U_SM_MICRO_SET) || DPA__U_SM_KIND == DPA__U_SM_KIND_MAP
#ifndef DPA__U_SM_NO_BITSET
  const size_t lobst = DPA__U_SM_LIST_OR_BITMAP_SIZE_THRESHOLD;
  if(that->count >= lobst)
    return;
#endif
  printf("%8s: %8s %4s %8s\n", "index", "hash idx", "PSL", "hash");
  int s = sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT - that->lbsize;
  size_t i_mask = ((size_t)1<<that->lbsize)-1;
  for(size_t i=0,n=(size_t)1<<that->lbsize; i<n; i++){
    DPA__U_SM_ENTRY_HASH_TYPE h = DPA__U_SM_KEY_ENTRY_HASH(that->key_list[i]);
    size_t hindex = h >> s;
    size_t PSL = (i - hindex - 1) & i_mask;
    printf("%8zX: %8zX %5zX ", i, hindex, PSL);
    for(unsigned i=(sizeof(DPA__U_SM_ENTRY_HASH_TYPE)*CHAR_BIT);i;i-=4)
      printf("%01X",(unsigned)((h>>(i-4))&0xF));
    puts("");
  }
#endif
}

 extern size_t DPA_U_CONCAT_E(DPA__U_SM_PREFIX, _count)(const DPA__U_SM_TYPE* that);

#undef BITMAP_KEY

#endif
