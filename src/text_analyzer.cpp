#include "text_analyzer.hpp"
#include "yandex_requester.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctype.h>


using std::map;
using std::pair;
using std::vector;
using std::string;
using std::stringstream;

text_analyzer::text_analyzer(std::ifstream& text_file) : dictionary_() {

    text_ << text_file.rdbuf();
}
// never used
bool is_begin(string const& word) {
/*
 * предлоги, начинающиеся с '. Рассмотреть их отдельно?
 * Как не перепутать с началом обычной фразы в кавычках?
 * 'long - вполне может быть началом фразы в кавычках со словом long.
 * Предлог ни при чем. Забить и всё равно гуглить?
 * Также можно просто в списке предлогов убрать '. Кажется, яндексу пофиг на ' при поиске.
    'bout
    'gainst
    'long
    'mong
    'mongst
    'round
    'neath
    'til
    'pon
    'twixt
*/
    return !isalpha(word[0]);
}

bool is_end(string const& word) {
    // исключение - предлог o'. not yet implemented
    return !isalpha(word[word.length() - 1]);
}

void remove_side_chars(string& word) {

    // удаление первого символа пока он не буква и пока длина слова > 0
    while (word.length() && !isalpha(word[0])) {
        word.erase(0, 1);
    }
    // удаление последнего символа пока он не буква и пока длина слова > 0
    while (word.length() && !isalpha(word[word.length() - 1])) {
        word.erase(word.length() - 1, 1);
    }
}

