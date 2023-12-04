
#include <stddef.h>
#include <stdalign.h>
#include <limits.h>

#ifdef DPA_U_BO_NOT_PACKED
enum { DPA__U_BO_COMMON_SIZE = sizeof(struct { char m[2]; size_t s; void* d; }) };
enum { DPA_U_BO_INLINE_MAX_SIZE = DPA__U_BO_COMMON_SIZE-2 };
#else
enum { DPA__U_BO_COMMON_SIZE = sizeof(struct { size_t s; void* d; }) };
enum { DPA_U_BO_INLINE_MAX_SIZE = DPA__U_BO_COMMON_SIZE-1 };
static_assert(DPA_U_BO_INLINE_MAX_SIZE <= (1<<4)-1, "It's too big to fit into a dpa_u_bo_inline_t. Please file a bug, and which platform has such huge pointers?");
#endif
#define DPA_U_BO_MAX_SIZE (((size_t)1)<<((sizeof(size_t)-1)*CHAR_BIT))
#define DPA__U_BO_ALIGNMENT alignof(struct{size_t a; void* b;})
