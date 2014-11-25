#ifndef CLINK_H
#define CLINK_H

#include "Access_API.h"

//TODO: Equivalency
//TODO: Fill
//TODO: Clear
//TODO: Sort

template<typename Type>
class Clink : public Access_API<Type> {

	template<typename Type>
	class Node {
	public:
		Type value;
		Node<Type>* next;

		Node(){ next = nullptr; }
		Node(const Type& input){ value = input; next = nullptr; }
		~Node(){ }
	};

	Node<Type>* element_first = new Node<Type>;
	Node<Type>* element_last = new Node<Type>;

	Node<Type>* node_placer;


public:

	Clink(){}
	Clink(Clink<Type>& input);
	~Clink();

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

	void operator=(Clink& input);
	bool operator==(Clink& input);
};

#include "Clink.cpp"
#endif