#include "Prepositions_Dictionary.h"
#include <fstream>
#include <iostream>

Prepositions_Dictionary::Prepositions_Dictionary() {

	std::ifstream prep_file("prepositions_list.txt");
	
//как быть, если не удалось открыть файл? return 1 - нельзя же
	if (prep_file.fail()) {
		std::cout << "Error: could not open dictionary" << std::endl;
//		cerr << "Error: could not open dictionary" << endl;
	}
	else {
		
		std::string line;
	
		while (getline(prep_file, line)) {	

			if (dictionary_.count(line[0])) {

				dictionary_[line[0]].insert(line);
			}
			else {
				
				std::set <std::string, set_cmp> new_set;
				new_set.insert(line);
				dictionary_.insert(std::pair <char, std::set <std::string, set_cmp> > (line[0], new_set));
			}
		}
	}
}

void Prepositions_Dictionary::print() {

	for (auto it : dictionary_) {

		std::cout << '*' << it.first << '*' << std::endl;
		for (auto jt : it.second) {

			std::cout << jt << std::endl;
		}

		std::cout << "***************" << std::endl;
	}
}
