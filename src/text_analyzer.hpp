#ifndef TEXT_ANALYZER_HPP
#define TEXT_ANALYZER_HPP

#include <sstream>
#include <fstream>
#include "prepositions_dictionary.hpp"

struct text_analyzer {

private:
    std::stringstream text_;
    prepositions_dictionary dictionary_;

    // bool is_begin(std::string const &word);
    // bool is_end(std::string const &word);
    //void remove_side_chars(std::string &word);

public:
    text_analyzer(std::ifstream &text_file);
    text_analyzer(text_analyzer const &) = delete;
    text_analyzer &operator=(text_analyzer const &) = delete;

    void analyze();
};


#endif
