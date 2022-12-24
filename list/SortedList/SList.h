#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include<iostream>
#include<cstring>

using namespace std;

template<class T> class m_list;

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
class m_list
{

	public: class m_iterator;
	public: class m_node;

	public: 
	class m_iterator
		{
			friend class m_list<T>;
				public:
					m_iterator():m_current(0){}
					m_iterator(m_node *m):m_current(m) {}
					m_iterator(const m_iterator &c):m_current(c.m_current) {}
					m_iterator &operator=(const m_iterator &i) {if (this != &i) {m_current = i.m_current;} return (*this);}
					bool operator==(const m_iterator &i) const {return (i.m_current == m_current);}
					bool operator!=(const m_iterator &i) const {return !((*this) == i);}
					m_iterator &operator++() {m_current = m_current->next; return (*this);}
					m_iterator operator++(int) {m_iterator tmp = (*this); ++(*this); return tmp;}
					m_iterator &operator--() {m_current = m_current->prev; return (*this);}
					m_iterator operator--(int) {m_iterator tmp = (*this); --(*this); return tmp;}
					bool operator!() {return (m_current == NULL);}
					T &operator*() {return m_current->data;}
					m_node *current() const {return m_current;}
				private:
					m_node *m_current;
		};

	class m_node
		{
			friend class m_list<T>;
				public:
					m_node(const T &_v):next(0),prev(0){_Construct(&data,_v);}
					m_node():next(0),prev(0){}
					m_node(const T &_d, m_node *_p, m_node *_n):next(_n),prev(_p){_Construct(&data,_d);}
					m_node(const m_node &c){next = c.next; prev = c.prev; _Construct(&data,c.data);} 
					void init(const T &_v, m_node *_p, m_node *_s) {prev = _p; next = _s; _Construct(&data,_v);}
                    bool operator==(const m_node &c) {return ((next == c.next) && (prev == c.prev) && compare(data,c.data)==EQUAL);}
					bool operator!=(const m_node &c) {return !(*this == c);}
					m_node &operator=(const m_node &c){if (this != &c) {next = c.next; prev = c.prev; _Construct(&data,c.data);} return (*this);}
					m_node *prev,*next;
					T data;
		};

	public:
		m_list();
		m_list(const m_list<T> &);
		~m_list();
		m_list<T> &operator=(const m_list<T> &);
		bool operator==(const m_list<T> &) const;
		bool operator!=(const m_list<T> &) const;
		T &front() {return (*begin());}
		T &back() {return (*rbegin());}
		const T &front() const {return (*begin());}
		const T &back() const {return (*rbegin());}
		m_iterator begin() const {return m_iterator(this->_head);}
		m_iterator end() const {return m_iterator(NULL);}
		m_iterator rbegin() const {return m_iterator(this->_tail);}
		m_iterator rend() const {return m_iterator(NULL);}
		void push(const T &);
		void insert(const T &);
		void pop_front();
		void pop_back();
		void erase(const T &);
		void erase(m_iterator);
		void destroy();
		m_node *locate(const T &);
		m_iterator locate(m_iterator,m_iterator, const T &);
		bool IsEmpty() const {return (_head == NULL);}
	private:
		m_node *_head, *_tail;
		typedef allocator<T> alloc;
		typedef typename alloc::template rebind< m_node >::other __Ot;
        __Ot __Nal;
		alloc _Al;

};

template<class T>
m_list<T>::m_list():_head(NULL),_tail(NULL) {}

template<class T>
m_list<T>::m_list(const m_list<T> &c):_head(NULL),_tail(NULL)
{
	
	m_iterator B = c.begin();
	m_iterator E = c.end();

	while (B != E)
			push(*(B++));
	

}

template<class T>
m_list<T> &m_list<T>::operator=(const m_list<T> &c)
{
	
	if (this != &c)
		{

		m_iterator B = c.begin();
		m_iterator E = c.end();
			
			while (B != E)
					push(*(B++));
				
		}

	return (*this);
}

