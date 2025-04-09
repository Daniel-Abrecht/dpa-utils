#include <dpa/utils/threads.h>
#ifdef DPA__U_THREADS_POLYFILL

dpa__u_api pthread_mutexattr_t dpa__u_attr_recursive;

extern int thrd_create(thrd_t* thread, thrd_start_t func, void* arg);
extern int thrd_equal(thrd_t a, thrd_t b);
extern thrd_t thrd_current(void);
extern int thrd_sleep(const struct timespec* duration, struct timespec* remaining);
extern void thrd_yield(void);
extern _Noreturn void thrd_exit(int res);
extern int thrd_detach(thrd_t thread);
extern int thrd_join(thrd_t thread, int* res);
extern int mtx_init(mtx_t* mutex, int type);
extern void mtx_destroy(mtx_t* mutex);
extern int mtx_lock(mtx_t* mutex);
extern int mtx_unlock(mtx_t* mutex);
extern int mtx_trylock(mtx_t* mutex);
extern int mtx_timedlock(mtx_t* mutex, const struct timespec*restrict time_point);
extern void call_once(once_flag* flag, void (*func)(void));
extern int cnd_init(cnd_t* cond);
extern void cnd_destroy(cnd_t* cond);
extern int cnd_signal(cnd_t* cond);
extern int cnd_broadcast(cnd_t* cond);
extern int cnd_wait(cnd_t* cond, mtx_t* mutex);
extern int cnd_timedwait(cnd_t* cond, mtx_t* mutex, const struct timespec*restrict abstime);
extern int tss_create(tss_t* key, tss_dtor_t destructor);
extern void* tss_get(tss_t key);
extern int tss_set(tss_t key, void* val);
extern void tss_delete(tss_t key);

static dpa_u_init void init(void){
  pthread_mutexattr_init(&dpa__u_attr_recursive);
  pthread_mutexattr_settype(&dpa__u_attr_recursive, PTHREAD_MUTEX_RECURSIVE);
}

dpa__u_api void* dpa__u_thrd_create_wrapper(void* p){
  const struct dpa__u_thrd_create_wrapper_args* a = p;
  return (void*)(uintptr_t)a->func(a->arg);
}

#endif
