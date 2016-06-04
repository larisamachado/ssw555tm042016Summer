/* CS 555 WS
 * Project 03 - GEDCOM parser : Save INDIs and FAMs
 * Clara Ramos, Larisa Machado, Varun Kumar
 * We pledge our honor that we have abided by the Stevens Honor System.
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* Global variables
 * data = current string pulled from GEDCOM file
 * tag = line's tag; if N/A, "Invalid tag"
 * test = file that code is parsing through
 * result = file where output is printed
 * firstNames = array that holds the first name of each individual
 * lastNames = array that holds the last name of each individual
 * FAMs = array that holds each family
 * indiv = flag that dictates if the info being read is from an INDI
 * it = iterator for firstNames and lastNames
 */
string data, tag = "Invalid tag";
fstream test, result;
string firstNames[5000];
string lastNames[5000];
string FAMs[1000];
bool indiv = false;
int it = 0;

/* Takes in the line's current level
 * prints the level to output and output.txt
 */
void printLevel(string s) {
	cout << s << '\n';
	cout << tag << '\n';
	result << s << endl;
	result << tag << endl;
}

//prints what's currently in data and the rest of the line
void restOfLine() {
	cout << data;
	result << data;
	getline(test, data);
	cout << data << '\n';
	result << data << endl;
}

/* Current line's level is 0
 * parses through the line looking for applicable tag
 * prints the line, level, and tag to output and to output.txt
 */
int foundAZero() {
	test >> data;
	if(data == "HEAD" || data == "TRLR" || data == "NOTE") {
		indiv = false;
		tag = data;
		cout << data << '\n';
		result << data << endl;
	} else if(data[0] == '@') {
		cout << data << " ";
		result << data << " ";
		test >> data;
		if(data == "INDI" || data == "FAM") {
			if(data == "INDI") {
				indiv = true;
				it++;
			}
			tag = data;
			cout << data << '\n';
			result << data << endl;
		} else {
			indiv = false;
			restOfLine();
		}
	} else {
		indiv = false;
		restOfLine();
	}
	return 0;
}

/* Current line's level is 1
 * parses through the line looking for tag
 * prints line, level, and tag to output and output.txt
 */
int foundAOne() {
	test >> data;
	if(data == "NAME" || data == "SEX" || data == "FAMC" || data == "FAMS" || data == "HUSB" || data == "WIFE" || data == "CHIL") {
		tag = data;
		if(data == "NAME" && indiv == true) {
			cout << data;
			result << data;
			getline(test, data);
			cout << data << '\n';
			result << data << endl;
			firstNames[it] = data;
		} else {
			restOfLine();
		}
	} else if(data == "BIRT" || data == "MARR" || data == "DIV") {
		tag = data;
		cout << data << '\n';
		result << data << endl;
	} else if(data == "DEAT") {
		tag = data;
		restOfLine();
	} else {
		restOfLine();
	}
	return 0;
}

/* Current line's level is 2
 * parses through the line looking for tag
 * prints line, level, and tag to output and output.txt
 */
int foundATwo() {
	test >> data;
	if(data == "DATE") {
		tag = data;
		restOfLine();
	} else {
		restOfLine();
	}
	return 0;
}

/* opens GEDCOM file and creates new output.txt
 * reads the level of each line and runs appropriate function
 * if unrecognized, prints error message and terminates program
 */
int main() {
	string num;
	int j;
	test.open("GEDCOM_test.ged", ios::in);
	result.open("output.txt", ios::out);
	test >> data;
	while(!test.eof()) {
		tag = "Invalid tag";
		cout << data << " ";
		result << data << " ";
		if(data[0] == '0') {
			foundAZero();
			num = "0";
		} else if(data[0] == '1') {
			foundAOne();
			num = "1";
		} else if(data[0] == '2') {
			foundATwo();
			num = "2";
		} else {
			cerr << "Error: unrecognizable level. Program Terminated" << '\n';
			result << "Error: unrecognizable level. Program Terminated" << '\n';
			return -1;
		}
		printLevel(num);
		test >> data;
	}

	cout << '\n' << "========================== INDIs ============================" << '\n';
	result << '\n' << "========================== INDIs ============================" << endl;
	for(j = 1; j < it; j++) {
		cout << "@I" << j << "@ ";
		cout << firstNames[j] << '\n';

		result << "@I" << j << "@ ";
		result << firstNames[j] << endl;
	}

	cout << '\n' << "========================== FAMs =============================" << '\n';
	result << '\n' << "========================== FAMs =============================" << '\n';

	test.close();
	result.close();
	return 0;
}


