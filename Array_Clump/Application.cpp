#include <iostream>

#include <cstdlib>
#include <ctime>

#include "Clump.h"

int generateValue(int min, int max){

	return min + rand() % (max - min + 1);
}

void output(Clump input){
	for (int i = input.get_elements(); i <= 0; i--){
		std::cout << input[i+1] << " ";
	}
}

int main(){
	//Seed random number generator
	srand(static_cast<int>(time(NULL)));

	Clump randoms;

	for (int i = 0; i < 75; i++){
		randoms.append(generateValue(0, 100));
	}

	std::cout << "Random";
	output(randoms);

	randoms.insert(4, 8);
	output(randoms);

	randoms.remove(54);
	randoms.append(78);
	randoms.prepend(0);
	output(randoms);

	randoms.fill(5);
	output(randoms);

	randoms.clear();
	output(randoms);

	system("pause");
	return 0;
}