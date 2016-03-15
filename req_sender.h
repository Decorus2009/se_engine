#ifndef REQ_SENDER_H
#define REQ_SENDER_H

#include <string>
#include <iostream>
#include <curl/curl.h>
#include <sstream>
#include <string>

using std::string;
//  класс нужно использовать так
// req_sender se; вся инициализация должна быть в конструкторе
// se.do("vasya");
// se.do("petya");
struct req_sender {

private:

    req_sender(req_sender const &);
    req_sender &operator=(req_sender const &);

    string yand_addr_;
    string user_;
    string api_key_;
    string filter_;
    string l10n_;
    
	//string showmecaptcha_;
    string xml_encode_type_;
    string req_header_;
    string query_;
    string sortby_;
    string maxpassages_;
    string page_;
    string groupby_;

	string url_;
    string request_;

	CURL *curl_;

	size_t write_response_data(char *ptr, size_t size, size_t nmemb, void *userdata);

public:

    req_sender();
	~req_sender();

    inline string get_url() const { return url_; }
    inline string get_request() const { return request_; }

	void send_request(string const &req_str);
};


#endif //req_sender_H


