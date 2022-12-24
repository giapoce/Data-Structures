#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "compare_functions.h"
using namespace std;

template<class T> class m_list;
template<class T> class m_iterator;
template<class T> class m_node;

template<class T>
class m_iterator
{
	friend class m_list<T>;
		public:
			m_iterator():m_current(0){}
			m_iterator(m_node<T> *m):m_current(m) {}
			m_iterator(const m_iterator<T> &c):m_current(c.m_current) {}
			m_iterator<T> &operator=(const m_iterator<T> &i) {if (this != &i) {m_current = i.m_current;} return (*this);}
			bool operator==(const m_iterator<T> &i) const {return (i.m_current == m_current);}
			bool operator!=(const m_iterator<T> &i) const {return !((*this) == i);}
			m_iterator<T> &operator++() {m_current = m_current->next; return (*this);}
			m_iterator<T> operator++(int) {m_iterator<T> tmp = (*this); ++(*this); return tmp;}
			m_iterator<T> &operator--() {m_current = m_current->prev; return (*this);}
			m_iterator<T> operator--(int) {m_iterator<T> tmp = (*this); --(*this); return tmp;}
			bool operator!() {return (m_current == NULL);}
			T &operator*() {return m_current->data;}
			const T &operator*() const {return m_current->data;}
			m_node<T> *current() const {return m_current;}
		private:
			m_node<T> *m_current;
};

template<class T>
class m_node
{
	friend class m_list<T>;
		public:
			m_node():next(0),prev(0){}
			void init(const T &_d, m_node<T> *_p, m_node<T> *_n) {next=_n; prev=_p; _Construct(&data,_d);}
			m_node(const T &_d, m_node<T> *_p, m_node<T> *_n):next(_n),prev(_p) {_Construct(&data,_d);}
			m_node(const m_node<T> &c){next = c.next; prev = c.prev; _Construct(&data,c.data);}
			bool operator==(const m_node<T> &c) const {return ((next == c.next) && (prev == c.prev) && compare(data,c.data)==EQUAL);}
			bool operator!=(const m_node<T> &c) const {return !(*this == c);}
			m_node<T> &operator=(const m_node<T> &c){if (this != &c) {next = c.next; prev = c.prev; _Construct(&data,c.data);} return (*this);}
			m_node<T> *prev,*next;
			T data;
};


template<class T> 
class m_list
{
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
		m_iterator<T> begin() const {return m_iterator<T>(this->_head);}
		m_iterator<T> end() const {return m_iterator<T>(NULL);}
		m_iterator<T> rbegin() const {return m_iterator<T>(this->_tail);}
		m_iterator<T> rend() const {return m_iterator<T>(NULL);}
		void push_back(const T &);
		void push_front(const T &);
		void pop_front();
		void pop_back();
		void erase(const T &);
		void erase(m_iterator<T>);
		void insertBefore(const T &, const T &);
		void insertBefore(m_iterator<T>, const T &);
		void insertAfter(const T &, const T &);
		void insertAfter(m_iterator<T>, const T &);
		void destroy();
		m_node<T> *locate(const T &);
		m_iterator<T> locate(m_iterator<T>,m_iterator<T>, const T &);
		bool IsEmpty() const {return (_head == NULL);}
	private:
		m_node<T> *_head, *_tail;
		typedef allocator<T> alloc;
		typedef typename alloc::template rebind< m_node<T> >::other __Ot;
        __Ot __Nal;
		alloc _Al;
		int m_size;

};

template<class T>
m_list<T>::m_list():_head(NULL),_tail(NULL),m_size(0) {}

template<class T>
m_list<T>::m_list(const m_list<T> &c):_head(NULL),_tail(NULL),m_size(0)
{
	
	m_iterator<T> B = c.begin();
	m_iterator<T> E = c.end();

	while (B != E)
			push_back(*(B++));
	
}

