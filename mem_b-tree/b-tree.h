 #ifndef BTREEH_H
#define BTREEH_H

#include <fstream>
#include <iostream>
#include <cstring>
#include <stack>
#include <io.h>

 
using namespace std;


//copyright:  Gianmarco Iapoce 2004 
//Mostly based upon: 
//Introduction to Algorithms by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest
 
 
 
enum CMP {EQUAL = 2, GREATER = 3, LOWER = 4};

template<class K>
	CMP key_compare(const K A, const K B)
		{
            
            cerr << "General type" << endl;
            
				if (A>B)  return GREATER;
				if (A<B)  return LOWER;
				if (A==B) return EQUAL;
				
				return EQUAL;
		}
		
template<>
    CMP key_compare(const char *A, const char *B)
		{
            
            cerr << "char array" << endl;
            
			int i = strcmp(A,B);

				if (i>0)  return GREATER;
				if (i<0)  return LOWER;
				if (i==0) return EQUAL;
				
				return EQUAL;

		}
		
template<>
    CMP key_compare(const string A, const string B)
		{
            
            cerr << "string type" << endl;
            
			int i = strcmp(A.c_str(),B.c_str());

				if (i>0)  return GREATER;
				if (i<0)  return LOWER;
				if (i==0) return EQUAL;

				return EQUAL;

		}
		
template <class K, class T>
class dataKey
{
    
	public:
		dataKey(){}
		~dataKey(){/*_Destroy(&key); _Destroy(&data);*/}
		void operator=(const dataKey<K,T> &cp) {_Construct(&key,cp.key); _Construct(&data,cp.data);/*key=cp.key; data=cp.data;*/}
        dataKey(const K _key,const T _data){_Construct(&key,_key); _Construct(&data,_data); /*key=_key; data=_data;*/}
		dataKey(const dataKey<K,T> &cp) {operator=(cp);}
		bool operator>(const dataKey<K,T> &c) const {return (key_compare(key,c.key)==GREATER);}
		bool operator<(const dataKey<K,T> &c) const {return (key_compare(key,c.key)==LOWER);}
		bool operator==(const dataKey<K,T> &c) const {return (key_compare(key,c.key)==EQUAL);}
		const K &getKey() const {return key;}
		void setKey(const K &_k) {_Construct(&key,_k);/*key=_k;*/}
		const T &getData() const {return data;}
		void setData(const T &_d) {_Construct(&data,_d); /*data=_data;*/}
		K key;
		T data;

};


template<class K, class T, int M=5>
class xBTree
{
	
	public: class node;
	public: struct entry;
    public: struct data_record;
    
    public:
    
           typedef dataKey<K,T> data;          
           typedef node *nodePtr;   
           
            
           
           struct data_record
           {
                int order;
				int count;
				dataKey<K,T> keys[(2*M)-1];
				bool isLeaf;
                long adresses[2*M];
                int p_counter;
            };
           
	public:
		
		class node 
		{
			friend class xBTree<K,T,M>;
			 
			public:
				node(bool is_leaf){init(is_leaf);}				 
				node(){init(false);}
				void flush() {for (int j=0; j<rec.count; j++) {_Destroy(&(rec.keys[j].key)); _Destroy(&(rec.keys[j].data));}}
				void init(bool fg=false) {rec.order=M; rec.isLeaf=fg; rec.count=0; rec.p_counter=0; memset(children,0,sizeof(node *)*(2*M));memset(rec.adresses,0,sizeof(long)*(2*M));}
				int getCount() const {return rec.count;}
				void setCount(int n) {rec.count = n;}
				bool IsLeaf() {return rec.isLeaf;}
				void setLeaf(bool f) {rec.isLeaf = f;}
				const K getKey(int i) const {return rec.keys[i].getKey();}
				const T getData(int i) const {return rec.keys[i].getData();}
				node *getChildren(int i) const {return children[i];}
				data_record rec; 
			private: 
				 node *children[2*M];
		};
			struct entry
				{
					public:
						entry(node *n,int i) {page = n; index = i;}
						const T getData(int index) {return page->getData(index);}
						node *page;
						int	index;
				};

