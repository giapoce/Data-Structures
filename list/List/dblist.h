#ifndef DBLIST_H
#define DBLIST_H

#include <iostream>
#include <cassert>

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



 

template<class T> class _list;

template<class T> 
class _list
{
	
	public: class _node;
	public: class _iterator;
	
	friend ostream &operator<<(ostream &O_, const _list<T> &_l)
        {
        	
        	int counter=0;
        
        	typename _list<T>::_iterator I = _l.begin();
        	typename _list<T>::_iterator F = _l.end();
        
        	while(I != F)
        		{
        			O_ << *I << "\t";
        				if (((++counter)+1)%10==0) O_ <<"\n";
        			++I;
        		}
        
        	return O_;
        
        }

	public:
		class _node
		{
			friend class _list<T>;
			public:	
			_node *next;
			_node *prev;
			T data;
			void operator=(const _node &c) {_Construct(&data,c.data);}
			_node(const T &item){next = prev = 0; _Construct(&data,item);}
			_node() {next = prev = 0;}
			 
		};

		class _iterator
		{
			friend class _list<T>;
			public:
				_iterator(){}
				_iterator(_node *p) {curr_node=p;}
				_iterator(const _iterator &i) {curr_node = i.curr_node;}
				_iterator& operator=(const _iterator &i) {curr_node = i.curr_node; return (*this);}
				_iterator& operator++() {curr_node=curr_node->next; return (*this);}
				_iterator operator++(int) {_iterator temp = *this; ++(*this); return temp;}
				_iterator& operator--() {curr_node=curr_node->prev; return *this;}
				_iterator operator--(int) {_iterator temp = *this; --(*this); return temp;}
				bool operator==(const _iterator &i) {return (i.curr_node==this->curr_node);}
				bool operator!=(const _iterator &i) {return !((*this)==i);}
				T &operator*() const {return curr_node->data;}
				_node *current() {return curr_node;}
			private:
				_node *curr_node;
		};
		

		_list();
		_list(const _list<T> &);
		~_list();
		void push_back(const T &value) {insert(end(),value);}
		void pop_back() {if (!isEmpty()) erase(--end());}
		void push_front(const T &value) {insert(begin(),value);}
		void pop_front() {if (!isEmpty()) erase(begin());}
		void insert(_iterator,_iterator,_iterator);
		void insert(_iterator, const T &);
		void erase(_iterator,_iterator);
		void erase(_iterator);
		void swap(_iterator,_iterator);
		void swap(_iterator,_iterator,_iterator);
		void merge(_list<T> &);
		T &_front() const;
		T &_back() const;
		void clear();
		int size() const;
		bool isEmpty() const;
		_list<T> &operator=(const _list<T> &);
		bool operator==(const _list<T> &) const;
		bool operator!=(const _list<T> &) const;

		_iterator begin() const;
		_iterator end() const;
		_iterator rbegin() const;
		_iterator rend() const;
		_iterator find(_iterator, _iterator, const T &);
	
	private:
		int m_size;
		_node *head;
		typedef allocator<T> alloc;
		typedef typename alloc::template rebind< _node >::other __Ot;
            __Ot __Nal;
		alloc _Al;

};

template<class T>
_list<T>::_list():m_size(0){head = (_node *)__Nal.allocate(1,(_node *)0); head->next=head->prev=head;}

template<class T>
_list<T>::_list(const _list<T> &cpy)
{	
	this->head = (_node *)__Nal.allocate(1,(_node *)0);
	this->head->next = this->head->prev = this->head;
	this->m_size = 0;
	
	insert(begin(),cpy.begin(),cpy.end());

}

template<class T>
_list<T>::~_list()
{

	erase(begin(),end());
	__Nal.deallocate(this->head,1);
	m_size=0;
}



template<class T>
bool _list<T>::isEmpty() const
{
	return m_size==0;
}

template<class T>
int _list<T>::size() const
{
	return m_size;
}

template<class T>
void _list<T>::clear()
{

	if (isEmpty())
		return;

	erase(begin(),end());
	head->next = head->prev = head;
	m_size=0;

}


