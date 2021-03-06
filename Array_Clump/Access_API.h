#ifndef ACCESS_H
#define ACCESS_H

template<typename Type>
class Access_API {
public:
	int elements;

	Access_API(){
		elements = 0;
	}

	//Getters
	virtual Type& get(int index) = 0;
	virtual Type get(int index) const = 0;

	virtual int get_elements() const { return elements; }
	virtual bool is_empty() const { return elements == 0; }

	virtual Type front() const { return get(0); }
	virtual Type back() const { return get(elements - 1); }

	//Mutators
	bool push_back(Type value) { return insert(value, elements); }
	bool push_front(Type value) { return insert(value, 0); }

	bool pop_back() { return remove(elements - 1); }
	bool pop_front() { return remove(0); }

	virtual bool insert(Type value, int index) = 0;
	virtual bool remove(int index) = 0;

	virtual void fill(Type) = 0;
	virtual void clear() = 0;

	virtual void sort();
};


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

#endif