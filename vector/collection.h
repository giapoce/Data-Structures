#ifndef VEC_H
#define VEC_H
 
#include <iostream>
#include <cassert>
#include <cstring>
 
using namespace std;
 
enum CMP {EQUAL = 2, GREATER = 3, LOWER = 4};

template<class K>
	CMP compare(const K &A, const K &B)
		{
				if (A>B)
					return GREATER;
				if (A<B)
					return LOWER;
				if (A == B)
					return EQUAL;
		}

CMP compare(char *A, char *B)
		{
			
			int i = strcmp(A,B);

				if (i>0)
					return GREATER;
				if (i<0)
					return LOWER;
				if (i==0)
					return EQUAL;
		}

template<class T> 
class collection;
 
template<class T>
class collection
{
	friend ostream &operator<<(ostream &output, const collection<T> &_tst) 
		{

			for (int i=0; i<_tst.num_items; ++i)
				{
					output << _tst.items[i] << '\t';
					if ((i + 1) % 10==0)
						output << endl;
			}
			
			return output;
		}

	public: class _iterator;
	public:
		collection(int i=2);
		collection(const collection<T> &);
		~collection();
		int size() const;
		int capacity() const;
		const T &operator[](int) const;
 		T &operator[](int);
		const collection<T> &operator=(const collection<T> &);
		void push_back(const T &value) {insert(end(),value);}
		void pop_back() {if (!isEmpty()) erase(--end());}
		void insert(_iterator,const T &);
		void insert(_iterator,_iterator,_iterator);
		void erase(_iterator);
		void erase(_iterator,_iterator);
		bool isEmpty();
		class _iterator
		{
			friend class collection<T>;
			public:
				_iterator() {curr_vec=0; curr_index=0;}
				_iterator(T *col, int curr_idx) {curr_vec = col; curr_index=curr_idx;}
				bool operator==(const _iterator &i) {return i.curr_index==curr_index;}
				bool operator!=(const _iterator &i) {return i.curr_index!=curr_index;}
				bool operator>(const _iterator &i) {return i.curr_index<curr_index;}
				bool operator<(const _iterator &i) {return i.curr_index>curr_index;}
				bool operator>=(const _iterator &i) {return i.curr_index<=curr_index;}
				bool operator<=(const _iterator &i) {return i.curr_index>=curr_index;}
				_iterator &operator++() {++curr_index; return *this;}
				_iterator operator++(int) {_iterator temp = *this; ++(*this); return temp;}
				_iterator &operator--() {--curr_index; return *this;}
				_iterator operator--(int) {_iterator temp = *this; --(*this); return temp;}
				_iterator &operator+=(int i) {curr_index+=i; return *this;}
				_iterator &operator-=(int i) {curr_index-=i; return *this;}
				_iterator operator+(int i) const {_iterator tmp = *this; return (tmp+=i);}
				_iterator operator-(int i) const {_iterator tmp = *this; return (tmp-=i);}
				int operator-(const _iterator &i) {return abs(i.curr_index-curr_index);}
				int operator+(const _iterator &i) {return i.curr_index+curr_index;}
				T &operator[](int _N) {return (*(*this + _N));}
				const T &operator*() const {return curr_vec[curr_index];}
				T &operator*() {return curr_vec[curr_index];}
				int index() {return curr_index;}
			private:
				int curr_index;
				T *curr_vec;
		};
		_iterator begin() const;
		_iterator end() const;
		_iterator rbegin() const;
		_iterator rend() const;
		_iterator find(_iterator,_iterator,const T &);
	private:
            
        void freeMemory(T *,int,int);
		void resize();
		int num_items;
		int m_size;
		T *items;
		const int GROW_RATIO;
		allocator<T> _Al;
		
};


template<class T>
collection<T>::collection(int num):GROW_RATIO(2),num_items(0),m_size(num)
{
     
	items = (T *)_Al.allocate(num,(T *)0);
	assert(items!=0);
	memset(items,0,m_size * sizeof(T));
}

template<class T>
collection<T>::collection(const collection<T> &ref):GROW_RATIO(2),num_items(ref.num_items),m_size(ref.m_size)
{
	items = (T *)_Al.allocate(ref.capacity(),(T *)0);
	assert(items!=0);
	for (int j = 0; j<ref.size(); j++)
		_Al.construct(&items[j],ref.items[j]);
}

