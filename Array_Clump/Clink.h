#ifndef CLINK_H
#define CLINK_H

#include "Access_API.h"

template<typename Type>
class Clink : public Access_API<Type> {

	template<typename Type>
	class Node {
	public:
		Type value;
		Node<Type>* next;

		Node(const Type& input){
			value = input;
			Node<Type>* first = nullptr;
		}
		~Node(){
			delete *next;
		}
	};

	Node<Type>* element_first;
	Node<Type>* element_last;
	Node<Type>* element_placer;

	bool set_placer(int index);

public:

	Clink();
	~Clink();

	Type get(int index);

	bool insert(Type value, int index);
	bool remove(int index);

	void fill(Type);
	void clear();

	void sort();
};


#endif