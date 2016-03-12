#include "xml_parser.h"
using std::cout;
using std::endl;

/* track the current level in the xml tree */
static int depth = 0;
//static char *last_content;
static std::string last_content;

static int RES = -1;

static bool found_docs_tag_found = false;

/* first when start element is encountered */
void xml_parser::start_tag(void *data, const char *element, const char **attribute) {

	if (std::string(element) == "found-docs"
		&& std::string(attribute[0]) == "priority"  
	 	&& std::string(attribute[1]) == "all") {

		found_docs_tag_found = true;
	}

	++depth;
}

/* decrement the current level of the tree */
void xml_parser::end_tag(void *data, const char *el) { 


	if (found_docs_tag_found) {
//CAN'T USE STOI!
//		int res = stoi(last_content);
		RES = atoi(last_content.c_str());
		found_docs_tag_found = false;
	}
	--depth;
}

void xml_parser::handle_data(void *data, const char *content, int length) {

	if (found_docs_tag_found) {
		char *tmp = new char[length + 1];
		strncpy(tmp, content, length);
		tmp[length] = '\0';
		data = (void *) tmp;
		last_content = tmp;    
		delete [] tmp;     

		//found_docs_tag_found = false;
	}
//???
/*
	std::string tmp = content;
	data = (void *)tmp.c_str();
	last_content = tmp;
*/
}

int xml_parser::xml_parse(std::stringstream &xml_content_stream) {

	//может, имеет смысл использовать буфер небольшого размера, чтобы хватило дойти до found-docs, а дальше уже парсить не надо.

	//размер xml_content_stream
	xml_content_stream.seekg(0, std::ios::end);
//	size_t size_of_xml_content_stream = xml_content_stream.tellg();
//	std::cout << "size_of_xml_content_stream " << size_of_xml_content_stream << " bytes" << std::endl << std::endl;

	size_t buff_size = 4096;
	//char buff[buff_size];
	char *buff = new char[buff_size];	
	memset(buff, 0, buff_size);


    FILE *xml_file = fopen("outf.xml", "r");
    if(xml_file == NULL) { printf("Failed to open file\n"); return 1; }


	//cout << xml_content_stream.str();
	//xml_content_stream.read(buff, buff_size);
	buff[buff_size] = '\0';
	fread(buff, sizeof(char), buff_size, xml_file);

//	cout << "BUFFER: " << endl;
//	for (int i = 0; i < buff_size; ++i) cout << buff[i];

    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_tag, end_tag);
	XML_SetCharacterDataHandler(parser, handle_data);
    
	/* parse the xml */
    if(XML_Parse(parser, buff, strlen(buff), XML_TRUE) == XML_STATUS_ERROR) {
		cout << "Error: " << XML_ErrorString(XML_GetErrorCode(parser));
    }

    fclose(xml_file);
    XML_ParserFree(parser);

	cout << endl << endl << "RESULT: " << RES << endl;
	cout << endl << endl << "RESULT: " << atoi(last_content.c_str()) << endl;

	return 0;

}
