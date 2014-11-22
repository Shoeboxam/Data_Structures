#ifndef CLUMP_H
#define CLUMP_H

#include "Access_API.h"
#include <iostream>

template<typename Type>
class Clump : public Access_API<Type> {
protected:
	Type * ptr = new Type[length];

	void reallocate();

public:
	Clump();
	Clump(Clump& input);
	~Clump();

	Type get(int index);


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

#endif