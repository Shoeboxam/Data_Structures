#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <cstdlib>
#include <ctime>

#include "SimpleVector.h"
#include "SimpleLinked.h"
#include "SimpleLinked_Rollup.h"
#include "SimpleLinked_Vendor.h"


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

void output_values(SimpleLinked_Rollup<float>& input){
	for (int i = 0; i < input.get_elements(); i++){
		cout << input.get(i).value << " ";
	}
	cout << endl;
}

void output_sums(SimpleLinked_Rollup<float>& input){
	for (int i = 0; i < input.get_elements(); i++){
		cout << input.get(i).sum << " ";
	}
	cout << endl;
}

int main(){
	//Seed random number generator
	srand(static_cast<int>(time(NULL)));

	cout << "------------------------" << endl;
	cout << "__       Rollup       __" << endl << endl;


	SimpleLinked_Rollup<float> randoms_rolled;

	for (int i = 0; i < 20; i++){
		randoms_rolled.push_back(generateValue(0, 50));
	}

	cout << "Ten values:  ";
	output_values(randoms_rolled);

	//randoms_rolled.rollup(0);

	cout << "Rolled sums: ";
	output_sums(randoms_rolled);

	cout << endl;

	cout << "------------------------" << endl;
	cout << "__     Vendor List    __" << endl << endl;


	SimpleLinked_Vendor vendor_list;
	vendor_list.build_list("Vendor List File.txt");
	cout << "City: ";
	cout << vendor_list.get(2).get(0)._city;

	system("pause");
	return 0;
};