#include <iostream>

#include <cstdlib>
#include <ctime>

#include "Clump.h"

int generateValue(int min, int max){
	return min + rand() % (max - min + 1);
}

void output(Clump input){
	for (int i = 1; i < input.get_elements() - 1; i++){
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

int main(){
	//Seed random number generator
	srand(static_cast<int>(time(NULL)));

	Clump randoms(true);

	for (int i = 0; i <= 8; i++){
		randoms.append(generateValue(0, 100));
	}

	std::cout << "Random" << std::endl;
	output(randoms);
	randoms.append(4);
	randoms.append(5);
	randoms.append(6);
	output(randoms);

	system("pause");
	return 0;
}