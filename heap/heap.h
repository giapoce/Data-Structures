#ifndef HEAP_H
#define HEAP_H

#include <cstring>
#include <iostream>

using namespace std;

class HeapOverflow
{
	public:
		HeapOverflow(const char *s = "Cannot allocate memory!"):message(s){}
		void print() {cout << message << endl;}
	private:
		const char *message;
};

template <class T> class heap;

enum CMP {EQUAL = 2, GREATER = 3, LOWER = 4};

template<class K>
	CMP compare(const K &A, const K &B)
		{
				
				if (A == B)
					return EQUAL;
				if (A>B)
					return GREATER;
				if (A<B)
					return LOWER;
								 
		}

CMP compare(char *A, char *B)
		{
                  
                 
			int i = strcmp(A,B);

				if (i>0)
					return GREATER;
				if (i<0)
					return LOWER;
				if (i == 0)
					return EQUAL;
				 
			 
		}

template<class T>
inline bool is_Greater_Equal(const T& _X,const T &_Y)
{
       return ((compare(_X,_Y) == EQUAL) ||(compare(_X,_Y) == GREATER));
}

template <class T> 
class heap
{
	public:
		heap(int num=1);
		heap(const heap<T> &);
		heap<T> &operator=(const heap<T> &);
		~heap();
		int _capacity() const {return capacity;}
		int _size() const {return size;}
		void push(const T &);
		void remove();
		void display();
		bool IsEmpty() const {return (size == 0);}
	private:
        void freeMemory(T *,int,int);
        void swap(T &,T &);
		T *items;
		int size;
		int capacity;
		allocator<T> _Al;
};

template<class T>
void heap<T>::swap(T &src,T &dst)
{
     
     T tmp;
     _Al.construct(&tmp,src);
     _Al.construct(&src,dst);
     _Al.construct(&dst,tmp);

}

template <class T> 
void heap<T>::freeMemory(T *buffer,int sz,int cp)
{
     for (int j=0; j<sz; j++)
          _Al.destroy(&buffer[j]);
     
     _Al.deallocate(buffer,cp);
     buffer = 0;     
}

template <class T> 
heap<T>::heap(int num):size(0),capacity(num)
{
			
	
	items = (T *)_Al.allocate(num,(T *)0);
	memset(items,0,sizeof(T)*num);

	if (!items)
		throw HeapOverflow();
	 

}

template <class T> 
heap<T>::heap(const heap<T> &c):size(c._size()),capacity(c._capacity())
{

	
	items = (T *)_Al.allocate(c._capacity(),(T *)0);
	memset(items,0,c._capacity() * sizeof(T));

	if (!items)
		throw HeapOverflow();

	for (int i=0; i<c._size(); ++i)
			_Al.construct(&items[i],c.items[i]);
	 
}

template <class T> 
heap<T> &heap<T>::operator=(const heap<T> &c)
{

	if (this != &c)
		{
			freeMemory(items,size,capacity);
			items = (T *)_Al.allocate(c.capacity,(T *)0);
			
			memset(items,0,c.capacity * sizeof(T));

			if (!items)
				throw HeapOverflow();

			for (int i=0; i<c.size; ++i)
					_Al.construct(&items[i],c.items[i]);
			 

			size = c.size;
			capacity = c.capacity;
		}

	return (*this);


}

template <class T> 
heap<T>::~heap()
{
	freeMemory(items,size,capacity);
}

template <class T> 
void heap<T>::push(const T &d)
{
	int newCapacity = 0;
	int oldCapacity = capacity;
	int count = 0;
	int parent = 0;
	T tmp;
	
	if (size == capacity)
		{
			
			T *old = items;

			newCapacity = oldCapacity * 2;
			
			items = (T *)_Al.allocate(newCapacity, (T *)0);
			memset(items,0,newCapacity * sizeof(T));
				
			if (!items)
				throw HeapOverflow("Reallocation not allowed");
			
			for (int i=0; i<size; i++)
					_Al.construct(&items[i],old[i]);

			freeMemory(old,size,oldCapacity);

			capacity = newCapacity;
			
		}
							
	
		count = size;
		_Al.construct(&items[size++],d);
		parent = (count - 1) / 2;

		while ((parent >= 0) && compare(items[count],items[parent])==GREATER)
			{
                swap(items[parent],items[count]);
				count = parent;
				parent = (count - 1) /2;
			}
}

template <class T> 
void heap<T>::remove()
{
	
	if (size == 0) 
		return; 

	T tmp;
	T r_value;
	
	int j = 0;
	int children = 0;
   
   try
        {
	    _Al.construct(&r_value,items[0]);
    	_Al.construct(&items[0],items[size-1]);
        }
    catch(...)
      {
              cout << "GOT EXCEPTION" << endl;          
      }

 try{
	while (j<=size/2)
		{
			children = (2 * j) + 1;

			if ((children + 1) < size)
            	if (compare(items[children],items[children+1])==LOWER)	
					children++;
            
            if (children < size) 
				if (is_Greater_Equal(items[j],items[children]))	
					break;

			if (children < size)
                  swap(items[j],items[children]);	 
						 	       
	             j = children;				              
		}
}
catch(...)
{
          cout << "PROBLEMS WHILE REMOVING ITEM" << endl;
}
	size--;
 
    try{
        cout << r_value << endl;
        }
        catch(...)
        {cout << "FAIL" << endl;}

}


template <class T> 
void heap<T>::display()
{
try{      
		for (int i=0; i<size; i++)
			{
				cout << items[i] << '\t';
				if (((i+1)%5)==0)
					cout << endl;
			}
}
catch(...)
{
          cout << "MEMORY PROBLEMS" << endl;
}
}
 
#endif
