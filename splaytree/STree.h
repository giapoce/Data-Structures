#ifndef STREE_H
#define STREE_H
 
#include "IQueue.h"

template<typename T> class SplayTree;

template<typename T> 
class SplayTree
{
	public:
		class Node
		{
			friend class SplayTree<T>;
			public:
			Node *right;
			Node *left;
			Node *parent;
			bool isRight() {return ((parent != NULL) && (this==parent->right));}
			bool isLeft() {return ((parent != NULL) && (this==parent->left));}
			bool isLeaf() {return ((!right)&&(!left));}
			bool isFull() {return ((right) && (left));}
			bool hasSingleChild() {return ((!right)^(!left));}
			T data;
			Node(const T &value){right = left = parent = 0; _Construct(&data,value);}
			Node(const Node &n){right = n.right; left = n.left; parent = n.parent; _Construct(&data,n.data);}
			Node() {right = left = parent = 0;}
			void init(const T &value) {left = right = parent = NULL; _Construct(&data,value);}
			void operator=(const Node &n) {_Construct(&data,n.data); right = n.right; left = n.left; parent = n.parent;}

		};		
		SplayTree():root(0),size(0){}
		SplayTree(const SplayTree<T> &);
		SplayTree<T> &operator=(const SplayTree<T> &);
		~SplayTree();
		void add(const T &);
		void remove(T &);
		const int getSize() const {return size;}
		void outputTree(ostream &);
		Node *findNode(const T &);
		void destroy();
	private:
	Node *root;
	int size;
	void outputTreeHelper(ostream &,Node *,int);
	void destroyHelper(Node *&);
	void rotateRight(Node *);
	void rotateLeft(Node *);
	void SplayNode(Node *);
    typedef allocator<T> alloc;
	typedef typename alloc::template rebind< Node >::other __Ot;
    __Ot __Nal;
	alloc _Al;
   
};

template<typename T> 
SplayTree<T>::SplayTree(const SplayTree<T> &c):root(0),size(0)
{
	
	IQueue< typename SplayTree<T>::Node * > q;
	Node *t = 0;

	if (c.root != NULL) q.enqueue(c.root);
		
		while (!q.isEmpty())
			{
	
				q.top(t);
				add(t->data);
				q.dequeue();
				
	
				if (t->left != NULL)
					q.enqueue(t->left);
				if (t->right != NULL)
					q.enqueue(t->right);
			}
		
}


template<typename T> 
SplayTree<T> &SplayTree<T>::operator=(const SplayTree<T> &c)
{

	if (c.root != NULL) 
		{
		
			if (this != &c)
				{
				
				IQueue< typename SplayTree<T>::Node * > q;
				Node *t = 0;

				q.enqueue(c.root);
					
					while (!q.isEmpty())
						{
				
							q.top(t);
							add(t->data);
							q.dequeue();
							
				
							if (t->left != NULL)
								q.enqueue(t->left);
							if (t->right != NULL)
								q.enqueue(t->right);
						}
				}
		
		}

	return (*this);

}

template<typename T> 
SplayTree<T>::~SplayTree()
{
	destroy();
}


template<typename T> 
void SplayTree<T>::add(const T &value)
{
	
	Node *curr = 0;
	Node *par = 0;

	curr = root;

	while (curr!=NULL)
		{
			par = curr;

			if (compare(value,curr->data)==EQUAL) return;
			
			if (compare(value,curr->data)==GREATER)
					curr = curr->right;
			else
					curr = curr->left;
		}

	curr = (Node *)__Nal.allocate(1,(Node *)0);
	curr->init(value);

	if (par!=0)
		{
			if (compare(value,par->data)==GREATER)
					par->right = curr;
			else
					par->left = curr;

			curr->parent = par;
		}
	else
		root = curr;
	
	SplayNode(curr);

	++size;
	
}