		xBTree();
		xBTree(const xBTree<K,T,M>&);
		~xBTree();
		const xBTree<K,T,M>& operator=(const xBTree<K,T,M>&);
		void insert(const dataKey<K,T>&);
		void erase(dataKey<K,T>);
		entry searchNode(const dataKey<K,T>&);
		void showTree();
		const node * _Root() const {return root;}
		long page_counter;
        nodePtr allocateNode(bool);
	private:
        typedef allocator<node> N_alloc;
        N_alloc _Nal;    
		void insertHelper(node *,const dataKey<K,T>&);
		void eraseHelper(node *,dataKey<K,T>);
		void borrowRight(node *,int,node *,node *);
		void borrowLeft(node *,int,node *,node *);
		void joinNodes(node *,int,node *,node *);
		node *findPred(node *);
		node *findSucc(node *);
		void keyDel(node *,int);
		void split(node *,int,node *);
		void showTreeHelper(node *,int);
		void loadTreeHelper(node *,int);
		void destroyHelper(node *);	
		void copyHelper(node *);
		const int b_order;
		node *root;
		const int MAX_ITEMS;
		const int MAX_CHILDREN;
		 
	
};

 
template<class K, class T, int M>
typename xBTree<K,T,M>::nodePtr xBTree<K,T,M>::allocateNode(bool f_g)
{
    try
       {
            nodePtr p = (nodePtr)_Nal.allocate(1,(nodePtr)0);
            if (!p)
                return ((nodePtr)0);
            
            p->init(f_g);
            p->rec.p_counter = (page_counter++);
             
            return p;
       }
    catch(...)
       {
            cerr << "Allocation failed" << endl;
       }
        
}

template<class K, class T, int M>
xBTree<K,T,M>::xBTree():b_order(M),MAX_ITEMS((2*M)-1),MAX_CHILDREN(2*M)
{
    
        
    page_counter=1;         
	root  = allocateNode(true);
	
	if (!root)
	       return;
	
	 
    
    
}


template<class K, class T, int M>
xBTree<K,T,M>::~xBTree()
{
 
	 destroyHelper(root);
       

}


template<class K, class T, int M>
xBTree<K,T,M>::xBTree(const xBTree<K,T,M> &cp):b_order(M),MAX_ITEMS((2*M)-1),MAX_CHILDREN(2*M)
{
 
	root  = allocateNode(true);
	 
	if (root)        
            copyHelper(cp.root);
                
      

}

template<class K, class T, int M>
const xBTree<K,T,M> &xBTree<K,T,M>::operator=(const xBTree<K,T,M> &cp)
{
 
	  if (&cp  != this)
		{
			if (cp.b_order == M)
				copyHelper(cp.root);
		}

	  return (*this);
 
}

template<class K, class T, int M>
void xBTree<K,T,M>::copyHelper(typename xBTree<K,T,M>::node *nd)
{
	if (!nd) 
		return;

		for (int i=0; i<=nd->rec.count; i++)
			if (!(nd->IsLeaf()))
				copyHelper(nd->children[i]);

			for (int j=0; j<nd->rec.count; j++)
				insert(nd->rec.keys[j]);

}

template<class K, class T, int M>
void xBTree<K,T,M>::destroyHelper(typename xBTree<K,T,M>::node *r)
{

	if (r != NULL)
		{
			for (int i=0; i<=r->rec.count; i++)
				destroyHelper(r->children[i]);
            
            r->flush();
			_Nal.deallocate(r,1);
			r=NULL;
		}
    
    
}

 
 
 

template<class K, class T, int M>
void xBTree<K,T,M>::insert(const dataKey<K,T> &dKey)
{
 
	if (!root)
		root = allocateNode(true);
	
    if (!root)
        return;		
 
 
  
	entry n = searchNode(dKey);

	if (n.page != NULL)
		{
			cout << "duplicate value" << endl;
			return;
		}
  
    
    	 	
    node *r = this->root;
     
	if (r->rec.count == MAX_ITEMS)
		{
			node *s = allocateNode(false);
			
			if (s)
			   {
                    
      
                    this->root = s;
        			s->children[0] = r;
        			s->rec.adresses[0] = r->rec.p_counter;  			
		          	split(s,0,r);
        			insertHelper(s,dKey);
                }
                
        		 
                    
                     
        }
	       else
		      	insertHelper(r,dKey);
		
        
}


