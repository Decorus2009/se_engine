#include "text_analyzer.hpp"
#include <iomanip>
#include <algorithm>

using std::map;
using std::pair;
using std::vector;
using std::string;
using std::stringstream;
using std::tuple;


static yandex_requester requester;

text_analyzer::text_analyzer(std::ifstream& text_file, string const& thr_type)
try : dictionary_(), thr_type_(thr_type)
{
    text_ << text_file.rdbuf();
}
catch (std::exception const& e)
{
    std::cerr << "Error in opening/reading dictionary" << std::endl;
    throw;
}


void text_analyzer::use_fixed_thr(int req_type, string const& req, long long req_res,
                                  size_t line_counter, size_t word_counter)
{
    map<int, size_t> thresholds;
    thresholds.insert(std::make_pair( 3,  100));
    thresholds.insert(std::make_pair(-2,  100));
    thresholds.insert(std::make_pair( 2,  100));
    thresholds.insert(std::make_pair(-1, 1000));
    thresholds.insert(std::make_pair( 1, 1000));

    if (req_res <= thresholds[req_type])
    {
        possible_mistakes_.push_back({req, line_counter, word_counter});
    }
}

void text_analyzer::use_fixed_context_dep_thr(long long full_req_res, vector<string> const& req_v,
                                              string const& preposition, prepositions_dictionary& dictionary,
                                              size_t line_counter, size_t word_counter, stringstream& ya_req_res_stream)
{
    sent_req_inf_.push_back({false, "* " + preposition, (long long)dictionary[preposition],
                             line_counter, word_counter, preposition, dictionary[preposition]});

    // для вычисления минимума
    vector<long long> word_and_prep_res;
    word_and_prep_res.push_back(dictionary[preposition]);

    for (int i = 0; i < req_v.size(); ++i)
    {
        // сам предлог предпосчитан
        if (!req_v[i].empty() && i != 2)
        {





//            long long req_res = requester.send_request(req_v[i]);
//            ya_req_res_file << req_res << std::endl;
            string ya_req_res_line;
            getline(ya_req_res_stream, ya_req_res_line);
            long long req_res = std::stoll(ya_req_res_line);






            sent_req_inf_.push_back({false, req_v[i], req_res, line_counter,
                                     word_counter, preposition, dictionary[preposition]});

            word_and_prep_res.push_back(req_res);
        }
    }

    long long min_val = *(std::min_element(word_and_prep_res.begin(), word_and_prep_res.end()));

    sent_req_inf_.push_back({false, "*** MIN", min_val,
                             line_counter, word_counter, preposition, dictionary[preposition]});
    // для пропуска строки в выводе в лог
    sent_req_inf_.push_back({false, "$$$", 0, 0, 0, "", 0});


    if (min_val)
    {
        double full_req_to_min_ratio = (double)full_req_res / min_val;

        double thr = 0.0000016;
        if (full_req_to_min_ratio < thr)
        {
            possible_mistakes_.push_back({req_v[2], line_counter, word_counter});
        }
    }
}

map<int, vector<string>> text_analyzer::
build_requests(vector<pair<string, size_t>> const& sentence, size_t begin_ind, size_t len)
{

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

            // TODO такие запросы пока не отправляются вообще, слишком недетерминированно.
            // Тут они формируются - для симметрии. Не буду их помещать в возвращаемое значение
            //requests.insert(make_pair(5, left_right_two_words_request));
        }
    }
    return requests;
}

void text_analyzer::send_and_log_requests(vector<pair<string, size_t> > const& sentence, size_t begin_ind, size_t len,
                                          size_t line_counter, size_t word_counter,
                                          prepositions_dictionary& dictionary, string const& preposition,
                                          stringstream& ya_req_res_stream)
{
    auto requests = build_requests(sentence, begin_ind, len);

    // строится ровно один запрос: типа 3, если нет, то -2 или 2, если нет, то -1 или 1
    vector<string> req_v;
    int req_type = 0;
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

    // тут может быть SEGV, если конструкция вида "..., at 01:00 local..." Нет такого элемента req_v[2]
    if (req_v.size() < 1) { return; }


    // в любом случае шлем полноценный запрос. Потом - опционально в зависимости от типа порога
//    long long full_req_res = requester.send_request(req_v[2]);
//    ya_req_res_file << full_req_res << std::endl;


    string ya_full_req_res_line;
    getline(ya_req_res_stream, ya_full_req_res_line);
    long long full_req_res = std::stoll(ya_full_req_res_line);





    sent_req_inf_.push_back({true, req_v[2], full_req_res, line_counter, word_counter, preposition, dictionary[preposition]});

    if (thr_type_ == "-fixed")
    {
        use_fixed_thr(req_type, req_v[2], full_req_res, line_counter, word_counter);
    }
    else if (thr_type_ == "-fixed_context_dep")
    {
        use_fixed_context_dep_thr(full_req_res, req_v, preposition, dictionary, line_counter, word_counter, ya_req_res_stream);
    }
    else if (thr_type_ == "-dynamic_context_dep")
    {

    }
}

void text_analyzer::analyze(logger &log, std::ofstream& thr_stat_file, stringstream& ya_req_res_stream, std::ofstream& aver_res_file)
{
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
                            all_preps_.push_back({it->first, line_counter, sentence[i].second});

                            size_t len = it->second;

                            send_and_log_requests(sentence, i, len, line_counter,
                                                  sentence[i].second, dictionary_, it->first, ya_req_res_stream);

                            i += len - 1;
                            possible_prepositions.clear();
                            break;
                        }
                    }
                }
                sentence.clear();
            }
        }
    }
    write_log(log, log_mode, thr_stat_file, aver_res_file);
}


