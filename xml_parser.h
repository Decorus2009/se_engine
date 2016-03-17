#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <string>
#include <expat.h>

struct xml_parser {

private:

//	static XML_Parser parser_;

	static void start_tag(void *data, const char *element, const char **attribute);
	static void end_tag(void *data, const char *el);
	static void handle_data(void *data, const char *content, int length);

	xml_parser(xml_parser const &);
	xml_parser &operator=(xml_parser const &);

public:

	//приходится его объявить
	xml_parser();
	static long long parse(std::string const &xml);

};
#endif
