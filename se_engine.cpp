#include "se_engine.h"

se_engine::se_engine(std::string query) : query_(query) {

    build_url();
    build_query();

}

se_engine::~se_engine() {}

void se_engine::build_url() {

    ya_address_ = "https://yandex.com/search/xml?";
    user_ = "decorus2009";
    api_key_ = "03.88707539:10c39ba1ba0ca5ad3a32a1f9387d0da2";

    //default
    l10n_ = "en";
    filter_ = "moderate";

    //default
    //showmecaptcha_ = "yes";

    url_ = ya_address_ + "user=" + user_ + "&key=" + api_key_ + "&l10n=" + l10n_ + "&filter=" + filter_;
}
void se_engine::build_query() {

    //надо сделать поддержку percent-encoding

    xml_encode_type_ = "UTF-8";
    req_header_ = (std::string)"<?xml version=" + "\"" + "1.0" + "\"" + " encoding=" + "\"" + xml_encode_type_ + "\"" + "?>";

    sortby_ = "rlv";
    maxpassages_ = "2";
    page_ = "0";
    groupby_ = (std::string)"attr=" + "\"" + "d" + "\"" + " mode=" + "\"" + (std::string)"deep" +
            "\"" + " groups-on-page=" + "\"" + "10" + "\"" + " docs-in-group=" + "\"" + "3" + "\"";

    request_ = req_header_ + "\n" + "<request>" + "\n" + "<query>" + query_ + "</query>" + "\n\t" +
               "<sortby>" + sortby_ + "</sortby>" + "\n\t" + "<maxpassages>" + maxpassages_ + "</maxpassages>" +
               "\n\t" + "<page>" + page_ + "</page>" + "\n\t" + "<groupings>" + "\n\t" + "<groupby " + groupby_ + " />" +
               "\n" + "</groupings>" + "\n" + "</request>";
}
