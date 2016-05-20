#include <fstream>
#include <iostream>
#include "prepositions_dictionary.hpp"

prepositions_dictionary::prepositions_dictionary()
{
    std::ifstream prepositions_list;
    prepositions_list.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        prepositions_list.open("en_prepositions_stat.txt");
    }
    // тут и так летит наверх, не надо throw;
    catch (std::ifstream::failure e)
    {
        std::cerr << "Error: could not open dictionary file" << std::endl;
    }

    // почему не работает??
    //    prepositions_list.clear();
    // приходится использовать
    prepositions_list.exceptions(std::ifstream::goodbit);
    std::string preposition;
    while (getline(prepositions_list, preposition))
    {
        std::string frequency;
        getline(prepositions_list, frequency);
        dictionary_.insert(make_pair(preposition, std::stoull(frequency)));
    }
}
