#ifndef VERTEX_H
#define VERTEX_H

#include "link.h"

template<class T>
class vertex
{

	public:
		vertex();
		vertex(const T&,bool=false);
		vertex(const vertex<T> &);
		~vertex();
		bool operator==(const vertex<T> &) const;
		bool operator!=(const vertex<T> &c) const {return !((*this) == c);}
		bool operator>(const vertex<T> &) const;
		bool operator<(const vertex<T> &) const;
		vertex<T> &operator=(const vertex<T> &);
		void insertLink(const link<T> &);
		void removeLink(const link<T> &);
		void setVisited() {visited = true;}
		void setUnvisited() {visited = false;}
		bool IsVisited() {return visited;}
		bool IsLeaf() {return links.IsEmpty();}
		m_iterator< link<T> > begin() const {return links.begin();}
		m_iterator< link<T> > end() const {return links.end();}
		m_iterator< link<T> > locate(const T &);
		T &getData() {return data;}
		void showLinks();
	private:
		T data;
		bool visited;
		m_list < link<T> > links;
		typedef allocator<T> alloc;
		alloc _Al;
};

template<class T>
vertex<T>::vertex():visited(false) {}

template<class T>
vertex<T>::vertex(const T &value, bool v):visited(v) {_Al.construct(&data,value);}

template<class T>
vertex<T>::vertex(const vertex<T> &c):visited(c.visited),links(c.links) {_Al.construct(&data,c.data);}

template<class T>
vertex<T>::~vertex() {}

template<class T>
vertex<T> &vertex<T>::operator=(const vertex<T> &v)
{
		if (this != &v)
			{
				_Al.construct(&data,v.data);
				links = v.links;
				visited = v.visited;
			}


		return (*this);
}


template<class T>
bool vertex<T>::operator==(const vertex<T> &v) const
{
	return (compare(data,v.data)==EQUAL && (links == v.links) && (visited == v.visited));					
}

template<class T>
bool vertex<T>::operator>(const vertex<T> &v) const
{
	return (compare(data,v.data)==GREATER);					
}

template<class T>
bool vertex<T>::operator<(const vertex<T> &v) const
{
	return (compare(data,v.data)==LOWER);					
}

template<class T>
void vertex<T>::insertLink(const link<T> &L)
{
	links.push_back(L);					
}

template<class T>
void vertex<T>::removeLink(const link<T> &L)
{
	links.erase(L);					
}

template<class T>
void vertex<T>::showLinks()
{
	
	m_iterator< link<T> >  I = links.begin();
	m_iterator< link<T> >  E = links.end();

	while (I != E)
				cout << "|____________" << (*(I++)).getDest() << endl;

	cout << " " << endl;
		
}

template<class T>
m_iterator < link<T> > vertex<T>::locate(const T &value)
{
	m_iterator< link<T> >  S = links.begin();
	m_iterator< link<T> >  E = links.end();

	while (S != E)
		{
			if (compare((*S).getDest(),value)==EQUAL)	
				break;
			else
				++S;
		}

	return S;

}


#endif
