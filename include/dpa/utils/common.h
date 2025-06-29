#ifndef DPA_UTILS_COMMON_H
#define DPA_UTILS_COMMON_H

#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <stdnoreturn.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdalign.h>
#include <stdbool.h>

/**
 * \addtogroup dpa-u-utils Utils
 * @{
 */

#ifdef DPA_U_CONFIG
#include DPA_U_CONFIG
#endif

#ifdef DPA_U_NO_THREADS
#warning "DANGER: C atomic or threads support missing, library will not be threadsafe!"
#endif

///////////////////////////////////////
//////        Compat Code        //////
///////////////////////////////////////
#if __STDC_VERSION__ < 202311
#if defined(__has_attribute)
#define DPA__U__has_c_attribute_opt(ext,c23) __has_attribute(ext)
#define DPA__U__has_c_attribute(ext,c23) __has_attribute(ext)
#elif defined(__has_c_attribute)
#define DPA__U__has_c_attribute_opt(ext,c23)  __has_c_attribute(ext)
#define DPA__U__has_c_attribute(ext,c23) __has_c_attribute(ext)
#else
#define DPA__U__has_c_attribute_opt 0
#define DPA__U__has_c_attribute 1
#endif
#else
#define DPA__U__has_c_attribute_opt(ext,c23)  __has_c_attribute(c23)
#define DPA__U__has_c_attribute(ext,c23) __has_c_attribute(c23)
#endif

#if __STDC_VERSION__ < 202311
#define dpa_u_attribute(ext,c23) __attribute__((ext))
#else
#define dpa_u_attribute(ext,c23) [[c23]]
#endif

#if DPA__U__has_c_attribute_opt(gcc_struct,gnu::gcc_struct)
#define dpa__u_gcc_struct dpa_u_attribute(gcc_struct,gnu::gcc_struct)
#endif
#if DPA__U__has_c_attribute_opt(packed,gnu::packed)
#define dpa__u_packed dpa_u_attribute(packed,gnu::packed) dpa__u_gcc_struct
#endif
#if DPA__U__has_c_attribute_opt(visibility,gnu::visibility)
#define dpa_u_export dpa_u_attribute(visibility("default"),gnu::visibility("default"))
#endif
#if DPA__U__has_c_attribute_opt(constructor,gnu::constructor)
#define dpa_u_init dpa_u_attribute(constructor,gnu::constructor)
#endif

#ifdef _MSC_VER
#define dpa_u_export __declspec(dllexport)
#define dpa_u_import __declspec(dllimport)
#endif

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

#define DPA_U_STR(X) #X
#define DPA_U_STR_EVAL(X) DPA_U_STR(X)

#ifndef dpa__u_gcc_struct
#define dpa__u_gcc_struct
#endif
#ifndef dpa_u_export
#define dpa_u_export
#endif
#ifndef dpa_u_import
#define dpa_u_import
#endif
#ifndef dpa__u_packed
#define dpa__u_packed dpa__u_gcc_struct
#endif
#ifndef dpa_u_init
#define dpa_u_init
#warning "WARNING: No attribute for initializer functions available. Some things may not work correctly!"
#endif

#ifdef DPA__U_BUILD_LIB
#define dpa__u_api dpa_u_export
#define dpa__u_api_var dpa_u_export
#else
#define dpa__u_api dpa_u_import
#define dpa__u_api_var dpa_u_import
#endif

#if defined(__llvm__) || defined(_MSC_VER)
#define DPA__U_STATIC_ASSERT_IN_STRUCT_BUGGY
#endif

#ifndef DPA__U_STATIC_ASSERT_IN_STRUCT_BUGGY
#define dpa_u_static_assert_as_expr(EXPR, ...) (void)(struct{ int x; _Static_assert((EXPR), __VA_ARGS__); }){0}
#else
#define dpa_u_static_assert_as_expr(EXPR, ...) (void)(char*[(!!(EXPR))*2-1]){(__VA_ARGS__)}
#endif

#define dpa_u_invalid_selection (dpa_u_invalid_selection_t){0}

typedef struct { int x; } dpa_u_invalid_selection_t;
#define dpa_u_generic(X, ...) _Generic((X), default: dpa_u_invalid_selection, __VA_ARGS__)
#define dpa_u_assert_selection(X) _Generic(0, \
    dpa_u_invalid_selection_t: dpa_u_static_assert_as_expr(_Generic((X), dpa_u_invalid_selection_t: 0, default: 1 ), "Unsupported type combination"), \
    default: (X) \
  )
