#ifndef DPA_UTILS_COMMON_H
#define DPA_UTILS_COMMON_H

/* Internal macros */

/**
 * Generic will check the semantics even for non-matching types.
 * This macro can be used to work around that, by always returning
 * an object of the expected type.
 */
#define DPA__G(T, V) _Generic((V), T: (V), default: (T){0})
#define DPA__GS(T, V) T: DPA__G(T, (V))

#define DPA_U_CONCAT(A,B) A ## B
#define DPA_U_CONCAT_E(A,B) DPA_U_CONCAT(A, B)

#define DPA_U_UNPACK(...) __VA_ARGS__

#define DPA_U_EXPORT __attribute__((visibility("default")))

#endif
