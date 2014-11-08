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

	Clump<int> randoms(2 /*Dimensions*/);

	randoms.append(23, vector < int > {1, 5});

	//randoms.

	system("pause");
	return 0;
}