template<class K, class T, int M>
void xBTree<K,T,M>::insertHelper(typename xBTree<K,T,M>::node *nd,const dataKey<K,T> &dKey)
{
 
 //non recursive insertion

 bool inserted = false;
  
 while (!inserted)
 {
  	int n = (nd->rec.count) - 1;

 	if (nd->IsLeaf())
		{
			 
			while (n>=0 && dKey < nd->rec.keys[n]) 
				{	
					nd->rec.keys[n+1] = nd->rec.keys[n];
					n--;
				}
				
				nd->rec.keys[n+1] = dKey;
				nd->rec.count++;
				inserted = true;
							    	 
			
		}
	
	else
		{
 			
			
			while (n>=0 && dKey<nd->rec.keys[n]) n--;
			
			++n;
			
 
  
			if (nd->children[n]->rec.count == MAX_ITEMS)
				{

					split(nd,n,nd->children[n]);
					
 					if (dKey>nd->rec.keys[n])
							n++;

 							
				}
            

            	nd = nd->children[n]; 
            	//insertHelper(nd->children[n],dKey);
			 
	}

 }

}
 

template<class K, class T, int M>
void xBTree<K,T,M>::split(typename xBTree<K,T,M>::node *x,int w, node *y)
{
  
  
   

	 node *z = allocateNode(y->IsLeaf());
	 
	 if (!z)
	    return;
	    
	 int xc = x->rec.count;

	 z->rec.count = b_order-1;

	 for (int j = 0; j<(b_order-1); j++)
			z->rec.keys[j] = y->rec.keys[j + b_order];
		

	 if (!y->IsLeaf())
			for (int i=0; i<b_order; i++)
					{
                        z->children[i] = y->children[i + b_order];
                        z->rec.adresses[i] = y->rec.adresses[i + b_order];
                    }
					 

	y->rec.count = b_order-1; 
	

	for (int k = xc; k>w; k--)
	     {
		    x->children[k+1] = x->children[k];
		    x->rec.adresses[k+1] = x->rec.adresses[k];
          }

	x->children[w+1] = z;
	x->rec.adresses[w+1] = z->rec.p_counter;
     
      
     
	for (int t = xc-1; t>=w; t--)
			x->rec.keys[t+1]=x->rec.keys[t];
		

	 x->rec.keys[w]=y->rec.keys[b_order-1];
	  
	 x->rec.count = xc+1;
      
      
}

 
template<class K, class T, int M>
void xBTree<K,T,M>::erase(dataKey<K,T> dKey)
{
 

	node *r = this->root;
	
	if (!r)
			{
				std::cout << "Tree is empty" << std::endl;
				return;
			}

	eraseHelper(r,dKey); 
	
	if (r->rec.count==0)
			{
				node *y = this->root;
				this->root = this->root->children[0];
				y->flush();
				_Nal.deallocate(y,1);
			}	

}

