#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include "req_sender.h"
#include "xml_parser.h"



int main(int argc, char* argv[]) {

	req_sender rs;

	rs.send_request("hello");


	
    return 0;
}
