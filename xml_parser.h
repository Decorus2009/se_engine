#ifndef XML_PARSER_H
#define XML_PARSER_H

//перенесети ненужные хидеры в cpp
#include <stdio.h>
#include <expat.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <sstream>

//разделить методы на приватные и публичные
struct xml_parser {
public:
	static void start_tag(void *data, const char *element, const char **attribute);
	static void end_tag(void *data, const char *el);
	static void handle_data(void *data, const char *content, int length);
	static int xml_parse(std::stringstream &xml_content_stream);
private:

	xml_parser(xml_parser const &);
	xml_parser &operator=(xml_parser const &);
};
#endif
