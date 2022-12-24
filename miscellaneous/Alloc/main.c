#include <stdio.h>
#include <stdlib.h>

struct memCell {
    char *baseAddress;
};

struct memCell nd;

char *getMemoryPool(char **addr,char *str) {

     printf("sssb%p\n",addr);
     printf("sssb%p\n",*addr);
  
    if (*addr) {
         printf("%s\n","Deallocating");
         free(*addr);
         *addr=NULL;
    }
    
    *addr=(char *)malloc(strlen(str)+1);
    if (!*addr) {
        printf("s\n","Cannot allocate");
        return (char *)NULL;    
    }
    
    printf("sssa%p\n",addr);
    printf("sssa%p\n",*addr);
    strcpy(*addr,str);
     
    return *addr;
}

int main(int argc, char *argv[])
{
  
  printf("%p\n",&nd.baseAddress);
  printf("%p\n",nd.baseAddress);
  
  char *s=getMemoryPool(&nd.baseAddress,"gigi");
  printf("%p\t%s\n",s,s);
  printf("%p\n",&s);
  printf("%p\n",&s[0]);
  printf("%p\n",&nd.baseAddress);
  printf("%p\n",nd.baseAddress);
  printf("%d\n",strcmp(s,nd.baseAddress));
  
  s=getMemoryPool(&nd.baseAddress,"ugo");
  printf("%p\t%s\n",s,s);
  printf("%p\n",&s);
  printf("%p\n",&s[0]);
  printf("%p\n",&nd.baseAddress);
  printf("%p\n",nd.baseAddress);
  printf("%d\n",strcmp(s,nd.baseAddress));
  
  free(nd.baseAddress);
  
  system("PAUSE");	
  return 0;
}
