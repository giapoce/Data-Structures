#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
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


template<class K,class T> class ListNode;
template<class K,class T> class List;

const int MAX_LEVEL = 16;

template<class K,class T>
class ListNode
{

    public:
             typedef ListNode<K,T> Node;
             typedef Node * ptrNode;
	public:
		ListNode();
		ListNode(const K &, const T &);
		ListNode(const K &, const T &, int);
		ListNode(int); 
		ListNode(const Node &); 
		Node &operator=(const Node &);
		void _init(const K &k,const T &t,int);
		void cleanup() {Xal.deallocate(forward,level);}
		void destroyNode() {_Destroy(&key); _Destroy(&data); cleanup();}
		void copy(const Node &);
		~ListNode() {cleanup();}
		ptrNode *forward;
		K key;
		T data;
		int level;
		allocator<ptrNode> Xal;
		
};

template<class K,class T>
void ListNode<K,T>::copy(const ListNode<K,T> &_C)
{
    _init(_C.key,_C.data,_C.level);
     cleanup();     
     
     forward = (ptrNode *)Xal.allocate(level,(ptrNode *)0); 
     
     for (int i=0; i<level; i++) 
         if (_C.forward[i]) 
            forward[i]->_init(_C.forward[i]->key,_C.forward[i]->data,_C.forward[i]->level);

}
               
template<class K,class T>
ListNode<K,T>::ListNode() 
{                         
         _init(K(),T(),1);
         
          forward = (ptrNode *)Xal.allocate(level,(ptrNode *)0); 
          forward[0] = (ptrNode)0;
}

template<class K,class T>
ListNode<K,T>::ListNode(const K &_k, const T &_t) 
{

   _init(_k,_t,1);                             
       
    forward = (ptrNode *)Xal.allocate(level,(ptrNode *)0); 
    forward[0] = (ptrNode)0;

}

template<class K,class T>
ListNode<K,T>::ListNode(const K &_k, const T &_t, int lvl) 
{
     
   _init(_k,_t,lvl);
   
    forward = (ptrNode *)Xal.allocate(level,(ptrNode *)0); 
    
    for (int i=0; i<level; i++) 
         forward[i] = (ptrNode)0;

}

template<class K,class T>
ListNode<K,T>::ListNode(int lvl) 
{

   _init(K(),T(),lvl);
   
    forward = (ptrNode *)Xal.allocate(level,(ptrNode *)0); 
    
    for (int i=0; i<level; i++) 
        forward[i] =(ptrNode)0;

}

template<class K,class T>
ListNode<K,T>::ListNode(const ListNode<K,T> &_C) 
{                                                          
      copy(_C);
}

template<class K,class T>
ListNode<K,T> &ListNode<K,T>::operator=(const ListNode<K,T> &_C)
{
     if (this != &_C) 
        copy(_C);
             
     return (*this);
}

template<class K,class T>
void ListNode<K,T>::_init(const K & _k,const T &_t,int lvl)
{

     _Construct(&key,_k);                                
     _Construct(&data,_t);
      level = lvl;
       
      forward = (ptrNode *)Xal.allocate(level,(ptrNode *)0);  
       
      for (int i=0; i<level; i++) 
           forward[i] = (ptrNode)0;
}

template<class K,class T>
class List
{
	public:
		List();
		List(const List<K,T> &);
		List<K,T> &operator=(const List<K,T> &);
		~List();
		void insert(const K &,const T &);
		void erase(const K &);
		ListNode<K,T> *getValue(const K &key);
		void print();
	private:
		ListNode<K,T> *head;
		ListNode<K,T> *NIL;
		int ListLevel;
		allocator< ListNode<K,T> > _Al;
};

template<class K,class T>
List<K,T>::List():ListLevel(0)
{

	head = (ListNode<K,T> *)_Al.allocate(1,(ListNode<K,T> *)0);
		head->_init(K(),T(),MAX_LEVEL);  
	
	NIL = (ListNode<K,T> *)_Al.allocate(1,(ListNode<K,T> *)0);
		NIL->_init(K(),T(),MAX_LEVEL);

	for (int i=0; i<MAX_LEVEL; i++)
		head->forward[i] = NIL;

}

