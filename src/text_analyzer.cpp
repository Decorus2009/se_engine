//#include "text_analyzer.hpp"
//#include <fstream>
//#include <iostream>
//#include <iomanip>
//#include <vector>
//#include <algorithm>
//#include <ctype.h>
//#include <locale>
//
//using std::map;
//using std::pair;
//using std::vector;
//using std::string;
//using std::stringstream;
//
//text_analyzer::text_analyzer(std::ifstream& text_file, string const& lang) try : dictionary_(lang)
//{
//    text_ << text_file.rdbuf();
//}
//catch (std::exception const& e)
//{
//    std::cerr << "Error in opening/reading dictionary" << std::endl;
//    throw;
//}
//
//bool text_analyzer::is_end(string const& word)
//{
//    // исключение - предлог o'. not yet implemented
//    return !isalpha(word[word.length() - 1]);
//}
//bool text_analyzer::is_article(string const& word)
//{
//    return (word == "the" || word == "an" || word == "a");
//}
//
//void text_analyzer::remove_side_chars(string& word) {
//
//
//    while (word.length() && !isalpha(word[0])) {
//        word.erase(0, 1);
//    }
//    while (word.length() && !isalpha(word[word.length() - 1])) {
//        word.erase(word.length() - 1, 1);
//    }
//}
//
//map<int, std::tuple<string, string, string, string, string>> text_analyzer::
//build_requests(vector<pair<string, size_t>> const& sentence, size_t begin_ind, size_t len) {
//
//    map<int, std::tuple<string, string, string, string, string>> requests;
//
//    string left_first_word, right_first_word,
//            left_two_words, right_two_words,
//            left_one_word_request, right_one_word_request,
//            left_two_words_request, right_two_words_request;
//    string second_word_left;
//    string second_word_right;
//
//    // формирование предлога (он может быть длиннее одного слова)
//    string preposition = sentence[begin_ind].first;
//    for (size_t i = begin_ind + 1; i < begin_ind + len; ++i)
//    {
//        preposition = preposition + " " + sentence[i].first;
//    }
//
//    if (sentence.size() > 1)
//    {
//        if (begin_ind + len <= sentence.size() && begin_ind > 0)
//        {
//            left_first_word += sentence[begin_ind - 1].first;
//
//            int cur_left_bound = begin_ind - 1;
//
//            if (begin_ind - 1 > 0 && is_article(sentence[cur_left_bound].first))
//            {
//                left_first_word = sentence[cur_left_bound - 1].first
//                                       + " "
//                                       + left_first_word;
//
//                --cur_left_bound;
//            }
//
//            left_one_word_request = left_first_word + " " + preposition;
//
//            // FOR TEST & LOG
////            all_requests_.push_back(left_one_word_request);
//
//            requests.insert(make_pair(-1, std::make_tuple("",
//                                                          "&quot;" + left_first_word + "&quot;",
//                                                          "&quot;" + left_one_word_request + "&quot;",
//                                                          "",
//                                                          "")));
//
//            --cur_left_bound;
//
//            if (cur_left_bound >= 0)
//            {
//                left_two_words = sentence[cur_left_bound].first
//                                        + " "
//                                        + left_first_word;
//
//                second_word_left = sentence[cur_left_bound].first;
//                if (cur_left_bound - 1 >= 0 && is_article(sentence[cur_left_bound].first))
//                {
//                    left_two_words = sentence[cur_left_bound - 1].first
//                                            + " "
//                                            + left_two_words;
//
//                    second_word_left = sentence[cur_left_bound - 1].first;
//                }
//
//                left_two_words_request = left_two_words + " " + preposition;
//                // FOR TEST & LOG
////                all_requests_.push_back(left_two_words_request);
//
//                requests.insert(make_pair(-2, std::make_tuple("&quot;" + second_word_left + "&quot;",
//                                                              "&quot;" + left_first_word + "&quot;",
//                                                              "&quot;" + left_two_words_request + "&quot;",
//                                                              "",
//                                                              "")));
//            }
//        }
//
//
//        if (begin_ind >= 0 && begin_ind + len < sentence.size())
//        {
//            right_first_word = sentence[begin_ind + len].first;
//
//            int cur_right_bound = begin_ind + len;
//            if (begin_ind + len < sentence.size() - 1 && is_article(sentence[begin_ind + len].first))
//            {
//                right_first_word += " " + sentence[cur_right_bound + 1].first;
//
//                ++cur_right_bound;
//            }
//
//            right_one_word_request = preposition + " " + right_first_word;
//            // FOR TEST & LOG
////            all_requests_.push_back(right_one_word_request);
//
//            requests.insert(make_pair(1, std::make_tuple("",
//                                                         "",
//                                                         "&quot;" + right_one_word_request + "&quot;",
//                                                         "&quot;" + right_first_word + "&quot;",
//                                                         "")));
//
//
//            ++cur_right_bound;
//
//            if (cur_right_bound <= sentence.size() - 1)
//            {
//                right_two_words = right_first_word
//                                         + " "
//                                         + sentence[cur_right_bound].first;
//
//                second_word_right = sentence[cur_right_bound].first;
//
//                if (cur_right_bound + 1 <= sentence.size() - 1 && is_article(sentence[cur_right_bound].first))
//                {
//                    right_two_words += " " + sentence[cur_right_bound + 1].first;
//                    second_word_right = sentence[cur_right_bound + 1].first;
//                }
//
//
//                right_two_words_request = preposition + " " + right_two_words;
//                // FOR TEST & LOG
////                all_requests_.push_back(right_two_words_request);
//
//                requests.insert(make_pair(2, std::make_tuple("",
//                                                             "",
//                                                             "&quot;" + right_two_words_request + "&quot;",
//                                                             "&quot;" + right_first_word + "&quot;",
//                                                             "&quot;" + second_word_right + "&quot;")));
//            }
//        }
//
//
//        if (!left_first_word.empty() && !right_first_word.empty())
//        {
//            string left_right_one_word_request = left_first_word
//                                                 + " "
//                                                 + preposition
//                                                 + " "
//                                                 + right_first_word;
//
//            // FOR TEST & LOG
////            all_requests_.push_back(left_right_one_word_request);
//
//            requests.insert(make_pair(3, std::make_tuple("",
//                                                         "&quot;" + left_first_word + "&quot;",
//                                                         "&quot;" + left_right_one_word_request + "&quot;",
//                                                         "&quot;" + right_first_word + "&quot;",
//                                                         "")));
//        }
//
//
//        if (!left_two_words.empty() && !right_two_words.empty())
//        {
//            string left_right_two_words_request = left_two_words
//                                                  + " "
//                                                  + preposition
//                                                  + " "
//                                                  + right_two_words;
//
//            // FOR TEST & LOG
////            all_requests_.push_back(left_right_two_words_request);
//
//            requests.insert(make_pair(5, std::make_tuple("&quot;" + second_word_left + "&quot;",
//                                                         "&quot;" + left_first_word + "&quot;",
//                                                         "&quot;" + left_right_two_words_request + "&quot;",
//                                                         "&quot;" + right_first_word + "&quot;",
//                                                         "&quot;" + second_word_right + "&quot;")));
//        }
//    }
//
////    map<int, string> requests;
////
////    string left_first_word, right_first_word,
////            left_two_words, right_two_words,
////            left_one_word_request, right_one_word_request,
////            left_two_words_request, right_two_words_request;
////
////    // формирование предлога (он может быть длиннее одного слова)
////    string preposition = sentence[begin_ind].first;
////    for (size_t i = begin_ind + 1; i < begin_ind + len; ++i)
////    {
////        preposition = preposition + " " + sentence[i].first;
////    }
////
////    if (sentence.size() > 1)
////    {
////        if (begin_ind + len <= sentence.size() && begin_ind > 0)
////        {
////            left_first_word += sentence[begin_ind - 1].first;
////
////            int cur_left_bound = begin_ind - 1;
////
////            if (begin_ind - 1 > 0 && is_article(sentence[cur_left_bound].first))
////            {
////                left_first_word = sentence[cur_left_bound - 1].first
////                                       + " "
////                                       + left_first_word;
////
////                --cur_left_bound;
////            }
////
////            left_one_word_request = left_first_word + " " + preposition;
////
////            // FOR TEST & LOG
////            all_requests_.push_back(left_one_word_request);
////
////            left_one_word_request = "&quot;" + left_one_word_request + "&quot;";
////
////            requests.insert(make_pair(-1, left_one_word_request));
////
////            --cur_left_bound;
////
////            if (cur_left_bound >= 0)
////            {
////                left_two_words = sentence[cur_left_bound].first
////                                        + " "
////                                        + left_first_word;
////
////                if (cur_left_bound - 1 >= 0 && is_article(sentence[cur_left_bound].first))
////                {
////                    left_two_words = sentence[cur_left_bound - 1].first
////                                            + " "
////                                            + left_two_words;
////                }
////
////                left_two_words_request = left_two_words + " " + preposition;
////                // FOR TEST & LOG
////                all_requests_.push_back(left_two_words_request);
////
////                left_two_words_request = "&quot;" + left_two_words_request + "&quot;";
////
////                requests.insert(make_pair(-2, left_two_words_request));
////            }
////        }
////
////        if (begin_ind >= 0 && begin_ind + len < sentence.size())
////        {
////            right_first_word = sentence[begin_ind + len].first;
////
////            int cur_right_bound = begin_ind + len;
////            if (begin_ind + len < sentence.size() - 1 && is_article(sentence[begin_ind + len].first))
////            {
////                right_first_word += " " + sentence[cur_right_bound + 1].first;
////
////                ++cur_right_bound;
////            }
////
////            right_one_word_request = preposition + " " + right_first_word;
////            // FOR TEST & LOG
////            all_requests_.push_back(right_one_word_request);
////
////            right_one_word_request = "&quot;" + right_one_word_request + "&quot;";
////
////            requests.insert(make_pair(1, right_one_word_request));
////
////            ++cur_right_bound;
////
////            if (cur_right_bound <= sentence.size() - 1)
////            {
////                right_two_words = right_first_word
////                                         + " "
////                                         + sentence[cur_right_bound].first;
////
////                if (cur_right_bound + 1 <= sentence.size() - 1 && is_article(sentence[cur_right_bound].first))
////                {
////                    right_two_words += " " + sentence[cur_right_bound + 1].first;
////                }
////
////
////                right_two_words_request = preposition + " " + right_two_words;
////                // FOR TEST & LOG
////                all_requests_.push_back(right_two_words_request);
////
////                right_two_words_request = "&quot;" + right_two_words_request + "&quot;";
////
////                requests.insert(make_pair(2, right_two_words_request));
////            }
////        }
////
////        if (!left_first_word.empty() && !right_first_word.empty())
////        {
////            string left_right_one_word_request = left_first_word
////                                                 + " "
////                                                 + preposition
////                                                 + " "
////                                                 + right_first_word;
////
////            // FOR TEST & LOG
////            all_requests_.push_back(left_right_one_word_request);
////
////            left_right_one_word_request = "&quot;" + left_right_one_word_request + "&quot;";
////            requests.insert(make_pair(3, left_right_one_word_request));
////        }
////
////        if (!left_two_words.empty() && !right_two_words.empty())
////        {
////            string left_right_two_words_request = left_two_words
////                                                  + " "
////                                                  + preposition
////                                                  + " "
////                                                  + right_two_words;
////
////            // FOR TEST & LOG
////            all_requests_.push_back(left_right_two_words_request);
////
////            left_right_two_words_request = "&quot;" + left_right_two_words_request + "&quot;";
////            requests.insert(make_pair(5, left_right_two_words_request));
////        }
////    }
//
//    return requests;
//}
//
//void text_analyzer::send_and_log_requests(vector<pair<string, size_t> > const& sentence,
//                           size_t begin_ind, size_t len,
//                           yandex_requester &requester,
//                           size_t line_counter, size_t word_counter,
//                           prepositions_dictionary& dictionary, string const& preposition)
//{
//    auto requests = build_requests(sentence, begin_ind, len);
//
//
//    //посылка запросов:
//    // строится ровно один запрос: типа 3, если нет, то -2 или 2, если нет, то -1 или 1
//
//    //string req;
//    vector<string> local_reqs;
//    int req_type = 0;
//    map<int, size_t> thresholds;
//    thresholds.insert(std::make_pair(3, 100));
//    thresholds.insert(std::make_pair(-2, 100));
//    thresholds.insert(std::make_pair(2, 100));
//    thresholds.insert(std::make_pair(-1, 1000));
//    thresholds.insert(std::make_pair(1, 1000));
//
//    string full_request;
//    if(requests.find(3) != requests.end())
//    {
//        local_reqs.push_back(std::get<1>(requests[3]));
//        local_reqs.push_back(std::get<3>(requests[3]));
//
//        full_request = std::get<2>(requests[3]);
////        req = requests[3];
//        req_type = 3;
//    }
//    else if (requests.find(-2) != requests.end())
//    {
//        local_reqs.push_back(std::get<0>(requests[-2]));
//        local_reqs.push_back(std::get<1>(requests[-2]));
//
//        full_request = std::get<2>(requests[-2]);
////        req = requests[-2];
//        req_type = -2;
//    }
//    else if (requests.find(2) != requests.end())
//    {
//        local_reqs.push_back(std::get<3>(requests[2]));
//        local_reqs.push_back(std::get<4>(requests[2]));
//
//        full_request = std::get<2>(requests[2]);
////        req = requests[2];
//        req_type = 2;
//    }
//    else if (requests.find(-1) != requests.end())
//    {
//        local_reqs.push_back(std::get<1>(requests[-1]));
//
//        full_request = std::get<2>(requests[-1]);
////        req = requests[-1];
//        req_type = -1;
//    }
//    else if (requests.find(1) != requests.end())
//    {
//        local_reqs.push_back(std::get<3>(requests[1]));
//
//        full_request = std::get<2>(requests[1]);
////        req = requests[1];
//        req_type = 1;
//    }
//
//    long long full_req_res = requester.send_request(full_request);
//    all_sent_requests_info_.push_back({true, full_request, full_req_res, line_counter, word_counter, preposition, dictionary[preposition]});
//
//    vector<long long> local_reqs_res;
//    for (int i = 0; i < local_reqs.size(); ++i)
//    {
//        string req = local_reqs[i];
//        long long req_res = requester.send_request(req);
//        local_reqs_res.push_back(req_res);
//        all_sent_requests_info_.push_back({false, req, req_res, line_counter, word_counter,
//                                           preposition, dictionary[preposition]});
//    }
//    local_reqs_res.push_back(dictionary[preposition]);
//
//    long long min_res_val = *(std::min_element(local_reqs_res.begin(), local_reqs_res.end()));
//
//    all_sent_requests_info_.push_back({false, "#MIN: ", min_res_val, line_counter, word_counter,
//                                       preposition, dictionary[preposition], (double)full_req_res/min_res_val});
//    // для отступа строки в последующем принте
//    all_sent_requests_info_.push_back({false, "###", 0, 0, 0, "", 0});
//
//
//
////        if (req_res <= thresholds[req_type])
////        {
////            possible_mistakes_.push_back({req, line_counter, word_counter});
////        }
//
//    // if (req_res <= (long long)(0.00000001 * dictionary[preposition]))
//    // {
//    //     possible_mistakes_.push_back({req, line_counter, word_counter});
//    // }
//
//}
//
//
//void text_analyzer::analyze(logger &log)
//{
//    yandex_requester requester;
//
//    string log_mode = log.get_severity();
//
//    string line;
//    size_t line_counter = 0;
//    while (getline(text_, line))
//    {
//        ++line_counter;
//
//        stringstream line_stream(line);
//
//        string word;
//        size_t word_counter = 0;
//        vector<pair<string, size_t> > sentence;
//        while (line_stream >> word)
//        {
//            ++word_counter;
//
//            sentence.push_back(make_pair(word, word_counter));
//            if (is_end(word))
//            {
//                remove_side_chars(sentence[0].first);
//                remove_side_chars(sentence[sentence.size() - 1].first);
//
//                for (size_t i = 0; i < sentence.size(); ++i)
//                {
//                    if (sentence[i].first.empty())
//                    {
//                        sentence.erase(sentence.begin() + i);
//
//                        --i;
//                        --word_counter;
//                    }
//                }
//
//                if (sentence.empty()){ continue; }
//
//                for (size_t i = 0; i < sentence.size(); ++i)
//                {
//                    string possible_preposition;
//                    size_t word_num = 0;
//                    size_t j = i;
//                    vector<pair<string, size_t> > possible_prepositions;
//                    while (j <= sentence.size() - 1  && word_num < 4)
//                    {
//                        possible_preposition = (!word_num) ? sentence[j].first
//                                                           : possible_preposition
//                                                             + " "
//                                                             + sentence[j].first;
//                        ++word_num;
//                        ++j;
//
//                        transform(possible_preposition.begin(), possible_preposition.end(),
//                                  possible_preposition.begin(), ::tolower);
//
//                        possible_prepositions.push_back(make_pair(possible_preposition, word_num));
//                    }
//
//                    for (auto it = possible_prepositions.rbegin(); it != possible_prepositions.rend(); ++it)
//                    {
//                        if (dictionary_.find(it->first))
//                        {
//                            all_prepositions_.push_back({it->first, line_counter, sentence[i].second});
//
//                            size_t len = it->second;
//
//                            send_and_log_requests(sentence, i, len, requester, line_counter,
//                                                  sentence[i].second, dictionary_, it->first);
//
//                            i += len - 1;
//                            possible_prepositions.clear();
//                            break;
//                        }
//                    }
//                }
//                sentence.clear();
//                //continue;
//            }
//        }
//    }
//
//    double sum = 0;
//    double full_to_min_ratio_aver = 0;
//    int min_count = 0;
//
//    if (log_mode == "DEBUG")
//    {
//        log << text_.str() << (string)"\n";
//
//        log << "Prepositions: " << (string)"\n";
//        for (int i = 0; i < all_prepositions_.size(); ++i)
//        {
//            log << "Found" << std::setw(15) << all_prepositions_[i].preposition_
//            << "   " << " at line: " << std::setw(5) << all_prepositions_[i].line_counter_
//            << "    word: " << std::setw(5) << all_prepositions_[i].word_counter_ << (string)"\n";
//        }
//        log << (string)"\n";
//
//
//        // если есть в слове кавычки, то setw как работает
//
//
//        for (int i = 0; i < all_sent_requests_info_.size(); ++i)
//        {
//            if (all_sent_requests_info_[i].request_ == "###")
//            {
//                log << (string)"\n";
//                continue;
//            }
//
//            log << std::setw(35) << all_sent_requests_info_[i].request_
//                << ": " << std::setw(12) << all_sent_requests_info_[i].result_
//                << "\tat line: " << std::setw(3) << all_sent_requests_info_[i].line_counter_
//                << "    word: " << std::setw(2) << all_sent_requests_info_[i].word_counter_;
//
//            if (all_sent_requests_info_[i].is_full_req)
//            {
//                log << "    preposition: " << std::setw(15) << all_sent_requests_info_[i].preposition_
//                    << "    reference: " << std::setw(11) << all_sent_requests_info_[i].reference_result_
//                    << "  ratio:       " << std::setw(5) << std::setprecision(9)
//                    << std::setw(15) << (double)all_sent_requests_info_[i].result_ / all_sent_requests_info_[i].reference_result_;
//
//                sum += (double)all_sent_requests_info_[i].result_ / all_sent_requests_info_[i].reference_result_;
//
////                if ((double)all_sent_requests_info_[i].result_ / all_sent_requests_info_[i].reference_result_ > 0.00001)
////                {
////                    log << "   *****";
////                }
//            }
//            else if (all_sent_requests_info_[i].request_ == "#MIN: ")
//            {
//                log << "                                               #full to min ratio: "
//                    << std::setprecision(9) << std::setw(21) << all_sent_requests_info_[i].full_to_min_ratio_;
//
//                full_to_min_ratio_aver += all_sent_requests_info_[i].full_to_min_ratio_;
//                ++min_count;
//            }
//            log << (string)"\n";
//
//        }
//    }
//    log << (string)"\n";
//
//    for (int i = 0; i < possible_mistakes_.size(); ++i)
//    {
//        log << "Possible mistake: " << "line: " << std::setw(3)
//        << possible_mistakes_[i].line_counter_ << ", word: " << std::setw(3)
//        << possible_mistakes_[i].word_counter_ << ": " << possible_mistakes_[i].request_ << (string)"\n";
//    }
//
////    std::cout << "average ratio: " << sum / all_sent_requests_info_.size() << std::endl << std::endl;
//    std::cout << "average full_to_min_ratio: " << full_to_min_ratio_aver / min_count << std::endl << std::endl;
//    // почему шаблонный оператор << не работает (undefined reference),
//    // если определить его в logger.cpp, а не в logger.hpp??????????????????????????????????????????????????????????????
//}
//
//
//
//
//
//
//
//
//
//
//
//


