#ifndef SIMPLELINKED_ROLLUP_H
#define SIMPLELINKED_ROLLUP_H

#include "SimpleLinked.h"

class DataRollup {
public:
	float value;
	float sum;

	DataRollup(){}
	DataRollup(float value_req) : value(value_req), sum(0) {}

	bool operator<(DataRollup& input){
		return value < input.value;
	}

	bool operator>(DataRollup& input){
		return value > input.value;
	}

	friend ostream& operator<<(ostream& out_stream, DataRollup& input){
		return out_stream << input.value;
	}
};

template<typename Type>
class SimpleLinked_Rollup : public SimpleLinked<DataRollup> {
	
	void rollup(int index);

public:

	template<typename Type>
	bool insert(Type value, int index);

	template<typename Type>
	bool remove(int index);

	template<typename Type>
	Type get_sum(int index);
};


template<typename Type>
void rollup(int index){
	set_placer(index - (index > 0));

	Type sum_last;
	bool loop_continue;

	do {
		sum_last = node_placer->sum;
		loop_continue = increment_placer();
		node_placer->sum = sum_last + node_placer->value;
	} while (loop_continue);
}

template<typename Type>
bool insert(Type value, int index){
	bool success = SimpleLinked<Type>::insert(value, index);
	rollup(index);

	return success;
}

template<typename Type>
bool remove(int index){
	bool success = SimpleLinked<Type>::insert(index);
	rollup(index);

	return success;
}

template<typename Type>
Type get_sum(int index){
	set_placer(index);
	return node_placer->sum;
}

#endif