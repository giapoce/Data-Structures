#include "STree.h"
#include <string>
 
SplayTree<string> b;

void writeOutput();
void insertValue();
void insertRandom();
void retrieveNode();
void getParent();
void removeNode();
void copyConstructor();

 

int main()
{
	
	int choice;

		do 
		{
			writeOutput();
			cin.sync();
			cin >> choice;
			if (cin.fail()) {cin.clear();cin.sync(); choice=0;}
			switch(choice)
			{
			case 1:
				cout << "" << "\n";
				insertValue();
				cout << "" << "\n";
				break;
			case 2:
				cout << "" << "\n";
				retrieveNode();
				b.outputTree(cout);
				cout << "" << "\n";
				break;
			case 3:
				cout << "" << "\n";
				getParent();
				cout << "" << "\n";
				break;
			case 4:
				cout << "" << "\n";
				removeNode();
				cout << "" << "\n";
				break;
			case 5:
				cout << "" << "\n";
				insertRandom();
				cout << "" << "\n";
				break;
			case 6:
				cout << "" << "\n";
				copyConstructor();
				cout << "" << "\n";
				break;
			}
		} while(choice!=7);

    system("PAUSE");		
	return 0;
}


void writeOutput()
{
		cout << "Tree class demo" << "\n";
		cout << "1 insert node" << "\n";
		cout << "2 find node" << "\n";
		cout << "3 find parent node" << "\n";
		cout << "4 remove node" << "\n";;
		cout << "5 random insertion" << "\n";
		cout << "6 copyConstructor" << "\n";
		cout << "7 exit" << "\n";
		cout << "" << "\n";
}


void insertValue()
{
	string valueToAdd;

	cout << "Enter a value" << endl;

	cin>>valueToAdd;
	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	b.add(valueToAdd);
	b.outputTree(cout);

}


void insertRandom()
{
     /*
	int num;

	cout << "Enter a value" << endl;

	cin>>num;
	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	b.destroy();
	for (int i=1; i<=num; ++i)
		b.add(i +rand() %num);
	b.outputTree(cout);
*/
}

void retrieveNode()
{

	string value;
	SplayTree<string>::Node *temp;

	cout<<"Enter a value"<<"\n";
	cin>>value;
	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	temp = b.findNode(value);

	if (temp)
	{
		cout << "" << "\n";
		cout << "Value found: " << temp->data <<"\n";
		cout << "" << "\n";
	}
	else
	{
		cout << "" << "\n";
		cout << "Value not found" << "\n";
		cout << "" << "\n";
	}


}

void getParent()
{

	string valueToFind;

	cout << "Enter the value of a node in the tree" << endl;
	cin >> valueToFind;
	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	SplayTree<string>::Node *temp = b.findNode(valueToFind);

	if (temp != NULL && temp->parent)
			cout << temp->parent->data << endl;
	else
			cout << "Node not found or the node is the root" << endl;

}

void removeNode()
{

	string valueToRemove;

	cout << "Enter the value of a node in the tree" << endl;
	cin >> valueToRemove;
	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	b.remove(valueToRemove);
	b.outputTree(cout);
	
}

void copyConstructor()
{

	SplayTree<string> cp1(b);
	SplayTree<string> cp2;
	cp2=b;
	cp1.outputTree(cout);
	cp2.outputTree(cout);
}
