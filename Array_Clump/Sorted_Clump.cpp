#include "Sorted_Clump.h"

template<typename Type>
Sorted_Clump<Type>::Sorted_Clump(Clump& input){
	this = input.sort();
}


template<typename Type>
bool Sorted_Clump<Type>::insert(Type value){

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