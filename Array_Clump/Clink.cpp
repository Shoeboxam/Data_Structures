#include "Clink.h"

template<typename Type>
Type Clink<Type>::get(int index){

}

template<typename Type>
bool Clink<Type>::insert(Type input, int index) {
	_next = *new Node<Type>(input);
}

template<typename Type>
bool Clink<Type>::remove(int index){
	return true; //TODO
}


template<typename Type>
void Clink<Type>::fill(Type value){

}

template<typename Type>
void Clink<Type>::clear(){

}

template<typename Type>
void Clink<Type>::sort(){

}