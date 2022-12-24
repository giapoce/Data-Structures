#include "SkipList.h"
#include <string>

void writeOutput();
void CreateAndDestroyList();
void InsertListNode();
void DeleteListNode();
void RetrieveListNode();
void copyContructor();
void assignOperator();


List<string,int> L;

 
void writeOutput()
{
	
	cout << "1) Insert" << endl;
	cout << "2) Erase" << endl;
	cout << "3) Get a value" << endl;
	cout << "4) Copy constructor" << endl;
	cout << "5) Assign operator" << endl;	
	cout << "6) Destructor" << endl;	

}

 
void copyConstructor()
{
	List<string,int> cp(L);
	cout << "\t" << endl;
	cp.print();
	cout << "\t" << endl;
}

void assignOperator()
{
	List<string,int> cp;
	cp = L;
	cout << "\t" << endl;
	cp.print();
	cout << "\t" << endl;
}

void CreateAndDestroyList()
{
	
	cout << "\t" << endl;

	List<string,int> X;
	X.insert("A",1);
	X.insert("B",2);
    X.insert("C",3);

    L = X;
    L.print();
	cout << "\t" << endl;
}

void InsertListNode()
{
	
	string key;

	int value;

	cout << "\t" << endl;
	cout << "Insert a key-value pair" << endl;
	cout << "\t" << endl;
    
    cin.sync();
    cin >> key;
	cin >> value;
     
        
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	L.insert(key,value);
	
	cout << "\t" << endl;
	L.print(); 
	cout << "\t" << endl;
}

void DeleteListNode()
{
	
	string key;

	cout << "\t" << endl;
	cout << "Insert a value" << endl;
	cout << "\t" << endl;

	cin.sync();
    cin>>key;
     
    
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	L.erase(key);
	
	cout << "\t" << endl;
	L.print(); 
	cout << "\t" << endl;
}

void RetrieveListNode()
{

	string key;

	cout << "\t" << endl;
	cout << "Insert a value" << endl;
	cout << "\t" << endl;

	cin.sync();
    cin>>key;
    
    
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	ListNode<string,int> *x = L.getValue(key);
	
	cout << "\t" << endl;

	if (x)
		cout << "Value found: "<< x->data << endl;
	else
		cout << "Value not found" << endl;
	
	cout << "\t" << endl;

}

int main()
{

	int choice;
	
	for (;;)
		{
			writeOutput();
			cin.sync();
			cin >> choice;
			if (cin.fail()) {cin.clear(); cin.sync(); choice=0;}

			switch (choice)
				{
					case 1:
						InsertListNode();
						break;
					case 2:
						DeleteListNode();
						break;
					case 3:
						RetrieveListNode();
						break;
					case 4:
						copyConstructor();
						break;
					case 5:
						assignOperator();
						break;
					case 6:
						CreateAndDestroyList();	
						break;

				}
		}
	
  
	return 0;
}
