#include "Yandex_requester.h"

Yandex_requester::Yandex_requester() {}

long long Yandex_requester::send_request(string const &req_str) {

    std::string xml = sender_.send_curl_request(req_str);
    return parser_.parse(xml);
}
