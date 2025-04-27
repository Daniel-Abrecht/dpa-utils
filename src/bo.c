#include <dpa/utils/bo.h>
#include <dpa/utils/mem.h>
#include <dpa/utils/map.h>
#include <dpa/utils/threads.h>
#include <dpa/utils/refcount.h>
#include <errno.h>

static const char*const dpa_u_bo_type[32] = {
  [0] = "ERROR|inline",
  [(DPA_U_BO_SIMPLE)>>3] = "simple",
  [(DPA_U_BO_HASHED)>>3] = "INVALID<inline|hashed>",
  [(DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)>>3] = "hashed|simple",
  [(DPA_U_BO_REFCOUNTED)>>3] = "INVALID<inline|refcounted>",
  [(DPA_U_BO_REFCOUNTED|DPA_U_BO_SIMPLE)>>3] = "refcounted|simple",
  [(DPA_U_BO_REFCOUNTED|DPA_U_BO_HASHED)>>3] = "INVALID<inline|refcounted|hashed>",
  [(DPA_U_BO_REFCOUNTED|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)>>3] = "refcounted|hashed|simple",
  [(DPA_U_BO_UNIQUE)>>3] = "inline|unique",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_SIMPLE)>>3] = "INVALID<unique|simple>",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_HASHED)>>3] = "INVALID<inline|unique|hashed>",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)>>3] = "INVALID<unique|hashed|simple>",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_REFCOUNTED)>>3] = "INVALID<inline|unique|refcounted>",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_REFCOUNTED|DPA_U_BO_SIMPLE)>>3] = "unique|refcounted|simple",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_REFCOUNTED|DPA_U_BO_HASHED)>>3] = "INVALID<inline|unique|refcounted|hashed>",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_REFCOUNTED|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE)>>3] = "unique|refcounted|hashed|simple",
  [(DPA_U_BO_STATIC)>>3] = "INVALID<inline|static>",
  [(DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)>>3] = "simple|static",
  [(DPA_U_BO_HASHED|DPA_U_BO_STATIC)>>3] = "INVALID<inline|hashed|static>",
  [(DPA_U_BO_HASHED|DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)>>3] = "hashed|simple|static",
  [(DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)>>3] = "INVALID<inline|refcounted|static>",
  [(DPA_U_BO_REFCOUNTED|DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)>>3] = "refcounted|simple|static",
  [(DPA_U_BO_REFCOUNTED|DPA_U_BO_HASHED|DPA_U_BO_STATIC)>>3] = "INVALID<inline|refcounted|hashed|static>",
  [(DPA_U_BO_REFCOUNTED|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)>>3] = "refcounted|hashed|simple|static",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_STATIC)>>3] = "INVALID<inline|unique|static>",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)>>3] = "unique|simple|static",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_HASHED|DPA_U_BO_STATIC)>>3] = "INVALID<inline|unique|hashed|static>",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)>>3] = "unique|hashed|simple|static",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)>>3] = "INVALID<inline|unique|refcounted|static>",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_REFCOUNTED|DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)>>3] = "unique|refcounted|simple|static",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_REFCOUNTED|DPA_U_BO_HASHED|DPA_U_BO_STATIC)>>3] = "INVALID<inline|unique|refcounted|hashed|static>",
  [(DPA_U_BO_UNIQUE|DPA_U_BO_REFCOUNTED|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE|DPA_U_BO_STATIC)>>3] = "unique|refcounted|hashed|simple|static",
};

