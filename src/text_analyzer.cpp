#include "text_analyzer.hpp"
#include "yandex_requester.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using std::ifstream;
using std::string;

static int A_symb  = (int)'A';
static int Z_symb  = (int)'Z';
static int a_symb  = (int)'a';
static int z_symb  = (int)'z';
//static int apostrophe = (int)'\'';

using namespace std;


text_analyzer::text_analyzer(ifstream &text_file) : dictionary_() {

    text_ << text_file.rdbuf();
}

bool is_begin(std::string const &word) {
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
    return !( ((int)word[0] >= A_symb && (int)word[0] <= Z_symb) ||
              ((int)word[0] >= a_symb && (int)word[0] <= z_symb) );
}
bool is_end(std::string const &word) {

    // исключение закрывающейся кавычки - предлог o'
    // not yet implemented

    return !( ((int)word[word.length() - 1] >= A_symb && (int)word[word.length() - 1] <= Z_symb) ||
              ((int)word[word.length() - 1] >= a_symb && (int)word[word.length() - 1] <= z_symb) );
}
void remove_side_chars(std::string &word) {

    // удаление последнего символа пока он не буква и пока длина слова > 0
    while ( word.length() &&
            !(((int)word[word.length() - 1] >= A_symb && (int)word[word.length() - 1] <= Z_symb) ||
              ((int)word[word.length() - 1] >= a_symb && (int)word[word.length() - 1] <= z_symb)) ) {

        //cout << endl << "word: " << word << '\t' << word[word.length() - 1] << endl;
        word.erase(word.length() - 1, 1);
    }

    // удаление первого символа пока он не буква и пока длина слова > 0
    while ( word.length() &&
            !(((int)word[0] >= A_symb && (int)word[0] <= Z_symb) ||
              ((int)word[0] >= a_symb && (int)word[0] <= z_symb)) ) {

        word.erase(0, 1);
    }

}

// можно ради оптимизации попробовать возвращать ссылки
pair<string, string> build_left_right_requests(vector<pair<string, size_t> > const &sentence, size_t begin_ind, size_t len) {

    string left_request;
    string right_request;


    string preposition = sentence[begin_ind].first;
    // вновь формируем сам предлог, но уже с '+'
    for (size_t i = begin_ind + 1; i < begin_ind + len; ++i) {
        preposition = preposition + " " + sentence[i].first;
    }


    // заменить кавычки в запросе на &quot; - percent-encoding?????

    if (sentence.size() > 1) {

        // только правый запрос
        if (begin_ind == 0) {
            right_request = (string)"&quot;";
            right_request += preposition + " " + sentence[begin_ind + len].first;
            right_request += "&quot;";
            //cout << "RIGHT REQUEST: " << right_request << endl;
        }
        // только левый запрос
        else if (begin_ind + len == sentence.size()) {
            left_request = (string)"&quot;";
            left_request += sentence[begin_ind - 1].first + " " + preposition;
            left_request += "&quot;";
            //cout << "LEFT REQUEST: " << left_request << endl;
        }
        // оба запроса
        else {
            left_request = (string)"&quot;";
            left_request += sentence[begin_ind - 1].first + " " + preposition;
            left_request += "&quot;";

            right_request = (string)"&quot;";
            right_request += preposition + " " + sentence[begin_ind + len].first;
            right_request += "&quot;";
            //cout << "LEFT REQUEST: " << left_request << endl;
            //cout << "RIGHT REQUEST: " << right_request << endl;
        }
    }
    return make_pair(left_request, right_request);
}


void text_analyzer::analyze() {

    //string next_word;

    // создаем его здесь, а не где-то в цикле, чтобы один раз инициализировать curl и пользоваться
    yandex_requester requester;


    cout << text_.str() << endl;

    // читаем целиком строку из стрима, ведем учет количества строк
    string line;
    size_t line_counter = 0;
    while (getline(text_, line)) {
        ++line_counter;

        // cout << endl << "******************************************************" << endl << "*** LINE " << line_counter << " ***" << endl;
        // cout << line << endl << "******************************************************" << endl;

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
                if (sentence.empty()) { continue; }


                //cout << endl << "sentence is complete: " << endl; for (auto it : sentence) { cout << "(" << it.first << ", " << it.second << ")";} cout << endl;
                //cout << "SIZE: " << sentence.size() << ' '; for (auto it : sentence) { cout << it.first << " "; } cout << endl;

                // достаем из смысловой конструкции наборы слов - потенциальных предлогов
                for (size_t i = 0; i < sentence.size(); ++i) {

                    // слова для поиска в словаре - в вектор. Ищем от одного до 4х слов, конкатенируем
                    string possible_preposition;
                    size_t word_num = 0;
                    size_t j = i;
                    vector<pair<string, int> > possible_prepositions;
                    while (j <= sentence.size() - 1 && word_num < 4) {

                        // если слово - самое первое (word_num пока == 0), то пробел не вставляем
                        possible_preposition = (!word_num) ? sentence[j].first : possible_preposition + " " + sentence[j].first;
                        ++word_num;
                        ++j;

                        // приводим запрос для поиска в словаре к lowercase
                        // имена и названия также пишутся с маленькой буквы, хорошо ли это?
                        // если всю линию сразу приводить к lowercase, то будет побыстрее, кажется
                        transform(possible_preposition.begin(), possible_preposition.end(), possible_preposition.begin(), ::tolower);
                        // формируем вектор из потенциальных предлогов длины <= 4 слова
                        // ищем сразу с большего кол-ва слов
                        possible_prepositions.push_back(make_pair(possible_preposition, word_num));
                    }

                    // ищем в словаре слова, начиная с максимального количества слов, т.е. с конца
                    // нашли максимально длинный предлог => break;
                    for (auto it = possible_prepositions.rbegin(); it != possible_prepositions.rend(); ++it) {

//                        cout << it->first << ' ' << it->second << endl;
                        if (dictionary_.find(it->first)) {

                            cout << "Found" << setw(20) << it->first << "   " <<
                            " at line: " << setw(5) << line_counter << ",    word: " << setw(5) << sentence[i].second << endl;


                            // формирование запроса
                            auto left_right_requests = build_left_right_requests(sentence, i, it->second);

                                //посылка запросов:
                            if (!left_right_requests.first.empty()) {
                                cout << "LEFT REQUEST: " << left_right_requests.first << "\t" << requester.send_request(left_right_requests.first) << endl;
                            }
                            if (!left_right_requests.second.empty()) {
                                cout << "RIGHT REQUEST: " << left_right_requests.second << "\t" << requester.send_request(left_right_requests.second) << endl;
                            }

                            //смещаемся в смысловой фразе на количество слов предлога,
                            // as far as - на три слова вправо и продолжаем искать после них
                            i += it->second - 1;
                            possible_prepositions.clear();
                            break;

                        }
                    }
                }

                sentence.clear();
                //continue;
            }
        }
        //cout << line_counter << ": " << word_counter << endl;
    }
}
