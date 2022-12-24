#include<iostream>
 
using namespace std;

// A simple red-black tree using STL allocators;

template<class K>
	int compare(K A,K B)
		{
				if (A>B)
					return 1;
				if (A<B)
					return -1;
				if (A == B)
					return 0;
		}

int compare(char *A, char *B)
		{
			
			int i = strcmp(A,B);

			return i;
		}

enum _Color {_Red =1,_Black};
                    
template<class _K,class _T> 
struct _xnode
{
	public:
		_xnode *_left;
		_xnode *_right;
		_xnode *_parent;
		_Color _cl;
		void _init() {_left = _right = _parent = NULL; _cl = _Black; _Construct(&_key,_K()); _Construct(&_data,_T()); }
		bool _isFull() const {return ((_left != NULL) && (_right != NULL));}
		bool _isLeft() const {return ((_parent != NULL) && (this == _parent->_left));}
		bool _isRight() const {return ((_parent != NULL) && (this == _parent->_right));}
		void operator=(const _xnode<_K,_T> &_X) {_left = _X._left; _right = _X._right; _parent = _X._parent; _cl = _X._cl; _Construct(&(_key),_X._key); _Construct(&(_data),_X._data);}
		void _put(const _K &_k,const _T& _d) {_Construct(&(_key),_k); _Construct(&(_data),_d);}
		bool operator==(const _xnode<_K,_T> & _c) {return (compare(_c._key,_key)==0);}
		bool operator!=(const _xnode<_K,_T> & _c) {return !(_c == (*this));}
		_xnode(const _xnode<_K,_T> &_X) {operator=(_X);}
 		_xnode() {}
 		_T _data;
 		_K _key;
};      

 
template<class _X, class _Y>
struct _xtree
{
public:
       typedef int (*_Cmp) (_X,_X); 
       _Cmp key_compare;
	public:
		void operator=(const _xtree<_X,_Y> &);
		_xtree(_Cmp _Fptr = compare):key_compare(_Fptr) {_NIL = (_xnode<_X,_Y> *)_Al.allocate(1,(_xnode<_X,_Y> *)0); _NIL->_init(); _Root = _NIL;}
		_xtree(const _xtree<_X,_Y> &);
		~_xtree();
		void insert(const _X &,const _Y &);
		void remove(const _X &);
		void output();
		_xnode<_X,_Y> *_find_x_node(const _X &);
		_xnode<_X,_Y> *_getRoot() const {return _Root;}		
		_xnode<_X,_Y> *_Nil() const {return _NIL;}		
	private:
		void _destroy(_xnode<_X,_Y> *);
		void _copy(const _xnode<_X,_Y> *,const _xnode<_X,_Y> *);
		void _output(ostream &,_xnode<_X,_Y> *,size_t);
		void _Lrotate(_xnode<_X,_Y> *);
		void _Rrotate(_xnode<_X,_Y> *);
		void _insertFixup(_xnode<_X,_Y> *);
		void _deleteFixup(_xnode<_X,_Y> *);
		_xnode<_X,_Y> *_Root;
		_xnode<_X,_Y> *_NIL;
		allocator< _xnode<_X,_Y> > _Al;
};



template<class _X,class _Y>
_xtree<_X,_Y>::_xtree(const _xtree<_X,_Y> &_Xt):key_compare(_Xt.key_compare)
{
	_NIL = (_xnode<_X,_Y> *)_Al.allocate(1,(_xnode<_X,_Y> *)0); 
	_NIL->_init(); 
	_Root = _NIL;
	_copy(_Xt._getRoot(),_Xt._Nil());
}

template<class _X,class _Y>
void _xtree<_X,_Y>::operator=(const _xtree<_X,_Y> &_Xt)
{
	_copy(_Xt._getRoot(),_Xt._Nil());
}

template<class _X,class _Y>
_xtree<_X,_Y>::~_xtree()
{
	_destroy(_Root);
	_Al.deallocate(_NIL,1);
}

template<class _X,class _Y>
void _xtree<_X,_Y>::_destroy(_xnode<_X,_Y> *_Xn)
{
	if (!_Xn || (_Xn == _NIL))
		return;

	_destroy(_Xn->_left);
	_destroy(_Xn->_right);

	_Destroy(&(_Xn->_data));
	_Destroy(&(_Xn->_key));
	_Al.deallocate(_Xn,1);
	_Xn = NULL;
	
}

