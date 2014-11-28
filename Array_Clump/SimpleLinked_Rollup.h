#ifndef SIMPLELINKED_ROLLUP_H
#define SIMPLELINKED_ROLLUP_H

#include "SimpleLinked.h"

template<typename Type>
class SimpleLinked_Rollup : public SimpleLinked<Type> {
	
	void rollup(int index);

public:

	template<typename Type>
	bool insert(Type value, int index);

	template<typename Type>
	bool remove(int index);

	template<typename Type>
	Type get_sum(int index);
};

#include "SimpleLinked_Rollup.cpp"

#endif