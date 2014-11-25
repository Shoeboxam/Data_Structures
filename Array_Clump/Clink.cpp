
template<typename Type>
Clink<Type>::~Clink(){
	clear();
}

template<typename Type>
Clink<Type>::Clink(Clink<Type>& input){
	*this = input;
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
bool Clink<Type>::insert(Type input, int index) {

	Node<Type>* node_new = new Node<Type>(input);

	if (elements == 0) {
		element_last = node_new;
	}

	if (index == 0) { 
		node_new->next = element_first;
		element_first = node_new;

		elements++;
		return true;
	}

	else if (index == elements) {
		element_last->next = node_new;
		element_last = node_new;

		elements++;
		return true;
	}

	else if (set_placer(index - 1)){
		node_new->next = node_placer->next;
		node_placer->next = node_new;

		elements++;
		return true;
	}

	return false;
}

template<typename Type>
bool Clink<Type>::remove(int index){
	if (index == 0) {
		element_first = element_first->next; //TODO: Fix memory leak here
	}

	if (!set_placer(index - 1)) return false;

	node_placer->next = node_placer->next->next; //Yeaugh

	elements--;
	return true;
}


template<typename Type>
void Clink<Type>::fill(Type input){
	set_placer(0);
	
	while (increment_placer()) node_placer->value = input;
}

template<typename Type>
void Clink<Type>::clear(){
	if (elements == 0) return;

	Node<Type>** buffer = new Node<Type>*[elements];

	int index = 0;
	set_placer(index);

	//Save pointers to each node in array
	while (increment_placer()) buffer[index++] = node_placer;

	//Call destructors on every node
	while (index > 0){
		delete &buffer[--index];
	}
	delete[] buffer;
}

template<typename Type>
void Clink<Type>::sort(){

}

template<typename Type>
bool Clink<Type>::set_placer(int index){
	if (index < 0) return false;

	node_placer = element_first;

	for (int i = 0; i < index; i++){
		if (node_placer->next == nullptr && i < index) return false; //if list ended before index reached
		node_placer = node_placer->next;
	}

	return true;
}

template<typename Type>
bool Clink<Type>::increment_placer(){
	//If next node DNE, return
	if (!(node_placer->next)) return false;

	node_placer = node_placer->next;
	return true;
}


template<typename Type>
void Clink<Type>::operator=(Clink<Type>& input){
	clear();
	input.set_placer(0);

	while (input.increment_placer()){
		push_back(input.get_placer());
	}
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