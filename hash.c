#include <openssl/sha.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

char *prefix = ".wil";

int
string_to_hex(unsigned char *str, char *hex)
{
  for (int i = 0; i < strlen(str); i++) {
    sprintf(&hex[i*2], "%02x", str[i]); 
  }
}

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
  if ((fd = open(name, O_RDONLY | O_CREAT, 0700)) < 0) {
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
  strncpy(path, prefix, strlen(prefix)+1);
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
  if((fd_src = open(file_src, O_RDONLY)) < 0) {
    goto error; 
  }
  if((fd_dst = open(file_dst, O_WRONLY | O_CREAT, 0700)) < 0) {
    goto error;   
  }
  while (read(fd_src, buffer, 1024) > 0) {
    write(fd_dst, buffer, strlen(buffer)); 
  }
  close(fd_src);
  close(fd_dst);
  return 1;

error:
  close(fd_src);
  close(fd_src);
  return 0;
}

int
main(int argc, char *argv[])
{
  int fd;
  unsigned char hash[SHA_DIGEST_LENGTH];
  char hex_hash[SHA_DIGEST_LENGTH];
  char path[1000];
  char contents[10000];
  char *target = argv[1];

  create_dir(prefix);
  
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

