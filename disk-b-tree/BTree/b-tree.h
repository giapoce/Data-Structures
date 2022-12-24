#ifndef BTREEH_H
#define BTREEH_H
 
#include <fstream>
#include <iostream>
#include <cstring>
#include <list>
#include <stack>
#include <map>
#include <sys/stat.h> 

//Copyright Gianmarco Iapoce Milan Italy
//Last update 04/03/2010

#undef DEBUG


#define MAX_KEY_LENGTH 256
#define MAX_FILE_NAME 256


using namespace std; 
enum CMP {EQUAL = 2, GREATER = 3, LOWER = 4};


template< class K, class T, int M=5 > class xBTree;
typedef char byte;


bool FileExists(string strFilename) { 

  struct stat stFileInfo; 
  bool blnReturn; 
  int intStat; 

  intStat = stat(strFilename.c_str(),&stFileInfo); 
  if(intStat == 0) { 
    blnReturn = true; 
  } else { 
    blnReturn = false; 
  } 
   
  return(blnReturn); 
}




template<class K>
	CMP key_compare( K &A,  K &B)
		{
				 
				
			if (A>B) 
                    return GREATER;
			else if (A<B) 
                    return LOWER;
                 

				return EQUAL;
		}
		



 template <class K>
 class DBObject
 {
 public:
 		DBObject(){k_size=0;}
		DBObject(const DBObject<K> &cp) {k_size=0; operator=(cp);}

		void operator=(const DBObject<K> &cp) 
		{
			
			memset(key,0,sizeof(K));
			k_size=sizeof(K);
			memcpy(key, &cp.key, sizeof(K));	
			
		}


		DBObject(const K& _key)
		{
			
			memset(key,0,sizeof(K));
			k_size=sizeof(K);
			memcpy(key, &_key, sizeof(K));
			
		}
		

		bool operator>(const DBObject<K> &c) const {return (key_compare(*(K *)key,*(K *)c.key)==GREATER);}
		bool operator<(const DBObject<K> &c) const {return (key_compare(*(K *)key,*(K *)c.key)==LOWER);}
		bool operator==(const DBObject<K> &c) const {return (key_compare(*(K *)key,*(K *)c.key)==EQUAL);}
		
		const K getKey() {return *(K *)key;}		 
		byte key[sizeof(K)];
		
		int k_size;
		
 
 };

template<>
class DBObject<string>
{

	public:
 		DBObject(){k_size=0; memset(key,0,MAX_KEY_LENGTH+1);}
		DBObject(const DBObject<string> &cp) {k_size=0;  operator=(cp);}

		void operator=(const DBObject<string> &cp) 
		{
			
			int len=cp.k_size;
			k_size=len;
						
			if ( len > MAX_KEY_LENGTH )
                   {
                    cerr << "Max key length allowed is " << MAX_KEY_LENGTH << endl;
                    len=MAX_KEY_LENGTH;
                   }  

			memset(key,0,MAX_KEY_LENGTH+1);
            	memcpy(key,cp.key,len);
            	key[len]='\0';
					       
  
		}

        
		DBObject(const string& _key)
		{
			
			int len=_key.length();
			k_size=len;
						
		   if ( len > MAX_KEY_LENGTH )
                {
                    cerr << "Max key length allowed is " << MAX_KEY_LENGTH << endl;
                    len=MAX_KEY_LENGTH;
                }	
            
            memset(key,0,MAX_KEY_LENGTH+1);
            memcpy(key,_key.c_str(),len);
            key[len]='\0';
            
			
		}

		bool operator>(const DBObject<string> &c) const {return (strcmp(c.key,key)>0);}
		bool operator<(const DBObject<string> &c) const {return (strcmp(c.key,key)<0);}
		bool operator==(const DBObject<string> &c) const {return (strcmp(c.key,key)==0);}
		
		const char *getKey() {return static_cast<char *>(key);}
		
		byte key[MAX_KEY_LENGTH+1];
		int k_size;
};


template <class K, class T>
class dataKey
{

	public:
 		dataKey(){}
		dataKey(const dataKey<K,T> &cp) {operator=(cp);}

