#ifndef SIMPLELINKED_ROLLUP_H
#define SIMPLELINKED_ROLLUP_H

#include "SimpleLinked.h" //Same file from part B

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
	
	SimpleLinked<DataRollup<Type>>::insert;
	SimpleLinked<DataRollup<Type>>::remove;

public:


	bool push_back(Type value) { return insert(value, elements); }
	bool push_front(Type value) { return insert(value, 0); }

	bool pop_back() { return remove(elements - 1); }
	bool pop_front() { return remove(0); }

	bool rollup(int index);
	SimpleLinked_Rollup(){}

	bool insert(Type value, int index);
	bool remove(int index);

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