#ifndef SimpleLinked_H
#define SimpleLinked_H

#include "Access_API.h"
#include <iostream>

template<typename Type>
class SimpleLinked : public Access_API<Type> {

	template<typename Type>
	class Node {
	public:
		Type value;
		Node<Type>* next;

		Node(){ next = nullptr; }
		Node(const Type& input){ value = input; next = nullptr; }

		ostream& operator<<(ostream& out_stream){
			return out_stream << value;
		}
	};

	Node<Type>* element_first = new Node<Type>;
	Node<Type>* element_last = new Node<Type>;

protected:
	Node<Type>* node_placer;


public:

	SimpleLinked(){}
	SimpleLinked(SimpleLinked<Type>& input);
	~SimpleLinked();

	Type& get(int index);
	Type get(int index) const;

	bool set_placer(int index);

	Type get_placer() { return node_placer->value; }
	bool increment_placer();

	bool insert(Type value, int index);
	bool remove(int index);

	void fill(Type);
	void clear();

	Type& operator[](int index);
	Type operator[](int index) const;

	void operator=(SimpleLinked& input);
	bool operator==(SimpleLinked& input);
};


template<typename Type>
SimpleLinked<Type>::~SimpleLinked(){
	clear();
}

template<typename Type>
SimpleLinked<Type>::SimpleLinked(SimpleLinked<Type>& input){
	*this = input;
}


template<typename Type>
Type& SimpleLinked<Type>::get(int index){
	Node<Type>* element_current = element_first;

	for (int i = 0; i < index && element_current->next != nullptr; i++){
		element_current = element_current->next;
	}
	return element_current->value;
}

template<typename Type>
Type SimpleLinked<Type>::get(int index) const{
	Node<Type>* element_current = element_first;

	for (int i = 0; i < index && element_current->next != nullptr; i++){
		element_current = element_current->next;
	}
	return element_current->value;
}

template<typename Type>
bool SimpleLinked<Type>::insert(Type input, int index) {

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
bool SimpleLinked<Type>::remove(int index){
	if (index == 0) {
		element_first = element_first->next; //TODO: Fix memory leak here
	}

	if (!set_placer(index - 1)) return false;

	node_placer->next = node_placer->next->next; //Yeaugh

	elements--;
	return true;
}


template<typename Type>
void SimpleLinked<Type>::fill(Type input){
	set_placer(0);

	do {
		node_placer->value = input;
	} while (increment_placer());
}

template<typename Type>
void SimpleLinked<Type>::clear(){
	if (elements == 0) return;

	Node<Type>** buffer = new Node<Type>*[elements];

	int index = 0;
	set_placer(index);

	//Save pointers to each node in array
	while (increment_placer()) buffer[index++] = node_placer;

	//Call destructors on every node
	while (index > 0){
		delete buffer[--index];
	}
	delete[] buffer;

	elements = 0;
}

template<typename Type>
bool SimpleLinked<Type>::set_placer(int index){
	if (index < 0) return false;

	node_placer = element_first;

	for (int i = 0; i < index; i++){
		if (node_placer->next == nullptr && i < index) return false; //if list ended before index reached
		node_placer = node_placer->next;
	}

	return true;
}

template<typename Type>
bool SimpleLinked<Type>::increment_placer(){
	//If next node DNE, return
	if (!(node_placer->next)) return false;

	node_placer = node_placer->next;
	return true;
}


template<typename Type>
void SimpleLinked<Type>::operator=(SimpleLinked<Type>& input){
	clear();
	input.set_placer(0);

	do {
		push_back(input.get_placer());
	} while (input.increment_placer());
}

template<typename Type>
Type& SimpleLinked<Type>::operator[](int index){
	return get(index);
}

template<typename Type>
Type SimpleLinked<Type>::operator[](int index) const {
	return get(index);
}

template<typename Type>
bool SimpleLinked<Type>::operator==(SimpleLinked& input){
	if (elements != input.get_elements()) return false;

	set_placer(0);

	while (increment_placer() && input.increment_placer()){
		if (get_placer() != input.get_placer()) return false;
	}

	return true;
}

#endif