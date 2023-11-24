
// A bo should always have a type set. If that was forgotten, and it was 0 initialised, the type is 0.
// Because of this, we so not define a type 0, and trying to get the data or size of such a bo may abort().
// It could still be useful to chek if a bo has ben set when passing a pointer to it to a function, though.

#define dpa_u_bo_any_type_list(X) \
  X((DPA_U_BO_INLINE, 1)) \
  X((DPA_U_BO_UNIQUE_HASHMAP)) \
  X((DPA_U_BO_SIMPLE)) \
  X((DPA_U_BO_HASHED)) \
  X((DPA_U_BO_REFCOUNTED)) \
  X((DPA_U_BO_REFCOUNTED_HASHED))

DPA_U_ENUM(dpa_u_bo_any_type)

#define DPA_U_BO_TYPES(T) \
  T(dpa_u_bo_inline) \
  T(dpa_u_bo_unique_hashmap) \
  T(dpa_u_bo_simple_ro) \
  T(dpa_u_bo_simple) \
  T(dpa_u_bo_unique) \
  T(dpa_u_bo_ro) \
  T(dpa_u_bo) \
  T(dpa_u_bo_hashed_ro) \
  T(dpa_u_bo_hashed) \
  T(dpa_u_bo_refcounted_ro) \
  T(dpa_u_bo_refcounted) \
  T(dpa_u_bo_refcounted_hashed_ro) \
  \
  T(dpa_u_any_bo_inline) \
  T(dpa_u_any_bo_unique_hashmap) \
  T(dpa_u_any_bo_simple_ro) \
  T(dpa_u_any_bo_simple) \
  T(dpa_u_any_bo_unique) \
  T(dpa_u_any_bo_ro) \
  T(dpa_u_any_bo) \
  \
  T(dpa_u_any_bo_hashed_ro) \
  T(dpa_u_any_bo_hashed) \
  T(dpa_u_any_bo_refcounted_ro) \
  T(dpa_u_any_bo_refcounted) \
  T(dpa_u_any_bo_refcounted_hashed_ro) \
  \
  T(dpa_u_bo_with_hash_ro) \
  T(dpa_u_bo_with_hash) \
  T(dpa_u_bo_gc_ro) \
  T(dpa_u_bo_with_refcount_ro) \
  T(dpa_u_bo_with_refcount) \
  T(dpa_u_bo_with_refcount_and_hash_ro)

#define DPA__U_BO_TYPE_CASES(S,C) case C:

#define case_dpa_u_bo_inline_t dpa_u_bo_inline_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_inline_m_type(F) \
  F(  1,DPA_U_BO_INLINE)
#define case_dpa_u_any_bo_inline_t dpa_u_any_bo_inline_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_inline_m_type(F) \
  F( A1,DPA_U_BO_INLINE)
#define case_dpa_u_bo_simple_t dpa_u_bo_simple_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_simple_m_type(F) \
  F(  2,DPA_U_BO_SIMPLE)
#define case_dpa_u_any_bo_simple_t dpa_u_any_bo_simple_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_simple_m_type(F) \
  F( A2,DPA_U_BO_SIMPLE) \
  F( A2,DPA_U_BO_HASHED) \
  F( A2,DPA_U_BO_REFCOUNTED)
#define case_dpa_u_bo_unique_hashmap_t dpa_u_bo_unique_hashmap_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_unique_hashmap_m_type(F) \
  F(  3,DPA_U_BO_UNIQUE_HASHMAP)
#define case_dpa_u_any_bo_unique_hashmap_t dpa_u_any_bo_unique_hashmap_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_unique_hashmap_m_type(F) \
  F( A3,DPA_U_BO_UNIQUE_HASHMAP)
#define case_dpa_u_bo_simple_ro_t dpa_u_bo_simple_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_simple_ro_m_type(F) \
  F(  4,DPA_U_BO_SIMPLE)
#define case_dpa_u_any_bo_simple_ro_t dpa_u_any_bo_simple_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_simple_ro_m_type(F) \
  F( A4,DPA_U_BO_SIMPLE) \
  F( A4,DPA_U_BO_UNIQUE_HASHMAP) \
  F( A4,DPA_U_BO_HASHED) \
  F( A4,DPA_U_BO_REFCOUNTED) \
  F( A4,DPA_U_BO_REFCOUNTED_HASHED)