		void operator=(const dataKey<K,T> &cp) 
		{
				key=cp.key;
				data=cp.data;
		}

        

		dataKey(const K& _key, const T& _data)
		{
				key=_key;
				data=_data;
		}
		

		bool operator>(const dataKey<K,T> &c) const {return (c.key>key);}
		bool operator<(const dataKey<K,T> &c) const {return (c.key<key);}
		bool operator==(const dataKey<K,T> &c) const {return (c.key==key);}
		
		const K getKey() {return key.getKey();}
		const T getData() {return data.getKey();}
		 
		DBObject<K> key;
		DBObject<T> data;

	

};




template<class K, class T, int M=5>
class DiskManager 
        {
			
		typedef typename xBTree<K,T,M>::file_header s_header;
		typedef typename xBTree<K,T,M>::node page;

		   public:
                DiskManager(char *, xBTree<K,T,M> *);
                ~DiskManager();
                fstream dbFile;
		    s_header f_header;
                void printTree();
                void DiskWrite(page *, long);
                void DiskFree(long);
                page* DiskRead(long);
		    void readRecord(page *,long);
		    void WriteHeader(s_header *);
                page *GetNode(bool);
                long page_counter;
		    stack < long > free_blocks;
                stack < page * > read_blocks;
		    stack < page *> print_blocks; 
		    map <long,page *> allocated_blocks;

            private:
                void printTreeHelper(page *,int);
                char file_name[MAX_FILE_NAME+1];
                xBTree<K,T,M> *btree;
};

  
 

template<class K, class T, int M>
class xBTree
{
	

	public: class node;
	public: struct entry;
	public: struct file_header;
   

    public:

	
           typedef dataKey<K,T> data;          
           typedef node *nodePtr;   
           
           struct file_header
           {
                long root_pos;
                long pg_counter; 
           };
           
           struct node
           {
                int order;
		    int count;
		    dataKey<K,T> keys[(2*M)-1];
		    bool isLeaf;
                long adresses[2*M];
                node *children[2*M];
		    long offset;
				
            };
           
            
		
		typedef DiskManager<K,T,M> dskManager;

		
            struct entry
			 {
					public:
						entry(node *n,int i) {page = n; index = i;}
						const T getData(int index) {return page->keys[index].getData();}
						node *page;
						int	index;
			};
        
        
		xBTree(char *);
		~xBTree();
		void insert(dataKey<K,T>);
		void erase(dataKey<K,T>);
		entry searchNode(const dataKey<K,T>&);
		void showTree();
		node *getRoot() const {return root;}
		void setRoot(node *n) {root = n;}
        dskManager *getDisk() {return disk;}
		void printTree() {disk->printTree();}
	private:
        dskManager *disk;
		void insertHelper(node *,dataKey<K,T>);
		void eraseHelper(node *,dataKey<K,T>);
		void borrowRight(node *,int,node *,node *);
		void borrowLeft(node *,int,node *,node *);
		void joinNodes(node *,int,node *,node *);
		node *findPred(node *);
		node *findSucc(node *);
		void keyDel(node *,int);
		void split(node *,int,node *);
		const int b_order;
		node *root;
		const int MAX_ITEMS;
		const int MAX_CHILDREN;
		 
	
};

 



template<class K, class T, int M>
xBTree<K,T,M>::xBTree(char *f_name):b_order(M),MAX_ITEMS((2*M)-1),MAX_CHILDREN(2*M)
{
    
    disk = new dskManager(f_name,this);
	   
        
}


template<class K, class T, int M>
xBTree<K,T,M>::~xBTree()
{
 

    
    	disk->WriteHeader(&(disk->f_header));
		delete disk;
	  
	 
       
}


 

