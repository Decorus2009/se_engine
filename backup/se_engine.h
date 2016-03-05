#ifndef SE_ENGINE_H
#define SE_ENGINE_H

#include<string>
#include<iostream>

struct se_engine {

public:

    se_engine(std::string query);
		~se_engine();

    inline std::string get_url() const { return url_; }
    inline std::string get_request() const { return request_; }

private:
    se_engine(se_engine const &);
    se_engine &operator=(se_engine const &);

    std::string ya_address_;
    std::string user_;
    std::string api_key_;
    std::string filter_;
    std::string l10n_;
		std::string url_;
    
		//std::string showmecaptcha_;
    std::string xml_encode_type_;
    std::string req_header_;
    std::string query_;
    std::string sortby_;
    std::string maxpassages_;
    std::string page_;
    std::string groupby_;
    std::string request_;

    void build_url();
    void build_query();
};


#endif //SE_ENGINE_H


