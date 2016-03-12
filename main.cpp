#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include "se_engine.h"
#include "xml_parser.h"


size_t write_response_data(char *ptr, size_t size, size_t nmemb, void *userdata) {

    std::stringstream* s = (std::stringstream*)userdata;
    size_t n = size * nmemb;
    s->write(ptr, n);
    return n;
}

int main(int argc, char* argv[]) {

	if (argc == 1) {
	
		std::cout << "no args" << std::endl;	
		return 0;
	} 

    CURL *curl = curl_easy_init();

    if (curl) {
		//если запрос состоит из нескольких слов, их надо сшить через "+"
		std::string terminal_query = "";
		for (int i = 1; i < argc; ++i) {
			terminal_query += std::string(argv[i]);
			if (i < argc - 1) {
				terminal_query += "+";
			}
		}

		std::cout << terminal_query << std::endl;

        se_engine se_request(terminal_query);

		std::cout << "******************URL******************" << std::endl;
		std::cout << se_request.get_url() << std::endl;
		std::cout << "******************REQUEST BODY******************" << std::endl;
		std::cout << se_request.get_request() << std::endl << std::endl;
		std::cout << "******************RUNNING A REQUEST******************" << std::endl;

       //request a HTTP POST
        curl_easy_setopt(curl, CURLOPT_POST, 1);

        //подробная информация
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_URL, se_request.get_url().c_str());

		//чтобы можно было работать через https
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, se_request.get_request().c_str());


	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_response_data);
		
		std::stringstream xml_content_stream;	
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &xml_content_stream);

        CURLcode code = curl_easy_perform(curl);

        curl_easy_cleanup(curl);


				
		//проверка размера xml_content_stream
		xml_content_stream.seekg(0, std::ios::end);
		int size_of_xml_content_stream = xml_content_stream.tellg();
		std::cout << "size_of_xml_content_stream " << size_of_xml_content_stream << " bytes" << std::endl << std::endl;

		//если хочется экспортировать stringstream в xml-файл		
		
		FILE * outff = fopen("outf.xml", "w");
		fputs(xml_content_stream.str().c_str(), outff);
		fclose(outff);
		
		xml_parse(xml_content_stream);

    }

    return 0;
}
