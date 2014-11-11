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

	int index_expansion(vector<int> coordinates);

	//Extra allocated space between sections of data
	int buffer_length = 1;
	//int buffer_multiplier = 1;

	struct actions{
		vector<Type> flat;
		flattened_vector(Type value, vector<int> coordinates);
	};

public:
	Clump(int mDimensions = 1);
	Clump(Clump& input);
	~Clump();

	//Getters
	Type get(vector<int> coordinates);

	int get_size() const { return index_expansion(length); }
	int get_length(int dimension) { return length[dim]; }

	int get_elements() const;
	int get_dimensions() const { return dimensions; }

	bool valid_point(vector<int> coordinates);
	bool valid_indice(vector<int> coordinates);

	vector<Type> traverse();
	vector<Type> traverse(vector<int> coordinates);

	//Setters
	bool set_buffer(int mBuffer);

	//Mutators
	bool assign(Type value, vector<int> index);
	bool assign(Clump<Type> value, vector<int> index);

	bool insert(vector<Type> value, vector<int> coordinates);
	bool insert(Clump& insertion, vector<int> coordinates);
	
	bool remove(vector<int> index);
	bool remove(int index);

	void fill(Type);
	void clear();

	Type operator()(vector<int> coordinates);
	void operator=(Clump input);
	bool operator==(Clump input);
};

#include "Clump.cpp"

#endif