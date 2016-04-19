#include "yandex_requester.hpp"
#include "prepositions_dictionary.hpp"
#include "text_analyzer.hpp"
#include "logger.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

int main(int argc, char **argv) {

	if (argc != 3) {
        std::cerr << "Usage: [mode] [file]" << std::endl;
        return 1;
    }

    logger log(argv[1]);
    if (string(argv[1]) == "DEBUG") {


    }
    else if (string(argv[1]) == "RELEASE") {

    }
    else {
        std::cerr << "Wrong mode" << std::endl;
        return 1;
    }
	std::ifstream text_file;
    try {
        text_file.open(argv[2], std::ios_base::binary);
        if (!text_file) {
            throw std::ios::failure("Error: could not open text file") ;
        }
    }
    catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
		return 1;
    }






	// exception бросать везде, где используется файл и не только
	// см. пример на сplusplus ifstream.exceptions()







	text_analyzer analyzer(text_file);
	analyzer.analyze(log);

	std::cout << "LOG: " << std::endl << std::endl;
	log.print_log();

	return 0;
}