template<class K, class T, int M>
void xBTree<K,T,M>::eraseHelper(typename xBTree<K,T,M>::node *nd,dataKey<K,T> dKey)
{

main_loop:
	int i = 0;
	
	while (i<=nd->rec.count-1 && dKey>nd->rec.keys[i])
		i++;

	
		if (i<=nd->rec.count-1 && dKey==nd->rec.keys[i])
			{	
				
				if (nd->IsLeaf())
					{
						std::cout << "case 1: deletion from a leaf" << std::endl;
						keyDel(nd,i);
						return;	
					}	
		
				else  
					{	
					
					cerr << "A leaf node: " << (i+1) << endl;
					
					if (nd->children[i]->rec.count>=b_order)
						{
							    
                                std::cout << "case 2a: replacement by predecessor" << std::endl;
							    node *s = findPred(nd->children[i]);
							    dataKey<K,T> predKey = s->rec.keys[s->rec.count-1];
							    nd->rec.keys[i] = s->rec.keys[s->rec.count-1];	 
							    nd=nd->children[i];
							    
							    dKey=predKey;
							    goto main_loop;
							    return;

                                //goto replaces the recoursive routine
                                //eraseHelper(nd->children[i],predKey);
                                  
						}
					else if (nd->children[i+1]->rec.count>=b_order)
							{
								
                                std::cout << "case 2b: replacement by successor" << std::endl;
								node *s = findSucc(nd->children[i+1]);
								dataKey<K,T> succKey = s->rec.keys[0];
								nd->rec.keys[i] = s->rec.keys[0];
								nd=nd->children[i+1];
								
                                dKey=succKey;
							    goto main_loop;
								return;

								//goto replaces the recoursive routine
                                //eraseHelper(nd->children[i+1],succKey);
								
							}
					else if ((nd->children[i]->rec.count==b_order-1) && (nd->children[i+1]->rec.count==b_order-1))
							{
								
                                std::cout << "case 2c: join" << std::endl;
								joinNodes(nd,i,nd->children[i],nd->children[i+1]);
								nd=nd->children[i];
								
							    goto main_loop;
								return;

								//goto replaces the recoursive routine
                                //eraseHelper(nd->children[i],dKey);
                                
								
							}
											
					}
			}

			if (!nd->IsLeaf())
				{
					if (nd->children[i]->rec.count==b_order-1)
						{
	
								
								
								if (i>0 && nd->children[i-1]->rec.count>=b_order)	
									{										
										std::cout << "case 3a: left borrow" << std::endl;
										borrowRight(nd,i-1,nd->children[i-1],nd->children[i]);					 
									}
								else if (i<nd->rec.count && nd->children[i+1]->rec.count>=b_order)
									{										
										std::cout << "case 3b: right borrow" << std::endl;
										borrowLeft(nd,i,nd->children[i],nd->children[i+1]);										 
										
									}							
								else if (i>0 && nd->children[i-1]->rec.count == b_order-1)
									{
										 
 										std::cout << "case 3c: left join" << std::endl;
										joinNodes(nd,i-1,nd->children[i-1],nd->children[i]);
										i--;
									}
								else if (i<nd->rec.count && nd->children[i+1]->rec.count == b_order-1)
									{										 
										std::cout << "case 3d: right join" << std::endl;
										joinNodes(nd,i,nd->children[i],nd->children[i+1]);	 
									}

							
						}
					       
					       
					       nd=nd->children[i];
						   goto main_loop;
						   
						 //goto replaces the recoursive routine  
						 //eraseHelper(nd->children[i],dKey);
			}		

													 				
}

template<class K, class T, int M>
void xBTree<K,T,M>::borrowRight(typename xBTree<K,T,M>::node *x,int i,typename xBTree<K,T,M>::node *y,typename xBTree<K,T,M>::node *z)
{
	
	int n = z->rec.count-1;

	for (int w = n; w>=0; w--)			
			z->rec.keys[w+1]=z->rec.keys[w];
			

	if (!(z->IsLeaf()))
		for (int t=z->rec.count; t>=0; t--)
			{
                z->children[t+1] = z->children[t];
                z->rec.adresses[t+1] = z->rec.adresses[t];
             }


	z->rec.keys[0]=x->rec.keys[i];
	x->rec.keys[i]=y->rec.keys[y->rec.count-1];
	

	if (!(z->IsLeaf()))
		{
            z->children[0] = y->children[y->rec.count];
            z->rec.adresses[0] = y->rec.adresses[y->rec.count];
        }

	y->children[y->rec.count] = NULL;
    y->rec.adresses[y->rec.count]=0;
    
	y->rec.count--;
	z->rec.count++;

}

template<class K, class T, int M>
void xBTree<K,T,M>::borrowLeft(typename xBTree<K,T,M>::node *x,int i,typename xBTree<K,T,M>::node *y,typename xBTree<K,T,M>::node *z)
{

 
	y->rec.keys[y->rec.count]=x->rec.keys[i];
	x->rec.keys[i]=z->rec.keys[0];

	y->rec.count++;

	if (!(y->IsLeaf()))
		{
            y->children[y->rec.count] = z->children[0];
            y->rec.adresses[y->rec.count] = z->rec.adresses[0];
        }

	for (int t=0; t<z->rec.count-1; t++)
		z->rec.keys[t]=z->rec.keys[t+1];

		 
	if (!(z->IsLeaf()))
		for (int m=0; m<z->rec.count; m++)
			{
                z->children[m] = z->children[m+1];
                z->rec.adresses[m] = z->rec.adresses[m+1];
            }
	
		z->children[z->rec.count] = NULL;
		z->rec.adresses[z->rec.count] = 0;


	z->rec.count--;
}

