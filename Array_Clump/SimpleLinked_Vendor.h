#ifndef SIMPLELINKED_VENDOR_H
#define SIMPLELINKED_VENDOR_H


#include "SimpleLinked.h" //Same file from part B
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>

#include <string>
#include <vector>
using std::string;
using std::vector;

struct Vendor {
	Vendor(){}

	Vendor(vector<string> input){
		set(input);
	}

	int _ID;
	string _name, _city, _state, _zip;

	bool operator<(Vendor& input){
		return _ID < input._ID;
	}

	bool operator>(Vendor& input){
		return _ID > input._ID;
	}

	friend ostream& operator<<(ostream& base, Vendor& input){
		cout << " " << input._name 
			<< " at " << input._city << " " << input._state << " " << input._zip << endl;
		return base;
	}

	void set(vector<string>& input){ 
		_ID = std::stoi(input[0]);
		_name = input[1]; 
		_city = input[2];
		_state = input[3];
		_zip = input[4];
	}
};


class IndexNode : public SimpleLinked<Vendor> {
public:
	string _state_IndexNode = "NA";

	IndexNode() : SimpleLinked(){}

	IndexNode(string state) : SimpleLinked() { 
		_state_IndexNode = state; 
		cout << "Created State Node: " << _state_IndexNode << endl;
	}

	friend bool operator<(IndexNode& base, IndexNode& input){
		return base._state_IndexNode < input._state_IndexNode;
	}

	friend bool operator>(IndexNode& base, IndexNode& input){
		return base._state_IndexNode > input._state_IndexNode;
	}

	void operator=(IndexNode& input){
		clear();
		input.set_placer(0);
		do {
			push_back(input.node_placer->value);
		} while (input.increment_placer());
	}

	friend ostream& operator<<(ostream& base, IndexNode& input){
		base << endl << "STATE " << input._state_IndexNode << endl;
		input.set_placer(0);
		do {
			if (input.node_placer->value._ID >= 0){
				base << input.node_placer->value;
			}
		} while (input.increment_placer());

		return base;
	}
};


class SimpleLinked_Vendor : public SimpleLinked<IndexNode> {
	//Hide inherited insert
	SimpleLinked<IndexNode>::insert;

public:

	SimpleLinked_Vendor() : SimpleLinked(){}

	bool add_vendor(Vendor& input);
	bool build_list(string filename);



	friend ostream& operator<<(ostream& base, SimpleLinked_Vendor& input){
		input.set_placer(0);
		do {
			base << input.node_placer->value;
		} while (input.increment_placer());
		return base;
	}
};

bool SimpleLinked_Vendor::add_vendor(Vendor& input){

	bool match = false;

	set_placer(0);
	if (elements != 0){
		do {
			if (node_placer->value._state_IndexNode == input._state){
				match = true;
			}
		} while (increment_placer() && !match);
	}

	if (!match){
		insert(*new IndexNode());
	}
	node_placer->value._state_IndexNode = input._state;

	//Set node placer to correct index node
	set_placer(0);
	while (input._state != node_placer->value._state_IndexNode && increment_placer()) { }

	node_placer->value.insert(input);

	return true;
}

bool SimpleLinked_Vendor::build_list(string filename){
	string line;
	std::ifstream file_input;

	file_input.open(filename);
	if (file_input.is_open()){

		getline(file_input, line);
		getline(file_input, line);
		getline(file_input, line);
		getline(file_input, line);

		while (!file_input.eof()){
			vector<string> delimited;

			getline(file_input, line);
			if (line.size() < 75) return false;

			delimited.push_back(line.substr(0, 10));
			delimited.push_back(line.substr(12, 31));
			delimited.push_back(line.substr(45, 16));
			delimited.push_back(line.substr(62, 2));
			delimited.push_back(line.substr(74, 5));

			add_vendor(*new Vendor(delimited));
		}
	}

	return true;
}

#endif