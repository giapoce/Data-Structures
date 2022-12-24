#include <stdio.h>
#include <stdlib.h>
 


void get_passwd(char *);


int main(int argc, char *argv[])
{
  
  /*if (argc < 2)
   {
        printf("Usage: get_passwd <name>\n");
        exit(1);
    }
    
  get_passwd(argv[1]);
  	*/
  	
  	 int start = 'a';
  	 int end = 'z';
  	 
  	 int ALPHA_SIZE = 24;

  	  int num = 4;
  	  int remaining_chars = (end - 'w') + 1;
  	  
  	  int offset = remaining_chars - num;
  	  
  	  
        printf("%d\n",offset);
  	  
  	  for (; start <= end; start++)
  	    printf("%d\t%c\n",(int)start,(char)start);
  	   
           
    system("PAUSE");
    
  return 0;
}


void get_passwd(char *user)
{
    
    char *p=user; 
    
    //Algoritmo rot13 modificato;
    
        while(*p)    
            {
                putchar(isalpha(*p)?tolower(*p)<'n'?tolower(*p+13):*p-13:*p);
                p++;
            }
            
        if (strlen(user) < 6)
            {
                char *s = user;
                while(*s)
                    {
                        putchar(isalpha(*s)?tolower(*s)<'q'?*s+10:tolower(*s-10):*s);
                        s++;
                    }   
            }             
            
           putchar(';');
                        
}