template<typename T>
void SplayTree<T>::remove(T &key)
{	
	Node *z = findNode(key);
	Node *x,*y;

	if (!z)
		return;
	
	if (z) SplayNode(z);

	if (!z->isFull()) 
         y = z;
	else 
		{
         y = z->left;
         while (y->right != NULL) y = y->right;
		}
		
	
     if (y->left != NULL)
         x = y->left;
     else 
         x = y->right;
 
     if (x) x->parent = y->parent;
     if (y->parent)
         if (y->isLeft())
             y->parent->left = x;
         else
             y->parent->right = x;
     else
         root = x;
 
     if (y != z) _Al.construct(&(z->data),y->data);
 
     _Al.destroy(&(y->data));
     __Nal.deallocate(y,1);

	 --size;

}

template<typename T>
void SplayTree<T>::outputTree(ostream &O)
{

	outputTreeHelper(O,root,5);
}

template<typename T>
void SplayTree<T>::outputTreeHelper(ostream &O, SplayTree<T>::Node *r,int indent)
{

	if (!r) return;
	int num = 0;

	outputTreeHelper(O,r->right,indent + 5);
		
	num = indent - 5;

		for (int i = 1; i<=num; i++)
				O << " ";
		O << r->data << endl;

	outputTreeHelper(O,r->left,indent + 5);
}

template<typename T>
void SplayTree<T>::destroy()
{
	destroyHelper(root);
}

template<typename T>
void SplayTree<T>::destroyHelper(SplayTree<T>::Node *&n)
{
	if (!n)
		return;
	destroyHelper(n->left);
	destroyHelper(n->right);
	_Al.destroy(&(n->data));
	__Nal.deallocate(n,1);
	n = 0;
}

template<typename T>
typename SplayTree<T>::Node *SplayTree<T>::findNode(const T &key)
{
	Node *temp = root;
	 
	while(temp)
	{	
		if (compare(key,temp->data)==EQUAL)
			{
				
				//SplayNode(temp);
				return temp;
			}
		else
			if (compare(key , temp->data)==GREATER)
				temp = temp->right;
		else
			if (compare(key , temp->data)==LOWER)
				temp = temp->left;
	}
	

	return 0;
}

template<typename T>
void SplayTree<T>::rotateRight(SplayTree<T>::Node *x)
{

   Node *y = x->left;
 
     x->left = y->right;
     if (y->right != NULL) y->right->parent = x;

     if (y != NULL) y->parent = x->parent;
     if (x->parent) 
	 {
         if (x == x->parent->right)
             x->parent->right = y;
         else
             x->parent->left = y;
     } 
	 else 
         root = y;
     
     y->right = x;
     if (x != NULL) x->parent = y;

}

template<typename T>
void SplayTree<T>::rotateLeft(SplayTree<T>::Node *x)
{

	 Node *y = x->right;
 
     x->right = y->left;
     if (y->left != NULL) y->left->parent = x;
 
     if (y != NULL) y->parent = x->parent;
     if (x->parent) 
	 {
         if (x == x->parent->left)
             x->parent->left = y;
         else
             x->parent->right = y;
     } 
	 else 
         root = y;
    
     y->left = x;
     if (x != NULL) x->parent = y;

}

template<typename T>
void SplayTree<T>::SplayNode(SplayTree<T>::Node *x)
{
	
	if (x == NULL)
			return;

          Node *p = 0;
          Node *g = 0;
	      bool L;

	while ((p = x->parent) != NULL)
		{
			
		g = p->parent;
		L = x->isLeft();

			if (g == NULL)
				{
					if (L) 
						rotateRight(p);
					else
						rotateLeft(p);
				}
			else if (x->isLeft() == p->isLeft())
				{
					if (L)
						{
							rotateRight(g);
							rotateRight(p);
						}
					else
						{
							rotateLeft(g);
							rotateLeft(p);
						}
				}
			else if (x->isLeft() != p->isLeft())
				{
					if (L)
						{
							rotateRight(p);
							rotateLeft(g);
						}
					else
						{
							rotateLeft(p);
							rotateRight(g);
						}
				}
		}

}


#endif
