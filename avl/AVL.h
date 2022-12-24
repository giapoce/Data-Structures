#include <iostream>
#include <cassert>
#include <cstring>
 

// Algorithms based on D.Knuth - the art of computer programming

using namespace std;

template<class X>
int key_compare(const X &A, const X &B)
{
               if (A > B)
                  return 1;
               if (B > A)
                  return -1;
               if (A == B)
                  return 0;
}

int key_compare(char *A, char *B)
{
               int i = strcmp(A,B);
               return i;
}

#ifndef PAVL_H
#define PAVL_H

template<class X>
class pavl_node
{
      public:
             pavl_node() {pavl_link[0] = pavl_link[1] = pavl_parent = NULL;}
             pavl_node<X> *pavl_link[2];
             pavl_node<X> *pavl_parent;
             X pavl_data;
             signed char pavl_balance;      
             void operator=(const pavl_node<X> &p) {_Construct(&pavl_data,p->pavl_data);}
             pavl_node(const pavl_node<X> &p) {operator=(p);}
             
};

template<class X>
class pavl_table
{
      public:
             pavl_table() {pavl_root=NULL;}
             pavl_table(const pavl_table<X> &);
             void operator=(const pavl_table<X> &);
    		~pavl_table();
             void pavl_insert(const X &);
             void pavl_delete(const X &);
             pavl_node<X> *pavl_find(const X &);
             void pavl_output();
             const pavl_node<X> *_getRoot() const {return pavl_root;}		
      private:
             void _destroy(pavl_node<X> *);
    		 void _copy(const pavl_node<X> *);
             void p_output(pavl_node<X> *,int);
             pavl_node<X> *pavl_root;
             typedef allocator<X> alloc;      
             typedef typename alloc::template rebind< pavl_node<X> >::other __Ot; 
             //typedef allocator< pavl_node<X> > __Ot;
             __Ot __Nal;
	         alloc _Al;

};


template<class X>
pavl_table<X>::pavl_table(const pavl_table<X> &_Xt)
{
	pavl_root = NULL;
	_copy(_Xt._getRoot());
}

template<class X>
void pavl_table<X>::operator=(const pavl_table<X> &_Xt)
{
	_copy(_Xt._getRoot());
}

template<class X>
pavl_table<X>::~pavl_table()
{
	_destroy(pavl_root);
}

template<class X>
void pavl_table<X>::_destroy(pavl_node<X> *_Xn)
{
	if (!_Xn)
		return;

	_destroy(_Xn->pavl_link[0]);
	_destroy(_Xn->pavl_link[1]);

	_Al.destroy(&(_Xn->pavl_data));
	__Nal.deallocate(_Xn,1);
	_Xn = NULL;
	
}

template<class X>
void pavl_table<X>::_copy(const pavl_node<X> *_Xn)
{
	if (!_Xn)
		return;

	_copy(_Xn->pavl_link[0]);
	_copy(_Xn->pavl_link[1]);

	pavl_insert(_Xn->pavl_data);

}

template<class X>
pavl_node<X> *pavl_table<X>::pavl_find(const X &item) 
{ 
     
     pavl_node<X> *p;
     
     
     for (p = pavl_root; p != NULL;) 
         { 
           int cmp = key_compare (item, p->pavl_data);
               /*if (cmp < 0) 
                  p = p->pavl_link[0];
               else if (cmp > 0) 
                  p = p->pavl_link[1];
               else
                   return p; */
                   if (cmp == 0)
                     return p;
                   else
                       p = p->pavl_link[(cmp>0)]; 
               /* cmp == 0 */ 
               
          }
    
    return NULL;
}

