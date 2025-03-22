#include <dpa/utils/bo.h>
#include <dpa/utils/mem.h>
#include <dpa/utils/map.h>
#include <dpa/utils/threads.h>
#include <dpa/utils/refcount.h>
#include <errno.h>

static const char*const dpa_u_bo_type[32] = {
  "ERROR|inline",
  "simple",
  "INVALID<inline|hashed>",
  "hashed|simple",
  "INVALID<inline|refcounted>",
  "refcounted|simple",
  "INVALID<inline|refcounted|hashed>",
  "refcounted|hashed|simple",
  "inline|unique",
  "INVALID<unique|simple>",
  "INVALID<inline|unique|hashed>",
  "INVALID<unique|hashed|simple>",
  "INVALID<inline|unique|refcounted>",
  "unique|refcounted|simple",
  "INVALID<inline|unique|refcounted|hashed>",
  "unique|refcounted|hashed|simple",
  "INVALID<inline|immortal>",
  "simple|immortal",
  "INVALID<inline|hashed|immortal>",
  "hashed|simple|immortal",
  "INVALID<inline|refcounted|immortal>",
  "refcounted|simple|immortal",
  "INVALID<inline|refcounted|hashed|immortal>",
  "refcounted|hashed|simple|immortal",
  "INVALID<inline|unique|immortal>",
  "unique|simple|immortal",
  "INVALID<inline|unique|hashed|immortal>",
  "unique|hashed|simple|immortal",
  "INVALID<inline|unique|refcounted|immortal>",
  "unique|refcounted|simple|immortal",
  "INVALID<inline|unique|refcounted|hashed|immortal>",
  "unique|refcounted|hashed|simple|immortal",
};

