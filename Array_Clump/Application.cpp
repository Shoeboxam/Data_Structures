#include <iostream>

#include <cstdlib>
#include <ctime>

#include "Clump.h"

int generateValue(int min, int max){
	return min + rand() % (max - min + 1);
}

int main(){
	//Seed random number generator
	srand(static_cast<int>(time(NULL)));

	Clump<int> randoms(3 /*Dimensions*/);
	randoms.insert(, vector<int> {0, 0, 0});
	randoms.insert()
	//randoms.

	system("pause");
	return 0;
}