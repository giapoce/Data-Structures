#ifndef DEQUE_H
#define DEQUE_H

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
				if (i == 0)
					return EQUAL;
		}

template <typename T> class _deque;

template <typename T> 
class _deque
{
 friend	ostream &operator<<(ostream &output, const _deque<T> &ref)
        {

		typename _deque<T>::_iterator _S = ref.begin();
		typename _deque<T>::_iterator _E = ref.end();
		int _C = 0;

		for (; _S != _E; ++_S)
				{
					cout << *_S << '\t';
					if ((++_C + 1) % 10 == 0) cout << endl;
				}

		return output;
    }
    
	public: class _iterator;
	friend class _iterator;

	public:
		_deque(int num=100);
		_deque(const _deque<T> &);
		~_deque();
		void push_back(const T &);
		void push_front(const T &);
		void pop_back();
		void pop_front();
		_iterator find(_iterator,_iterator,const T &);
		void insert(_iterator,const T &);
		void insert(_iterator,_iterator,_iterator);
		void erase(_iterator);
		void erase(_iterator,_iterator);
		bool isEmpty() const {return num_items==0;}
		int capacity() const {return m_capacity;}
		int size() const {return num_items;}
		const T &_front() const {return *(begin());}
		const T &_back() const {return *(--end());}
		const T &operator[](int) const;
 		T &operator[](int);
		_deque<T> &operator=(const _deque<T> &);
		class _iterator
		{
			friend class _deque<T>;
			public:
				_iterator() {_index=_nxt=_prev=0; cap = 0;}
				_iterator(T *dik, int curr_idx, int _capacity) {_index=_nxt=_prev=curr_idx; curr_deque = dik; cap = _capacity;}
				_iterator(const _iterator &i) {_index=_nxt=_prev=i._index; curr_deque = i.curr_deque; cap = i.cap;}
				bool operator==(const _iterator &i) const {return i.index()==_index;}
				bool operator!=(const _iterator &i) const {return !((*this)==i);}
				const _iterator &operator=(const _iterator &i) {if (this != &i) {_index = i.index(); curr_deque = i.curr_deque;} return (*this);}
				_iterator &operator++() {_nxt = (_index + 1) % cap; _index = _nxt; return (*this);}
				_iterator operator++(int) {_iterator tmp = *this; ++(*this); return tmp;}
				_iterator &operator--() {_prev = ((_index - 1) + cap) % cap; _index = _prev; return (*this);}
				_iterator operator--(int) {_iterator tmp = *this; --(*this); return tmp;}
				_iterator &operator-=(int i) {_nxt = ((_index - i) + cap) % cap; _index = _nxt; return *this;}
				_iterator &operator+=(int i) {_nxt = (_index + i) % cap; _index = _nxt; return *this;}
				_iterator operator-(int i) {_iterator tmp =*this; return (tmp -= i);}
				_iterator operator+(int i) {_iterator tmp =*this; return (tmp += i);}
				bool operator>(const _iterator &_i) {return _index > _i.index();}
				bool operator<(const _iterator &_i) {return _index < _i.index();}
				bool operator>=(const _iterator &_i) {return _index >= _i.index();}
				bool operator<=(const _iterator &_i) {return _index <= _i.index();}
				int operator-(const _iterator &I) {return ((_index - I.index()) + cap) % cap;}
				int operator+(const _iterator &I) {return (_index + I.index()) % cap;}
				T &operator*() {return curr_deque[_index];}
				const T &operator*() const {return curr_deque[_index];}
				const T &operator[](int _N) {return (*(*this + _N));}
				int index() const {return _index;}
			private:
				int _index;
				int _nxt;
				int _prev;
				int cap;
				T *curr_deque;
		};
		_iterator begin() const;
		_iterator end() const;
		_iterator rbegin() const;
		_iterator rend() const;
	private:
            void freeMemory(T *,int,int);    
		T *items;
		int m_capacity;
		int num_items;
		int front;
		int rear;
		const int GROW_RATIO;
		void resize();
		allocator<T> _Al;

};


template<typename T>
_deque<T>::_deque(int num):GROW_RATIO(2),front(0),rear(0),m_capacity(num),num_items(0)
{
	items = (T *)_Al.allocate(num,(T *)0);
	assert(items!=0);
	memset(items,0,m_capacity * sizeof(T));
}

template<typename T>
_deque<T>::_deque(const _deque<T> &cpy):GROW_RATIO(2),front(0),rear(0),m_capacity(cpy.m_capacity),num_items(0)
{
    items = (T *)_Al.allocate(cpy.capacity(),(T *)0);
	assert(items!=0);
	
	_iterator _S = cpy.begin();
	_iterator _E = cpy.end();

	for (; _S != _E; ++_S)
		push_back(*_S);
}

