#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

This is a doubly linked list that I wrote to use in my hash table
implementation. It's sort of specialized for that, although mainly 
just in that it has pointers to three different values (key, value,
hash) and that it has a smaller set of functions for normal list
operations (i.e. we only insert at the head of the list, no 
function for reversing, etc). Check out my 

// structs
typedef struct node {
    struct node *previous;
    struct node *next;
    char *key;
    char *value;
    unsigned char *hash;
} node;

typedef struct list {
    node *head;
    node *tail;
} list;

// functions
list *listinit()
{
    list *newlist;
    newlist = malloc(sizeof (list));
    node *sentinel;
    sentinel = malloc(sizeof (node));

    sentinel->key = '\0';
    sentinel->value = '\0';
    sentinel->hash = '\0';
    sentinel->next = sentinel;
    sentinel->previous = sentinel;

    newlist->head = sentinel;
    newlist->tail = sentinel;
    
    return newlist;
}

void destroylist(list *oldlist)
{
    node *sentinel = oldlist->tail;
    node *iternode = oldlist->head;
    node *next;
    while (iternode != sentinel) {
        next = iternode->next;
        free(iternode);
        iternode = next;
    }
    free(sentinel);
    free(oldlist);
}

node *nodegen(char *key, char *value, unsigned char *hash)
{ // make a new node
    node *newnode;
    newnode = malloc(sizeof (node));
    newnode->key = key;
    newnode->value = value;
    newnode->hash = hash;
    return newnode;
}

void listinsert(list *insertlist, node *toinsert)
{ // inserts a new item at the beginning
    toinsert->next = insertlist->head;
    toinsert->previous = insertlist->tail;
    insertlist->head = toinsert;
}

void listremove(list *curlist, node *toremove)
{ // remove a given node (use listsearch to find it)
    if (curlist->head == toremove) {
        curlist->head = toremove->next;
        curlist->head->previous = toremove->previous;
        free(toremove);
    } else {
        toremove->next->previous = toremove->previous;
        toremove->previous->next = toremove->next;
        free(toremove);
    }
}

node *listsearch(list *tosearch, char *key, char *value)
{
    node *iternode = tosearch->head;
    while (iternode != tosearch->tail) {
        if ((strcmp(iternode->key, key) == 0) && (strcmp(iternode->value, value) == 0)) {
            return iternode;
        } else {
            iternode = iternode->next;
        }
    }
    return tosearch->tail;
}

node *listkeysearch(list *tosearch, char *key)
{
    node *iternode = tosearch->head;
    while (iternode != tosearch->tail) {
        if (strcmp(iternode->key, key) == 0) {
            return iternode;
        } else {
            iternode = iternode->next;
        }
    }
    return tosearch->tail;
}

int empty(list *tocheck)
{
    if (tocheck->head == tocheck->tail)
        return 1;
    else
        return 0;
}

// debugging tools
void printlist(list *toprint)
{
    node *iternode = toprint->head;
    if (iternode == toprint->tail)
        printf("empty list!\n");
    while (iternode != toprint->tail) {
	printf("%s\t", iternode->key);
	printf("%s\n", iternode->value);
	iternode = iternode->next;
    }
}


