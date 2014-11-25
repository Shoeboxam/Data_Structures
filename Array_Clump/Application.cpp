#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>
#include <ctime>

#include "Clump.h"
#include "Clink.h"

int generateValue(int min, int max){
	return min + rand() % (max - min + 1);
}

template<typename Type>
void output(Type& input){
	for (int i = 0; i < input.get_elements(); i++){
		cout << input[i] << " ";
	}
	cout << endl;
}

int main(){
	//Seed random number generator
	srand(static_cast<int>(time(NULL)));

	Clink<int> randoms;

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
	Clink<int> randoms2 = randoms;
	cout << endl << "Clump == copy constructed clump?  " << (randoms2==randoms) << endl;

	randoms2.push_back(4);
	cout << "Clump == modified clump?   " << (randoms2 == randoms) << endl;

	cout << endl << "Sorted: " << endl;
	randoms.sort();
	output(randoms);

	cout << endl << "Const duplicate:" << endl;
	const Clink<int> randoms3(randoms);
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

	system("pause");
	return 0;
};