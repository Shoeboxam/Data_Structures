#include "Clump.h"

Clump::~Clump(){
	delete[] data;
}

void Clump::reallocate(){
	//Create new array with double number of elements
	length = elements * 2;
	int * buffer = new int[length];

	//Copy elements of data into new array
	for (int i = 0; i <= length/2; i++){
		buffer[i] = *data[i];
	}

	//Delete data, then set data to the new array
	delete[] data;
	*data = buffer;
}

bool Clump::insert(int value, int index){
	if (index > ++elements) return false;
	if (elements == length) reallocate();

	for (int i = index; i <= elements; i++){
		data[i + 1] = data[i];
	}

	data[index] = &value;
}

bool Clump::remove(int index){
	if (index > elements--) return false;
	if (elements == length/2) reallocate();

	for (; index < elements; index++){
		*data[index] = *data[index + 1];
	}

	delete data[index];
}

void Clump::fill(int value){
	for (int i = 0; i <= elements; i++){
		data[i] = &value;
	}
}

void Clump::clear(){
	for (int i = elements; i >= 0; i--){
		delete data[i];
	}
}