#include <math.h>
#include <vector>
using std::vector;

struct Filter{
	float standard_deviation(const vector<int> &data) const;
	float average(const vector<int> &data) const;
	vector<int> get_bandpass(const vector<int> &data, int min, int max) const;

	float operator()(const vector<int> &data) const { return standard_deviation(data); }
};

float Filter::average(const vector<int> &data) const{
	float mean = 0;
	for (int elem : data){
		mean += elem;
	}
	mean /= data.size();
	return mean;
}

float Filter::standard_deviation(const vector<int> &data) const{
	float variance = 0;
	float mean = average(data);
	for (int elem : data){
		variance += std::pow(elem - mean, 2);
	}

	return std::sqrt(variance / data.size());
}

vector<int> Filter::get_bandpass(const vector<int> &data, int min, int max) const {
	vector<int> buffer;
	for (int elem : data){
		if (elem >= min && elem <= max){
			buffer.push_back(elem);
		}
	}
	return buffer;
}