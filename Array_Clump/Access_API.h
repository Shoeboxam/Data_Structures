
template<typename Type>
class Access_API {
protected:
	int length = 1;
	int elements = 0;


public:
	//Getters
	virtual Type get_value(int index) const = 0;

	virtual int get_length() const { return length; }
	virtual int get_elements() const { return elements; }
	virtual bool is_empty() const { return elements == 0; }

	virtual front() const { return get_value(0); }
	virtual back() const { return get_value(elements - 1); }

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