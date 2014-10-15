#include "Clump.h"

Clump::Clump(bool mOffset){
	offset = mOffset;
}

Clump::Clump(Clump& input){

	offset = input.is_offset();
	elements = input.get_elements();
	length = input.get_length();

	int * buffer = new int[length];

	//Copy elements of data into new array
	for (int i = 0; i <= elements - 1; i++){
		buffer[i] = input[i + offset];
	}

	delete[] ptr;
	ptr = buffer;
}

Clump::~Clump(){
	delete[] ptr;
}

void Clump::reallocate(){
	//Create new array with double length
	length = elements * 2;
	int * buffer = new int[length];

	//Copy elements of data into new array
	for (int i = 0; i <= length/2; i++){
		buffer[i] = ptr[i];
	}

	//Delete ptr contents, then set pointer to the new array
	delete[] ptr;
	ptr = buffer;
}

bool Clump::insert(int value, int index){
	//Check if value is in range
	if (index < offset || index > elements + offset) return false;

	//Map input to array indice
	index -= offset;

	//Ensure adequate space is available in array
	if (elements >= length) reallocate();

	//Shift values forward one from the end to the insertion
	if (elements > 0){
		for (int i = elements + offset; i >= index; i--){
			ptr[i] = ptr[i - 1];
		}
	}

	ptr[index] = value;
	elements++;

	return true;
}

bool Clump::remove(int index){
	index -= offset;

	if (index > elements) return false;
	if (elements >= length/2) reallocate();

	for (; index <= elements-1; index++){
		ptr[index] = ptr[index+1];
	}

	ptr[index] = 0;
	elements--;

	return true;
}

void Clump::fill(int value){
	for (int i = 0; i < elements; i++){
		ptr[i] = value;
	}
}

void Clump::clear(){
	for (int i = elements - 1; i >= 0; i--){
		ptr[i] = 0;
	}
	elements = 0;
}

void Clump::operator=(Clump input){
	offset = input.is_offset();
	elements = input.get_elements();
	length = input.get_length();

	int * buffer = new int[length];

	//Copy elements of data into new array
	for (int i = 0; i <= elements - 1; i++){
		buffer[i] = input[i + offset];
	}

	delete[] ptr;
	ptr = buffer;
}

int Clump::operator[](int index){
	if (index < offset || index > elements - !offset){
		throw std::out_of_range("Error: index out of bounds");
	}

	return ptr[index - offset];
}

bool Clump::operator==(Clump input){
	if (elements != input.get_elements()) return false;

	for (int i = 0; i <= elements - 1; i++){
		if (ptr[i] != input[i + input.is_offset()]) return false;
	}
	return true;
}