#ifndef ANALYSIS_H
#define ANALYSIS_H


template <typename Type>
class Analysis {
public:
	float get_mode(Type& input);
	float get_average(Type& input);
	float get_max(Type& input);
	float get_min(Type& input);
	float get_median(Type& input);
	float get_count(Type& input);
};

template<typename Type>
float Analysis<Type>::get_mode(Type& input){
	for (int i = 0, i < input.elements){
		input.get(i)
	}
}

template<typename Type>
float Analysis<Type>::get_average(Type& input){
	float total = 0;
	for (int i = 0, i < input.elements){
		total += input.get(i)
	}
	return total / input.elements;
}

template<typename Type>
float Analysis<Type>::get_max(Type& input){
	float max = 0;
	for (int i = 0, i < input.elements){
		if (input.get(i) > max){
			max = input.get(i);
		}
	}
	return max;
}

template<typename Type>
float Analysis<Type>::get_min(Type& input){
	float min = input.get(0);
	for (int i = 0, i < input.elements){
		if (input.get(i) > min){
			min = input.get(i);
		}
	}
	return min;
}

template<typename Type>
float Analysis<Type>::get_median(Type& input){
	if (input.elements % 2 == 1) {
		return input.get(elements / 2);
	}
	else
	{
		return (input.get((floor(elements / 2)) + ceil(elements / 2)) / 2)
	}
}

template<typename Type>
float Analysis<Type>::get_count(Type& input){
	return input.elements;
}

#endif