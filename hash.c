#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>

int
string_to_hex(unsigned char *str, char *hex)
{
  for (int i = 0; i < strlen(str); i++) {
    sprintf(&hex[i*2], "%02x", str[i]); 
  }
}

int
create_hash(char *text, unsigned char hash[])
{
  size_t len = sizeof(text);
  SHA1(text, len, hash);
}
