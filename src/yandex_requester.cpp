#include "yandex_requester.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

using std::string;
using std::stringstream;

yandex_requester::yandex_requester() {}

long long yandex_requester::send_request(std::string const &req_str)
{
    yandex_request_sender ya_req_sen_tmp;
    string xml = ya_req_sen_tmp.send_curl_request(req_str);

    std::ofstream xml_file("xml_resp.xml");
    xml_file << xml;

    if (xml.find("Sorry, there are no results for this search") != string::npos ||
        xml.find("Request limit reached") != string::npos ||
        xml.find("list of permitted IP addresses") != string::npos)
    {
        return 0;
    }

    return yandex_xml_parser::parse(xml);
}


static long long found_res_num = 0;
static bool found_docs_tag_found = false;
static string last_content;

yandex_requester::yandex_xml_parser::yandex_xml_parser() {}

void yandex_requester::
yandex_xml_parser::start_tag(void *data, const char *element, const char **attribute)
{
    if (string(element) == "found-docs" &&
        string(attribute[0]) == "priority" &&
        string(attribute[1]) == "all")
    {
        found_docs_tag_found = true;
    }
}

void yandex_requester::yandex_xml_parser::end_tag(void *data, const char *el)
{
    if (found_docs_tag_found)
    {
        found_res_num = atoll(last_content.c_str());
        found_docs_tag_found = false;
    }
}

void yandex_requester::
yandex_xml_parser::handle_data(void *data, const char *content, int length)
{
    if (found_docs_tag_found)
    {
        last_content = string(content);
    }
}

long long yandex_requester::yandex_xml_parser::parse(std::string const &xml)
{
    XML_Parser parser_ = XML_ParserCreate(NULL);

    XML_SetElementHandler(parser_, start_tag, end_tag);
    XML_SetCharacterDataHandler(parser_, handle_data);

    if (XML_Parse(parser_, xml.c_str(), xml.length(), XML_TRUE) == XML_STATUS_ERROR)
    {
        std::cerr << "Error: " << XML_ErrorString(XML_GetErrorCode(parser_)) << std::endl;
    }

    XML_ParserFree(parser_);

    return found_res_num;
}


// yandex_request_sender
yandex_requester::yandex_request_sender::yandex_request_sender()
{
    curl_ = curl_easy_init();

    curl_easy_setopt(curl_, CURLOPT_POST, 1);
    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);
//    curl_easy_setopt(curl_, CURLOPT_VERBOSE, 1);
}

yandex_requester::yandex_request_sender::~yandex_request_sender()
{
    curl_easy_cleanup(curl_);
}

size_t yandex_requester::
yandex_request_sender::write_response_data(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    stringstream* s = (stringstream *)userdata;
    size_t n = size * nmemb;
    s->write(ptr, n);

    return n;
}

string yandex_requester::yandex_request_sender::send_curl_request(std::string const &query)
{
    //showmecaptcha_ = "yes";                                                    //попытка отключения автоисправления поиска
    string url_ = ya_addr_ + "user=" + user_ + "&key=" + api_key_ + "&l10n=en&filter=moderate" + "&noreask=1";

    string request = (string)"<?xml version=\"1.0\" encoding=\"UTF-8\"?><request><query>" + "&quot;" + query + "&quot;" +
                     "</query><sortby>rlv</sortby><maxpassages>1</maxpassages><page>0</page>" +
                     "<groupings><groupby attr=\"d\" mode=\"deep\" groups-on-page=\"1\" docs-in-group=\"1\" /></groupings></request>";


    curl_easy_setopt(curl_, CURLOPT_URL, url_.c_str());
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, request.c_str());

    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &yandex_request_sender::write_response_data);

    stringstream xml_stream;
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &xml_stream);

//    CURLcode code = curl_easy_perform(curl_);
    curl_easy_perform(curl_);

    return xml_stream.str();
}
