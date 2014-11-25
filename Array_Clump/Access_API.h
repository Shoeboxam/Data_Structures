#ifndef ACCESS_H
#define ACCESS_H


template<typename Type>
class Access_API {
protected:
public:
	int elements;

	Access_API(){
		elements = 0;
	}

	//Getters
	virtual Type& get(int index) = 0;
	virtual Type get(int index) const = 0;

	virtual int get_elements() const { return elements; }
	virtual bool is_empty() const { return elements == 0; }

	virtual Type front() const { return get(0); }
	virtual Type back() const { return get(elements - 1); }

	//Mutators
	bool push_back(Type value) { return insert(value, elements); }
	bool push_front(Type value) { return insert(value, 0); }

	bool pop_back() { return remove(elements - 1); }
	bool pop_front() { return remove(0); }

	virtual bool insert(Type value, int index) = 0;
	virtual bool remove(int index) = 0;

	virtual void fill(Type) = 0;
	virtual void clear() = 0;

	virtual void sort();
};

#include "Access_API.cpp"

#endif