#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINES 24

typedef struct
{
	char name[256];
	char surname[256];
	char address[256];
	char zipcode[256];
	char town[256];
	char district[256];
	char phone[25];
}contact;

void addRecord();
void editRecord();
void deleteRecord();
void printOutput();
void writeOutput();
void printText();
void grep(char *,char *,size_t,size_t);
void findText();
bool showRecord(FILE *,int);
void copyFile(FILE *,FILE *,int);
void removeFile();
void inputline(char *,int,char='\n');
void inputData(contact *);

int main()
{
	
	int choice;
	
	while (true)
		{
			
			writeOutput();
			fflush(stdin);
			int _s = scanf("%d",&choice);
			if (_s != 1) {fflush(stdin); choice = 0;}

			switch(choice)
				{
					case 1:
						addRecord();
						break;
					case 2:
						editRecord();
						break;
					case 3:
						deleteRecord();
						break;
					case 4:
						printOutput();
						break;
					case 5:
						removeFile();
						break;
					case 6:
						printText();
						break;
					case 7:
						findText();
						break;
					default:
						printf("\nIncorrect choice\n");
						break;
				}
		
		} 

	return 0;
}



void writeOutput()
{

	
	printf("\n+----------------------------------+\n");
	printf("|\t1 Add a new record         |\n");
	printf("+----------------------------------+\n");
	printf("|\t2 Edit a record            |\n");
	printf("+----------------------------------+\n");
	printf("|\t3 Delete a record          |\n");
	printf("+----------------------------------+\n");
	printf("|\t4 Show all records         |\n");
	printf("+----------------------------------+\n");
	printf("|\t5 Delete file              |\n");
	printf("+----------------------------------+\n");
	printf("|\t6 Print report             |\n");
	printf("+----------------------------------+\n");
	printf("|\t7 Find text                |\n");
	printf("+----------------------------------+\n");
	printf("|\tEnd program: CTRL + C      |\n");
	printf("+----------------------------------+\n\n");
	printf("\tEnter your choice: "); 
	
}


void addRecord()
{
	
	FILE *in = fopen("contacts.dat","ab+");
	
	if (!in)
		{printf("\nImpossible to open file 'contacts'\n"); return;}
		
	
	contact tmp = {0,0,0,0,0,0,0};

	inputData(&tmp);	
	fwrite(&tmp,sizeof(contact),1,in);
	
	fclose(in);

}

void editRecord()
{
	
	FILE *in = fopen("contacts.dat","rb+");
	
	contact tmp = {0,0,0,0,0,0,0};
	int ID = 0;
	
	if (!in)
		{printf("\nImpossible to open file 'contacts'\n"); return;}
	
	printf("\nInsert the number of the record you want to edit: ");
	int _str = scanf("%d",&ID);
	
	if (_str != 1) {fflush(stdin); fclose(in); return;} 
	else 
		if (showRecord(in,ID))
			{
				fflush(stdin);
				fseek(in,sizeof(contact) * (ID-1),SEEK_SET); 
				int len = fread(&tmp,sizeof(contact),1,in); 
				if (len) inputData(&tmp);	

				fseek(in,sizeof(contact) * (ID-1),SEEK_SET); 
				fwrite(&tmp,sizeof(contact),1,in);
			}
		
	fclose(in);

}

void deleteRecord()
{

	FILE *in = fopen("contacts.dat","rb+");
	
	int ID = 0;
	
	if (!in)
		{printf("\nImpossible to open file 'contacts'\n"); return;}
	
	printf("\nInsert the number of the record you want to delete: ");
	int _str = scanf("%d",&ID);

	if (_str != 1) {fflush(stdin);  fclose(in); return;} 
	else 
		if (showRecord(in,ID))
			{	
				fflush(stdin);
				printf("\nDo you really want to delete this record? (y/n): ");
				char c = fgetc(stdin);

				if (tolower(c) != 'y') 
					{
						fflush(stdin); 
						fclose(in);
						return;
					} 
				else 
					{
						FILE *out = fopen("buffer.dat","wb+");
						if (!out) {printf("Impossible to remove record\n"); fclose(in); return;}
						copyFile(in,out,(ID-1));
						remove("contacts.dat");
						rename("buffer.dat","contacts.dat");
					}
			}
	
}

