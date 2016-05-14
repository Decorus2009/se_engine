#include "yandex_requester.hpp"
#include "prepositions_dictionary.hpp"
#include "text_analyzer.hpp"
#include "logger.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <locale>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: [mode] [-lang] [file]" << std::endl;
        return 1;
    }

    logger log(argv[1]);
    if (string(argv[1]) != "DEBUG" && string(argv[1]) == "RELEASE")
    {
        std::cerr << "Wrong mode" << std::endl;
        return 1;
    }

    std::ifstream text_file;
    text_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        text_file.open(argv[3], std::ios_base::binary);
        text_analyzer analyzer(text_file, argv[2]);
        analyzer.analyze(log);
        std::cout << std::endl;
        log.print_log();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "Error: could not open/read a text file" << std::endl;
        //std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (std::exception const& e)
    {
        std::cerr << "Something bad happened" << std::endl;
        return 1;
    }

    cout << "runtime = " << clock()/1000.0 << endl;






    if(!setlocale(LC_ALL, "ru_RU.UTF-8")) {
        perror("setlocale fail");
    }



//
    string line = "fluttered versus the open";
    yandex_requester ya;
    cout << ya.send_request(line) << endl;


    return 0;
}