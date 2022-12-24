#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
 


// A very simple database to store informations about personal contacts.
// This software allows you to add a new record, to edit or delete an existing one,
// to search for a match, to print a simple report showing all records.
// More sophisticated features will be added later.

namespace
{
	int MAX_LINES = 24;	
}

typedef struct
{
	char name[256];
	char surname[256];
	char address[256];
	char zipcode[256];
	char town[256];
	char district[256];
	char phone[256];
}contact;


using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;
using std::setw;
using std::setiosflags;

void addRecord();
void editRecord();
void deleteRecord();
void printOutput();
void writeOutput();
void printReport();
void findText();
void inputData(contact &);
void copyFile(fstream &, fstream &,int);
void removeFile();
void inputline(char *,int,char='\n');
bool showRecord(fstream &,int);
void grep(char *,char *,size_t,size_t);

int main()
{
	
	int choice;

	while (true)
		{
			
			writeOutput();
			cin.sync();
			cin >> choice;
			if (cin.fail()) {cin.clear(); cin.sync(); choice = 0;}

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
						printReport();
						break;
					case 6:
						removeFile();
						break;
					case 7:
						findText();
						break;
					default:
						cout << "\nIncorrect choice" << endl;
						break;
				}
		
		}

	return 0;
}



void writeOutput()
{
	
	cout << "\n1 Add a new record" << endl;
	cout << "2 Edit a record" << endl;
	cout << "3 Delete a record" << endl;
	cout << "4 Show all records" << endl;
	cout << "5 Print report" << endl;
	cout << "6 Remove file" << endl;
	cout << "7 Find text" << endl;
	cout << "End program: CTRL + C" << endl;
	cout << "\nEnter choice: ";
}


void addRecord()
{
	
	ofstream output("contacts.dat",ios::app|ios::binary);
	
	if (!output)
		{cout << "\nImpossible to open file" << endl; return;}
		
	contact tmp = {0,0,0,0,0,0,0};

	inputData(tmp);

	output.write((char *)&tmp,sizeof(contact));
	output.close();

}

void editRecord()
{
	
	fstream output("contacts.dat",ios::in|ios::out|ios::binary);
	contact tmp = {0,0,0,0,0,0,0};
	int ID = 0;
	
	if (!output)
		{cout << "\nImpossible to open file" << endl; return;}
	
	cout << "\nInsert the numeric identifier of the record you want to edit: ";
	cin >> ID;
	if (cin.fail()) {cin.clear(); cin.sync(); output.close(); return;} 
	else 
		if (showRecord(output,ID))
			{
				cin.sync();
				output.seekg(sizeof(contact) * (ID-1),ios::beg);
				output.read((char *)&tmp,sizeof(contact));
				inputData(tmp); 

				output.seekp(sizeof(contact) * (ID-1),ios::beg);
				output.write((char *)&tmp,sizeof(contact));
			}

	output.close();

}

void deleteRecord()
{

	fstream output("contacts.dat",ios::in|ios::out|ios::binary);
	int ID = 0;

	if (!output)
		{cout << "\nImpossible to open file" << endl; return;}
	
	cout << "\nInsert the numeric identifier of the record you want to delete: ";
	cin >> ID;
	if (cin.fail()) {cin.clear(); cin.sync(); output.close(); return;} 
	else 
		if (showRecord(output,ID))
			{
				cin.sync();
				cout << "\nDo you really want to delete this record? (y/n): ";
				char c = cin.get();

				if (( cin.fail() ) || ( tolower(c) != 'y' )) 
					{
						cin.clear();
						cin.sync(); 
						output.close();
						return;
					} 
				else 
					{
						fstream buf("buffer.dat",ios::out|ios::binary);
						copyFile(output,buf,(ID-1));
						remove("contacts.dat");
						rename("buffer.dat","contacts.dat");
					}
			}
		
}

void printOutput()
{

	ifstream input("contacts.dat",ios::in|ios::binary);
	int id = 1;
	char ch = 'y';
	cin.sync();

	if (!input)
		{cout << "\nImpossible to open file" << endl; return;}
		
	contact tmp;
	cout << endl; 
	cout << setiosflags(ios::left) << setw(5) << "ID" << setw(30) << "Name" << setw(30) << "Surname" << setw(45) << "Address" << setw(30) << "Zip code" << setw(30) << "City" << setw(30) << "District" << setw(30) << "Phone number" << endl;
	
	while (!input.eof() && (tolower(ch) == 'y'))
		{
			
            if ((id % MAX_LINES) == 0)
					{
						cout << "Do you want to continue? (y/n)" << endl;
						ch = getchar();
						if (tolower(ch) != 'y')
							break;
					}
			
            input.read((char *)&tmp,sizeof(contact));
			
			if (!input.eof()) 					
				cout << setiosflags(ios::left) << setw(5) << id++ << setw(30) << tmp.name << setw(30)  << tmp.surname << setw(45)  << tmp.address << setw(30)  << tmp.zipcode << setw(30) << tmp.town << setw(30) << tmp.district << setw(30) << tmp.phone << endl; 
					
		}

	cout << endl;
	input.close();
	
}

void printReport()
{

	ifstream input("contacts.dat",ios::in|ios::binary);
	ofstream output;

	int id = 1;

	if (!input)
		{cout << "\nImpossible to open source file" << endl; return;}
	else
		output.open("print.txt",ios::out);
		
	contact tmp;
	output << setiosflags(ios::left) << setw(5) << "ID" << setw(30) << "Name" << setw(30) << "Surname" << setw(45) << "Address" << setw(30) << "Zip code" << setw(30) << "City" << setw(30) << "District" << setw(30) << "Phone number" << endl;

	while (!input.eof())
		{
			input.read((char *)&tmp,sizeof(contact));
			if (!input.eof()) output << setiosflags(ios::left) << setw(5) << id++ << setw(30) << tmp.name << setw(30)  << tmp.surname << setw(45)  << tmp.address << setw(30)  << tmp.zipcode << setw(30) << tmp.town << setw(30) << tmp.district << setw(30) << tmp.phone << endl; 
		}


	input.close();
	output.close();

}


