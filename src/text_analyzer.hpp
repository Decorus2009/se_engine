//#ifndef TEXT_ANALYZER_HPP
//#define TEXT_ANALYZER_HPP
//
//#include <sstream>
//#include <fstream>
//#include <vector>
//#include <map>
//#include <tuple>
//#include "prepositions_dictionary.hpp"
//#include "logger.hpp"
//#include "yandex_requester.hpp"
//
//struct text_analyzer
//{
//
//public:
//    text_analyzer(std::ifstream &text_file, std::string const& lang);
//    text_analyzer(text_analyzer const&) = delete;
//    text_analyzer &operator=(text_analyzer const&) = delete;
//
//    void analyze(logger &log);
//
//
//
//    // FOR TEST
//    inline std::string const &get_preposition(size_t ind) const { return all_preps_.at(ind).preposition_; }
//    inline std::string const &get_request(size_t ind) const { return all_requests_.at(ind); }
//    inline std::pair<std::string, long long> const get_request_result(size_t ind)
//    {
//        return std::make_pair(sent_req_inf_.at(ind).request_, sent_req_inf_.at(ind).result_);
//    }
//
//    inline size_t const get_all_preps_size() const { return all_preps_.size(); }
//    inline size_t const get_all_requests_size() const { return all_requests_.size(); }
//    inline size_t const get_sent_req_inf__size() const { return sent_req_inf_.size(); }
//
//
//private:
//    std::stringstream text_;
//    prepositions_dictionary dictionary_;
//
//    bool is_end(std::string const& word);
//    bool is_article(std::string const& word);
//    void remove_side_chars(std::string& word);
//    std::map<int, std::tuple<std::string, std::string, std::string, std::string, std::string>>
//            build_requests(std::vector<std::pair<std::string, size_t>> const& sentence,
//                                              size_t begin_ind, size_t len);
//
//    void send_and_log_requests(std::vector<std::pair<std::string, size_t> > const& sentence, size_t begin_ind,
//                               size_t len, yandex_requester& requester, size_t line_counter, size_t word_counter,
//                               prepositions_dictionary& dictionary, std::string const& preposition);
//
//
//
//    // FOR TEST AND LOG
//    struct preposition
//    {
//        std::string preposition_;
//        size_t line_counter_;
//        size_t word_counter_;
//    };
//    std::vector<preposition> all_preps_;
//    std::vector<std::string> all_requests_;
//
//    struct sent_req
//    {
//        bool is_full_req;
//        std::string request_;
//        long long result_;
//        size_t line_counter_;
//        size_t word_counter_;
//
//        // результат запроса только предлога, без остальных слов (из словаря)
//        std::string preposition_;
//        uint64_t reference_result_;
//        double full_to_min_ratio_;
//
//    };
//    std::vector<sent_req> sent_req_inf_;
//
//    struct possible_mistake
//    {
//        std::string request_;
//        size_t line_counter_;
//        size_t word_counter_;
//    };
//    std::vector<possible_mistake> possible_mistakes_;
//};
//
//
//
//
//
//#endif

#ifndef TEXT_ANALYZER_HPP
#define TEXT_ANALYZER_HPP

#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include "prepositions_dictionary.hpp"
#include "logger.hpp"
#include "yandex_requester.hpp"

struct text_analyzer
{

public:
    text_analyzer(std::ifstream &text_file, std::string const& thr_type);
    text_analyzer(text_analyzer const&) = delete;
    text_analyzer &operator=(text_analyzer const&) = delete;

    void analyze(logger &log, std::ofstream& thr_stat_file);



    // FOR TEST
    inline std::string const &get_preposition(size_t ind) const { return all_preps_.at(ind).prep_; }
    inline std::string const &get_request(size_t ind) const { return all_requests_.at(ind); }
    inline std::pair<std::string, long long> const get_request_result(size_t ind)
    {
        return std::make_pair(sent_req_inf_.at(ind).req_, sent_req_inf_.at(ind).res_);
    }

    inline size_t const get_all_preps_size() const { return all_preps_.size(); }
    inline size_t const get_all_requests_size() const { return all_requests_.size(); }
    inline size_t const get_sent_req_inf__size() const { return sent_req_inf_.size(); }

private:
    std::stringstream text_;
    prepositions_dictionary dictionary_;
    std::string thr_type_;

private:

    bool is_end(std::string const& word);
    bool is_article(std::string const& word);
    void remove_side_chars(std::string& word);
    std::map<int, std::vector<std::string>>
    build_requests(std::vector<std::pair<std::string, size_t>> const& sentence, size_t begin_ind, size_t len);

    void use_fixed_thr(int req_type, std::string const& req, long long req_res,
                       size_t line_counter, size_t word_counter);

    void use_fixed_context_dep_thr(long long full_req_res, std::vector<std::string> const& req_v,
                                   std::string const& preposition, prepositions_dictionary& dictionary,
                                   size_t line_counter, size_t word_counter);

    void send_and_log_requests(std::vector<std::pair<std::string, size_t> > const& sentence, size_t begin_ind,
                               size_t len, /*yandex_requester& requester, */size_t line_counter, size_t word_counter,
                               prepositions_dictionary& dictionary, std::string const& preposition);

    void write_log(logger& log, std::string const& log_mode, std::ofstream& thr_stat_file);
    template<class T>
    void write_thr_stat(T& t, double sum_found_to_min, int counter_found_to_min);


    // FOR TEST AND LOG
    struct preposition
    {
        std::string prep_;
        size_t line_c_;
        size_t word_c_;
    };
    std::vector<preposition> all_preps_;
    std::vector<std::string> all_requests_;

    struct sent_req
    {
        bool is_full_req_;
        std::string req_;
        long long res_;
        size_t line_c_;
        size_t word_c_;

        // результат запроса только предлога, без остальных слов (из словаря)
        std::string prep_;
        uint64_t ref_res_;
    };
    std::vector<sent_req> sent_req_inf_;

    struct possible_mistake
    {
        std::string req_;
        size_t line_c_;
        size_t word_c_;
    };
    std::vector<possible_mistake> possible_mistakes_;
};





#endif
