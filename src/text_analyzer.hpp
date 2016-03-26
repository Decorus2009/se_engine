#ifndef TEXT_ANALYZER_HPP
#define TEXT_ANALYZER_HPP

#include "prepositions_dictionary.hpp"
#include <sstream>
#include <fstream>

struct text_analyzer {

private:
    std::stringstream text_;
    prepositions_dictionary dictionary_;

    std::pair<bool, bool> check_word_bounds(std::string &word);

public:
    text_analyzer(std::ifstream &text_file);
    text_analyzer(text_analyzer const &) = delete;
    text_analyzer &operator=(text_analyzer const &) = delete;

    void analyze();
};


#endif
