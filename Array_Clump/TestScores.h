#include "Clump.h"
#include "Filter.h"

class TestScores{
	Filter mathFilter;
	Clump<int> Students;
	int student_id = 0;
	int test_id = 0;

public:
	TestScores(){}

	vector<int> get_student_scores(int mStudent_id) const;
	float get_student_average(int mStudent_id) const;
	float get_class_average() const;
	float get_standard_deviation() const;

	int get_test_count() { return Students.get_height(); }
	int get_student_count() { return Students.get_width(); }

	vector<int> get_all_tests() { return Students.get(); }


	bool add_student(vector<int> scores) { return student_id++, Students.append_column(scores); }
	bool add_test(vector<int> scores) { return test_id++, Students.append_row(scores); }
	
};



vector<int> TestScores::get_student_scores(int student_id) const{
	return Students.get_column(student_id);
}

float TestScores::get_student_average(int student_id) const{
	return mathFilter.average(get_student_scores(student_id));
}

float TestScores::get_class_average() const{
	return mathFilter.average(Students.get());
}

float TestScores::get_standard_deviation() const{
	return mathFilter(Students.get());
}