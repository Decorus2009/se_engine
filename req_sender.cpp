#include "req_sender.h"
#include <sstream>

req_sender::req_sender() {

	curl_ = curl_easy_init();

    //request a HTTP POST
    curl_easy_setopt(curl_, CURLOPT_POST, 1);
	//для работы через https
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L); 
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);
	//подробная информация
//    curl_easy_setopt(curl_, CURLOPT_VERBOSE, 1);
}

req_sender::~req_sender() {

	curl_easy_cleanup(curl_);	
}

size_t req_sender::write_response_data(char *ptr, size_t size, size_t nmemb, void *userdata) {

    std::stringstream* s = (std::stringstream *)userdata;
    size_t n = size * nmemb;
    s->write(ptr, n);
    return n;
}


string req_sender::send_curl_request(string const & req_str) {

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

    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &req_sender::write_response_data);		

	std::stringstream xml_stream;	
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &xml_stream);

//    CURLcode code = curl_easy_perform(curl_);
	curl_easy_perform(curl_);

	return xml_stream.str();
}