template<class T>
void collection<T>::freeMemory(T *buffer,int sz,int cp)
{
    for (int i=0; i<sz; i++)
	    _Al.destroy(&buffer[i]);
	_Al.deallocate(buffer,cp);
	buffer = 0; 
}

template<class T>
collection<T>::~collection()
{
    freeMemory(items,num_items,m_size);                           	
}


template<class T>
bool collection<T>::isEmpty()
{
	return (num_items==0);
}

template<class T>
const collection<T> &collection<T>::operator=(const collection<T> &cpy)  
{

	if (this != &cpy)
		{
			if (num_items!=cpy.num_items)
				{
					freeMemory(items,num_items,m_size);
					m_size = cpy.m_size;	
					items = (T *)_Al.allocate(m_size,(T *)0);
					assert(items!=0);
				}
			num_items = cpy.num_items;
			for (int j=0; j<cpy.size(); j++)
      			_Al.construct(&items[j],cpy.items[j]);
		}
				
		return (*this);

}

template<class T>
const T &collection<T>::operator[](int index) const 
{
		assert((0<=index)&&(index<num_items));
		return items[index];
}

template<class T>
T &collection<T>::operator[](int index)
{
		assert((0<=index)&&(index<num_items));
		return items[index];
}

template<class T>
void collection<T>::resize()
{	
	int oldSize = m_size;
	int newSize = oldSize * GROW_RATIO;

	if (newSize > oldSize)
		{
	            T *oldItems = items;
			
      	      items = (T *)_Al.allocate(newSize,(T *)0);
				assert(items!=0);
			
	            for (int j=0; j<num_items; j++)
				_Al.construct(&items[j],oldItems[j]);
      		           
            	freeMemory(oldItems,num_items,oldSize);
				m_size = newSize;
		}
}

template<class T>
int collection<T>::size() const
{
	return num_items;
}

template<class T>
int collection<T>::capacity() const
{
	return m_size;
}

template<class T>
typename collection<T>::_iterator collection<T>::begin() const
{
	return (typename collection<T>::_iterator(this->items,0));
}

template<class T>
typename collection<T>::_iterator collection<T>::end() const
{
	return (typename collection<T>::_iterator(this->items,num_items));
}

template<class T>
typename collection<T>::_iterator collection<T>::rbegin() const
{
	return (typename collection<T>::_iterator(this->items,num_items-1));
}

template<class T>
typename collection<T>::_iterator collection<T>::rend() const
{
	return (typename collection<T>::_iterator(this->items,-1));	
}

template<class T>
typename collection<T>::_iterator collection<T>::find(typename collection<T>::_iterator _S, typename collection<T>::_iterator _E, const T &value)   
{
	
	while (_S != _E)
		if (compare(*_S,value) == EQUAL) break; else ++_S;

			return _S;
}


template<class T>
void collection<T>::erase(typename collection<T>::_iterator position)
{
	if (position != end())
		{
			int _p = position.index();
			int num = ((num_items - _p) - 1);
			int j=_p;
			 while (num--)
				{
					_Al.construct(&items[j],items[j+1]);
					j++;
				}
			//memmove(&items[_p],&items[_p + 1],((num_items - _p) - 1) * sizeof(T));
			--num_items;
		}
}

template<class T>
void collection<T>::erase(typename collection<T>::_iterator first,typename collection<T>::_iterator last)
{
	if ((first != end()) && (last != end()))
		{
			
			int to_remove = last - first;
			int _f = first.index(), _l = last.index();
			int num = num_items - _l;
			int j = _f;
			int m = _l;
			while (num--)
				{
					_Al.construct(&items[j],items[m]);
					j++; m++;
				}

			//memmove(&items[_f], &items[_l],(num_items - _l) * sizeof(T));
			num_items -= to_remove;
		}
}


template<class T>
void collection<T>::insert(typename collection<T>::_iterator i, const T &value)
{

		if (num_items==m_size) resize();

		int c_index = i.index();
		
		if (c_index != num_items) 
			{
                    				 
		                for (int j=num_items; j>c_index; j--)
				    _Al.construct(&items[j],items[j-1]);
				    				    
					_Al.construct(&items[c_index],value);
					++num_items;
			}
		else
			_Al.construct(&items[num_items++],value);

}

template<class T>
void collection<T>::insert(typename collection<T>::_iterator i, typename collection<T>::_iterator b, typename collection<T>::_iterator c)
{

		while (b!=c)
			{
				insert(i,*b++);
				i++;
			}

}

   
 

  
#endif