template<class X>
void pavl_table<X>::pavl_insert (const X &item) 
{
       
       pavl_node<X> *y; /* Top node to update balance factor, and parent. */
       pavl_node<X> *p, *q; /* Iterator, and parent. */
       pavl_node<X> *n; /* Newly inserted node. */
       pavl_node<X> *w; /* New root of rebalanced subtree. */
       int dir; /* Direction to descend. */
        
       
       y = pavl_root;
       
       for (q = NULL, p = pavl_root; p != NULL; q = p, p = p->pavl_link[dir]) 
       { 
           int cmp = key_compare (item, p->pavl_data);
           
           if (cmp == 0)
              return;
           
           dir = (cmp > 0);
           
           if (p->pavl_balance != 0)
                  y = p;     
      }

n = (pavl_node<X> *)__Nal.allocate(1,(pavl_node<X>*) 0);

if (n == NULL)
   return;
           

           n->pavl_link[0] = n->pavl_link[1] = NULL;
           n->pavl_parent = q;
           _Al.construct(&n->pavl_data,item);

if (q != NULL)
   q->pavl_link[dir] = n;
else 
   pavl_root = n;

     n->pavl_balance = 0;
     if (pavl_root == n)
              return;

      for (p = n; p != y; p = q) 
          { 
             q = p->pavl_parent;
             dir = (q->pavl_link[0] != p);
                 if (dir == 0)
                    q->pavl_balance--;
                 else 
                    q->pavl_balance++;
          }
          
          
          if (y->pavl_balance == -2)
             { 
               
               pavl_node<X> *x = y->pavl_link[0];
               
               if (x->pavl_balance == -1)
                 { 

                 /*<Rebalance for - balance factor in PAVL insertion in left subtree>*/ 

                         w = x;
                         y->pavl_link[0] = x->pavl_link[1];
                         x->pavl_link[1] = y;
                         x->pavl_balance = y->pavl_balance = 0;
                         
                         x->pavl_parent = y->pavl_parent;
                         y->pavl_parent = x;
               
                         if (y->pavl_link[0] != NULL)
                            y->pavl_link[0]->pavl_parent = y;
                 } 
               else 
                 { 
                                       
                 /*<Rebalance for + balance factor in PAVL insertion in left subtree>*/
                 
                assert (x->pavl_balance == +1);
                
                w = x->pavl_link[1];
                x->pavl_link[1] = w->pavl_link[0];
                w->pavl_link[0] = x;
                y->pavl_link[0] = w->pavl_link[1];
                w->pavl_link[1] = y;
                
                if (w->pavl_balance == -1) 
                     x->pavl_balance = 0, y->pavl_balance = +1;
                else if (w->pavl_balance == 0) 
                     x->pavl_balance = y->pavl_balance = 0;
                else 
                     x->pavl_balance = -1, y->pavl_balance = 0;
                     
                     w->pavl_balance = 0;
                
                    w->pavl_parent = y->pavl_parent;
                    x->pavl_parent = y->pavl_parent = w;
                    
                    if (x->pavl_link[1] != NULL)
                       x->pavl_link[1]->pavl_parent = x;
                    
                    if (y->pavl_link[0] != NULL)
                       y->pavl_link[0]->pavl_parent = y;
                 
                 }             
                 
                 } 
          else if (y->pavl_balance == +2)
                  { 

                  /*<Rebalance PAVL tree after insertion in right subtree >*/  

                  pavl_node<X> *x = y->pavl_link[1];
                  
                  if (x->pavl_balance == +1)
                     { 
                            w = x;
                            y->pavl_link[1] = x->pavl_link[0];
                            x->pavl_link[0] = y;
                            x->pavl_balance = y->pavl_balance = 0;
                            x->pavl_parent = y->pavl_parent;
                            y->pavl_parent = x;
                          
                            if (y->pavl_link[1] != NULL)
                               y->pavl_link [1]->pavl_parent = y;
                          
                          /*<Rebalance for + balance factor in PAVL insertion in right subtree>*/
                          
                     } 
                      else 
                      { 
                           /*<Rebalance for - balance factor in PAVL insertion in right subtree>*/
                            assert (x->pavl_balance == -1);
                            
                            w = x->pavl_link[0];
                            
                            x->pavl_link[0] = w->pavl_link [1];
                            w->pavl_link[1] = x;
                            y->pavl_link[1] = w->pavl_link [0];
                            w->pavl_link[0] = y;
                  
                            if (w->pavl_balance == +1) 
                               x->pavl_balance = 0, y->pavl_balance = -1;
                            else if (w->pavl_balance == 0) 
                                 x->pavl_balance = y->pavl_balance = 0;
                            else 
                                 x->pavl_balance = +1, y->pavl_balance = 0;
                  
                                 w->pavl_balance = 0;
                                 
                                 w->pavl_parent = y->pavl_parent;
                                 x->pavl_parent = y->pavl_parent = w;
                                 
                                if (x->pavl_link[0] != NULL)
                                   x->pavl_link[0]->pavl_parent = x ;
                                if (y->pavl_link[1] != NULL)
                                   y->pavl_link[1]->pavl_parent = y;
                      }
                  
                  } 
          else 
               return;
          
          if (w->pavl_parent != NULL)
              w->pavl_parent->pavl_link [y != w->pavl_parent->pavl_link[0]] = w;
          else pavl_root = w;
          
          
}


