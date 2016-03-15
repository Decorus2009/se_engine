#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include "xml_parser.h"

using std::string;
using std::cout;
using std::endl;

/* track the current level in the xml tree */
size_t depth = 0;
long long found = -1;
string last_content;
bool found_docs_tag_found = false;

/* first when start element is encountered */
void xml_parser::start_tag(void *data, const char *element, const char **attribute) {

	if (string(element) == "found-docs"
		&& string(attribute[0]) == "priority"  
	 	&& string(attribute[1]) == "all") {

		found_docs_tag_found = true;
	}
	++depth; 
}

/* decrement the current level of the tree */
void xml_parser::end_tag(void *data, const char *el) { 

	if (found_docs_tag_found) {

		found = atoll(last_content.c_str());
		found_docs_tag_found = false;
	}
	--depth;
}

void xml_parser::handle_data(void *data, const char *content, int length) {

	if (found_docs_tag_found) {

		last_content = string(content);
	}
}

long long xml_parser::parse(std::stringstream &xml_content_stream) {

    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_tag, end_tag);
	XML_SetCharacterDataHandler(parser, handle_data);
    

	string buffer = xml_content_stream.str();

    if (XML_Parse(parser, buffer.c_str(), buffer.length(), XML_TRUE) == XML_STATUS_ERROR) {
		cout << "Error: " << XML_ErrorString(XML_GetErrorCode(parser));
    }

    XML_ParserFree(parser);

	cout << endl << endl << "foundULT: " << found << endl;

	return found;
}
