#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include "hashlist.h"

/* My hashtable implementation. This code is free to use/re-use/whatever */
/* if you find it helpful */
/* :D */

/* This is a hashtable using SHA1 - we use a linked list implementation */
/* I wrote to provide for separate chaining. Every bin in the table */ 
/* is initialized pointing to an empty linked list, if we hash a key */ 
/* that points to that node then we add things to that list (key/value pairs) */
/* then later we can look in that list to find everything hashed to that key! */
/* To make this work you also need the 'hashlist.h' file in the same directory */
/* which defines the doubly linked list we use here for separate chaining */

typedef struct hashtable {
    int size;
    list **table;
} hashtable;

int hashindex(hashtable *table, unsigned char *key, unsigned char *output)
{ // takes a key, gives you the index for it
    size_t len = sizeof(key);
    SHA1(key, len, output);

    int i = 1;
    int arraykey = 1;
    int j = 0;

    while (i < table->size) {
        arraykey *= output[j++];
        i *= 256;
    }
    return arraykey % table->size;
}

char *hashlookup(hashtable *hashtab, unsigned char *key)
{ // find the value for key in hashtab
    unsigned char keyhash[SHA_DIGEST_LENGTH];
    int index;
    index = hashindex(hashtab, key, keyhash);
    list *templist = hashtab->table[index];
    if (empty(templist))
        return "not found";
    else {
        node *tempnode = listkeysearch(templist, key);
        return tempnode->value;
    }
}

void inserthash(hashtable *hashtab, unsigned char *key, char *value)
{ // insert key,value pair into hashtab
    unsigned char keyhash[SHA_DIGEST_LENGTH];
    int index = hashindex(hashtab, key, keyhash);
    list *temp = hashtab->table[index];
    listinsert(temp, nodegen(key, value, keyhash));
}

hashtable *hashinit(int size)
{ // allocates hashtable array, returns pointer to array
    list **hasharray;
    hasharray = malloc(sizeof (list) * size);
    hashtable *hashtab;
    hashtab = malloc(sizeof (hashtable));

    int i;
    for (i = 0; i < size; i++) {
        hasharray[i] = listinit();
    }

    hashtab->table = hasharray;
    hashtab->size = size;
    return hashtab;
}

void destroyhash(hashtable *oldtable)
{ // destroy!!
    int i;
    for (i = 0; i < oldtable->size; i++) {
        destroylist(oldtable->table[i]);
    }
    free(oldtable);
}

void printhashtab(hashtable *toprint)
{
    int i;
    list *templist;
    printf("keys:\tvalues:\n");
    for (i = 0; i < toprint->size; i++) {
        templist = toprint->table[i];
        if (! (empty(templist)))
            printlist(templist);
    }
}

void hashdel(hashtable *hashtab, unsigned char *toremove)
{ // delete the key/value pair from the hashtable
    unsigned char keyhash[SHA_DIGEST_LENGTH];
    int index = hashindex(hashtab, toremove, keyhash);
    list *templist = hashtab->table[index];
    if (! (empty(templist))) {
        node *delnode = listkeysearch(templist, toremove);
        listremove(templist, delnode);
    }
}



void hash(unsigned char *key, unsigned char *output)
{ // for testing
    size_t len = sizeof(key);
    SHA1(key, len, output);
}
