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
For now: just use the openssl API functions e.g. ```SHA1(...)```

## so...?
KEY:
"\<file name\>" => "file contents"

Let's say we have file A. It contains "hello world". I can hash the file, save its contents in a new file under the name if its hash. We now have "ab42d97a" => "hello world".

Now I have file B. It contains "goodbye world". I can do the same hashing above and now we have "e4f98c1e" => "goodbye world".

Now I can have a file that contains: 
```
A  ab42d97a
B  e4f98c1e
```
and is stored under the hash produced by running this contents through the hash algorithm, for example "726ba93a".

We now have a tree like so:
```
               name:     726ba93a
               contents: A  ab42d97a
                         B  e4f98c1e
                        /\
                       /  \
  name:      ab42d97a      name: e4f98c1e
  contents: hello world    contents: goodbye world
```

The hash of the root also informs us about the integrity of the entire tree. The hash of any node will tell us the integrity of its entire subtree. We can detect changes anywhere in the tree and find the hash. 