template<class K, class T, int M>
void xBTree<K,T,M>::joinNodes(typename xBTree<K,T,M>::node *x,int i,typename xBTree<K,T,M>::node *y,typename xBTree<K,T,M>::node *z)
{
	
		y->rec.keys[b_order-1]=x->rec.keys[i];
		
		
		for (int t=0; t < b_order-1; t++)
				y->rec.keys[t + b_order]=z->rec.keys[t];
				

		if (!(y->IsLeaf()))
			for (int m=0; m < b_order; m++)
				{
                    y->children[m + b_order] = z->children[m];
                    y->rec.adresses[m + b_order] = z->rec.adresses[m];
                }
		
	
		y->rec.count = 2 * b_order-1;

		keyDel(x,i);
        
        z->flush();
		_Nal.deallocate(z,1);
	    

}

template<class K, class T, int M>
void xBTree<K,T,M>::keyDel(typename xBTree<K,T,M>::node *x,int i)
{

	 
	for (int t=i; t<x->rec.count-1; t++)
		x->rec.keys[t]=x->rec.keys[t+1];

	if (!(x->IsLeaf()))
		for (int z=i+1; z<x->rec.count; z++)
			{
                x->children[z] = x->children[z+1];
                x->rec.adresses[z] = x->rec.adresses[z+1];
            }
	
	x->children[x->rec.count] = NULL;
	x->rec.adresses[x->rec.count] = 0;
 

	x->rec.count--;
	 
}

template<class K, class T, int M>
typename xBTree<K,T,M>::node *xBTree<K,T,M>::findPred(typename xBTree<K,T,M>::node *x)
{
	while (!(x->IsLeaf()))
		x = x->children[x->rec.count];

	return x;
}

template<class K, class T, int M>
typename xBTree<K,T,M>::node *xBTree<K,T,M>::findSucc(typename xBTree<K,T,M>::node *x)
{

	while (!(x->IsLeaf()))
		x = x->children[0];

	return x;
}

 

template<class K, class T, int M>
typename xBTree<K,T,M>::entry xBTree<K,T,M>::searchNode(const dataKey<K,T> &dKey)
{
  
	node *temp = root;
	
	//Iterative search

	while (temp != NULL)
		{
				
			int i=temp->rec.count-1;
		  
		     while ((i>=0) && dKey<temp->rec.keys[i]) i--;
			
			 if (i>=0 && temp->rec.keys[i]==dKey)
				return entry(temp,i); 
			 
			 if (temp->IsLeaf())
				 return entry((node *)NULL,0);
			  
			temp = temp->children[i+1];		
		}		 
		 
 

	return entry((node *)NULL,0);
 
}



template<class K, class T, int M>
void xBTree<K,T,M>::showTree()
{
 
	 
	std::cout << std::endl;
	showTreeHelper(root,0);	 
	std::cout << std::endl;
	
}

template<class K, class T, int M>
void xBTree<K,T,M>::showTreeHelper(typename xBTree<K,T,M>::node *nd,int l)
{
 
    if (!nd)
     return;
     
      if (nd->rec.count>0)
	    {

            for (int j=0; j<l*2; j++) cout << " ";
	        std::cout << "LEVEL " << l << ": ";


            for (int x = 0; x<=nd->rec.count; x++)
				{
                    if (x<nd->rec.count) std::cout << "{" << nd->rec.p_counter << "}" << " (" << nd->rec.keys[x].getKey() << " - " << nd->rec.keys[x].getData() << ") \t";
		            std::cout << nd->rec.adresses[x] << "\t";


                }

            std::cout << std::endl;

        }


        if (!nd->IsLeaf())
        {
             	for (int i=0; i<=nd->rec.count; i++)
        			 {
                            showTreeHelper(nd->children[i],l+1);
                                                        
                     }
                     	 
        }



	  

 
	 		
	 	
}

 
 

#endif
