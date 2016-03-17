#include <iostream>
#include "Prepositions_Dictionary.h"

#include <fstream>
#include <sstream>
#include <string>
#include <map>
//#include <pair>

using namespace std;

/*
ifstream infile("prepositions_list.txt");
string line;	


void print(multimap<char, string> mm) {

	for (multimap<char, string>::iterator mmit = mm.begin(); mmit != mm.end(); ++ mmit) {
cout << (*mmit).first << ' ' << (*mmit).second << endl;
	}
	cout << endl;
}
*/

int main() {

	Prepositions_Dictionary PS;
	PS.print_all();


/*

	multimap <char, string> single_words_;
	multimap <char, string> two_words_;
	multimap <char, string> three_words_;
	multimap <char, string> preposition_noun_preposition_;
	multimap <char, string> archaic_dialectal_;
	multimap <char, string> postpositions_;


	getline(infile, line); 
	getline(infile, line); 
	
	while (line != "#Two_words") {

		single_words_.insert(pair<char, string>(line[0], line));
		getline(infile, line);
	}
	
	getline(infile, line); 
	while (line != "#Three_words") {

		two_words_.insert(pair<char, string>(line[0], line));
		getline(infile, line);
	}
	
	getline(infile, line); 
	while (line != "#Preposition_noun_preposition") {

		three_words_.insert(pair<char, string>(line[0], line));
		getline(infile, line);
	}
	
	getline(infile, line); 
	while (line != "#Archaic_dialectal") {

		preposition_noun_preposition_.insert(pair<char, string>(line[0], line));
		getline(infile, line);
	}
	
	getline(infile, line); 
	while (line != "#Postpositions") {

		archaic_dialectal_.insert(pair<char, string>(line[0], line));
		getline(infile, line);
	}
	
	while (getline(infile, line)) {
	
		postpositions_.insert(pair<char, string>(line[0], line));	
	}
	

	

	cout << endl << "single words" << endl;
	print(single_words_);
	cout << endl << "two words" << endl;
	print(two_words_);
	cout << endl << "three words" << endl;
	print(three_words_);
	cout << endl << "pnp words" << endl;
	print(preposition_noun_preposition_);
	cout << endl << "arch words" << endl;
	print(archaic_dialectal_);
	cout << endl << "postpos words" << endl;
	print(postpositions_);

*/
	return 0;
}
