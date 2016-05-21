#include "yandex_requester.hpp"
#include "prepositions_dictionary.hpp"
#include "text_analyzer.hpp"
#include <algorithm>
#include <iomanip>

#include <math.h>

using namespace std;

int main(int argc, char **argv)
{
    // argv[4] - файл, в который записать результаты запросов Я
    if (argc != 6)
    {
        std::cerr << "Usage: [mode] [thr type] [file]" << std::endl;
        return 1;
    }

    logger log(argv[1]);
    if (string(argv[1]) != "-d" && string(argv[1]) != "-r" && string(argv[1]) != "-n")
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


        // запись статистики работы порогов
        ofstream thr_stat_file;
        thr_stat_file.open("thr_stat.txt", std::ios_base::app);
        thr_stat_file << endl << (string)argv[3] << endl;


        // записанный файл с результатами запросов, для автономности
        ifstream ya_req_res_file;
        ya_req_res_file.open(argv[4], std::ios_base::app);
        stringstream ya_req_res_stream;
        ya_req_res_stream << ya_req_res_file.rdbuf();

        ofstream aver_res_file;
        aver_res_file.open(argv[5], std::ios_base::app);

        analyzer.analyze(log, thr_stat_file, ya_req_res_stream, aver_res_file);
//        std::cout << std::endl;
        if (string(argv[1]) != "-n")
        {
            log.print_log();
        }
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

    //cout << "runtime = " << clock()/1000.0 << endl;

//    // на этом коде ide выводит в консоль только часть результатов, почему?
//    prepositions_dictionary dictionary;
//
//    vector<pair<string, long long>> v;
//    for (auto it = dictionary.dictionary_.begin(); it != dictionary.dictionary_.end(); ++it)
//    {
//        v.push_back(make_pair(it->first,it->second));
//    }
//    sort(v.begin(), v.end(), [](pair<string, long long> p1, pair<string, long long>p2) -> bool { return p1.second > p2.second; });
//
//    for (auto i : v)
//    {
//        cout << setw(20) << i.first << setw(15) << i.second << scientific << setw(20) << pow(10, -(log(i.second) / log(9))) << endl;
//    }
//
    return 0;
}