#define dpa_u_generic_if_selection(X, Y) _Generic((X), dpa_u_invalid_selection_t: dpa_u_invalid_selection, default: (Y))

#if __STDC_VERSION__ >= 202311 || defined(typeof) || defined(HAVE_TYPEOF)
#define dpa_u_typeof typeof
#elif defined(__GNUC__) || defined(__llvm__) || defined(__typeof__) || defined(HAVE___TYPEOF__)
#define dpa_u_typeof __typeof__
#endif

#ifdef dpa_u_typeof
#define dpa_u_container_of(ptr, type, member) \
  ((type*)((char*)((dpa_u_typeof(((type*)0)->member)*){(ptr)}) - offsetof(type, member)))
#else
#define dpa_u_container_of(ptr, type, member) \
  ((type*)((char*)(ptr) - offsetof(type, member)))
#endif
#define dpa_u_container_of_0(ptr, type, member) \
  ((ptr)?dpa_u_container_of(ptr, type, member):0)

#ifdef __has_builtin
#define DPA__U__has_builtin(X) __has_builtin(X)
#else
#define DPA__U__has_builtin(X) 0
#endif

#ifdef __has_include
#define DPA__U__has_include(...) __has_include(__VA_ARGS__)
#else
#define DPA__U__has_include(...) 1 /* Let's be optimistic! */
#endif

#if DPA__U__has_builtin(__builtin_expect)
#define dpa_u_likely(X)   __builtin_expect(!!(X), 1)
#define dpa_u_unlikely(X) __builtin_expect(!!(X), 0)
#else
#define dpa_u_likely(X)   (X)
#define dpa_u_unlikely(X) (X)
#endif

#if DPA__U__has_c_attribute_opt(unsequenced,unsequenced)
#define dpa__u_unsequenced_1 dpa_u_attribute(unsequenced,unsequenced)
#else
#define dpa__u_unsequenced_1
#endif
#if DPA__U__has_c_attribute_opt(const,gnu::const)
#define dpa__u_unsequenced_2 dpa_u_attribute(const,gnu::const)
#else
#define dpa__u_unsequenced_2
#endif
#define dpa_u_unsequenced dpa__u_unsequenced_1 dpa__u_unsequenced_2

#if DPA__U__has_c_attribute_opt(reproducible,reproducible)
#define dpa__u_reproducible_1 dpa_u_attribute(reproducible,reproducible)
#else
#define dpa__u_reproducible_1
#endif
#if DPA__U__has_c_attribute_opt(pure,gnu::pure)
#define dpa__u_reproducible_2 dpa_u_attribute(pure,gnu::pure)
#else
#define dpa__u_reproducible_2
#endif
#define dpa_u_reproducible dpa__u_reproducible_1 dpa__u_reproducible_2

#if DPA__U__has_c_attribute_opt(weak,gnu::weak)
#define dpa_u_weak dpa_u_attribute(weak,gnu::weak)
#else
#define dpa_u_weak
#endif

#if DPA__U__has_c_attribute_opt(format,gnu::format)
#define dpa_u_format_param(...) dpa_u_attribute(format(__VA_ARGS__),gnu::format(__VA_ARGS__))
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