template<class K, class T, int M>
void xBTree<K,T,M>::insert(dataKey<K,T> dKey)
{
 
 
	
	entry n = searchNode(dKey);

	if (n.page != NULL)
		{
			cerr << "duplicate value" << endl;
			return;
		}
  
 
	node *r = this->root;

	 
	if (r->count == MAX_ITEMS)
		{

			node *s = disk->GetNode(false);
            	long rt_pos;
            			     

                        this->root = s;
				s->children[0] = r;
        			s->adresses[0] = r->offset;
        			rt_pos = s->offset;
		          	split(s,0,r);
        			insertHelper(s,dKey);
              
                    
                    disk->f_header.root_pos = rt_pos;
                    disk->WriteHeader(&(disk->f_header));

                     
        }
	       else
		      	insertHelper(r,dKey);
		


        
}


template<class K, class T, int M>
void xBTree<K,T,M>::insertHelper(node *nd,dataKey<K,T> dKey)
{
 

bool inserted = false;
int n=0;

while (!inserted)
{
  	n = (nd->count) - 1;
	
 	if (nd->isLeaf)
		{
			 
			while (n>=0 && dKey < nd->keys[n]) 
				{	
					
					nd->keys[n+1] = nd->keys[n];
					n--;
				}
				
				nd->keys[n+1] = dKey;
				nd->count++;
				
			    	 
                long pos = nd->offset;
                disk->DiskWrite(nd,pos);
				inserted = true;
			
		}
	
	else
		{
 			
			
			while (n>=0 && dKey<nd->keys[n]) n--;
			
			++n;
			
			 
			long childPos = nd->adresses[n];
			nd->children[n] = disk->DiskRead(childPos);
			
			  
			if (nd->children[n]->count == MAX_ITEMS)
				{

					split(nd,n,nd->children[n]);
			 
					if (dKey>nd->keys[n])
							{
                               

                                n++;     
								long offset = nd->adresses[n];
                                nd->children[n] = disk->DiskRead(offset);
                                
                                
			                 }
			                 
							
				}
            
              	
            	nd = nd->children[n];
            	
			 
		}
 
 }
	
}
 

template<class K, class T, int M>
void xBTree<K,T,M>::split(node *x,int w,node *y)
{
  


	 node *z = disk->GetNode(y->isLeaf);
	 
	 if (!z)
	    return;

	 int xc = x->count;

	 z->count = b_order-1;

	 for (int j = 0; j<(b_order-1); j++)
			z->keys[j] = y->keys[j + b_order];
		

	 if (!y->isLeaf)
			for (int i=0; i<b_order; i++)
					{
                        z->children[i] = y->children[i + b_order];
                        z->adresses[i] = y->adresses[i + b_order];
                    }
					 

	y->count = b_order-1; 
	

	for (int k = xc; k>w; k--)
	     {
		    x->children[k+1] = x->children[k];
		    x->adresses[k+1] = x->adresses[k];
          }

	x->children[w+1] = z;
	x->adresses[w+1] = z->offset;
     
      
     
	for (int t = xc-1; t>=w; t--)
			x->keys[t+1]=x->keys[t];
		

	 x->keys[w]=y->keys[b_order-1];
	  
	 x->count = xc+1;

     long leftChildPos = y->offset;
     long newChildPos = z->offset;
     long parentPos = x->offset;
    

     disk->DiskWrite(y,leftChildPos);
     disk->DiskWrite(z,newChildPos);
     disk->DiskWrite(x,parentPos);
     
     
      
}

 
template<class K, class T, int M>
void xBTree<K,T,M>::erase(dataKey<K,T> dKey)
{
 
 
	node *r = this->root;
	
	if (r->count==0)
			{
				std::cout << "Tree is empty" << std::endl;
				return;
			}
	
	eraseHelper(r,dKey); 
	
	if (r->count==0)
			{
			
				long hdr_size = sizeof(file_header);
				long pg_size = sizeof(node);
				
				node *y=this->root;
                 		
				long ch_pos = this->root->adresses[0];
				
 				if (ch_pos)	 
					 {
	
    					this->root->children[0] = disk->DiskRead(ch_pos);	
						long new_root = this->root->children[0]->offset;
						 
						this->root = this->root->children[0];
						disk->f_header.root_pos = new_root;				
						disk->WriteHeader(&(disk->f_header));
 
					 
                            
					       disk->DiskFree(y->offset);
					       y=NULL;  
                    }		
                    
					
			}	

		
}

