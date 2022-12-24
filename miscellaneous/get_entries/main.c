#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512

void _ERROR(char *m)
{
     printf("%s\n",m);
     exit(1);     
}

int get_line(FILE *std,char buff[],int del,int count)
{

    int i=0;
    char c;

    while (!feof(std) && i<count)
        {
            c=fgetc(std);
            if (ferror(std))
                    _ERROR("I/O ERROR\n");

            if (c==del || c == EOF)
		break;

            buff[i]=c;
            i++;
        }

    buff[i]='\0';
    return i;

}

char * trim(char *s)
{
    
	 
	int i=0,j;
	while((s[i]==' ')||(s[i]=='\t')) {
		i++;
	}
	
	if(i>0) {
		for(j=0;j<strlen(s);j++) {
			s[j]=s[j+i];
		}
	s[j]='\0';
	}

 
	i=strlen(s)-1;
	
	while((s[i]==' ')||(s[i]=='\t')) {
		i--;
	}
	
	if(i<(strlen(s)-1)) {
		s[i+1]='\0';
	}
	
	return s;
}


void skipComments(FILE *in,FILE *out)
{
    
    char buffer[BUFFER_SIZE];
    memset(buffer,0,BUFFER_SIZE);
    
        while (!feof(in))
            {
                
                    int count=get_line(in,buffer,'\n',BUFFER_SIZE);
                    
                    if (count)
                        if (!strchr(buffer,'#'))
                            if (fputs(buffer,out)<0)
                                _ERROR("I/O ERROR");
                        
            }
            
            fclose(in);
            rewind(out);
            
}

int getEntry(FILE *fd,char *buf,size_t len)
{
     int j=0;
     int p_cn=0;
     char ch;
           
         while(j<len && !feof(fd))
            {
                     
                    ch=fgetc(fd);
                    if (ferror(fd))
                    _ERROR("I/O error");

                       if (ch == EOF)
			break;
 
                            buf[j]=ch;
                            j++;   

                    if (ch=='(')
                       p_cn++;
                    else if (ch==')')
                       p_cn--;
                     
                     if ((ch == EOF && p_cn != 0))
                        _ERROR("Unbalanced parenthesis");
                    

                    if  ( strchr(buf,'(') || strchr(buf,')') )     
                        if (p_cn==0)
                            break;
                          
                                                     
            }     

           
           buf[j]='\0';
           return j;
}


int main(int argc, char *argv[])
{
  
    char buf[BUFFER_SIZE];
    char ora_buf[255];
    int p_count=0;

    memset(buf,0,BUFFER_SIZE);    
    char *p=getenv("ORACLE_HOME");
 
    if (!p)
       _ERROR("NO ORACLE_HOME");
    else
       strcpy(ora_buf,p);

#ifdef WINDOWS 
    
    char *s=strcat(ora_buf,"\\NETWORK\\ADMIN\\tnsnames.ora");
    char *tmp= strcat(p,"\\NETWORK\\ADMIN\\tnsnames.tmp");

#else

    char *s=strcat(ora_buf,"/NETWORK/ADMIN/tnsnames.ora");
    char *tmp= strcat(p,"/NETWORK/ADMIN/tnsnames.tmp");

#endif
    
    FILE *in = fopen(s,"r");
    if (!in)
       _ERROR("Cannot open input file");
    
    FILE *out = fopen(tmp,"w+");
    if (!out)
       _ERROR("Cannot open temporary file");
       
    skipComments(in,out);
    
        while (!feof(out))
                {
                    
                                           
                     int count=getEntry(out,buf,BUFFER_SIZE);    
                     if (count) 
                      {
                                                 
                                char *q=strtok(buf,"=");
                                        if (q)         
                                                printf("%s\n",trim(q));
                                                
                                   
                       }
                       
                        memset(buf,0,BUFFER_SIZE);
                        
                }
       
    fclose(out);    
    remove(tmp);
    return EXIT_SUCCESS;
    
  
}
