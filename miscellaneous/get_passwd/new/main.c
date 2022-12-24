#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#include <time.h>

static char sem[] = {'A','B','C','D'};
static char special_chars[] = {'%','&','/','('};
static char special_nums[] = {'5','6','7','8'};

void get_passwd();
void rotateLetters(char *,int);
void printSem(char *,int);

int main(int argc, char *argv[])
{


  if (argc < 2)
   {
        printf("Usage: get_passwd <name>\n");
        exit(1);
    }
 

    if (strlen(argv[1])<4)
        {
            printf("Nome utente troppo breve\nDev'essere almeno 4 caratteri\n");
            exit(1);
        }
        
    get_passwd(argv[1]);
  

  return 0;
}


void rotateLetters(char *user, int num)
{
    
     char *p=user;
     char curr_char = 'z' - num;
     int l_counter = 0;
     
        while(*p && l_counter <4)
            {
                
                int remaining_chars = 'z' - *p;
                int offset = (num - remaining_chars)-1;
                  
                putchar(isalpha(*p)?tolower(*p)<=curr_char?tolower(*p+num):'a'+offset:*p);
                if (ferror(stdout))
                    {
                        printf("I/O error\n");
                        exit(1);
                    }
                
                p++;
                l_counter++;
                
            }    
}


void get_passwd(char *s)
{
  
  time_t seconds;

  int field_counter = 0; 
  char curr_date[256];
  char *tok = NULL;
/*
   strcpy(curr_date,ctime(&seconds));
    


   tok = strtok(curr_date, " ");
        
        
        while (tok != NULL && field_counter <1) {
            tok = strtok(NULL," ");
            field_counter++;
        }
  


  
    printf ("%s\n",curr_date);
    
    int isFirstSem = ((strcmp(tok,"Jan")==0 || strcmp(tok,"Gen")==0) || strcmp(tok,"Feb")==0  || strcmp(tok,"Mar")==0);
   int isSecondSem = (strcmp(tok,"Apr")==0 || (strcmp(tok,"May")==0 || strcmp(tok,"Mag")==0) || (strcmp(tok,"Jun")==0 || strcmp(tok,"Giu")==0));
   int isThirdSem = ((strcmp(tok,"Jul")==0 || strcmp(tok,"Lug")==0) || (strcmp(tok,"Aug")==0 || strcmp(tok,"Ago")==0) || (strcmp(tok,"Sep")==0 || strcmp(tok,"Set")==0));
   int isFourthSem = ((strcmp(tok,"Oct")==0 || strcmp(tok,"Ott")==0) || strcmp(tok,"Nov")==0 || (strcmp(tok,"Dec")==0 || strcmp(tok,"Dic")==0));

*/
  //  if ( isFirstSem )
        printSem(s,1);         
    
    /*
    else if ( isSecondSem )
         printSem(s,1);
    else if ( isThirdSem )
         printSem(s,1);
    else if ( isFourthSem )
         printSem(s,1);

 */

}

void printSem(char *u,int num)
{
    
     int p=num;
     
     putchar(sem[num-1]); 
     
     while (num--)
           putchar('I');
     
     putchar(special_nums[p-1]);      
     putchar(special_chars[p-1]);
     
     rotateLetters(u,p);

     
}
