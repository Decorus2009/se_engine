#ifndef REQ_SENDER_H
#define REQ_SENDER_H

#include <string>
#include <curl/curl.h>

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

	static size_t write_response_data(char *ptr, size_t size, size_t nmemb, void *userdata);

public:

    req_sender();
	~req_sender();

	string send_curl_request(string const &req_str);
};


#endif 


