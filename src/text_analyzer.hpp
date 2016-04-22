#ifndef TEXT_ANALYZER_HPP
#define TEXT_ANALYZER_HPP

#include <sstream>
#include <fstream>
#include <vector>
#include "prepositions_dictionary.hpp"
#include "logger.hpp"

struct text_analyzer {

public:
    text_analyzer(std::ifstream &text_file);
    text_analyzer(text_analyzer const &) = delete;
    text_analyzer &operator=(text_analyzer const &) = delete;

    void analyze(logger &log);

    std::string const &get_found_preposition(size_t ind);
private:
    std::stringstream text_;
    prepositions_dictionary dictionary_;


    // for test
    std::vector<std::string> found_prepositions_;
};





#endif
