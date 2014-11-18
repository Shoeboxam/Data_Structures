#ifndef SORTED_CLUMP_H
#define SORTED_CLUMP_H

#include "Clump.h"

template<typename Type>
class Sorted_Clump : public Clump<Type> {
	//Hides these members inherited from the base class
	void append(Type value) { insert(value); }
	void prepend(Type value) { insert(value); }

	bool insert(Type value, int index){}

public:
	Sorted_Clump(Clump& input);

	bool insert(Type value);
};

#endif