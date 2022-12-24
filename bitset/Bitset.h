#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <cassert>
#include <iostream>

using namespace std;

	template<int size_t>
	class Bset
	{

		friend ostream &operator<<(ostream &O, const Bset<size_t> &_B)
		{
               for (int i=0; i<_B.m_size; ++i)
		           {

                   		O << _B.items[i];
			
        		     	if ((i+1)%10==0)
		         	   	   O << endl;
		         	   	   
                    }

	                return O;       
        }

		public:			
			Bset();
			Bset(const Bset<size_t> &);
			Bset<size_t> &operator=(const Bset<size_t> &);
			~Bset();
			void set(int);
			void set();
			void reset(int);
			void reset();
			void flip(int);
			void flip();
			int size();
			int count();
			void print();
			bool any();
			bool none();
			bool operator[](int) const;
			bool operator!=(const Bset<size_t> &);
			bool operator==(const Bset<size_t> &);
			Bset<size_t> &operator>>(int);
			Bset<size_t> &operator<<(int);

		private:

			bool *items;
			int m_size;
			int m_count;

	};

template<int size_t>
Bset<size_t>::Bset():m_size(size_t),m_count(0)
{
	items = new bool[size_t];
	memset(items,0,sizeof(bool)*size_t);	
}

template<int size_t>
Bset<size_t>::Bset(const Bset<size_t> &C):m_size(size_t),m_count(0)
{
	items = new bool[size_t];
	for (int i = 0; i < size_t; ++i)
		items[i] = C.items[i];
}

template<int size_t>
Bset<size_t> &Bset<size_t>::operator=(const Bset<size_t> &C)
{
	if (this != &C)
		{
			for (int i = 0; i < size_t; ++i)
				items[i] = C.items[i];
		}

	return (*this);
}

template<int size_t>
Bset<size_t>::~Bset()
{
	delete [] items;
	items = 0;
}

template<int size_t>
void Bset<size_t>::set(int num)
{
	assert((0<=num)&&(num<m_size));
	if (!items[num])
		items[num] = true;
}

template<int size_t>
void Bset<size_t>::set()
{
	for (int num = 0; num < size_t; ++num)
	if (!items[num])
		items[num] = true;
}

template<int size_t>
void Bset<size_t>::reset(int num)
{
	assert((0<=num)&&(num<size_t));
	if (items[num])
		items[num] = false;
}

template<int size_t>
void Bset<size_t>::reset()
{
	for (int num = 0; num < size_t; ++num)
	if (items[num])
		items[num] = false;
}

template<int size_t>
void Bset<size_t>::flip(int num)
{
	assert((0<=num)&&(num<size_t));
		items[num] = !items[num];
}

template<int size_t>
void Bset<size_t>::flip()
{
	for (int num = 0; num < size_t; ++num)
		items[num] = !items[num];		
}

template<int size_t>
bool Bset<size_t>::operator[](int num) const
{
	assert ((0<=num)&&(num<size_t));
		return items[num];
}

template<int size_t>
bool Bset<size_t>::operator!=(const Bset<size_t> &x) 
{
	return!(*this==x);
}

template<int size_t>
bool Bset<size_t>::operator==(const Bset<size_t> &x) 
{
	for (int i=0; i<m_size; ++i)
		if (items[i]!=x[i])	
			{
				return false;
				break;
			}
				return true;
}

template<int size_t>
Bset<size_t> &Bset<size_t>::operator>>(int num) 
{
	int sz = (num>size_t)? size_t:num;
	for (int y=0; y<sz; ++y)
		if (items[y])
			this->reset(y);

		return (*this);
}

template<int size_t>
Bset<size_t> &Bset<size_t>::operator<<(int num) 
{
	int startIndex = size_t - 1;
	int sz = (num>size_t)? size_t:num;
	int endIndex = size_t - sz;

	for (int y = startIndex; y>=endIndex; --y)
		if (items[y])
			this->reset(y);

	return (*this);

}

template<int size_t>
int Bset<size_t>::size()
{
	return m_size;
}

template<int size_t>
int Bset<size_t>::count() 
{
	int num = 0;

	for (int y=0; y<size_t; ++y)
			if (items[y])
				++num;

	m_count = num;
	return num;
}

template<int size_t>
bool Bset<size_t>::any()
{

	return (m_count!=0);
}

template<int size_t>
bool Bset<size_t>::none()
{
	return (m_count==0);
}

template<int size_t>
void Bset<size_t>::print()
{
		
	for (int i=0; i<m_size; ++i)
		{

		std::cout << (items[i])?'1':'0';
			
			if ((i+1)%10==0)
				std::cout << endl;
		}
		
} 

#endif
