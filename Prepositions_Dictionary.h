#ifndef PREPOSITIONS_DICTIONARY
#define PREPOSITIONS_DICTIONARY

#include <map>
#include <set>
#include <string>


// std::map <char, std::set <std::string, set_cmp> > dictionary_ -
// словарь, чар - первая буква слова, set <string> - упорядоченный специальным образом (set_cmp) сет строк, начинающихся с этой буквы, 
// различной длины (предлоги могут состоять из 2 и 3х слов. 
// Например, as и as far as --> надо как-то правильно парсить текст с учетом этого) --> идея :  
// set упорядочивается по невозрастанию длины предлога и в тексте сразу ищется самый длинный предлог
// (т.е., сразу ищем as far as (если, конечно он есть), а не просто as). Итого, ищем предлог в полной его форме, а не часть его.


// Также нужен учет устаревших предлогов, для них порог ниже

struct Prepositions_Dictionary {

private:

	struct set_cmp {

		bool operator()(std::string const &s1, std::string const &s2) { 
			return s1.length() >= s2.length(); 
		}
	};

	std::map <char, std::set <std::string, set_cmp> > dictionary_;

	Prepositions_Dictionary(Prepositions_Dictionary const &);
	Prepositions_Dictionary &operator=(Prepositions_Dictionary const &);

public:
	
	Prepositions_Dictionary();
	void print();
};

#endif