template<class _X,class _Y>
void _xtree<_X,_Y>::_copy(const _xnode<_X,_Y> *_Xn,const _xnode<_X,_Y> *_Xt)
{
	if (!_Xn || (_Xn == _Xt))
		return;

	_copy(_Xn->_left,_Xt);
	_copy(_Xn->_right,_Xt);

	insert(_Xn->_key,_Xn->_data);

}

template<class _X,class _Y>
void _xtree<_X,_Y>::insert(const _X &_s,const _Y &_t)
{
	 
		
	_xnode<_X,_Y> *_curr = 0;
	_xnode<_X,_Y> *_par = 0;

	_curr = _Root;
	

	while (_curr!=_NIL)
		{
			_par = _curr;

			if (key_compare(_s,_curr->_key)==0) return;
			
			if (key_compare(_s,_curr->_key)>0)
					_curr = _curr->_right;
			else
					_curr = _curr->_left;
		}
	
	_curr = (_xnode<_X,_Y> *)_Al.allocate(1,(_xnode<_X,_Y> *)0);  
	_curr->_left = _curr->_right = _NIL;
	_curr->_parent = NULL;
	_curr->_cl = _Red;
	_curr->_put(_s,_t);
	 
	if (_par != NULL)
		{
			if (key_compare(_s,_par->_key)>0)
					_par->_right = _curr;
			else
					_par->_left = _curr;

			_curr->_parent = _par;
		}
	else
		_Root = _curr;

	_insertFixup(_curr);

}

template<class _X,class _Y>
void _xtree<_X,_Y>::remove(const _X &_k)
{

	_xnode<_X,_Y> *z = _find_x_node(_k);
	_xnode<_X,_Y> *x,*y;

    
	if ((z == NULL) || (z == _NIL))
		return;

	if (z->_left == _NIL || z->_right == _NIL) 
         y = z;
	else 
		{
         y = z->_left;
         while (y->_right != _NIL) y = y->_right;
		}
 

     if (y->_left != _NIL)
         x = y->_left;
     else 
         x = y->_right;
 
		 x->_parent = y->_parent;

     if (y->_parent != NULL)
 			 if (y->_isLeft())
				 y->_parent->_left = x;
			else
				 y->_parent->_right = x;
      else
 			 _Root = x;
		
     if (y != z) 
			{
                _Destroy(&(z->_key));
				_Destroy(&(z->_data));
				z->_put(y->_key,y->_data);
			}
		
	 if (y->_cl == _Black)
		 _deleteFixup(x);

     _Destroy(&(y->_key)); 
	 _Destroy(&(y->_data)); 
     _Al.deallocate(y,1);
	 y = NULL;
	 
}

template<class _X,class _Y>
void _xtree<_X,_Y>::_Lrotate(_xnode<_X,_Y> *_x)
{
	
	 _xnode<_X,_Y> *y = _x->_right;
 
     _x->_right = y->_left;
     if (y->_left != _NIL) y->_left->_parent = _x;
 
     if (y != _NIL) y->_parent = _x->_parent;
     if (_x->_parent) 
	 {
         if (_x == _x->_parent->_left)
             _x->_parent->_left = y;
         else
             _x->_parent->_right = y;
     } 
	 else 
         _Root = y;
    
     y->_left = _x;
     if (_x != _NIL) _x->_parent = y;

}

template<class _X,class _Y>
void _xtree<_X,_Y>::_Rrotate(_xnode<_X,_Y> *_x)
{

	 _xnode<_X,_Y> *y = _x->_left;
 
     _x->_left = y->_right;
     if (y->_right != _NIL) y->_right->_parent = _x;

     if (y != _NIL) y->_parent = _x->_parent;
     if (_x->_parent) 
	 {
         if (_x == _x->_parent->_right)
             _x->_parent->_right = y;
         else
             _x->_parent->_left = y;
     } 
	 else 
         _Root = y;
     
     y->_right = _x;
     if (_x != _NIL) _x->_parent = y;

}

