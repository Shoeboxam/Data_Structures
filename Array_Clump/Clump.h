#ifndef CLUMP_H
#define CLUMP_H

#include <iostream>
#include <stdexcept>

class Clump{
	int length;
	int elements = 0;

	int * ptr;
	void reallocate();

public:
	Clump(int length = 10);
	~Clump();

	//If true, numbering starts at 1
	bool offset = true;

	bool empty() { return elements = 0 ? true : false; }

	int front() { return *ptr; }
	int back() { return *(ptr+elements); }

	//Getters
	int get_length() const { return length; }
	int get_elements() const { return elements; }

	//Mutators
	void append(int value) { insert(value, elements+1); }
	void prepend(int value) { insert(value, 0); }

	bool insert(int value, int index);
	bool remove(int index);

	void fill(int);
	void clear();

	void operator=(Clump input){
		delete[] &ptr;
		length = input.get_elements();
		int * ptr = new int[length];

		//Copy elements of data into new array
		for (int i = 0; i < length; i++){
			ptr[i] = input[i];
		}
	}
	
	int& operator[](int index){
		if (index > elements || index < 0){
			throw std::out_of_range("Error: index out of bounds");
		}

		return ptr[index+offset];
	}

	bool operator==(Clump input){
		if (this->elements != input.get_elements()) return false;

		for (int i = 0; i <= elements; i++){
			if (ptr[i+offset] != input[i]) return false;
		}
		return true;
	}
};

#endif