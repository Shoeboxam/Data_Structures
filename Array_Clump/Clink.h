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

		Node(){ next = nullptr; }
		Node(const Type& input){ value = input; next = nullptr; }
		~Node(){
			delete next;
		}
	};

	Node<Type>* element_first;
	Node<Type>* element_last;

	Node<Type>* node_placer;


public:

	Clink(){}
	Clink(Clink<Type>& input);
	~Clink();

	Type get(int index);
	bool set_placer(int index);

	Type get_placer() { return node_placer->value; }
	bool increment_placer();

	bool insert(Type value, int index);
	bool remove(int index);

	void fill(Type);
	void clear();

	void sort();

	void operator=(Clink& input);
	Type operator[](int index);
	bool operator==(Clink& input);
};

#include "Clink.cpp"
#endif