dpa__u_api dpa_u_format_param(printf, 3, 4) inline char* dpa__u_compound_printf(size_t s, char c[], const char* format, ...){
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

#define DPA__U_ENUM_STR_3(X, ...) [X] = #X,
#define DPA__U_ENUM_STR_2(X) DPA__U_ENUM_STR_3 X
#define DPA__U_ENUM_STR(...) DPA__U_ENUM_STR_2((DPA_U_FIRST __VA_ARGS__,1))
#define DPA_U_ENUM_STR(ENUM) ENUM(DPA__U_ENUM_STR)

// A simple comma expression would be nicer here, but then the compiler will be clever enough to warn about the unseless expressions.
#define DPA__U_ENUM_COUNT_3(X, ...) &0)+(X
#define DPA__U_ENUM_COUNT_2(X) DPA__U_ENUM_COUNT_3 X
#define DPA__U_ENUM_COUNT(...) DPA__U_ENUM_COUNT_2((DPA_U_FIRST __VA_ARGS__,1))
#define DPA_U_ENUM_COUNT(ENUM) (((-1 ENUM(DPA__U_ENUM_COUNT)))+1)

#define DPA_U_ENUM(ENUM) \
  enum ENUM { DPA_U_ENUM_CONST(ENUM ## _list) }; \
  enum { ENUM ## _count = DPA_U_ENUM_COUNT(ENUM ## _list) }; \
  dpa__u_api_var extern const char*const ENUM ## _s[];

#define DPA_U_ENUM_DEF(ENUM) \
  dpa__u_api const char*const ENUM ## _s[] = { DPA_U_ENUM_STR(ENUM ## _list) };

#define dpa_u_enum_get_name(ENUM,X) \
  ( (X) < (int)ENUM ## _count && ENUM ## _s[(X)] \
     ? ENUM ## _s[(X)] \
     : dpa_u_compound_printf(DPA_U_INT_MAX_B10_DIGITS+sizeof("<invalid %d>"), "<invalid %d>", (int)(X)) \
  )

//

dpa__u_api dpa_u_format_param(printf, 1, 2) extern noreturn void dpa_u_abort_p(const char* format, ...);
#define dpa_u_abort(F, ...) { dpa_u_abort_p("%s:%d: %s: " F "\n",  __FILE__, __LINE__, __func__, __VA_ARGS__); }

#if DPA__U__has_c_attribute_opt(always_inline,gnu::always_inline)
#define dpa__u_really_inline dpa_u_attribute(always_inline,gnu::always_inline)
#else
#define dpa__u_really_inline
#endif

// The if(0) below isn't a mistake. Forming the error messages isn't cheap, so we don't do it, but we still want to
// check that it'd be valid so the debug builds won't unexpectedly break.
#if defined(DPA_U_DEBUG)
#define dpa_u_unreachable(...) dpa_u_abort(__VA_ARGS__)
#elif DPA__U__has_builtin(__builtin_unreachable)
#define dpa_u_unreachable(...) { __builtin_unreachable(); if(0){ dpa_u_abort(__VA_ARGS__); } }
#elif DPA__U__has_builtin(__builtin_trap)
#define dpa_u_unreachable(...) { __builtin_trap(); if(0){ dpa_u_abort(__VA_ARGS__); } }
#else
#define dpa_u_unreachable(...) { abort(); if(0){ dpa_u_abort(__VA_ARGS__); } }
#endif

dpa_u_unsequenced dpa__u_really_inline dpa__u_api inline int dpa_u_ptr_compare(const void*const a, const void*const b){
  return (uintptr_t)a < (uintptr_t)b ? -1 : (uintptr_t)b < (uintptr_t)a ? 1 : 0;
}

#define dpa_u_rescope(T,V) (struct{T v;}){(V)}.v

// TODO: This is currently not a very safe macro
#define DPA_U_MIN(X,Y) ((X)<(Y)?(X):(Y))
#define DPA_U_MAX(X,Y) ((X)>(Y)?(X):(Y))

/////////////////////////////////
//////      Constants      //////
/////////////////////////////////

#define DPA_U_B36 "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ///< Digits for base36 numbers. Also suitable for bases < 36.
#define DPA_U_B64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=" ///< Digits for base64 encoded content

/////////////////////////////////////////////
//////      Interopability macros      //////
/////////////////////////////////////////////

#ifdef BITINT_MAXWIDTH
#define DPA__U_BITINT_MAXWIDTH BITINT_MAXWIDTH
#else
#define DPA__U_BITINT_MAXWIDTH 0
#endif

#ifdef INT128_MAX
#define DPA_HAS_INT128
typedef int128_t dpa_int128_t;
#define DPA_HAS_UINT128
typedef uint128_t dpa_uint128_t;
#elif UINTMAX_MAX / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) \
                  / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) == UINTMAX_C(0xFFFF)
#define DPA_HAS_INT128
typedef intmax_t dpa_int128_t;
#define DPA_HAS_UINT128
typedef uintmax_t dpa_uint128_t;
#elif DPA__U_BITINT_MAXWIDTH >= 128
#define DPA_HAS_INT128
typedef _BitInt(128) dpa_int128_t;
#define DPA_HAS_UINT128
typedef unsigned _BitInt(128) dpa_uint128_t;
#elif defined(__SIZEOF_INT128__)
#define DPA_HAS_INT128
typedef __int128_t dpa_int128_t;
#define DPA_HAS_UINT128
typedef __uint128_t dpa_uint128_t;
#endif

#ifdef INT256_MAX
#define DPA_HAS_INT256
typedef int256_t dpa_int256_t;
#define DPA_HAS_UINT256
typedef uint256_t dpa_uint256_t;
#elif UINTMAX_MAX / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) \
                  / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) \
                  / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) \
                  / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) / UINTMAX_C(0x10000) == UINTMAX_C(0xFFFF)