#define case_dpa_u_bo_hashed_t dpa_u_bo_hashed_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_hashed_m_type(F) \
  F(  5,DPA_U_BO_HASHED)
#define case_dpa_u_any_bo_hashed_t dpa_u_any_bo_hashed_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_hashed_m_type(F) \
  F( A5,DPA_U_BO_HASHED)
#define case_dpa_u_bo_hashed_ro_t dpa_u_bo_hashed_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_hashed_ro_m_type(F) \
  F(  6,DPA_U_BO_HASHED)
#define case_dpa_u_any_bo_hashed_ro_t dpa_u_any_bo_hashed_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_hashed_ro_m_type(F) \
  F( A6,DPA_U_BO_UNIQUE_HASHMAP) \
  F( A6,DPA_U_BO_HASHED)
#define case_dpa_u_bo_refcounted_t dpa_u_bo_refcounted_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_refcounted_m_type(F) \
  F(  7,DPA_U_BO_REFCOUNTED)
#define case_dpa_u_any_bo_refcounted_t dpa_u_any_bo_refcounted_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_refcounted_m_type(F) \
  F( A7,DPA_U_BO_REFCOUNTED)
#define case_dpa_u_bo_refcounted_ro_t dpa_u_bo_refcounted_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_refcounted_ro_m_type(F) \
  F(  8,DPA_U_BO_REFCOUNTED)
#define case_dpa_u_any_bo_refcounted_ro_t dpa_u_any_bo_refcounted_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_refcounted_ro_m_type(F) \
  F( A8,DPA_U_BO_REFCOUNTED) \
  F( A8,DPA_U_BO_REFCOUNTED_HASHED)
#define case_dpa_u_bo_refcounted_hashed_ro_t dpa_u_bo_refcounted_hashed_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_refcounted_hashed_ro_m_type(F) \
  F(  9,DPA_U_BO_REFCOUNTED_HASHED)
#define case_dpa_u_any_bo_refcounted_hashed_ro_t dpa_u_any_bo_refcounted_hashed_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_refcounted_hashed_ro_m_type(F) \
  F( A9,DPA_U_BO_REFCOUNTED_HASHED)
#define case_dpa_u_bo_ro_t dpa_u_bo_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_ro_m_type(F) \
  F( 10,DPA_U_BO_INLINE) \
  F( 10,DPA_U_BO_UNIQUE_HASHMAP) \
  F( 10,DPA_U_BO_SIMPLE)
#define case_dpa_u_any_bo_ro_t dpa_u_any_bo_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_ro_m_type(F) \
  F(A10,DPA_U_BO_INLINE) \
  F(A10,DPA_U_BO_UNIQUE_HASHMAP) \
  F(A10,DPA_U_BO_SIMPLE) \
  F(A10,DPA_U_BO_HASHED) \
  F(A10,DPA_U_BO_REFCOUNTED) \
  F(A10,DPA_U_BO_REFCOUNTED_HASHED)
#define case_dpa_u_bo_t dpa_u_bo_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_m_type(F) \
  F( 11,DPA_U_BO_INLINE) \
  F( 11,DPA_U_BO_SIMPLE)
#define case_dpa_u_any_bo_t dpa_u_any_bo_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_m_type(F) \
  F(A11,DPA_U_BO_INLINE) \
  F(A11,DPA_U_BO_SIMPLE) \
  F(A11,DPA_U_BO_HASHED) \
  F(A11,DPA_U_BO_REFCOUNTED)
#define case_dpa_u_bo_unique_t dpa_u_bo_unique_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_unique_m_type(F) \
  F( 12,DPA_U_BO_INLINE) \
  F( 12,DPA_U_BO_UNIQUE_HASHMAP)
#define case_dpa_u_any_bo_unique_t dpa_u_any_bo_unique_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_any_bo_unique_m_type(F) \
  F(A12,DPA_U_BO_INLINE) \
  F(A12,DPA_U_BO_UNIQUE_HASHMAP)
