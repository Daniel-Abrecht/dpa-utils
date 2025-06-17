#include <dpa/utils/bo.h>
#include <dpa/utils/mem.h>
#include <dpa/utils/map.h>
#ifndef DPA_U_NO_THREADS
#include <dpa/utils/threads.h>
#endif
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

#if defined(__AVR) && defined(ENOERR)
#define BAD_ERRNOS
#endif

#ifndef BAD_ERRNOS
static const dpa_u_a_bo_unique_t bo_error[] = {
  [0] = {{{DPA__U_INLINE_STRING('E','R','R','O','R',' ','0')}}},
#ifdef E2BIG
  [E2BIG] = {{{DPA__U_INLINE_STRING('E','2','B','I','G')}}},
#endif
#ifdef EACCES
  [EACCES] = {{{DPA__U_INLINE_STRING('E','A','C','C','E','S')}}},
#endif
#ifdef EADDRINUSE
  [EADDRINUSE] = {{{DPA__U_INLINE_STRING('E','A','D','D','R','I','N')}}},
#endif
#ifdef EADDRNOTAVAIL
  [EADDRNOTAVAIL] = {{{DPA__U_INLINE_STRING('E','A','D','D','R','N','O')}}},
#endif
#ifdef EADV
  [EADV] = {{{DPA__U_INLINE_STRING('E','A','D','V')}}},
#endif
#ifdef EAFNOSUPPORT
  [EAFNOSUPPORT] = {{{DPA__U_INLINE_STRING('E','A','F','N','O','S','U')}}},
#endif
#ifdef EAGAIN
  [EAGAIN] = {{{DPA__U_INLINE_STRING('E','A','G','A','I','N')}}},
#endif
#ifdef EALREADY
  [EALREADY] = {{{DPA__U_INLINE_STRING('E','A','L','R','E','A','D')}}},
#endif
#ifdef EBADE
  [EBADE] = {{{DPA__U_INLINE_STRING('E','B','A','D','E')}}},
#endif
#ifdef EBADF
  [EBADF] = {{{DPA__U_INLINE_STRING('E','B','A','D','F')}}},
#endif
#ifdef EBADFD
  [EBADFD] = {{{DPA__U_INLINE_STRING('E','B','A','D','F','D')}}},
#endif
#ifdef EBADMSG
  [EBADMSG] = {{{DPA__U_INLINE_STRING('E','B','A','D','M','S','G')}}},
#endif
#ifdef EBADR
  [EBADR] = {{{DPA__U_INLINE_STRING('E','B','A','D','R')}}},
#endif
#ifdef EBADRQC
  [EBADRQC] = {{{DPA__U_INLINE_STRING('E','B','A','D','R','Q','C')}}},
#endif
#ifdef EBADSLT
  [EBADSLT] = {{{DPA__U_INLINE_STRING('E','B','A','D','S','L','T')}}},
#endif
#ifdef EBFONT
  [EBFONT] = {{{DPA__U_INLINE_STRING('E','B','F','O','N','T')}}},
#endif
#ifdef EBUSY
  [EBUSY] = {{{DPA__U_INLINE_STRING('E','B','U','S','Y')}}},
#endif
#ifdef ECANCELED
  [ECANCELED] = {{{DPA__U_INLINE_STRING('E','C','A','N','C','E','L')}}},
#endif
#ifdef ECHILD
  [ECHILD] = {{{DPA__U_INLINE_STRING('E','C','H','I','L','D')}}},
#endif
#ifdef ECHRNG
  [ECHRNG] = {{{DPA__U_INLINE_STRING('E','C','H','R','N','G')}}},
#endif
#ifdef ECOMM
  [ECOMM] = {{{DPA__U_INLINE_STRING('E','C','O','M','M')}}},
#endif
#ifdef ECONNABORTED
  [ECONNABORTED] = {{{DPA__U_INLINE_STRING('E','C','O','N','N','A','B')}}},
#endif
#ifdef ECONNREFUSED
  [ECONNREFUSED] = {{{DPA__U_INLINE_STRING('E','C','R','E','F','U','S')}}},
#endif
#ifdef ECONNRESET
  [ECONNRESET] = {{{DPA__U_INLINE_STRING('E','C','R','E','S','E','T')}}},
#endif
#ifdef EDEADLK
  [EDEADLK] = {{{DPA__U_INLINE_STRING('E','D','E','A','D','L','K')}}},
#endif
#ifdef EDEADLOCK
#if EDEADLK != EDEADLOCK
  [EDEADLOCK] = {{{DPA__U_INLINE_STRING('E','D','E','A','D','L','O')}}},
#endif
#endif
#ifdef EDESTADDRREQ
  [EDESTADDRREQ] = {{{DPA__U_INLINE_STRING('E','D','E','S','T','A','D')}}},
#endif
#ifdef EDOM
  [EDOM] = {{{DPA__U_INLINE_STRING('E','D','O','M')}}},
#endif
#ifdef EDOTDOT
  [EDOTDOT] = {{{DPA__U_INLINE_STRING('E','D','O','T','D','O','T')}}},
#endif
#ifdef EDQUOT
  [EDQUOT] = {{{DPA__U_INLINE_STRING('E','D','Q','U','O','T')}}},
#endif
#ifdef EEXIST
  [EEXIST] = {{{DPA__U_INLINE_STRING('E','E','X','I','S','T')}}},
#endif
#ifdef EFAULT
  [EFAULT] = {{{DPA__U_INLINE_STRING('E','F','A','U','L','T')}}},
#endif
#ifdef EFBIG
  [EFBIG] = {{{DPA__U_INLINE_STRING('E','F','B','I','G')}}},
#endif
#ifdef EHOSTDOWN
  [EHOSTDOWN] = {{{DPA__U_INLINE_STRING('E','H','O','S','T','D','O')}}},
#endif
#ifdef EHOSTUNREACH
  [EHOSTUNREACH] = {{{DPA__U_INLINE_STRING('E','H','O','S','T','U','N')}}},
#endif
#ifdef EHWPOISON
  [EHWPOISON] = {{{DPA__U_INLINE_STRING('E','H','W','P','O','I','S')}}},
#endif
#ifdef EIDRM
  [EIDRM] = {{{DPA__U_INLINE_STRING('E','I','D','R','M')}}},
#endif
#ifdef EILSEQ
  [EILSEQ] = {{{DPA__U_INLINE_STRING('E','I','L','S','E','Q')}}},
#endif
#ifdef EINPROGRESS
  [EINPROGRESS] = {{{DPA__U_INLINE_STRING('E','I','N','P','R','O','G')}}},
#endif
#ifdef EINTR
  [EINTR] = {{{DPA__U_INLINE_STRING('E','I','N','T','R')}}},
#endif
#ifdef EINVAL
  [EINVAL] = {{{DPA__U_INLINE_STRING('E','I','N','V','A','L')}}},
#endif
#ifdef EIO
  [EIO] = {{{DPA__U_INLINE_STRING('E','I','O')}}},
#endif
#ifdef EISCONN
  [EISCONN] = {{{DPA__U_INLINE_STRING('E','I','S','C','O','N','N')}}},
#endif
#ifdef EISDIR
  [EISDIR] = {{{DPA__U_INLINE_STRING('E','I','S','D','I','R')}}},
#endif
#ifdef EISNAM
  [EISNAM] = {{{DPA__U_INLINE_STRING('E','I','S','N','A','M')}}},
#endif
#ifdef EKEYEXPIRED
  [EKEYEXPIRED] = {{{DPA__U_INLINE_STRING('E','K','E','Y','E','X','P')}}},
#endif
#ifdef EKEYREJECTED
  [EKEYREJECTED] = {{{DPA__U_INLINE_STRING('E','K','E','Y','R','E','J')}}},
#endif
#ifdef EKEYREVOKED
  [EKEYREVOKED] = {{{DPA__U_INLINE_STRING('E','K','E','Y','R','E','V')}}},
#endif
#ifdef EL2HLT
  [EL2HLT] = {{{DPA__U_INLINE_STRING('E','L','2','H','L','T')}}},
#endif
#ifdef EL2NSYNC
  [EL2NSYNC] = {{{DPA__U_INLINE_STRING('E','L','2','N','S','Y','N')}}},
#endif
#ifdef EL3HLT
  [EL3HLT] = {{{DPA__U_INLINE_STRING('E','L','3','H','L','T')}}},
#endif
#ifdef EL3RST
  [EL3RST] = {{{DPA__U_INLINE_STRING('E','L','3','R','S','T')}}},
#endif
#ifdef ELIBACC
  [ELIBACC] = {{{DPA__U_INLINE_STRING('E','L','I','B','A','C','C')}}},
#endif
#ifdef ELIBBAD
  [ELIBBAD] = {{{DPA__U_INLINE_STRING('E','L','I','B','B','A','D')}}},
#endif
#ifdef ELIBEXEC
  [ELIBEXEC] = {{{DPA__U_INLINE_STRING('E','L','I','B','E','X','E')}}},
#endif
#ifdef ELIBMAX
  [ELIBMAX] = {{{DPA__U_INLINE_STRING('E','L','I','B','M','A','X')}}},
#endif
#ifdef ELIBSCN
  [ELIBSCN] = {{{DPA__U_INLINE_STRING('E','L','I','B','S','C','N')}}},
#endif
#ifdef ELNRNG
  [ELNRNG] = {{{DPA__U_INLINE_STRING('E','L','N','R','N','G')}}},
#endif
#ifdef ELOOP
  [ELOOP] = {{{DPA__U_INLINE_STRING('E','L','O','O','P')}}},
#endif
#ifdef EMEDIUMTYPE
  [EMEDIUMTYPE] = {{{DPA__U_INLINE_STRING('E','M','E','D','I','U','M')}}},
#endif
#ifdef EMFILE
  [EMFILE] = {{{DPA__U_INLINE_STRING('E','M','F','I','L','E')}}},
#endif
#ifdef EMLINK
  [EMLINK] = {{{DPA__U_INLINE_STRING('E','M','L','I','N','K')}}},
#endif
#ifdef EMSGSIZE
  [EMSGSIZE] = {{{DPA__U_INLINE_STRING('E','M','S','G','S','I','Z')}}},
#endif
#ifdef EMULTIHOP
  [EMULTIHOP] = {{{DPA__U_INLINE_STRING('E','M','U','L','T','I','H')}}},
#endif
#ifdef ENAMETOOLONG
  [ENAMETOOLONG] = {{{DPA__U_INLINE_STRING('E','N','A','M','E','T','O')}}},
#endif
#ifdef ENAVAIL
  [ENAVAIL] = {{{DPA__U_INLINE_STRING('E','N','A','V','A','I','L')}}},
#endif
#ifdef ENETDOWN
  [ENETDOWN] = {{{DPA__U_INLINE_STRING('E','N','E','T','D','O','W')}}},
#endif
#ifdef ENETRESET
  [ENETRESET] = {{{DPA__U_INLINE_STRING('E','N','E','T','R','E','S')}}},
#endif
#ifdef ENETUNREACH
  [ENETUNREACH] = {{{DPA__U_INLINE_STRING('E','N','E','T','U','N','R')}}},
#endif
#ifdef ENFILE
  [ENFILE] = {{{DPA__U_INLINE_STRING('E','N','F','I','L','E')}}},
#endif
#ifdef ENOANO
  [ENOANO] = {{{DPA__U_INLINE_STRING('E','N','O','A','N','O')}}},
#endif
#ifdef ENOBUFS
  [ENOBUFS] = {{{DPA__U_INLINE_STRING('E','N','O','B','U','F','S')}}},
#endif
#ifdef ENOCSI
  [ENOCSI] = {{{DPA__U_INLINE_STRING('E','N','O','C','S','I')}}},
#endif
#ifdef ENODATA
  [ENODATA] = {{{DPA__U_INLINE_STRING('E','N','O','D','A','T','A')}}},
#endif
#ifdef ENODEV
  [ENODEV] = {{{DPA__U_INLINE_STRING('E','N','O','D','E','V')}}},
#endif
#ifdef ENOENT
  [ENOENT] = {{{DPA__U_INLINE_STRING('E','N','O','E','N','T')}}},
#endif
#ifdef ENOEXEC
  [ENOEXEC] = {{{DPA__U_INLINE_STRING('E','N','O','E','X','E','C')}}},
#endif
#ifdef ENOKEY
  [ENOKEY] = {{{DPA__U_INLINE_STRING('E','N','O','K','E','Y')}}},
#endif
#ifdef ENOLCK
  [ENOLCK] = {{{DPA__U_INLINE_STRING('E','N','O','L','C','K')}}},
#endif
#ifdef ENOLINK
  [ENOLINK] = {{{DPA__U_INLINE_STRING('E','N','O','L','I','N','K')}}},
#endif
#ifdef ENOMEDIUM
  [ENOMEDIUM] = {{{DPA__U_INLINE_STRING('E','N','O','M','E','D','I')}}},
#endif
#ifdef ENOMEM
  [ENOMEM] = {{{DPA__U_INLINE_STRING('E','N','O','M','E','M')}}},
#endif
#ifdef ENOMSG
  [ENOMSG] = {{{DPA__U_INLINE_STRING('E','N','O','M','S','G')}}},
#endif
#ifdef ENONET
  [ENONET] = {{{DPA__U_INLINE_STRING('E','N','O','N','E','T')}}},
#endif
#ifdef ENOPKG
  [ENOPKG] = {{{DPA__U_INLINE_STRING('E','N','O','P','K','G')}}},
#endif
#ifdef ENOPROTOOPT
  [ENOPROTOOPT] = {{{DPA__U_INLINE_STRING('E','N','O','P','R','O','T')}}},
#endif
#ifdef ENOSPC
  [ENOSPC] = {{{DPA__U_INLINE_STRING('E','N','O','S','P','C')}}},
#endif
#ifdef ENOSR
  [ENOSR] = {{{DPA__U_INLINE_STRING('E','N','O','S','R')}}},
#endif
#ifdef ENOSTR
  [ENOSTR] = {{{DPA__U_INLINE_STRING('E','N','O','S','T','R')}}},
#endif
#ifdef ENOSYS
  [ENOSYS] = {{{DPA__U_INLINE_STRING('E','N','O','S','Y','S')}}},
#endif
#ifdef ENOTBLK
  [ENOTBLK] = {{{DPA__U_INLINE_STRING('E','N','O','T','B','L','K')}}},
#endif
#ifdef ENOTCONN
  [ENOTCONN] = {{{DPA__U_INLINE_STRING('E','N','O','T','C','O','N')}}},
#endif
#ifdef ENOTDIR
  [ENOTDIR] = {{{DPA__U_INLINE_STRING('E','N','O','T','D','I','R')}}},
#endif
#ifdef ENOTEMPTY
  [ENOTEMPTY] = {{{DPA__U_INLINE_STRING('E','N','O','T','E','M','P')}}},
#endif
#ifdef ENOTNAM
  [ENOTNAM] = {{{DPA__U_INLINE_STRING('E','N','O','T','N','A','M')}}},
#endif
#ifdef ENOTRECOVERABLE
  [ENOTRECOVERABLE] = {{{DPA__U_INLINE_STRING('E','N','O','T','R','E','C')}}},
#endif
#ifdef ENOTSOCK
  [ENOTSOCK] = {{{DPA__U_INLINE_STRING('E','N','O','T','S','O','C')}}},
#endif
#ifdef ENOTSUP
  [ENOTSUP] = {{{DPA__U_INLINE_STRING('E','N','O','T','S','U','P')}}},
#endif
#ifdef ENOTTY
  [ENOTTY] = {{{DPA__U_INLINE_STRING('E','N','O','T','T','Y')}}},
#endif
#ifdef ENOTUNIQ
  [ENOTUNIQ] = {{{DPA__U_INLINE_STRING('E','N','O','T','U','N','I')}}},
#endif
#ifdef ENXIO
  [ENXIO] = {{{DPA__U_INLINE_STRING('E','N','X','I','O')}}},
#endif
#ifdef EOPNOTSUPP
#if ENOTSUP != EOPNOTSUPP
  [EOPNOTSUPP] = {{{DPA__U_INLINE_STRING('E','O','P','N','O','T','S')}}},
#endif
#endif
#ifdef EOVERFLOW
  [EOVERFLOW] = {{{DPA__U_INLINE_STRING('E','O','V','E','R','F','L')}}},
#endif
#ifdef EOWNERDEAD
  [EOWNERDEAD] = {{{DPA__U_INLINE_STRING('E','O','W','N','E','R','D')}}},
#endif
#ifdef EPERM
  [EPERM] = {{{DPA__U_INLINE_STRING('E','P','E','R','M')}}},
#endif
#ifdef EPFNOSUPPORT
  [EPFNOSUPPORT] = {{{DPA__U_INLINE_STRING('E','P','F','N','O','S','U')}}},
#endif
#ifdef EPIPE
  [EPIPE] = {{{DPA__U_INLINE_STRING('E','P','I','P','E')}}},
#endif
#ifdef EPROTO
  [EPROTO] = {{{DPA__U_INLINE_STRING('E','P','R','O','T','O')}}},
#endif
#ifdef EPROTONOSUPPORT
  [EPROTONOSUPPORT] = {{{DPA__U_INLINE_STRING('E','P','R','O','T','O','N')}}},
#endif
#ifdef EPROTOTYPE
  [EPROTOTYPE] = {{{DPA__U_INLINE_STRING('E','P','R','O','T','O','T')}}},
#endif
#ifdef ERANGE
  [ERANGE] = {{{DPA__U_INLINE_STRING('E','R','A','N','G','E')}}},
#endif
#ifdef EREMCHG
  [EREMCHG] = {{{DPA__U_INLINE_STRING('E','R','E','M','C','H','G')}}},
#endif
#ifdef EREMOTE
  [EREMOTE] = {{{DPA__U_INLINE_STRING('E','R','E','M','O','T','E')}}},
#endif
#ifdef EREMOTEIO
  [EREMOTEIO] = {{{DPA__U_INLINE_STRING('E','R','E','M','I','O')}}},
#endif
#ifdef ERESTART
  [ERESTART] = {{{DPA__U_INLINE_STRING('E','R','E','S','T','A','R')}}},
#endif
#ifdef ERFKILL
  [ERFKILL] = {{{DPA__U_INLINE_STRING('E','R','F','K','I','L','L')}}},
#endif
#ifdef EROFS
  [EROFS] = {{{DPA__U_INLINE_STRING('E','R','O','F','S')}}},
#endif
#ifdef ESHUTDOWN
  [ESHUTDOWN] = {{{DPA__U_INLINE_STRING('E','S','H','U','T','D','O')}}},
#endif
#ifdef ESOCKTNOSUPPORT
  [ESOCKTNOSUPPORT] = {{{DPA__U_INLINE_STRING('E','S','O','C','K','T','N')}}},
#endif
#ifdef ESPIPE
  [ESPIPE] = {{{DPA__U_INLINE_STRING('E','S','P','I','P','E')}}},
#endif
#ifdef ESRCH
  [ESRCH] = {{{DPA__U_INLINE_STRING('E','S','R','C','H')}}},
#endif
#ifdef ESRMNT
  [ESRMNT] = {{{DPA__U_INLINE_STRING('E','S','R','M','N','T')}}},
#endif
#ifdef ESTALE
  [ESTALE] = {{{DPA__U_INLINE_STRING('E','S','T','A','L','E')}}},
#endif
#ifdef ESTRPIPE
  [ESTRPIPE] = {{{DPA__U_INLINE_STRING('E','S','T','R','P','I','P')}}},
#endif
#ifdef ETIME
  [ETIME] = {{{DPA__U_INLINE_STRING('E','T','I','M','E')}}},
#endif
#ifdef ETIMEDOUT
  [ETIMEDOUT] = {{{DPA__U_INLINE_STRING('E','T','I','M','E','D','O')}}},
#endif
#ifdef ETOOMANYREFS
  [ETOOMANYREFS] = {{{DPA__U_INLINE_STRING('E','T','O','O','M','A','N')}}},
#endif
#ifdef ETXTBSY
  [ETXTBSY] = {{{DPA__U_INLINE_STRING('E','T','X','T','B','S','Y')}}},
#endif
#ifdef EUCLEAN
  [EUCLEAN] = {{{DPA__U_INLINE_STRING('E','U','C','L','E','A','N')}}},
#endif
#ifdef EUNATCH
  [EUNATCH] = {{{DPA__U_INLINE_STRING('E','U','N','A','T','C','H')}}},
#endif
#ifdef EUSERS
  [EUSERS] = {{{DPA__U_INLINE_STRING('E','U','S','E','R','S')}}},
#endif
#ifdef EWOULDBLOCK
#if EWOULDBLOCK != EAGAIN
  [EWOULDBLOCK] = {{{DPA__U_INLINE_STRING('E','W','O','U','L','D','B')}}},
#endif
#endif
#ifdef EXDEV
  [EXDEV] = {{{DPA__U_INLINE_STRING('E','X','D','E','V')}}},
#endif
#ifdef EXFULL
  [EXFULL] = {{{DPA__U_INLINE_STRING('E','X','F','U','L','L')}}},
#endif
};
static_assert(sizeof(bo_error)/sizeof(*bo_error) < 1024, "Ridiculus errno values!");
#endif

