#define _DEFAULT_SOURCE
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <dpa/utils/test.h>

#define NUMPAD 3

// This isn't very efficient, but it's just test results so whatever...
struct testsuite {
  struct testsuite *children;
  struct testsuite *parent;
  struct testsuite *next;
  char* name;
  size_t total;
  size_t result_count;
  struct result_value* result;
};

struct result_value {
  size_t value;
};

static unsigned i_success = ~0u;
static unsigned i_failed = ~0u;
static int parent_fd = -1;
static char buf[0x1000];
static char** result_name;
static size_t result_count;
static struct testsuite testsuite;
static bool got_results = false;
static int level_limit = ~0u >> 1;
static bool failed = false;

static struct testsuite* testsuite_create_sub(const char* name, struct testsuite* parent, struct testsuite** next){
  struct testsuite* ts = calloc(1, sizeof(*ts));
  if(!ts){
    perror("malloc");
    return 0;
  }
  ts->name = strdup(name);
  if(!ts->name){
    perror("strdup");
    free(ts->name);
    return 0;
  }
  ts->parent = parent;
  if(next){
    ts->next = *next;
    *next = ts;
  }
  if(parent && !parent->children)
    parent->children = ts;
  return ts;
}

static struct testsuite* testsuite_create(const char* ns){
  struct testsuite* ts = &testsuite;
  for(size_t nslen=0,off=0; (nslen=strlen(ns+off)); off += nslen+1){
    if(!ts->children){
      ts = testsuite_create_sub(ns+off, ts, 0);
      if(!ts) return 0;
    }else{
      struct testsuite** it = &ts->children;
      while(true){
        int result = strcmp(ns+off, (*it)->name);
        if(result == 0){
          ts = *it;
          break;
        }else if(result > 0){
          it = &(*it)->next;
          if(*it) continue;
        }
        ts = testsuite_create_sub(ns+off, ts, it);
        if(!ts) return 0;
      }
    }
  }
  return ts;
}

ssize_t result_name_create(size_t len, const char name[static len]){
  for(size_t i=0; i<result_count; i++)
    if(!strncmp(result_name[i], name, len))
      return i;
  char** tmp = realloc(result_name, (result_count+1)*sizeof(*result_name));
  if(!tmp){
    perror("realloc");
    return -1;
  }
  result_name = tmp;
  char* dname = strndup(name, len);
  if(!dname){
    perror("strndup");
    return -1;
  }
  result_name[result_count] = dname;
  if(!strcmp(dname, "success")){
    i_success = result_count;
  }else if(!strcmp(dname, "failed")){
    i_failed = result_count;
  }
  return result_count++;
}

static void final_message_handler(const char* ns, size_t msglen, const char msg[msglen]){
  struct testsuite* ts = testsuite_create(ns);
  if(!ts){
    fprintf(stderr, "testsuite_create failed\n");
    return;
  }
  ssize_t i = result_name_create(msglen, msg);
  if(i < 0){
    fprintf(stderr, "result_name_create failed\n");
    return;
  }
  for(struct testsuite* it=ts; it; it=it->parent){
    if(it->result_count <= (size_t)i){
      struct result_value* rv = realloc(it->result, sizeof(*rv)*result_count);
      if(!rv){
        perror("realloc");
        return;
      }
      memset(rv+it->result_count, 0, sizeof(*rv) * (result_count - it->result_count));
      it->result = rv;
      it->result_count = result_count;
    }
    struct result_value* rv = &it->result[i];
    rv->value += 1;
    it->total += 1;
  }
  if(strncmp(msg, "success", msglen) && strncmp(msg, "skipped", msglen))
    failed = true;
}

static void message_handler(size_t length){
  got_results = true;
  static size_t name_length;
  if(!name_length)
    name_length = strlen(testsuite.name);
  if(parent_fd >= 0){
    if(sizeof(buf) - length < name_length+1)
      return;
    memmove(buf+2+name_length+1, buf+2, length-2);
    memcpy(buf+2, testsuite.name, name_length+1);
    length += name_length+1;
    buf[0] = length >> 8;
    buf[1] = length;
    // This has to be a single write (because this is a SOCK_SEQPACKET socket)
    if(write(parent_fd, buf, length) != (ssize_t)length)
      perror("write");
    return;
  }
  size_t off=2, i=0;
  for(size_t nslen; off < length && (nslen=strnlen(buf+off, length-off)); off += nslen+1)
    i += 1;
  if(++off > length)
    return;
  (void)i;
  final_message_handler(buf+2, length-off, buf+off);
}

