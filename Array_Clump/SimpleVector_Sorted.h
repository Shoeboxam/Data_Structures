#ifndef SORTED_SimpleVector_H
#define SORTED_SimpleVector_H

#include "SimpleVector.h"

template<typename Type>
class Sorted_SimpleVector : public SimpleVector<Type> {

public:
	Sorted_SimpleVector(SimpleVector<Type> input);

	bool insert(Type value);
};

#endif