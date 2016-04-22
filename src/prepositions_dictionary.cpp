#include <fstream>
#include <iostream>
#include <string>
#include "prepositions_dictionary.hpp"

prepositions_dictionary::prepositions_dictionary() {

    std::ifstream prepositions_list;
    prepositions_list.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        prepositions_list.open("prepositions_list.txt");
    }
    catch (std::ifstream::failure e) {
        //std::cerr << "Error: could not open dictionary file" << std::endl;
        throw;
    }


    // почему не работает??
//    prepositions_list.clear();


    // приходится использовать
    prepositions_list.exceptions(std::ifstream::goodbit);
    std::string line;
    while (getline(prepositions_list, line)) {

        bool prep_type = (bool) (line[line.length() - 1] - '0');

        // вырезать символ - тип и пробел перед ним, оставить только само слово
        line.erase(line.length() - 2, 2);

        // метод insert проверяет, есть ли уже в файле такой ключ
        dictionary_.insert(make_pair(line, prep_type));
    }
}

bool prepositions_dictionary::find(std::string const &word) {
    return dictionary_.find(word) != dictionary_.end();
}
