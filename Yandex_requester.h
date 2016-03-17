#ifndef YANDEX_REQUESTER
#define YANDEX_REQUESTER

#include "req_sender.h"
#include "xml_parser.h"

struct Yandex_requester {

private: 

	xml_parser parser_;
	req_sender sender_;	

	Yandex_requester(Yandex_requester const &);
	Yandex_requester &operator=(Yandex_requester const &);

public: 
	
	Yandex_requester();

	long long send_request(string const &req_str);
};


#endif
