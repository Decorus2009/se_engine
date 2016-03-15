#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include "req_sender.h"



int main(int argc, char* argv[]) {

	req_sender rs;

	rs.send_request("hello");


	
    return 0;
}
