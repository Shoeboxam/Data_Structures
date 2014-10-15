#include <iostream>

#include <cstdlib>
#include <ctime>

#include "Clump.h"

int generateValue(int min, int max){
	return min + rand() % (max - min + 1);
}

void output(Clump input){
	for (int i = input.is_offset(); i < input.get_elements() + input.is_offset(); i++){
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

int main(){
	//Seed random number generator
	srand(static_cast<int>(time(NULL)));

	Clump randoms(true);

	for (int i = 0; i < 3; i++){
		randoms.append(generateValue(0, 100));
	}

	std::cout << std::endl << "Explicit output 1: " << randoms[randoms.is_offset()] << std::endl;
	std::cout << "Explicit output 2: " << randoms[randoms.is_offset()+1] << std::endl;
	std::cout << "Explicit output 3: " << randoms[randoms.is_offset()+2] << std::endl;

	std::cout << "3 Random numbers: " << std::endl;
	output(randoms);

	std::cout << std::endl << "Prepend 785: " << std::endl;
	randoms.prepend(785);
	output(randoms);

	std::cout << std::endl << "Append five: " << std::endl;
	randoms.append(5);
	output(randoms);

	std::cout << std::endl << "Explicit output 1: " << randoms[1] << std::endl;

	std::cout << std::endl << "Remove index 2: " << std::endl;
	randoms.remove(2);
	output(randoms);

	system("pause");
	return 0;
}