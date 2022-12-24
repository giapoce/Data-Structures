#ifndef LINK_H
#define LINK_H

template<class T> class vertex;

template<class T> 
class link
{ 
	
	public:
		link(vertex<T> * = NULL, bool=false, int=0);
		link(vertex<T> *, vertex<T> *, bool=false, int=0);
		link(const link<T> &);
		link<T> &operator=(const link<T> &);
		bool operator==(const link<T> &) const;
		bool operator>(const link<T> &) const;
		bool operator<(const link<T> &) const;
		bool operator!=(const link<T> &c) const {return !((*this) == c);}
		void setChecked() const {checked = true;}
		bool IsChecked() const {return checked;}
		T &getDest() const;
		T &getSrc() const;
		int getWeight() const {return weight;}
		void setWeight(int w) {weight=w;}
		vertex<T> *destination() const {return dest;} 
		vertex<T> *source() const {return src;} 
		void setSource(vertex<T> *sc) {src = sc;}
	private:
		int weight;
		vertex<T> *src;
		vertex<T> *dest;
		bool checked;
};

template<class T>
link<T>::link(vertex<T> *dst, bool c, int w):src(NULL),dest(dst),checked(c),weight(w) 
{

}

template<class T>
link<T>::link(vertex<T> *sc, vertex<T> *dst, bool c, int w):src(sc),dest(dst),checked(c),weight(w) 
{

}

template<class T>
link<T>::link(const link<T> &c):src(c.src),dest(c.dest),checked(c.checked),weight(c.weight) 
{

}

template<class T>
link<T> &link<T>::operator=(const link<T> &c)
{

	if (this != &c)
		{	
			src = c.src;
			dest = c.dest;
			weight = c.weight;
			checked = c.checked;
		}

	return (*this);
}


template<class T>
T &link<T>::getDest() const
{
	return dest->getData();
}

template<class T>
T &link<T>::getSrc() const
{
	return src->getData();
}

template<class T>
bool link<T>::operator==(const link<T> &c) const 
{
	return ((dest == c.dest) && (src == c.src) && (weight == c.weight) && (checked == c.checked));
}

template<class T>
bool link<T>::operator>(const link<T> &c) const 
{
	return (compare(dest->getData(),c.dest->getData())==GREATER);
}

template<class T>
bool link<T>::operator<(const link<T> &c) const 
{
	return (compare(dest->getData(),c.dest->getData())==LOWER);
}

#endif
