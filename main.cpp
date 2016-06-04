/* CS 555 WS
 * Project 03 - GEDCOM parser : Save INDIs and FAMs
 * Clara Ramos, Larisa Machado, Varun Kumar
 * We pledge our honor that we have abided by the Stevens Honor System.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
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
 * family = flag that dictates which line of the info being read is from a FAM
 * it = iterator for INDIs
 * fit = iterator for FAMs
 */
string data, tag = "Invalid tag";
fstream test, result;
string INDIs[5000][2];
int FAMs[1000][5000];
bool indiv = false;
int family = -1, it = 0, fit = 0;

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
			} else if(data == "FAM") {
				family = 0;
				fit++;
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
			restOfLine();

			/* divides the INDIs name to first and last
			 * removes the '/' surrounding the last name
			 */
			char* fullName = &data[0];
			char* splitName = strtok(fullName, " /");
			INDIs[it][0] = splitName;
			splitName = strtok(NULL, " /");
			INDIs[it][1] = splitName;
		} else if((data == "HUSB" || data == "WIFE" || data == "CHIL") && family > -1) {
			restOfLine();

			char* ID = &data[0];
			char* person = strtok(ID, " @I");
			FAMs[fit][family] = atoi(person);
			family++;
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
	for(j = 1; j <= it; j++) {
		cout << "@I" << j << "@: ";
		cout << INDIs[j][0] << " " << INDIs[j][1] << '\n';

		result << "@I" << j << "@: ";
		result << INDIs[j][0] << " " << INDIs[j][1] << endl;
	}

	cout << '\n' << "========================== FAMs =============================" << '\n';
	result << '\n' << "========================== FAMs =============================" << endl;
	for(j = 1; j <= fit; j++) {
		cout << "@F" << j << "@:" << '\n';
		cout << "  Husband: @I" << FAMs[j][0] << "@" << '\n';
		cout << "    " << INDIs[FAMs[j][0]][0] << " " << INDIs[FAMs[j][0]][1] << '\n';
		cout << "  Wife: @I" << FAMs[j][1] << "@" << '\n';
		cout << "    " << INDIs[FAMs[j][1]][0] << " " << INDIs[FAMs[j][1]][1] << '\n';

		result << "@F" << j << "@:" << '\n';
		result << "  Husband: @I" << FAMs[j][0] << "@" << endl;
		result << "    " << INDIs[FAMs[j][0]][0] << " " << INDIs[FAMs[j][0]][1] << endl;
		result << "  Wife: @I" << FAMs[j][1] << "@" << endl;
		result << "    " << INDIs[FAMs[j][1]][0] << " " << INDIs[FAMs[j][1]][1] << endl;
	}

	test.close();
	result.close();
	return 0;
}


