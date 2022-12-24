#ifndef BTREE_H
#define BTREE_H

#include "IQueue.h"

/*A very simple implementation of a templated binary tree class.*/

template<typename T> class BinaryTree;

template<typename T> 
class BinaryTree
{
      public: class Node;
	public:
		class Node
		{
			friend class BinaryTree<T>;
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
			void _init(Node *_R,Node *_L,Node *_P) {right = _R; left = _L; parent = _P;}
			void operator=(const Node &n) {_Construct(&data,n.data); right = n.right; left = n.left;}
			Node(const T &value) {right = left = parent = 0; _Construct(&data,value);}
			Node() {right = left = parent = 0;}
			Node(const Node &n) {left = n.left; right = n.right; _Construct(&data,n.data);}
		};
        
		BinaryTree():root(0),size(0){}
		BinaryTree(const BinaryTree<T> &);
		BinaryTree<T> &operator=(const BinaryTree<T> &);
		~BinaryTree();
		void add(const T &);
		void remove(T &);
		Node *getOutmostRight(Node *);
		Node *getOutmostLeft(Node *);
		const int getSize() const {return size;}
		void traverseTreePreOrder();
		void traverseTreePostOrder();
		void traverseTreeAscending();
		void traverseTreeDescending();
		void outputTree(ostream &);
		Node *findNode(const T &);
		void destroy();
	private:
	Node *root;
	int size;
	void traverseTreeHelperPreOrder(Node *);
	void traverseTreeHelperPostOrder(Node *);
	void traverseTreeHelperAscending(Node *);
	void traverseTreeHelperDescending(Node *);
	void outputTreeHelper(ostream &,Node *,int);
	void destroyHelper(Node *&);
    typedef allocator<T> alloc;		
    typedef typename alloc::template rebind<Node>::other __Ot;
    __Ot __Nal;
    alloc _Al;
    
};

template<typename T> 
BinaryTree<T>::BinaryTree(const BinaryTree<T> &c):root(0),size(0)
{
	
	IQueue< Node * > q;
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
BinaryTree<T> &BinaryTree<T>::operator=(const BinaryTree<T> &c)
{

	if (c.root != NULL) 
		{
		
			if (this != &c)
				{
				
				IQueue< typename BinaryTree<T>::Node * > q;
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
BinaryTree<T>::~BinaryTree()
{
	destroy();
}


template<typename T> 
void BinaryTree<T>::add(const T &value)
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
	curr->_init(NULL,NULL,NULL);
    _Al.construct(&(curr->data),value);
    
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
	
	++size;
	
}

template<typename T>
void BinaryTree<T>::remove(T &key)
{	
	Node *z = findNode(key);
	Node *x,*y;

	if (!z)
		return;

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
void BinaryTree<T>::outputTree(ostream &O)
{

	outputTreeHelper(O,root,5);
}

template<typename T>
void BinaryTree<T>::outputTreeHelper(ostream &O,typename BinaryTree<T>::Node *r,int indent)
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
void BinaryTree<T>::destroy()
{
	destroyHelper(root);
}

template<typename T>
void BinaryTree<T>::destroyHelper(typename BinaryTree<T>::Node *&n)
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
void BinaryTree<T>::traverseTreePreOrder()
{	
	traverseTreeHelperPreOrder(this->root);
}

template<typename T>
void BinaryTree<T>::traverseTreeHelperPreOrder(typename BinaryTree<T>::Node *ptr)
{	
	if (!ptr)
		return;
	
	cout << ptr->data << "\n";

	traverseTreeHelperPreOrder(ptr->left);
	traverseTreeHelperPreOrder(ptr->right);
}

template<typename T>
void BinaryTree<T>::traverseTreePostOrder()
{	
	traverseTreeHelperPostOrder(this->root);
}

template<typename T>
void BinaryTree<T>::traverseTreeHelperPostOrder(typename BinaryTree<T>::Node *ptr)
{	
	if (!ptr)
		return;
	
	traverseTreeHelperPostOrder(ptr->left);
	traverseTreeHelperPostOrder(ptr->right);
	cout << ptr->data << "\n";

}

template<typename T>
void BinaryTree<T>::traverseTreeAscending()
{	
	traverseTreeHelperAscending(this->root);
}

template<typename T>
void BinaryTree<T>::traverseTreeHelperAscending(typename BinaryTree<T>::Node *ptr)
{	
	if (!ptr)
		return;
	traverseTreeHelperAscending(ptr->left);
		cout << ptr->data << "\n";
	traverseTreeHelperAscending(ptr->right);
}


template<typename T>
void BinaryTree<T>::traverseTreeDescending()
{	
	traverseTreeHelperDescending(this->root);
}

template<typename T>
void BinaryTree<T>::traverseTreeHelperDescending(typename BinaryTree<T>::Node *ptr)
{	
	if (!ptr)
		return;
	traverseTreeHelperDescending(ptr->right);
		cout << ptr->data << "\n";
	traverseTreeHelperDescending(ptr->left);
}

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::findNode(const T &key)
{
	Node *temp = root;

	while(temp)
		{	
			if (compare(key,temp->data)==EQUAL)
				return temp;
			else
				if (compare(key, temp->data)==GREATER)
					temp = temp->right;
			else
				if (compare(key, temp->data)==LOWER)
					temp = temp->left;
		}

	return 0;
}


template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::getOutmostRight(BinaryTree<T>::Node *nd)
{
	while(nd->right)
			nd = nd->right;
	
	return nd;

}

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::getOutmostLeft(BinaryTree<T>::Node *nd)
{
	while(nd->left)
			nd = nd->left;
	
	return nd;

}

#endif
