#include <dpa/utils/test.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>

struct dpa__u_testcase* dpa__u_testcase_list;

bool dpa_u_testcase_result(int fd, const char* name, const char* result){
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
  mem[2+name_length] = 0;
  memcpy(mem+2+name_length+1, result, result_length);
  // This has to be a single write (because this is a SOCK_SEQPACKET socket)
  if(write(fd, mem, length) != (ssize_t)length){
    perror("write");
    return false;
  }
  return true;
}

int dpa_u_test_main(int argc, const char* argv[]){
  if(argc == 1){
    for(struct dpa__u_testcase* it=dpa__u_testcase_list; it; it=it->next)
      puts(it->name);
  }else if(argc == 2){
    for(struct dpa__u_testcase* it=dpa__u_testcase_list; it; it=it->next){
      if(strcmp(it->name, argv[1]) && strcmp(argv[1], "-a"))
        continue;
      if(dpa__u_test_setup)
        dpa__u_test_setup();
      int res = it->run();
      if(dpa__u_test_teardown)
        dpa__u_test_teardown();
      return res;
    }
  }
  return 10;
}
