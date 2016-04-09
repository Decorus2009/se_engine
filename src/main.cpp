#include "yandex_requester.hpp"
#include "prepositions_dictionary.hpp"
#include "text_analyzer.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "logger.hpp"


int main(int argc, char **argv) {

	if (argc == 1) {
		std::cout << "No arguments" << std::endl;
		return 0;
	}

	std::ifstream text_file;
    try {
        text_file.open(argv[1], std::ios_base::binary);
        if (!text_file) {
            throw std::ios::failure("Error: could not open text file") ;
        }
    }
    catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
		return 1;
    }

	logger log;
	text_analyzer analyzer(text_file);
	analyzer.analyze(log);

	std::cout << std::endl << "LOG: " << std::endl << std::endl;
	log.print_log();

	return 0;
}
