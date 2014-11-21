#ifndef CLINK_H
#define CLINK_H

#include "Access_API.h"

template<typename Type>
class Clink : public Access_API<Type> {

	template<typename Type>
	class Node;

	Node<Type>* element_first;
	Node<Type>* element_last;

public:

	Type get_value(int index);

	bool insert(Type value, int index);
	bool remove(int index);

	void fill(Type);
	void clear();

	void sort();
};


#endif