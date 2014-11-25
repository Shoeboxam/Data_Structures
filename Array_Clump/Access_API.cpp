
//Features implemented in the API cannot be optimized for the data structure. 
//I could rewrite the sort swapper in child classes to optimize away get calls
//For instance, get calls are calculated in linear time on linked lists...
// ...node_placer can eliminate the get calls entirely to reduce computational complexity
template<typename Type>
void Access_API<Type>::sort(){
	int gap = elements;
	float shrink = 1.3;
	bool swapped = false;

	while (gap != 1 || swapped == true){
		gap /= shrink;
		if (gap < 1) gap = 1;

		swapped = false;
		for (int index = 0; index + gap < elements; index++){
			if (get(index) > get(index + gap)){

				//Swap!
				Type buffer = get(index + gap);
				get(index + gap) = get(index);
				get(index) = buffer;

				swapped = true;
			}
		}
	}
}