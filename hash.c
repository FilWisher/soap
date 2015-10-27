#include <openssl/sha.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
  size_t length = sizeof(argv[2]);
  
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1(argv[2], length, hash);
  
  int fd = open(argv[1], O_WRONLY);
  if (fd < 0) {
    printf("AOEUAOEU"); 
  }
  write(fd, hash, SHA_DIGEST_LENGTH);
  
  return 0;
}
