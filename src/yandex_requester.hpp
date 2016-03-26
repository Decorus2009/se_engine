#ifndef YANDEX_REQUESTER_HPP
#define YANDEX_REQUESTER_HPP

#include "request_sender.hpp"
#include "xml_parser.hpp"

struct yandex_requester {

private:

	xml_parser parser_;
	request_sender sender_;

public:

	yandex_requester();
	yandex_requester(yandex_requester const &) = delete;
	yandex_requester &operator=(yandex_requester const &) = delete;

	long long send_request(std::string const &req_str);
};


#endif
