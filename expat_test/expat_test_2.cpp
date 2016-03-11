#include <stdio.h>
#include <expat.h>
#include <string>
#include <iostream>

#define BUFFSIZE 1024	
char Buff[BUFFSIZE];
int depth;
XML_Parser first;
std::string tmp_str;

static void XMLCALL start(void *user_data, const char *tag, const char **attr)
{
    int i;
    for (i = 0; i < depth; i++) {
		printf("\t");
	}	
    
	printf("tag = %s", tag);

    for (i = 0; attr[i]; i += 2) {
		printf(" : attrib %s='%s'\n", attr[i], attr[i + 1]);
    }
	
	tmp_str = std::string(tag);	
	//std::cout << "TMP_STR: " << tmp_str << std::endl;
    ++depth;
}

static void XMLCALL end(void *userdata, const char *tag) { --depth; }


void text_handler(void *data, const char *txt, int txtlen) {

	if (tmp_str == "found") {

	  	printf("\n%4d: Text - ", depth++);
	  	fwrite(txt, txtlen, sizeof(char), stdout);
	}	
}

int main (void) {
	
	FILE * f = fopen("simple_xml_test.xml", "r");
    int done, len;
    first = XML_ParserCreate(NULL);
    XML_SetElementHandler(first, start, end);
	XML_SetCharacterDataHandler(first, text_handler);
    
	do {
		len = fread(Buff, 1, BUFFSIZE, f);
		done = feof(f);
		XML_Parse(first, Buff, len, done);
    } 
	while (!done);
    
	XML_ParserFree(first);
    return 0;
}
