#ifndef CLUMP_H
#define CLUMP_H

#include <iostream>
#include <stdexcept>
#include <assert.h>

#include <vector>
using std::vector;

template<typename Type>
class Clump{
	int alloc_width = 1;
	int alloc_height = 1;

	int elem_width = 0;
	int elem_height = 0;

	Type * ptr = new Type[get_length()];

	void reallocate(int width_diff, int height_diff);

	//Higher = greater allocation size, fewer reallocations
	int alloc_buffer = 2;

public:
	Clump(){}
	Clump(const Clump& input);
	Clump(vector<Type> values, int mWidth, int mHeight);
	~Clump();


	bool empty() { return get_elements() == 0; }

	Type front() { return *ptr[0]; }
	Type back() { return get(elem_width, elem_height); }

	//Getters
	Type& at(int x, int y);
	Type at(int x, int y) const;

	vector<Type> get() const;
	vector<Type> get_row(int index) const;
	vector<Type> get_column(int index) const;


	int get_length() const { return alloc_height * alloc_width; }
	int get_elements() const { return elem_height * elem_width; }

	int get_width() const { return elem_width; }
	int get_height() const { return elem_height; }

	//Mutators
	bool append_row(vector<Type> value) { return insert_row(value, get_width()); }
	bool append_column(vector<Type> value) { return insert_column(value, get_height()); }

	bool prepend_row(vector<Type> value) { return insert_row(value, 0); }
	bool prepend_column(vector<Type> value) { return insert_column(value, 0); }

	bool insert_row(vector<Type> value, int index);
	bool insert_column(vector<Type> value, int index);

	bool remove_row(int index);
	bool remove_column(int index);

	void fill(Type);
	void clear();

	void operator=(const Clump &input);
	bool operator==(Clump input) const;

	Type& operator()(int x, int y) { return at(x, y); }
	Type operator()(int x, int y) const { return at(x, y); }
};

#include "Clump.cpp"

#endif