#include <iostream>
#include <string>
#include <vector>
 
using namespace std;

struct __exception
{
       __exception() {}
       void print() {cout << "ERROR" << endl;}
};

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

template<class K> int HashCode(const K &_k) 
{
	int res = 0;
	int len = sizeof(K);
	const char *p = reinterpret_cast<const char  *>(&_k);
	while (len--)
		res = (res<<1)^*p++;
	return res;
} // to be overloaded

int HashCode(const std::string &_k) 
{
	int res = 0;
	
	string::const_iterator S = _k.begin();
	
	while (S != _k.end())
		res = (res << 1) ^ *S++; 

	return res;
} 


int HashCode(char *key) {
	
	unsigned long h = 0; 
	while(*key) {
		h = (h<<4) + *key++; 
		unsigned long g = h & 0xf0000000L; 
		if (g) {
			h^= g >> 24;
		} h &= ~g;
	} 
	return (h);

}


template<class _K,class _V>
struct entry
{
       _K _key;
       _V _value;
       void _init(const _K &_k,const _V _v) {_Construct(&_key,_k);_Construct(&_value,_v); _next = 0;}
       entry() {_init(_K(),_V());}
       entry(const entry<_K,_V> &c) {_Construct(&_key,c._key); _Construct(&_value,c._value); _next = c._next;}
       entry<_K,_V> *_next;
};

template<class _K,class _V>
class hashtable
{
      public:
             hashtable(int s = 997);
             hashtable(const hashtable<_K,_V> &);
             const hashtable<_K,_V> &operator=(const hashtable<_K,_V> &);
             ~hashtable();
             void insert(const _K &,const _V &);
             void erase(const _K &);
             entry<_K,_V> *find(const _K &);
             _V &operator[](const _K &);	
		     const _V &operator[](const _K &) const;
		     int size() const {return _buckets.size();}
      private:      
             void clear();
             void _copy(const hashtable<_K,_V> &);
             entry<_K,_V> *_node_allocate(const _K &,const _V &);
             void _node_deallocate(entry<_K,_V> *);
             vector< entry<_K,_V> *> _buckets;
             allocator< entry<_K,_V> > _node_allocator;
             int _size;                           
};

template<class _K,class _V>
hashtable<_K,_V>::hashtable(int _S):_size(_S)
{
    typedef entry<_K,_V> _Node;    
	_buckets.reserve(_S);
	_buckets.insert(_buckets.end(), _S, (_Node*) 0);
	cout << "DEFAULT CONSTRUCTOR" << endl;
}

template<class _K,class _V>
hashtable<_K,_V>::hashtable(const hashtable<_K,_V> &__Ht)
{
      _copy(__Ht);                                  
      _size = __Ht.size();
      cout << "COPY CONSTRUCTOR" << endl;
}

template<class _K,class _V>
const hashtable<_K,_V> &hashtable<_K,_V>::operator=(const hashtable<_K,_V> &__Ht)
{

if (this != &__Ht)
   {
          clear();
         _copy(__Ht);
         _size = __Ht.size();
   }
   
      cout << "ASSIGN OPERATOR" << endl;
   
      return (*this);      
}

template<class _K,class _V>
hashtable<_K,_V>::~hashtable()
{
   clear();
   cout << "DESTRUCTOR" << endl;
}

template<class _K,class _V>
void hashtable<_K,_V>::_copy(const hashtable<_K,_V> &__ht)
{
   typedef entry<_K,_V> _Node;
   
  _buckets.clear();
  _buckets.reserve(__ht._buckets.size());
  _buckets.insert(_buckets.end(), __ht._buckets.size(), (_Node*) 0);

  try {

    for (size_t __i = 0; __i < __ht._buckets.size(); ++__i) 
    {
      const _Node* __cur = __ht._buckets[__i];
      if (__cur) {
        _Node* __local_copy = _node_allocate(__cur->_key,__cur->_value); 
        _buckets[__i] = __local_copy;

        for (_Node* __next = __cur->_next;  __next; __cur = __next, __next = __cur->_next) 
        {
          __local_copy->_next = _node_allocate(__next->_key,__next->_value);
          __local_copy = __local_copy->_next;
        }
      }
    }
 
  }
  catch(...)
    {
      clear();
      throw __exception();
    }


}