dpa__u_api dpa_u_a_bo_unique_t dpa_u_bo_error(int err){
#ifndef BAD_ERRNOS
  if(dpa_u_unlikely(err < 0 || err >= (int)(sizeof(bo_error)/sizeof(*bo_error)) || !bo_error[err].p.value[0])){
#endif
    if(err < 0 || err >= 1000000)
      return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING('E','R','R','O','R')}}};
    return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING('E', ((err/100000)%10)+'0', ((err/10000)%10)+'0', ((err/1000)%10)+'0', ((err/100)%10)+'0', ((err/10)%10)+'0', (err%10)+'0')}}};
#ifndef BAD_ERRNOS
  }
  return bo_error[err];
#endif
}

dpa__u_api int dpa_u_bo_error_to_errno(dpa_u_a_bo_unique_t bo){
  (void)bo;
#ifndef BAD_ERRNOS
  for(unsigned i=0; i<sizeof(bo_error)/sizeof(*bo_error); i++)
    if(!memcmp(&bo, &bo_error[i], 8))
      return i;
#endif
  return -1;
}

static dpa_u_map_u64_t unique_string_map;

#ifndef DPA_U_NO_THREADS
static mtx_t unique_string_map_lock;
static dpa_u_init void init(void){
  mtx_init(&unique_string_map_lock, mtx_plain);
}
#endif