#include "text_analyzer.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <locale>
#include <tuple>
#include <regex.h>

using std::map;
using std::pair;
using std::vector;
using std::string;
using std::stringstream;
using std::tuple;


static yandex_requester requester;

text_analyzer::text_analyzer(std::ifstream& text_file, string const& lang) try : dictionary_(lang)
{
    text_ << text_file.rdbuf();
}
catch (std::exception const& e)
{
    std::cerr << "Error in opening/reading dictionary" << std::endl;
    throw;
}

bool text_analyzer::is_end(string const& word)
{
    // исключение - предлог o'. not yet implemented
    return !isalpha(word[word.length() - 1]);
}
bool text_analyzer::is_article(string const& word)
{
    return (word == "the" || word == "an" || word == "a");
}

void text_analyzer::remove_side_chars(string& word) {


    while (word.length() && !isalpha(word[0])) {
        word.erase(0, 1);
    }
    while (word.length() && !isalpha(word[word.length() - 1])) {
        word.erase(word.length() - 1, 1);
    }
}

map<int, vector<string>> text_analyzer::
build_requests(vector<pair<string, size_t>> const& sentence, size_t begin_ind, size_t len) {

    map<int, vector<string>> requests;

    string left_first_word,
            right_first_word,
            left_two_words,
            right_two_words,
            left_one_word_request,
            right_one_word_request,
            left_two_words_request,
            right_two_words_request,
            left_second_word,
            right_second_word;


    // формирование предлога (он может быть длиннее одного слова)
    string preposition = sentence[begin_ind].first;
    for (size_t i = begin_ind + 1; i < begin_ind + len; ++i)
    {
        preposition = preposition + " " + sentence[i].first;
    }

    vector<string> reqs_v;

    if (sentence.size() > 1)
    {

        if (begin_ind + len <= sentence.size() && begin_ind > 0)
        {
            left_first_word += sentence[begin_ind - 1].first;

            int cur_left_bound = begin_ind - 1;

            if (begin_ind - 1 > 0 && is_article(sentence[cur_left_bound].first))
            {
                left_first_word = sentence[cur_left_bound - 1].first
                                       + " "
                                       + left_first_word;

                --cur_left_bound;
            }

            left_one_word_request = left_first_word + " " + preposition;

            // FOR TEST & LOG
            all_requests_.push_back(left_one_word_request);

            // left_one_word_request = "&quot;" + left_one_word_request + "&quot;";

            reqs_v = {"", left_first_word, left_one_word_request, "", ""};
            requests.insert(make_pair(-1, reqs_v));

            --cur_left_bound;

            if (cur_left_bound >= 0)
            {
                left_two_words = sentence[cur_left_bound].first
                                        + " "
                                        + left_first_word;

                left_second_word = sentence[cur_left_bound].first;

                if (cur_left_bound - 1 >= 0 && is_article(sentence[cur_left_bound].first))
                {
                    left_two_words = sentence[cur_left_bound - 1].first
                                            + " "
                                            + left_two_words;


                    left_second_word = sentence[cur_left_bound - 1].first + left_second_word;
                }

                left_two_words_request = left_two_words + " " + preposition;
                // FOR TEST & LOG
                all_requests_.push_back(left_two_words_request);

                // left_two_words_request = "&quot;" + left_two_words_request + "&quot;";

                reqs_v = {left_second_word, left_first_word, left_two_words_request, "", ""};
                requests.insert(make_pair(-2, reqs_v));

            }
        }

        if (begin_ind >= 0 && begin_ind + len < sentence.size())
        {
            right_first_word = sentence[begin_ind + len].first;

            int cur_right_bound = begin_ind + len;
            if (begin_ind + len < sentence.size() - 1 && is_article(sentence[begin_ind + len].first))
            {
                right_first_word += " " + sentence[cur_right_bound + 1].first;

                ++cur_right_bound;
            }

            right_one_word_request = preposition + " " + right_first_word;
            // FOR TEST & LOG
            all_requests_.push_back(right_one_word_request);

            // right_one_word_request = "&quot;" + right_one_word_request + "&quot;";


            reqs_v = {"", "", right_one_word_request, right_first_word, ""};
            requests.insert(make_pair(1, reqs_v));

            ++cur_right_bound;

            if (cur_right_bound <= sentence.size() - 1)
            {
                right_two_words = right_first_word
                                         + " "
                                         + sentence[cur_right_bound].first;


                right_second_word = sentence[cur_right_bound].first;

                if (cur_right_bound + 1 <= sentence.size() - 1 && is_article(sentence[cur_right_bound].first))
                {
                    right_two_words += " " + sentence[cur_right_bound + 1].first;


                    right_second_word += sentence[cur_right_bound + 1].first;
                }


                right_two_words_request = preposition + " " + right_two_words;
                // FOR TEST & LOG
                all_requests_.push_back(right_two_words_request);

                // right_two_words_request = "&quot;" + right_two_words_request + "&quot;";

                reqs_v = {"", "", right_two_words_request, right_first_word, right_second_word};
                requests.insert(make_pair(2, reqs_v));
            }
        }

        if (!left_first_word.empty() && !right_first_word.empty())
        {
            string left_right_one_word_request = left_first_word
                                                 + " "
                                                 + preposition
                                                 + " "
                                                 + right_first_word;

            // FOR TEST & LOG
            all_requests_.push_back(left_right_one_word_request);

            // left_right_one_word_request = "&quot;" + left_right_one_word_request + "&quot;";
            reqs_v = {"", left_first_word, left_right_one_word_request, right_first_word, ""};
            requests.insert(make_pair(3, reqs_v));
        }

        if (!left_two_words.empty() && !right_two_words.empty())
        {
            string left_right_two_words_request = left_two_words
                                                  + " "
                                                  + preposition
                                                  + " "
                                                  + right_two_words;

            // FOR TEST & LOG
            all_requests_.push_back(left_right_two_words_request);

            // left_right_two_words_request = "&quot;" + left_right_two_words_request + "&quot;";

            // TODO такие запросы пока не отправляются вообще, слишком недетерминированно.
            // Тут они формируются - для симметрии. Поэтому не буду их помещать в возвращаемое значение
            //requests.insert(make_pair(5, left_right_two_words_request));
        }
    }

    return requests;
}

