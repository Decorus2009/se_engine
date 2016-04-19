#include "yandex_requester.hpp"
#include <iostream>
#include <sstream>

using std::string;
using std::stringstream;

yandex_requester::yandex_requester() {}

long long yandex_requester::send_request(std::string const &req_str) {

    yandex_request_sender ya_req_sen_tmp;
    string xml = ya_req_sen_tmp.send_curl_request(req_str);
    return yandex_xml_parser::parse(xml);
}


// yandex_xml_parser
static long long found_res_num = -1;
static bool found_docs_tag_found = false;
static string last_content;

yandex_requester::yandex_xml_parser::yandex_xml_parser() {}

void yandex_requester::yandex_xml_parser::start_tag(void *data, const char *element,
                                                    const char **attribute) {

    if (string(element) == "found-docs"
        && string(attribute[0]) == "priority"
        && string(attribute[1]) == "all") {

        found_docs_tag_found = true;
    }
}

void yandex_requester::yandex_xml_parser::end_tag(void *data, const char *el) {

    if (found_docs_tag_found) {

        found_res_num = atoll(last_content.c_str());
        found_docs_tag_found = false;
    }
}

void yandex_requester::yandex_xml_parser::handle_data(void *data, const char *content, int length) {

    if (found_docs_tag_found) {

        last_content = string(content);
    }
}

long long yandex_requester::yandex_xml_parser::parse(std::string const &xml) {
    XML_Parser parser_ = XML_ParserCreate(NULL);

    XML_SetElementHandler(parser_, start_tag, end_tag);
    XML_SetCharacterDataHandler(parser_, handle_data);

    if (XML_Parse(parser_, xml.c_str(), xml.length(), XML_TRUE) == XML_STATUS_ERROR) {
        std::cerr << "Error: " << XML_ErrorString(XML_GetErrorCode(parser_)) << std::endl;
    }

    XML_ParserFree(parser_);

    return found_res_num;
}


// yandex_request_sender
yandex_requester::yandex_request_sender::yandex_request_sender() {

    curl_ = curl_easy_init();

    //request a HTTP POST
    curl_easy_setopt(curl_, CURLOPT_POST, 1);
    //для работы через https
    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);
    //подробная информация
//    curl_easy_setopt(curl_, CURLOPT_VERBOSE, 1);
}

yandex_requester::yandex_request_sender::~yandex_request_sender() {
    curl_easy_cleanup(curl_);
}

size_t yandex_requester::yandex_request_sender::write_response_data(char *ptr, size_t size,
                                                                    size_t nmemb, void *userdata) {

    stringstream* s = (stringstream *)userdata;
    size_t n = size * nmemb;
    s->write(ptr, n);
    return n;
}

string yandex_requester::yandex_request_sender::send_curl_request(std::string const &req_str) {

    query_ = req_str;
    yand_addr_ = "https://yandex.com/search/xml?";
    user_ = "decorus2009";
    api_key_ = "03.88707539:10c39ba1ba0ca5ad3a32a1f9387d0da2";
    l10n_ = "en";
    filter_ = "moderate";
    //showmecaptcha_ = "yes";

    url_ = yand_addr_ + "user=" + user_ + "&key=" + api_key_ +
           "&l10n=" + l10n_ + "&filter=" + filter_;


    //надо сделать поддержку percent-encoding

    xml_encode_type_ = "UTF-8";


    req_header_ = (string)"<?xml version=" + "\"" + "1.0" + "\"" +
                  " encoding=" + "\"" + xml_encode_type_ + "\"" + "?>";

    sortby_ = "rlv";
    maxpassages_ = "2";
    page_ = "0";

    groupby_ = (string)"attr=" + "\"" + "d" + "\"" +
               " mode=" + "\"" + "deep" +
               "\"" + " groups-on-page=" + "\"" +
               "10" + "\"" + " docs-in-group=" +
               "\"" + "3" + "\"";

    request_ = req_header_ + "<request>" + "<query>" + query_ +
               "</query>" + "<sortby>" + sortby_ + "</sortby>" +
               "<maxpassages>" + maxpassages_ + "</maxpassages>" + "<page>" +
               page_ + "</page>" + "<groupings>" + "<groupby " +
               groupby_ + " />" + "</groupings>" + "</request>";



    //подробная информация
    curl_easy_setopt(curl_, CURLOPT_URL, url_.c_str());
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, request_.c_str());

    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &yandex_request_sender::write_response_data);

    stringstream xml_stream;
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &xml_stream);

//    CURLcode code = curl_easy_perform(curl_);
    curl_easy_perform(curl_);

    return xml_stream.str();
}
