#include <iostream>
#include "allocator.h"

int main()
{

	_allocator<int> _a;
	const int SIZE = 100;

	int *ptr = _a.allocate(SIZE);
	std::cout << "Allocated memory for " << SIZE << " integers." << std::endl;

	_a.construct(&ptr[0],1010);

	std::cout << std::endl;

	std::cout << "Constructed a new integer at " << &ptr[0] << " memory location,\nwhose value is: " << ptr[0] << "." << std::endl;

	return 0;
}