static const dpa_u_a_bo_unique_t bo_error[] = {
  [E2BIG] = {{"\0E2BIG"}},
  [EACCES] = {{"\0EACCES"}},
  [EADDRINUSE] = {{"\0EADDRIN"}},
  [EADDRNOTAVAIL] = {{"\0EADDRNO"}},
  [EADV] = {{"\0EADV"}},
  [EAFNOSUPPORT] = {{"\0EAFNOSU"}},
  [EAGAIN] = {{"\0EAGAIN"}},
  [EALREADY] = {{"\0EALREAD"}},
  [EBADE] = {{"\0EBADE"}},
  [EBADF] = {{"\0EBADF"}},
  [EBADFD] = {{"\0EBADFD"}},
  [EBADMSG] = {{"\0EBADMSG"}},
  [EBADR] = {{"\0EBADR"}},
  [EBADRQC] = {{"\0EBADRQC"}},
  [EBADSLT] = {{"\0EBADSLT"}},
  [EBFONT] = {{"\0EBFONT"}},
  [EBUSY] = {{"\0EBUSY"}},
  [ECANCELED] = {{"\0ECANCEL"}},
  [ECHILD] = {{"\0ECHILD"}},
  [ECHRNG] = {{"\0ECHRNG"}},
  [ECOMM] = {{"\0ECOMM"}},
  [ECONNABORTED] = {{"\0ECONNAB"}},
  [ECONNREFUSED] = {{"\0ECREFUS"}},
  [ECONNRESET] = {{"\0ECRESET"}},
  [EDEADLK] = {{"\0EDEADLK"}},
#if EDEADLK != EDEADLOCK
  [EDEADLOCK] = {{"\0EDEADLO"}},
#endif
  [EDESTADDRREQ] = {{"\0EDESTAD"}},
  [EDOM] = {{"\0EDOM"}},
  [EDOTDOT] = {{"\0EDOTDOT"}},
  [EDQUOT] = {{"\0EDQUOT"}},
  [EEXIST] = {{"\0EEXIST"}},
  [EFAULT] = {{"\0EFAULT"}},
  [EFBIG] = {{"\0EFBIG"}},
  [EHOSTDOWN] = {{"\0EHOSTDO"}},
  [EHOSTUNREACH] = {{"\0EHOSTUN"}},
  [EHWPOISON] = {{"\0EHWPOIS"}},
  [EIDRM] = {{"\0EIDRM"}},
  [EILSEQ] = {{"\0EILSEQ"}},
  [EINPROGRESS] = {{"\0EINPROG"}},
  [EINTR] = {{"\0EINTR"}},
  [EINVAL] = {{"\0EINVAL"}},
  [EIO] = {{"\0EIO"}},
  [EISCONN] = {{"\0EISCONN"}},
  [EISDIR] = {{"\0EISDIR"}},
  [EISNAM] = {{"\0EISNAM"}},
  [EKEYEXPIRED] = {{"\0EKEYEXP"}},
  [EKEYREJECTED] = {{"\0EKEYREJ"}},
  [EKEYREVOKED] = {{"\0EKEYREV"}},
  [EL2HLT] = {{"\0EL2HLT"}},
  [EL2NSYNC] = {{"\0EL2NSYN"}},
  [EL3HLT] = {{"\0EL3HLT"}},
  [EL3RST] = {{"\0EL3RST"}},
  [ELIBACC] = {{"\0ELIBACC"}},
  [ELIBBAD] = {{"\0ELIBBAD"}},
  [ELIBEXEC] = {{"\0ELIBEXE"}},
  [ELIBMAX] = {{"\0ELIBMAX"}},
  [ELIBSCN] = {{"\0ELIBSCN"}},
  [ELNRNG] = {{"\0ELNRNG"}},
  [ELOOP] = {{"\0ELOOP"}},
  [EMEDIUMTYPE] = {{"\0EMEDIUM"}},
  [EMFILE] = {{"\0EMFILE"}},
  [EMLINK] = {{"\0EMLINK"}},
  [EMSGSIZE] = {{"\0EMSGSIZ"}},
  [EMULTIHOP] = {{"\0EMULTIH"}},
  [ENAMETOOLONG] = {{"\0ENAMETO"}},
  [ENAVAIL] = {{"\0ENAVAIL"}},
  [ENETDOWN] = {{"\0ENETDOW"}},
  [ENETRESET] = {{"\0ENETRES"}},
  [ENETUNREACH] = {{"\0ENETUNR"}},
  [ENFILE] = {{"\0ENFILE"}},
  [ENOANO] = {{"\0ENOANO"}},
  [ENOBUFS] = {{"\0ENOBUFS"}},
  [ENOCSI] = {{"\0ENOCSI"}},
  [ENODATA] = {{"\0ENODATA"}},
  [ENODEV] = {{"\0ENODEV"}},
  [ENOENT] = {{"\0ENOENT"}},
  [ENOEXEC] = {{"\0ENOEXEC"}},
  [ENOKEY] = {{"\0ENOKEY"}},
  [ENOLCK] = {{"\0ENOLCK"}},
  [ENOLINK] = {{"\0ENOLINK"}},
  [ENOMEDIUM] = {{"\0ENOMEDI"}},
  [ENOMEM] = {{"\0ENOMEM"}},
  [ENOMSG] = {{"\0ENOMSG"}},
  [ENONET] = {{"\0ENONET"}},
  [ENOPKG] = {{"\0ENOPKG"}},
  [ENOPROTOOPT] = {{"\0ENOPROT"}},
  [ENOSPC] = {{"\0ENOSPC"}},
  [ENOSR] = {{"\0ENOSR"}},
  [ENOSTR] = {{"\0ENOSTR"}},
  [ENOSYS] = {{"\0ENOSYS"}},
  [ENOTBLK] = {{"\0ENOTBLK"}},
  [ENOTCONN] = {{"\0ENOTCON"}},
  [ENOTDIR] = {{"\0ENOTDIR"}},
  [ENOTEMPTY] = {{"\0ENOTEMP"}},
  [ENOTNAM] = {{"\0ENOTNAM"}},
  [ENOTRECOVERABLE] = {{"\0ENOTREC"}},
  [ENOTSOCK] = {{"\0ENOTSOC"}},
  [ENOTSUP] = {{"\0ENOTSUP"}},
  [ENOTTY] = {{"\0ENOTTY"}},
  [ENOTUNIQ] = {{"\0ENOTUNI"}},
  [ENXIO] = {{"\0ENXIO"}},
#if ENOTSUP != EOPNOTSUPP
  [EOPNOTSUPP] = {{"\0EOPNOTS"}},
#endif
  [EOVERFLOW] = {{"\0EOVERFL"}},
  [EOWNERDEAD] = {{"\0EOWNERD"}},
  [EPERM] = {{"\0EPERM"}},
  [EPFNOSUPPORT] = {{"\0EPFNOSU"}},
  [EPIPE] = {{"\0EPIPE"}},
  [EPROTO] = {{"\0EPROTO"}},
  [EPROTONOSUPPORT] = {{"\0EPROTON"}},
  [EPROTOTYPE] = {{"\0EPROTOT"}},
  [ERANGE] = {{"\0ERANGE"}},
  [EREMCHG] = {{"\0EREMCHG"}},
  [EREMOTE] = {{"\0EREMOTE"}},
  [EREMOTEIO] = {{"\0EREMIO"}},
  [ERESTART] = {{"\0ERESTAR"}},
  [ERFKILL] = {{"\0ERFKILL"}},
  [EROFS] = {{"\0EROFS"}},
  [ESHUTDOWN] = {{"\0ESHUTDO"}},
  [ESOCKTNOSUPPORT] = {{"\0ESOCKTN"}},
  [ESPIPE] = {{"\0ESPIPE"}},
  [ESRCH] = {{"\0ESRCH"}},
  [ESRMNT] = {{"\0ESRMNT"}},
  [ESTALE] = {{"\0ESTALE"}},
  [ESTRPIPE] = {{"\0ESTRPIP"}},
  [ETIME] = {{"\0ETIME"}},
  [ETIMEDOUT] = {{"\0ETIMEDO"}},
  [ETOOMANYREFS] = {{"\0ETOOMAN"}},
  [ETXTBSY] = {{"\0ETXTBSY"}},
  [EUCLEAN] = {{"\0EUCLEAN"}},
  [EUNATCH] = {{"\0EUNATCH"}},
  [EUSERS] = {{"\0EUSERS"}},
#if EWOULDBLOCK != EAGAIN
  [EWOULDBLOCK] = {{"\0EWOULDB"}},
#endif
  [EXDEV] = {{"\0EXDEV"}},
  [EXFULL] = {{"\0EXFULL"}},
};

