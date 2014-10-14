#include "Clump.h"

Clump::Clump(bool mOffset){
	offset = mOffset;
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

	if (index > elements) return false;
	if (++elements >= length) reallocate();

	for (int i = elements; i > index; i--){
		ptr[i]= ptr[i-1];
	}

	ptr[index] = value;

	return true;
}

bool Clump::remove(int index){

	if (index > elements) return false;
	if (--elements >= length/2) reallocate();

	for (; index <= elements-1; index++){
		ptr[index] = ptr[index+1];
	}

	ptr[index] = 0;

	return true;
}

void Clump::fill(int value){
	for (int i = 0; i < elements; i++){
		ptr[i] = value;
	}
}

void Clump::clear(){
	for (int i = elements; i >= 0; i--){
		ptr[i] = 0;
	}
	elements = 0;
}

void Clump::operator=(Clump input){
	delete[] & ptr;
	length = input.get_elements();
	int * ptr = new int[length];

	//Copy elements of data into new array
	for (int i = 0; i < length; i++){
		ptr[i] = input[i];
	}
}

int& Clump::operator[](int index){
	if (index >= elements || index < offset){
		throw std::out_of_range("Error: index out of bounds");
	}

	return ptr[index - offset];
}

bool Clump::operator==(Clump input){
	if (this->elements != input.get_elements()) return false;

	for (int i = 0; i <= elements; i++){
		if (ptr[i + offset] != input[i]) return false;
	}
	return true;
}