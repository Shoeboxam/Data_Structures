#ifndef CLINK_H
#define CLINK_H

template<typename Type>
class Clink {
public:
	Type value;
	Clink<Type>* _next = NULL;

	Clink(const Type& input) { value = input; Clink<Type>* next_node = NULL}
	~Clink() { delete *next_node; }

	bool add(Type input) { next = *new Clink<Type>(input) }
};


#endif