// можно ради оптимизации попробовать возвращать ссылки
map<int, string> build_requests(vector<pair<string, size_t>> const& sentence,
                                          size_t begin_ind, size_t len) {

    // также "fly by the road" - полноценный запрос даст около 10 ответов,
    // тогда как "fly by" и "by the road" вернут много результатов
    // правльнее, кажется искать со словами справа и слева

    // например, хорошо работает "glaring at him" - 19000 vs. "glaring with him" - 4 ответа




    // замечание: "his idea of hiding here" - 25 ответов.
    // "his idea by hiding here" - 10 000 000 ответов. Скорее всего фразу именно в кавычках он не нашел нигде,
    // поэтому поисковый запрос преобразовался в обычный без кавычек.
    // Как тогда быть, ведь такое значение выше любого порога???????????????????????????????????????????????????????





    // результат записывается в map, ключ - тип запроса, значение - запрос
    // ключи:
    // -1 - запрос с одним словом левее (артикль не считается)
    // +1 - с одним словом правее
    // -2/+2 - с двумя словами левее/правее
    // 3 - запрос, содержащий предлог с одним словом слева и одним словом справа
    // 5 - по два слова по бокам)

    map<int, string> requests;

    // нужны для отдельного формирования запросов со одним словом и справа, и слева
    string left_one_word_prefix;
    string right_one_word_suffix;
    // нужны для отдельного формирования запросов с двуся словами и справа, и слева
    string left_two_words_prefix;
    string right_two_words_suffix;
    // полноценные запросы с одним словом справа и слева
    string left_one_word_request;
    string right_one_word_request;
    // полноценные запросы с двумя словами справа и слева
    string left_two_words_request;
    string right_two_words_request;

    // формирование предлога (он может быть длиннее одного слова)
    string preposition = sentence[begin_ind].first;
    for (size_t i = begin_ind + 1; i < begin_ind + len; ++i) {

        preposition = preposition + " " + sentence[i].first;
    }

    if (sentence.size() > 1) {

        // левый запрос
        if (begin_ind + len <= sentence.size() && begin_ind > 0) {

            left_one_word_prefix += sentence[begin_ind - 1].first;

            // cur_left_bound соответствует слову левее предлога
            int cur_left_bound = begin_ind - 1;

            // если левое слово в запросе - артикль и есть еще слова левее
            if (begin_ind - 1 > 0
                && sentence[cur_left_bound].first == "the"
                || sentence[cur_left_bound].first == "an"
                || sentence[cur_left_bound].first == "a") {

                left_one_word_prefix = sentence[cur_left_bound - 1].first
                                       + " "
                                       + left_one_word_prefix;

                // теперь cur_left_bound соответствует слову левее артикля
                --cur_left_bound;
            }

            // left_one_word_request для одного слова левее (ну или с артиклем)
            left_one_word_request = "&quot;"
                                    + left_one_word_prefix
                                    + " "
                                    + preposition
                                    + "&quot;";
            requests.insert(make_pair(-1, left_one_word_request));

            // cur_left_bound соответствует слову левее слова левее предлога
            // (либо, если if выше выполнился - слову левее слова левее артикля)
            --cur_left_bound;

            if (cur_left_bound >= 0) {
                left_two_words_prefix = sentence[cur_left_bound].first
                                        + " "
                                        + left_one_word_prefix;

                left_two_words_request = "&quot;"
                                         + left_two_words_prefix
                                         + " "
                                         + preposition
                                         + "&quot;";

                requests.insert(make_pair(-2, left_two_words_request));
            }
        }

        // правый запрос
        if (begin_ind >= 0 && begin_ind + len < sentence.size()) {

            right_one_word_suffix = sentence[begin_ind + len].first;

            // cur_right_bound соответствует слову правее предлога
            int cur_right_bound = begin_ind + len;
            // если слово, прикрепленное справа - артикль - смещаемся еще на слово правее, если можно
            if (begin_ind + len < sentence.size() - 1
                && sentence[begin_ind + len].first == "the"
                || sentence[begin_ind + len].first == "an"
                || sentence[begin_ind + len].first == "a") {

                right_one_word_suffix += " " + sentence[cur_right_bound + 1].first;

                // теперь cur_right_bound соответствует слову правее артикля
                ++cur_right_bound;
            }

            right_one_word_request = "&quot;"
                                     + preposition
                                     + " "
                                     + right_one_word_suffix
                                     + "&quot;";

            requests.insert(make_pair(1, right_one_word_request));

            // cur_right_bound соответствует слову правее слова правее предлога
            // (либо, если if выше выполнился - слову правее слова правее артикля)
            ++cur_right_bound;

            if (cur_right_bound <= sentence.size() - 1) {

                right_two_words_suffix = right_one_word_suffix
                                         + " "
                                         + sentence[cur_right_bound].first;

                right_two_words_request = "&quot;"
                                          + preposition
                                          + " "
                                          + right_two_words_suffix
                                          + "&quot;";

                requests.insert(make_pair(2, right_two_words_request));
            }
        }

        // запрос справа и слева, если слева и справа от предлога есть какие-то слова
        // может быть совсем мало ответов: "trying to butt" -> 352 ответа всего.
        // "it's in the air" -> 3000
        // "it's on the air" -> 361, "on the air" - уже 48000 - и по идее так говорить правильно,
        // => 361 - значение выше какого-то порога.

        if (!left_one_word_prefix.empty()
            && !right_one_word_suffix.empty()) {

            string left_right_one_word_request = "&quot;"
                                                 + left_one_word_prefix
                                                 + " "
                                                 + preposition
                                                 + " "
                                                 + right_one_word_suffix
                                                 + "&quot;";

            requests.insert(make_pair(3, left_right_one_word_request));
        }
        if (!left_two_words_prefix.empty()
            && !right_two_words_suffix.empty()) {

            string left_right_two_words_request = "&quot;"
                                                  + left_two_words_prefix
                                                  + " "
                                                  + preposition
                                                  + " "
                                                  + right_two_words_suffix
                                                  + "&quot;";

            requests.insert(make_pair(5, left_right_two_words_request));
        }
    }

    return requests;
}

