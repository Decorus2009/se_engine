#include "yandex_requester.hpp"
#include "prepositions_dictionary.hpp"
#include "text_analyzer.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;


int main(int argc, char **argv) {

	if (argc == 1) {
		cout << "No arguments" << endl;
		return 0;
	}

	ifstream text_file(argv[1], ios_base::binary);
	if (text_file.fail()) {
        cerr << "Error: could not open " << '"' << text_file << '"' << " file" << endl;
        return 1;
    }

	text_analyzer analyzer(text_file);
	analyzer.analyze();

	//
	// ifstream f("test_text_HPOP");
	// string s;
	// string text;
	// while (getline(f, s)) {
	// 	text += s;
	// }
	// cout << text << endl;
	//
	// istringstream iss(text);
    // string word;
    // while(iss >> word) {
	// 	//cout << word << endl;
    // }


// 	ifstream ifile("prepositions_stat_found_sort.txt", ios_base::binary);
// 	stringstream iss;
// 	iss << ifile.rdbuf();
// 	//cout << iss.str();
//
// 	string word;
//     while(iss >> word) {
// //		cout << word << ' ';
//     }
//
// 	string st = "test_text_HPOP";
// 	text_analyzer ta(st);
//
//
	return 0;
}
