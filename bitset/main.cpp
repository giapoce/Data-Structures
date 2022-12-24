#include "Bitset.h"

const int sz_t = 10;

int main()
{
	
	Bset<sz_t> a;
	Bset<sz_t> b;
	Bset<sz_t> c;
	
	a.set();
	b.set();
	c.set();
	c.reset();
	
	bool c1 = (a==b);
	bool c2 = (a!=b);
	bool c3 = (b==c);
	bool c4 = (b!=c);
	bool c5 = (a==c);
	bool c6 = (a!=c);

	cout << "a==b: " << c1 << endl;
	cout << "a!=b: " << c2 << endl;
	cout << "b==c: " << c3 << endl;
	cout << "b!=c: " << c4 << endl;
	cout << "a==c: " << c5 << endl;
	cout << "a!=c: " << c6 << endl;

	b<<4;
	cout << b << endl;

	Bset<sz_t> x(b);
	Bset<sz_t> y = b;

	cout << x << endl;
	cout << y << endl;
	system("PAUSE");
	
	return 0;
}