void text_analyzer::write_log(logger& log, string const& log_mode,
                              std::ofstream& thr_stat_file, std::ofstream& aver_res_file)
{
    using std::setw;
    using std::setprecision;
    using std::scientific;
    using std::fixed;

    double sum_found_to_min = 0;
    int counter_found_to_min = 0;

    long long full_req_res = 0;
//    for (int i = 0; i < sent_req_inf_.size(); ++i)
//    {
//        if (sent_req_inf_[i].is_full_req_)
//        {
//            full_req_res = sent_req_inf_[i].res_;
//        }
//        if (sent_req_inf_[i].req_ == "*** MIN")
//        {
//            // тут sent_req_inf_[i].res_ - минимум, вычисленный и записанный в структуру ранее
//            sum_found_to_min += (double)full_req_res / sent_req_inf_[i].res_;
//            ++counter_found_to_min;
//        }
//    }

    if (log_mode == "-d")
    {
//        log << text_.str() << (string)"\n";
        log << "PREPOSITIONS:\n";
        for (int i = 0; i < all_preps_.size(); ++i)
        {
            log << "Found"
                << setw(25) << all_preps_[i].prep_
                << setw(12) << "at line:"
                << setw(4)  << all_preps_[i].line_c_
                << setw(8) << "word:"
                << setw(4)  << all_preps_[i].word_c_
                << (string)"\n";
        }
        log << (string)"\n" << "RESULTS:\n";


        full_req_res = 0;
        for (int i = 0; i < sent_req_inf_.size(); ++i)
        {
            if (sent_req_inf_[i].req_ == "$$$") { log << (string)"\n"; continue; }

            log << setw(35) << sent_req_inf_[i].req_
                << ":"
                << setw(13) << sent_req_inf_[i].res_;

            if (sent_req_inf_[i].is_full_req_)
            {
                full_req_res = sent_req_inf_[i].res_;

                log << setw(12) << "at line:"
                    << setw(3)  << sent_req_inf_[i].line_c_
                    << setw(6)  << "word:"
                    << setw(3)  << sent_req_inf_[i].word_c_
                    //<< setw(15) << "preposition:"
                    << setw(16) << sent_req_inf_[i].prep_
                    << setw(13) << "reference:"
                    << setw(15) << sent_req_inf_[i].ref_res_
                    << setw(8)  << "ratio:"
                    << setprecision(3)
                    << setw(13) << scientific << (double)sent_req_inf_[i].res_ / sent_req_inf_[i].ref_res_;
            }

            if (sent_req_inf_[i].req_ == "*** MIN")
            {
                log << setw(18) << "FOUND TO MIN: "
                    << setprecision(3)
                    << setw(13) << scientific << (double)full_req_res / sent_req_inf_[i].res_;

                // тут sent_req_inf_[i].res_ - минимум, вычисленный и записанный в структуру ранее
                sum_found_to_min += (double)full_req_res / sent_req_inf_[i].res_;
                ++counter_found_to_min;
            }
            log << (string)"\n";
        }
    }
    log << (string)"\n";

    if (log_mode != "-n")
    {
        for (int i = 0; i < possible_mistakes_.size(); ++i)
        {
            log << "Possible mistake!"
            << setw(6) << "Line:"
            << setw(3) << possible_mistakes_[i].line_c_
            << setw(6) << "word:"
            << setw(3) << possible_mistakes_[i].word_c_ << ":"
            << setw(36) << possible_mistakes_[i].req_ << (string)"\n";
        }
        log << (string)"\n";


        write_thr_stat(log, sum_found_to_min, counter_found_to_min);
//        write_thr_stat(thr_stat_file, sum_found_to_min, counter_found_to_min);
    }


    double poss_mist_to_full_req_ratio = (double)possible_mistakes_.size() / all_preps_.size();
    double remaining = 1.0 - poss_mist_to_full_req_ratio;
    aver_res_file << setprecision(1) << fixed << poss_mist_to_full_req_ratio * 100 << std::endl;
    aver_res_file << setprecision(1) << fixed << remaining * 100 << std::endl;


}

// utilities
template<class T>
void text_analyzer::write_thr_stat(T& stream, double sum_found_to_min, int counter_found_to_min)
{
    using std::setw;
    using std::setprecision;
    using std::scientific;
    using std::fixed;

    stream << "AVERAGE: FOUND TO MIN:"
           << setprecision(3)
           << setw(27) << scientific << sum_found_to_min / counter_found_to_min << (string)"\n";
    stream << "TOTAL: FULL REQS NUM:"
           << setw(28) << all_preps_.size() << (string)"\n";
    stream << "TOTAL: POSS MIST NUM:"
           << setw(28) << possible_mistakes_.size() << (string)"\n";


    // дублирование кода
    double poss_mist_to_full_req_ratio = (double)possible_mistakes_.size() / all_preps_.size();
    stream << "RATIO: POSS MIST NUM TO FULL REQS NUM:"
           << setprecision(1)
           << setw(10) << fixed << poss_mist_to_full_req_ratio * 100
           << "%" << (string)"\n";

    double remaining = 1.0 - poss_mist_to_full_req_ratio;
    stream << "RATIO: REMAINING"
           << setprecision(1)
           << setw(32) << fixed << remaining * 100
           << "%" << (string)"\n";
}
bool text_analyzer::is_end(string const& word)
{
    return !isalpha(word[word.length() - 1]);
}
bool text_analyzer::is_article(string const& word)
{
    return (word == "the" || word == "an" || word == "a");
}
void text_analyzer::remove_side_chars(string& word)
{
    while (word.length() && !isalpha(word[0]))
    {
        word.erase(0, 1);
    }
    while (word.length() && !isalpha(word[word.length() - 1]))
    {
        word.erase(word.length() - 1, 1);
    }
}


