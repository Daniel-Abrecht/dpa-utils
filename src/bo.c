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
  [E2BIG] = {{"\5E2BIG"}},
  [EACCES] = {{"\6EACCES"}},
  [EADDRINUSE] = {{"\7EADDRIN"}},
  [EADDRNOTAVAIL] = {{"\7EADDRNO"}},
  [EADV] = {{"\4EADV"}},
  [EAFNOSUPPORT] = {{"\7EAFNOSU"}},
  [EAGAIN] = {{"\6EAGAIN"}},
  [EALREADY] = {{"\7EALREAD"}},
  [EBADE] = {{"\5EBADE"}},
  [EBADF] = {{"\5EBADF"}},
  [EBADFD] = {{"\6EBADFD"}},
  [EBADMSG] = {{"\7EBADMSG"}},
  [EBADR] = {{"\5EBADR"}},
  [EBADRQC] = {{"\7EBADRQC"}},
  [EBADSLT] = {{"\7EBADSLT"}},
  [EBFONT] = {{"\6EBFONT"}},
  [EBUSY] = {{"\5EBUSY"}},
  [ECANCELED] = {{"\7ECANCEL"}},
  [ECHILD] = {{"\6ECHILD"}},
  [ECHRNG] = {{"\6ECHRNG"}},
  [ECOMM] = {{"\5ECOMM"}},
  [ECONNABORTED] = {{"\7ECONNAB"}},
  [ECONNREFUSED] = {{"\7ECREFUS"}},
  [ECONNRESET] = {{"\7ECRESET"}},
  [EDEADLK] = {{"\7EDEADLK"}},
#if EDEADLK != EDEADLOCK
  [EDEADLOCK] = {{"\7EDEADLO"}},
#endif
  [EDESTADDRREQ] = {{"\7EDESTAD"}},
  [EDOM] = {{"\4EDOM"}},
  [EDOTDOT] = {{"\7EDOTDOT"}},
  [EDQUOT] = {{"\6EDQUOT"}},
  [EEXIST] = {{"\6EEXIST"}},
  [EFAULT] = {{"\6EFAULT"}},
  [EFBIG] = {{"\5EFBIG"}},
  [EHOSTDOWN] = {{"\7EHOSTDO"}},
  [EHOSTUNREACH] = {{"\7EHOSTUN"}},
  [EHWPOISON] = {{"\7EHWPOIS"}},
  [EIDRM] = {{"\5EIDRM"}},
  [EILSEQ] = {{"\6EILSEQ"}},
  [EINPROGRESS] = {{"\7EINPROG"}},
  [EINTR] = {{"\5EINTR"}},
  [EINVAL] = {{"\6EINVAL"}},
  [EIO] = {{"\3EIO"}},
  [EISCONN] = {{"\7EISCONN"}},
  [EISDIR] = {{"\6EISDIR"}},
  [EISNAM] = {{"\6EISNAM"}},
  [EKEYEXPIRED] = {{"\7EKEYEXP"}},
  [EKEYREJECTED] = {{"\7EKEYREJ"}},
  [EKEYREVOKED] = {{"\7EKEYREV"}},
  [EL2HLT] = {{"\6EL2HLT"}},
  [EL2NSYNC] = {{"\7EL2NSYN"}},
  [EL3HLT] = {{"\6EL3HLT"}},
  [EL3RST] = {{"\6EL3RST"}},
  [ELIBACC] = {{"\7ELIBACC"}},
  [ELIBBAD] = {{"\7ELIBBAD"}},
  [ELIBEXEC] = {{"\7ELIBEXE"}},
  [ELIBMAX] = {{"\7ELIBMAX"}},
  [ELIBSCN] = {{"\7ELIBSCN"}},
  [ELNRNG] = {{"\6ELNRNG"}},
  [ELOOP] = {{"\5ELOOP"}},
  [EMEDIUMTYPE] = {{"\7EMEDIUM"}},
  [EMFILE] = {{"\6EMFILE"}},
  [EMLINK] = {{"\6EMLINK"}},
  [EMSGSIZE] = {{"\7EMSGSIZ"}},
  [EMULTIHOP] = {{"\7EMULTIH"}},
  [ENAMETOOLONG] = {{"\7ENAMETO"}},
  [ENAVAIL] = {{"\7ENAVAIL"}},
  [ENETDOWN] = {{"\7ENETDOW"}},
  [ENETRESET] = {{"\7ENETRES"}},
  [ENETUNREACH] = {{"\7ENETUNR"}},
  [ENFILE] = {{"\6ENFILE"}},
  [ENOANO] = {{"\6ENOANO"}},
  [ENOBUFS] = {{"\7ENOBUFS"}},
  [ENOCSI] = {{"\6ENOCSI"}},
  [ENODATA] = {{"\7ENODATA"}},
  [ENODEV] = {{"\6ENODEV"}},
  [ENOENT] = {{"\6ENOENT"}},
  [ENOEXEC] = {{"\7ENOEXEC"}},
  [ENOKEY] = {{"\6ENOKEY"}},
  [ENOLCK] = {{"\6ENOLCK"}},
  [ENOLINK] = {{"\7ENOLINK"}},
  [ENOMEDIUM] = {{"\7ENOMEDI"}},
  [ENOMEM] = {{"\6ENOMEM"}},
  [ENOMSG] = {{"\6ENOMSG"}},
  [ENONET] = {{"\6ENONET"}},
  [ENOPKG] = {{"\6ENOPKG"}},
  [ENOPROTOOPT] = {{"\7ENOPROT"}},
  [ENOSPC] = {{"\6ENOSPC"}},
  [ENOSR] = {{"\5ENOSR"}},
  [ENOSTR] = {{"\6ENOSTR"}},
  [ENOSYS] = {{"\6ENOSYS"}},
  [ENOTBLK] = {{"\7ENOTBLK"}},
  [ENOTCONN] = {{"\7ENOTCON"}},
  [ENOTDIR] = {{"\7ENOTDIR"}},
  [ENOTEMPTY] = {{"\7ENOTEMP"}},
  [ENOTNAM] = {{"\7ENOTNAM"}},
  [ENOTRECOVERABLE] = {{"\7ENOTREC"}},
  [ENOTSOCK] = {{"\7ENOTSOC"}},
  [ENOTSUP] = {{"\7ENOTSUP"}},
  [ENOTTY] = {{"\6ENOTTY"}},
  [ENOTUNIQ] = {{"\7ENOTUNI"}},
  [ENXIO] = {{"\5ENXIO"}},
