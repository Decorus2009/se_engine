#include "Prepositions_Dictionary.h"
#include <fstream>
#include <iostream>

using namespace std;
Prepositions_Dictionary::Prepositions_Dictionary() {

	ifstream prep_file("prepositions_list.txt");
	string line;	
	
//как быть, если не удалось открыть файл? return 1 - нельзя же
	if (prep_file.fail()) {
		cout << "Error: could not open dictionary" << endl;
//		cerr << "Error: could not open dictionary" << endl;
	}

	else {
		getline(prep_file, line); 

		getline(prep_file, line); 	
		while (line != "#TWO_WORDS") {

			single_words_.insert(pair<char, string>(line[0], line));
			getline(prep_file, line);
		}
	
		getline(prep_file, line); 
		while (line != "#THREE_WORDS") {

			two_words_.insert(pair<char, string>(line[0], line));
			getline(prep_file, line);
		}
	
		getline(prep_file, line); 
		while (line != "#PREPOSITION_NOUN_PREPOSITION") {

			three_words_.insert(pair<char, string>(line[0], line));
			getline(prep_file, line);
		}
	
		getline(prep_file, line); 
		while (line != "#ARCHAIC_DIALECTICAL") {

			preposition_noun_preposition_.insert(pair<char, string>(line[0], line));
			getline(prep_file, line);
		}
	
		getline(prep_file, line); 
		while (line != "#POSTPOSITIONS") {

			archaic_dialectal_.insert(pair<char, string>(line[0], line));
			getline(prep_file, line);
		}
	
		while (getline(prep_file, line)) {
	
			postpositions_.insert(pair<char, string>(line[0], line));	
		}

		prep_file.close();
	}
}

void Prepositions_Dictionary::print(multimap <char, string> mm) {

	for (multimap<char, string>::iterator mmit = mm.begin(); mmit != mm.end(); ++ mmit) {
cout << (*mmit).first << ' ' << (*mmit).second << endl;
	}
	cout << endl;

}


void Prepositions_Dictionary::print_all() {

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
}
