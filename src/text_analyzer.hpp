#ifndef TEXT_ANALYZER_HPP
#define TEXT_ANALYZER_HPP

#include <sstream>
#include <fstream>
#include "prepositions_dictionary.hpp"
#include "logger.hpp"

struct text_analyzer {

private:
    std::stringstream text_;
    prepositions_dictionary dictionary_;

public:
    text_analyzer(std::ifstream &text_file);
    text_analyzer(text_analyzer const &) = delete;
    text_analyzer &operator=(text_analyzer const &) = delete;

    void analyze(logger &log);
};


#endif
