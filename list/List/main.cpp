#include "dblist.h"
#include <string>

void writeoutput();
void TraverseList();
void TraverseListBack();
void insertRange();
void FindValue();
void removeItem();
void insertItem();
void push_back();
void push_front();
void deleteRng();
void CopyConstructor();

_list<string> _l;
typedef _list<string>::_iterator _i_;

int main()
{

	int choice;

	do 
	{
		writeoutput();
		cin.sync();
		cin>>choice;
		if (cin.fail()) {cin.clear();cin.sync(); choice=0;}
		switch(choice)
		{
		case 1:
			cout<<""<<"\n";
			push_back();
			cout << _l << endl;
			cout<<""<<"\n";
			break;
		case 2:
			cout<<""<<"\n";
			_l.pop_back();
			cout << _l << endl;
			cout<<""<<"\n";
			break;
		case 3:
			cout<<""<<"\n";
			push_front();
			cout << _l << endl;
			cout<<""<<"\n";
			 
			break;
		case 4:
			cout<<""<<"\n";
			_l.pop_front();
			cout << _l << endl;
			cout<<""<<"\n";
			break;
		case 5:
			cout<<""<<"\n";
			removeItem();
			cout << _l << endl;
			cout<<""<<"\n";
			break;
		case 6:
			cout<<""<<"\n";
			insertItem();
			cout << _l << endl;
			cout<<""<<"\n";
			break;
		case 7:
			cout<<""<<"\n";
			TraverseList();
			cout<<""<<"\n";
			break;
		case 8:
			cout<<""<<"\n";
			TraverseListBack();
			cout<<""<<"\n";
			break;
		case 9:
			cout<<""<<"\n";
			FindValue();
			cout<<""<<"\n";
		break;
		case 10:
			cout<<""<<"\n";
			deleteRng();
			cout << _l << endl;			
			cout<<""<<"\n";
		break;
		case 11:
			cout<<""<<"\n";
			insertRange();
			cout << _l << endl;
			cout<<""<<"\n";
		break;
		case 12:
			cout<<""<<"\n";
			_l.clear();
			cout<<""<<"\n";
		break;
		case 13:
			cout<<""<<"\n";
			cout << _l.size() <<endl;
			cout<<""<<"\n";
		break;
		case 14:
			cout<<""<<"\n";
			CopyConstructor();
			cout<<""<<"\n";
		break;
		}
	} while(choice!=15);
	

return 0;

}

void TraverseList()
{

	if (_l.isEmpty())
		return;

		_i_ s = _l.begin();
		int num = 1;
		
		while (s!=_l.end())
			{	
				cout << *s <<"\t";
				if ((num+1)%10==0)
					cout << "\n";
				s++;		
			}
			
}

void TraverseListBack()
{

	if (_l.isEmpty())
		return;

		_i_ s = _l.rbegin();
		int num = 1;
			
			while (s!=_l.rend())
			{
				cout << *s << "\t";
				if ((num+1)%10==0)
				cout << "\n";		
				s--;
			}
				
}

void writeoutput()
{
	cout<<"List class demo"<<"\n";
	cout<<"1: pushBack"<<"\n";
	cout<<"2: popBack"<<"\n";
	cout<<"3: pushFront"<<"\n";
	cout<<"4: popFront"<<"\n";
	cout<<"5: remove"<<"\n";
	cout<<"6: insert"<<"\n";
	cout<<"7: iterate"<<"\n";
	cout<<"8: iterate back"<<"\n";
	cout<<"9: find"<<"\n";
	cout<<"10: deleteRange"<<"\n";
	cout<<"11: insertRange"<<"\n";
	cout<<"12: clear"<<"\n";
	cout<<"13: size"<<"\n";
	cout<<"14: copy constructor"<<"\n";
	cout<<"15: exit"<<"\n";
	cout<<"Enter a value between 1 and 14"<<"\n";
}

void FindValue()
{
	
	if (_l.isEmpty())
		return;

	string val;
	_i_ result;
	_i_ a = _l.begin();
	_i_ b = _l.end();

	cout << "Enter a value:" << "\n";
	cin >> val;
	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	result= _l.find(a,b,val);
	
	if (result!=_l.end())
		cout << "Value found: "<< *result <<"\n";
	else
		cout << "Value not found" << "\n";

}


void removeItem()
{

	if (_l.isEmpty())
		return;

	string value;

	cout << "Enter a value" <<"\n";
	cin >> value;
	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	_i_ pos = _l.find(_l.begin(),_l.end(),value);  
	if (pos!=_l.end()) _l.erase(pos);

}

void push_back()
{
     
	string value;
	 
	cout<<"Enter a value" << endl;
	 
	cin>>value;
    _l.push_back(value);
	  
}

void push_front()
{
     
	string value;
	 
	cout<<"Enter a value" << endl;
	 
	cin>>value;
    _l.push_front(value);
    
 
}

void insertItem()
{

	if (_l.isEmpty())
		return;

	string value1;
    string value2;
	_i_ a = _l.begin();
	_i_ b = _l.end();
	_i_ result;

	cout<<"Enter the value in the list before which you want to insert a new item "<<"\n";
	cout<<"and the value of the new item you want to insert: "<<"\n";

	cin>>value1>>value2;
	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	result = _l.find(a,b,value1);

	if (result!=_l.end())
		_l.insert(result,value2);
	else
		cout<< value1 <<" not found"<< "\n";

}


void insertRange()
{


	string value1;
    string value2;
	_i_ result1;
	_i_ result2;
 
	cout<<"Enter the starting and the end value of the range you want to insert: \n";
	
	cin>>value1>>value2;
	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	result1 = _l.find(_l.begin(),_l.end(),value1);
	result2 = _l.find(_l.begin(),_l.end(),value2);

	if ((result1!=_l.end())&&(result2!=_l.end()))
		_l.insert(_l.begin(),result1,result2);
	else
		cout<< "Values not found"<< "\n";

}


void deleteRng()
{

	if (_l.isEmpty())
		return;

	string value1;
    string value2;
	_i_ result1;
	_i_ result2;

	cout<<"Enter the starting and the end value of the range you want to delete: \n";
	
	cin>>value1>>value2;
	if (cin.fail()) {cin.clear(); cin.sync(); return;}
	result1 = _l.find(_l.begin(),_l.end(),value1);
	result2 = _l.find(_l.begin(),_l.end(),value2);

	if ((result1!=_l.end())&&(result2!=_l.end()))
		_l.erase(result1,result2);
	else
		cout<< "Values not found"<< "\n";

}


void CopyConstructor()
{
	
	_list<string> cp1(_l);
	_list<string> cp2;
	cp2 = _l;

	_i_ S = cp1.begin();
	_i_ E = cp1.end();
	
	_i_ I = cp2.begin();
	_i_ F = cp2.end();

	while (S != E)
		cout << *S++ << endl;

	while (I != F)
		cout << *I++ << endl;

}
