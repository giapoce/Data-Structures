#include "SList.h"
#include <string>

void writeOutput();
void insertNode();
void traverse();
void traverseBack();
void removeNode();
void getNode();

m_list<string> l;
typedef m_list<string>::m_iterator i;
typedef m_list<string>::m_node n;

int main()
{

	int choice;

	while(true)
		{
			
			writeOutput();
			cin.sync();
			cin >> choice;
			if (cin.fail()) {cin.clear(); cin.sync(); choice=0;}

			switch(choice)
				{

					case 1:
						cout << " " << endl;
						insertNode();
						cout << " " << endl;
					break;
						
					case 2:
						cout << " " << endl;
						removeNode();
						cout << " " << endl;
					break;
						
					case 3:
						cout << " " << endl;
						getNode();
						cout << " " << endl;
					break;

					case 4:
						cout << " " << endl;
						traverseBack();
						cout << " " << endl;
					break;
				}
			
	
		}
	

	return 0;

}


void writeOutput()
{

	cout << "1) insert node " << endl;
	cout << "2) remove node " << endl;
	cout << "3) get node " << endl;
	cout << "4) traverse back" << endl;	
	cout << "Do your choice" << endl;

}


void insertNode()
{
	
	string x;

	cout << "Insert a value" << endl;
	cin >> x;
		
	l.push(x);

	traverse();

}


void removeNode()
{
	
	string x;

	cout << "Insert a value" << endl;
	cin >> x;

	l.erase(x);
	
	traverse();

}


void getNode()
{
	
	string value;

	cout << "Insert a value" << endl;
	cin >> value;
	 
	n *P = l.locate(value);

	if (P)
		cout << "Value found: " << P->data << endl;
	else
		cout << "Value not found" << endl;

}

void traverse()
{
	
	i x =  l.begin();
	i y =  l.end();

	while (x!=y)
		cout << *(x++) << endl;

}

void traverseBack()
{
	
	i x =  l.rbegin();
	i y =  l.rend();

	while (x!=y)
		cout << *(x--) << endl;

}
