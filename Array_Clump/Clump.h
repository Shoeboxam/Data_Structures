#ifndef CLUMP_H
#define CLUMP_H

#include <iostream>
#include <stdexcept>

class Clump{
	int length = 1;
	int elements = 0;

	int * ptr = new int[length];
	void reallocate();

	//If true, numbering starts at 1
	bool offset = true;

public:
	Clump(bool mOffset = true);
	~Clump();


	bool empty() { return elements == 0; }

	int front() { return ptr[0]; }
	int back() { return ptr[elements - 1]; }

	//Getters
	int get_length() const { return length; }
	int get_elements() const { return elements; }

	//Mutators
	void append(int value) { insert(value, elements); }
	void prepend(int value) { insert(value, 0); }

	bool insert(int value, int index);
	bool remove(int index);

	void fill(int);
	void clear();

	void operator=(Clump input);
	int& operator[](int index);
	bool operator==(Clump input);
};

#endif