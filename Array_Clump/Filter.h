#include <math.h>
#include <vector>
using std::vector;

struct Filter{
	float standard_deviation(vector<int> &data) const;
	float average(vector<int> &data) const;

	float operator()(vector<int> data) const { return standard_deviation(data); }
};

float Filter::average(vector<int> &data) const{
	float mean = 0;
	for (int elem : data){
		mean += elem;
	}
	mean /= data.size();
	return mean;
}

float Filter::standard_deviation(vector<int> &data) const{
	float variance = 0;
	float mean = average(data);
	for (int elem : data){
		variance += std::pow(elem - mean, 2);
	}

	return std::sqrt(variance / data.size());
}