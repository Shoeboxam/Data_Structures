#ifndef SIMPLELINKED_ROLLUP_H
#define SIMPLELINKED_ROLLUP_H

#include "SimpleLinked.h"
#include <iostream>

template<typename Type>
class DataRollup {
public:
	Type value;
	Type sum;

	DataRollup(){}
	DataRollup(float value_req) : value(value_req), sum(value_req) {}

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
class SimpleLinked_Rollup : public SimpleLinked<DataRollup<Type>> {
	

public:
	bool rollup(int index);
	SimpleLinked_Rollup(){}

	virtual bool insert(Type value, int index);
	virtual bool remove(int index);

	Type get_sum(int index);
};


template<typename Type>
bool SimpleLinked_Rollup<Type>::rollup(int index){
	Type sum_last = 0;
	bool loop_continue;

	set_placer(index);
	if (index != 0) sum_last = get(index - 1).sum;

	do {
		node_placer->value.sum = sum_last + node_placer->value.value;
		sum_last = node_placer->value.sum;
	} while (increment_placer());
	return true;
}

template<typename Type>
bool SimpleLinked_Rollup<Type>::insert(Type value, int index){
	cout << "Test";
	return (SimpleLinked<DataRollup<Type>>::insert(*new DataRollup<Type>(value), index) && rollup(index));
}

template<typename Type>
bool SimpleLinked_Rollup<Type>::remove(int index){
	return (SimpleLinked<DataRollup<Type>>::remove(index) && rollup(index));
}

template<typename Type>
Type SimpleLinked_Rollup<Type>::get_sum(int index){
	return get(index)->value.sum;
}

#endif