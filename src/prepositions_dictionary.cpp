#include "prepositions_dictionary.hpp"
#include <fstream>
#include <iostream>

using std::string;

prepositions_dictionary::prepositions_dictionary() {

    std::ifstream prep_file("prepositions_list.txt");

//как быть, если не удалось открыть файл? return 1 - нельзя же





// тут надо бросить исключение





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

bool prepositions_dictionary::find(string const &word) {

    return dictionary_.find(word) != dictionary_.end();
}

void prepositions_dictionary::print() {

    std::cout << "Dictionary:" << std::endl;
    for (auto it : dictionary_) {

        std::cout << it.first << ' ' << it.second << std::endl;
    }
}
