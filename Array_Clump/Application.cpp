#include <iostream>

#include <cstdlib>
#include <ctime>

#include "Clump.h"
#include "TestScores.h"

using std::cout;
using std::endl;

int generateValue(int min, int max){
	return min + rand() % (max - min + 1);
}

vector<int> generate_vector(int length){
	vector<int> buffer;

	for (int i = 0; i < length; i++){
		buffer.push_back(generateValue(45, 100));
	}

	return buffer;
}

int main(){
	//Seed random number generator
	srand(static_cast<int>(time(NULL)));

	TestScores classroom;

	for (int i = 0; i < 15; i++){
		cout << classroom.add_student(generate_vector(classroom.get_test_count()));
	}

	for (int i = 0; i < 5; i++){
		cout << classroom.add_test(generate_vector(classroom.get_student_count()));
	}

	cout << "Print all tests: \n";
	for (int elem : classroom.get_all_tests()){
		cout << elem << ", ";
	}
	cout << classroom.get_student_count() << endl;
	cout << classroom.get_test_count();

	cout << "Print student 10's scores: \n";
	for (int elem : classroom.get_student_scores(10)){
		cout << elem << ", ";
	}


	cout << "Standard deviation of class: \n";
	cout << classroom.get_standard_deviation() << endl;


	system("pause");
	return 0;
}