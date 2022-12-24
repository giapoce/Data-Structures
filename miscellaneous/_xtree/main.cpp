#include<iostream>
#include<cstring>

// A simple red-black tree using STL allocators;

using namespace std;

// Generic comparator function

template<class K>
	int compare(const K &A, const K &B)
		{
				if (A>B)
					return 1;
				if (A<B)
					return -1;
				if (A==B)
					return 0;
		}

int compare(char *A, char *B)
		{
			
			int i = strcmp(A,B);
            return i;
				 
		}


enum _Color {_Red =1,_Black};
                    
template<class _T> 
struct _xnode
{
	public:
		_xnode *_left;
		_xnode *_right;
		_xnode *_parent;
		_Color _cl;
		void _init() {_left = _right = _parent = NULL; _cl = _Black;}
		bool _isFull() const {return ((_left != NULL) && (_right != NULL));}
		bool _isLeft() const {return ((_parent != NULL) && (this == _parent->_left));}
		bool _isRight() const {return ((_parent != NULL) && (this == _parent->_right));}
		void operator=(const _xnode<_T> &_X) {_left = _X._left; _right = _X._right; _parent = _X._parent; _cl = _X._cl; _Construct(&(_data),_X._Data);}
		_xnode(const _xnode<_T> &_X) {operator=(_X);}
 		_xnode() {}
 		_T _data;
};      

 
template<class _X>
struct _xtree
{
	public:
		typedef int (*_Cmp) (_X,_X); 
		void operator=(const _xtree<_X> &);
		_xtree(_Cmp _Fptr = compare):key_compare(_Fptr) {_NIL = (_xnode<_X> *)__Nal.allocate(1,(_xnode<_X> *)0); _NIL->_init(); _Root = _NIL;}
		_xtree(const _xtree<_X> &);
		~_xtree();
		void insert(const _X &);
		void remove(const _X &);
		void output();
		_xnode<_X> *_find_x_node(const _X &);
		const _xnode<_X> *_getRoot() const {return _Root;}		
		const _xnode<_X> *_Nil() const {return _NIL;}		
		_Cmp key_compare;
	private:
		void _destroy(_xnode<_X> *);
		void _copy(const _xnode<_X> *,const _xnode<_X> *);
		void _output(ostream &,_xnode<_X> *,size_t);
		void _Lrotate(_xnode<_X> *);
		void _Rrotate(_xnode<_X> *);
		void _insertFixup(_xnode<_X> *);
		void _deleteFixup(_xnode<_X> *);
		_xnode<_X> *_Root;
		_xnode<_X> *_NIL;
		typedef allocator<_X> alloc;
		typedef typename alloc::template rebind< _xnode<_X> >::other __Ot;
        __Ot __Nal;
	    alloc _Al;
};

template<class _X>
_xtree<_X>::_xtree(const _xtree<_X> &_Xt):key_compare(_Xt.key_compare)
{
	_NIL = (_xnode<_X> *)__Nal.allocate(1,(_xnode<_X> *)0); 
	_NIL->_init(); 
	_Root = _NIL;
	_copy(_Xt._getRoot(),_Xt._Nil());
}

template<class _X>
void _xtree<_X>::operator=(const _xtree<_X> &_Xt)
{
	_copy(_Xt._getRoot(),_Xt._Nil());
}

template<class _X>
_xtree<_X>::~_xtree()
{
	_destroy(_Root);
	__Nal.deallocate(_NIL,1);
}

template<class _X>
void _xtree<_X>::_destroy(_xnode<_X> *_Xn)
{
	if (!_Xn || (_Xn == _NIL))
		return;

	_destroy(_Xn->_left);
	_destroy(_Xn->_right);

	_Al.destroy(&(_Xn->_data));
	__Nal.deallocate(_Xn,1);
	_Xn = NULL;
	
}

template<class _X>
void _xtree<_X>::_copy(const _xnode<_X> *_Xn,const _xnode<_X> *_Xt)
{
	if (!_Xn || (_Xn == _Xt))
		return;

	_copy(_Xn->_left,_Xt);
	_copy(_Xn->_right,_Xt);

	insert(_Xn->_data);

}

template<class _X>
void _xtree<_X>::insert(const _X &_s)
{
	 
		
	_xnode<_X> *_curr = 0;
	_xnode<_X> *_par = 0;

	_curr = _Root;
	

	while (_curr!=_NIL)
		{
			_par = _curr;

			if (key_compare(_s,_curr->_data)==0) return;
			
			if (key_compare(_s,_curr->_data)>0)
					_curr = _curr->_right;
			else
					_curr = _curr->_left;
		}
	
	_curr = (_xnode<_X> *)__Nal.allocate(1,(_xnode<_X> *)0);  
	_curr->_left = _curr->_right = _NIL;
	_curr->_parent = NULL;
	_curr->_cl = _Red;
	_Al.construct(&(_curr->_data),_s);
	 
	if (_par != NULL)
		{
			if (key_compare(_s,_par->_data)>0)
					_par->_right = _curr;
			else
					_par->_left = _curr;

			_curr->_parent = _par;
		}
	else
		_Root = _curr;

	_insertFixup(_curr);

}

template<class _X>
void _xtree<_X>::remove(const _X &_k)
{

	_xnode<_X> *z = _find_x_node(_k);
	_xnode<_X> *x,*y;

    
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
				_Al.destroy(&(z->_data));
				_Al.construct(&(z->_data),(y->_data));
			}
		
	 if (y->_cl == _Black)
		 _deleteFixup(x);

	 _Al.destroy(&(y->_data)); 
     __Nal.deallocate(y,1);
	 y = NULL;
	 
}