void send_and_log_requests(vector<pair<string, size_t> > const& sentence,
                           size_t begin_ind, size_t len,
                           yandex_requester &requester,
                           size_t line_counter, size_t word_counter,
                           stringstream &results_info,
                           string const &log_mode) {

    // формирование запросов
    auto requests = build_requests(sentence, begin_ind, len);


    //посылка запросов:
    // строится ровно один запрос: типа 3, если нет, то -2 или 2, если нет, то -1 или 1

    string req;
    int req_type = 0;
    map<int, size_t> thresholds;
    thresholds.insert(std::make_pair(3, 100));
    thresholds.insert(std::make_pair(-2, 100));
    thresholds.insert(std::make_pair(2, 100));
    thresholds.insert(std::make_pair(-1, 1000));
    thresholds.insert(std::make_pair(1, 1000));

    if(requests.find(3) != requests.end()) {

        req = requests[3];
        req_type = 3;

        if (log_mode == "DEBUG") {
            results_info << " 3" << std::setw(35);
        }
    }
    // иначе - запросы с двумя словами - только слева, либо только справа
    // (одновременно запросы с двумя словами и слева, и справа не найти,
    // т.к. не нашлось даже запроса с одним словом и слева, и справа)

    // если есть левый запрос на два слова
    else if (requests.find(-2) != requests.end()) {

        req = requests[-2];
        req_type = -2;

        if (log_mode == "DEBUG") {
            results_info << "-2" << std::setw(35);
        }
    }
    // если есть правый запрос на два слова
    else if (requests.find(2) != requests.end()) {

        req = requests[2];
        req_type = 2;

        if (log_mode == "DEBUG") {
            results_info << " 2" << std::setw(35);
        }
    }
    // иначе рассматриваем возможные запросы - только с одним словом слева,
    // либо только с одним словом справа.
    // если есть левый запрос на 1 слово
    else if (requests.find(-1) != requests.end()) {

        req = requests[-1];
        req_type = -1;

        if (log_mode == "DEBUG") {
            results_info << "-1" << std::setw(35);
        }
    }
    // если есть правый запрос на 1 слово
    else if (requests.find(1) != requests.end()) {

        req = requests[1];
        req_type = 1;

        if (log_mode == "DEBUG") {
            results_info << " 1" << std::setw(35);
        }
    }

    long long req_res = requester.send_request(req);

    // отрезаем "quot;"
    // надо только для вывода в дебаге
    int quot_size = 6;
    req.erase(0, quot_size);
    req.erase(req.size() - quot_size, quot_size);

    if (log_mode == "DEBUG") {
        results_info  << req << ": " << std::setw(12) << req_res
        << "\tat line: " << std::setw(3) << line_counter
        << "    word: " << std::setw(2) << word_counter << std::endl;
    }

    // результат ниже порога
    // записываем его в дебаг и в релиз выводы
    if (req_res <= thresholds[req_type]) {

        results_info << "Possible mistake: " << "line: " << std::setw(3)
        << line_counter << ", word: " << std::setw(3)
        << word_counter << ": " << req << std::endl;
    }
    // запрос с двумя словами слева и справа
    // TODO or not?
}


