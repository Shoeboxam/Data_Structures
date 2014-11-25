#ifndef SORTED_CLUMP_H
#define SORTED_CLUMP_H

#include "Clump.h"

template<typename Type>
class Sorted_Clump : public Clump<Type> {

public:
	Sorted_Clump(Clump<Type> input);

	bool insert(Type value);
};

#endif