template<class X>
void pavl_table<X>::pavl_delete (const X &item) 
{ 
     
     pavl_node<X> *p; /* Traverses tree to find node to delete. */
     pavl_node<X> *q; /* Parent of p. */
     int dir;      /* Side of q on which p is linked. */
    
    
    if (pavl_root == NULL)
       return;
    
    p = pavl_root;

    for (;;) 
        { 
             int cmp = key_compare (item, p->pavl_data);
             
             if (cmp == 0)
                break;
             
             dir = (cmp > 0);
             
             p = p->pavl_link[dir];
             
             if (p == NULL)
                return;
         }


q = p->pavl_parent;

if (q == NULL) 
 { 
      q = (pavl_node<X> *) &this->pavl_root;
      dir = 0;
 }

    if (p->pavl_link[1] == NULL)
        { 
                     
          q->pavl_link[dir] = p->pavl_link[0];
          
          if (q->pavl_link[dir] != NULL)
             q->pavl_link[dir]->pavl_parent = p->pavl_parent;

        } 
         else 
         {
             pavl_node<X> *r = p->pavl_link[1];
             
             if (r->pavl_link[0] == NULL)
                { 
                  
                  /*<Case 2 in PAVL deletion>*/ 
                    
                    r->pavl_link[0] = p->pavl_link[0];
                    q->pavl_link[dir] = r;
                    r->pavl_parent = p->pavl_parent;
                    
                    if (r->pavl_link[0] != NULL)
                       r->pavl_link[0]->pavl_parent = r;

                    r->pavl_balance = p->pavl_balance;
                    q = r;
                    dir = 1;
                } 
             else 
                { 
                  
                  /*<Case 3 in PAVL deletion>*/ 
                  
                  pavl_node<X> *s = r->pavl_link[0];
                    
                    while (s->pavl_link[0] != NULL)
                          s = s->pavl_link[0];
                           
                          r = s->pavl_parent;
                          
                    r->pavl_link[0] = s->pavl_link[1];
                    s->pavl_link[0] = p->pavl_link[0];
                    s->pavl_link[1] = p->pavl_link[1];
                    q->pavl_link[dir] = s;
                    
                    if (s->pavl_link[0] != NULL)
                       s->pavl_link[0]->pavl_parent = s;
                       
                       s->pavl_link[1]->pavl_parent = s;
                       s->pavl_parent = p->pavl_parent;
                       
                    if (r->pavl_link[0] != NULL)
                       r->pavl_link[0]->pavl_parent = r;
                                          
                    s->pavl_balance = p->pavl_balance;
                    q = r;
                    dir = 0;
                }
         }
     
     _Al.destroy(&(p->pavl_data));
     __Nal.deallocate(p,1);

    /*<Steps 3 and 4: Update balance factors and rebalance after PAVL deletion>*/
    
while (q != (pavl_node<X> *) &this->pavl_root) 
    { 
                pavl_node<X> *y = q;
                
                if (y->pavl_parent != NULL)
                    q = y->pavl_parent;
                else 
                     q = (pavl_node<X> *) &pavl_root;
             
        if (dir == 0) 
           { 
                
                dir = (q->pavl_link[0] != y);
                
                y->pavl_balance++;
                
                if (y->pavl_balance == +1)
                   break;
                else if (y->pavl_balance == +2)
                     { 
                       /*<Step 4: Rebalance after PAVL deletion>*/ 
                       
                          pavl_node<X> *x = y->pavl_link[1];
                          
                          if (x->pavl_balance == -1)
                          {           

                          /*<Left-side rebalancing case 1 in PAVL deletion>*/ 
                                   
                            assert(x->pavl_balance == -1);
                            
                            pavl_node<X> *w;
                            
                            w = x->pavl_link[0];
                            
                            x->pavl_link[0] = w->pavl_link[1];
                            w->pavl_link[1] = x;
                            y->pavl_link[1] = w->pavl_link[0];
                            w->pavl_link[0] = y;
                            
                            if (w->pavl_balance == +1) 
                               x->pavl_balance = 0, y->pavl_balance = -1;
                            else if (w->pavl_balance == 0) 
                                 x->pavl_balance = y->pavl_balance = 0;
                            else 
                                 x->pavl_balance = +1, y->pavl_balance = 0;
                                 
                                 w->pavl_balance = 0;
                                 
                                 w->pavl_parent = y->pavl_parent;
                                 x->pavl_parent = y->pavl_parent = w;
                                
                                if (x->pavl_link[0] != NULL)
                                   x->pavl_link[0]->pavl_parent = x;
                                   
                                if (y->pavl_link[1] != NULL)
                                   y->pavl_link[1]->pavl_parent = y; 
                                   
                                q->pavl_link[dir] = w;    
                                
                                    } 
                               else { 
                                    
                                    /*<Left-side rebalancing case 2 in PAVL deletion>*/ 
                                    
                                            y->pavl_link[1] = x->pavl_link[0];
                                            x->pavl_link[0] = y;
                                            x->pavl_parent = y->pavl_parent;
                                            y->pavl_parent = x;
                            
                                            if (y->pavl_link[1] != NULL)
                                               y->pavl_link[1]->pavl_parent = y;
                            
                                               q->pavl_link[dir] = x;
                            
                                            if (x->pavl_balance == 0) 
                                               { 
                                                       x->pavl_balance = -1;
                                                       y->pavl_balance = +1;
                                                       break;
                                               } 
                                            else 
                                               { 
                                                       x->pavl_balance = y->pavl_balance = 0;
                                                       y = x;
                                               }
                                    }
                       }
           }
           else 
               { 
                    /*<Steps 3 and 4: Symmetric case in PAVL deletion>*/ 
                    
                    dir = (q->pavl_link[0] != y);
                    y->pavl_balance--;
                    
                    if (y->pavl_balance == -1)
                         break;
                    else if (y->pavl_balance == -2) 
                         { 
                            pavl_node<X> *x = y->pavl_link[0];
                                if (x->pavl_balance == +1)
                                   { 
                                      
                                       /*<Right-side rebalancing case 1 in PAVL deletion>*/
                                        
                                        assert (x->pavl_balance == +1);
                                        pavl_node<X> *w;
                                        w = x->pavl_link[1];
                                        
                                        x->pavl_link[1] = w->pavl_link[0];
                                        w->pavl_link[0] = x;
                                        y->pavl_link[0] = w->pavl_link[1];
                                        w->pavl_link[1] = y;
                                        
                                        if (w->pavl_balance == -1) 
                                             x->pavl_balance = 0, y->pavl_balance = +1;
                                        else if (w->pavl_balance == 0) 
                                             x->pavl_balance = y->pavl_balance = 0;
                                        else 
                                             x->pavl_balance = -1, y->pavl_balance = 0;
                                        
                                            w->pavl_balance = 0;
                                        
                                            w->pavl_parent = y->pavl_parent;
                                            x->pavl_parent = y->pavl_parent = w;
                                            
                                            if (x->pavl_link[1] != NULL)
                                               x->pavl_link[1]->pavl_parent = x;
                                            
                                            if (y->pavl_link[0] != NULL)
                                               y->pavl_link[0]->pavl_parent = y;       
                                            
                                            q->pavl_link[dir] = w;
                                   } 
                                else 
                                   { 
                                           /*<Right-side rebalancing case 2 in PAVL deletion>*/ 
                                           
                                           y->pavl_link[0] = x->pavl_link[1];
                                           
                                            x->pavl_link[1] = y;
                                            x->pavl_parent = y->pavl_parent;
                                            y->pavl_parent = x;
                                            
                                            if (y->pavl_link[0] != NULL)
                                               y->pavl_link[0]->pavl_parent = y;
                                            
                                            q->pavl_link[dir] = x;
                                            
                                            if (x->pavl_balance == 0) 
                                               { 
                                                        x->pavl_balance = +1;
                                                        y->pavl_balance = -1;
                                                        break;
                                               } 
                                            
                                            else 
                                               { 
                                                        x->pavl_balance = y->pavl_balance = 0;
                                                        y = x;
                                               }
                                   }
                       
                       }
               }
        }
        

}


template<class X> 
void pavl_table<X>::pavl_output()
{
	p_output(pavl_root,0);
}

template<class X>  
void pavl_table<X>::p_output(pavl_node<X> *_x,int _off)
{
	if (!_x)
		return;

	p_output(_x->pavl_link[1],_off + 5);
    int j;
     
		for (j=0; j<_off; j++) 
            cout << " ";
	
			cout << _x->pavl_data << endl;
            
	p_output(_x->pavl_link[0],_off + 5);
}





#endif