template<class K, class T, int M>
void xBTree<K,T,M>::eraseHelper(node *nd,dataKey<K,T> dKey)
{

main_loop:
    
	int i = 0;
	
	while (i<=nd->count-1 && dKey>nd->keys[i])
		i++;

	
		if (i<=nd->count-1 && dKey==nd->keys[i])
			{	
				
				if (nd->isLeaf)
					{

#ifdef DEBUG
						std::cout << "case 1: deletion from a leaf" << std::endl;
#endif
						keyDel(nd,i);
						long nodePos = nd->offset;
						disk->DiskWrite(nd,nodePos);
						return;	
						
					}	
		
				else  
					{	
					
						long i_pos = nd->adresses[i];
						long i_succ_pos = 0;

						nd->children[i] = disk->DiskRead(i_pos);
						
						
						      
    						if (i<nd->count)
    							i_succ_pos = nd->adresses[i+1];
    						if (i_succ_pos)
    							nd->children[i+1] = disk->DiskRead(i_succ_pos);
                        
                    
                    
					if (nd->children[i]->count>=b_order)
						{
							    
#ifdef DEBUG
                                std::cout << "case 2a: replacement by predecessor" << std::endl;
#endif							    
								
							node *s = findPred(nd->children[i]);
						      dataKey<K,T> predKey = s->keys[s->count-1];
							nd->keys[i] = s->keys[s->count-1];	 					 
								
							   long offset = nd->offset;
							   disk->DiskWrite(nd,offset);
								 
							    nd=nd->children[i];
							    dKey=predKey;

							    goto main_loop;
							    return;
							     

                                 
                                  
						}
					else if (nd->children[i+1]->count>=b_order)
							{

#ifdef DEBUG
                                std::cout << "case 2b: replacement by successor" << std::endl;
#endif 								
								
								node *s = findSucc(nd->children[i+1]);			
								dataKey<K,T> succKey = s->keys[0];								
								nd->keys[i] = s->keys[0];	
								
								long offset = nd->offset;
								disk->DiskWrite(nd,offset);
				
								nd=nd->children[i+1];
                                dKey=succKey;

							      goto main_loop;
								return; 

								 
								
							}
					else if ((nd->children[i]->count==b_order-1) && (nd->children[i+1]->count==b_order-1))
							{

#ifdef DEBUG
                                std::cout << "case 2c: join" << std::endl;
#endif
								joinNodes(nd,i,nd->children[i],nd->children[i+1]);
								nd=nd->children[i];
								
							      goto main_loop;
								return;

								 
							}
											
					}
			}

			if (!nd->isLeaf)
				{

					long i_pos = nd->adresses[i];
					nd->children[i] = disk->DiskRead(i_pos);
						
						 
					if (nd->children[i]->count==b_order-1)
						{
	
							long i_succ_pos = 0;
							long i_prev_pos = 0;
							
							if (i>0)
								i_prev_pos = nd->adresses[i-1];
							if (i<nd->count)
								i_succ_pos = nd->adresses[i+1];

							if (i_prev_pos) 
								nd->children[i-1] = disk->DiskRead(i_prev_pos);
							if (i_succ_pos)
								nd->children[i+1] = disk->DiskRead(i_succ_pos);

							if (i>0 && nd->children[i-1]->count>=b_order)	
								   {										
#ifdef DEBUG								
									    std::cout << "case 3a: left borrow" << std::endl;
#endif
										borrowRight(nd,i-1,nd->children[i-1],nd->children[i]);					 
									}
							else if (i<nd->count && nd->children[i+1]->count>=b_order)
									{										
#ifdef DEBUG
										std::cout << "case 3b: right borrow" << std::endl;
#endif
										borrowLeft(nd,i,nd->children[i],nd->children[i+1]);										 
										
									}							
							else if (i>0 && nd->children[i-1]->count == b_order-1)
									{
										 
#ifdef DEBUG
										std::cout << "case 3c: left join" << std::endl;
#endif
										joinNodes(nd,i-1,nd->children[i-1],nd->children[i]);
										i--;
										long  new_offset = nd->adresses[i];
										nd->children[i] = disk->DiskRead(new_offset);

									}
							else if (i<nd->count && nd->children[i+1]->count == b_order-1)
									{										 
#ifdef DEBUG	
										std::cout << "case 3d: right join" << std::endl;
#endif
										joinNodes(nd,i,nd->children[i],nd->children[i+1]);	 
									}

							
						}
					       
					       
					       nd=nd->children[i];
						   goto main_loop;
						   
						  
			}		

													 				
}

