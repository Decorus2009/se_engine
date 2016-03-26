#include <iostream>
#include "xml_parser.hpp"

using std::string;

xml_parser::xml_parser() {}

static long long found_res_num = -1;
static bool found_docs_tag_found = false;
static string last_content;

/* first when start element is encountered */
void xml_parser::start_tag(void *data, const char *element, const char **attribute) {

	if (string(element) == "found-docs"
		&& string(attribute[0]) == "priority"
	 	&& string(attribute[1]) == "all") {

		found_docs_tag_found = true;
	}
}

void xml_parser::end_tag(void *data, const char *el) {

	if (found_docs_tag_found) {

		found_res_num = atoll(last_content.c_str());
		found_docs_tag_found = false;
	}
}

void xml_parser::handle_data(void *data, const char *content, int length) {

	if (found_docs_tag_found) {

		last_content = string(content);
	}
}

long long xml_parser::parse(string const &xml) {

	XML_Parser parser_ = XML_ParserCreate(NULL);


    XML_SetElementHandler(parser_, start_tag, end_tag);
    XML_SetCharacterDataHandler(parser_, handle_data);


    if (XML_Parse(parser_, xml.c_str(), xml.length(), XML_TRUE) == XML_STATUS_ERROR) {
		std::cout << "Error: " << XML_ErrorString(XML_GetErrorCode(parser_)) << std::endl;
    }

	XML_ParserFree(parser_);

	return found_res_num;
}
