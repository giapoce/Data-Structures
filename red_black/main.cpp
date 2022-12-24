#include "rbtree.h"
#include <string>

void _putKey();
void _delKey();
void _getKey();
void _copyConstructor();
void _write_output();
void _clear_input(istream &);

_xtree<string> _x;

int main()
{
  
	int _choice = 0;
	 
	 while (1)
		{
			_write_output();
			cin.sync();
			cin >> _choice;
			if (cin.fail())
					{
						_clear_input(cin);		  
						_choice = 0;
					}
			switch(_choice)
				{
					case 1:
						_putKey();
					break;
					case 2:
						_delKey();
					break;
					case 3:
						_getKey();
					break;
					case 4:
						_copyConstructor();
					break;
					default:
						cout << "Incorrect choice" << endl << endl;
					break;
				}
			 		
		}

	 
		 
	return 0;
}



void _clear_input(istream &_I)
{
		_I.clear();
		_I.sync();	 
}

void _write_output()
{
	
	cout << endl << "XTree 1.0 - Copyright: Gianmarco Iapoce 26/12/2004" << endl;
	cout << "1) Insert a key" << endl;
	cout << "2) Remove a key"<< endl;
	cout << "3) Find a key"<< endl;
	cout << "4) Copy constructor Assign operator Destructor"<< endl;
	cout << "Do your choice" << endl << endl;
	
}

void _putKey()
{

	 
	cin.sync();
 	
	string buffer;
	  
	cout << "Insert a key" << endl;	
	cin>> buffer;
	 	
	 
  
	_x.insert(buffer);
     
	_x.output();
	 
}

void _delKey()
{

	cin.sync();
	
	string buffer;
    

	cout << "Insert a key" << endl;	
	cin>>buffer;
	
	_x.remove(buffer);
	_x.output();
	 
}


void _getKey()
{

	 
	cin.sync();
	string buffer;


	cout << "Insert a key" << endl;	
	cin>>buffer;
	 
 
	_xnode<string> *_z = _x._find_x_node(buffer);

	if (_z != _x._Nil())
		cout << "Key found: " << _z->_data << endl;
	else
		cout << "Key not found" << endl;

	 
}


void _copyConstructor()
{
	_xtree<string> _y(_x);

	 
	_xtree<string> _z;
				   _z.insert("ciao");
 
	cout << "copy constructor" << endl;
	_y.output();

	  
	cout << "assign operator" << endl;
	_z = _y;
	_z.output();
	 
	
}

