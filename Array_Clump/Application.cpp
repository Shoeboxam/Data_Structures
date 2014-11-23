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

void output(Clink<int>& input){
	for (int i = 0; i < input.get_elements(); i++){
		cout << input[i] << " ";
	}
	cout << endl;
}

int main(){
	//Seed random number generator
	srand(static_cast<int>(time(NULL)));

	Clink<int> randoms;

	for (int i = 0; i < 10; i++){
		cout << randoms.push_back(generateValue(0, 100)) << endl;
	}

	cout << endl;
	cout << "Explicit output 1: " << randoms[0] << endl;
	cout << "Explicit output 2: " << randoms[1] << endl;
	cout << "Explicit output 3: " << randoms[2] << endl;

	cout << "3 Random numbers: " << endl;
	output(randoms);

	cout << endl << "Prepend 785: " << endl;
	randoms.push_front(785);
	output(randoms);

	cout << endl << "Append five: " << endl;
	randoms.push_back(5);
	output(randoms);

	cout << endl << "Explicit output 1: " << randoms[1] << endl;

	cout << endl << "Remove index 2: " << endl;
	randoms.remove(2);
	output(randoms);

	cout << endl << "Insert to index 2: " << endl;
	randoms.insert(41, 2);
	output(randoms);

	cout << endl << "Front: " << randoms.front() << endl;
	cout << endl << "Back: " << randoms.back() << endl;


	Clink<int> randoms2 = randoms;
	cout << endl << "Clump == identical clump?  " << (randoms2==randoms) << endl;

	randoms2.push_back(4);
	cout << "Clump == modified clump?   " << (randoms2 == randoms) << endl;

	cout << "Sorted" << endl;
	randoms.sort();
	output(randoms);

	cout << endl << "Fill with zeros: " << endl;
	randoms.fill(0);
	output(randoms);

	cout << endl << "Clear: " << endl;
	randoms.clear();
	output(randoms);

	system("pause");
	return 0;
};