template<typename T>
void _deque<T>::freeMemory(T *buffer,int sz,int cp)
{
      _iterator _K = begin();
      _iterator _H = end();
      
      if (sz)
         while ( _K != _H)
                 _Al.destroy(&(*(_K++)));
                 
     _Al.deallocate(items,cp);
     items = 0;     
}

template<typename T>
_deque<T>::~_deque()
{
	
       freeMemory(items,num_items,m_capacity);
}

template<typename T>
void _deque<T>::push_back(const T &new_value)
{
	if (num_items == m_capacity) resize();
	_Al.construct(&items[rear],new_value);
	rear = (rear + 1) % m_capacity;
	++num_items;
}

template<typename T>
void _deque<T>::push_front(const T &new_value)
{
	if (num_items == m_capacity) resize();
	front = ((front - 1) + m_capacity) % m_capacity;
	_Al.construct(&items[front],new_value);
	++num_items;
}

template<typename T>
void _deque<T>::pop_back()
{
	if (!isEmpty())
		{
			rear = ((rear - 1) + m_capacity) % m_capacity;
			--num_items;
		}
}

template<typename T>
void _deque<T>::pop_front()
{
	if (!isEmpty())
		{
			front = (front + 1) % m_capacity;
			--num_items;
		}
}

template<typename T>
void _deque<T>::insert(_iterator _I, const T &value)
{
	int _pos = _I.index();
	int _OFF = _I - begin();
	int _last_pos = 0;
	int _first_pos = 0;
	bool _isBefore = (_OFF <= (num_items/2));
	//int start,stop;

	if (_I == begin()) (*this).push_front(value);
	else if (_I == (--end())) (*this).push_back(value);
	else
	{
		if (num_items == m_capacity) resize();
		
		if (_isBefore)
			{
				_first_pos = (--front + m_capacity) % m_capacity;

				_iterator _FS(items,_first_pos,m_capacity);
				_iterator _PS = _FS;
				_iterator _LS(items,_pos,m_capacity);
		
				for (;_FS != _LS; ++_FS)
						_Al.construct(&(*_FS),*(++_PS));

				_Al.construct(&(*(--_PS)),value);
				front = _first_pos;
			}
		else
			{
				_last_pos = ++rear % m_capacity;
				_iterator _S(items,_last_pos,m_capacity);
				_iterator _M = _S;
				_iterator _E(items,_pos,m_capacity);
		
				for (;_S != _E; --_S)
						_Al.construct(&(*_S),*(--_M));
				
				_Al.construct(&(*_M),value);
				rear = _last_pos;

			}

		/*	start = _pos;
			stop = last_pos;
			
			 if (start < stop)
				for (int i = stop; i > start; i--)
					items[i] = items[i - 1];
			else
			{
				for (int m = stop; m > 0; m--)
					items[m] = items[m - 1];
				items[0] = items[m_capacity - 1];
				for (int n = m_capacity - 1; n > start; n--)
					items[n] = items[n - 1];
			}
		*/
			
			++num_items;
	}

}

template<typename T>
void _deque<T>::insert(_iterator _P,_iterator _F,_iterator _L)
{
	int size_right = _P - begin();
	int size_left = end() - _P;
	int _OFF = _L - _F; 
	bool is_Before = (size_right <= size_left);
	
	if (is_Before)
		
		{
			if (_OFF >= size_right)
					
					{
						_iterator _G = --_L;
						_iterator _H = --begin();
						_iterator _Q = begin();
						_iterator _N = --_P;

						for (; _G >= _F; --_G)
								push_front(*_G);
						for (;_N!=_H;--_N)
								push_front(*_N);
							erase(_Q,++_P);
					}
			
			else
					
					{
						_iterator _K = --_P;
						_iterator _W = --begin();
						_iterator _E = begin();
						
						for (; _K != _W; --_K)
								push_front(*_K);
						for (;_F!=_L;++_F)
								_Al.construct(&(*(_E++)),*_F);
						erase(_E,++_P);
							
					}

		}
		
	else
		
		{
				if (_OFF >= size_left)
					
					{
						_iterator _D = end();
						_iterator _J = end();
						_iterator _X = _P;

						while (_F != _L)
								push_back(*_F++);
						for (;_X!=_D;++_X)
								push_back(*_X);
						erase(_P,_J);
					}

				else

					{
						_iterator _B = end();
						_iterator _A = _B;
						_iterator _Z = _P;
						_iterator _T = _P;

						while (_Z != _B)
								push_back(*_Z++);
						while (_F != _L)
								_Al.construct(&(*(_T++)),*(_F++));
						erase(_T,_A);

					}

		}


}

