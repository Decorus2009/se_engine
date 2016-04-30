#include <fstream>
#include <iostream>
#include <string>
#include "prepositions_dictionary.hpp"

prepositions_dictionary::prepositions_dictionary(std::string const& lang)
{
    std::ifstream prepositions_list;
    prepositions_list.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        if (lang == "-en")
        {
            prepositions_list.open("en_prepositions_list.txt");
        }
        else if (lang == "-ru")
        {
            prepositions_list.open("ru_prepositions_list.txt");
        }
    }
    catch (std::ifstream::failure e)
    {
        //std::cerr << "Error: could not open dictionary file" << std::endl;
        throw;
    }


    // почему не работает??
//    prepositions_list.clear();


    // приходится использовать
    prepositions_list.exceptions(std::ifstream::goodbit);
    std::string line;
    while (getline(prepositions_list, line))
    {
        dictionary_.insert(line);
    }
}

bool prepositions_dictionary::find(std::string const& word) const
{
    return dictionary_.find(word) != dictionary_.end();
}
