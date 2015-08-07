#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include "hashtable.h"

int main() {
    printf("initialize list:\n");
    list *mylist = listinit();
    printlist(mylist);
    
    printf("\nadd things:\n");
    listinsert(mylist, nodegen("key", "value"));
    listinsert(mylist, nodegen("bloop", "dingles"));
    node *testnode = nodegen("canwe", "delete?");
    listinsert(mylist, testnode);
    printlist(mylist);

    printf("\nremove things:\n");
    listremove(mylist, testnode);
    printlist(mylist);

    printf("\nsearch for things!\n");
    node *search = listsearch(mylist, "bloop", "dingles");
    listremove(mylist, search);
    printlist(mylist);

    printf("\ninitialize the hashtable:\n");
    hashtable *table;
    table = hashinit(100);

    printf("\ntwo things should hash to the same value:\n");
    unsigned char trial_text[] = "let's check that!";
    printf("going to hash: '%s'\n", trial_text);
    unsigned char trialone[SHA_DIGEST_LENGTH];
    unsigned char trialtwo[SHA_DIGEST_LENGTH];
    hash(trial_text, trialone);
    hash(trial_text, trialtwo);
    int i;
    printf("one:\n");
    for (i = 0; i < SHA_DIGEST_LENGTH; i++) {
        printf("%02x ", trialone[i]);
    }
    printf("\ntwo:\n");
    for (i = 0; i < SHA_DIGEST_LENGTH; i++) {
        printf("%02x ", trialtwo[i]);
    }

    printf("\ndestroy a hashtable:\n");
    destroyhash(table);
    table = hashinit(100);
    printf("success!\n");
    inserthash(table, "key", "value");

    printf("\ninsert some things into the table:\n");
    inserthash(table, "mykey", "myvalue");
    printf("success!\n");

    printf("\ntry to print the table:\n");
    printhashtab(table);

    printf("\nInsert more things!\n");
    inserthash(table, "purple", "dinosaur");
    inserthash(table, "blue", "potato");
    inserthash(table, "chicken", "duck");
    printhashtab(table);

}
