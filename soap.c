#include <openssl/sha.h>
#include <unistd.h>
#include <stdio.h> 
#include "file.h"
#include "hash.h"

#define PREFIX ".wil"

int
main(int argc, char *argv[])
{
  int fd;
  unsigned char hash[SHA_DIGEST_LENGTH];
  char hex_hash[SHA_DIGEST_LENGTH];
  char path[1000];
  char contents[10000];
  char *target = argv[1];

  create_dir(PREFIX);
  
  int target_fd = open_file(target);
  if (read(target_fd, contents, 10000) < 0) {
    perror("read"); 
  }
 
  create_hash(contents, hash);
  string_to_hex(hash, hex_hash); 
  make_file_path(hex_hash, path);
  
  copy_contents(target, path);
 
  close(target_fd);
  
  return 0;
}
