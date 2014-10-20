
template<typename Type>
Clump<Type>::Clump(bool mOffset){
	offset = mOffset;
}

template<typename Type>
Clump<Type>::Clump(Clump& input){

	offset = input.is_offset();
	elements = input.get_elements();
	width = input.get_width();
	height = input.get_height();

	Type * buffer = new Type[get_length()];

	//Copy elements of data into new array

	for (int i = 0; i <= input.; i++){
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
void Clump<Type>::reallocate(int width_diff, int height_diff){
	//Create new array with multiplied true dimensions
	int new_width = alloc_width + width_diff;
	int new_height = alloc_height + height_diff;

	//For any reason, if reallocation would truncate values, then return
	if (new_width < elem_width || new_height < elem_height) return;

	Type * buffer = new Type[new_width * new_height];

	//Copy elements of data into new array
	for (int x = 0; x < alloc_width; x++){
		for (int y = 0; y < alloc_height; y++){
			buffer[new_width * x + y] = ptr[alloc_width * x + y];
		}
	}

	//Delete ptr contents, then set pointer to the new array
	delete[] ptr;
	ptr = buffer;

	alloc_width = new_width;
	alloc_height = new_height;
}

template<typename Type>
void Clump<Type>::insert_row(vector<Type> value, int index){

	//Ensure vector is correct length for insertion
	assert (value.size() == elem_width);

	//Check if index is in range
	assert (index >= offset && index <= elements + offset);

	//Map input to array indice
	index -= offset;

	//Ensure adequate space is available in array
	if (alloc_height >= length) reallocate(0, alloc_buffer * value.size());

	//Shift values forward one from the end to the insertion on every column
	if (elem_height > 0){
		for (int x = elem_width + offset; x >= index; x--){
			for (int y = elem_height + offset; x >= offset; y--){
				ptr[x * elem_width + y] = ptr[(x - 1) * elem_width + y];
			}
		}
	}

	//Assign input vector to array
	for (int i = alloc_width * index; i < alloc_width * (index + 1); i++){
		ptr[i] = value[i / alloc_width];
	}

	elements += value.size();
}

template<typename Type>
void Clump<Type>::insert_column(vector<Type> value, int index){

	//Ensure vector is correct length for insertion
	assert (value.size() == elem_height);

	//Check if index is in range
	assert(index >= offset && index <= elements + offset);

	//Map input to array indice
	index -= offset;

	//Ensure adequate space is available in array
	if (alloc_width >= length) reallocate(alloc_buffer * value.size(), 0);

	//Shift values forward one from the end to the insertion on every column
	if (elem_width > 0){
		for (int y = elem_height + offset; x >= offset; y--){
			for (int x = elem_width + offset; x >= index; x--){
				ptr[x + y * elem_width] = ptr[(x - 1) + y * elem_width];
			}
		}
	}

	//Assign input vector to array
	for (int i = index; i < get_length(); i += alloc_width){
		ptr[i] = value[(i - index) / alloc_width];
	}

	elements += value.size();
}

template<typename Type>
void Clump<Type>::remove_row(int index){
	index -= offset;

	assert (index < elem_height);

	//Shrink data structure if it is too large
	if (elem_height < alloc_height - alloc_buffer) reallocate(0, -alloc_buffer * alloc_height);

	//Loop through each row
	int row = index;
	for (; row <= alloc_height; row++){
		//Within each row, set it to the value of the next row
		for (int i = row * alloc_width; i < row * (alloc_width + 1); i++){
			ptr[i] = ptr[i + alloc_width];
		}
	}

	//Delete final row to prevent leftovers
	for (int i = 0; i < alloc_width; i++){
		delete ptr[row * alloc_width + i];
	}
	
	elem_height--;
}

template<typename Type>
void Clump<Type>::remove_column(int index){
	index -= offset;

	assert(index < elem_width);

	//Shrink data structure if it is too large
	if (elem_width < alloc_width - alloc_buffer) reallocate(-alloc_buffer * alloc_width, 0);

	//Loop through each row
	int column = index;
	for (; column <= alloc_height; column++){
		//Set each row to the value of the next row
		for (int i = column * alloc_width; i < column * (alloc_width + 1); i++){
			ptr[i] = ptr[i + alloc_width];
		}
	}

	//Delete final row to prevent leftovers
	for (int i = 0; i < alloc_width; i++){
		delete ptr[row * alloc_width + i];
	}

	elem_height--;
}

template<typename Type>
void Clump<Type>::fill(Type value){
	for (int x = 0; x < elem_width; x++){
		for (int y = 0; y < elem_height; y++){
			ptr[x + y * alloc_width] = value;
		}
	}
}

template<typename Type>
void Clump<Type>::clear(){
	for (int x = 0; x < elem_width; x++){
		for (int y = 0; y < elem_height; y++){
			delete ptr[x + y * alloc_width];
		}
	}
}

template<typename Type>
void Clump<Type>::operator=(Clump input){
	offset = input.is_offset();
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
bool Clump<Type>::operator==(Clump input){
	if (elements != input.get_elements()) return false;

	for (int i = 0; i <= elements - 1; i++){
		if (ptr[i] != input[i + input.is_offset()]) return false;
	}
	return true;
}