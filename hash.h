#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A very basic implementation of an hash-map

#define EQ 0
#define LT -1
#define GT 1

typedef enum {KEY_NOT_FOUND=0, KEY_FOUND} KEY_EXISTS;

typedef struct HashEntry {
    char *key;
    char *data;
    struct HashEntry *prev;
    struct HashEntry *next;
} Entry;

typedef Entry *EntryPtr;
typedef EntryPtr *HtPtr;

typedef struct HashTable {
    long size;
    HtPtr ht;
} Map;

typedef Map *MapPtr;

long hashFunc(MapPtr HashMap,char *key) {

   unsigned long HASH_VAL=0;

        while(*key) {
                HASH_VAL = (HASH_VAL<<4) + *key++;
                unsigned long g = HASH_VAL & 0xf0000000L;
                if (g) {
                        HASH_VAL^= g >> 24;
                }
        HASH_VAL &= ~g;
        }


    return (HASH_VAL%(HashMap->size));

}


int KeyCmp(char *p1,char *p2) {

    return strcmp(p1,p2);

}


char *getEntry(MapPtr HashMap,char *key) {

     int bckt = hashFunc(HashMap,key);
     EntryPtr curr = (EntryPtr)HashMap->ht[bckt];


     while (curr) {

            if ( !strcmp(curr->key,key) ) {
                return curr->data;
            }
            else
                curr=curr->next;

    }

    return NULL;

}

int putEntry(MapPtr HashMap,char *key,char *data) {

    //Sorted insertion

    char *s=getEntry(HashMap,key);
    if ( s ) {
        printf("%s\n","Key alreay in map");
        return 1;
    }

    EntryPtr et = (EntryPtr)malloc(sizeof(Entry));
    if (!et) {
        printf("%s\n","Cannot allocate memory to fit your request");
        return 1;
    }

    et->next=et->prev=(EntryPtr)NULL;
    et->key=(char *)NULL;

    et->key=strdup(key);
    if (!(et)->key ) {
        printf("%s\n","Cannot fulfill your memory request");
        return 1;
    }

    et->data=strdup(data);
    if (!(et)->data ) {
        printf("%s\n","Cannot fulfill your memory request");
        return 1;
    }

    int bucket = hashFunc(HashMap,key);
    EntryPtr first = (EntryPtr)HashMap->ht[bucket];

    if (! first )   {
            HashMap->ht[bucket]=(EntryPtr)et;
            return 0;
    }

     EntryPtr curr = first;
     EntryPtr prev = curr->prev;

     while (curr && KeyCmp(key,curr->key)==GT) {

            prev = curr;
            curr=curr->next;

     }

     if ( ! prev ) {

            et->next = first;
            first->prev = et;
            HashMap->ht[bucket]=(EntryPtr)et;

        } else {

            et->next = curr;

                        if (curr)
               curr->prev = et;
                        if (prev)
                prev->next = et;

                        et->prev = prev;

    }





    return 0;

}

int deleteEntry(MapPtr HashMap,char *key) {


   char *s=getEntry(HashMap,key);
   if (!s) {
        printf("%s\n","Key not found");
        return 1;
    }

    int bucket = hashFunc(HashMap,key);
    EntryPtr first = (EntryPtr)HashMap->ht[bucket];

        EntryPtr curr = first;
        EntryPtr prev = curr->prev;
        EntryPtr toDel = NULL;

        while (curr) {

            if (!strcmp(curr->key,key)) {

                toDel = curr;

                if (curr->next)
                    curr->next->prev = prev;
                if (prev)
                    prev->next = curr->next;
                break;

            }

            prev = curr;
            curr=curr->next;

        }

        if (! toDel->prev )
            HashMap->ht[bucket]=(EntryPtr)(toDel->next);

            free(toDel->key);
            free(toDel->data);
            free(toDel);

}

void deleteHashChain(MapPtr HashMap) {

    int i;

    for (i = 0; i < HashMap->size; ++i)
    {
        EntryPtr cur = (EntryPtr)HashMap->ht[i];

        while (cur)
              {
                    EntryPtr next = cur->next;

                    free(cur->key);
                    free(cur->data);

                    free(cur);
                    cur = next;

              }

          HashMap->ht[i] = NULL;

    }

    free(HashMap->ht);
    HashMap->ht=NULL;

}


void traverseHashChain(MapPtr HashMap) {

    int i;

    for (i = 0; i < HashMap->size; ++i)
    {
        EntryPtr cur = (EntryPtr)HashMap->ht[i];
        EntryPtr last = NULL;

        if (!cur)
           continue;

        if (cur->key)
            printf("\nSlot: %d ",i);

        while (cur) {
                    if (cur->key)
                        printf("%s->%s",cur->key,cur->data);
                        last = cur;
                        cur = cur->next;

              }


         printf("\n");


      }

}

int createHt(MapPtr *HashMap,long sz) {

  *HashMap=(MapPtr)malloc(sizeof(Map));
  if (!*HashMap) {
        printf("%s\n","Cannot allocate memory");
        return -1;
  }

  (*HashMap)->size=sz;
  (*HashMap)->ht=(HtPtr)malloc(sizeof(EntryPtr)*sz);
  if (!(*HashMap)->ht) {
        printf("%s\n","Cannot allocate memory");
        return -1;
  }

  memset((*HashMap)->ht,0,sz);
  return 0;

}

int destroyHt(MapPtr *HashMap) {

 deleteHashChain(*HashMap);
 free(*HashMap);

 return 0;

}
