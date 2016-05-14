//#include "text_analyzer_ru.hpp"
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
//using std::wstring;
//using std::wstringstream;
//
//text_analyzer_ru::text_analyzer_ru(std::ifstream& text_file, std::string const& lang) try : dictionary_(lang)
//{
//    text_ << text_file.rdbuf();
//}
//catch (std::exception const& e)
//{
//    std::cerr << "Error in opening/reading dictionary" << std::endl;
//    throw;
//}
//
//bool text_analyzer_ru::is_end(wstring const& word)
//{
//    // исключение - предлог o'. not yet implemented
//    return !isalpha(word[word.length() - 1]);
//}
//bool text_analyzer_ru::is_article(wstring const& word)
//{
//    return (word == "the" || word == "an" || word == "a");
//}
//
//void text_analyzer_ru::remove_side_chars(wstring& word) {
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
//map<int, wstring> text_analyzer_ru::
//build_requests(vector<pair<wstring, size_t>> const& sentence, size_t begin_ind, size_t len) {
//
//    map<int, wstring> requests;
//
//    wstring left_one_word_prefix, right_one_word_suffix,
//            left_two_words_prefix, right_two_words_suffix,
//            left_one_word_request, right_one_word_request,
//            left_two_words_request, right_two_words_request;
//
//    // формирование предлога (он может быть длиннее одного слова)
//    wstring preposition = sentence[begin_ind].first;
//    for (size_t i = begin_ind + 1; i < begin_ind + len; ++i)
//    {
//        preposition = preposition + " " + sentence[i].first;
//    }
//
//    if (sentence.size() > 1)
//    {
//        if (begin_ind + len <= sentence.size() && begin_ind > 0)
//        {
//            left_one_word_prefix += sentence[begin_ind - 1].first;
//
//            int cur_left_bound = begin_ind - 1;
//
//            if (begin_ind - 1 > 0 && is_article(sentence[cur_left_bound].first))
//            {
//                left_one_word_prefix = sentence[cur_left_bound - 1].first
//                                       + " "
//                                       + left_one_word_prefix;
//
//                --cur_left_bound;
//            }
//
//            left_one_word_request = left_one_word_prefix + " " + preposition;
//
//            // FOR TEST & LOG
//            all_requests_.push_back(left_one_word_request);
//
//            left_one_word_request = "&quot;" + left_one_word_request + "&quot;";
//
//            requests.insert(make_pair(-1, left_one_word_request));
//
//            --cur_left_bound;
//
//            if (cur_left_bound >= 0)
//            {
//                left_two_words_prefix = sentence[cur_left_bound].first
//                                        + " "
//                                        + left_one_word_prefix;
//
//                if (cur_left_bound - 1 >= 0 && is_article(sentence[cur_left_bound].first))
//                {
//                    left_two_words_prefix = sentence[cur_left_bound - 1].first
//                                            + " "
//                                            + left_two_words_prefix;
//                }
//
//                left_two_words_request = left_two_words_prefix + " " + preposition;
//                // FOR TEST & LOG
//                all_requests_.push_back(left_two_words_request);
//
//                left_two_words_request = "&quot;" + left_two_words_request + "&quot;";
//
//                requests.insert(make_pair(-2, left_two_words_request));
//            }
//        }
//
//        if (begin_ind >= 0 && begin_ind + len < sentence.size())
//        {
//            right_one_word_suffix = sentence[begin_ind + len].first;
//
//            int cur_right_bound = begin_ind + len;
//            if (begin_ind + len < sentence.size() - 1 && is_article(sentence[begin_ind + len].first))
//            {
//                right_one_word_suffix += " " + sentence[cur_right_bound + 1].first;
//
//                ++cur_right_bound;
//            }
//
//            right_one_word_request = preposition + " " + right_one_word_suffix;
//            // FOR TEST & LOG
//            all_requests_.push_back(right_one_word_request);
//
//            right_one_word_request = "&quot;" + right_one_word_request + "&quot;";
//
//            requests.insert(make_pair(1, right_one_word_request));
//
//            ++cur_right_bound;
//
//            if (cur_right_bound <= sentence.size() - 1)
//            {
//                right_two_words_suffix = right_one_word_suffix
//                                         + " "
//                                         + sentence[cur_right_bound].first;
//
//                if (cur_right_bound + 1 <= sentence.size() - 1 && is_article(sentence[cur_right_bound].first))
//                {
//                    right_two_words_suffix += " " + sentence[cur_right_bound + 1].first;
//                }
//
//
//                right_two_words_request = preposition + " " + right_two_words_suffix;
//                // FOR TEST & LOG
//                all_requests_.push_back(right_two_words_request);
//
//                right_two_words_request = "&quot;" + right_two_words_request + "&quot;";
//
//                requests.insert(make_pair(2, right_two_words_request));
//            }
//        }
//
//        if (!left_one_word_prefix.empty() && !right_one_word_suffix.empty())
//        {
//            wstring left_right_one_word_request = left_one_word_prefix
//                                                 + " "
//                                                 + preposition
//                                                 + " "
//                                                 + right_one_word_suffix;
//
//            // FOR TEST & LOG
//            all_requests_.push_back(left_right_one_word_request);
//
//            left_right_one_word_request = "&quot;" + left_right_one_word_request + "&quot;";
//            requests.insert(make_pair(3, left_right_one_word_request));
//        }
//
//        if (!left_two_words_prefix.empty() && !right_two_words_suffix.empty())
//        {
//            wstring left_right_two_words_request = left_two_words_prefix
//                                                  + " "
//                                                  + preposition
//                                                  + " "
//                                                  + right_two_words_suffix;
//
//            // FOR TEST & LOG
//            all_requests_.push_back(left_right_two_words_request);
//
//            left_right_two_words_request = "&quot;" + left_right_two_words_request + "&quot;";
//            requests.insert(make_pair(5, left_right_two_words_request));
//        }
//    }
//
//    return requests;
//}
//
//void text_analyzer_ru::send_and_log_requests(vector<pair<wstring, size_t> > const& sentence,
//                                          size_t begin_ind, size_t len,
//                                          yandex_requester &requester,
//                                          size_t line_counter, size_t word_counter,
//                                          prepositions_dictionary& dictionary, wstring const& preposition)
//{
//    auto requests = build_requests(sentence, begin_ind, len);
//
//
//    //посылка запросов:
//    // строится ровно один запрос: типа 3, если нет, то -2 или 2, если нет, то -1 или 1
//
//    wstring req;
//    int req_type = 0;
//    map<int, size_t> thresholds;
//    thresholds.insert(std::make_pair(3, 100));
//    thresholds.insert(std::make_pair(-2, 100));
//    thresholds.insert(std::make_pair(2, 100));
//    thresholds.insert(std::make_pair(-1, 1000));
//    thresholds.insert(std::make_pair(1, 1000));
//
//    if(requests.find(3) != requests.end())
//    {
//        req = requests[3];
//        req_type = 3;
//    }
//    else if (requests.find(-2) != requests.end())
//    {
//        req = requests[-2];
//        req_type = -2;
//    }
//    else if (requests.find(2) != requests.end())
//    {
//        req = requests[2];
//        req_type = 2;
//    }
//    else if (requests.find(-1) != requests.end())
//    {
//        req = requests[-1];
//        req_type = -1;
//    }
//    else if (requests.find(1) != requests.end())
//    {
//        req = requests[1];
//        req_type = 1;
//    }
//
//    long long req_res = requester.send_request(req);
//    // long long req_res = 0;
//
//    int quot_size = 6;
//    req.erase(0, quot_size);
//    req.erase(req.size() - quot_size, quot_size);
//
//    // FOR TEST
//    all_sent_requests_info_.push_back({req, req_res, line_counter, word_counter, preposition, dictionary[preposition]});
//
//
//
//    // if (req_res <= (long long)(0.00000001 * dictionary[preposition]))
//    // {
//    //     possible_mistakes_.push_back({req, line_counter, word_counter});
//    // }
//
//
//    if (req_res <= thresholds[req_type])
//    {
//        possible_mistakes_.push_back({req, line_counter, word_counter});
//    }
//
//
//
//    // запрос с двумя словами слева и справа
//    // TODO or not?
//}
//
//
//void text_analyzer_ru::analyze(logger &log)
//{
//    yandex_requester requester;
//
//    wstring log_mode = log.get_severity();
//
//    wstring line;
//    size_t line_counter = 0;
//    while (getline(text_, line))
//    {
//        ++line_counter;
//
//        wstringstream line_stream(line);
//
//        wstring word;
//        size_t word_counter = 0;
//        vector<pair<wstring, size_t> > sentence;
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
//                    wstring possible_preposition;
//                    size_t word_num = 0;
//                    size_t j = i;
//                    vector<pair<wstring, size_t> > possible_prepositions;
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
//
//    if (log_mode == "DEBUG")
//    {
//        log << text_.str() << (wstring)"\n";
//
//        log << "Prepositions: " << (wstring)"\n";
//        for (int i = 0; i < all_prepositions_.size(); ++i)
//        {
//            log << "Found" << std::setw(15) << all_prepositions_[i].preposition_
//            << "   " << " at line: " << std::setw(5) << all_prepositions_[i].line_counter_
//            << "    word: " << std::setw(5) << all_prepositions_[i].word_counter_ << (wstring)"\n";
//        }
//        log << (wstring)"\n";
//
//
//        // если есть в слове кавычки, то setw как работает
//
//
//        for (int i = 0; i < all_sent_requests_info_.size(); ++i)
//        {
//            log << std::setw(35) << all_sent_requests_info_[i].request_
//            << ": " << std::setw(12) << all_sent_requests_info_[i].result_
//            << "\tat line: " << std::setw(3) << all_sent_requests_info_[i].line_counter_
//            << "    word: " << std::setw(2) << all_sent_requests_info_[i].word_counter_
//            << "    preposition: " << std::setw(15) << all_sent_requests_info_[i].preposition_
//            << "    reference: " << std::setw(11) << all_sent_requests_info_[i].reference_result_
//            << "  ratio:       " << std::setw(5) << std::setprecision(9)
//            << std::setw(15) << (double)all_sent_requests_info_[i].result_ / all_sent_requests_info_[i].reference_result_;
//
//            sum += (double)all_sent_requests_info_[i].result_ / all_sent_requests_info_[i].reference_result_;
//
//            if ((double)all_sent_requests_info_[i].result_ / all_sent_requests_info_[i].reference_result_ > 0.00001)
//            {
//                log << "   *****";
//            }
//            log << (wstring)"\n";
//        }
//    }
//    log << (wstring)"\n";
//
//    for (int i = 0; i < possible_mistakes_.size(); ++i)
//    {
//        log << "Possible mistake: " << "line: " << std::setw(3)
//        << possible_mistakes_[i].line_counter_ << ", word: " << std::setw(3)
//        << possible_mistakes_[i].word_counter_ << ": " << possible_mistakes_[i].request_ << (wstring)"\n";
//    }
//
//    std::cout << "average ratio: " << sum / all_sent_requests_info_.size() << std::endl << std::endl;
//    // почему шаблонный оператор << не работает (undefined reference),
//    // если определить его в logger.cpp, а не в logger.hpp??????????????????????????????????????????????????????????????
//}
