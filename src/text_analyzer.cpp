#include "text_analyzer.hpp"
#include "yandex_requester.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using std::ifstream;
using std::string;

using namespace std;
text_analyzer::text_analyzer(ifstream &text_file) : dictionary_() {
    text_ << text_file.rdbuf();
}

// ищем по 4 слова, т.к. встречаются предлоги из 4х слов.
// надо для каждого search_word_i обрезать конец или начало, если там стоит:
// ’ ' [ ] ( ) { } ⟨ ⟩ : , ‒ – – – … ... . . . ! . ‐ - ? „ “ « » “ ” ‘ ’ ‹ › ; и тд
// проще просто проверить что первый и последний символ в строке именно буква, т.е. принадлежит диапазону кодов букв.

// возможный баг - предлог 'long. Вполне может быть частью фразы в кавычках, которая начинается с long
// если первый символ у слова " - то как быть. По идее тут начинается фраза, даже, если в ней первым стоит предлог.
// Нет смысла искать со словом левее?
// как-то надо разделить. Если в конце слова стоит что-то вроде : то надо искать только со словом левее и тд.
// аналогочино, если в конце слова стоит, например, ?, то скорее всего предложение закончено, слово правее брать бессмысленно
// и как быть с символом многоточия? Его в аски нет

// Исключение - предлоги, начинающиеся на ' и предлоги "c., ca. (от circa), o'(от of), vs., v., w/ (от with)"
// их свойство - они все состоят из одного слова (пока их не рассматриваем).



// ATTENTION: можно все слова просто сложить в вектор, но тогда увеличится память и затрутся пробелы и переносы строки
// зато легко собирать из него слова

void text_analyzer::analyze() {
    cout << "TEXT: " << endl << text_.str() << endl << endl;




    // отдельно надо проверить работу на текстах с меньшим количеством слов
    vector<string> search_words;
    vector<string> reserve_words;
    // max число слов в предлоге 4
    const int max_words_num = 4;
    string next_word;

    text_ >> next_word;
    do {
        reserve_words.push_back(next_word);
    }
    //проверка идет именно в таком порядке, иначе next_word считывается лишний раз
    while (reserve_words.size() < max_words_num && text_ >> next_word);

    int cur_words_num = reserve_words.size();
    search_words.resize(cur_words_num);

    search_words[0] = reserve_words[0];
    for (int i = 0; i < cur_words_num - 1; ++i) {
        search_words[i + 1] = search_words[i] + " " + reserve_words[i + 1];
    }

    pair<bool, bool> bounds_status;
    auto prep_dict = dictionary_.get_dictionary();

    // тут рассматриваем только первые 4 слова, ост - в while
    for (int i = cur_words_num - 1; i >= 0; --i) {

        // поиск слов в словаре
        bounds_status = check_word_bounds(search_words[i]);
        if (prep_dict.find(search_words[i]) != prep_dict.end()) {

            cout << endl << endl << search_words[i] << " FOUND!!!!!" << endl << endl;

            // что-то удалили у слова поиска с обоих концов
            if (!bounds_status.first && !bounds_status.second) {
            }
            // что-то удалили у слова поиска с правого конца
            else if (bounds_status.first && !bounds_status.second) {
            }
            // что-то удалили у слова поиска с левого конца
            else if (!bounds_status.first && bounds_status.second) {
            }
            // слово поиска не менялось, искать можно, добавляя слова с обоих концов
            else {
            }

            // если находимся в самом начале текста => берем для поиска только слово правее
            string add_right_word_request;
            // если заюзали все 4 слова для поиска - берем следующее слово, которого нет в reserve_words
            if (i == cur_words_num - 1) {
                add_right_word_request = search_words[i] + " " + next_word;
            }
            else {
                add_right_word_request = search_words[i] + " " + reserve_words[i + 1];
            }

            cout << "ADD_LEFT_WORD_REQUEST " << add_right_word_request << endl;

            break;
        }
    }





    // Если слово, которое прибавляем к поиску - артикль the a an - мб имеет смысл добавить следующее слово


    size_t circle_counter = 0;
    while (text_ >> next_word) {


        for (int i = 0; i < cur_words_num - 1; ++i) {
            reserve_words[i] = reserve_words[i + 1];
        }
        reserve_words[cur_words_num - 1] = next_word;

        search_words[0] = reserve_words[0];
        for (int i = 0; i < cur_words_num - 1; ++i) {
            search_words[i + 1] = search_words[i] + " " + reserve_words[i + 1];
        }

        for (int i = cur_words_num - 1; i >= 0; --i) {
            cout << search_words[i] << endl;
        }
        cout << endl;

        for (int i = 0; i < cur_words_num; ++i)
            bounds_status = check_word_bounds(search_words[i]);


        for (int i = cur_words_num - 1; i >= 0; --i) {
            cout << search_words[i] << endl;
        }

        // for (auto it = search_words.rbegin(); it != search_words.rend(); ++it) {
        //     cout << *it << endl;
        // }
        // for (int i  = 0; i < cur_words_num; ++i) {
        //     pair<bool, bool> p = check_word_bounds(search_words[cur_words_num - 1 - i]);
        //     cout << p.first << ' ' << p.second << endl;
        // }
        // for (auto it = search_words.rbegin(); it != search_words.rend(); ++it) {
        //     cout << *it << endl;
        // }
        ++circle_counter;
    }

}



// возвращает пару булов: с какой стороны слова был удален лишний символ (, . " и тд)
std::pair<bool, bool> text_analyzer::check_word_bounds(string &word) {

    int A_symbol_code = (int)'A';
    int Z_symbol_code = (int)'Z';
    int a_symbol_code = (int)'a';
    int z_symbol_code = (int)'z';
    int apostrophe    = (int)'\'';

    bool first_symbol_erased = false;
    bool last_symbol_erased  = false;

    int checks_num = 2;
    // пускаем чек два раза, чтобы учесть ситуации типа 'Where is he, anyway?' (?' -> (после одного раза ?))
    // немного несогласованно получается при возврате пары булов, они перезаписываются.
    for (int i = 0; i < checks_num; ++i) {

        int word_first_symbol = (int)word[0];
        int word_last_symbol  = (int)word[word.length() - 1];

        // начальный символ - буква или апостроф (для 'gainst 'neath 'bout и тд)
        if ( (word_first_symbol >= A_symbol_code && word_first_symbol <= Z_symbol_code) ||
             (word_first_symbol >= a_symbol_code && word_first_symbol <= z_symbol_code) ||
              word_first_symbol == apostrophe ) {

            first_symbol_erased = false;
        }
        // иначе - надо удалить первый символ + ищем со словом правее (кавычки, например)
        else {
            word.erase(0, 1);
            first_symbol_erased = true;
        }

        // конечный символ - буква
        if ( (word_last_symbol >= A_symbol_code && word_last_symbol <= Z_symbol_code) ||
             (word_last_symbol >= a_symbol_code && word_last_symbol <= z_symbol_code) ) {

            last_symbol_erased = false;
        }
        else {
            word.erase(word.length() - 1, 1);
            last_symbol_erased = true;
        }
    }

    return make_pair(first_symbol_erased, last_symbol_erased);
}
