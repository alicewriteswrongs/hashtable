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

void inserthash(hashtable *hashtab, unsigned char *key, char *value)
{ // insert key,value pair into hashtab
    unsigned char keyhash[SHA_DIGEST_LENGTH];
    int index = hashindex(hashtab, key, keyhash);
    list *temp = hashtab->table[index];
    listinsert(temp, nodegen(key, value));
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
        if (templist->head == templist->tail) {
        } else {
            printlist(templist);
        }
    }
}

void hash(unsigned char *key, unsigned char *output)
{
    size_t len = sizeof(key);
    SHA1(key, len, output);
}


