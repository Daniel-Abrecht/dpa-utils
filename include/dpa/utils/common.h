#ifndef DPA_UTILS_COMMON_H
#define DPA_UTILS_COMMON_H

#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <stdnoreturn.h>
#include <stdio.h>
#include <stdarg.h>

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
#define DPA_U_FIRST_1(X, ...) X
#define DPA_U_FIRST(...) DPA_U_FIRST_1(__VA_ARGS__,1)

#define DPA_U_EXPORT __attribute__((visibility("default")))

#ifdef __llvm__
#define DPA__U_STATIC_ASSERT_IN_STRUCT_BUGGY
#endif

#ifndef DPA__U_STATIC_ASSERT_IN_STRUCT_BUGGY
#define dpa_u_static_assert_as_expr(EXPR, ...) (void)(struct{ int x; _Static_assert((EXPR), __VA_ARGS__); }){0}
#else
#define dpa_u_static_assert_as_expr(EXPR, ...) (void)(char*[(!!(EXPR))*2-1]){(__VA_ARGS__)}
#endif

typedef struct { int x; } invalid_selection_t;
#define dpa_u_generic(X, ...) _Generic((X), default: (invalid_selection_t){0}, __VA_ARGS__)
#define dpa_u_assert_selection(X) _Generic(0, \
    invalid_selection_t: dpa_u_static_assert_as_expr(_Generic((X), invalid_selection_t: 0, default: 1 ), "Unsupported type combination"), \
    default: (X) \
  )
#define dpa_u_generic_if_selection(X, Y) _Generic((X), invalid_selection_t: (invalid_selection_t){0}, default: (Y))

#if __STDC_VERSION__ >= 202311 || defined(typeof) || defined(HAVE_TYPEOF)
#define dpa_u_typeof typeof
#elif defined(__GNUC__) || defined(__llvm__) || defined(__typeof__) || defined(HAVE___TYPEOF__)
#define dpa_u_typeof __typeof__
#endif

#ifdef dpa_u_typeof
#define dpa_u_container_of(ptr, type, member) \
  ((type*)( (ptr) ? (char*)((dpa_u_typeof(((type*)0)->member)*){(ptr)}) - offsetof(type, member) : 0 ))
#else
#define dpa_u_container_of(ptr, type, member) \
  ((type*)( (ptr) ? (char*)(ptr) - offsetof(type, member) : 0 ))
#endif

#if defined(__has_builtin) && __has_builtin(__builtin_expect)
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define likely(x)
#define unlikely(x)
#endif

#if defined(__GNUC__) || defined(__llvm__)
#define dpa_u_format_param(...) __attribute__ ((format (__VA_ARGS__)))
#else
#define dpa_u_format_param(...)
#endif

enum {
  DPA_U_I8_MAX_B10_DIGITS = 5,
  DPA_U_I16_MAX_B10_DIGITS = 7,
  DPA_U_I32_MAX_B10_DIGITS = 12,
  DPA_U_I64_MAX_B10_DIGITS = 21,
  DPA_U_CHAR_MAX_B10_DIGITS = CHAR_BIT * sizeof(char) / 3 + 3,
  DPA_U_SHORT_MAX_B10_DIGITS = CHAR_BIT * sizeof(short) / 3 + 3,
  DPA_U_INT_MAX_B10_DIGITS = CHAR_BIT * sizeof(int) / 3 + 3,
  DPA_U_LONG_MAX_B10_DIGITS = CHAR_BIT * sizeof(long) / 3 + 3,
  DPA_U_LONG_LONG_MAX_B10_DIGITS = CHAR_BIT * sizeof(long long) / 3 + 3,
};

DPA_U_EXPORT dpa_u_format_param(printf, 3, 4)
  inline char* dpa__u_compound_printf(size_t s, char c[s], const char* format, ...){
    va_list args;
    va_start(args, format);
    vsnprintf(c,s, format, args);
    va_end(args);
    return c;
  }

#define dpa_u_compound_printf(S,...) dpa__u_compound_printf( (S), (char[(S)]){0}, __VA_ARGS__ )

// Helpers for enums
#define DPA__U_ENUM_CONST_3_2(X,V) X = V,
#define DPA__U_ENUM_CONST_3_1(X,V) X,
#define DPA__U_ENUM_CONST_3_0(X,V,N,...) DPA__U_ENUM_CONST_3_ ## N (X,V)
#define DPA__U_ENUM_CONST_3(X) DPA__U_ENUM_CONST_3_0 X
#define DPA__U_ENUM_CONST_2(X, ...) DPA__U_ENUM_CONST_3((DPA_U_UNPACK X,2,1,0))
#define DPA__U_ENUM_CONST(...) DPA__U_ENUM_CONST_2(__VA_ARGS__,1)
#define DPA_U_ENUM_CONST(ENUM) ENUM(DPA__U_ENUM_CONST)

#define DPA__U_ENUM_STR_2(X, ...) [X] = #X,
#define DPA__U_ENUM_STR(...) DPA__U_ENUM_STR_2(DPA_U_FIRST __VA_ARGS__,1)
#define DPA_U_ENUM_STR(ENUM) ENUM(DPA__U_ENUM_STR)

// A simple comma expression would be nicer here, but then the compiler will be clever enough to warn about the unseless expressions.
#define DPA__U_ENUM_COUNT_2(X, ...) &0)+(X
#define DPA__U_ENUM_COUNT(...) DPA__U_ENUM_COUNT_2(DPA_U_FIRST __VA_ARGS__,1)
#define DPA_U_ENUM_COUNT(ENUM) (((-1 ENUM(DPA__U_ENUM_COUNT)))+1)

#define DPA_U_ENUM(ENUM) \
  enum ENUM { DPA_U_ENUM_CONST(ENUM ## _list) }; \
  enum { ENUM ## _count = DPA_U_ENUM_COUNT(ENUM ## _list) }; \
  DPA_U_EXPORT extern const char*const ENUM ## _s[];

#define dpa_u_enum_get_name(ENUM,X) \
  ( (X) < (int)ENUM ## _count && ENUM ## _s[(X)] \
     ? ENUM ## _s[(X)] \
     : dpa_u_compound_printf(DPA_U_INT_MAX_B10_DIGITS+sizeof("<invalid %d>"), "<invalid %d>", (int)(X)) \
  )

//

DPA_U_EXPORT extern noreturn void dpa_u_abort_p(const char* format, ...) dpa_u_format_param(printf, 1, 2);
#define dpa_u_abort(F, ...) dpa_u_abort_p("%s:%d: %s: " F "\n",  __FILE__, __LINE__, __func__, __VA_ARGS__)

// TODO: This is currently not a very safe macro
#define DPA_U_MIN(X,Y) ((X)<(Y)?(X):(Y))
#define DPA_U_MAX(X,Y) ((X)>(Y)?(X):(Y))

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
