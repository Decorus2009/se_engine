#ifndef PREPOSITIONS_DICTIONARY_HPP
#define PREPOSITIONS_DICTIONARY_HPP

#include <set>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

struct prepositions_dictionary
{

public:
    prepositions_dictionary();


    inline bool find(std::string const& word) const
    {
        return dictionary_.find(word) != dictionary_.end();
    }
    inline uint64_t operator[](std::string const& preposition)
    {
        return dictionary_[preposition];
    }
    inline uint64_t at(std::string const& preposition)
    {
        return dictionary_.at(preposition);
    }
    inline void print()
    {
        std::cout << "Prepositions List: " << std::endl;
        for (auto it : dictionary_)
    	{
    		std::cout << it.first << '\t' << it.second << std::endl;
    	}
    }


    prepositions_dictionary(prepositions_dictionary const&) = delete;
    prepositions_dictionary& operator=(prepositions_dictionary const&) = delete;

//private:
    std::map<std::string, uint64_t> dictionary_;
    //std::set<std::string> dictionary_;
};

#endif
