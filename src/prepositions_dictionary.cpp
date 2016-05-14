#include <fstream>
#include <iostream>
#include <string>
#include "prepositions_dictionary.hpp"

prepositions_dictionary::prepositions_dictionary(std::string const& lang)
{
//    for (auto i : dictionary_)
//    {
//        std::cout << i.first << ' ' << i.second << std::endl;
//    }

    std::ifstream prepositions_list;
    prepositions_list.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        if (lang == "-en")
        {
            //prepositions_list.open("/home/decorus/Dropbox/CSC/Practice/I/se_engine/en_prepositions_stat.txt");
            prepositions_list.open("en_prepositions_stat.txt");
        }
        else if (lang == "-ru")
        {
            //prepositions_list.open("/home/decorus/Dropbox/CSC/Practice/I/se_engine/ru_prepositions_list.txt");
            prepositions_list.open("ru_prepositions_list.txt");
        }
    }


    // тут и так летит наверх, не надо throw;
    catch (std::ifstream::failure e)
    {
        //std::cerr << "Error: could not open dictionary file" << std::endl;
        throw;
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

bool prepositions_dictionary::find(std::string const& word) const
{
    return dictionary_.find(word) != dictionary_.end();
}
