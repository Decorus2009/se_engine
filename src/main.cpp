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
    text_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        text_file.open(argv[2], std::ios_base::binary);
//        while (!text_file.eof()) text_file.get();
//        text_file.close();
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Error: could not open/read a text file" << std::endl;
        //std::cerr << e.what() << std::endl;

        return 1;
    }

    try {
        text_analyzer analyzer(text_file);
        analyzer.analyze(log);
        std::cout << std::endl;
        log.print_log();

    }
    catch (std::exception const& e) {

        std::cerr << "Something bad happened" << std::endl;
        return 1;
    }




	return 0;
}