static void print_testsuite(struct testsuite* ts, int level){
  static const struct result_value nrv = {0};
  for(size_t i=0; i<result_count; i++){
    const struct result_value* rv = i<ts->result_count ? &ts->result[i] : &nrv;
    printf("%*zu ", NUMPAD, rv->value);
  }
  const bool success = (unsigned long)ts->result_count > i_success && ts->result[i_success].value;
  const bool failed  = (unsigned long)ts->result_count > i_failed && ts->result[i_failed].value;
  const char* color1 = "";
  const char* color2 = "\033[0;0m";
  if(failed && success){
    color1 = "\033[0;33m";
  }else if(failed){
    color1 = "\033[1;31m";
  }else if(success){
    color1 = "\033[0;32m";
  }else{
    color1 = "\033[1;35m";
  }
  if(!*color1) color2 = "";
  printf("%*s%s%s%s\n", level*2, "", color1, ts->name, color2);
}

static void print_testsuite_level(struct testsuite* ts, int level){
  for(;ts;ts=ts->next){
    if(level > level_limit && level_limit >= 0)
      continue;
    if(level_limit == -1 && level != 0 && ts->total <= 1)
      continue;
    print_testsuite(ts, level);
    if(level_limit == -2 && level != 0 && ts->total <= 1)
      continue;
    print_testsuite_level(ts->children, level+1);
  }
}

static void print_results(void){
  {
    const char* tsl = getenv("TESTSUITE_LEVEL");
    if(tsl)
      level_limit = atoi(tsl);
  }
  for(size_t i=0; i<result_count; i++){
    printf("%*s%s\n", (int)i*(NUMPAD+1), "", result_name[i]);
  }
  print_testsuite_level(&testsuite, 0);
}

int main(int argc, char* argv[]){
  if(argc < 3){
    fprintf(stderr, "usage: %s name cmd [args...]\n", argv[0]);
    return 10;
  }
  argc -= 1; argv += 1;
  testsuite.name = argv[0]; argc -= 1; argv += 1;
  {
    const char* value = getenv("TESTSUITE_FD");
    if(value)
      parent_fd = atoi(value);
  }
  int pair[2];
  if(socketpair(AF_UNIX, SOCK_SEQPACKET, 0, pair) == -1){
    perror("socketpair");
    return 10;
  }
  if(fcntl(pair[0], F_SETFD, FD_CLOEXEC) == -1){
    perror("fcntl");
    return 10;
  }
  pid_t pid = fork();
  if(pid == -1){
    perror("fork");
    return 10;
  }
  if(!pid){
    close(pair[0]);
    if(parent_fd >= 0){
      if(pair[1] == parent_fd || dup2(pair[1], parent_fd) == -1){
        perror("dup2");
        return 10;
      }
      close(pair[1]);
    }else{
      parent_fd = pair[1];
      snprintf(buf, sizeof(buf), "%d", parent_fd);
      setenv("TESTSUITE_FD", buf, true);
    }
    execvp(argv[0], argv);
    perror("execvp");
    if(!dpa_u_testcase_result(parent_fd, 0, "unavailable"))
      fprintf(stderr, "function \"dpa_u_testcase_result\" failed");
    return 10;
  }
  close(pair[1]);
  while(true){
    ssize_t size = read(pair[0], buf, sizeof(buf));
    if(!size)
      break;
    if(size < 0){
      if(errno == EINTR)
        continue;
      perror("read");
      return 10;
    }
    size_t length = (buf[0]&0xFF)<<8 | (buf[1]&0xFF);
    if(length > sizeof(buf) && size == sizeof(buf)){
      fprintf(stderr, "packet too large!\n");
      // TODO: discard
      continue;
    }
    if(length != (size_t)size || length < 2){
      fprintf(stderr, "got incomplete or invalid packet! %zu != %zu\n", length, (size_t)size);
      continue;
    }
    message_handler(length);
  }
  const char* result = 0;
  int status = 1;
  while(waitpid(pid, &status, 0) == -1){
    if(errno == EINTR)
      continue;
    perror("waitpid");
    result = "unknown";
    break;
  }
  if(!result){
    if(WIFEXITED(status)){
      status = WEXITSTATUS(status);
    }else if(WIFSIGNALED(status)){
      status = WTERMSIG(status);
      if(status) status = 10;
    }else status = 10;
    if(status == 0){
      result = "success";
    }else{
      result = "failed";
    }
  }
  if(parent_fd == -1){
    if(!got_results)
      final_message_handler("", strlen(result), result);
    print_results();
  }else{
    if(!got_results)
      dpa_u_testcase_result(parent_fd, testsuite.name, result);
  }
  return failed;
}