template<class K, class T, int M>
void xBTree<K,T,M>::borrowRight(node *x,int i,node *y,node *z)
{
	
	int n = z->count-1;

	for (int w = n; w>=0; w--)			
			z->keys[w+1]=z->keys[w];
			

	if (!z->isLeaf)
		for (int t=z->count; t>=0; t--)
			{
                z->children[t+1] = z->children[t];
                z->adresses[t+1] = z->adresses[t];
             }


	z->keys[0]=x->keys[i];
	x->keys[i]=y->keys[y->count-1];
	

	if (!z->isLeaf)
		{
            z->children[0] = y->children[y->count];
            z->adresses[0] = y->adresses[y->count];
        }

	y->children[y->count] = NULL;
    y->adresses[y->count]=0;
    
	y->count--;
	z->count++;

	long x_addr = x->offset;
	long y_addr = y->offset;
	long z_addr = z->offset;

	disk->DiskWrite(x,x_addr);
	disk->DiskWrite(y,y_addr);
	disk->DiskWrite(z,z_addr);


}

template<class K, class T, int M>
void xBTree<K,T,M>::borrowLeft(node *x,int i,node *y,node *z)
{

 
	y->keys[y->count]=x->keys[i];
	x->keys[i]=z->keys[0];

	y->count++;

	if (!y->isLeaf)
		{
            y->children[y->count] = z->children[0];
            y->adresses[y->count] = z->adresses[0];
        }

	for (int t=0; t<z->count-1; t++)
		z->keys[t]=z->keys[t+1];

		 
	if (!z->isLeaf)
		for (int m=0; m<z->count; m++)
			{
                z->children[m] = z->children[m+1];
                z->adresses[m] = z->adresses[m+1];
            }
	
		z->children[z->count] = NULL;
		z->adresses[z->count] = 0;


	z->count--;

	long x_addr = x->offset;
	long y_addr = y->offset;
	long z_addr = z->offset;

	disk->DiskWrite(x,x_addr);
	disk->DiskWrite(y,y_addr);
	disk->DiskWrite(z,z_addr);

}

template<class K, class T, int M>
void xBTree<K,T,M>::joinNodes(node *x,int i,node *y,node *z)
{
	
		y->keys[b_order-1]=x->keys[i];
		
		
		for (int t=0; t < b_order-1; t++)
                    y->keys[t + b_order]=z->keys[t];
            
				

		if (!y->isLeaf)
			for (int m=0; m < b_order; m++)
				{
                    y->children[m + b_order] = z->children[m];
                    y->adresses[m + b_order] = z->adresses[m];
                }
		
	
		y->count = 2 * b_order-1;

		keyDel(x,i);
		
		long x_addr = x->offset;
		long y_addr = y->offset;
		long z_addr = z->offset;

		disk->DiskWrite(x,x_addr);
		disk->DiskWrite(y,y_addr);	
		disk->DiskFree(z_addr);
        
        
        
		
}

template<class K, class T, int M>
void xBTree<K,T,M>::keyDel(node *x,int i)
{

	 
	for (int t=i; t<x->count-1; t++)
		x->keys[t]=x->keys[t+1];

	if (!x->isLeaf)
		for (int z=i+1; z<x->count; z++)
			{
                x->children[z] = x->children[z+1];
                x->adresses[z] = x->adresses[z+1];
            }
	
	x->children[x->count] = NULL;
	x->adresses[x->count] = 0;
 

	x->count--;
	 
}

template<class K, class T, int M>
typename xBTree<K,T,M>::node *xBTree<K,T,M>::findPred(node *x)
{
	while (!x->isLeaf)
		{
			long pred_Pos = x->adresses[x->count];
			x->children[x->count] = disk->DiskRead(pred_Pos);
			x = x->children[x->count];
		}

	return x;
}