dpa__u_api dpa_u_a_bo_unique_t dpa_u_bo_error(int err){
  if(err < 0 || err >= (int)(sizeof(bo_error)/sizeof(*bo_error)))
    return (dpa_u_a_bo_unique_t){{"\0ERROR"}};
  return bo_error[err];
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

struct bo_unique_entry_simple {
  dpa_u_refcount_freeable_t refcount;
  dpa_u_bo_t bo;
};

struct bo_unique_entry_hashed {
  dpa_u_refcount_freeable_t refcount;
  struct dpa_u__bo_hashed bo;
};
static_assert(offsetof(struct bo_unique_entry_hashed, bo.bo) == offsetof(struct bo_unique_entry_simple, bo), "Unexpected offset");

dpa__u_api void dpa__u_bo_unique_destroy(const dpa_u_refcount_freeable_t* rc){
  const enum dpa_u_refcount_type type = dpa_u_refcount_get_type(&rc->refcount);
  struct bo_unique_entry_simple* bo = (struct bo_unique_entry_simple*)rc;
  if(type == DPA_U_REFCOUNT_BO_UNIQUE){
    free(bo->bo.data);
  }else{
    dpa_u_bo_put(dpa_u_container_of((char(*)[])bo->bo.data, struct dpa_u_refcount_freeable_data, data)->refcount);
  }
  free(bo);
}

dpa__u_api dpa_u_a_bo_unique_t dpa__u_bo_intern_h(dpa_u_a_bo_any_ro_t bo){
  if(dpa_u_bo_is_type(bo, DPA_U_BO_UNIQUE)){
    dpa_u_a_bo_unique_t res = {bo.p};
    dpa_u_bo_ref(res);
    return res;
  }
  const uint64_t hash = dpa_u_bo_get_hash(bo);
  const size_t size = dpa_u_bo_get_size(bo);
  const void* data = dpa_u_bo_get_data(bo);
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
  const uint64_t truncated_hash = (dpa__u_map_u64_hash_sub(hash) &  ~0xFFFF);
  // dpa_u_map_u64_it_safe_t it = {
  //   .entry = truncated_hash
  // };
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
    const dpa_u_bo_ro_t v = dpa_u_to_bo_ro(entry);
    if( v.size == size && ( v.data == data || !memcmp(data, v.data, size) )){
      dpa_u_bo_ref(entry);
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
  struct bo_unique_entry_hashed* eh = malloc(sizeof(*eh));
  if(!dpa_u_bo_is_type(bo, DPA_U_BO_REFCOUNTED|DPA_U_BO_IMMORTAL)){
    char* d = malloc(size);
    memcpy(d, data, size);
    data = d;
  }
  *eh = (struct bo_unique_entry_hashed){
    .bo.bo.size = size,
    .bo.bo.data = (char*)data,
    .bo.hash = hash,
  };
  dpa_u_a_bo_unique_t ret = { DPA_U__BO_TAG(&eh->bo, DPA_U_BO_UNIQUE|DPA_U_BO_HASHED|DPA_U_BO_SIMPLE) };
  dpa__u_map_u64_insert_sub(
    &unique_string_map,
    unused_e,
    (dpa_u_any_value_t){.u64=dpa_u_a_bo_unique_to_uint(ret)},
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
