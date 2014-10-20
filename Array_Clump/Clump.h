#ifndef CLUMP_H
#define CLUMP_H

#include <iostream>
#include <stdexcept>
#include <assert.h>

#include <vector>
using std::vector;

template<typename Type>
class Clump{
	int alloc_width = 1
	int alloc_height = 1;

	int elem_width = 0;
	int elem_height = 0;

	Type * ptr = new Type[length];

	void reallocate(int width_diff, int height_diff);

	//If true, numbering starts at 1
	bool offset = true;

	//Higher = greater allocation size, fewer reallocations upon insertion
	int alloc_buffer = 2;

public:
	Clump(bool mOffset = false);
	Clump(Clump& input);
	~Clump();


	bool empty() { return elements == 0; }

	Type front() { return ptr[0]; }
	Type back() { return ptr[elements - 1]; }

	//Getters
	int get_length() const { return alloc_height * alloc_width; }

	int get_elements() const { return elem_height * elem_width; }
	int get_width() const { return elem_width; }
	int get_height() const { return elem_height; }

	bool is_offset() const { return offset; }

	//Mutators
	void append_row(vector<Type> value) { insert(value, get_width() + offset); }
	void append_column(vector<Type> value) { insert(value, get_height() + offset); }

	void prepend_row(vector<Type> value) { insert(value, offset); }
	void prepend_column(vector<Type> value) { insert(value, offset); }

	void insert_row(vector<Type> value, int index);
	void insert_column(vector<Type> value, int index);

	void remove_row(int index);
	void remove_column(int index);

	void fill(Type);
	void clear();

	void operator=(Clump input);
	bool operator==(Clump input);
};

#include "Clump.cpp"

#endif