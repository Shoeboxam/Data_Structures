
template<typename Type>
Clink<Type>::~Clink(){
	clear();
}


template<typename Type>
Type Clink<Type>::get(int index){
	Node<Type>* element_current = element_first;

	for (int i = 0; i < index && element_current->next != nullptr; i++){
		element_current = element_current->next;
	}
	return element_current->value;
}

template<typename Type>
bool Clink<Type>::set_placer(int index){
	node_placer = element_first;

	for (int i = 0; i < index; i++){
		if (node_placer->next == nullptr && i < index) return false;
		node_placer = node_placer->next;
	}

	return true;
}

template<typename Type>
bool Clink<Type>::insert(Type input, int index) {

	if (!set_placer(index - 1)) return false;

	Node<Type>* node_new = new Node<Type>(input);

	node_new->next = node_placer->next;
	node_placer->next = node_new;

	return true;
}

template<typename Type>
bool Clink<Type>::remove(int index){
	if (index == 0) {
		element_first = element_first->next; //TODO: Fix memory leak here
	}

	if (!set_placer(index - 1)) return false;

	node_placer->next = node_placer->next->next; //Yeaugh
	return true;
}


template<typename Type>
void Clink<Type>::fill(Type input){
	set_placer(0);

	while (node_placer->next != nullptr){
		node_placer->value = input;
		node_placer = node_placer->next;
	}
}

template<typename Type>
void Clink<Type>::clear(){
	Type * buffer = new Type[elements];

	int index = 0;
	set_placer(index);

	while (increment_placer()){
		buffer[index] = get_placer();
	}
	delete[] buffer;
}

template<typename Type>
void Clink<Type>::sort(){

}

template<typename Type>
bool Clink<Type>::increment_placer(){
	if (node_placer->next == nullptr) return false;

	node_placer = node_placer->next;
	return true;

}


template<typename Type>
void Clink<Type>::operator=(Clink& input){
	elements = input.get_elements();

	Type * buffer = new Type[length];

	//Copy elements of data into new array
	for (int i = 0; i <= elements - 1; i++){
		buffer[i] = input[i];
	}

	delete[] ptr;
	ptr = buffer;
}

template<typename Type>
Type Clink<Type>::operator[](int index){
	return get(index);
}

template<typename Type>
bool Clink<Type>::operator==(Clink& input){
	if (elements != input.get_elements()) return false;
	
	set_placer(0);

	while (increment_placer() && input.increment_placer()){
		if (get_placer() != input.get_placer()) return false;
	}

	return true;
}