template<class K, class T, int M>
typename xBTree<K,T,M>::node *xBTree<K,T,M>::findSucc(node * x)
{

	while (!x->isLeaf)
		{
			long succ_Pos = x->adresses[0];
			x->children[0] = disk->DiskRead(succ_Pos);
			x = x->children[0];
		}

	return x;
}

 

template<class K, class T, int M>
typename xBTree<K,T,M>::entry xBTree<K,T,M>::searchNode(const dataKey<K,T> &dKey)
{
  
	node *temp = root;
	
              
	while (temp != NULL)
		{
				
			int i=temp->count-1;
		  
		     while ((i>=0) && dKey<temp->keys[i]) i--;
			
			 if (i>=0 && temp->keys[i]==dKey)
				return entry(temp,i); 
			 
			 if (temp->isLeaf)
				 return entry((node *)NULL,0);
			  
			  long offset = temp->adresses[i+1];
              temp = disk->DiskRead(offset);
               
              
		}		 
		 
 

	return entry((node *)NULL,0);
 
}



 
 
template<class K, class T, int M>
DiskManager<K,T,M>::~DiskManager()
{

    typedef typename map<long,page *>::iterator itr;
	itr it = allocated_blocks.begin();

	while ( it != allocated_blocks.end() )
			{
					
                    page *curr = (it)->second;
					it++;
                    delete(curr);
					
			}
	
	
	  
		  while (!read_blocks.empty())
				{
						delete read_blocks.top();
						read_blocks.pop();
				}
   

            dbFile.flush();
            dbFile.close();
}


template<class K, class T, int M>
typename xBTree<K,T,M>::node *DiskManager<K,T,M>::GetNode(bool f_g)
{
     	   
		    
		   page *p = new page();
           if (!p)
                return ((page *)0);
            
			p->count=0;
			p->isLeaf=f_g;
			p->order=M;
				
			memset(p->children,0,sizeof(page *)*(2*M));
			memset(p->adresses,0,sizeof(long)*(2*M));
			
			if (free_blocks.empty())
                {
                        p->offset = sizeof(s_header) + ((page_counter-1) * sizeof(page));
                        f_header.pg_counter = page_counter++;
                }
            else
                {
                        p->offset = free_blocks.top();
                        free_blocks.pop();
                }
                
            
			 
			return allocated_blocks.insert(make_pair(p->offset,p)).first->second;      
             


}



template<class K, class T, int M>
void DiskManager<K,T,M>::DiskWrite(page *data, long offset)
{

	 
    long pg_size =  sizeof(page);
     
	
    dbFile.seekp(0,ios::beg);
	 if (dbFile.bad())
	    {
            cerr << "I/O error" << endl;
            dbFile.clear();
            dbFile.close();
            return;
        }
		

	dbFile.seekp(offset,ios::beg);
    if (dbFile.bad())
	    {
            cerr << "I/O error" << endl;
            dbFile.clear();
            dbFile.close();
            return;
        }

    dbFile.write((char *)data,pg_size);
    if (dbFile.bad())
	    {
            cerr << "Error writing data to disk" << endl;
            dbFile.clear();
            dbFile.close();
            return;
        }

    dbFile.flush();

}


template<class K, class T, int M>
void DiskManager<K,T,M>::readRecord(page *buffer,long offset)
{


    long pg_size =  sizeof(page);

	
    dbFile.seekg(0,ios::beg);
	 if (dbFile.bad())
	    {
            cerr << "I/O error" << endl;
            dbFile.clear();
            dbFile.close();
            return;
        }
		
    
    dbFile.seekg(offset,ios::beg);
    if (dbFile.bad())
            {
                cerr << "I/O error" << endl;
                dbFile.clear();
                dbFile.close();
                return;
            }
 
    
    dbFile.read((char *)buffer,pg_size);
	if (dbFile.bad())
            {
                cerr << "Error reading data from disk" << endl;
                dbFile.clear();
                dbFile.close();
                return;
            }



}
 

