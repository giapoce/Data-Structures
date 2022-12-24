#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10


int myArr[ARRAY_SIZE];
int countInserted=0;


int orderedInsert(int arr[],int val) {
    
    if (countInserted==ARRAY_SIZE) {
        printf("%s\n","Array is full");
        return 1;
    }
    
    int i=0;
    int j=countInserted;
    int duplicateFound=0;
    
    //Se la matrice è vuota, inserisco nella prima posizione ed esco
    if (!countInserted) {
        arr[0]=val;
        countInserted++;
        return 0;
    }
    
    //Cerco il punto di inserimento
    while (val>arr[i] && i<countInserted)
            i++;
    
    //Ho trovato un duplicato
    if (arr[i]==val) {
            printf("%s\n","Duplicate found!!");
            duplicateFound=1;
    }
        
    //Sposto tutti gli altri elementi se non ho trovato un duplicato
    if (!duplicateFound) {
        
        for (;j>i;j--)
            arr[j]=arr[j-1];    
            
        //Inserisco
        arr[i]=val;
        countInserted++;
        
    }

    return 0;
    
}

int printArray(int arr[]) {
    
    int i;
    
    for (i=0; i<ARRAY_SIZE; i++) 
        printf("%d\t",arr[i]);
}

int main(int argc, char *argv[])
{
  
  memset(myArr,0,ARRAY_SIZE*sizeof(int));
  int num;
  
  while (1) {
        
        printf("%s: ","Insert a number");
        int s=scanf("%d",&num);
        if (s!=1) {
            printf("%s\n","Bad input");
            fflush(stdin);
            continue;
        }
     
        orderedInsert(myArr,num);
        printArray(myArr);
        
    }
    
  getchar();	
  return 0;
  
}
