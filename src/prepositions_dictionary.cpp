#include "prepositions_dictionary.hpp"
#include <fstream>
#include <iostream>

using std::string;

prepositions_dictionary::prepositions_dictionary() {

    std::ifstream prep_file;
    try {
        prep_file.open("prepositions_list.txt");
        if (!prep_file) {
            throw std::ios::failure("Error: could not open dictionary file") ;
        }
    }
    catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }

    string line;

    while (getline(prep_file, line)) {
        // метаинформация
        bool prep_type = (bool) (line[line.length() - 1] - '0');

        // вырезать символ - тип и пробел перед ним, оставить только само слово
        line.erase(line.length() - 2, 2);

        // метод insert проверяет, есть ли уже в файле такой ключ
        dictionary_.insert(make_pair(line, prep_type));
    }
}

bool prepositions_dictionary::find(string const &word) {

    return dictionary_.find(word) != dictionary_.end();
}

// never used
/*
void prepositions_dictionary::print() {

    std::cout << "Dictionary:" << std::endl;
    for (auto it : dictionary_) {

        std::cout << it.first << ' ' << it.second << std::endl;
    }
}
*/
