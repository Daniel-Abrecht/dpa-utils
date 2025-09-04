#define _GNU_SOURCE /* required for O_PATH */

#include <dpa/utils/unicode.h>

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define DPA_U_DEFAULT_DATA_DIR "/usr/local/share/dpa/utils/"

const dpa_u_unicode_codepoint_t* unicodedata_0;
size_t unicodedata_0_length;

#ifndef O_PATH
#warning "O_PATH isn't defined"
#define O_PATH O_RDONLY
#endif

dpa_u_init static void init(void){
  const char* data_dir_str = getenv("DPA_U_DATA_DIR");
  if(!data_dir_str)
    data_dir_str = DPA_U_DEFAULT_DATA_DIR;
  int data_dir = open(data_dir_str, O_PATH|O_DIRECTORY);
  if(data_dir == -1){
    fprintf(stderr, "open(\"%s\"): %d %s\n", data_dir_str, errno, strerror(errno));
    goto error;
  }

  int unicode_dir = openat(data_dir, "unicode", O_PATH|O_DIRECTORY);
  if(unicode_dir == -1){
    fprintf(stderr, "open(\"%s/unicode/\"): %d %s\n", data_dir_str, errno, strerror(errno));
    goto error2;
  }
  int unicode_data_fd = openat(unicode_dir, "UnicodeData.0.bin", O_RDONLY);
  if(unicode_data_fd == -1){
    fprintf(stderr, "open(\"%s/unicode/UnicodeData.0.bin\"): %d %s\n", data_dir_str, errno, strerror(errno));
    goto error3;
  }
  off_t size = lseek(unicode_data_fd, 0, SEEK_END);
  if(size < 0){
    perror("lseek");
    goto error4;
  }
  void* data = mmap(0, size, PROT_READ, MAP_PRIVATE, unicode_data_fd, 0);
  if(data == MAP_FAILED){
    perror("mmap");
    goto error4;
  }
  unicodedata_0 = data;
  unicodedata_0_length = size;
error4:
  close(unicode_data_fd);
error3:
  close(unicode_dir);

error2:
  close(data_dir);
error:
  return;
}
