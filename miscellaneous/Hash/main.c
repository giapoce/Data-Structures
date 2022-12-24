#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A very basic implementation of an hash-map

#define NUMSLOT 911 // Best performances are achieved with prime numbers

#define EQ 0
#define LT -1
#define GT 1

typedef enum {KEY_NOT_FOUND=0, KEY_FOUND} KEY_EXISTS;  

typedef struct HashEntry {
    char *key;
    struct HashEntry *prev;
    struct HashEntry *next;
} Entry;

typedef Entry * EntryPtr;
EntryPtr HashTable[NUMSLOT];

int putEntry(char *);
int getEntry(char *);
int deleteEntry(char *);

long hashFunc(char *key) {

   unsigned long HASH_VAL=0;
      
	while(*key) {
		HASH_VAL = (HASH_VAL<<4) + *key++; 
		unsigned long g = HASH_VAL & 0xf0000000L; 
		if (g) {
			HASH_VAL^= g >> 24;
		} 
        HASH_VAL &= ~g;
	} 


    return (HASH_VAL%NUMSLOT);
    
}


int KeyCmp(char *p1,char *p2) {

    return strcmp(p1,p2);
    
}


int getEntry(char *key) {

     int bckt = hashFunc(key);
     EntryPtr curr = HashTable[bckt];
     KEY_EXISTS KE=KEY_NOT_FOUND;
     
     
     while (curr) {
                        
            if ( !strcmp(curr->key,key) ) {
                KE=KEY_FOUND;
                break;
            }
            else 
                curr=curr->next;
                
    }   
    
    return KE;
        
}

int putEntry(char *key) {

    //Sorted insertion
    
    KEY_EXISTS KV=getEntry(key);
    if ( KV == KEY_FOUND ) {
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
    
    et->key=(char *)malloc(strlen(key)+1);
    if (!(et)->key ) {
        printf("%s\n","Cannot fulfill your memory request");
        return 1;
    }
        
    memset((et)->key,0,strlen(key)+1);
    strcpy((et)->key,key);
    
    int bucket = hashFunc(key);
    EntryPtr first = HashTable[bucket];
    
    if (! first )   {
            HashTable[bucket] = et;
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
            HashTable[bucket] = et;            
            
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

int deleteEntry(char *key) {


   KEY_EXISTS KV=getEntry(key);
   if (KV==KEY_NOT_FOUND) {
        printf("%s\n","Key not found");
        return 1;
    }
    
    int bucket = hashFunc(key);
    EntryPtr first = HashTable[bucket];
         
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
            HashTable[bucket]=toDel->next;
            
            free(toDel->key);
            free(toDel);

}

void deleteHashChain() {

    int i;

    for (i = 0; i < NUMSLOT; ++i) 
    {
        EntryPtr cur = HashTable[i];
    
        while (cur) 
              {
                    EntryPtr next = cur->next;
                    free(cur->key);
                    free(cur);
                    cur = next;
              }
        
          HashTable[i] = NULL;
          
    }
      
}


void traverseHashChain() {

    int i;

    for (i = 0; i < NUMSLOT; ++i) 
    {
        EntryPtr cur = HashTable[i];
        EntryPtr last = NULL;
        
        if (!cur)
           continue;
           
        if (cur->key)
            printf("\nSlot: %d ",i);
        
        while (cur) {
                    if (cur->key)
                        printf("%s->",cur->key);
                        last = cur;
                    cur = cur->next;
                    
              }
              
        printf("\n\t");          
      
         while (last) {
                    if (last->key)
                        printf("%s->",last->key);
                    last = last->prev;
                    
              }
              

         printf("\n");
         printf("\n");  
          
          
      }
      
}

int main(int argc, char *argv[])
{

  char s;
  char Buf[80];
  int Res=-1;
  memset(HashTable,0,NUMSLOT);
  
   do {
        
        memset(Buf,0,80);      
        printf("\n%s","Type a command (i|d|g|t|q): ");
        scanf("%s",&s);
        
        switch(s) {
            case 'i':
                    printf("%s","Type a word: ");
                    scanf("%s",&Buf);                 
                    putEntry(Buf);
                break;
            case 'd':
                    printf("%s","Type a word: ");
                    scanf("%s",&Buf);
                    deleteEntry(Buf);
                break;
            case 'g':
                    printf("%s","Type a word: ");
                    scanf("%s",&Buf);
                    KEY_EXISTS KV=getEntry(Buf);                    
                    if (KV==KEY_NOT_FOUND)
                        printf("%s\n","Key not found");
                    else
                        printf("%s\n","Key found!!");
                break;
           case 't':
                  traverseHashChain();
                break;     
            default:
                if ( s != 'q' )
                    printf("Unkown command\n");
        }
        
        Res = ( s=='q' );

        
    } while ( Res != 1 );
    
  deleteHashChain();
    
  return 0;
  
}