static const dpa_u_a_bo_unique_t bo_error[] = {
  [0] = {{{DPA__U_INLINE_STRING('E','R','R','O','R',' ','0')}}},
  [E2BIG] = {{{DPA__U_INLINE_STRING('E','2','B','I','G')}}},
  [EACCES] = {{{DPA__U_INLINE_STRING('E','A','C','C','E','S')}}},
  [EADDRINUSE] = {{{DPA__U_INLINE_STRING('E','A','D','D','R','I','N')}}},
  [EADDRNOTAVAIL] = {{{DPA__U_INLINE_STRING('E','A','D','D','R','N','O')}}},
  [EADV] = {{{DPA__U_INLINE_STRING('E','A','D','V')}}},
  [EAFNOSUPPORT] = {{{DPA__U_INLINE_STRING('E','A','F','N','O','S','U')}}},
  [EAGAIN] = {{{DPA__U_INLINE_STRING('E','A','G','A','I','N')}}},
  [EALREADY] = {{{DPA__U_INLINE_STRING('E','A','L','R','E','A','D')}}},
  [EBADE] = {{{DPA__U_INLINE_STRING('E','B','A','D','E')}}},
  [EBADF] = {{{DPA__U_INLINE_STRING('E','B','A','D','F')}}},
  [EBADFD] = {{{DPA__U_INLINE_STRING('E','B','A','D','F','D')}}},
  [EBADMSG] = {{{DPA__U_INLINE_STRING('E','B','A','D','M','S','G')}}},
  [EBADR] = {{{DPA__U_INLINE_STRING('E','B','A','D','R')}}},
  [EBADRQC] = {{{DPA__U_INLINE_STRING('E','B','A','D','R','Q','C')}}},
  [EBADSLT] = {{{DPA__U_INLINE_STRING('E','B','A','D','S','L','T')}}},
  [EBFONT] = {{{DPA__U_INLINE_STRING('E','B','F','O','N','T')}}},
  [EBUSY] = {{{DPA__U_INLINE_STRING('E','B','U','S','Y')}}},
  [ECANCELED] = {{{DPA__U_INLINE_STRING('E','C','A','N','C','E','L')}}},
  [ECHILD] = {{{DPA__U_INLINE_STRING('E','C','H','I','L','D')}}},
  [ECHRNG] = {{{DPA__U_INLINE_STRING('E','C','H','R','N','G')}}},
  [ECOMM] = {{{DPA__U_INLINE_STRING('E','C','O','M','M')}}},
  [ECONNABORTED] = {{{DPA__U_INLINE_STRING('E','C','O','N','N','A','B')}}},
  [ECONNREFUSED] = {{{DPA__U_INLINE_STRING('E','C','R','E','F','U','S')}}},
  [ECONNRESET] = {{{DPA__U_INLINE_STRING('E','C','R','E','S','E','T')}}},
  [EDEADLK] = {{{DPA__U_INLINE_STRING('E','D','E','A','D','L','K')}}},
#if EDEADLK != EDEADLOCK
  [EDEADLOCK] = {{{DPA__U_INLINE_STRING('E','D','E','A','D','L','O')}}},
#endif
  [EDESTADDRREQ] = {{{DPA__U_INLINE_STRING('E','D','E','S','T','A','D')}}},
  [EDOM] = {{{DPA__U_INLINE_STRING('E','D','O','M')}}},
  [EDOTDOT] = {{{DPA__U_INLINE_STRING('E','D','O','T','D','O','T')}}},
  [EDQUOT] = {{{DPA__U_INLINE_STRING('E','D','Q','U','O','T')}}},
  [EEXIST] = {{{DPA__U_INLINE_STRING('E','E','X','I','S','T')}}},
  [EFAULT] = {{{DPA__U_INLINE_STRING('E','F','A','U','L','T')}}},
  [EFBIG] = {{{DPA__U_INLINE_STRING('E','F','B','I','G')}}},
  [EHOSTDOWN] = {{{DPA__U_INLINE_STRING('E','H','O','S','T','D','O')}}},
  [EHOSTUNREACH] = {{{DPA__U_INLINE_STRING('E','H','O','S','T','U','N')}}},
  [EHWPOISON] = {{{DPA__U_INLINE_STRING('E','H','W','P','O','I','S')}}},
  [EIDRM] = {{{DPA__U_INLINE_STRING('E','I','D','R','M')}}},
  [EILSEQ] = {{{DPA__U_INLINE_STRING('E','I','L','S','E','Q')}}},
  [EINPROGRESS] = {{{DPA__U_INLINE_STRING('E','I','N','P','R','O','G')}}},
  [EINTR] = {{{DPA__U_INLINE_STRING('E','I','N','T','R')}}},
  [EINVAL] = {{{DPA__U_INLINE_STRING('E','I','N','V','A','L')}}},
  [EIO] = {{{DPA__U_INLINE_STRING('E','I','O')}}},
  [EISCONN] = {{{DPA__U_INLINE_STRING('E','I','S','C','O','N','N')}}},
  [EISDIR] = {{{DPA__U_INLINE_STRING('E','I','S','D','I','R')}}},
  [EISNAM] = {{{DPA__U_INLINE_STRING('E','I','S','N','A','M')}}},
  [EKEYEXPIRED] = {{{DPA__U_INLINE_STRING('E','K','E','Y','E','X','P')}}},
  [EKEYREJECTED] = {{{DPA__U_INLINE_STRING('E','K','E','Y','R','E','J')}}},
  [EKEYREVOKED] = {{{DPA__U_INLINE_STRING('E','K','E','Y','R','E','V')}}},
  [EL2HLT] = {{{DPA__U_INLINE_STRING('E','L','2','H','L','T')}}},
  [EL2NSYNC] = {{{DPA__U_INLINE_STRING('E','L','2','N','S','Y','N')}}},
  [EL3HLT] = {{{DPA__U_INLINE_STRING('E','L','3','H','L','T')}}},
  [EL3RST] = {{{DPA__U_INLINE_STRING('E','L','3','R','S','T')}}},
  [ELIBACC] = {{{DPA__U_INLINE_STRING('E','L','I','B','A','C','C')}}},
  [ELIBBAD] = {{{DPA__U_INLINE_STRING('E','L','I','B','B','A','D')}}},
  [ELIBEXEC] = {{{DPA__U_INLINE_STRING('E','L','I','B','E','X','E')}}},
  [ELIBMAX] = {{{DPA__U_INLINE_STRING('E','L','I','B','M','A','X')}}},
  [ELIBSCN] = {{{DPA__U_INLINE_STRING('E','L','I','B','S','C','N')}}},
  [ELNRNG] = {{{DPA__U_INLINE_STRING('E','L','N','R','N','G')}}},
  [ELOOP] = {{{DPA__U_INLINE_STRING('E','L','O','O','P')}}},
  [EMEDIUMTYPE] = {{{DPA__U_INLINE_STRING('E','M','E','D','I','U','M')}}},
  [EMFILE] = {{{DPA__U_INLINE_STRING('E','M','F','I','L','E')}}},
  [EMLINK] = {{{DPA__U_INLINE_STRING('E','M','L','I','N','K')}}},
  [EMSGSIZE] = {{{DPA__U_INLINE_STRING('E','M','S','G','S','I','Z')}}},
  [EMULTIHOP] = {{{DPA__U_INLINE_STRING('E','M','U','L','T','I','H')}}},
  [ENAMETOOLONG] = {{{DPA__U_INLINE_STRING('E','N','A','M','E','T','O')}}},
  [ENAVAIL] = {{{DPA__U_INLINE_STRING('E','N','A','V','A','I','L')}}},
  [ENETDOWN] = {{{DPA__U_INLINE_STRING('E','N','E','T','D','O','W')}}},
  [ENETRESET] = {{{DPA__U_INLINE_STRING('E','N','E','T','R','E','S')}}},
  [ENETUNREACH] = {{{DPA__U_INLINE_STRING('E','N','E','T','U','N','R')}}},
  [ENFILE] = {{{DPA__U_INLINE_STRING('E','N','F','I','L','E')}}},
  [ENOANO] = {{{DPA__U_INLINE_STRING('E','N','O','A','N','O')}}},
  [ENOBUFS] = {{{DPA__U_INLINE_STRING('E','N','O','B','U','F','S')}}},
  [ENOCSI] = {{{DPA__U_INLINE_STRING('E','N','O','C','S','I')}}},
  [ENODATA] = {{{DPA__U_INLINE_STRING('E','N','O','D','A','T','A')}}},
  [ENODEV] = {{{DPA__U_INLINE_STRING('E','N','O','D','E','V')}}},
  [ENOENT] = {{{DPA__U_INLINE_STRING('E','N','O','E','N','T')}}},
  [ENOEXEC] = {{{DPA__U_INLINE_STRING('E','N','O','E','X','E','C')}}},
  [ENOKEY] = {{{DPA__U_INLINE_STRING('E','N','O','K','E','Y')}}},
  [ENOLCK] = {{{DPA__U_INLINE_STRING('E','N','O','L','C','K')}}},
  [ENOLINK] = {{{DPA__U_INLINE_STRING('E','N','O','L','I','N','K')}}},
  [ENOMEDIUM] = {{{DPA__U_INLINE_STRING('E','N','O','M','E','D','I')}}},
  [ENOMEM] = {{{DPA__U_INLINE_STRING('E','N','O','M','E','M')}}},
  [ENOMSG] = {{{DPA__U_INLINE_STRING('E','N','O','M','S','G')}}},
  [ENONET] = {{{DPA__U_INLINE_STRING('E','N','O','N','E','T')}}},
  [ENOPKG] = {{{DPA__U_INLINE_STRING('E','N','O','P','K','G')}}},
  [ENOPROTOOPT] = {{{DPA__U_INLINE_STRING('E','N','O','P','R','O','T')}}},
  [ENOSPC] = {{{DPA__U_INLINE_STRING('E','N','O','S','P','C')}}},
  [ENOSR] = {{{DPA__U_INLINE_STRING('E','N','O','S','R')}}},
  [ENOSTR] = {{{DPA__U_INLINE_STRING('E','N','O','S','T','R')}}},
  [ENOSYS] = {{{DPA__U_INLINE_STRING('E','N','O','S','Y','S')}}},
  [ENOTBLK] = {{{DPA__U_INLINE_STRING('E','N','O','T','B','L','K')}}},
  [ENOTCONN] = {{{DPA__U_INLINE_STRING('E','N','O','T','C','O','N')}}},
  [ENOTDIR] = {{{DPA__U_INLINE_STRING('E','N','O','T','D','I','R')}}},
  [ENOTEMPTY] = {{{DPA__U_INLINE_STRING('E','N','O','T','E','M','P')}}},
  [ENOTNAM] = {{{DPA__U_INLINE_STRING('E','N','O','T','N','A','M')}}},
  [ENOTRECOVERABLE] = {{{DPA__U_INLINE_STRING('E','N','O','T','R','E','C')}}},
  [ENOTSOCK] = {{{DPA__U_INLINE_STRING('E','N','O','T','S','O','C')}}},
  [ENOTSUP] = {{{DPA__U_INLINE_STRING('E','N','O','T','S','U','P')}}},
  [ENOTTY] = {{{DPA__U_INLINE_STRING('E','N','O','T','T','Y')}}},
  [ENOTUNIQ] = {{{DPA__U_INLINE_STRING('E','N','O','T','U','N','I')}}},
  [ENXIO] = {{{DPA__U_INLINE_STRING('E','N','X','I','O')}}},
#if ENOTSUP != EOPNOTSUPP
  [EOPNOTSUPP] = {{{DPA__U_INLINE_STRING('E','O','P','N','O','T','S')}}},
#endif
  [EOVERFLOW] = {{{DPA__U_INLINE_STRING('E','O','V','E','R','F','L')}}},
  [EOWNERDEAD] = {{{DPA__U_INLINE_STRING('E','O','W','N','E','R','D')}}},
  [EPERM] = {{{DPA__U_INLINE_STRING('E','P','E','R','M')}}},
  [EPFNOSUPPORT] = {{{DPA__U_INLINE_STRING('E','P','F','N','O','S','U')}}},
  [EPIPE] = {{{DPA__U_INLINE_STRING('E','P','I','P','E')}}},
  [EPROTO] = {{{DPA__U_INLINE_STRING('E','P','R','O','T','O')}}},
  [EPROTONOSUPPORT] = {{{DPA__U_INLINE_STRING('E','P','R','O','T','O','N')}}},
  [EPROTOTYPE] = {{{DPA__U_INLINE_STRING('E','P','R','O','T','O','T')}}},
  [ERANGE] = {{{DPA__U_INLINE_STRING('E','R','A','N','G','E')}}},
  [EREMCHG] = {{{DPA__U_INLINE_STRING('E','R','E','M','C','H','G')}}},
  [EREMOTE] = {{{DPA__U_INLINE_STRING('E','R','E','M','O','T','E')}}},
  [EREMOTEIO] = {{{DPA__U_INLINE_STRING('E','R','E','M','I','O')}}},
  [ERESTART] = {{{DPA__U_INLINE_STRING('E','R','E','S','T','A','R')}}},
  [ERFKILL] = {{{DPA__U_INLINE_STRING('E','R','F','K','I','L','L')}}},
  [EROFS] = {{{DPA__U_INLINE_STRING('E','R','O','F','S')}}},
  [ESHUTDOWN] = {{{DPA__U_INLINE_STRING('E','S','H','U','T','D','O')}}},
  [ESOCKTNOSUPPORT] = {{{DPA__U_INLINE_STRING('E','S','O','C','K','T','N')}}},
  [ESPIPE] = {{{DPA__U_INLINE_STRING('E','S','P','I','P','E')}}},
  [ESRCH] = {{{DPA__U_INLINE_STRING('E','S','R','C','H')}}},
  [ESRMNT] = {{{DPA__U_INLINE_STRING('E','S','R','M','N','T')}}},
  [ESTALE] = {{{DPA__U_INLINE_STRING('E','S','T','A','L','E')}}},
  [ESTRPIPE] = {{{DPA__U_INLINE_STRING('E','S','T','R','P','I','P')}}},
  [ETIME] = {{{DPA__U_INLINE_STRING('E','T','I','M','E')}}},
  [ETIMEDOUT] = {{{DPA__U_INLINE_STRING('E','T','I','M','E','D','O')}}},
  [ETOOMANYREFS] = {{{DPA__U_INLINE_STRING('E','T','O','O','M','A','N')}}},
  [ETXTBSY] = {{{DPA__U_INLINE_STRING('E','T','X','T','B','S','Y')}}},
  [EUCLEAN] = {{{DPA__U_INLINE_STRING('E','U','C','L','E','A','N')}}},
  [EUNATCH] = {{{DPA__U_INLINE_STRING('E','U','N','A','T','C','H')}}},
  [EUSERS] = {{{DPA__U_INLINE_STRING('E','U','S','E','R','S')}}},
#if EWOULDBLOCK != EAGAIN
  [EWOULDBLOCK] = {{{DPA__U_INLINE_STRING('E','W','O','U','L','D','B')}}},
#endif
  [EXDEV] = {{{DPA__U_INLINE_STRING('E','X','D','E','V')}}},
  [EXFULL] = {{{DPA__U_INLINE_STRING('E','X','F','U','L','L')}}},
};

