#ifndef ALLOCATOR_H
#define ALLOCATOR_H

// A very simple allocator class.

template <typename T> class _allocator;

template <typename T> 
class _allocator
{

	public:
		typedef T _type;
		typedef T* _pointer;
		typedef T& _reference;
		typedef const T& _const_reference;
		typedef char * byte; 
		_allocator(){}
		~_allocator(){}
		_pointer allocate(unsigned int _size) {return (_pointer)(::operator new(_size * sizeof(_type)));}
		void deallocate(_pointer p) {::operator delete((void *)p);}
		void construct(_pointer p, _const_reference _v) {new((void *)p) _type(_v);}
		void destroy(_pointer p) {p->~_type();}
		template <typename U>
		         struct rebind { typedef _allocator<U> other; };

};

#endif
