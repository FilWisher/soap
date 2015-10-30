# soap
Experimenting with how to hash files

## hashing?
We can run an array af bytes through an algorithm to transform it into a shorter, fixed-length array of bytes.

Hashing algorithms are deterministing by definition: it will transform the same input X to the same output Y every time.

This means that I can transform the string "hello" into, for example, "a4fg8e" (hex representation of a byte array). From "a4fg8e", if we can't reverse the algorithm to get back the string "hello"; the algorithm is *crytographically* secure. SHA1 is a deterministic, crytographically-secure, hashing algorithm.

## why?
hashing is useful for:
 - content-addressing - asking for a file by its contents (hashed)
 - dedeplicating data - files can only be stored once (if hashes are the same, they will overwrite)
 - checking integrity - if the hash has changed, the file has changed
 - sorting (and retrieving) (hash-tables/hash-trees/hash-DAGs) - hashes can be used to introduce the above benefits to familiar data structures.

## how?
For now: we just use the openssl API functions e.g. ```SHA1(...)```
