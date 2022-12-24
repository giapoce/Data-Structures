#include <iostream>
#include <vector>

#ifndef SMART_H
#define SMART_H

//Smart pointer with reference counting
using namespace std;

class RefCount
	{
	private:
		int references;

	public:
		RefCount() : references(0) {}
		virtual ~RefCount() {}
		virtual void inc() { ++references; }
		virtual void dec(void)
		{
			if (--references == 0)
			{
				delete this;
			}
		}
		virtual int count() {return references;}
	};

	 
	
	template <class T> class Ptr
	{
        
	private:
		T* _p;

	public:
		Ptr(const Ptr<T>& ptr) : _p(ptr._p) { if (_p) _p->inc(); }
		Ptr() : _p(0) {}
		Ptr(T* p) : _p(p) { if (_p) _p->inc(); }
		~Ptr(void) { if (_p) _p->dec(); }
		operator T*(void) const { return _p; }
		T& operator*(void) const { return *_p; }
		T* operator->(void) const { return _p; }
		Ptr& operator=(const Ptr<T> &p) { return operator=((T*)(Ptr<T>)p); }
		Ptr& operator=(T* p)
		{
			if (_p) _p->dec();
			_p = p;
			if (_p) _p->inc();
			return *this;
		}
		Ptr& operator=(const T* p)
		{
			return operator=((T*)p);
		}
		void dump() const { cout << _p << endl;}
         
 
	};

#endif

using namespace std;

class _Xt:public RefCount
	{
	
		public:
			 _Xt(int _x) {_ptr = new int(_x);}
			~_Xt() {cout << "Object being destroyed" << endl; delete _ptr;}
			int operator*(void) const { return *_ptr; }
		    int get_value() {return (int)*_ptr;}
        private:
		      int *_ptr;
        
			
	};

int main()
{

	Ptr<_Xt> _X(new _Xt(10));
	Ptr<_Xt> _Y(_X);
	Ptr<_Xt> _Z = _Y;
	Ptr<_Xt> ptr = new _Xt(11);
    
        
    vector< Ptr<_Xt> > vec;
    vec.push_back(_X);
    
    vector< Ptr<_Xt> >::iterator it =  vec.begin();


    int p = *(*(*it));
    cout  << p << endl;
    
    int s = *(*_X);
    cout << s << endl;
    
    int q = *(*ptr);
    cout << q << endl;
    
    ptr = _Y;

    q = *(*ptr);
    cout << q << endl;
    
    _X.dump(); _Y.dump(); _Z.dump(); ptr.dump();

    system("PAUSE");
	return 0;
}
