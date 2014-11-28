
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