#define DPA_HAS_INT256
typedef intmax_t dpa_int256_t;
#define DPA_HAS_UINT256
typedef uintmax_t dpa_uint256_t;
#elif DPA__U_BITINT_MAXWIDTH >= 256
#define DPA_HAS_INT256
typedef _BitInt(256) dpa_int256_t;
#define DPA_HAS_UINT256
typedef unsigned _BitInt(256) dpa_uint256_t;
#elif defined(__SIZEOF_INT256__)
#define DPA_HAS_INT256
typedef __int256_t dpa_int256_t;
#define DPA_HAS_UINT256
typedef __uint256_t dpa_uint256_t;
#endif

#ifdef UINT8_MAX
#define DPA_U_IF_HAS_UINT8(...) __VA_ARGS__
#else
#define DPA_U_IF_HAS_UINT8(...)
#endif
#ifdef UINT16_MAX
#define DPA_U_IF_HAS_UINT16(...) __VA_ARGS__
#else
#define DPA_U_IF_HAS_UINT16(...)
#endif
#ifdef UINT24_MAX
#define DPA_U_IF_HAS_UINT24(...) __VA_ARGS__
#else
#define DPA_U_IF_HAS_UINT24(...)
#endif
#ifdef UINT32_MAX
#define DPA_U_IF_HAS_UINT32(...) __VA_ARGS__
#else
#define DPA_U_IF_HAS_UINT32(...)
#endif
#ifdef UINT64_MAX
#define DPA_U_IF_HAS_UINT64(...) __VA_ARGS__
#else
#define DPA_U_IF_HAS_UINT64(...)
#endif
#ifdef DPA_HAS_UINT128
#define DPA_U_IF_HAS_DPA_UINT128(...) __VA_ARGS__
#else
#define DPA_U_IF_HAS_DPA_UINT128(...)
#endif
#ifdef DPA_HAS_UINT256
#define DPA_U_IF_HAS_DPA_UINT256(...) __VA_ARGS__
#else
#define DPA_U_IF_HAS_DPA_UINT256(...)
#endif

#if defined(DPA_HAS_INT256)
#define DPA_U_GIANT_INT_WIDTH 256
#define DPA_U_GIANT_UNSIGNED_INT_WIDTH 256
typedef dpa_int256_t dpa_u_giant_int_t;
typedef dpa_uint256_t dpa_u_giant_unsigned_int_t;
#elif defined(DPA_HAS_INT128)
#define DPA_U_GIANT_INT_WIDTH 128
#define DPA_U_GIANT_UNSIGNED_INT_WIDTH 128
typedef dpa_int128_t dpa_u_giant_int_t;
typedef dpa_uint128_t dpa_u_giant_unsigned_int_t;
#else
typedef long long dpa_u_giant_int_t;
typedef unsigned long long dpa_u_giant_unsigned_int_t;
#endif

// This makes it easy to change the type used in bitmaps.
typedef unsigned dpa_u_bitmap_entry_t;

#ifdef __clang__
#define DPA__U_ISS_MULTITARGET
#elif defined(__GNUC__)
#define DPA__U_ISS_IFUNC
#else
#define DPA__U_ISS_NONE
#endif

#include <dpa/utils/_bo/bo-type-1.h>

typedef struct dpa_u_any_value {
  union {
    uintptr_t uptr;
    uint64_t u64;
    void* ptr;
    dpa_u_a_bo_unique_t ubo;
    dpa_u_a_bo_any_t abo;
    dpa_u_a_bo_gc_t gbo;
    dpa_u_a_bo_refcounted_t rbo;
    dpa_u_a_bo_hashed_t hbo;
  };
} dpa_u_any_value_t;

typedef struct dpa_u_optional {
  dpa_u_any_value_t value;
  bool present;
} dpa_u_optional_t;

typedef struct dpa_u_optional_pointer {
  void* value;
  bool present;
} dpa_u_optional_pointer_t;

dpa__u_api_var extern alignas(256) char dpa_u_seed[256];

/** @} */

#endif
