#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int get_line(FILE *,char *,int,int);
char *str_tolower(char *);
void _ERROR(char *);
static char *usage = "usage: grep [-in] <file> <pattern>";

void _ERROR(char *m)
{
     printf("%s\n",m);
     exit(1);     
}

int get_line(FILE *std,char buff[],int del,int count)
{

    int i=0;
    char c;

    while (i<count && (c=fgetc(std))!=del)
        {
            if (ferror(std))
                _ERROR("Cannot open file");    
                
                
            buff[i]=c;
            i++;
        }

    buff[i]='\0';
    return i;

}

char *str_tolower(char *s)
{
  char *cp;

  for (cp=s; *cp; ++cp)
    *cp=(char)tolower(*cp);
  
  return(s);
  
}

main(int argc, char *argv[])
{


  char buffer[BUFFER_SIZE];
  int i;
  char c;
  int ign_case=0;
  int cnt_line=0;
  
  while (argc > 1 && argv[1][0] == '-')
    {

		 for( i=1; (c=argv[1][i]) != '\0'; i++ )
			  {

				switch(argv[1][i]) {
					case 'i':
						ign_case=1;
					break;
					case 'n':
						cnt_line=1;
					break;
					default:
						printf("unknown option \n");
					break;
				}

               }

            argc--;
            argv++;

    }


        if (argc>2)
            {
                
                int j;
                int n = 0;
                
                        FILE *in=fopen(argv[1],"r");

                        if (!in)
                            _ERROR("Cannot open file");
                        
    
                                    
                        while ( !feof(in) )
                            {
                                 n++;   
                                 int cnt=get_line(in,buffer,'\n',BUFFER_SIZE);
                                    
                                  if (cnt>0)
                                    {
                                        char *a=NULL;
                                        char *b=NULL;
                                        
                                        if (ign_case)
                                            {
                                                a=str_tolower(strdup(buffer));
                                                b=str_tolower(strdup(argv[2]));
                                            }
                                        
                                          if (strstr(ign_case?a:buffer,ign_case?b:argv[2]))
                                                if (cnt_line)
                                                    printf("file: %s\tline:%d\t%s\n",argv[1],n,buffer);
                                                else
                                                    printf("file: %s\t%s\n",argv[1],buffer);
                                            
                                            if (a) {free(a);}
                                            if (b) {free(b);}
                                            
                                    }
                                             
                                    memset(buffer,0,BUFFER_SIZE);

                            }
                        
                        
                        fclose(in);
                            
                        
                }
                else
                    printf("%s\n",usage);


}
