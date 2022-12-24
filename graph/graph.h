#ifndef GRAPH_H
#define GRAPH_H

#include "dblist.h"
#include "adaptors.h"
#include "vertex.h"

template<class T>
class graph
{
	
	public:
		graph();
		graph(graph<T> &);
		graph<T> &operator=(graph<T> &);
		vertex<T> *insertVertex(const T&);
		void insertVertex(const T&,const T&);
		void removeVertex(const T&);
		void removeLink(const T&,const T&);
		void addLink(vertex<T> &,vertex<T> &);
		void breadthFirst(vertex<T> *);
		void depthFirst(vertex<T> *);
		void breadthFirst(m_iterator< vertex<T> >);
		void depthFirst(m_iterator< vertex<T> >);
		void generalBF();
		void generalDF();
		m_iterator< vertex<T> > locate(const T &);
		bool isConnected(const T &, const T &);
		bool isPathAvailable(const T &, const T &);
		void routeTo(const T &, const T &);
		m_iterator< vertex<T> > begin() const {return vertices.begin();}
		m_iterator< vertex<T> > end() const {return vertices.end();}
		void show();
		void setUnvisited();
	private:
		m_list< vertex<T> > vertices;
};


template<class T>
graph<T>::graph()
{
	
}

template<class T>
graph<T>::graph(graph<T> &c)
{
	
	m_iterator< vertex<T> >  S = c.begin();
	m_iterator< vertex<T> >  E = c.end();

	while (S != E)
		{

			m_iterator< link<T> >  I = (*S).begin();
			m_iterator< link<T> >  F = (*S).end();
			
			insertVertex((*S).getData());

			while (I != F)
					insertVertex((*S).getData(),(*I++).getDest());

			++S;
		}
		
}

template<class T>
graph<T> &graph<T>::operator=(graph<T> &c)
{
	if (this != &c)
		{
				
			m_iterator< vertex<T> >  S = c.begin();
			m_iterator< vertex<T> >  E = c.end();

			while (S != E)
				{
					m_iterator< link<T> >  I = (*S).begin();
					m_iterator< link<T> >  F = (*S).end();
					
					insertVertex((*S).getData());

					while (I != F)
							insertVertex((*S).getData(),(*I++).getDest());
		
				
					++S;


				}

		}

	return (*this);
}

template<class T>
bool graph<T>::isConnected(const T &src, const T &dst)
{
	
	m_iterator< vertex<T> > _P1 = locate(src);
	m_iterator< vertex<T> > _P2 = locate(dst);

	if ( (_P1 == vertices.end()) || (_P2 == vertices.end()) )
		return false;
	
	m_iterator< link<T> > _L = (*_P1).locate(dst);

	if (_L != (*_P1).end())
		   return true;
		
		   return false;
	

}

template<class T>
bool graph<T>::isPathAvailable(const T &src, const T &dst)
{
	m_iterator< vertex<T> > _P1 = locate(src);
	m_iterator< vertex<T> > _P2 = locate(dst);
	m_iterator< link<T> > I;
	m_iterator< link<T> > F;
	m_stack< vertex<T> *> S;
	vertex<T> *C = 0;
	int x = 0;

	if ( (_P1 == vertices.end()) || (_P2 == vertices.end()) )
		return false;


	S.push( &(*_P1) );
	(*_P1).setVisited();

	while (!S.IsEmpty())
		{
			
			C = S.top();
			

			if (compare(C->getData(),dst)==EQUAL)
				{
					setUnvisited();
					return true;
				}
		
			S.pop();

			
					I = C->begin();
					F = C->end();

					while (I != F)
						{
							if (!((*I).destination())->IsVisited()) 
								{
									(*I).destination()->setVisited();
									S.push((*I).destination());
								}
							
								I++;
						}
		}


	setUnvisited();
	return false;

}


template<class T>
void graph<T>::routeTo(const T &src, const T &dst)
{
     
	m_iterator< vertex<T> > _P1 = locate(src);
	m_iterator< vertex<T> > _P2 = locate(dst);
	m_iterator< link<T> > I;
	m_iterator< link<T> > F;
	m_stack< vertex<T> *> S;
	vertex<T> *C = 0;
	int x = 0;

	if ( (_P1 == vertices.end()) || (_P2 == vertices.end()) )
		return;


	S.push( &(*_P1) );
	(*_P1).setVisited();

   cout << " " << endl;
   
	while (!S.IsEmpty())
		{
			
			C = S.top();
			cout << C->getData() << endl;

			if (compare(C->getData(),dst)==EQUAL)
					{
                      setUnvisited();
                      cout << *(_P2)->getData() << endl;
                      break;
                    }
					
		
			S.pop();

			
					I = C->begin();
					F = C->end();

					while (I != F)
						{
							if (!((*I).destination())->IsVisited()) 
								{
									(*I).destination()->setVisited();
									S.push((*I).destination());
								}
							
								I++;
						}
		}


	setUnvisited();
	

}


