#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <expat.h>
#include <sstream>

struct xml_parser {

private:

	static void start_tag(void *data, const char *element, const char **attribute);
	static void end_tag(void *data, const char *el);
	static void handle_data(void *data, const char *content, int length);

	xml_parser(xml_parser const &);
	xml_parser &operator=(xml_parser const &);

public:

	static long long parse(std::stringstream &xml_content_stream);

};
#endif