dpa__u_api dpa_u_a_bo_unique_t dpa_u_bo_error(int err){
  if(dpa_u_unlikely(err < 0 || err >= (int)(sizeof(bo_error)/sizeof(*bo_error)) || !bo_error[err].p.value[0])){
    if(err < 0 || err >= 1000000)
      return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING('E','R','R','O','R')}}};
    return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING('E', ((err/100000)%10)+'0', ((err/10000)%10)+'0', ((err/1000)%10)+'0', ((err/100)%10)+'0', ((err/10)%10)+'0', (err%10)+'0')}}};
  }
  return bo_error[err];
}

dpa__u_api int dpa_u_bo_error_to_errno(dpa_u_a_bo_unique_t bo){
  for(unsigned i=0; i<sizeof(bo_error)/sizeof(*bo_error); i++)
    if(!memcmp(&bo, &bo_error[i], 8))
      return i;
  return -1;
}

static dpa_u_map_u64_t unique_string_map;
static mtx_t unique_string_map_lock;

static dpa_u_init void init(void){
  mtx_init(&unique_string_map_lock, mtx_plain);
}

dpa__u_api const char* dpa_u_bo_type_to_string(enum dpa_u_bo_type_flags type){
  if(type>=0x100 || type<0)
    return "INVALID";
  return dpa_u_bo_type[type>>3];
}

