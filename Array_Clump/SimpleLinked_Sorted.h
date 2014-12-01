#ifndef SIMPLELINKED_SORTED_H
#define SIMPLELINKED_SORTED_H

#include "SimpleLinked.h"

template<typename Type>
class SimpleLinked_Sorted : public SimpleLinked<Type> {
	SimpleLinked<Type>::insert;

public:
	SimpleLinked_Sorted(){}

	bool push_back(Type value) { return insert(value, elements); }
	bool push_front(Type value) { return insert(value, 0); }

	bool insert(Type value, int index);
};

template<typename Type>
bool SimpleLinked_Sorted<Type>::insert(Type value, int index){

	//Simply overwrites the index with where it would be sorted
	set_placer(0);
	while (node_placer->value < value) increment_placer(), index++;

	return SimpleLinked<Type>::insert(Type value, int index);
}

#endif