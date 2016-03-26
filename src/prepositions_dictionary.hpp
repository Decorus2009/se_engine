#ifndef PREPOSITIONS_DICTIONARY_HPP
#define PREPOSITIONS_DICTIONARY_HPP

#include <map>
#include <set>
#include <string>
#include <vector>

/*
* Single word
* Two words
* Three words
* Preposition + (article) + noun + preposition ()
* Archaic
* Postposition (1 слово, некоторые слова пересекаются с предлогами, 1 слово - устар)
*z
* Метаинформация:
* (тип 0/1 (устар/норм)) (0 - archaic poetic rare) =>
* map <string, bool>
*
* Замечания: наверное, не надо учитывать предлоги a и an (в смысле per).
* Будут пересекаться с артиклями, много лишних запросов.
* Preposition + (article) + noun + preposition - есть несколько предлогов из 4 слов (из-за артиклей):
* at the behest of, for the sake of, with a view to
* Так что, скорее всего, придется искать по 4м словам, а не по 3м.
*
* Надо навести статистику для определения порогов. Каждый предлог соответствующего типа отправить в Я,
* получить возвращенное число ответов, и сформировать пороговое значение для каждого предлога
* МБ стоит посылать Я такой запрос: <preposition "какой-то предлог">.
* !!!Для проверки
* (слишком много предлогов типа cross (archaic) - пересекается с существительным =>
* будет некорректное число запросов; Scotland, poetic, rare и тд)
* надо будет сопоставить возвращенное число с установленными мной типами (1 или 0)
* Также, например, предлог ablow - находит какого-то чувака
* Когда будем искать предлог+слово (слева или справа) надо будет учесть то, что словом может оказаться the или a (an)
* => надо в запрос вставлять и артикль и следующее слово
*
* again, gain - устар от against. Для них порог должен быть маленький, но поиск будет работать некорректно, найдет много.
*
*
*
*
*
*/

struct prepositions_dictionary {

private:
	std::map <std::string, bool> dictionary_;



public:
	prepositions_dictionary();
	prepositions_dictionary(prepositions_dictionary const &) = delete;
	prepositions_dictionary &operator=(prepositions_dictionary const &) = delete;

	void print();
	std::map <std::string, bool> const &get_dictionary();
};

#endif
