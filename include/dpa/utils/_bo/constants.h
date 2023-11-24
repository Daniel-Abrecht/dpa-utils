
#include <stddef.h>
#include <stdalign.h>
#include <limits.h>

enum { DPA__U_BO_COMMON_SIZE = sizeof(size_t) + sizeof(void*) };
enum { DPA_U_BO_INLINE_MAX_SIZE = DPA__U_BO_COMMON_SIZE-1 };
#define DPA_U_BO_MAX_SIZE (((size_t)1)<<((sizeof(size_t)-1)*CHAR_BIT))
#define DPA__U_BO_ALIGNMENT alignof(struct{size_t a; void* b;})

static_assert(DPA_U_BO_INLINE_MAX_SIZE <= (1<<4)-1, "It's too big to fit into a dpa_u_bo_inline_t. Please file a bug, and which platform has such huge pointers?");