void printOutput()
{

	FILE *in = fopen("contacts.dat","rb");
	char ch = 'y';
	int id = 1;
	fflush(stdin);

	if (!in)
		{printf("\nImpossible to open file 'contacts'\n"); return;}
	else
		{printf("\n");}


	contact tmp;
	printf("%-5s\t%-20s\t%-30s\t%-45s\t%-10s\t%-30s\t%-30s\t%-20s\n","ID","Name","Surname","Address","Zip code","City","District","Phone");
	printf("%-5s\t%-20s\t%-30s\t%-45s\t%-10s\t%-30s\t%-30s\t%-20s\n","-----","--------------------","------------------------------","---------------------------------------------","----------","------------------------------","------------------------------","--------------------");

	while ((!feof(in)) && (tolower(ch) == 'y'))
		{
			if ((id % MAX_LINES) == 0)
					{
						printf("Do you want to continue? (y/n)\n");
						ch = getchar();
						if (tolower(ch)!= 'y')
							break;
					}
			size_t len = fread(&tmp,sizeof(contact),1,in);
			if (len) 
					{
						printf("%-5d\t%-20s\t%-30s\t%-45s\t%-10s\t%-30s\t%-30s\t%-20s\n",id++,tmp.name,tmp.surname,tmp.address,tmp.zipcode,tmp.town,tmp.district,tmp.phone); 
						printf("%-5s\t%-20s\t%-30s\t%-45s\t%-10s\t%-30s\t%-30s\t%-20s\n","-----","--------------------","------------------------------","---------------------------------------------","----------","------------------------------","------------------------------","--------------------");
					}

		}
	
	printf("\n"); 
	fclose(in);

}

void printText()
{

	FILE *in = fopen("contacts.dat","rb");
	FILE *out = 0;

	int id = 1;

	if (!in)
		{printf("\nImpossible to open source file\n"); return;}
	else
		out = fopen("print.txt","w");
	 
	contact tmp;
	fprintf(out,"%-5s\t%-20s\t%-30s\t%-45s\t%-10s\t%-30s\t%-30s\t%-20s\n","ID","Name","Surname","Address","Zip code","City","District","Phone");
	fprintf(out,"%-5s\t%-20s\t%-30s\t%-45s\t%-10s\t%-30s\t%-30s\t%-20s\n","-----","--------------------","------------------------------","---------------------------------------------","----------","------------------------------","------------------------------","--------------------");

	while (!feof(in	))
		{
			size_t len = fread(&tmp,sizeof(contact),1,in);
			if (len) 
					{
						fprintf(out,"%-5d\t%-20s\t%-30s\t%-45s\t%-10s\t%-30s\t%-30s\t%-20s\n",id++,tmp.name,tmp.surname,tmp.address,tmp.zipcode,tmp.town,tmp.district,tmp.phone); 	
						fprintf(out,"%-5s\t%-20s\t%-30s\t%-45s\t%-10s\t%-30s\t%-30s\t%-20s\n","-----","--------------------","------------------------------","---------------------------------------------","----------","------------------------------","------------------------------","--------------------");
					}
		}
	
		fclose(in);
		fclose(out);

}


void inputline(char *old,int n,char c)
{

	int j = 0;
	char *buf = (char *)malloc(n); //This is the buffer, where input data are temporarily stored.
	bool copying = false; //Are there in the buffer new data to be copied to the old buffer?
	char ch = getc(stdin);

	memset(buf,0,n);

	while (ch!=c)
		{
			//Input data
			if (j<n) buf[j++] = ch; 	
			ch = getc(stdin);
		}
	
	buf[j] = '\0'; //string terminator
		
	for (int k=0; k<n; k++)
		{
		//Is there any printable character in the buffer? (Let's skip white spaces)
			if ((isalnum(buf[k]))&&(isspace(buf[k])!=8))
				{
					copying = true;
					break;
				}
		}

	if (copying)
		{
			//If we have at least one printable character, we copy it to the old buffer.
			memset(old,0,n); 
			memcpy(old,buf,n);
		}

	free(buf); // Let's free allocated memory.
	
}

