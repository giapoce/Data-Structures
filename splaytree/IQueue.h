#ifndef IQUEUE_H
#define IQUEUE_H

#include<iostream>
#include<cstring>

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



template<typename T> class IQueue;

template<typename T>
class IQueue
{
    public: struct Node;
    
	public:
		IQueue() {head=tail=0; size=0;}
		IQueue(const IQueue<T> &);
		IQueue<T> &operator=(const IQueue<T>&);
		~IQueue();
		bool isEmpty() {return (head==NULL);}
		void enqueue(const T &);
		void dequeue();
		bool top(T &);
		struct Node
			{
             friend class IQueue<T>;
				T data;
				Node *next;
				Node(const T &d){next = 0; _Construct(&data,d);}
				Node(const Node &n){next = n.next; _Construct(&data,n.data);}
				void operator=(const Node &n) {_Construct(&data,n.data); next = n.next;}
				 
			};
		 
		private:
		typedef allocator<T> alloc;
		typedef typename alloc::template rebind< Node >::other __Ot;
        __Ot __Nal;
		alloc _Al;
		Node *head;
		Node *tail;
		int size;
};


template<typename T>
IQueue<T>::IQueue(const IQueue<T> &c):head(0),tail(0)
{

	Node *curr = c.head;

	while (curr)
		{
			enqueue(curr->data);
			curr = curr->next;
		}
}


template<typename T>
IQueue<T> &IQueue<T>::operator=(const IQueue<T> &c)
{

	if (this != &c)
		{
			Node *curr = c.head;

			while (curr)
				{
					enqueue(curr->data);
					curr = curr->next;
				}
		}

	return (*this);
}

template<typename T>
IQueue<T>::~IQueue()
{

	Node *curr = head;
	Node *c =0;

	while (curr)
		{
			c = curr;
			curr = curr->next;
			_Al.destroy(&(c->data));
            __Nal.deallocate(c,1);
		}

 }

template<typename T>
void IQueue<T>::enqueue(const T &value) 
{
	Node *temp = (Node *)__Nal.allocate(1,(Node *)0);
 	temp->next = NULL;
	_Al.construct(&(temp->data),value);

	if (head==0)
		head=tail=temp;
	else
	{
		
		tail->next = temp;
		tail = temp;
	}
	
	++size;

}

template<typename T>
void IQueue<T>::dequeue() 
{

	Node *temp;

		temp = head;

		if (head->next)
				head = head->next;
		else
				head = 0;
       
       _Al.destroy(&(temp->data));
       __Nal.deallocate(temp,1);
		

	--size;

}

template<typename T>
bool IQueue<T>::top(T &v)
{
	if (head==0)
		return false;
		
		_Al.construct(&v,head->data);
		return true;
}


#endif
