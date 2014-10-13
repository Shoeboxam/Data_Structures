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

	Clump randoms;

	for (int i = 0; i < 75; i++){
		randoms.append(generateValue(0, 100));
	}

	for (int i = randoms.get_elements(); i <= 0; i--){
		std::cout << randoms[i] << " ";
	}

	system("pause");
	return 0;
}