template<class K, class T, int M>
typename xBTree<K,T,M>::node* DiskManager<K,T,M>::DiskRead(long offset)
{
    typedef typename map<long,page *>::iterator itr;
    itr it = allocated_blocks.find(offset);
    if ( it != allocated_blocks.end() ) 
    return (it)->second;

    page * buffer = new page;

    long pg_size =  sizeof(page);
    
                	
	dbFile.seekg(0,ios::beg);
	 if (dbFile.bad())
	    {
            cerr << "I/O error" << endl;
            dbFile.clear();
            dbFile.close();
            return (page *)NULL;
        }
		
    
    dbFile.seekg(offset,ios::beg);
    if (dbFile.bad())
            {
                cerr << "I/O error" << endl;
                dbFile.clear();
                dbFile.close();

                return (page *)NULL;
            }


    dbFile.read((char *)(buffer),pg_size);
	if (dbFile.bad())
            {
                cerr << "Error reading data from disk" << endl;
                dbFile.clear();
                dbFile.close();

                return (page *)NULL;
            }
 
  
	 read_blocks.push(buffer);
	 return buffer;


}


template<class K, class T, int M>
void DiskManager<K,T,M>::DiskFree(long offset)
{

           page blank;
	       blank.count=0;
	       blank.offset=0;
	       blank.isLeaf=0;
	       blank.order=0;

	       memset(blank.keys,0,sizeof(dataKey<K,T>)*((2*M)-1));
	       memset(blank.children,0,sizeof(page *)*(2*M));
	       memset(blank.adresses,0,sizeof(long)*(2*M));
	       
           DiskWrite(&blank,offset);
	       allocated_blocks.erase(offset);
           free_blocks.push(offset);

	       

}
 
template<class K, class T, int M>
void DiskManager<K,T,M>::printTree()
{
      
		typedef typename list<page *>::iterator tit;
        s_header tmp_f_header;
        
		long hdr_size = sizeof(s_header);
        long pg_size = sizeof(page);
		
		page *buffer =  new page;
		
         
        dbFile.seekg(0,ios::beg);
        if (dbFile.bad())
    	    {
                cerr << "I/O error" << endl;
                dbFile.clear();
                dbFile.close();
                return;
            }
    
        dbFile.read((char *)&tmp_f_header,hdr_size);
        if (dbFile.bad())
    	    {
                cerr << "Error reading data from disk - bad header" << endl;
                dbFile.clear();
                dbFile.close();
                return;
            }
        
       
        long r_pos=tmp_f_header.root_pos;


        dbFile.seekg(r_pos,ios::beg);
        if (dbFile.bad())
    	    {
                cerr << "I/O error" << endl;
                dbFile.clear();
                dbFile.close();
                return;
            }
        
   
     
        dbFile.read((char *)(buffer),pg_size);    
        if (dbFile.bad())
    	    {
                cerr << "Error reading data from disk - corrupted root" << endl;
                dbFile.clear();
                dbFile.close();
                return;
            }	           
       
		print_blocks.push(buffer);
		printTreeHelper(buffer,0);

		while (!print_blocks.empty())
		{
			delete print_blocks.top();
			print_blocks.pop();
		}

 
}

template<class K, class T, int M>
void DiskManager<K,T,M>::printTreeHelper(page *nd,int l)
{
	 
	    
      if (nd->count>0)
	    {

             for (int j=0; j<l*2; j++) cout << " ";
	           std::cout << "LEVEL " << l << ": ";

              
               for (int x = 0; x<=nd->count; x++)
				{
                    if (x<nd->count) std::cout << "{" << nd->offset << "}" << " (" << nd->keys[x].getKey() << " - " << nd->keys[x].getData() << ") \t";
		            std::cout << nd->adresses[x] << "\t";


                }


        }

        
        std::cout << std::endl;

        if (!nd->isLeaf)
        {

             	for (int i=0; i<=nd->count; i++)
        			 {

                             long pos = nd->adresses[i];

                                
                                  if (pos)
                                    {
									  
									  
									  page *buf = new page; 
                                      readRecord(buf,pos);
									  print_blocks.push(buf);
                                      printTreeHelper(buf,l+1);
                                      

                                   }

                     }


            

        }
      
}

 
 
