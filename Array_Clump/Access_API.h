#ifndef ACCESS_H
#define ACCESS_H


template<typename Type>
class Access_API {
protected:
public:
	int length, elements;

	Access_API(){
		length = 1;
		elements = 0;
	}

	//Getters
	virtual Type get(int index) = 0;

	virtual int get_length() const { return length; }
	virtual int get_elements() const { return elements; }
	virtual bool is_empty() const { return elements == 0; }

	virtual Type front() { return get(0); }
	virtual Type back() { return get(elements - 1); }

	//Mutators
	bool push_back(Type value) { return insert(value, elements); }
	bool push_front(Type value) { return insert(value, 0); }

	bool pop_back() { return remove(elements - 1); }
	bool pop_front() { return remove(0); }

	virtual bool insert(Type value, int index) = 0;
	virtual bool remove(int index) = 0;

	virtual void fill(Type) = 0;
	virtual void clear() = 0;

	virtual void sort() = 0;
};

#endif