template<class T>
vertex<T> *graph<T>::insertVertex(const T &value)
{
	m_iterator< vertex<T> > _P = locate(value);

	if (_P == vertices.end())
			vertices.push_back(vertex<T>(value));
			
	
	return &vertices.back();
}


template<class T>
void graph<T>::insertVertex(const T &src, const T &dst)
{
	
	m_iterator< vertex<T> > _P1 = locate(src);
	m_iterator< vertex<T> > _P2 = locate(dst);
	
	vertex<T> *_S,*_D;

	if (_P1 != vertices.end())
			_S = &(*_P1);
	else
		{
			vertices.push_back(vertex<T>(src));
			_S = &(vertices.back());
		}

	if (_P2 != vertices.end())
			_D = &(*_P2);
	else
		{
			vertices.push_back(vertex<T>(dst));
			_D = &(vertices.back());
			if (compare(*_D,*_S)==EQUAL)
				{
					vertices.erase(*_D);
					cout << "Duplicate value" << endl;
					return;
				}
		}

	m_iterator< link<T> > L = _S->locate(dst);

	if ((L == _S->end()) && compare(*_S,*_D)!=EQUAL)
		_S->insertLink(link<T>(_S,_D));
	else
		cout << "You're trying to connect a node with itself or the link already exists" << endl;
	

}


template<class T>
void graph<T>::removeVertex(const T &value)
{
	m_iterator< vertex<T> >  P = locate(value);

	if (P != vertices.end())
		{
		
			m_iterator< vertex<T> >  S = vertices.begin();
			m_iterator< vertex<T> >  E = vertices.end();

		while (S != E)
			{

				m_iterator< link<T> >  I = (*S).begin();
				m_iterator< link<T> >  F = (*S).end();
				
				while (I != F)
					{
						if (compare((*I).getDest(),value)==EQUAL)
							{
								m_iterator< link<T> >  C = I++;
								(*S).removeLink(*C);								
							}							
 						else
							I++;
					}
				
				++S;
			}
		
			vertices.erase(P);	
		}


}

template<class T>
void graph<T>::addLink(vertex<T> &src,vertex<T> &dst)
{
	
	m_iterator< vertex<T> >  P = locate(src.getData());
	m_iterator< vertex<T> >  A = locate(src.getData());

	if (P != vertices.end() && A != vertices.end())
			(*P).insertLink(link<T>(&src,&dst));
	else
		cout << "Source or destination not included in the graph" << endl;

}

template<class T>
void graph<T>::removeLink(const T &src, const T &dst)
{
	
	m_iterator< vertex<T> >  P = locate(src);

	if (P != vertices.end())
		{
				
				m_iterator< link<T> >  I = (*P).begin();
				m_iterator< link<T> >  F = (*P).end();
				
				while (I != F)
					{
						if (compare((*I).getDest(),dst)==EQUAL)	
							{
								(*P).removeLink(*I);
								break;
							}
						else
							I++;
					}

		}
	
}

template<class T>
void graph<T>::show()
{

	m_iterator< vertex<T> >  S = vertices.begin();
	m_iterator< vertex<T> >  E = vertices.end();

	cout << " " << endl;

	while (S != E)
		{
			cout << (*S).getData() << endl;
				(*S++).showLinks();
		}

}

template<class T>
m_iterator < vertex<T> > graph<T>::locate(const T &value)
{
	m_iterator< vertex<T> >  S = vertices.begin();
	m_iterator< vertex<T> >  E = vertices.end();

	while (S != E)
		{
			if (compare((*S).getData(),value)==EQUAL)		
				break;
			else
				++S;
		}

	return S;

}

template<class T>
void graph<T>::breadthFirst(vertex<T> *V)
{
	
	m_queue< vertex<T> *> Q;
	m_iterator< link<T> > I;
	m_iterator< link<T> > F;

	if ( V != NULL )
			{
				V->setVisited(); 
				Q.enqueue( V );
			}
		
	while (!Q.IsEmpty())
			{
				vertex<T> *curr = Q.top();
				
				cout << curr->getData() << endl;
				
				Q.dequeue();

					I = curr->begin();
					F = curr->end();

					while (I != F)
						{
							if (!((*I).destination())->IsVisited()) 
								{
									(*I).destination()->setVisited();
									Q.enqueue((*I).destination());
								}
							
								I++;
						}

			}

	setUnvisited();

}

