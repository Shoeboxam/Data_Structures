#ifndef CLUMP_H
#define CLUMP_H

#include <iostream>

#include "Access_API.h"

template<typename Type>
class Clump : public Access_API {
protected:
	Type * ptr = new Type[length];

	void reallocate();

public:
	Clump(Clump& input);
	~Clump();

	Type get_value(int index);


	//Mutators
	bool insert(Type value, int index);
	bool remove(int index);

	void fill(Type);
	void clear();

	void sort();

	void operator=(Clump input);
	Type operator[](int index);
	bool operator==(Clump input);
};

#include "Clump.cpp"

#endif