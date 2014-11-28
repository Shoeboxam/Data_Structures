#ifndef SimpleVector_H
#define SimpleVector_H

#include "Access_API.h"
#include <iostream>

template<typename Type>
class SimpleVector : public Access_API<Type> {
protected:
	Type * ptr = new Type[length];

	void reallocate();

	int length;

public:
	SimpleVector(){ length = 1; }
	SimpleVector(SimpleVector& input);
	~SimpleVector();

	Type& get(int index);
	Type get(int index) const;

	int get_length() const { return length; }

	//Mutators
	bool insert(Type value, int index);
	bool remove(int index);

	void fill(Type);
	void clear();

	Type& operator[](int index);
	Type operator[](int index) const;

	void operator=(const SimpleVector& input);
	bool operator==(const SimpleVector& input);
};

#include "SimpleVector.cpp"

#endif