#include "hashmap.h"
#include <string>

void createAndDestroy();
void insert();
void remove();

HashTree<string, int> _M;
HashTree<string, int> _X;
typedef HashTree<string, int>::node n;

int main()
{
	createAndDestroy();

	_M.insert("A",11);
	_M.insert("D",12);
	_M.insert("C",13);
	_M.insert("B",14);

	n x = _M.findKey("B");

	if (x != _M.Nil()) 
		cout <<  x->_data << endl;
	else
		cout << "Unexisting key" << endl;

	n y = _M.findKey("E");

	if (y != _M.Nil()) 
		cout <<  y->_data << endl;
	else
		cout << "Unexisting key" << endl;
	
	createAndDestroy();
	cout << _M["W"] << endl;
	
    
    insert();
    remove();
    system("PAUSE");
	return 0;
	
}

void insert()
{
     string k;
     int v;
     cout << "INSERT A KEY-VALUE PAIR" << endl;
     
     cin >> k;
     cin >> v;
     if (cin.fail()) {cin.clear(); cin.sync();}
     
     _M.insert(k,v);
     cout << _M[k] << endl;
      
}

void remove()
{
    
     string k;
     
     cout << "INSERT A KEY" << endl;
     
     cin.sync();
     cin >> k;
      
     _M.erase(k);
     
      cout << _M[k] << endl;
      
}

void createAndDestroy()
{
	
    HashTree<string, int> _C;	
	
      _C.insert("X",1);
	_C.insert("Y",2);
	_C.insert("Z",3);
	_C.insert("W",4);
	
    cout << _C["Z"] << endl;	
	
    _X = _C;
    _M = _C;
	
    cout << _X["Y"] << endl;	
	
    HashTree<string, int> S(_C);
    
    cout << S["W"] << endl;	
    
}
