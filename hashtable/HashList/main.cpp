#include "HashList.h"
#include <string>

void createAndDestroy();
void insert();
void destroy();

HashList<string, int> _X;
HashList<string, int> _M;

int main()
{
	
	
	_M.insert("A",11);
	_M.insert("D",12);
	_M.insert("C",13);
	_M.insert("B",14);

	 
    cout << _M["C"] << endl;
    createAndDestroy();
    cout << _M["W"] << endl;
    
    insert();
    destroy();
    
    system("PAUSE");
    
	return 0;
}

void insert()
{
     cout << "INSERT A KEY-VALUE PAIR" << endl;
     string X;
     int v;
     
     cin >> X;
     cin >> v;
     
     if (cin.fail()) {cin.clear(); cin.sync();}
     
     _M.insert(X,v);      
     
     cout << _M[X] << endl;
}

void destroy()
{
     cout << "INSERT A KEY" << endl;
     string X;
      
     cin >> X;
     
     _M.erase(X);      
     
     cout << _M[X] << endl;     
}

void createAndDestroy()
{
	HashList<string, int> _C;	
	_C.insert("X",1);
	_C.insert("Y",2);
	_C.insert("Z",3);
	_C.insert("W",4);
	cout << _C["Z"] << endl;	
	_X = _C;
    _M = _C;
	cout << _X["Y"] << endl;	
	
    HashList<string, int> S(_C);
    
    cout << S["W"] << endl;	
    
}
