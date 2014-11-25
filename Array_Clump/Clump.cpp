
#include <iostream>
using std::cout;

template<typename Type>
Clump<Type>::Clump(Clump& input){

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
Clump<Type>::~Clump(){
	delete[] ptr;
}

template<typename Type>
void Clump<Type>::reallocate(){
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
Type& Clump<Type>::get(int index){
	if (index < 0 || index > elements - 1){
		throw std::out_of_range("Error: index out of bounds");
	}

	return ptr[index];
}

template<typename Type>
Type Clump<Type>::get(int index) const{
	if (index < 0 || index > elements - 1){
		throw std::out_of_range("Error: index out of bounds");
	}

	return ptr[index];
}


template<typename Type>
bool Clump<Type>::insert(Type value, int index){
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
bool Clump<Type>::remove(int index){

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
void Clump<Type>::fill(Type value){
	for (int i = 0; i < elements; i++){
		ptr[i] = value;
	}
}

template<typename Type>
void Clump<Type>::clear(){
	for (int i = elements - 1; i >= 0; i--){
		ptr[i] = 0;
	}
	elements = 0;
}

template<typename Type>
void Clump<Type>::operator=(const Clump& input){
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
Type& Clump<Type>::operator[](int index){
	return get(index);
}


template<typename Type>
bool Clump<Type>::operator==(const Clump& input){
	if (elements != input.get_elements()) return false;

	for (int i = 0; i <= elements - 1; i++){
		if (ptr[i] != input[i]) return false;
	}
	return true;
}