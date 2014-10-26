#ifndef CLUMP_H
#define CLUMP_H

#include <iostream>
#include <stdexcept>

template<typename Type>
class Clump{
	int length = 1;
	int elements = 0;

	Type * ptr = new Type[length];

	void reallocate();

	//If true, numbering starts at 1
	bool offset = true;

public:
	Clump(bool mOffset = false);
	Clump(Clump& input);
	~Clump();

	//Getters
	int get_length() const { return length; }
	int get_elements() const { return elements; }
	bool is_offset() const { return offset; }
	bool is_empty() { return elements == 0; }

	Type front() { return ptr[0]; }
	Type back() { return ptr[elements - 1]; }

	//Mutators
	void append(Type value) { insert(value, elements + offset); }
	void prepend(Type value) { insert(value, offset); }

	bool insert(Type value, int index);
	bool remove(int index);

	void fill(Type);
	void clear();

	void operator=(Clump input);
	Type operator[](int index);
	bool operator==(Clump input);
};

#include "Clump.cpp"

#endif