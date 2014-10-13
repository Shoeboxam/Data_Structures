#ifndef CLUMP_H
#define CLUMP_H

class Clump{
	int length;
	int elements = 0;

	int * ptr;
	void reallocate();

public:
	Clump(int length = 1);
	~Clump();

	bool empty() { return elements = 0 ? true : false; }

	int front() { return *ptr; }
	int back() { return *(ptr+elements); }

	//Getters
	int get_length() const { return length; }
	int get_elements() const { return elements; }

	int& operator[](int index){ return *(ptr + index + 1); }

	//Mutators
	void append(int value) { insert(value, elements+1); }
	void prepend(int value) { insert(value, 0); }

	bool insert(int value, int index);
	bool remove(int index);

	void fill(int);
	void clear();
};

#endif