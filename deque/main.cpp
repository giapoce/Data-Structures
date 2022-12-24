#include "dik.h"
#include <string>
 
void traverseOn();
void traverseBack();
void jumpOn();
void jumpBack();
void iteratorPlus();
void iteratorMinus();
void writeOutput();
void removeItem();
void insert();
void insertRange();
void deleteRange();
void copyConstructor();
void addNewItem();


int size = 10;
_deque<string> v;

int main()
{
	
	int choice;

	 
		v.push_back("a");
		v.push_back("b");
		v.push_back("c");
		v.push_back("d");
		v.push_back("e");
		v.push_back("f");
		v.push_back("g");
		v.push_back("h");
		v.push_back("i");
		v.push_back("l");

	while(1)
	{
		 
		writeOutput();
		cin.sync();
		cin>>choice;
		if (cin.fail()) {cin.clear();cin.sync();choice=0;}
		switch(choice)
		{
			case 1:
				traverseOn();
				break;
			case 2:
				traverseBack();
				break;
			case 3:
				cout << "Number of items in the deque: " << v.size() <<"\n";
				cout << "Deque capacity: " << v.capacity() <<"\n";
			break;
			case 4:
				jumpOn();
			break;
			case 5:
				jumpBack();
			break;
			case 6:
				iteratorPlus();
			break;
			case 7:
				iteratorMinus();
			break;
			case 8:
				addNewItem();				
				traverseOn();
			break;	
			case 9:
				v.erase(v.begin());
				traverseOn();
			break;
			case 10:
				v.pop_back();
				traverseOn();
			break;
			case 11:
				removeItem();
				traverseOn();
			break;
			case 12:
				insert();
				traverseOn();
			break;
			case 13:
				insertRange();
				traverseOn();
			break;
			case 14:
				deleteRange();
				traverseOn();
			break;
			case 15:
				copyConstructor();
			break;
			 
			 
		}
	}
	


	return 0;
}

void writeOutput()
{

	cout << "\n" << "Vector class demo" <<"\n";
	cout << "1: iterate" <<"\n";
	cout << "2: iterate back" <<"\n";
	cout << "3: capacity - size" <<"\n";
	cout << "4: jump on" <<"\n";
	cout << "5: jump back" <<"\n";
	cout << "6: iterateAdd" <<"\n";
	cout << "7: iterateMinus" <<"\n";
	cout << "8: pushFront" <<"\n";
	cout << "9: popFront" <<"\n";
	cout << "10: popBack" <<"\n";
	cout << "11: remove" <<"\n";
	cout << "12: insert" <<"\n";
	cout << "13: insertRange" <<"\n";
	cout << "14: deleteRange" <<"\n";
	cout << "15: copy constructor" <<"\n";

}

 

void traverseOn()
{
	
	_deque<string>::_iterator a = v.begin();
	int counter = 1;

		while (a!=v.end())
		{
			cout << *a <<"\t";
			if ((counter+1)%10==0)
				cout <<"\n";
			++a;
		}
}

void traverseBack()
{
	
	_deque<string>::_iterator a = v.rbegin();
	int counter = 1;

		while (a!=v.rend())
		{
			cout << *a <<"\t";
			if ((counter+1)%10==0)
				cout <<"\n";
			--a;
		}
}

void jumpOn()
{

	_deque<string>::_iterator a = v.begin();
	int valueToAdd;
	
	cout << "Enter a value:" << "\n";
	cin >> valueToAdd;

	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	cout << *(a += valueToAdd) << "\n";
	
}


void jumpBack()
{

	_deque<string>::_iterator a = v.rbegin();
	int valueToAdd;
	
	cout << "Enter a value:" << "\n";
	cin >> valueToAdd;

	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	cout << *(a -= valueToAdd) <<"\n";
	
}

void iteratorPlus()
{

	_deque<string>::_iterator a = v.begin();
	int valueToAdd;
	
	cout << "Enter a value:" << "\n";
	cin >> valueToAdd;

	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	cout << *(a+valueToAdd) <<"\n";
	
}

void iteratorMinus()
{

	_deque<string>::_iterator a = v.rbegin();
	int valueToAdd;
	
	cout << "Enter a value:" << "\n";
	cin >> valueToAdd;

	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	cout << *(a-valueToAdd) <<"\n";
	
}


void removeItem()
{
	
	string valueToRemove;
     

    cin.sync();
	cout << "Enter a value:\n ";	
	cin>>valueToRemove;

	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	_deque<string>::_iterator a = v.find(v.begin(),v.end(),valueToRemove);
	v.erase(a);

}

void insert()
{
	
	string valueBeforeWhichInsert;
	string valueToInsert;
	 

	cout << "Enter the value in the vector before which you want to insert a new item\n ";
	cout << "and the value you want to insert:\n ";

 
	cin>>valueBeforeWhichInsert; 
    cin>>valueToInsert;

	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	_deque<string>::_iterator a = v.find(v.begin(),v.end(),valueBeforeWhichInsert);
	
	if (a!=v.end())
		v.insert(a,valueToInsert);
	else
		cout << "Value not found" << endl;

}

void insertRange()
{
	
	string valueBeforeWhichInsert ;
	string limit1 ; 
	string limit2 ;
	
	 

	cout << "Enter the position before which to insert the new values and limits of the range you want to insert\n ";

    cin.sync();
	cin>>valueBeforeWhichInsert;
    cin>>limit1;
    cin>>limit2;
	
	_deque<string> k(v);
	

	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	_deque<string>::_iterator a = v.find(v.begin(),v.end(),valueBeforeWhichInsert);
	_deque<string>::_iterator b = k.find(k.begin(),k.end(),limit1);
	_deque<string>::_iterator c = k.find(k.begin(),k.end(),limit2);

	if ((a!=v.end()) && (b!=v.end()))
		v.insert(a,b,c);
	else
		cout << "Values not found" << endl;

}

void deleteRange()
{
	
	string limit1; 
	string limit2;
	 
	cout << "Enter the limits of the range you want to delete\n ";
	
	cin.sync();

	cin>>limit1; 
	cin>>limit2;
	
	
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	_deque<string>::_iterator a = v.find(v.begin(),v.end(),limit1);
	_deque<string>::_iterator b = v.find(v.begin(),v.end(),limit2);
	

	if ((a!=v.end()) && (b!=v.end()))
		v.erase(a,b);
	else
		cout << "Values not found" << endl;

}

void addNewItem()
{
	 string newItem ;
 

	 cout << "Insert new item" << endl;
	
	 cin.sync();
	 cin>>newItem;

	 v.insert(v.begin(),newItem);

}

void copyConstructor()
{
	_deque<string> x;

	_deque<string> cp1(v);
	_deque<string> cp2;
	cp2 = v;

	_deque<string> cp3(x);
	_deque<string> cp4;
	cp4 = x;
 
  
	cout << cp1 << endl;
	cout << cp2 << endl;

	cout << cp3 << endl;
	cout << cp4 << endl;
 
 
}