template<class T>
m_list<T> &m_list<T>::operator=(const m_list<T> &c)
{
	
	if (this != &c)
		{

		m_iterator<T> B = c.begin();
		m_iterator<T> E = c.end();
			
			while (B != E)
					push_back(*(B++));
				
		}

	return (*this);
}

template<class T>
bool m_list<T>::operator==(const m_list<T> &c) const
{
	
	m_iterator<T> B = c.begin();
	m_iterator<T> E = c.end();
	m_iterator<T> I = begin();
	m_iterator<T> F = end();

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

	m_iterator<T> B = begin();
	m_iterator<T> E = end();

	while (B != E)
		{
			m_iterator<T> curr = B++;
			erase(curr);
		}

	_head = _tail;
	m_size = 0;
}

template<class T>
void m_list<T>::push_back(const T &value)
{
	
	if (_tail == NULL)
		{
			_tail = (m_node<T> *)__Nal.allocate(1,(m_node<T> *)0);
            _tail->init(value,NULL,NULL);
			_head  = _tail;
		}
	else
		{
			_tail->next = (m_node<T> *)__Nal.allocate(1,(m_node<T> *)0);
            _tail->next->init(value,_tail,NULL);
			_tail = _tail->next;
		}
	
	m_size++;
}

template<class T>
void m_list<T>::push_front(const T &value)
{
	
	if (_head == NULL)
		{
			_head = (m_node<T> *)__Nal.allocate(1,(m_node<T> *)0);
			_head->init(value,NULL,NULL);
			_tail = _head;
		}
	else
		{
			_head->prev = (m_node<T> *)__Nal.allocate(1,(m_node<T> *)0);
            _head->prev->init(value,NULL,_head);
			_head = _head->prev;
		}

	m_size++;
}

template<class T>
void m_list<T>::pop_front()
{
	if (_head != NULL) erase(begin());	m_size--;
}

template<class T>
void m_list<T>::pop_back()
{
	if (_tail != NULL) erase(rbegin()); m_size--;
}

template<class T>
void m_list<T>::erase(const T &value)
{
	m_node<T> *x = locate(value);

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
            	
            m_size--;

		}


}

template<class T>
void m_list<T>::erase(m_iterator<T> i)
{
	erase(*i);
}

template<class T>
m_node<T> *m_list<T>::locate(const T &value)
{
	m_iterator<T> P = locate(begin(),end(),value);
	return P.current();
}

template<class T>
m_iterator<T> m_list<T>::locate(m_iterator<T> B, m_iterator<T> E, const T &value)
{
	
	
	while (B != E)
			{
				if (compare(*B,value)==EQUAL)
					break;  
				else 
					B++;
			}

			return B;
}

template<class T>
void m_list<T>::insertBefore(const T &prv, const T &value)
{
	
	m_iterator<T> P = locate(begin(),end(),prv);
	insertBefore(P,value);
			
}

template<class T>
void m_list<T>::insertBefore(m_iterator<T> B, const T &value)
{
	
		if (B != end())
			{
				if (B == begin()) 
						push_front(value);
				else
					{
						m_node<T> *tmp = (m_node<T> *)__Nal.allocate(1,(m_node<T> *)0);
                        tmp->init(value,(B.current())->prev,B.current());
						(B.current())->prev->next = tmp;
						(B.current())->prev = tmp;
					}
					
				m_size++;

			}

}

template<class T>
void m_list<T>::insertAfter(const T &prv, const T &value)
{
	
	m_iterator<T> P = locate(begin(),end(),prv);
	insertAfter(P,value);
			
}

template<class T>
void m_list<T>::insertAfter(m_iterator<T> B, const T &value)
{
	
		if (B != end())
			{
				if (B == rbegin()) 
						push_back(value);
				else
					{
						m_node<T> *tmp = (m_node<T> *)__Nal.allocate(1,(m_node<T> *)0);
                        tmp->init(value,B.current(),(B.current())->next);
						(B.current())->next->prev = tmp;
						(B.current())->next = tmp;
					}

				m_size++;
	
			}
	
}



#endif