template<class T>
void graph<T>::depthFirst(vertex<T> *V)
{
	
	m_stack< vertex<T> *> S;
	m_iterator< link<T> > I;
	m_iterator< link<T> > F;

	if ( V != NULL )
			{
				V->setVisited(); 
				S.push( V );
			}

		
	while (!S.IsEmpty())
			{
				
				vertex<T> *curr = S.top();
				
				cout << curr->getData() << endl;
				
				S.pop();

					I = curr->begin();
					F = curr->end();

					while (I != F)
						{
							if (!((*I).destination())->IsVisited()) 
								{
									(*I).destination()->setVisited();
									S.push((*I).destination());
								}
							
								I++;
						}

			}

	setUnvisited();
	
}


template<class T>
void graph<T>::breadthFirst(m_iterator< vertex<T> > V)
{
	
	m_queue< vertex<T> *> Q;
	m_iterator< link<T> > I;
	m_iterator< link<T> > F;


	if ( V != end() )
			{
				(*V).setVisited(); 
				Q.enqueue( &(*V) );
			}
			
	while (!Q.IsEmpty())
			{
				vertex<T> *curr = Q.top();
				
				cout << curr->getData() << endl;
				
				Q.dequeue();

					I = curr->begin();
					F = curr->end();

					while (I != F)
						{
							if (!((*I).destination())->IsVisited()) 
								{
									(*I).destination()->setVisited();
									Q.enqueue((*I).destination());
								}
							
								I++;
						}

			}

	setUnvisited();

}

template<class T>
void graph<T>::depthFirst(m_iterator< vertex<T> > V)
{
	
	m_stack< vertex<T> *> S;
	m_iterator< link<T> > I;
	m_iterator< link<T> > F;


	if ( V != end() )
			{
				(*V).setVisited(); 
				S.push( &(*V) );
			}
			
	while (!S.IsEmpty())
			{
				vertex<T> *curr = S.top();
				
				cout << curr->getData() << endl;
				
				S.pop();

					I = curr->begin();
					F = curr->end();

					while (I != F)
						{
							if (!((*I).destination())->IsVisited()) 
								{
									(*I).destination()->setVisited();
									S.push((*I).destination());
								}
							
								I++;
						}

			}

	setUnvisited();
}


template<class T>
void graph<T>::generalBF()
{
	
	m_queue< vertex<T> *> Q;
	m_iterator< link<T> > I;
	m_iterator< link<T> > F;
	m_iterator< vertex<T> > S = begin();
	m_iterator< vertex<T> > E = end();


while (S != E)
	{			
			
		if (!(*S).IsVisited()) 
			{
				Q.enqueue( &(*S) ); 
				(*S).setVisited();
			}

	while (!Q.IsEmpty())
			{
				vertex<T> *curr = Q.top();
				
				cout << curr->getData() << endl;
				
				Q.dequeue();

					I = curr->begin();
					F = curr->end();

					while (I != F)
						{
							if (!((*I).destination())->IsVisited()) 
								{
									(*I).destination()->setVisited();
									Q.enqueue((*I).destination());
								}
							
								I++;
						}

			}
	
			S++;
	}
	
	setUnvisited();
}

template<class T>
void graph<T>::generalDF()
{
	
	m_stack< vertex<T> *> P;
	m_iterator< link<T> > I;
	m_iterator< link<T> > F;
	m_iterator< vertex<T> > S = begin();
	m_iterator< vertex<T> > E = end();


while (S != E)
	{	
		if (!(*S).IsVisited())
			{
				P.push( &(*S) ); 
				(*S).setVisited();	
			}
			
	while (!P.IsEmpty())
			{
				vertex<T> *curr = P.top();
				
				cout << curr->getData() << endl;
				
				P.pop();

					I = curr->begin();
					F = curr->end();

					while (I != F)
						{
							if (!((*I).destination())->IsVisited()) 
								{
									(*I).destination()->setVisited();
									P.push((*I).destination());
								}
							
								I++;
						}

			}
	
		S++;
	}
	
	setUnvisited();

}

template<class T>
void graph<T>::setUnvisited()
{

	m_iterator< vertex<T> >  S = vertices.begin();
	m_iterator< vertex<T> >  E = vertices.end();

	while (S != E)
			(*S++).setUnvisited();
				
}


#endif
