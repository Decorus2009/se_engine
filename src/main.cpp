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
    if (string(argv[1]) == "DEBUG")
	{

    }
    else if (string(argv[1]) == "RELEASE")
	{

    }
    else
	{
        std::cerr << "Wrong mode" << std::endl;
        return 1;
    }

	// yandex_requester ya;
	// ya.send_request("fluttered ecnetsixenon the open");




    std::ifstream text_file;
    text_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
	{
        text_file.open(argv[3], std::ios_base::binary);
//        while (!text_file.eof()) text_file.get();
//        text_file.close();
    }
    catch (std::ifstream::failure e)
	{
        std::cerr << "Error: could not open/read a text file" << std::endl;
        //std::cerr << e.what() << std::endl;

        return 1;
    }


    try
	{
		// wstring ws = L"Hekko";
		// wcout << ws << endl;


		// const wchar_t c = 'Я';
		//
		// cout << c << endl << endl;
		//
		// std::locale loc2("ru_UA.UTF-8");
		// cout << isalpha(c, loc2) << endl;
		// cout << isalpha((wchar_t)'d', loc2) << endl;


		// const wchar_t c = L'\u042f';
		// std::locale loc2("en_US.UTF8");
    	// std::cout << "isalpha('Я', Unicode locale) returned " << std::boolalpha << std::isalpha(c, loc2) << '\n';


        text_analyzer analyzer(text_file, argv[2]);
        analyzer.analyze(log);
        std::cout << std::endl;
        log.print_log();

		// for (size_t i = 0; i < analyzer.get_found_prepositions_size(); ++i)	{ cout << analyzer.get_found_preposition(i) << endl;}
		// cout << endl;
		// for (size_t i = 0; i < analyzer.get_found_requests_size(); ++i) { cout << analyzer.get_found_request(i) << endl;}

    }
    catch (std::exception const& e)
	{

        std::cerr << "Something bad happened" << std::endl;
        return 1;
    }

	cout << "runtime = " << clock()/1000.0 << endl;
	return 0;
}