template<class _X,class _Y>
void _xtree<_X,_Y>::_insertFixup(_xnode<_X,_Y> *_x)
{

while (_x != _Root && _x->_parent->_cl == _Red) 
  {

          if (_x->_parent == _x->_parent->_parent->_left) 
		  {
             _xnode<_X,_Y> *y = _x->_parent->_parent->_right;
             if (y->_cl == _Red) 
			 {
 
                 _x->_parent->_cl = _Black;
                  y->_cl = _Black;
                 _x->_parent->_parent->_cl = _Red;
                 _x = _x->_parent->_parent;
             } 
			 else 
			 {
 
                  if (_x == _x->_parent->_right) 
				  {

					 _x = _x->_parent;
                     _Lrotate(_x);
                  }
 
                 _x->_parent->_cl = _Black;
                 _x->_parent->_parent->_cl = _Red;
                 _Rrotate(_x->_parent->_parent);
             }
         } 
		  else 
		  {
 
              _xnode<_X,_Y> *y = _x->_parent->_parent->_left;
             if (y->_cl == _Red) 
			 {

                 _x->_parent->_cl = _Black;
                  y->_cl = _Black;
                 _x->_parent->_parent->_cl = _Red;
                 _x = _x->_parent->_parent;
             } 
			 else 
			 {
 
                 if (_x == _x->_parent->_left) 
				 {
                     _x = _x->_parent;
                     _Rrotate(_x);
                 }
                 _x->_parent->_cl = _Black;
                 _x->_parent->_parent->_cl = _Red;
                 _Lrotate(_x->_parent->_parent);
             }
         }
     }

     _Root->_cl = _Black;

}

template<class _X,class _Y>
void _xtree<_X,_Y>::_deleteFixup(_xnode<_X,_Y> *_x)
{

	while (_x != _Root && _x->_cl == _Black) 
		 {

		 if (_x == _x->_parent->_left) 
		 {
             _xnode<_X,_Y> *w = _x->_parent->_right;
             if (w->_cl == _Red) 
			 {
                 w->_cl = _Black;
                 _x->_parent->_cl = _Red;
                 _Lrotate (_x->_parent);
                 w = _x->_parent->_right;
             }
             if (w->_left->_cl == _Black && w->_right->_cl == _Black) 
			 {
                 w->_cl = _Red;
                 _x = _x->_parent;
             } 
			 else 
			 {
                 if (w->_right->_cl == _Black) 
				 {
                     w->_left->_cl = _Black;
                     w->_cl = _Red;
                     _Rrotate (w);
                     w = _x->_parent->_right;
                 }
                 w->_cl = _x->_parent->_cl;
                 _x->_parent->_cl = _Black;
                 w->_right->_cl = _Black;
                 _Lrotate (_x->_parent);
                 _x = _Root;
             }
         } 
		 else 
		 {
             _xnode<_X,_Y> *w = _x->_parent->_left;
             if (w->_cl == _Red) 
			 {
                 w->_cl = _Black;
                 _x->_parent->_cl = _Red;
                 _Rrotate (_x->_parent);
                 w = _x->_parent->_left;
             }
             if (w->_right->_cl == _Black && w->_left->_cl == _Black) 
			 {
                 w->_cl = _Red;
                 _x = _x->_parent;
             } 
			 else 
				{
                 if (w->_left->_cl == _Black) 
				 {
                     w->_right->_cl = _Black;
                     w->_cl = _Red;
                     _Lrotate (w);
                     w = _x->_parent->_left;
                 }
                 w->_cl = _x->_parent->_cl;
                 _x->_parent->_cl = _Black;
                 w->_left->_cl = _Black;
                 _Rrotate (_x->_parent);
                 _x = _Root;
             }
         }
     }

     _x->_cl = _Black;

}


template<class _X,class _Y>
_xnode<_X,_Y> *_xtree<_X,_Y>::_find_x_node(const _X &_k)
{
	_xnode<_X,_Y> *_temp = _Root;

	while(_temp != _NIL)
		{	
			if (key_compare(_k,_temp->_key)==0)
				return _temp;
			else
				if (key_compare(_k, _temp->_key)>0)
					_temp = _temp->_right;
			else
				if (key_compare(_k, _temp->_key)<0)
					_temp = _temp->_left;
		}

	return _NIL;
}

template<class _X,class _Y>
void _xtree<_X,_Y>::output()
{
	_output(cout,_Root,0);
}

template<class _X,class _Y>
void _xtree<_X,_Y>::_output(ostream &_O,_xnode<_X,_Y> *_x,size_t _off)
{
	if (!_x || (_x == _NIL))
		return;

	_output(cout,_x->_right,_off + 5);

		for (size_t j=0; j<_off; j++) _O << " ";
	
			_O << _x->_data << endl;

	_output(cout,_x->_left,_off + 5);
}
