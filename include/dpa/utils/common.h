#ifndef DPA_UTILS_COMMON_H
#define DPA_UTILS_COMMON_H

#include <limits.h>
#include <stdint.h>

///////////////////////////////////////
//////      Internal macros      //////
///////////////////////////////////////

/**
 * Generic will check the semantics even for non-matching types.
 * This macro can be used to work around that, by always returning
 * an object of the expected type.
 */
#define DPA__G(T, V) _Generic((V), T: (V), default: (T){0})
#define DPA__GS(T, V) T: DPA__G(T, (V))

/////////////////////////////////////
//////      Useful macros      //////
/////////////////////////////////////

#define DPA_U_CONCAT(A,B) A ## B
#define DPA_U_CONCAT_E(A,B) DPA_U_CONCAT(A, B)

#define DPA_U_UNPACK(...) __VA_ARGS__

#define DPA_U_EXPORT __attribute__((visibility("default")))

#ifdef __llvm__
#define STATIC_ASSERT_IN_STRUCT_BUGGY
#endif

#ifndef STATIC_ASSERT_IN_STRUCT_BUGGY
#define static_assert_as_expr(EXPR, ...) (void)(struct{ int x; _Static_assert((EXPR), __VA_ARGS__); }){0}
#else
#define static_assert_as_expr(EXPR, ...) (void)(char*[(!!(EXPR))*2-1]){(__VA_ARGS__)}
#endif

typedef struct { int x; } invalid_selection_t;
#define dpa_u_generic(X, ...) _Generic((X), default: (invalid_selection_t){0}, __VA_ARGS__)
#define dpa_u_assert_selection(X) _Generic(0, \
    invalid_selection_t: static_assert_as_expr(_Generic((X), invalid_selection_t: 0, default: 1 ), "Unsupported type combination"), \
    default: (X) \
  )
#define dpa_u_generic_if_selection(X, Y) _Generic((X), invalid_selection_t: (invalid_selection_t){0}, default: (Y))

#if __STDC_VERSION__ >= 202311
#define dpa_u_typeof typeof
#else
#define dpa_u_typeof __typeof__
#endif

#define dpa_u_container_of(ptr, type, member) \
  ((type*)( (ptr) ? (char*)((dpa_u_typeof(((type*)0)->member)*){ptr}) - offsetof(type, member) : 0 ))

/////////////////////////////////
//////      Constants      //////
/////////////////////////////////

#define DPA_U__B36 "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ///< Digits for base36 numbers. Also suitable for bases < 36.
#define DPA_U__B64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=" ///< Digits for base64 encoded content

/////////////////////////////////////////////
//////      Interopability macros      //////
/////////////////////////////////////////////

#ifdef INT128_MAX
#define DPA_HAS_INT128
typedef int128_t dpa_int128_t;
#define DPA_HAS_UINT128
typedef uint128_t dpa_uint128_t;
#elif UINTMAX_MAX / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) == UINTMAX_C(0xFFFF)
#define DPA_HAS_INT128
typedef intmax_t dpa_int128_t;
#define DPA_HAS_UINT128
typedef uintmax_t dpa_uint128_t;
#elif BITINT_MAXWIDTH >= 128
#define DPA_HAS_INT128
typedef __BitInt(128) dpa_int128_t;
#define DPA_HAS_UINT128
typedef unsigned __BitInt(128) dpa_uint128_t;
#elif defined(__SIZEOF_INT128__)
#define DPA_HAS_INT128
typedef __int128_t dpa_int128_t;
#define DPA_HAS_UINT128
typedef __uint128_t dpa_uint128_t;
#endif

#ifdef __clang__
#define DPA__U_ISS_MULTITARGET
#elif defined(__GNUC__)
#define DPA__U_ISS_IFUNC
#else
#define DPA__U_ISS_NONE
#endif

#endif
