#ifndef REQUEST_SENDER_HPP
#define REQUEST_SENDER_HPP

#include <string>
#include <curl/curl.h>

//  класс нужно использовать так
// request_sender se; вся инициализация должна быть в конструкторе
// se.do("vasya");
// se.do("petya");
struct request_sender {

private:

    std::string yand_addr_;
    std::string user_;
    std::string api_key_;
    std::string filter_;
    std::string l10n_;

	//std::string showmecaptcha_;
    std::string xml_encode_type_;
    std::string req_header_;
    std::string query_;
    std::string sortby_;
    std::string maxpassages_;
    std::string page_;
    std::string groupby_;

	std::string url_;
    std::string request_;

	CURL *curl_;

	static size_t write_response_data(char *ptr, size_t size, size_t nmemb, void *userdata);

public:

    request_sender();
	~request_sender();
    request_sender(request_sender const &) = delete;
    request_sender &operator=(request_sender const &) = delete;

    std::string send_curl_request(std::string const &req_str);
};


#endif
