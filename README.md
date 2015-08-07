#Hash table

OK, we're going to make a hash table! Cool! What is a hash table? Well,
it's basically a data structure that implements an associative array. An
associative array is an ADT that is a set of key-value pairs, where
a particular key may appear at most once in the array. There are a couple
of operations that are commonly supported, like inserting a new key-value
pair, getting the value associated with a particular key, deleting
a key-value pair, and so on.

All that is great, but how do we actually implement it? Well, there are
a variety of choices to be made. This image stolen from wikipedia gives us
an idea of what we're shooting for:

![](https://upload.wikimedia.org/wikipedia/commons/7/7d/Hash_table_3_1_1_0_1_0_0_SP.svg)

So what we'd like is a function where we can hash a string like `John
Smith` and get the array index `02` out. That sounds great, but we've got
a problem, and the name of that problem is hash collision.

##Collisions and collisions

One of the problems with this is that unless we allocate an amount of
storage similar to the keyspace size to our array (the array whose indices
we'll get from the hash function) we will have collisions. A collision is
when two values (`title` and `director`, if we're storing movie info)
produce the same hash value. We need to think hard about what to do in
this case.

If the keys for our key/value store (associative array) are going to be,
say, strings of up to 20 characters, then the keyspace is really really
big. We do not want to allocate enough space to completely avoid
collisions (which would require allocated space equal to keyspace size)
since we'd probably like to store other things on our computer besides our
small movie database.

So how do we get around this? Well, one simple way is with the modulo
operator. Say we make a guess about how much storage to allocate - maybe
we want to do 1000 records or so. So we can allocate an array with
dimension 1000, and then once we hash our keys we can take `hash(key)
% 1000` to get an array index into which to stick the value.

That sounds great, but what about collisions? Well, there's a couple of
things we could do. What we're going to do is called separate chaining.
Basically we make each bin of our hash table (so the array entry
`hash(key)`) point to a linked list - in that linked list we can store
everything that hashes to that particular key. Nice!

I wrote a new implementation of a doubly-linked list that includes two
`*char` in order to hold both the key and the value (we want to store both
in our list so that we can tell which value corresponds to which key).

##Hash functions

I think for this we're just going to use the SHA1 hash - this isn't
considered secure for crypto work but it should be good enough here. We
can get it on Linux from `openssl/sha.h`, handy! To get that to work you
need to run gcc with the `-I/usr/include/openssl` and `-lcrypto` flags
(assuming you're running Debian or similar, it may be different on other
distros or on e.g. OSX).

We're just going to do something like:

```C
#include <openssl/sha.h>

unsigned char *hash(unsigned char *key, unsigned char *output)
{ // get the hash of a key
    size_t len = sizeof(key);
    SHA1(key, len, output);
}
```

Then the function `hash` will return the SHA1 hash of `key`. Nice! 