dpa__u_api void dpa__u_bo_unique_destroy(const dpa_u_refcount_freeable_t* rc){
  mtx_lock(&unique_string_map_lock);
  if(!dpa_u_refcount_is_zero(rc)){
    // This only happens if the entry was picked from the set before it was removed. In that case, it was incremented.
    // That reference is taken by dpa__u_bo_intern_h on behalf of this function, under the unique_string_map_lock lock.
    // We drop it again.
    if(dpa_u_refcount_decrement(&rc->refcount))
      goto end; // This is not the last reference anymore.
  }
  const enum dpa_u_refcount_type type = dpa_u_refcount_get_type(&rc->refcount);
  const dpa_u_bo_t*const bo = (dpa_u_bo_t*)(rc+1);
  const uint64_t hash = (bo->size > 64) ? ((dpa__u_bo_hashed_t*)bo)->hash : dpa_u_bo_get_hash(*bo);
  const uint64_t truncated_hash = dpa__u_map_u64_hash_sub(hash) & ~0xFFFF;
  const struct dpa__u_sm_lookup_result result = dpa__u_map_u64_lookup_sub(&unique_string_map, truncated_hash, unique_string_map.lbsize);
  const int shift = sizeof(uint64_t)*CHAR_BIT - unique_string_map.lbsize;
  const uint64_t I = (uint64_t)1 << shift;
  uint64_t i = (uint64_t)result.index << shift;
  for(; unique_string_map.key_list[i>>shift] == i || DPA_U_UNTAG(unique_string_map.value_list[i>>shift].u64) != bo; i += I);
  i >>= shift;
  // printf("%lX %lX %lX\n", i, result.index, (i-result.index));
  dpa__u_map_u64_remove_index_sub(&unique_string_map, i);
  if(type == DPA_U_REFCOUNT_BO_UNIQUE_EXTREF)
    dpa_u_refcount_put(dpa_u_container_of((char(*)[])bo->data, struct dpa_u_refcount_freeable_data, data)->refcount);
  free((void*)rc);
end:
  mtx_unlock(&unique_string_map_lock);
}