void text_analyzer::send_and_log_requests(vector<pair<string, size_t> > const& sentence,
                                          size_t begin_ind, size_t len,
                                          /*yandex_requester &requester,*/
                                          size_t line_counter, size_t word_counter,
                                          prepositions_dictionary& dictionary, string const& preposition)
{
    auto requests = build_requests(sentence, begin_ind, len);


    //посылка запросов:
    // строится ровно один запрос: типа 3, если нет, то -2 или 2, если нет, то -1 или 1

    vector<string> req_v;
    int req_type = 0;
    map<int, size_t> thresholds;
    thresholds.insert(std::make_pair(3, 100));
    thresholds.insert(std::make_pair(-2, 100));
    thresholds.insert(std::make_pair(2, 100));
    thresholds.insert(std::make_pair(-1, 1000));
    thresholds.insert(std::make_pair(1, 1000));

    if(requests.find(3) != requests.end())
    {
        req_v = requests[3];
        req_type = 3;
    }
    else if (requests.find(-2) != requests.end())
    {
        req_v = requests[-2];
        req_type = -2;
    }
    else if (requests.find(2) != requests.end())
    {
        req_v = requests[2];
        req_type = 2;
    }
    else if (requests.find(-1) != requests.end())
    {
        req_v = requests[-1];
        req_type = -1;
    }
    else if (requests.find(1) != requests.end())
    {
        req_v = requests[1];
        req_type = 1;
    }

    // посылаем сначала полноценный запрос со словами, потом - отдельно слова.
    // Информация о результате запроса только для предлога уже предпосчитана в словаре


    // тут может быть SEGV, если конструкция вида "..., at 01:00 local..." Не такого элемента req_v[2]



    // халтура! Смотри файл SEGV.txt, на нем падает, потому что не строится ни один реквест,
    // только предлог есть и все, поэтому req_v.size() == 0;
    // Но это только один случай, он почти не влияет на статистику вывода, а вот программу ломает. Пока забью на него
    if (req_v.size() < 1)
    {
        return;
    }
    all_sent_requests_info_.push_back({true, req_v[2],
                                       requester.send_request(req_v[2]),
                                       line_counter, word_counter,
                                       preposition, dictionary[preposition]});

    all_sent_requests_info_.push_back({false, "* " + preposition, (long long)dictionary[preposition],
                                       line_counter, word_counter,
                                       preposition, dictionary[preposition]});

    // для вычисления минимума
    vector<long long> word_and_prep_res;
    word_and_prep_res.push_back(dictionary[preposition]);

    for (int i = 0; i < req_v.size(); ++i)
    {
        if (!req_v[i].empty() && i != 2)
        {
            long long req_res = requester.send_request(req_v[i]);
            all_sent_requests_info_.push_back({false, req_v[i], req_res,
                                               line_counter, word_counter,
                                               preposition, dictionary[preposition]});

            word_and_prep_res.push_back(req_res);
        }
    }

    long long min_val = *(std::min_element(word_and_prep_res.begin(), word_and_prep_res.end()));
    all_sent_requests_info_.push_back({false, "*** MIN", min_val,
                                       line_counter, word_counter,
                                       preposition, dictionary[preposition]});

    // для пропуска строки в выводе в лог
    all_sent_requests_info_.push_back({false, "$$$", 0, 0, 0, "", 0});
//
//     long long req_res = 0;
//
//     int quot_size = 6;
//     req.erase(0, quot_size);
//     req.erase(req.size() - quot_size, quot_size);
//
//     FOR TEST
//    all_sent_requests_info_.push_back({req, req_res, line_counter, word_counter, preposition, dictionary[preposition]});
//
//
//
//     if (req_res <= (long long)(0.00000001 * dictionary[preposition]))
//     {
//         possible_mistakes_.push_back({req, line_counter, word_counter});
//     }
//
//
//    if (req_res <= thresholds[req_type])
//    {
//        possible_mistakes_.push_back({req, line_counter, word_counter});
//    }
}


