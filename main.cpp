/*
 * CS 555 WS
 * Project 02 - GEDCOM parser
 * Clara Gail Ramos
 * I pledge my honor that I have abided by the Stevens Honor System.
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
 * Global variables
 * data = current string pulled from GEDCOM file
 * tag = line's tag; if N/A, "Invalid tag"
 */
string data, tag;
fstream test, result;

/*
 * Current line's level is 0
 * parses through the line looking for applicable tag
 * prints the line, level, and tag to output and to output.txt
 */
int foundAZero() {
	cout << data << " ";
	result << data << " ";
	test >> data;
	if(data == "HEAD" || data == "TRLR" || data == "NOTE") {
		tag = data;
		cout << data << '\n';
		result << data << endl;
	} else if(data[0] == '@') {
		cout << data << " ";
		result << data << " ";
		test >> data;
		if(data == "INDI" || data == "FAM") {
			tag = data;
			cout << data << '\n';
			result << data << endl;
		} else {
			tag = "Invalid tag";
			cout << data;
			result << data;
			getline(test, data);
			cout << data << '\n';
			result << data << endl;
		}
	} else {
		tag = "Invalid tag";
		cout << data;
		result << data;
		getline(test, data);
		cout << data << '\n';
		result << data << endl;
	}
	cout << "0" << '\n';
	cout << tag << '\n';
	result << "0" << endl;
	result << tag << endl;
	return 0;
}

/*
 * Current line's level is 1
 * parses through the line looking for tag
 * prints line, level, and tag to output and output.txt
 */
int foundAOne() {
	cout << data << " ";
	result << data << " ";
	test >> data;
	if(data == "NAME") {
		tag = data;
		cout << data;
		result << data;

		getline(test, data);
		cout << data << '\n';
		result << data << endl;
	} else if(data == "SEX" || data == "FAMC" || data == "FAMS" || data == "HUSB" || data == "WIFE" || data == "CHIL") {
		tag = data;
		cout << data;
		result << data;
		getline(test, data);
		cout << data << '\n';
		result << data << endl;
	} else if(data == "BIRT" || data == "MARR" || data == "DIV") {
		tag = data;
		cout << data << '\n';
		result << data << endl;
	} else if(data == "DEAT") {
		tag = data;
		cout << data;
		result << data;
		getline(test, data);
		cout << data << '\n';
		result << data << endl;
	} else {
		tag = "Invalid tag";
		cout << data;
		result << data;
		getline(test, data);
		cout << data << '\n';
		result << data << endl;
	}
	cout << "1" << '\n';
	cout << tag << '\n';
	result << "1" << endl;
	result << tag << endl;
	return 0;
}

/*
 * Current line's level is 2
 * parses through the line looking for tag
 * prints line, level, and tag to output and output.txt
 */
int foundATwo() {
	cout << data << " ";
	result << data << " ";
	test >> data;
	if(data == "DATE") {
		tag = data;
		cout << data;
		result << data;
		getline(test, data);
		cout << data << '\n';
		result << data << endl;
	} else {
		tag = "Invalid tag";
		cout << data;
		result << data;
		getline(test, data);
		cout << data << '\n';
		result << data << endl;
	}
	cout << "2" << '\n';
	cout << tag << '\n';
	result << "2" << endl;
	result << tag << endl;
	return 0;
}

/*
 * opens GEDCOM file and creates new output.txt
 * reads the level of each line and runs appropriate function
 * if unrecognized, prints error message and terminates program
 */
int main() {
	test.open("GEDCOM_test.ged", ios::in);
	result.open("output.txt", ios::out);

	test >> data;
	while(!test.eof()) {
		if(data[0] == '0') {
			foundAZero();
		} else if(data[0] == '1') {
			foundAOne();
		} else if(data[0] == '2') {
			foundATwo();
		} else {
			cerr << "Error: unrecognizable level. Program Terminated" << '\n';
			result << "Error: unrecognizable level. Program Terminated" << '\n';
			return -1;
		}
		test >> data;
	}

	test.close();
	result.close();
	return 0;
}