dpa__u_api dpa_u_a_bo_unique_t dpa__u_bo_intern_h(dpa_u_a_bo_any_t bo){
  if(dpa_u_bo_is_error(bo))
    return bo_error[EINVAL];
  const int bo_type = dpa_u_bo_get_type(bo);
  if(bo_type & DPA_U_BO_UNIQUE){
    dpa_u_a_bo_unique_t res = {bo.p};
    dpa_u_bo_ref(res);
    return res;
  }
  const size_t size = dpa_u_bo_get_size(bo);
  const void* data = dpa_u_bo_get_data(bo);
  if(size <= 7){
    dpa_u_a_bo_unique_t res = {{{DPA_U_MOVE_TAG(DPA_U_BO_UNIQUE+size)}}};
    memcpy(((char*)res.p.value)+1, data, size);
    return res;
  }
  const uint64_t hash = dpa_u_bo_get_hash(bo);
  int error;

  mtx_lock(&unique_string_map_lock);

  if(dpa__u_map_u64_maybe_grow(&unique_string_map) == -1){
    fprintf(stderr, "dpa__u_bo_intern_h failed: failed to increase size of hash map of all unique strings\n");
    error = errno;
    goto error;
  }
  const int shift = sizeof(uint64_t)*CHAR_BIT - unique_string_map.lbsize;
  // After hashing the key, the resulting value will have a few of it's least significant bits set to 0
  // The u64 map is sorted by the hash value. We use this here to store up to 2**16 entries for the same hash.
  // This is a giant hack, if the map implementation ever changes, this may break.
  // However, the map implementation is part of this very same library, so this should be fine.
  const uint64_t truncated_hash = dpa__u_map_u64_hash_sub(hash) & ~0xFFFF;
  const struct dpa__u_sm_lookup_result result = dpa__u_map_u64_lookup_sub(&unique_string_map, truncated_hash, unique_string_map.lbsize);
  uint64_t next, last=truncated_hash-1, unused_i=-1, unused_e;
  if(!result.found){
    unused_i = result.index<<shift;
    unused_e = truncated_hash;
  }
  const uint64_t I = (uint64_t)1 << shift;
  uint64_t i = (uint64_t)result.index << shift;
  while(true){
    while((next=unique_string_map.key_list[i>>shift]) == i && (i&~0xFFFF) == truncated_hash)
      i += I;
    if((next&~0xFFFF) != truncated_hash){
      if((last+1)&0xFFFF){
        unused_i = i;
        unused_e = last+1;
      }
      break;
    }
    // An entry with matching hash found
    const dpa_u_a_bo_unique_t entry = dpa_u_bo_unique_from_uint(unique_string_map.value_list[i>>shift].u64);
    const dpa_u_bo_t v = dpa_u_to_bo(entry);
    if( v.size == size && ( v.data == data || !memcmp(data, v.data, size) )){
      dpa_u_refcount_freeable_t* rc = dpa_u_bo_get_refcount(entry);
      if(dpa_u_refcount_is_zero(rc)){
        // This entry was due for removal. We increment the refcount one more on behalf of the dpa__u_bo_unique_destroy
        // callback, which is going to run later. This ensures the refcount doesn't hit 0 before that happens again.
        dpa_u_refcount_ref(rc);
      }
      dpa_u_refcount_ref(rc);
      mtx_unlock(&unique_string_map_lock);
      return entry;
    }
    if(last+1 != next){
      unused_i = i;
      unused_e = last+1;
    }
    last = next;
    i += I;
  }
  if(unused_i == (uint64_t)-1){
    fprintf(stderr, "dpa__u_bo_intern_h failed: bucket full, there can only be up to 65535 entries per bucket\n");
    error = errno;
    goto error;
  }
  int entry_size = sizeof(dpa_u_bo_t);
  int type = DPA_U_BO_UNIQUE | DPA_U_BO_SIMPLE;
  if(size > 64){
    type |= DPA_U_BO_HASHED;
    entry_size = sizeof(dpa__u_bo_hashed_t);
  }
  if(bo_type & DPA_U_BO_STATIC){
    type |= DPA_U_BO_STATIC;
  }else{
    type |= DPA_U_BO_REFCOUNTED;
    entry_size += sizeof(dpa_u_refcount_t);
  }
  if(!(bo_type & (DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC)))
    entry_size += size;
  void* eh = malloc(entry_size);
  if(!(bo_type & (DPA_U_BO_REFCOUNTED|DPA_U_BO_STATIC))){
    char* d = (char*)eh + entry_size - size;
    memcpy(d, data, size);
    data = d;
  }else if(bo_type & DPA_U_BO_REFCOUNTED){
    dpa_u_bo_ref(bo); // TODO
  }
  if(type & DPA_U_BO_REFCOUNTED){
    struct dpa__u_refcount_bo_unique* rc = eh;
    rc->value = bo_type & DPA_U_BO_REFCOUNTED
              ? DPA_U_REFCOUNT_INIT(DPA_U_REFCOUNT_BO_UNIQUE_EXTREF) + 1
              : DPA_U_REFCOUNT_INIT(DPA_U_REFCOUNT_BO_UNIQUE) + 1;
    eh = rc+1;
  }
  *(dpa_u_bo_t*)eh = (dpa_u_bo_t){
    .size = size,
    .data = (char*)data,
  };
  if(type & DPA_U_BO_HASHED)
    ((dpa__u_bo_hashed_t*)eh)->hash = hash;
  dpa_u_a_bo_unique_t ret = { DPA__U_BO_TAG(eh, type) };
  dpa__u_map_u64_insert_sub(
    &unique_string_map,
    unused_e,
    (dpa_u_any_value_t){.u64=dpa_u_bo_unique_to_uint(ret)},
    unused_i >> shift,
    unique_string_map.lbsize
  );
  // printf("%016lX %016lX %016lX %lX %lX\n", truncated_hash, unused_e, unique_string_map.value_list[unused_i>>shift].u64, unique_string_map.count, unused_i >> shift);
  unique_string_map.count++;

  mtx_unlock(&unique_string_map_lock);
  return ret;
error:
  mtx_unlock(&unique_string_map_lock);
  return dpa_u_bo_error(error);
}
