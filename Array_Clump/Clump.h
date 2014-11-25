#ifndef CLUMP_H
#define CLUMP_H

#include "Access_API.h"
#include <iostream>

template<typename Type>
class Clump : public Access_API<Type> {
protected:
	Type * ptr = new Type[length];

	void reallocate();

	int length;

public:
	Clump(){ length = 1; }
	Clump(Clump& input);
	~Clump();

	Type& get(int index);
	Type get(int index) const;

	int get_length() const { return length; }

	//Mutators
	bool insert(Type value, int index);
	bool remove(int index);

	void fill(Type);
	void clear();

	void operator=(const Clump& input);
	Type& operator[](int index);
	bool operator==(const Clump& input);
};

#include "Clump.cpp"

#endif