#ifndef PREPOSITIONS_DICTIONARY
#define PREPOSITIONS_DICTIONARY

#include <map>
#include <string>

using std::multimap;
using std::string;

struct Prepositions_Dictionary {

private:

	multimap <char, string> single_words_;
	multimap <char, string> two_words_;
	multimap <char, string> three_words_;
	multimap <char, string> preposition_noun_preposition_;
	multimap <char, string> archaic_dialectal_;
	multimap <char, string> postpositions_;

	Prepositions_Dictionary(Prepositions_Dictionary const &);
	Prepositions_Dictionary &operator=(Prepositions_Dictionary const &);

public:
	
	Prepositions_Dictionary();
	void print(multimap<char, string> mm); 
	void print_all();
};

#endif

