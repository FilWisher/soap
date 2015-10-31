#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <stdio.h>

#define PREFIX ".wil"

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
  strncpy(path, PREFIX, strlen(PREFIX)+1);
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
