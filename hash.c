#include <openssl/sha.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

char *prefix = ".wil";

int
create_dir(char *name)
{
  struct stat st = {0};
  if (stat(name, &st) == -1) {
    mkdir(name, 0700); 
    return 1;
  }
  return 0;
}

int
create_hash(char *text, unsigned char hash[])
{
  size_t len = sizeof(text);
  SHA1(text, len, hash);
}

int
open_file(char *name)
{
  int fd;
  if ((fd = open(name, O_WRONLY | O_CREAT, 0700)) < 0) {
    perror("open"); 
  }
  return fd;
}

int
write_file(int fd, unsigned char *text)
{
  if (write(fd, text, SHA_DIGEST_LENGTH)) {
    perror("write");
    return 1;
  }
  return 0;
}

int
make_file_path(char *filename, char *path)
{
  strcat(path, prefix);
  strcat(path, "/");
  strcat(path, filename);
  return 1;
}

int
copy_contents(char *file_src, char *file_dst)
{
  /* TODO: check errors */
  int fd_src, fd_dst;
  char buffer[1024];
  fd_src = open(file_src, O_RDONLY);
  fd_dst = open(file_src, O_WRONLY);
  while (read(fd_src, buffer, 1024) > 0) {
    write(fd_dst, buffer, 1024); 
  }
}

int
main(int argc, char *argv[])
{
  int fd;
  unsigned char hash[SHA_DIGEST_LENGTH];
  char path[1000];
  char contents[10000];
  char *target = argv[1];

  int target_fd = open_file(target);
  read(target_fd, contents, 1024);
  
  create_hash(contents, hash);
  
  make_file_path(hash, path);
  
  printf("path: %s\n", path);
  create_dir(prefix);
 
  copy_contents(target, path);
  
  return 0;
}
