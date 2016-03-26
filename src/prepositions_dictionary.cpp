#include "prepositions_dictionary.hpp"
#include <fstream>
#include <iostream>

using std::string;

prepositions_dictionary::prepositions_dictionary() {

	// возможно, правильнее будет взять файл с предподсчитанной статистикой, 
	// а не просто список предлогов с метаинформацией
	std::ifstream prep_file("prepositions_list.txt");

//как быть, если не удалось открыть файл? return 1 - нельзя же
	if (prep_file.fail()) {
		std::cout << "Error: could not open dictionary" << std::endl;
//		cerr << "Error: could not open dictionary" << endl;
	}
	else {

		string line;

		while (getline(prep_file, line)) {
			// метаинформация
			bool prep_type = (bool) (line[line.length() - 1] - '0');
			// вырезать символ - тип и пробел перед ним, оставить только само слово
			dictionary_[line.erase(line.length() - 2, 2)] = prep_type;
		}
	}
}

void prepositions_dictionary::print() {

	std::cout << "Dictionary:" << std::endl;
	for (auto it : dictionary_) {

		std::cout << it.first << ' ' << it.second << std::endl;
	}
}

std::map<std::string, bool> const &prepositions_dictionary::get_dictionary() {
	return dictionary_;
}