template<class T>
typename _list<T>::_iterator _list<T>::find(typename _list<T>::_iterator _S, typename _list<T>::_iterator _E, const T &value)   
{
	
	while (_S != _E)
		if (compare(*_S,value)==EQUAL) break; else ++_S;

			return _S;

}

template<class T>
void _list<T>::insert(typename _list<T>::_iterator position, const T &value)
{

	_node *temp = (_node *)__Nal.allocate(1,(_node *)0);
	_Al.construct(&(temp->data),value);
	
	temp->next = position.current();
	temp->prev = (position.current())->prev;
	(position.current())->prev->next = temp;
	(position.current())->prev = temp;

	++m_size;
}


template<class T>
void _list<T>::insert(typename _list<T>::_iterator position, typename _list<T>::_iterator s, typename _list<T>::_iterator e)
{
	while(s!=e) insert(position,*s++); 
}

template<class T>
void _list<T>::erase(_iterator position)
{
	(position.current())->prev->next = (position.current()->next);
	(position.current())->next->prev = (position.current()->prev);
	(position.current())->prev = (position.current())->next = 0; 
	_Al.destroy(&(position.current()->data));
	__Nal.deallocate(position.current(),1);
	--m_size;
}


template<class T>
void _list<T>::erase(typename _list<T>::_iterator first, typename _list<T>::_iterator last)
{
	while (first!=last) erase(first++);
}

template<class T>
void _list<T>::swap(typename _list<T>::_iterator F_, typename _list<T>::_iterator L_)
{
	T temp; 
    _Al.construct(&temp,*F_);
	_Al.construct(&(*F_),*L_);
	_Al.construct(&(*L_),temp);
}

template<class T>
void _list<T>::swap(typename _list<T>::_iterator F_, typename _list<T>::_iterator L_, typename _list<T>::_iterator position)
{
	for (;F_!=L_;++F_)
		{
			swap(F_,position++);
			if (position==end()) break;
		}
}

template<class T>
void _list<T>::merge(_list<T> &cpy)
{
	
	if (cpy.isEmpty()) return;

	_iterator _S = cpy.begin();
	_iterator _E = cpy.end();
	_iterator _N;

	while (_S!=_E)
		{
			_N = _S; 	
			(*this).push_back(*_N);
			++_N;
			cpy.erase(_S);
			_S = _N;
		}
	
	cpy.clear();

}

template<class T>
T &_list<T>::_front() const
{
	return (*begin());
}

template<class T>
T &_list<T>::_back() const
{
	return (*rbegin());
}

template<class T>
_list<T> &_list<T>::operator=(const _list<T> &cpy)
{
	if (this!=&cpy)
	{

		_iterator S_1 = begin();
		_iterator E_1 = end();
		_iterator S_2 = cpy.begin();
		_iterator E_2 = cpy.end();

		for (; ((S_1 != E_1) && (S_2 != E_2)); ++S_1,++S_2)
			_Al.construct(&(*S_1),*S_2);
		
		erase(S_1,E_1);
		insert(E_1,S_2,E_2);
	}
	return (*this);

}

template<class T>
bool _list<T>::operator==(const _list<T> &c) const
{
	
	typename _list<T>::_iterator B = c.begin();
	typename _list<T>::_iterator E = c.end();
	typename _list<T>::_iterator I = begin();
    typename _list<T>::_iterator F = end();

	bool equal = true;

	while ((B != E) && (I != F))
		{
			if (compare(*B,*I)!=EQUAL)
				equal =false;

			++B; ++I;
		}

	return ((equal) && (B.current()!=NULL) && (I.current()!=NULL));
}

template<class T>
bool _list<T>::operator!=(const _list<T> &c) const
{
	return !((*this) == c);
}

template<class T>
typename _list<T>::_iterator _list<T>::begin() const
{
	return _iterator(this->head->next); 
}

template<class T>
typename _list<T>::_iterator _list<T>::end() const
{
	return _iterator(this->head); 
}

template<class T>
typename _list<T>::_iterator _list<T>::rbegin() const
{
	return _iterator(this->head->prev); 
}

template<class T>
typename _list<T>::_iterator _list<T>::rend() const
{
	return _iterator(this->head);  
}

#endif
