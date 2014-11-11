#include "Clump.h"

template<typename Type>
void Clump<Type>::actions::flattened_vector(Type value, vector<int> coordinates){
	flat.push_back(value);
}

template<typename Type>
Clump<Type>::Clump(int mDimensions){
	if (mDimensions > 0) { dimensions = mDimensions; }

	for (int i = 0; i < dimensions; i++){
		length.push_back(1);
		elements.push_back(0);
	}
}

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
Type Clump<Type>::get(vector<int> coordinate){
	int index = 0;
	for (int i = 0; i < coordinate.size(), i++){
		if (coordinate[i] >= length[i] || coordinate[i] < 0) { return false; }

		index += ptr[length[i] * coordinate[i]];
	}
	return ptr[index];
}

template<typename Type>
int Clump<Type>::get_elements() const {
	int components = 0;
	for (int dim = 0; dim < dimensions; dim++){
		components += pow(elements[dim], components);
	}
	return components;
}

template<typename Type>
bool Clump<Type>::set_buffer(int mBuffer){
	return mBuffer < 0 ? return false : (buffer = mBuffer, return true);
}

//Map coordinate to flat array indice
template<typename Type>
int Clump<Type>::index_expansion(vector<int> coordinate){

	if (coordinate.size() > dimensions) {
		throw "Error: Too many dimensions specified in coordinate.";
	}

	int index = 0;
	for (int dim = 1; dim <= coordinate.size(); dim++){
		index += point * length[dim];
	}

	return index;
}

//Useful for deep copy, gets flat vector of all elements
template<typename Type>
vector<Type> Clump<Type>::traverse(){
	vector<int> coordinates;
	for (int i = 0; i < dimensions; i++){
		coordinates.push_back(0);
	}

	return traverse(coordinates);
}


//Depth first graph/tree traversal algorithm
template<typename Type>
vector<Type> Clump<Type>::traverse(){
	
	vector<Type> recurse(int dim){
		
		vector<Type> traversal;

		for (int dim = 0; dim < dimensions; dim++){
			for (int i = 0; i < length[dim]; i++){

				coordinates[dim] = i;
				traversal.push_back(get(coordinates));

				recurse(dim);
			}
		}
		return traversal;
	}

	return recurse(dimensions);
}

//Coordinate validation - check for valid point or range
//Point validation
template<typename Type>
bool Clump<Type>::valid_point(vector<int> coordinate){
	if (coordinate.size() != dimensions) { return false; }

	for (int dim = 1; dim <= coordinate.size(); dim++){
		if (coordinate[dim] > length[dim] || coordinate[dim] < 0) { return false; }
	}

	return true;
}

//Indice validation
template<typename Type>
bool Clump<Type>::valid_indice(vector<int> coordinate){
	if (dimensions < coordinate.size()) { return false; }

	for (int dim = 1; dim <= coordinate.size(); dim++){
		if (coordinate[dim] > length[dim] || coordinate[dim] < 0) { return false; }
	}

	return true;
}


//Expansion and contraction of underlying C-array storage
template<typename Type>
void Clump<Type>::reallocate(vector<int> length_new){

	//Find index of maximum possible coordinate, set length of buffer to it
	Type * buffer = new Type[index_expand(length_new)];

	//Copy elements of data into new array with respect to newly allocated indices
	for (int dim = 0; dim <= length.size(); dim++){
		for (int i = 0; i <= length[dim]; i++){
			buffer[length[dim] * i] = ptr[old_length[dim] * i];
		}
	}

	//Delete ptr contents, then set pointer to the new array
	delete[] ptr;
	ptr = buffer;
}

//TODO: Insertion should accept Clumps compatible with child dimensions
template<typename Type>
bool Clump<Type>::insert(vector<Type> value, vector<int> coordinate){
	//NOTE: Insertion of >1D array bucket fills child dimensions
	//IE: Inserting five @ dimension 4 of 7 bucket fills five in the newly created child rows in dimensions 4, 5, 6 and 7

	//Convert from coordinate to raw index
	int index = index_expansion(coordinate);

	//Check if value is in range
	if (index < 0 || index > elements) { return false; }

	//Ensure adequate space is available in array
	if (elements.front() >= length.front()) { 
		reallocate(coordinate[dim], 1); 
	}

	//TODO: dimensional shifting
	//Shift values forward one from the end to the insertion
	//for (int dim = 0; dim < coordinate.size(); dim++){
	if (elements.back() > 0){
		for (int dim = 1; dim < dimensions; dim++){
			for (int i = elements[dim]; i >= 0; i--){
				ptr[i + length[dim]]
			}
		}
		for (int i = elements.back(); i >= index; i--){
			ptr[i] = ptr[i - 1];
		}
	}

	ptr[index] = value;
	elements[coordinate.size()]++;

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
bool Clump<Type>::assign(Clump<Type> value, vector<int> coordinate){
	if (!valid_coordinate(coordinate)) { return false; }
	if (value.get_dimensions() + coordinate.size() != dimensions) { return false; }

	Type * buffer = new Type[index_expand(length)];

	for (int dim = 1; dim <= value.get_dimensions(); dim++){	//Y
		for (int i = 0; i < value.get_length(dim); i++){		//X
			ptr[i + dim * length[dim]] = value.get();
		}
	}
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
void Clump<Type>::operator=(Clump input){
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
bool Clump<Type>::operator==(Clump input){
	if (elements != input.get_elements()) return false;

	for (int i = 0; i <= elements - 1; i++){
		if (ptr[i] != input[i]) return false;
	}
	return true;
}