void inputline(char *old,int n,char c)
{

	int j = 0;
	char *buf = new char[n]; //This is the buffer, where input data are temporarily stored.
	bool copying = false; //Are there in the buffer new data to be copied to the old buffer?
	char ch = cin.get();

	memset(buf,0,n);

	while (ch!=c)
		{
			//Let's copy characters to the buffer
			if (j<n) buf[j++] = ch; //Let's check that buffer doesn't overflow	
			ch = cin.get();
		}

	buf[j] = '\0'; //Let's put an end to the string
		
	for (int k=0; k<n; k++)
		{
		//Is there any printable character in the buffer? 
			if ((isalnum (buf[k]))&&(isspace(buf[k])!=8)) 
				{
					copying = true;
					break;
				}
		}

	if (copying)
		{
		//If we have at least one printable character, let's copy it in the old buffer.
			memset(old,0,n); 
			memcpy(old,buf,n);
		}

	delete(buf); // Let's free allocated memory.
	
}

void copyFile(fstream &in, fstream &out,int skip)
{

	// copy all records from file 'in' to file 'out' but the one corresponding to 'skip' index

	contact tmp;
	int pos = 0;
	in.seekg(0,ios::beg);

	while (!in.eof())
		{
			if (pos++ == skip) in.seekg(sizeof(contact),ios::cur);
			in.read((char *)&tmp,sizeof(contact));
			if (!in.eof()) out.write((char *)&tmp,sizeof(contact));
		}

	in.close();
	out.close();

}

void inputData(contact &tm)
{

	cin.sync();
	cout << "\nInsert name: "; inputline(tm.name,256); cin.sync();
	cout << "Insert surname: "; inputline(tm.surname,256); cin.sync();
	cout << "Insert address: "; inputline(tm.address,256); cin.sync();
	cout << "Insert zip code: "; inputline(tm.zipcode,256); cin.sync();
	cout << "Insert town: "; inputline(tm.town,256); cin.sync();
	cout << "Insert district: "; inputline(tm.district,256); cin.sync();
	cout << "Insert phone: "; inputline(tm.phone,25);
}


bool showRecord(fstream &input,int ID)
{

	contact tmp;
	input.seekg(sizeof(contact) * (ID-1),ios::beg);
	input.read((char *)&tmp,sizeof(contact));
	
	if (input.gcount())
		{
			cout << "\nRecord is: \n" << endl;
			cout << setiosflags(ios::left) << "Name: " << tmp.name << endl; 
			cout << setiosflags(ios::left) << "Surname: " << tmp.surname << endl;
			cout << setiosflags(ios::left) << "Address: " << tmp.address << endl; 
			cout << setiosflags(ios::left) << "Zip code: " << tmp.zipcode << endl; 
			cout << setiosflags(ios::left) << "Town: " << tmp.town << endl; 
			cout << setiosflags(ios::left) << "District: " << tmp.district << endl; 
			cout << setiosflags(ios::left) << "Phone: " << tmp.phone  << endl; 
			input.seekg(0,ios::beg);
			return true;
		}
	else
		{cout << "\nThere' s no data in the record" << endl; input.close(); }

	return false;
}

void removeFile()
{	

	fstream f("contacts.dat");
	
	if (!f)
		{cout << "\nFile cannot be accessed" << endl; return;}
	else
		f.close();

	cin.sync();
	cout << "\nDo you really want to remove file? (y/n): ";
	char ch = cin.get();

	if ((tolower(ch) != 'y') || (cin.fail()))
		{cin.clear(); cin.sync();}
	else
		remove("contacts.dat");

}

void findText()
{
	 
	ifstream input("contacts.dat",ios::in|ios::binary);

	if (!input)
		{cout << "\nImpossible to open file" << endl; return;}

	size_t c_size = sizeof(contact);
	size_t id = 1;
	char buffer[255];
	memset(buffer,0,255);
	char ch = 'y';
	
	input.seekg(0,ios::beg);
	cin.sync();

	cout << "Insert a string to find" << endl;
	cin.getline(buffer,255);
	cout << endl;
	 
			while(!input.eof())
				{
					contact tmp = {0,0,0,0,0,0,0}; 
					input.read((char *)&tmp,c_size); 

					if (!input.eof() && strlen(buffer) && (tolower(ch) == 'y'))
						{
								if ((id % (MAX_LINES/2)) == 0)
									{
										cout << "Do you want to continue? (y/n)" << endl;
										ch = getchar();
										if (tolower(ch) != 'y')
											break;
									}
								
								grep(buffer,(char *)&tmp,c_size,id);		
								cout << endl;
								id++;
						}
					 					
				}
		 
	
	cin.sync();
	input.seekg(0,ios::beg);
	input.close();

}

void grep(char *sub, char *str, size_t len,size_t id)
{

	// This is a naive algorithm to search a substring within a string.
	// It's not very effective.
	// A more sophisticated algorithm is Knutt-Morris-Pratt's algorithm,
	// but I've never studied it.
	// Some day I'll do.

	char *p, *p2, *start;

	
			for (size_t t=0; t<len; t++)
				{
					p = &str[t];
					start = p;
					p2 = sub;
					while (*p2 && *p2 == *p)
						{
							++p; ++p2;
						}
					if (!*p2)
						cout << "Record " << id << ": " << start << endl;
				}
		


}
