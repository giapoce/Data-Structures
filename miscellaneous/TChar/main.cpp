#include <iostream>
#include <cstring>

using namespace std;

//Programma di conversione da int a char *

char *_TChar(char *, int);

int main()
{

	int num = 0;
	 
	char cBuffer[32];
	
	while(true)
		{
			memset(cBuffer,0,32);
			cin.sync();
			cout << "Insert a number" << endl;		
			cin >> num;
			if (cin.fail())
						{
							cout << "Bad input or integer overflow" << endl;
							cin.clear();
							cin.sync();
							memset(cBuffer,0,32);
							num = 0;
						}
			else
				cout << "Your number converted to string is: " << _TChar(cBuffer,num) << endl;
			 

		}

	 
	return 0;
}


char *_TChar(char *buf, int num)
{

	int x = num;
	int c = 0,i = 0;
	bool isNegative = (num < 0);

	if (num==0) 
		{
			buf[0] = (char)('0' + 48);
			return buf;
		}
	else if (isNegative)
		{
			num *= (-1);
			x = num;
		}

	do 
		{
			c = (x % 10);
			buf[i++] =  (char)(c + 48);
		} while(x/=10);

	if (isNegative) buf[i] = '-';
    
	strrev(buf);
	return buf;

}

