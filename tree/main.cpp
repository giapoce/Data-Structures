#include "BTree.h"
#include <string>
BinaryTree<string> b;

void writeOutput();
void insertValue();
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
			if (cin.fail()) {cin.clear(); cin.sync(); choice=0;}
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
				b.traverseTreeDescending();
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
				b.traverseTreeAscending();
				cout << "" << "\n";
				break;
			case 6:
				cout << "" << "\n";
				b.traverseTreeDescending();
				cout << "" << "\n";
				break;
			case 7:
				cout << "" << "\n";
				b.outputTree(cout);
				cout << "" << "\n";
				break;
			case 8:
				cout << "" << "\n";
				copyConstructor();
				cout << "" << "\n";
				break;
			}
		} while(choice!=9);

 
    	
	return 0;
}


void writeOutput()
{
		cout << "Tree class demo" << "\n";
		cout << "1 insert node" << "\n";
		cout << "2 find node" << "\n";
		cout << "3 find parent node" << "\n";
		cout << "4 remove node" << "\n";
		cout << "5 traverse ascending" << "\n";
		cout << "6 traverse descending" << "\n";
		cout << "7 outputTree" << "\n";
		cout << "8 copyConstructor" << "\n";
		cout << "9 exit" << "\n";
		cout << "" << "\n";
}

void insertValue()
{
	string valueToAdd;
    
    cin.sync(); 
	cout << "Enter a value" << endl;
	cin >> valueToAdd;

     
	 
	b.add(valueToAdd);
	b.outputTree(cout);

}

void retrieveNode()
{

	string value;

    cin.sync(); 
	cout << "Enter a value" << endl;
	cin>>value;
 	
	BinaryTree<string>::Node *temp;
	
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
 
     cin.sync();
	cout << "Enter a value" << endl;
	cin>>valueToFind;

	
	 
	BinaryTree<string>::Node *temp = b.findNode(valueToFind);

	if (temp && temp->parent)
		{
			cout << temp->parent->data << endl;
		}
	else
		cout << "Node not found or the node is the root" << endl;

}

void removeNode()
{

	string valueToRemove;
 
    cin.sync();
	cout << "Enter a value" << endl;
	cin>>valueToRemove;
 
	
	 
	b.remove(valueToRemove);
	b.outputTree(cout);
	
}

void copyConstructor()
{

	BinaryTree<string > cp1(b);
	BinaryTree<string > cp2;
	cp2=b;
	cp1.outputTree(cout);
	cp2.outputTree(cout);
}

