#include <stdio.h>
#include <stdlib.h>

int count = 5;
char *args[] = {NULL,"uno","due","tre","quattro"};
    
void print_args(char *[]);
void print_str(char *);


int main(int argc, char *argv[])
{
    typedef char * STRING;

     STRING *p = args;
     
     //printf("%s\n",*(p+4));
       
       print_args(p);
       
    system("PAUSE");
    return EXIT_SUCCESS;

}


void print_str(char *s)
{
    while (*s)
        {
            printf("%c\t",*s);    
            s++;
        }
        
        printf("\n");
}


void print_args(char *a[])
{
    
    while (count > 1)
        {
            printf("%s\t",a[1]);
            count--;
            a++;
        }    
            printf("\n");

}
