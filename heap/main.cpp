#include "heap.h"
#include <string>

void writeOutput();
void insertValue();
void removeValue();
void copyConstructor();

heap<string> h;
 
int main()
{

	int choice;
	
	while (1)
		{
			writeOutput();
			cin.sync();
			cin >> choice;
			if (cin.fail()) {cin.clear(); cin.sync(); choice = 0;}
			
			switch (choice)
				{
					case 1:
							cout << endl;
							insertValue();
							cout << endl;
					break;
					
					case 2:
							cout << endl;
							removeValue();
							cout << endl;
					break;

					case 3:
							cout << endl;
							copyConstructor();
							cout << endl;
					break;
				}
		}

     
	return 0;
}

void writeOutput()
{

	cout << "1) Insert a value" << endl;
	cout << "2) Remove a value" << endl;
	cout << "3) Copy constructor" << endl;
	
}

 

void insertValue()
{

	string buf;

	//int num;

	cout << "Insert a value" << endl;
	cin.sync();
	cin>>buf;
  
	h.push(buf);
	h.display();

}


void removeValue()
{
	
	h.remove();
	h.display();
		
}

void copyConstructor()
{
	heap<string> x(h);
	heap<string> y;
	y = h;
	x.display();
	y.display();
}

