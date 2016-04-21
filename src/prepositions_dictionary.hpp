#ifndef PREPOSITIONS_DICTIONARY_HPP
#define PREPOSITIONS_DICTIONARY_HPP

#include <map>
#include <string>
#include <fstream>

/*
* Метаинформация:
* (тип 0/1 (устар/норм)) (0 - archaic poetic rare) =>
* map <string, bool>
*
* Замечания: наверное, не надо учитывать предлоги a и an (в смысле per).
* Будут пересекаться с артиклями, много лишних запросов.

 * Надо навести статистику для определения порогов. Каждый предлог соответствующего типа отправить в Я,
* получить возвращенное число ответов, и сформировать пороговое значение для каждого предлога

* надо будет сопоставить возвращенное число с установленными мной типами (1 или 0)
* Также, например, предлог ablow - находит какого-то чувака
*
* again, gain - устар от against. Для них порог должен быть маленький, но поиск будет работать некорректно, найдет много.
*/

struct prepositions_dictionary {

public:
    prepositions_dictionary();

    bool find(std::string const &word);

    prepositions_dictionary(prepositions_dictionary const &) = delete;
    prepositions_dictionary &operator=(prepositions_dictionary const &) = delete;

private:
    std::map<std::string, bool> dictionary_;
};

#endif