template<class _K,class _V>
void hashtable<_K,_V>::insert(const _K &_k,const _V & _v)
{
     
     const size_t __n = HashCode(_k) % _size;
     typedef entry<_K,_V> _Node;
     _Node* __first = _buckets[__n];

  for (_Node* __cur = __first; __cur; __cur = __cur->_next) 
    if (compare(__cur->_key, _k)==0)
       {
           cout << "Key already existing" << endl;                  
           return;
       }

  _Node* __tmp = _node_allocate(_k,_v);
  __tmp->_next = __first;
  _buckets[__n] = __tmp;
 
  
}

template<class _K,class _V>
entry<_K,_V> *hashtable<_K,_V>::_node_allocate(const _K &_k,const _V &_v)
{
 
 entry<_K,_V> *_tmp;
             
         try{
             _tmp = _node_allocator.allocate(1,(entry<_K,_V>*)0); 
             if (_tmp)
                _tmp->_init(_k,_v);
             else
                  {
                   throw __exception();
                   exit(1);
                  }
             }
         catch(__exception e)
         {
                          e.print();
                          return NULL;
         }
         
         return _tmp;
                          
}

template<class _K,class _V>
void hashtable<_K,_V>::_node_deallocate(entry<_K,_V> *_Et)
{
  
         try
            {
              _Destroy(&(_Et->_key));
              _Destroy(&(_Et->_value));
              _node_allocator.deallocate(_Et,1); 
             }
         catch(...)
         {
                cout << "EXCEPTION OCCURED" << endl;           
         }
         
          
                          
}

template<class _K,class _V>
void hashtable<_K,_V>::erase(const _K &__key)
{
  typedef entry<_K,_V> _Node;
  
  const size_t __n = HashCode(__key) % _size;
  _Node* __first = _buckets[__n];
  
  if (__first) {
  
    _Node* __cur = __first;
    _Node* __next = __cur->_next;
  
    while (__next) {
      if (compare(__next->_key, __key)==0) {
        __cur->_next = __next->_next;
        _node_deallocate(__next);
        __next = __cur->_next;
      }
      else {
        __cur = __next;
        __next = __cur->_next;
      }
    }
    if (compare(__first->_key, __key)==0) {
      _buckets[__n] = __first->_next;
      _node_deallocate(__first);
    }
    
  }
     
}

template<class _K,class _V>
entry<_K,_V> *hashtable<_K,_V>::find(const _K &_k)
{
    typedef entry<_K,_V> _Node;
    
    size_t __n = HashCode(_k) % _size;
    _Node* __first = _buckets[__n];
    
    while (__first)
      {
          if (compare(__first->_key,_k)==0)
             break;
          else
            __first = __first->_next;
      }
      
    return __first;           
}

template<class _K,class _V>
void hashtable<_K,_V>::clear()
{

typedef entry<_K,_V> _Node;

for (size_t __i = 0; __i < _buckets.size(); ++__i) 
    {
        _Node* __cur = _buckets[__i];
    
        while (__cur != 0) 
              {
                    _Node* __next = __cur->_next;
                    _node_deallocate(__cur);
                    __cur = __next;
              }
        
          _buckets[__i] = 0;
          
      }
      _size = 0;
}


template<class _K,class _V>
_V &hashtable<_K,_V>::operator[](const _K &__key)
{
                                       			
	entry<_K,_V> *__Et = 0;

	try 
		{
			__Et = find(__key);
			if (!__Et) 
               throw __exception();
		}
	catch(__exception e)
		{
			e.print();		
			exit(1);
		}
			return __Et->_value;

}

template<class _K,class _V>
const _V &hashtable<_K,_V>::operator[](const _K &__key) const
{
 
	entry<_K,_V> *__Et = 0;

	try 
		{
			__Et = find(__key);
			if (!__Et) 
               throw __exception();
		}
	catch(__exception e)
		{
			e.print();		
			exit(1);
		}
			return __Et->_value;
	
}