template<class T>
bool m_list<T>::operator==(const m_list<T> &c) const
{
	
	m_iterator B = c.begin();
	m_iterator E = c.end();
	m_iterator I = begin();
	m_iterator F = end();

	bool equal = true;

	while ((B != E) && (I != F))
		{
			if (compare(*B,*I)!=EQUAL)
				equal =false;

			++B; ++I;
		}

	return ((equal) && (!B.current()) && (!I.current()));
}

template<class T>
bool m_list<T>::operator!=(const m_list<T> &c) const
{
	
	return !((*this) == c);
}

template<class T>
m_list<T>::~m_list()
{
	destroy();
}

template<class T>
void m_list<T>::destroy() 
{
	
	if (IsEmpty()) return;

	m_iterator B = begin();
	m_iterator E = end();

	while (B != E)
		{
			m_iterator curr = B++;
			erase(curr);
		}

	_head = _tail;
}

template<class T>
void m_list<T>::push(const T &value)
{

	m_node *_H = _head;
	m_node *_P = NULL;
	m_node *_N = (m_node *)__Nal.allocate(1,(m_node *)0); 
	_N->init(value,NULL,NULL);

	if ( _head == NULL)
		{
			_head = _tail = _N;
			return;
		}

	while( (_H != NULL) && compare(value , _H->data )==GREATER)
		{	
			_P = _H;
			_H = _H->next;
		}

			if (_P == NULL)
				{
					_N->next = _head;
					_head->prev = _N;
					_head = _N;
				}
			else
				{
					_N->next = _H;
					if (_H != NULL) _H->prev = _N;
					if (_P != NULL) _P->next = _N;
					_N->prev = _P;
				}
			
		if (_H == NULL)
			_tail = _N;
}

template<class T>
void m_list<T>::insert(const T &value)
{

	m_iterator _H = begin();
	m_iterator _P(NULL);
	m_node *_N = (m_node *)__Nal.allocate(1,(m_node *)0); 
	_N->init(value,NULL,NULL);

	if ( _head == NULL)
		{
			_head = _tail = _N;
			return;
		}

	while( (_H != end()) && compare(value,*_H )==GREATER )
			_P = _H++;


			if (_P.current() == NULL)
				{
					_N->next = _head;
					_head->prev = _N;
					_head = _N;
				}
			else
				{
					_N->next = _H.current();
					if (_H.current() != NULL) (_H.current())->prev = _N;
					if (_P.current() != NULL) (_P.current())->next = _N;
					_N->prev = _P.current();
				}
		
			if (_H.current() == NULL)
				_tail = _N;
}


template<class T>
void m_list<T>::pop_front()
{
	if (_head != NULL) erase(begin());	
}

template<class T>
void m_list<T>::pop_back()
{
	if (_tail != NULL) erase(rbegin());
}

template<class T>
void m_list<T>::erase(const T &value)
{
	m_node *x = locate(value);

	if (x)
		{
			if (x->next)
				x->next->prev = x->prev;
			else
				_tail = _tail->prev;

			if (x->prev)
				x->prev->next = x->next;
			else
				_head = _head->next;
			
			_Al.destroy(&(x->data));
			__Nal.deallocate(x,1);
		}

}

template<class T>
void m_list<T>::erase(typename m_list<T>::m_iterator i)
{
	 erase(*i);
}

template<class T>
typename m_list<T>::m_node *m_list<T>::locate(const T &value)
{
	m_iterator P = locate(begin(),end(),value);
	return P.current();
}

template<class T>
typename m_list<T>::m_iterator m_list<T>::locate(typename m_list<T>::m_iterator B, typename m_list<T>::m_iterator E, const T &value)
{


	while (B != E)
			if (compare(*B,value)==EQUAL) 
				break;  
			else 
				B++;

			return B;
}


#endif
