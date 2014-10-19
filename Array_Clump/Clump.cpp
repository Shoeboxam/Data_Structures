template<typename Type>
Clump<Type>::Clump(bool mOffset, int mDimensions){
	if (mDimensions > 0) { dimensions = mDimensions; }

	for (int i = 0; i < dimensions; i++){
		length.push_back(1);
		elements.push_back(0);
	}
}

template<typename Type>
Clump<Type>::Clump(Clump& input){

	offset = input.get_offset();
	elements = input.get_elements();
	length = input.get_length();

	Type * buffer = new Type[length];

	//Copy elements of data into new array
	for (int i = 0; i <= elements - 1; i++){
		buffer[i] = input[i + offset];
	}

	delete[] ptr;
	ptr = buffer;
}

template<typename Type>
Clump<Type>::~Clump(){
	delete[] ptr;
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

//Point validation
template<typename Type>
bool Clump<Type>::valid_coordinate(vector<int> coordinate){
	if (coordinate.size() != dimensions) { return false; }

	for (int dim = 1; dim <= coordinate.size(); dim++){
		if (coordinate[dim] > length[dim] || coordinate[dim] < 0) { return false; }
	}

	return true;
}

//Row validation
template<typename Type>
bool Clump<Type>::valid_dimension(vector<int> coordinate){
	if (dimensions < coordinate.size()) { return false; }

	for (int dim = 1; dim <= coordinate.size(); dim++){
		if (coordinate[dim] > length[dim] || coordinate[dim] < 0) { return false; }
	}

	return true;
}


//Expansion and contraction of underlying C-array storage
template<typename Type>
void Clump<Type>::reallocate(int degree, int growth){
	//Degree specifies dimension to grow, growth specifies how many new indices


	vector<int> old_length = length;

	//Extend length at dimension degree by growth. Build in buffer here
	length[degree] = elements[degree] + growth + buffer_length;

	//Find index of maximum possible coordinate, set length of buffer to it
	//Buffers are already built into length
	Type * buffer = new Type[index_expand(length)];

	//Copy elements of data into new array with respect to newly allocated indices
	for (int dim = 0; dim <= old_length.size(); dim++){
		for (int i = 0; i <= old_length[dim]; i++){
			buffer[length[dim] * i] = ptr[old_length[dim] * i];
		}
	}

	//Delete ptr contents, then set pointer to the new array
	delete[] ptr;
	ptr = buffer;
}

template<typename Type>
bool Clump<Type>::insert(Type value, vector<int> coordinate){
	//NOTE: Insertion of >1D array bucket fills all child dimensions
	//IE: Inserting five @ dimension 4 of 7 bucket fills five in the newly created child rows in dimensions 4, 5, 6 and 7

	//Convert from coordinate to raw index
	int index = index_expansion(coordinate);

	//Check if value is in range
	if (index < offset || index > elements + offset) { return false; }

	//Map input to array indice
	index -= offset;

	//Ensure adequate space is available in array
	for (int dim = 0; dim < coordinate.size(); dim++){
		if (elements[dim] >= length[dim]) { 
			reallocate(coordinate[dim], 1); 
		}
	}

	//TODO: dimensional shifting
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

//Cover for simpler insertion on 1D arrays
template<typename Type>
bool Clump<Type>::insert(Type value, int index){
	if (dimensions > 1){
		cout << "Error: Insufficient coordinate given for multidimensional Clump."
		return false;
	}

	vector<int> buffer;
	buffer.push_back(index);
	return insert(value, buffer);
}

template<typename Type>
bool Clump<Type>::insert(std::vector<Type> value, int index){
	//Check if value is in range
	if (index < offset || index > elements + offset) return false;

	//Map input to array indice
	index -= offset;

	//Include new elements before reallocation
	elements += value.size();

	//Ensure adequate space is available in array
	if (elements >= length) reallocate();

	//Shift values forward from the end to the insertion
	if (elements > 0){
		for (int i = elements + offset; i >= index; i--){
			ptr[i] = ptr[i - value.size()];
		}
	}

	for (int i = 0, i <= value.size(); i++){
		ptr[index + i] = value[i];
	}

	return true;
}

template<typename Type>
bool Clump<Type>::remove(int index){
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
	offset = input.get_offset();
	elements = input.get_elements();
	length = input.get_length();

	Type * buffer = new Type[length];

	//Copy elements of data into new array
	for (int i = 0; i <= elements - 1; i++){
		buffer[i] = input[i + offset];
	}

	delete[] ptr;
	ptr = buffer;
}

template<typename Type>
Type Clump<Type>::operator[](int index){
	if (index < offset || index > elements - !offset){
		throw std::out_of_range("Error: index out of bounds");
	}

	return ptr[index - offset];
}

template<typename Type>
bool Clump<Type>::operator==(Clump input){
	if (elements != input.get_elements()) return false;

	for (int i = 0; i <= elements - 1; i++){
		if (ptr[i] != input[i + input.get_offset()]) return false;
	}
	return true;
}