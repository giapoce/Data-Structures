#ifndef HASHMAP_H
#define HASHMAP_H

#include "rbtree.h"

class UnexistingKey
{
	public:
		UnexistingKey(char *m = "No valid key"):message(m) {}
		void print() const {std::cout << message << std::endl;}
	private:
		const char *message;
};

//A map implemented with a red-black tree.

template<class K, class V>
class HashTree
{

	public:
		HashTree() {}
		void insert(const K &, const V &);
		void erase(const K &);
		typedef _xnode<K,V> * node;
		node findKey(const K &);
		const V operator[](const K &);
		const node Nil() const {return _tree._Nil();}
	private:
		_xtree <K, V> _tree;
};


template<class K, class V>
void HashTree<K, V>::insert(const K &_key, const V &_value)
{	
	_tree.insert(_key,_value);
}

template<class K, class V>
void HashTree<K, V>::erase(const K &_key)
{	
	_tree.remove(_key);
}

template<class K, class V>
const V HashTree<K, V>::operator[](const K &_key)
{
      node _N = 0;
      
	  try
        {
		          _N  = _tree._find_x_node(_key);
		 
                    if (_N == Nil())
                         throw UnexistingKey();  
                         
          }
       catch(UnexistingKey x)
             {
                           x.print();
                            return 0;
             }
           
		return _N->_data;
}

template<class K, class V>
typename HashTree<K, V>::node HashTree<K, V>::findKey(const K &_key)
{
	
		node _N = _tree._find_x_node(_key);
		return _N;

}


#endif
