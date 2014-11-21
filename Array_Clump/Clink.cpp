#include "Clink.h"

template<typename Type>
class Clink<Type>::Node {
public:
	Type value;
	Node<Type>* _next;

	Node(const Type& input);
	~Node();
};

template<typename Type>
Clink<Type>::Node<Type>::~Node(){
	delete *next_node;
}


template<typename Type>
Clink<Type>::Node<Type>::Node(const Type& input) { 
	value = *input;
	Node<Type>* first = NULL;
}

template<typename Type>
Type Clink<Type>::get_value(int index){

}

template<typename Type>
bool Clink<Type>::insert(Type input, int index) {
	_next = *new Node<Type>(input);
}

template<typename Type>
bool Clink<Type>::remove(int index){

}


template<typename Type>
void Clink<Type>::fill(Type){

}

template<typename Type>
void Clink<Type>::clear(){

}


template<typename Type>
void Clink<Type>::sort(){

}