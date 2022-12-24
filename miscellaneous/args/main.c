#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

int i;
char c;

 while (argc > 1 && argv[1][0] == '-')
    {
         
		 for( i=1; (c=argv[1][i]) != '\0'; i++ )
			  {
				
				switch(argv[1][i]) {
					case 's':
						printf("option s\n");
					break;
					case 'r':
						printf("option r\n");
					break;
					case 'n':
						printf("option n\n");
					break;
					default:
						printf("unknown option \n");
					break;
				}
				
	}
			
            argc--;
            argv++;
            printf("%s\n",argv[1]);

    }
    
        if (argc>1)
            {
                printf("remaining arguments\n");
                for(i=1; i<argc; i++)
                    printf("%s\t",argv[i]);
                    printf("\n");
            }
        
        
  system("PAUSE");	
  return 0;
}