template<class _X>
void _xtree<_X>::_Lrotate(_xnode<_X> *_x)
{
	
	 _xnode<_X> *y = _x->_right;
 
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

template<class _X>
void _xtree<_X>::_Rrotate(_xnode<_X> *_x)
{

	 _xnode<_X> *y = _x->_left;
 
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

template<class _X>
void _xtree<_X>::_insertFixup(_xnode<_X> *_x)
{

while (_x != _Root && _x->_parent->_cl == _Red) 
  {

          if (_x->_parent == _x->_parent->_parent->_left) 
		  {
             _xnode<_X> *y = _x->_parent->_parent->_right;
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
 
              _xnode<_X> *y = _x->_parent->_parent->_left;
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

template<class _X>
void _xtree<_X>::_deleteFixup(_xnode<_X> *_x)
{

	while (_x != _Root && _x->_cl == _Black) 
		 {

		 if (_x == _x->_parent->_left) 
		 {
             _xnode<_X> *w = _x->_parent->_right;
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
             _xnode<_X> *w = _x->_parent->_left;
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


template<class _X>
_xnode<_X> *_xtree<_X>::_find_x_node(const _X &_k)
{
	_xnode<_X> *_temp = _Root;

	while(_temp != _NIL)
		{	
			if (key_compare(_k,_temp->_data)==0)
				return _temp;
			else
				if (key_compare(_k, _temp->_data)>0)
					_temp = _temp->_right;
			else
				if (key_compare(_k, _temp->_data)<0)
					_temp = _temp->_left;
		}

	return _NIL;
}

template<class _X>
void _xtree<_X>::output()
{
	_output(cout,_Root,0);
}

template<class _X>
void _xtree<_X>::_output(ostream &_O,_xnode<_X> *_x,size_t _off)
{
	if (!_x || (_x == _NIL))
		return;

	_output(cout,_x->_right,_off + 5);

		for (size_t j=0; j<_off; j++) _O << " ";
	
			_O << _x->_data << endl;

	_output(cout,_x->_left,_off + 5);
}


void _putKey();
void _delKey();
void _getKey();
void _copyConstructor();
void _write_output();
void _clear_input(istream &);
void _cleanup();

int _strcmp(char *a,char *b)
{
	return (strcmp(a,b));
}

_xtree<char *> _x(_strcmp);
 
char *__xbuffer = 0;
char *__ybuffer = 0;
char *__zbuffer = 0;
allocator<char> _Xal;

int main()
{
  
	int _choice = 0;
	 
	 while (1)
		{
			_write_output();
			cin.sync();
			cin >> _choice;
			if (cin.fail())
					{
						_clear_input(cin);		  
						_choice = 0;
					}
			switch(_choice)
				{
					case 1:
						_putKey();
					break;
					case 2:
						_delKey();
					break;
					case 3:
						_getKey();
					break;
					case 4:
						_copyConstructor();
					break;
					default:
						cout << "Incorrect choice" << endl << endl;
					break;
				}
			 		
		}

	_cleanup();
		 
	return 0;
}

void _cleanup()
{
	if (__xbuffer) _Xal.deallocate(__xbuffer,1);	
	if (__ybuffer) _Xal.deallocate(__ybuffer,1);
	if (__zbuffer) _Xal.deallocate(__zbuffer,1);
}

void _clear_input(istream &_I)
{
		_I.clear();
		_I.sync();	 
}

void _write_output()
{
	
	cout << endl << "XTree 1.0 - Copyright: Gianmarco Iapoce 26/12/2004" << endl;
	cout << "1) Insert a key" << endl;
	cout << "2) Remove a key"<< endl;
	cout << "3) Find a key"<< endl;
	cout << "4) Copy constructor Assign operator Destructor"<< endl;
	cout << "Do your choice" << endl << endl;
	
}

void _putKey()
{

	 
	cin.sync();
 	
	 char *buffer = (char *)_Xal.allocate(25,(char *)0);
	 

	cout << "Insert a key" << endl;	
	cin.getline(buffer,25);
	__xbuffer = buffer;
 
	_x.insert(buffer);
	_x.output();
	 
}

void _delKey()
{

	 

	cin.sync();
	
	char *buffer = (char *)_Xal.allocate(25,(char *)0);

	cout << "Insert a key" << endl;	
	cin.getline(buffer,25);
	__ybuffer = buffer;

 
	_x.remove(__ybuffer);
	_x.output();
	 
}


void _getKey()
{

	 
	cin.sync();
	char *buffer = (char *)_Xal.allocate(25,(char *)0);
	

	cout << "Insert a key" << endl;	
	cin.getline(buffer,25);
	__zbuffer = buffer;
 
	_xnode<char *> *_z = _x._find_x_node((char *)buffer);

	if (_z != _x._Nil())
		cout << "Key found: " << _z->_data << endl;
	else
		cout << "Key not found" << endl;

	 
}


void _copyConstructor()
{
	_xtree<char *> _y(_x);

	 
	_xtree<char *> _z(_strcmp);
				   _z.insert("ciao");
 
	cout << "copy constructor" << endl;
	_y.output();

	  
	cout << "assign operator" << endl;
	_z = _y;
	_z.output();
	 
	
}
