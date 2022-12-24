#include "hashtable.h"
#include <string>

typedef hashtable<string,int> Ht;
 
Ht _H;
Ht _X;

Ht getHashTable()
{
                 
   Ht h;
   h.insert("X",21);
   return h;
   
}

void createAndDestroy()
{
     
     Ht _M;     
     _M.insert("A",1);	 
     _M.insert("B",2);	 
     _M.insert("C",3);

     Ht N = getHashTable();
     cout << N["X"] << endl; 
     
     
       _X = _M;
      Ht _S(_X);

                 
      cout << _X["B"] << endl;
      cout << _S["C"] << endl;

       
}

int main()
{
	
  _H.insert("A",12);	 
  _H.insert("B",22);	 
  _H.insert("C",33);	 
  _H.insert("C",44);	 

      cout << _H["B"] << endl;
      
system("PAUSE");

  createAndDestroy();

system("PAUSE");

  cout << _H["C"] << endl;
  _H.erase("C");
  cout << _H["C"] << endl;
  
system("PAUSE");
  
  
  return 0;

}

