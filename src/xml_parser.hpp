#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include <string>
#include <expat.h>

struct xml_parser {

private:

	static void start_tag(void *data, const char *element, const char **attribute);
	static void end_tag(void *data, const char *el);
	static void handle_data(void *data, const char *content, int length);

public:

	//приходится его объявить
	xml_parser();
	xml_parser(xml_parser const &) = delete;
	xml_parser &operator=(xml_parser const &) = delete;

	static long long parse(std::string const &xml);
};
#endif
