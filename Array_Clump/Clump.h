#ifndef CLUMP_H
#define CLUMP_H

#include <iostream>
#include <stdexcept>
#include <vector>

using std::vector;

template<typename Type>
class Clump{
	int dimensions;

	vector<int> length;		//Allocated memory
	vector<int> elements;	//Used memory

	//default_length = 1 // ...Type[default_length ^ dimensions] // equivalent to 1
	Type * ptr = new Type[1];

	void reallocate(int degree, int growth);

	int index_expansion(vector<int> coordinate);
	bool valid_coordinate(vector<int> coordinate);
	bool valid_dimension(vector<int> coordinate);

	//If true, numbering starts at 1
	bool offset = true;

	//Extra allocated space between sections of data
	int buffer_length = 1;
	//int buffer_multiplier = 1;

public:
	Clump(bool mOffset = false, int mDimensions = 1);
	Clump(Clump& input);
	~Clump();


	bool is_empty() { return elements == 0; }

	Type front() { return ptr[0]; }
	Type back() { return ptr[elements - 1]; }
	

	//Getters
	Type get(vector<int> coordinate);

	int get_length() const { return index_expansion(length); }
	int get_length(int dim) { return length[dim]; }

	int get_elements() const;
	bool get_offset() const { return offset; }
	int get_dimensions() const { return dimensions; }

	vector<Type> traverse();

	//Setters
	void set_offset(bool mOffset) { offset(mOffset); }
	bool set_buffer(int mBuffer);

	//Mutators
	bool assign(Type value, int index);
	bool assign(Clump<Type> value, int index);
	bool assign(Type value, vector<int> index);
	bool assign(Clump<Type> value, vector<int> index);

	void append(Type value) { insert(value, elements + offset); }
	void prepend(Type value) { insert(value, offset); }

	bool insert(vector<Type> value, vector<int> index);

	bool remove(vector<int> index);
	bool remove(int index);

	void fill(Type);
	void clear();

	Type operator()(vector<int> coordinate);
	void operator=(Clump input);
	bool operator==(Clump input);
};

#include "Clump.cpp"

#endif