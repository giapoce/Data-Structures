#include <iostream>
#include <cmath>

bool isnegative(long v) { return v < 0; }
unsigned char *__tobin(long,unsigned char *);

using std::cout;
using std::endl;
using std::cin;

int main()
{
	
	long choice;
	unsigned char buffer[32];
	
	while (true)
		{	
				
			
			cout << "Insert a value" << endl;		
			cin.sync();
			cin >> choice; 
			
			if (cin.fail()) 		
					{cin.clear(); cin.sync(); cout << "Bad input or buffer overflow." << endl;}
			else
					 cout << __tobin(choice, buffer) << endl;	

		}


		return 0;
}


unsigned char *__tobin(long value, unsigned char *buffer)
{
	
	value = isnegative(value)? ~(abs(value)) + 1:value;
	memset(buffer,0,32);
	buffer[32] = '\0';

	long mask = 1 << 31; //Maschera a 32 bits.
	
	for (int i=1; i<=32; i++)
		{
			memset(&buffer[i-1],((value & mask)?'1':'0'),1);
			value <<= 1;
		}
	
	return buffer;

}
