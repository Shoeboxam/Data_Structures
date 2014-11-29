#ifndef SORTED_SimpleVector_H
#define SORTED_SimpleVector_H

#include "SimpleVector.h"

template<typename Type>
class Sorted_SimpleVector : public SimpleVector<Type> {

public:
	Sorted_SimpleVector(SimpleVector<Type> input);

	bool insert(Type value);
};

template<typename Type>
Sorted_SimpleVector<Type>::Sorted_SimpleVector(SimpleVector<Type> input){
	this = input.sort();
}


template<typename Type>
bool Sorted_SimpleVector<Type>::insert(Type value){

	//Ensure adequate space is available in array
	if (elements >= length) reallocate();

	int index = 0;
	while (value < ptr[index]) index++;

	//Shift values forward one from the end to the insertion
	if (elements > 0){
		for (int i = elements; i >= index; i--){
			ptr[i] = ptr[i - 1];
		}
	}

	ptr[index] = value;
	elements++;

	return true;
}

#endif