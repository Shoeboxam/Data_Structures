#include "Clink.h"

template<typename Type>
Type Clink<Type>::get(int index){
	Node<Type>* element_current = element_first;

	for (int i = 0; i < index && element_current.node_next != nullptr; i++){
		element_current = *element_current.node_next;
	}
	return element_current.value;
}

template<typename Type>
bool Clink<Type>::set_placer(int index){
	element_placer = *element_first;

	for (int i = 0; i < index; i++){
		if (element_placer.next == nullptr && i < index) return false;
		element_placer = *element_placer.next;
	}

	return true;
}

template<typename Type>
bool Clink<Type>::insert(Type input, int index) {

	if (!set_placer(index - 1)) return false;

	Node<Type> node_new = new Node<Type>(input);

	node_new.next = node_placer->next;
	node_placer->next = *node_new;

	return true;
}

template<typename Type>
bool Clink<Type>::remove(int index){
	if (index == 0) {
		node_first = *node_first->next; //TODO: Fix memory leak here
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

}

template<typename Type>
void Clink<Type>::sort(){

}