#if ENOTSUP != EOPNOTSUPP
  [EOPNOTSUPP] = {{"\7EOPNOTS"}},
#endif
  [EOVERFLOW] = {{"\7EOVERFL"}},
  [EOWNERDEAD] = {{"\7EOWNERD"}},
  [EPERM] = {{"\5EPERM"}},
  [EPFNOSUPPORT] = {{"\7EPFNOSU"}},
  [EPIPE] = {{"\5EPIPE"}},
  [EPROTO] = {{"\6EPROTO"}},
  [EPROTONOSUPPORT] = {{"\7EPROTON"}},
  [EPROTOTYPE] = {{"\7EPROTOT"}},
  [ERANGE] = {{"\6ERANGE"}},
  [EREMCHG] = {{"\7EREMCHG"}},
  [EREMOTE] = {{"\7EREMOTE"}},
  [EREMOTEIO] = {{"\6EREMIO"}},
  [ERESTART] = {{"\7ERESTAR"}},
  [ERFKILL] = {{"\7ERFKILL"}},
  [EROFS] = {{"\5EROFS"}},
  [ESHUTDOWN] = {{"\7ESHUTDO"}},
  [ESOCKTNOSUPPORT] = {{"\7ESOCKTN"}},
  [ESPIPE] = {{"\6ESPIPE"}},
  [ESRCH] = {{"\5ESRCH"}},
  [ESRMNT] = {{"\6ESRMNT"}},
  [ESTALE] = {{"\6ESTALE"}},
  [ESTRPIPE] = {{"\7ESTRPIP"}},
  [ETIME] = {{"\5ETIME"}},
  [ETIMEDOUT] = {{"\7ETIMEDO"}},
  [ETOOMANYREFS] = {{"\7ETOOMAN"}},
  [ETXTBSY] = {{"\7ETXTBSY"}},
  [EUCLEAN] = {{"\7EUCLEAN"}},
  [EUNATCH] = {{"\7EUNATCH"}},
  [EUSERS] = {{"\6EUSERS"}},
#if EWOULDBLOCK != EAGAIN
  [EWOULDBLOCK] = {{"\7EWOULDB"}},
#endif
  [EXDEV] = {{"\5EXDEV"}},
  [EXFULL] = {{"\6EXFULL"}},
};

dpa__u_api dpa_u_a_bo_unique_t dpa_u_bo_error(int err){
  if(err < 0 || err >= (int)(sizeof(bo_error)/sizeof(*bo_error)))
    return (dpa_u_a_bo_unique_t){{"\5ERROR"}};
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
  if(!dpa_u_refcount_is_zero(rc))
    goto end;
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

dpa__u_api dpa_u_a_bo_unique_t dpa__u_bo_intern_h(dpa_u_a_bo_any_ro_t bo){
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_UNIQUE)){
    dpa_u_a_bo_unique_t res = {bo.p};
    dpa_u_bo_ref(res);
    return res;
  }
  const size_t size = dpa_u_bo_get_size(bo);
  const void* data = dpa_u_bo_get_data(bo);
  if(size <= 7){
    dpa_u_a_bo_unique_t res = {{{DPA_U_BO_UNIQUE+size}}};
    memcpy(res.p.c+1, data, size);
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
  int entry_size = sizeof(dpa_u_bo_t);
  int type = DPA_U_BO_UNIQUE | DPA_U_BO_SIMPLE;
  if(size > 64){
    type |= DPA_U_BO_HASHED;
    entry_size = sizeof(dpa__u_bo_hashed_t);
  }
  if(dpa_u_bo_is_any_type(bo, DPA_U_BO_IMMORTAL)){
    type |= DPA_U_BO_IMMORTAL;
  }else{
    type |= DPA_U_BO_REFCOUNTED;
    entry_size += sizeof(dpa_u_refcount_t);
  }
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED|DPA_U_BO_IMMORTAL))
    entry_size += size;
  void* eh = malloc(entry_size);
  if(!dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED|DPA_U_BO_IMMORTAL)){
    char* d = (char*)eh + entry_size - size;
    memcpy(d, data, size);
    data = d;
  }
  if(type & DPA_U_BO_REFCOUNTED){
    struct dpa__u_refcount_bo_unique* rc = eh;
    rc->value = dpa_u_bo_is_any_type(bo, DPA_U_BO_REFCOUNTED)
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
  dpa_u_a_bo_unique_t ret = { DPA_U__BO_TAG(eh, type) };
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