void text_analyzer::analyze(logger &log)
{
    yandex_requester requester;

    string log_mode = log.get_severity();

    string line;
    size_t line_counter = 0;
    while (getline(text_, line))
    {
        ++line_counter;

        stringstream line_stream(line);

        string word;
        size_t word_counter = 0;
        vector<pair<string, size_t> > sentence;
        while (line_stream >> word)
        {
            ++word_counter;

            sentence.push_back(make_pair(word, word_counter));
            if (is_end(word))
            {
                remove_side_chars(sentence[0].first);
                remove_side_chars(sentence[sentence.size() - 1].first);

                for (size_t i = 0; i < sentence.size(); ++i)
                {
                    if (sentence[i].first.empty())
                    {
                        sentence.erase(sentence.begin() + i);

                        --i;
                        --word_counter;
                    }
                }

                if (sentence.empty()){ continue; }

                for (size_t i = 0; i < sentence.size(); ++i)
                {
                    string possible_preposition;
                    size_t word_num = 0;
                    size_t j = i;
                    vector<pair<string, size_t> > possible_prepositions;
                    while (j <= sentence.size() - 1  && word_num < 4)
                    {
                        possible_preposition = (!word_num) ? sentence[j].first
                                                           : possible_preposition
                                                             + " "
                                                             + sentence[j].first;
                        ++word_num;
                        ++j;

                        transform(possible_preposition.begin(), possible_preposition.end(),
                                  possible_preposition.begin(), ::tolower);

                        possible_prepositions.push_back(make_pair(possible_preposition, word_num));
                    }

                    for (auto it = possible_prepositions.rbegin(); it != possible_prepositions.rend(); ++it)
                    {
                        if (dictionary_.find(it->first))
                        {
                            all_prepositions_.push_back({it->first, line_counter, sentence[i].second});

                            size_t len = it->second;

                            send_and_log_requests(sentence, i, len, /*requester,*/ line_counter,
                                                  sentence[i].second, dictionary_, it->first);

                            i += len - 1;
                            possible_prepositions.clear();
                            break;
                        }
                    }
                }
                sentence.clear();
                //continue;
            }
        }
    }

    double sum = 0;
    int counter = 0;

    if (log_mode == "DEBUG")
    {
        log << text_.str() << (string)"\n";

        log << "Prepositions: " << (string)"\n";
        for (int i = 0; i < all_prepositions_.size(); ++i)
        {
            log << "Found" << std::setw(15) << all_prepositions_[i].preposition_
                << "   " << " at line: " << std::setw(5) << all_prepositions_[i].line_counter_
                << "    word: " << std::setw(5) << all_prepositions_[i].word_counter_ << (string)"\n";
        }
        log << (string)"\n";

        // если есть в слове кавычки, то setw как работает


        long long full_req_res = -1;
        for (int i = 0; i < all_sent_requests_info_.size(); ++i)
        {
            if (all_sent_requests_info_[i].request_ == "$$$")
            {
                log << (string)"\n";
                continue;
            }

            log << std::setw(35) << all_sent_requests_info_[i].request_
                << ": " << std::setw(12) << all_sent_requests_info_[i].result_;

            if (all_sent_requests_info_[i].is_full_req_)
            {
                full_req_res = all_sent_requests_info_[i].result_;
                log << "\tat line: " << std::setw(3) << all_sent_requests_info_[i].line_counter_
                    << "    word: " << std::setw(2) << all_sent_requests_info_[i].word_counter_
                    << "    preposition: " << std::setw(15) << all_sent_requests_info_[i].preposition_
                    << "    reference: " << std::setw(11) << all_sent_requests_info_[i].reference_result_
                    << "  ratio:       " << std::setw(5) << std::setprecision(9)
                    << std::setw(15) << (double)all_sent_requests_info_[i].result_ / all_sent_requests_info_[i].reference_result_;
            }
            if (all_sent_requests_info_[i].request_ == "*** MIN")
            {
                log << "\tFOUND RESULTS TO MIN: " << std::setprecision(9)
                    << std::setw(15) << (double)full_req_res / all_sent_requests_info_[i].result_;

                sum += (double)full_req_res / all_sent_requests_info_[i].result_;
                ++counter;
            }

//            sum += (double)all_sent_requests_info_[i].result_ / all_sent_requests_info_[i].reference_result_;
//            if ((double)all_sent_requests_info_[i].result_ / all_sent_requests_info_[i].reference_result_ > 0.00001)
//            {
//                log << "   *****";
//            }
            log << (string)"\n";
        }
    }
    log << (string)"\n";




    for (int i = 0; i < possible_mistakes_.size(); ++i)
    {
        log << "Possible mistake: " << "line: " << std::setw(3)
        << possible_mistakes_[i].line_counter_ << ", word: " << std::setw(3)
        << possible_mistakes_[i].word_counter_ << ": " << possible_mistakes_[i].request_ << (string)"\n";
    }

    log << "AVERAGE FOUND RESULTS TO MIN RATIO: " << sum / counter << (string)"\n";
    // почему шаблонный оператор << не работает (undefined reference),
    // если определить его в logger.cpp, а не в logger.hpp??????????????????????????????????????????????????????????????
}