dpa__u_api const char* dpa_u_bo_type_to_string(enum dpa_u_bo_type_flags type){
  if(type>=0x100 || type<0)
    return "INVALID";
  return dpa_u_bo_type[type>>3];
}

dpa__u_api void dpa__u_bo_unique_destroy(const dpa_u_refcount_freeable_t* rc){
#ifndef DPA_U_NO_THREADS
  mtx_lock(&unique_string_map_lock);
  if(!dpa_u_refcount_is_zero(rc)){
    // This only happens if the entry was picked from the set before it was removed. In that case, it was incremented.
    // That reference is taken by dpa__u_bo_intern_h on behalf of this function, under the unique_string_map_lock lock.
    // We drop it again.
    if(dpa_u_refcount_decrement(&rc->refcount))
      goto end; // This is not the last reference anymore.
  }
#endif
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
    dpa_u_refcount_put(((dpa_u_refcount_freeable_t**)bo)[-1]);
  free((void*)rc);
#ifndef DPA_U_NO_THREADS
end:
  mtx_unlock(&unique_string_map_lock);
#endif
}

dpa__u_api dpa_u_a_bo_unique_t dpa__u_bo_intern_h(dpa_u_a_bo_any_t bo){
  if(dpa_u_bo_is_error(bo))
    return (dpa_u_a_bo_unique_t){{{DPA__U_INLINE_STRING('E','I','N','V','A','L')}}};
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

#ifndef DPA_U_NO_THREADS
  mtx_lock(&unique_string_map_lock);
#endif

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
#ifndef DPA_U_NO_THREADS
      if(dpa_u_refcount_is_zero(rc)){
        // This entry was due for removal. We increment the refcount one more on behalf of the dpa__u_bo_unique_destroy
        // callback, which is going to run later. This ensures the refcount doesn't hit 0 before that happens again.
        dpa_u_refcount_ref(rc);
      }
#endif
      dpa_u_refcount_ref(rc);
#ifndef DPA_U_NO_THREADS
      mtx_unlock(&unique_string_map_lock);
#endif
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
  bool has_extref = false;
  if(size > 64){
    type |= DPA_U_BO_HASHED;
    entry_size = sizeof(dpa__u_bo_hashed_t);
    has_extref = bo_type & DPA_U_BO_REFCOUNTED; // If the BO is small, it may not be worth storing the refcount.
  }
  if(has_extref)
    entry_size += sizeof(dpa_u_refcount_freeable_t*);
  if(bo_type & DPA_U_BO_STATIC){
    type |= DPA_U_BO_STATIC;
  }else{
    type |= DPA_U_BO_REFCOUNTED;
    entry_size += sizeof(dpa_u_refcount_t);
  }
  const bool data_inlined = !(bo_type & DPA_U_BO_STATIC) && !has_extref;
  if(data_inlined)
    entry_size += size;
  void*restrict eh = malloc(entry_size);
  if(data_inlined){
    char*restrict d = (char*)eh + entry_size - size;
    memcpy(d, data, size);
    data = d;
  }else if(has_extref){
    dpa_u_refcount_freeable_t* extref = dpa_u_container_of(DPA__U_BO_UNTAG(dpa_u_bo_t*, bo.p), dpa__u_bo_refcounted_t, bo)->refcount;
    dpa_u_refcount_increment(extref);
    *((dpa_u_refcount_freeable_t**)eh) = extref;
    eh = ((dpa_u_refcount_freeable_t**)eh)+1;
  }
  if(type & DPA_U_BO_REFCOUNTED){
    struct dpa__u_refcount_bo_unique*const rc = eh;
    rc->value = bo_type & DPA_U_BO_REFCOUNTED
              ? DPA_U_REFCOUNT_INIT(DPA_U_REFCOUNT_BO_UNIQUE_EXTREF) + 1
              : DPA_U_REFCOUNT_INIT(DPA_U_REFCOUNT_BO_UNIQUE) + 1;
    eh = rc+1;
  }
  *(dpa_u_bo_t*restrict)eh = (dpa_u_bo_t){
    .size = size,
    .data = (char*)data,
  };
  if(type & DPA_U_BO_HASHED)
    ((dpa__u_bo_hashed_t*restrict)eh)->hash = hash;
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

#ifndef DPA_U_NO_THREADS
  mtx_unlock(&unique_string_map_lock);
#endif
  return ret;
error:
#ifndef DPA_U_NO_THREADS
  mtx_unlock(&unique_string_map_lock);
#endif
  return dpa_u_bo_error(error);
}
