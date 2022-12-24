#ifndef HASHLIST_H
#define HASHLIST_H

#include "List.h"

// A map class implemented with a skip list

class UnexistingKey
{
	public:
		UnexistingKey(char *m = "No valid key"):message(m) {}
		void print() const {std::cout << message << std::endl;}
	private:
		char *message;
};

template<class K, class V>
class HashList
{

	public:
		HashList() {}
		void insert(const K &, const V &);
		void erase(const K &);
		typedef ListNode<K, V> * nd;
		nd findKey(const K &);
		const V &operator[](const K &);
	private:
		List<K, V> _list;
};


template<class K, class V>
void HashList<K, V>::insert(const K &_key, const V &_value)
{	
	_list.insert(_key,_value);
}

template<class K, class V>
void HashList<K, V>::erase(const K &_key)
{	
	_list.erase(_key);
}

template<class K, class V>
const V &HashList<K, V>::operator[](const K &_key)
{
	
		nd _N = 0;
  		try
    		{
            _N = _list.getValue(_key);
	        	   if (!_N) throw UnexistingKey();
              }
         catch(UnexistingKey e)
                             {
                               e.print();
                               exit(0);
                             }
		return _N->data;
}

template<class K, class V>
typename HashList<K, V>::nd HashList<K, V>::findKey(const K &_key)
{
	
		nd _N = _list.getValue(_key);
		if (_N) return _N;

		return (0);
}


#endif
