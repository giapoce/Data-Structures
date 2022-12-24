#ifndef ADAPTORS_H
#define ADAPTORS_H

template<class T>
class m_stack
{
	public:
		explicit m_stack() {}
		explicit m_stack(const m_stack<T> &s):items(s.items) {}
		m_stack<T> &operator=(const m_stack<T> &s) {if (this != &s) {items = s.items;} return (*this);}
		T &top() {return items.front();}
		const T &top() const {return items.front();}
		void pop() {items.pop_front();}
		void push(const T &v) {items.push_front(v);}
		bool IsEmpty() const {return items.IsEmpty();}
	private:
		m_list<T> items; 
};

template<class T>
class m_queue
{
	public:
		explicit m_queue() {}
		explicit m_queue(const m_queue<T> &q):items(q.items) {}
		m_queue<T> &operator=(const m_queue<T> &q) {if (this != &q) {items = q.items;} return (*this);}
		const T &top() const {return items.front();}
		T &top() {return items.front();}
		void dequeue() {items.pop_front();}
		void enqueue(const T &v) {items.push_back(v);}
		bool IsEmpty() const {return items.IsEmpty();}
	private:
		m_list<T> items; 
};

#endif
