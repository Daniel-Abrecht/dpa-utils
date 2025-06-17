#ifndef DPA_U_THREADS_H
#define DPA_U_THREADS_H
#include <dpa/utils/common.h>
#ifdef DPA_U_NO_THREADS
#warning "DPA_U_NO_THREADS has been specified!"
#else
#if !defined(__STDC_NO_THREADS__) && DPA__U__has_include(<threads.h>)
#include <threads.h>
#else
// polyfill //
#define DPA__U_THREADS_POLYFILL
#include <pthread.h>
#include <time.h>
#include <sched.h>
#include <errno.h>
#include <stdint.h>

#ifndef thread_local
#define thread_local _Thread_local
#endif

typedef pthread_once_t once_flag;
#define ONCE_FLAG_INIT PTHREAD_ONCE_INIT;

typedef int(*thrd_start_t)(void*);
typedef void(*tss_dtor_t)(void*);

enum {
  thrd_success = 0,
  thrd_error = -1,
  thrd_nomem = -2,
  thrd_timedout = -3,
  thrd_busy = -4,
};

enum {
  mtx_plain = 0,
  mtx_timed = 1,
  mtx_recursive = 2,
  // mtx_timed | mtx_recursive = 3
};

typedef struct {
  pthread_t v;
} thrd_t;

typedef struct {
  pthread_mutex_t v;
} mtx_t;

typedef struct {
  pthread_cond_t v;
} cnd_t;

typedef struct {
  pthread_key_t v;
} tss_t;

struct dpa__u_thrd_create_wrapper_args {
  thrd_start_t func;
  void* arg;
};

dpa__u_api extern void* dpa__u_thrd_create_wrapper(void*);

dpa__u_api inline int thrd_create(thrd_t* thread, thrd_start_t func, void* arg){
  int res = pthread_create(&thread->v, 0, dpa__u_thrd_create_wrapper, &(struct dpa__u_thrd_create_wrapper_args){func,arg});
  if(res == 0)
    return  thrd_success;
  if(res == EAGAIN)
    return thrd_nomem;
  return thrd_error;
}

dpa__u_api inline int thrd_equal(thrd_t a, thrd_t b){
  return pthread_equal(a.v, b.v);
}

dpa__u_api inline thrd_t thrd_current(void){
  return (thrd_t){pthread_self()};
}

dpa__u_api inline int thrd_sleep(const struct timespec* duration, struct timespec* remaining){
  int ret = nanosleep(duration,remaining);
  if(!ret) return 0;
  if(errno == EINTR) return -1;
  return -2;
}

dpa__u_api inline void thrd_yield(void){
  //pthread_yield();
  sched_yield();
}

dpa__u_api inline _Noreturn void thrd_exit(int res){
  pthread_exit((void*)(uintptr_t)res);
}

dpa__u_api inline int thrd_detach(thrd_t thread){
  return pthread_detach(thread.v) ? thrd_error : thrd_success;
}

dpa__u_api inline int thrd_join(thrd_t thread, int* res){
  void* ret;
  int s = pthread_join(thread.v, &ret);
  if(s) return thrd_error;
  *res = (int)(uintptr_t)ret;
  return thrd_success;
}

dpa__u_api_var extern pthread_mutexattr_t dpa__u_attr_recursive;

dpa__u_api inline int mtx_init(mtx_t* mutex, int type){
  pthread_mutexattr_t* attr = 0;
  if(type & mtx_recursive)
    attr = &dpa__u_attr_recursive;
  return pthread_mutex_init(&mutex->v, attr) ? thrd_error : thrd_success;
}

dpa__u_api inline void mtx_destroy(mtx_t* mutex){
  pthread_mutex_destroy(&mutex->v);
}

dpa__u_api inline int mtx_lock(mtx_t* mutex){
  return pthread_mutex_lock(&mutex->v) ? thrd_error : thrd_success;
}

dpa__u_api inline int mtx_unlock(mtx_t* mutex){
  return pthread_mutex_unlock(&mutex->v) ? thrd_error : thrd_success;
}

dpa__u_api inline int mtx_trylock(mtx_t* mutex){
  switch(pthread_mutex_lock(&mutex->v)){
    case 0: return thrd_success;
    case EBUSY: return thrd_busy;
  }
  return thrd_error;
}

dpa__u_api inline int mtx_timedlock(mtx_t* mutex, const struct timespec*restrict time_point){
  switch(pthread_mutex_timedlock(&mutex->v, time_point)){
    case 0: return thrd_success;
    case ETIMEDOUT: return thrd_timedout;
  }
  return thrd_error;
}

dpa__u_api inline void call_once(once_flag* flag, void (*func)(void)){
  pthread_once(flag, func);
}

dpa__u_api inline int cnd_init(cnd_t* cond){
  switch(pthread_cond_init(&cond->v, 0)){
    case 0: return thrd_success;
    case ENOMEM: return thrd_nomem;
  }
  return thrd_error;
}

dpa__u_api inline void cnd_destroy(cnd_t* cond){
  pthread_cond_destroy(&cond->v);
}

dpa__u_api inline int cnd_signal(cnd_t* cond){
  return pthread_cond_signal(&cond->v) ? thrd_error : thrd_success;
}

dpa__u_api inline int cnd_broadcast(cnd_t* cond){
  return pthread_cond_broadcast(&cond->v) ? thrd_error : thrd_success;
}

dpa__u_api inline int cnd_wait(cnd_t* cond, mtx_t* mutex){
  return pthread_cond_wait(&cond->v, &mutex->v) ? thrd_error : thrd_success;
}

dpa__u_api inline int cnd_timedwait(cnd_t* cond, mtx_t* mutex, const struct timespec*restrict abstime){
  switch(pthread_cond_timedwait(&cond->v, &mutex->v, abstime)){
    case 0: return thrd_success;
    case ETIMEDOUT: return thrd_timedout;
  }
  return thrd_error;
}

dpa__u_api inline int tss_create(tss_t* key, tss_dtor_t destructor){
  return pthread_key_create(&key->v, destructor);
}

dpa__u_api inline void* tss_get(tss_t key){
  return pthread_getspecific(key.v);
}

dpa__u_api inline int tss_set(tss_t key, void* val){
  return pthread_setspecific(key.v, val) ? thrd_error : thrd_success;
}

dpa__u_api inline void tss_delete(tss_t key){
  pthread_key_delete(key.v);
}

#endif
#endif
#endif
