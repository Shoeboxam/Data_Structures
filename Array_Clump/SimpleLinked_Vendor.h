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

	string _ID, _name, _city, _state, _zip;

	bool operator<(Vendor& input){
		return _ID < input._ID;
	}

	bool operator>(Vendor& input){
		return _ID > input._ID;
	}

	friend ostream& operator<<(ostream& base, Vendor& input){
		base << endl
			<< " --------------------" << endl
			<< " ID    " << input._ID << endl
			<< " Name  " << input._name << endl
			<< " City  " << input._city << endl
			<< " State " << input._state << endl
			<< " Zip   " << input._zip << endl;
		return base;
	}

	void set(vector<string>& input){ 
		_ID = input[0];
		_name = input[1]; 
		_city = input[2];
		_state = input[3];
		_zip = input[4];
	}

	//bool set_ID(string ID){ _ID = stoi(ID); }

	//void set_ID(int ID){ _ID = ID; }
	//void set_name(string name){ _name = name; }
	//void set_city(string city){ _city = city; }
	//void set_state(string state){ _state = state; }
	//void set_zip(string zip){ _zip = zip; }

	//int get_ID(){ return _ID; }
	//string get_name(){ return _name; }
	//string get_city(){ return _city; }
	//string get_state(){ return _state; }
	//string get_zip(){ return _zip; }
};


class IndexNode : public SimpleLinked<Vendor> {
public:
	string _state_IndexNode;

	IndexNode() : SimpleLinked(){}

	IndexNode(string state) : SimpleLinked() { _state_IndexNode = state; }

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

		input.set_placer(0);
		do {
			base << input.node_placer->value;
		} while (input.increment_placer());

		return base;
	}
};


class SimpleLinked_Vendor : public SimpleLinked<IndexNode> {
	//Hide inherited insert
	SimpleLinked<IndexNode>::insert;
	bool add_state(IndexNode value){
		SimpleLinked<IndexNode>::insert(value);
	}

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
	set_placer(0);

	bool match = false;
	do {
		if (node_placer->value._state_IndexNode == input._state){
			match = true;
		}
	} while (increment_placer() && !match);
	if (!match){
		insert(*new IndexNode(input._state));
	}
	//Set node pointer to correct index node
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
			cout << line << endl;
			if (line.size() < 75) return false;

			delimited.push_back(line.substr(0, 10));
			delimited.push_back(line.substr(12, 31));
			delimited.push_back(line.substr(45, 15));
			delimited.push_back(line.substr(62, 10));
			delimited.push_back(line.substr(74, 5));

			Vendor buffer = *new Vendor(delimited);
			cout << buffer;
			add_vendor(*new Vendor(delimited));
		}
	}

	return true;
}

#endif