template<class K, class T, int M>
void DiskManager<K,T,M>::WriteHeader(s_header *f)
{
    
       long hdr_size = sizeof(s_header);
        
        dbFile.seekp(0,ios::beg);
        if (dbFile.bad())
    	    {
                cerr << "I/O error" << endl;
                dbFile.clear();
                dbFile.close();
                return;
            }

        dbFile.write((char *)f,hdr_size);
        if (dbFile.bad())
    	    {
                cerr << "Error writing header data to disk" << endl;
                dbFile.clear();
                dbFile.close();
                return;
            }
     
		dbFile.flush();    
       
}

template<class K, class T, int M>
DiskManager<K,T,M>::DiskManager(char *f_name, xBTree<K,T,M> *_btree)
{
    
    btree = _btree;
       
    long hdr_size = sizeof(s_header);
    long pg_size =  sizeof(page);
    size_t len = strlen(f_name);

	memset(file_name,0,MAX_FILE_NAME+1);

    if (len > MAX_FILE_NAME)
        {
            cout << "Name is too long" << endl;
            return;
        }

    strcpy(file_name,f_name);
    bool creating = !FileExists(file_name);
    
    
if (creating)
 {
    

    page_counter=1;

    dbFile.open(file_name,ios::in|ios::out|ios::trunc|ios::binary);
    if (dbFile.fail())
        {
            cerr << "Failed to open output file" << endl;
            dbFile.clear();
            dbFile.close();
            return;
        }
    
    
    page *new_root = GetNode(true);
    if (!new_root)
        return;
        
    btree->setRoot(new_root);
    
    page *curr_root_rec = btree->getRoot();
    f_header.root_pos = curr_root_rec->offset;
    f_header.pg_counter = page_counter;


    dbFile.seekp(0,ios::beg);
	if (dbFile.bad())
	    {
            cerr << "I/O error" << endl;
            dbFile.clear();
            dbFile.close();
            return;
        }

    dbFile.write((char *)&f_header,hdr_size);
	if (dbFile.bad())
	    {
            cerr << "Error writing data to disk" << endl;
            dbFile.clear();
            dbFile.close();
            return;
        }

    long nodePos = f_header.root_pos;

	dbFile.seekp(nodePos,ios::beg);
	if (dbFile.bad())
	    {
            cerr << "I/O error" << endl;
            dbFile.clear();
            dbFile.close();
            return;
        }

    dbFile.write((char *)curr_root_rec,pg_size);
	if (dbFile.bad())
	    {
            cerr << "Error writing data to disk" << endl;
            dbFile.clear();
            dbFile.close();
            return;
        }

 dbFile.flush(); 
 

}
else
    {
     
        page *buffer = new page;

        dbFile.open(file_name,ios::in | ios::out | ios::binary);
        if (dbFile.fail())
            {
                cerr << "Failed to open output file" << endl;
                dbFile.clear();
                dbFile.close();
                return;
            }


        dbFile.seekg(0,ios::beg);
    	if (dbFile.bad())
    	    {
                cerr << "I/O error" << endl;
                dbFile.clear();
                dbFile.close();
                return;
            }

        dbFile.read((char *)&f_header,hdr_size);
	    if (dbFile.bad())
	    {
            cerr << "Error reading data from disk - reopening" << endl;
            dbFile.clear();
            dbFile.close();
            return;
        }

        page_counter = f_header.pg_counter;
        long r_pos = f_header.root_pos;		
		page_counter++;

        dbFile.seekg(r_pos,ios::beg);
    	  if (dbFile.bad())
    	    {
                cerr << "I/O error" << endl;
                dbFile.clear();
                dbFile.close();
                return;
            }

        

	    dbFile.read((char *)(buffer),pg_size);
	    if (dbFile.bad())
	    {
            cerr << "Error reading data from disk" << endl;
            dbFile.clear();
            dbFile.close();
            return;
          }
        

        
		 read_blocks.push(buffer);
		 btree->setRoot(buffer);
        
    }
    
 
}


#endif