template<typename T>
void _deque<T>::erase(_iterator _I)
{

	if (_I != end())
		{
			int _pos = _I.index();
			int _OFF = _I - begin();
			bool _isBefore = (_OFF <= (num_items/2));

			//int start,stop;

			if (_I == begin()) (*this).pop_front();
			else if (_I == (--end())) (*this).pop_back();
			else
			{
			
			if (_isBefore)
					{
						_iterator _FS(items,_pos,m_capacity);
						_iterator _MS = _FS;
						_iterator _ES(items,front,m_capacity);

						for (; _FS != _ES; --_FS)
								_Al.construct(&(*_FS),*(--_MS));

						front = ++front % m_capacity;
					}
			else
				{
						_iterator _S(items,_pos,m_capacity);
						_iterator _M = _S;
						_iterator _E(items,(front + (num_items - 1)) % m_capacity,m_capacity);

						for (; _S != _E; ++_S)
								_Al.construct(&(*_S),*(++_M));

						rear = (--rear + m_capacity) % m_capacity;
				}

				/*

				start = _pos;
				stop = rear;
				
				if (start < stop)
					for (int i = start; i < stop; i++)
						items[i] = items[i + 1];
				else
				{
					for (int m = start; m < m_capacity - 1; m++)
						items[m] = items[m + 1];
					items[m_capacity - 1] = items[0];
					for (int n = 0; n < stop; n++)
						items[n] = items[n + 1];
				} 
				
				*/

				--num_items;
			}
	}
}

template<typename T>
void _deque<T>::erase(_iterator _S, _iterator _E)
{
	
	if ((_S != end()) && (_E != end()))
		{
			int _OFF = _E - _S;
			int _OFF_R = _S - begin();
			int _OFF_L = end() - _E;
			

			if (_OFF_R < _OFF_L)
					{
							_iterator _P = --begin();
							_iterator _N = --_S;
							_iterator _D = --_E;

								while (_N != _P)
										_Al.construct(&(*(_E--)),*(_N--));
								
								while (_OFF--)
										pop_front();
					}
			else
					{
			
							_iterator _G = end();
							_iterator _F = _E;
							_iterator _H = _S;

								while (_F != _G)
										_Al.construct(&(*(_H++)),*(_F++));
								
								while (_OFF--)
										pop_back();
					}
		}

}

template<typename T>
typename _deque<T>::_iterator _deque<T>::find(typename _deque<T>::_iterator _S, typename _deque<T>::_iterator _E, const T &value)
{
	while (_S != _E)
			if (compare(*_S,value)==EQUAL) break; else ++_S;

			return _S;
}

template<class T>
const T &_deque<T>::operator[](int index) const 
{
		int real_pos = (index + front) % m_capacity;
		return items[real_pos];
}

template<typename T>
T &_deque<T>::operator[](int index)
{
		int real_pos = (index + front) % m_capacity;
		return items[real_pos];
}

template<typename T>
_deque<T> &_deque<T>::operator=(const _deque<T> &cpy)
{
 
	if (this != &cpy)
		 {
 
			 freeMemory(items,num_items,m_capacity);
			 items = 0;

			 _iterator _S = cpy.begin();
			 _iterator _E = cpy.end();
 
			 m_capacity = cpy.m_capacity;

			 items = (T *)_Al.allocate(m_capacity,(T *)0);
			 assert(items != 0);

			 while (_S != _E)
					push_back(*_S++);
		
		}

	return (*this);
}

template<typename T>
void _deque<T>::resize()
{

	int new_capacity = m_capacity * GROW_RATIO;
	int save_items = num_items;
	int last_pos = (front + (num_items - 1)) % m_capacity;
	T *temp = (T *)_Al.allocate(new_capacity, (T *)0);
	
	if (front <= last_pos)
		for (int i = front, j = 0; i <= last_pos; i++, j++)
			_Al.construct(&temp[j],items[i]);
	else
	{
		for (int m = front, n = 0; m < m_capacity; m++, n++)
			_Al.construct(&temp[n],items[m]);
		for (int k = 0, h = m_capacity - front; k <= last_pos; k++, h++)
			_Al.construct(&temp[h],items[k]);
	}


	freeMemory(items,num_items,m_capacity);
	items = temp;
	m_capacity = new_capacity;
	front = 0; rear = save_items % m_capacity;
	num_items = save_items;
	
}

template<typename T>
typename _deque<T>::_iterator _deque<T>::begin() const
{
	return (typename _deque<T>::_iterator(this->items,front % m_capacity,m_capacity));
}

template<typename T>
typename _deque<T>::_iterator _deque<T>::end() const
{
	return (typename _deque<T>::_iterator(this->items,(front + num_items) % m_capacity,m_capacity));
}

template<typename T>
typename _deque<T>::_iterator _deque<T>::rbegin() const
{
	return (typename _deque<T>::_iterator(this->items,(front + (num_items - 1)) % m_capacity,m_capacity));
}

template<typename T>
typename _deque<T>::_iterator _deque<T>::rend() const
{
	return (typename _deque<T>::_iterator(this->items,((front - 1) + m_capacity) % m_capacity,m_capacity));
}

 
 
#endif


