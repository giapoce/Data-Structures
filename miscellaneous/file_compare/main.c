#include <stdio.h>
#include <stdlib.h>

//Copyright Gianmarco Iapoce - Zurich company

#define BUF_SIZE 1024

int file_comp(char *,char *);
int getline(FILE *fd,char *,char);

char buf1[BUF_SIZE];
char buf2[BUF_SIZE];

int main(int argc, char *argv[])
{
  
    memset(buf1,0,BUF_SIZE);
    memset(buf2,0,BUF_SIZE);
  
    if (argc<3)
       {
               printf("usage: file_cmp FILE1 FILE2\n");
               return 1;
        }
  
    file_comp(argv[1],argv[2]);
  
  system("PAUSE");	
  return 0;
  
}

int _getline(FILE *fd,char *buf,size_t len,char del)
{
     int j=0;
     char ch;

     while (j<len)
           {

             ch=fgetc(fd);
             if (ferror(fd))
                {
                    printf("I/O error\n");
                    return 1;
                }
                

             if (ch == del || ch == EOF)
                break;

             buf[j]=ch;
             j++;

           }

           buf[j]='\0';
           return j;
}                


int file_comp(char *f1,char *f2)
{
        
        int line_counter_1 = 0;
        int line_counter_2 = 0;
        
        FILE *fl1 =fopen(f1,"rb+");
            if (!fl1)
                {
                    printf("cannot open %s\n",f2);
                    return 1;
                }
                
        FILE *fl2 =fopen(f2,"rb+");
            if (!fl2)
                {
                    printf("cannot open %s\n",f2);
                    return 1;
                }
    
         
            
        while (!feof(fl1) && !feof(fl2))
            {
                        
                    _getline(fl1,buf1,BUF_SIZE,'\n');
                    _getline(fl2,buf2,BUF_SIZE,'\n');
                               
                    if (memcmp(buf1,buf2,1024) != 0)
                        {
                                printf("FILE 1 - line:%d\t%s\n",line_counter_1,buf1);
                                printf("FILE 2 - line:%d\t%s\n",line_counter_2,buf2);
                        }
                    
                    line_counter_1++;
                    line_counter_2++;
                     
                     memset(buf1,0,BUF_SIZE);
                     memset(buf2,0,BUF_SIZE);
                     
            }
            
                
                    
                             
            if (fclose(fl1)==EOF)
                printf("Error closing file\n");
                
            if (fclose(fl2)==EOF)
                printf("Error closing file\n");
                
            
}