void text_analyzer::analyze(logger &log) {
    // создаем его здесь, а не где-то в цикле, чтобы один раз инициализировать curl и пользоваться
    yandex_requester requester;

    // для последующей записи в лог. Накапливаем результаты в них, чтобы потом
    // записать в лог все Found, а потом все результаты запросов. Чтобы не вперемешку было, а последовательно
    stringstream results_info;
    stringstream found_info;

    string log_mode = log.get_severity();

    // читаем целиком строку из стрима, ведем учет количества строк
    string line;
    size_t line_counter = 0;
    while (getline(text_, line)) {
        ++line_counter;

        // из линии - стрим для считывания отдельных слов и подсчёта оных
        stringstream line_stream(line);


        string word;
        size_t word_counter = 0;
        vector<pair<string, size_t> > sentence;
        while (line_stream >> word) {

            // ". . ." - считаются как 3 отдельных слова, " - " - как 1 слово
            // Скорее всего надо будет уменьшать счётчик слов потом, когда будут оставаться пустые строки после удаления небуквенных символов
            ++word_counter;

            sentence.push_back(make_pair(word, word_counter));
            if (is_end(word)) {

                remove_side_chars(sentence[0].first);
                remove_side_chars(sentence[sentence.size() - 1].first);

                // пробегаем по вектору в поисках пустых строк
                for (size_t i = 0; i < sentence.size(); ++i) {
                    if (sentence[i].first.empty()) {

                        sentence.erase(sentence.begin() + i);
                        // Строка оказалась пустой после удаления небуквенных символов =>
                        // состояла только из них, ". . .", " - " - а это не слова => уменьшаем счётчик слов.

                        // i уменьшаем из-за реализции erase() со сдвигом итераторов. Смаль рассказывал
                        --i;
                        --word_counter;
                    }
                }

                // если вектор оказался пуст после удаления пустых строк
                // (состоял из одной строки, которая после чистки стала пустой ("."), а потом ее удалили),
                // надо его исключить из рассмотрения и продолжить
                if (sentence.empty()) {
                    continue;
                }

                // достаем из смысловой конструкции наборы слов - потенциальных предлогов
                for (size_t i = 0; i < sentence.size(); ++i) {

                    // слова для поиска в словаре - в вектор. Ищем от одного до 4х слов, конкатенируем
                    string possible_preposition;
                    size_t word_num = 0;
                    size_t j = i;
                    vector<pair<string, int> > possible_prepositions;
                    while (j <= sentence.size() - 1 && word_num < 4) {

                        // если слово - самое первое (word_num пока == 0), то пробел не вставляем
                        possible_preposition = (!word_num) ? sentence[j].first
                                                           : possible_preposition
                                                             + " "
                                                             + sentence[j].first;
                        ++word_num;
                        ++j;

                        // приводим запрос для поиска в словаре к lowercase
                        // имена и названия также пишутся с маленькой буквы, хорошо ли это?
                        // если всю линию сразу приводить к lowercase, то будет побыстрее, кажется
                        transform(possible_preposition.begin(), possible_preposition.end(),
                                  possible_preposition.begin(), ::tolower);

                        // формируем вектор из потенциальных предлогов длины <= 4 слова
                        // ищем сразу с большего кол-ва слов
                        possible_prepositions.push_back(make_pair(possible_preposition, word_num));
                    }

                    // ищем в словаре слова, начиная с максимального количества слов, т.е. с конца
                    // нашли максимально длинный предлог => break;
                    for (auto it = possible_prepositions.rbegin(); it != possible_prepositions.rend(); ++it) {

                        if (dictionary_.find(it->first)) {




                            // ПОЧЕМУ ВСЕ ЕДЕТ, ЕСЛИ КАВЫЧКУ ДОБАЛЯТЬ? "/' ???????????????????????????????????????????????????????????





                            // пишем в лог дебага список найденных предлогов
                            if (log_mode == "DEBUG") {

                                found_info << "Found" << std::setw(15) << it->first
                                << "   " << " at line: " << std::setw(5) << line_counter
                                << "    word: " << std::setw(5) << sentence[i].second << std::endl;
                            }

                            size_t len = it->second;

                            send_and_log_requests(sentence, i, len, requester,
                                                  line_counter, sentence[i].second,
                                                  results_info, log_mode);

                            //смещаемся в смысловой фразе на количество слов предлога,
                            // as far as - на три слова вправо и продолжаем искать после них
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


    // почему шаблонный оператор << не работает (undefined reference),
    // если определить его в logger.cpp, а не в logger.hpp??????????????????????????????????????????????????????????????
    if (log_mode == "DEBUG") {
        log << text_.str() << (string)"\n";
        log << found_info.str() << (string)"\n";
    }
    log << results_info.str();
}
