#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Copyright Giamarco Iapoce - gianmarcoiapoce@gmail.com - Matrix(Telcom Italia) Feb 2008

void _ERROR(char *m)
{
     printf("%s\n",m);
     exit(1);     
}

char *lowercase(char *s)
{
  char *cp;

  for (cp=s; *cp; ++cp)
    *cp=(char)tolower(*cp);
  return(s);
}


int my_memcmp(char *buf,char *str,size_t len)
{
  
     
     if (strchr(str,'(')!=NULL || strchr(str,')')!=NULL)
        return -1;
     
     if (strlen(str)<len)
        return -1; 
     
     char *p=strdup(buf);
     
     return memcmp(lowercase(p),lowercase(str),strlen(str));
    
     free(p);
}

void printEntry(FILE *fd)
{
     
     int p_cn=0;
     char ch;
           
         while(!feof(fd))
            {
                  
                  
                    ch=fgetc(fd);
                    if (ferror(fd))
                    _ERROR("I/O error");
                    
                    fputc(ch,stdout);
                    if (ferror(fd))
                    _ERROR("I/O error");
                    
                         
                    if (ch=='(')
                       p_cn++;
                    else if (ch==')')
                       p_cn--;
                     
                     
                     if ((ch == EOF && p_cn != 0))
                        _ERROR("Unbalanced parenthesis");
                     
                      
                     if(ch==')')
                       if (p_cn==0)
                          break;
                          
                                                  
            }     

}

int _getline(FILE *fd,char *buf,size_t len,char del)
{
     int j=0;
     char ch;
     
     while (j<len)
           {
            
             
             ch=fgetc(fd);
             if (ferror(fd))
                _ERROR("I/O error");
                
             if (ch == del || ch == EOF || ch == ' ' || ch == '=' || ch == ',') 
                break;   
                
             buf[j]=ch;     
             j++;
             
           }
           
           buf[j]='\0';
           return j;
}



 

int main(int argc, char *argv[])
{
   
    char buf[255];
    char ora_buf[255];
    char ch;
    char ch_c;
    
    int c=0;
    int found=0;
    
    memset(buf,0,255);
    
    
    if (argc<2)
       {
               printf("usage: tnsentry <db_entry>");
               exit(1);
        }
    
    
    char *p=getenv("ORACLE_HOME");
    
    if (!p)
       _ERROR("NO ORACLE_HOME");
    else
       strcpy(ora_buf,p);
    
    #ifdef WINDOWS
    
        char *s=strcat(ora_buf,"\\NETWORK\\ADMIN\\tnsnames.ora");
        
    #else
        
        char *s=strcat(ora_buf,"/NETWORK/ADMIN/tnsnames.ora");
    
    #endif
     
    FILE *in = fopen(s,"rw");
    
    
    if (!in)
       _ERROR("Cannot open file");
           
    while (!feof(in))
                {
                        
                                             
                        memset(buf,0,255);                           
                        int count=_getline(in,buf,255,'\n');
                        if (count)
					       c=my_memcmp(buf,argv[1],count);
                        
                        
                        if (!c)
                             {
                                fputs(buf,stdout);
                                if (ferror(in))
                                    _ERROR("I/O error\n");
                                    
                                printEntry(in);
                                printf("\n");
                                found=1; 
                                break;        
                             }       
                         
                }
                
                
    if (!found)
       printf("No such entry\n");
       
    return EXIT_SUCCESS;
    
}
