#include "Clump.h"

class ClumpArray{
	//Array of pointers to arrays of ints
	Clump<Clump<int>> * ptr = new Clump<Clump<int>>[];

	void reallocate(int degree);

public:
	ClumpArray(bool offset = false);
	ClumpArray(ClumpArray&);
	~ClumpArray();

	bool get_row(int index);
	bool get_column(int index);

	bool insert_row(int value, int index);
	bool insert_column(int value, int index);

	bool remove_row(int index);
	bool remove_column(int index);
};