#define case_dpa_u_bo_with_hash_t dpa_u_bo_with_hash_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_with_hash_m_type(F) \
  F(W20,DPA_U_BO_INLINE) \
  F(W20,DPA_U_BO_HASHED)
#define case_dpa_u_bo_with_hash_ro_t dpa_u_bo_with_hash_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_with_hash_ro_m_type(F) \
  F(W21,DPA_U_BO_INLINE) \
  F(W21,DPA_U_BO_UNIQUE_HASHMAP) \
  F(W21,DPA_U_BO_HASHED) \
  F(W21,DPA_U_BO_REFCOUNTED_HASHED)
#define case_dpa_u_bo_with_refcount_t dpa_u_bo_with_refcount_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_with_refcount_m_type(F) \
  F(W22,DPA_U_BO_REFCOUNTED)
#define case_dpa_u_bo_with_refcount_ro_t dpa_u_bo_with_refcount_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_with_refcount_ro_m_type(F) \
  F(W23,DPA_U_BO_UNIQUE_HASHMAP) \
  F(W23,DPA_U_BO_REFCOUNTED) \
  F(W23,DPA_U_BO_REFCOUNTED_HASHED)
#define case_dpa_u_bo_with_refcount_and_hash_ro_t dpa_u_bo_with_refcount_and_hash_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_with_refcount_and_hash_ro_m_type(F) \
  F(W24,DPA_U_BO_UNIQUE_HASHMAP) \
  F(W24,DPA_U_BO_REFCOUNTED_HASHED)
#define case_dpa_u_bo_gc_ro_t dpa_u_bo_gc_ro_m_type(DPA__U_BO_TYPE_CASES)
#define dpa_u_bo_gc_ro_m_type(F) \
  F(W25,DPA_U_BO_INLINE) \
  F(W25,DPA_U_BO_UNIQUE_HASHMAP) \
  F(W25,DPA_U_BO_REFCOUNTED) \
  F(W25,DPA_U_BO_REFCOUNTED_HASHED)

#define DPA__U_TYPE_ENUMS_SUB(S, C) C ## _ ## S = C,
#define DPA__U_TYPE_ENUMS(T) enum T ## _type { T ## _m_type(DPA__U_TYPE_ENUMS_SUB) };

/**
 * Many compilers have this really nice feature that they can warn you about enums without a case in a switch.
 * Not all types are compatible, so not all of them will need a case. These enums correspond to types with just
 * the possible type constants. The values are the same as in the enum dpa_u_bo_any_type.
 * @{
 */
DPA_U_BO_TYPES(DPA__U_TYPE_ENUMS)
// @}
#undef DPA__U_TYPE_ENUMS_SUB
#undef DPA__U_TYPE_ENUMS

#define DPA__U_TYPE_MASKS_SUB(S, C) |(1u<<(C))
#define DPA__U_TYPE_MASKS(T) dpa_u_mask_ ## T = (0 T ## _m_type(DPA__U_TYPE_MASKS_SUB)),
/**
 * Since some types could contain various variants of other types, or point to derived types, here are some masks
 * of the dynamic types each of these static types can contain.
 * @{
 */
enum { DPA_U_BO_TYPES(DPA__U_TYPE_MASKS) };
// @}
#undef DPA__U_TYPE_MASKS_SUB
#undef DPA__U_TYPE_MASKS


// We erase the type information from these enums, because we do not want it to warn if they are assigned to one of the specialized enums above.
#define DPA_U_BO_INLINE ((int)DPA_U_BO_INLINE)
#define DPA_U_BO_SIMPLE ((int)DPA_U_BO_SIMPLE)
#define DPA_U_BO_UNIQUE_HASHMAP ((int)DPA_U_BO_UNIQUE_HASHMAP)
#define DPA_U_BO_HASHED ((int)DPA_U_BO_HASHED)
#define DPA_U_BO_REFCOUNTED ((int)DPA_U_BO_REFCOUNTED)
#define DPA_U_BO_REFCOUNTED_HASHED ((int)DPA_U_BO_REFCOUNTED_HASHED)
