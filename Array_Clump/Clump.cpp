#include "Clump.h"

Clump::Clump(int length){
	ptr = new int[length];
}

Clump::~Clump(){
	delete[] &ptr;
}

void Clump::reallocate(){
	//Create new array with double number of elements
	length = elements * 2;
	int * buffer = new int[length];

	//Copy elements of data into new array
	for (int i = 0; i <= length/2; i++){
		buffer[i] = *(ptr + i);
	}

	//Delete data, then set data to the new array
	delete[] &ptr;
	ptr= buffer;
}

bool Clump::insert(int value, int index){

	if (index > ++elements) return false;
	if (elements == length) reallocate();

	for (int i = index; i <= elements; i++){
		*(ptr + i + 1) = *(ptr + i);
	}

	*(ptr + index) = value;
}

bool Clump::remove(int index){

	if (index > elements--) return false;
	if (elements == length/2) reallocate();

	for (; index < elements; index++){
		*(ptr + index) = *(ptr + index + 1);
	}

	delete (ptr + index);
}

void Clump::fill(int value){
	for (int i = 0; i <= elements; i++){
		*(ptr + i) = value;
	}
}

void Clump::clear(){
	for (int i = elements; i >= 0; i--){
		delete (ptr + i);
	}
}