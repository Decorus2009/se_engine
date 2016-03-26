#include "yandex_requester.hpp"

yandex_requester::yandex_requester() {}

long long yandex_requester::send_request(std::string const &req_str) {

    std::string xml = sender_.send_curl_request(req_str);
    return parser_.parse(xml);
}