template<class K,class T>
List<K,T>::List(const List<K,T> &C):ListLevel(0)
{
	head = (ListNode<K,T> *)_Al.allocate(1,(ListNode<K,T> *)0);
		head->_init(K(),T(),MAX_LEVEL);  
	
	NIL = (ListNode<K,T> *)_Al.allocate(1,(ListNode<K,T> *)0);
		NIL->_init(K(),T(),MAX_LEVEL);

	for (int i=0; i<MAX_LEVEL; i++)
		head->forward[i] = NIL;

	ListNode<K,T> *pHead = C.head->forward[0];

	while (pHead != C.NIL)
		{
			insert(pHead->key,pHead->data);
			pHead = pHead->forward[0];
		}

}

template<class K,class T>
List<K,T> &List<K,T>::operator=(const List<K,T> &C)
{
	if (this != &C)
		{
			ListNode<K,T> *pHead = C.head->forward[0];

			while (pHead != C.NIL)
				{
					insert(pHead->key,pHead->data);
					pHead = pHead->forward[0];
				}
		}

	return (*this);
}

template<class K,class T>
List<K,T>::~List()
{
	ListNode<K,T> *pHead = head;
	ListNode<K,T> *pCurr = 0;

	while (pHead != NIL)
		{
			pCurr = pHead;
			pHead = pHead->forward[0];
			pCurr->destroyNode();
            _Al.deallocate(pCurr,1);
		}
		
        	
			NIL->destroyNode();
            _Al.deallocate(NIL,1);
}

template<class K,class T>
void List<K,T>::insert(const K &key, const T &value)
{
	
	ListNode<K,T> *update[MAX_LEVEL];

	ListNode<K,T> *pHead = head;
	
	for (int i=ListLevel; i>=0; i--)
		{
			while ((pHead->forward[i] != NIL) && compare(pHead->forward[i]->key,key)==LOWER)
				pHead = pHead->forward[i];
		
			update[i] = pHead;
		}
	
		pHead = pHead->forward[0];
		
		if ((pHead != NIL) && compare(pHead->key,key)==EQUAL) return;

		int newLevel = 1 + rand() % (MAX_LEVEL - 1);
		 
		if (newLevel > ListLevel)
			{
				for (int x=ListLevel + 1; x<newLevel; x++)
					update[x] = head;
					ListLevel= newLevel;
			}
		
		pHead = (ListNode<K,T> *)_Al.allocate(1,(ListNode<K,T> *)0);
        pHead->_init(key,value,newLevel);
		
          
		for (int y=0; y<newLevel; y++)
			{
				pHead->forward[y] = update[y]->forward[y];
				update[y]->forward[y] = pHead;
			}

}


template<class K,class T>
void List<K,T>::erase(const K &key)
{
	
	ListNode<K,T> *update[MAX_LEVEL];
	
	ListNode<K,T> *pHead = head;
	
	for (int i=ListLevel; i>=0; i--)
		{
			while ((pHead->forward[i] != NIL) && compare(pHead->forward[i]->key,key)==LOWER)
				pHead = pHead->forward[i];
		
			update[i] = pHead;
		}
		
		pHead = pHead->forward[0];

		if ((pHead == NIL) || compare(pHead->key,key)!=EQUAL) 
			return;
		
		for (int y=0; y<=ListLevel; y++)
			{
				if (update[y]->forward[y] != pHead) break;
				update[y]->forward[y] = pHead->forward[y];
			}

        pHead->destroyNode();
		_Al.deallocate(pHead,1);

		while ((ListLevel>0) && (head->forward[ListLevel] == NIL))
			ListLevel--;
				 
}

template<class K,class T>
ListNode<K,T> *List<K,T>::getValue(const K &key)
{
	ListNode<K,T> *pHead = head;

	for (int i=ListLevel; i>=0; i--)
		{
			while ((pHead->forward[i] != NIL) && compare(pHead->forward[i]->key,key)==LOWER)
				pHead = pHead->forward[i];
		}

		pHead = pHead->forward[0];

		if ((pHead != NIL) && compare(pHead->key,key)==EQUAL) 
			return pHead;
		else
			return (0);
}

template<class K,class T>
void List<K,T>::print()
{
	
	ListNode<K,T> *pHead = head->forward[0];
	
	while (pHead != NIL)
		{
			cout << pHead->data << endl;
			
			for (int y=0; y<pHead->level; y++)
				cout << "|_______________\t" << pHead->forward[y]->data << endl;

			pHead = pHead->forward[0];   
		}

}

#endif

