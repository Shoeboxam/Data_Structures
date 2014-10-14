#include <iostream>

#include <cstdlib>
#include <ctime>

#include "Clump.h"

int generateValue(int min, int max){
	return min + rand() % (max - min + 1);
}

void output(Clump input){
	for (int i = input.get_elements() - 1; i > 0; i--){
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

int main(){
	//Seed random number generator
	srand(static_cast<int>(time(NULL)));

	Clump randoms(true);

	for (int i = 0; i <= 5; i++){
		randoms.append(generateValue(0, 100));
	}

	std::cout << "Random" << std::endl;
	output(randoms); //This one runs fine
	output(randoms); //This one corrupts the heap...

	system("pause");
	return 0;
}