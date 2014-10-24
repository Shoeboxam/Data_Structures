template<typename Type>
Clump<Type>::Clump(const Clump& input){
	this = input;
}

/*
template<typename Type>
Clump<Type>::Clump(vector<Type> values, int mWidth, int mHeight){

	if (mWidth > 0 && mHeight > 0 && values.size() == mWidth * mHeight){

		reallocate(mWidth, mHeight);
		elem_width = mWidth;
		elem_height = mHeight;

		int i = 0;
		for (int y = 0; y < elem_height; y++){
			for (int x = 0; x < elem_width; x++){
				ptr[y * alloc_width + x] = values[i++];
			}
		}
	}
}*/

template<typename Type>
Clump<Type>::~Clump(){
	delete[] ptr;
}

template<typename Type>
Type Clump<Type>::at(int x, int y) const{
	//Bounds checking
	assert (x < elem_width && x >= 0);
	assert (y < elem_height && y >= 0);

	return ptr[x + y*alloc_width]; 
}

template<typename Type>
Type& Clump<Type>::at(int x, int y){
	//Bounds checking
	assert(x < elem_width && x >= 0);
	assert(y < elem_height && y >= 0);

	return ptr[x + y*alloc_width];
}

template<typename Type>
vector<Type> Clump<Type>::get() const{
	vector<Type> buffer;
	for (int y = 0; y < elem_height; y++){
		for (int x = 0; x < elem_width; x++){
			buffer.push_back(ptr[x + y * alloc_width]);
		}
	}
	return buffer;
}

template<typename Type>
vector<Type> Clump<Type>::get_row(int index) const{
	if (index < elem_width && index >= 0) throw "Out of range!";

	vector<Type> buffer;
	for (int i = 0; i < elem_width; i++){
		buffer.push_back(ptr[index * alloc_width + i])
	}
	return buffer;
}

template<typename Type>
vector<Type> Clump<Type>::get_column(int index) const{
	if (index < elem_height && index >= 0) throw "Out of range!";;

	vector<Type> buffer;
	for (int i = 0; i < elem_height; i++){
		buffer.push_back(ptr[index + alloc_width * i]);
	}
	return buffer;
}

template<typename Type>
void Clump<Type>::reallocate(int width_diff, int height_diff){
	//Create new array with multiplied true dimensions
	int new_width = alloc_width + width_diff;
	int new_height = alloc_height + height_diff;

	//For any reason, if reallocation would truncate values, then return
	if (new_width < elem_width || new_height < elem_height) return;

	Type * buffer = new Type[(new_width * new_height)];

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
bool Clump<Type>::insert_row(vector<Type> value, int index){

	//Ensure vector is correct length for insertion
	if (value.size() != elem_width) return false;

	//Check if index is in range
	if (index < 0 || index > elem_height) return false;

	//Ensure adequate space is available in array
	if (elem_height >= alloc_height) reallocate(0, alloc_buffer * value.size());

	//Shift values forward one from the end to the insertion on every column
	if (elem_height > 0){
		for (int x = 0; x < elem_width; x++){
			for (int y = elem_height; y > index; y--){
				ptr[y * alloc_width + x] = ptr[(y - 1) * alloc_width + x];
			}
		}
	}

	//Assign input vector to array
	for (int x = 0; x < value.size(); x++){
		ptr[index * alloc_width + x] = value[x];
	}

	elem_height++;

	return true;
}

template<typename Type>
bool Clump<Type>::insert_column(vector<Type> value, int index){

	//Ensure vector is correct length for insertion
	if (value.size() != elem_height) return false;

	//Check if index is in range
	if (index < 0 || index > elem_width) return false;

	//Ensure adequate space is available in array
	if (elem_width >= alloc_width) reallocate(alloc_buffer * value.size(), 0);

	//Shift values forward one from the end to the insertion on every row
	if (elem_width > 0){
		for (int y = elem_height - 1; y >= 0; y--){
			for (int x = index + 1; x < elem_width; x++){
				ptr[x + y * elem_width] = ptr[(x - 1) + y * elem_width];
			}
		}
	}

	//Assign input vector to array
	for (int y = 0; y < value.size(); y++){
		ptr[index + y * alloc_width] = value[y];
	}

	elem_width++;

	return true;
}

template<typename Type>
bool Clump<Type>::remove_row(int index){

	if (index >= elem_height) return false;

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

	return true;
}

template<typename Type>
bool Clump<Type>::remove_column(int index){

	if (index >= elem_width) return false;

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

	return true;
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
void Clump<Type>::operator=(const Clump &input){
	int alloc_width = input.alloc_width;
	int alloc_height = input.alloc_height;

	int elem_width = input.elem_width;
	int elem_height = input.elem_height;

	int alloc_buffer = input.alloc_buffer;

	Type * buffer = new Type[get_length()];

	//Copy elements of data into new array
	for (int y = 0; y < elem_height; y++){
		for (int x = 0; x < elem_width; x++){
			buffer[x + y * alloc_width] = ptr[x + y * alloc_width];
		}
	}

	delete[] ptr;
	ptr = buffer;
}

template<typename Type>
bool Clump<Type>::operator==(Clump input) const{
	if (elements != input.get_elements()) return false;

	for (int i = 0; i <= elements - 1; i++){
		if (ptr[i] != input[i]) return false;
	}
	return true;
}