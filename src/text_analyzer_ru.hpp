#ifndef SRC_EXE_TEXT_ANALYZER_RU_HPP
#define SRC_EXE_TEXT_ANALYZER_RU_HPP

#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include "prepositions_dictionary.hpp"
#include "logger.hpp"
#include "yandex_requester.hpp"

struct text_analyzer_ru
{

public:
    text_analyzer_ru(std::ifstream &text_file, std::string const& lang);
    text_analyzer_ru(text_analyzer_ru const&) = delete;
    text_analyzer_ru &operator=(text_analyzer_ru const&) = delete;

    void analyze(logger &log);



    // FOR TEST
    inline std::wstring const &get_preposition(size_t ind) const { return all_prepositions_.at(ind).preposition_; }
    inline std::wstring const &get_request(size_t ind) const { return all_requests_.at(ind); }
    inline std::pair<std::wstring, long long> const get_request_result(size_t ind)
    {
        return std::make_pair(all_sent_requests_info_.at(ind).request_, all_sent_requests_info_.at(ind).result_);
    }

    inline size_t const get_all_prepositions_size() const { return all_prepositions_.size(); }
    inline size_t const get_all_requests_size() const { return all_requests_.size(); }
    inline size_t const get_all_sent_requests_info__size() const { return all_sent_requests_info_.size(); }


private:
    std::wstringstream text_;
    prepositions_dictionary dictionary_;

    bool is_end(std::wstring const& word);
    bool is_article(std::wstring const& word);
    void remove_side_chars(std::wstring& word);
    std::map<int, std::wstring> build_requests(std::vector<std::pair<std::wstring, size_t>> const& sentence,
                                              size_t begin_ind, size_t len);

    void send_and_log_requests(std::vector<std::pair<std::wstring, size_t> > const& sentence, size_t begin_ind,
                               size_t len, yandex_requester& requester, size_t line_counter, size_t word_counter,
                               prepositions_dictionary& dictionary, std::wstring const& preposition);



    // FOR TEST AND LOG
    struct preposition
    {
        std::wstring preposition_;
        size_t line_counter_;
        size_t word_counter_;
    };
    std::vector<preposition> all_prepositions_;
    std::vector<std::wstring> all_requests_;

    struct sent_request
    {
        std::wstring request_;
        long long result_;
        size_t line_counter_;
        size_t word_counter_;

        // результат запроса только предлога, без остальных слов (из словаря)
        std::wstring preposition_;
        uint64_t reference_result_;
    };
    std::vector<sent_request> all_sent_requests_info_;

    struct possible_mistake
    {
        std::wstring request_;
        size_t line_counter_;
        size_t word_counter_;
    };
    std::vector<possible_mistake> possible_mistakes_;
};


#endif