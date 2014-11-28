
#include <iostream>
using std::cout;

template<typename Type>
SimpleVector<Type>::SimpleVector(SimpleVector& input){

	elements = input.get_elements();
	length = input.get_length();

	Type * buffer = new Type[length];

	//Copy elements of data into new array
	for (int i = 0; i <= elements - 1; i++){
		buffer[i] = input[i];
	}

	delete[] ptr;
	ptr = buffer;
}

template<typename Type>
SimpleVector<Type>::~SimpleVector(){
	delete[] ptr;
}

template<typename Type>
void SimpleVector<Type>::reallocate(){
	//Create new array with double length
	length = elements * 2;
	Type * buffer = new Type[length];

	//Copy elements of data into new array
	for (int i = 0; i <= length/2; i++){
		buffer[i] = ptr[i];
	}

	//Delete ptr contents, then set pointer to the new array
	delete[] ptr;
	ptr = buffer;
}

template<typename Type>
Type& SimpleVector<Type>::get(int index){
	if (index < 0 || index > elements - 1){
		throw std::out_of_range("Error: index out of bounds");
	}

	return ptr[index];
}

template<typename Type>
Type SimpleVector<Type>::get(int index) const{
	if (index < 0 || index > elements - 1){
		throw std::out_of_range("Error: index out of bounds");
	}

	return ptr[index];
}


template<typename Type>
bool SimpleVector<Type>::insert(Type value, int index){
	//Check if value is in range
	if (index < 0 || index > elements) return false;

	//Ensure adequate space is available in array
	if (elements >= length) reallocate();

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

template<typename Type>
bool SimpleVector<Type>::remove(int index){

	if (index > elements) return false;
	if (elements >= length/2) reallocate();

	for (; index <= elements-1; index++){
		ptr[index] = ptr[index+1];
	}

	ptr[index] = 0;
	elements--;

	return true;
}

template<typename Type>
void SimpleVector<Type>::fill(Type value){
	for (int i = 0; i < elements; i++){
		ptr[i] = value;
	}
}

template<typename Type>
void SimpleVector<Type>::clear(){
	for (int i = elements - 1; i >= 0; i--){
		ptr[i] = 0;
	}
	elements = 0;
}

template<typename Type>
void SimpleVector<Type>::operator=(const SimpleVector& input){
	elements = input.get_elements();
	length = input.get_length();

	Type * buffer = new Type[length];

	//Copy elements of data into new array
	for (int i = 0; i <= elements - 1; i++){
		buffer[i] = input[i];
	}

	delete[] ptr;
	ptr = buffer;
}

template<typename Type>
Type& SimpleVector<Type>::operator[](int index){
	return get(index);
}

template<typename Type>
Type SimpleVector<Type>::operator[](int index) const {
	return get(index);
}


template<typename Type>
bool SimpleVector<Type>::operator==(const SimpleVector& input){
	if (elements != input.get_elements()) return false;

	for (int i = 0; i <= elements - 1; i++){
		if (ptr[i] != input[i]) return false;
	}
	return true;
}