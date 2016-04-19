#ifndef YANDEX_REQUESTER_HPP
#define YANDEX_REQUESTER_HPP

#include <string>
#include <expat.h>
#include <curl/curl.h>

struct yandex_requester {

public:

    yandex_requester();
    long long send_request(std::string const &req_str);

    yandex_requester(yandex_requester const &) = delete;
    yandex_requester &operator=(yandex_requester const &) = delete;
private:

    struct yandex_xml_parser {

    public:

        //приходится его объявить
        yandex_xml_parser();
        yandex_xml_parser(yandex_xml_parser const &) = delete;
        yandex_xml_parser &operator=(yandex_xml_parser const &) = delete;

        static long long parse(std::string const &xml);

    private:

        static void start_tag(void *data, const char *element, const char **attribute);
        static void end_tag(void *data, const char *el);
        static void handle_data(void *data, const char *content, int length);
    };

    struct yandex_request_sender {

    public:

        yandex_request_sender();
        ~yandex_request_sender();
        yandex_request_sender(yandex_request_sender const &) = delete;
        yandex_request_sender &operator=(yandex_request_sender const &) = delete;

        std::string send_curl_request(std::string const &req_str);

    private:

        std::string yand_addr_, user_, api_key_, filter_, l10n_,
                    xml_encode_type_, req_header_, query_, sortby_,
                    maxpassages_, page_, groupby_, url_, request_;
        //std::string showmecaptcha_;

        CURL *curl_;

        static size_t write_response_data(char *ptr, size_t size, size_t nmemb, void *userdata);
    };
};

#endif
