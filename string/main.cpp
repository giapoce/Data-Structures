// Fig. 8.5: fig08_05.cpp
// Driver for class IString

#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

#include "IString.h"

int main()
{

   IString string1( "Hello world" );

	   IString::_iterator s = string1.begin();
	   IString::_iterator e = string1.rbegin();

	   cout << string1 << endl;
	   cout << "" << endl;

	  while(s!=string1.end())
			cout << *s++ << " ";
	
	  cout << "" << endl;

	  while(e!=string1.rend())
			cout << *e-- << " ";
		

		cout << "" << endl;	
		cout << e[4] << endl;

		IString buffer;

		cout << "Input a string" << endl;
		cin >> buffer;
		cout << buffer << endl;
       system("PAUSE");
	   
   return 0;
}
