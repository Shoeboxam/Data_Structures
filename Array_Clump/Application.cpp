#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <cstdlib>
#include <ctime>

#include "SimpleVector.h"
#include "SimpleLinked.h"
#include "SimpleLinked_Rollup.h"


int generateValue(int min, int max){
	return min + rand() % (max - min + 1);
}

struct DataRollup {
	float value = generateValue(0, 100);
	float sum;

	bool operator<(DataRollup& input){
		return value < input.value;
	}

	bool operator>(DataRollup& input){
		return value > input.value;
	}
};

template<typename Type>
void output(Type& input){
	for (int i = 0; i < input.get_elements(); i++){
		cout << input[i] << " ";
	}
	cout << endl;
}

void output_values(SimpleLinked_Rollup<DataRollup>& input){
	for (int i = 0; i < input.get_elements(); i++){
		cout << input.get_value(i) << " ";
	}
	cout << endl;
}

template<typename Type>
void output_sums(SimpleLinked_Rollup<DataRollup>& input){
	for (int i = 0; i < input.get_elements(); i++){
		cout << SimpleLinked_Rollup<int>(input.get_sum(i)) << " ";
	}
	cout << endl;
}

int main(){
	//Seed random number generator
	srand(static_cast<int>(time(NULL)));

	SimpleLinked<int> randoms;

	cout << endl << "Append ten random numbers: " << endl;
	for (int i = 0; i < 10; i++){
		randoms.push_back(generateValue(0, 100));
	}
	output(randoms);

	cout << endl << "Prepend 785: " << endl;
	randoms.push_front(785);
	output(randoms);

	cout << endl << "Subscript accessor [1]: " << randoms[1] << endl;

	cout << endl << "Remove index 2: " << endl;
	randoms.remove(2);
	output(randoms);

	cout << endl << "Insert to index 2: " << endl;
	randoms.insert(41, 2);
	output(randoms);

	cout << endl << "Front: " << randoms.front() << endl;
	cout << endl << "Back: " << randoms.back() << endl;

	cout << endl << "Node Placer: " << randoms.get_placer() << endl;
	SimpleLinked<int> randoms2 = randoms;
	cout << endl << "SimpleVector == copy constructed SimpleVector?  " << (randoms2==randoms) << endl;

	randoms2.push_back(4);
	cout << "SimpleVector == modified SimpleVector?   " << (randoms2 == randoms) << endl;

	cout << endl << "Sorted: " << endl;
	randoms.sort();
	output(randoms);

	cout << endl << "Const duplicate:" << endl;
	const SimpleLinked<int> randoms3(randoms);
	output(randoms3);

	randoms.set_placer(2);
	cout << endl << "Node Placer: " << randoms.get_placer() << endl;
	randoms.increment_placer();
	cout << "Incremented Node Placer: " << randoms.get_placer() << endl;

	cout << endl << "Fill with zeros: " << endl;
	randoms.fill(0);
	output(randoms);

	cout << endl << "Clear: " << endl;
	randoms.clear();
	output(randoms);

	SimpleLinked_Rollup<DataRollup> randoms_rolled;

	for (int i = 0; i < 10; i++){
		randoms_rolled.push_back(*new DataRollup());
	}
	output_values(randoms_rolled);

	randoms_rolled.set_placer(5);
	//output_sums(randoms_rolled);

	system("pause");
	return 0;
};