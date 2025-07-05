#include <dpa/utils/test.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <spawn.h>
#include <wait.h>

dpa__u_api struct dpa__u_testcase* dpa__u_testcase_list;

dpa__u_api bool dpa_u_testcase_result(int fd, const char* name, const char* result){
  if(fd < 0){
    static int sfd = -1;
    if(sfd == -1){
      const char* tfd = getenv("TESTSUITE_FD");
      if(!tfd) return false;
      int x = atoi(tfd);
      if(x < 0) return false;
      sfd = x;
    }
    fd = sfd;
  }
  const size_t name_length = (name && *name) ? strlen(name)+1 : 0;
  const size_t result_length = strlen(result);
  const size_t length = 2+name_length+1+result_length;
  if(length > 0x1000)
    return false;
  char mem[length];
  mem[0] = length >> 8;
  mem[1] = length;
  if(name_length)
    memcpy(mem+2, name, name_length);
  for(size_t i=0; i<name_length; i++)
    if(mem[2+i] == '\t')
      mem[2+i] = 0;
  mem[2+name_length] = 0;
  memcpy(mem+2+name_length+1, result, result_length);
  // This has to be a single write (because this is a SOCK_SEQPACKET socket)
  if(write(fd, mem, length) != (ssize_t)length){
    perror("write");
    return false;
  }
  return true;
}

dpa__u_api int dpa_u_test_main(int argc, const char* argv[]){
  if(argc == 2 && !strcmp(argv[1], "-l")){
    for(struct dpa__u_testcase* it=dpa__u_testcase_list; it; it=it->next)
      puts(it->name);
    return 0;
  }else if(argc == 2){
    for(struct dpa__u_testcase* it=dpa__u_testcase_list; it; it=it->next){
      if(argc > 1 && strcmp(it->name, argv[1]))
        continue;
      if(dpa_u_test_setup)
        dpa_u_test_setup();
      int res = it->run();
      if(dpa_u_test_teardown)
        dpa_u_test_teardown();
      return res;
    }
    fprintf(stderr, "No test '%s' found\n", argv[1]);
    return 1;
  }else{
    bool any_failed = false;
    for(struct dpa__u_testcase* it=dpa__u_testcase_list; it; it=it->next){
      if(argc > 1){
        for(int i=1; i<argc; i++)
          if(!strcmp(it->name, argv[i]))
            goto found;
        continue;
        found:;
      }
      pid_t pid;
      extern char **environ;
      int error = posix_spawn(&pid, "/proc/self/exe", 0, 0, (char**)(const char*[]){argv[0],it->name,0}, environ);
      if(error){
        fprintf(stderr, "posix_spawn failed: %d: %s\n", errno, strerror(errno));
        continue;
      }
      int status;
      retry: if(waitpid(pid, &status, 0) == -1){
        if(errno == EINTR)
          goto retry;
        perror("waitpid failed");
        continue;
      }
      if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
        dpa_u_testcase_result(-1, it->name, "success");
        continue;
      }
      any_failed = true;
      dpa_u_testcase_result(-1, it->name, "failed");
      if(WIFSIGNALED(status))
        fprintf(stderr, "test '%s' was terminated by signal %d: %s\n", it->name, WTERMSIG(status), strsignal(WTERMSIG(status)));
    }
    return any_failed;
  }
}