void copyFile(FILE *in,FILE *out,int skip)
{

	// copy all records from file 'in' to file 'out' but the one corresponding to 'skip' index

	contact tmp;
	int pos = 0;

	rewind(in);

	while (!feof(in))
		{
			if (pos++ == skip) fseek(in,sizeof(contact),SEEK_CUR);
			size_t len = fread(&tmp,sizeof(contact),1,in);
			if (len) fwrite(&tmp,sizeof(contact),1,out);
		}
	
		fclose(in);
		fclose(out);
}

void inputData(contact *tm)
{

	fflush(stdin);
	printf("\nInsert name: "); inputline(tm->name,256); fflush(stdin);
	printf("Insert surname: "); inputline(tm->surname,256); fflush(stdin);
	printf("Insert address: "); inputline(tm->address,256); fflush(stdin);
	printf("Insert zip code: "); inputline(tm->zipcode,256); fflush(stdin);
	printf("Insert town: "); inputline(tm->town,256); fflush(stdin);
	printf("Insert district: "); inputline(tm->district,256); fflush(stdin);
	printf("Insert phone: "); inputline(tm->phone,25);

}

bool showRecord(FILE *in,int n)
{	
	contact tmp;
	int len = 0;

	int pos = fseek(in,sizeof(contact) * (n-1),SEEK_SET); 
	if (pos == 0) 
		len = fread(&tmp,sizeof(contact),1,in);

	if (len) 
		{printf("\nThe record is:\n\nName: %-s\nSurname: %-s\nAddress: %-s\nZip code: %-s\nTown: %-s\nDistrict: %-s\nPhone: %-s\n",tmp.name,tmp.surname,tmp.address,tmp.zipcode,tmp.town,tmp.district,tmp.phone); rewind(in); return true;}
	else
		{printf("\nThere's no data in the record\n"); fclose(in);}
	
	return false;
}

void removeFile()
{	

	FILE *in = fopen("contacts.dat","rb");

	if (!in)
		{printf("\nFile cannot be accessed\n"); return;}
	else
		fclose(in);

	fflush(stdin);
	printf("\nDo you really want to remove file? (y/n): ");
	char ch = getc(stdin);

	if (tolower(ch) != 'y')
		fflush(stdin);
	else
		remove("contacts.dat");

}

void findText()
{
	
	FILE *in = fopen("contacts.dat","rb");
	size_t size = sizeof(contact);
	size_t id = 1;
	char buffer[255];
	memset(buffer,0,255);
	char ch = 'y';

	if (!in)
		{
			printf("\nImpossible to open file\n"); 
			return;
		}

	rewind(in);
	fflush(stdin);

	printf("%s\n","Insert a string to find");	
	gets(buffer);
	printf("\n"); 
	 
			while(!feof(in))
				{

					contact tmp = {0,0,0,0,0,0,0}; 
					size_t len = fread(&tmp,size,1,in); 
	
					if (len && strlen(buffer) && (tolower(ch) == 'y'))
							{
								if ((id % (MAX_LINES/2)) == 0)
									{
										printf("Do you want to continue? (y/n)");
										ch = getchar();
										if (tolower(ch) != 'y')
											break;
									}
								grep(buffer,(char *)&tmp,size,id);
								printf("\n");		
								id++; 
							}
					 					
				}
		 
	fflush(stdin);
	rewind(in);
	fclose(in);

}

void grep(char *sub, char *str, size_t len,size_t id)
{

	// This is a simple algorithm to search a substring within a string.
	// It's not very efficient.
	// A more sophisticated algorithm is Knutt-Morris-Pratt's algorithm,
	// but I've never studied it.
	// Some day I'll do.

	char *p, *p2, *start;

	
			for (size_t t=0; t<len; t++)
				{
					p = &str[t];
					start = p;
					p2 = sub;
					while (*p2 && (*p2 == *p))
						{
							++p; ++p2;
						}
					if (!*p2)
						printf("Record\t%d:\t%s\n",id,start);
				}
		

}
