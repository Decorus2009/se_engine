#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include "se_engine.h"

size_t write_response_data(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::stringstream* s = (std::stringstream*)userdata;
    size_t n = size * nmemb;
    s->write(ptr, n);
    return n;
}


struct File {
  const char *filename;
  FILE *stream;
};
 
static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
  struct File *out = (struct File *)stream;

  if(out && !out->stream) {
    //open file for writing 
    out->stream=fopen(out->filename, "wb");

		//failure, can't open file to write
    if(!out->stream) {
      return -1; 
		}
  }
  return fwrite(buffer, size, nmemb, out->stream);
}

int main(int argc, char* argv[])
{

		if (argc == 1) {
	
			std::cout << "no args" << std::endl;	
			return 0;
		} 

		File my_xml_file = {"/home/decorus/Dropbox/CSC/Practice/I/se_engine/test.xml", /* name to store the file as if successful */ NULL	};

    CURL *curl = NULL;
    curl = curl_easy_init();
    if (curl)
    {

				std::string terminal_query = "";
				for (int i = 1; i < argc; ++i) {
						terminal_query += std::string(argv[i]);
						if (i < argc - 1) {
							terminal_query += "+";
						}
				}

				std::cout << terminal_query << std::endl;

        se_engine se_test(terminal_query);
				std::cout << se_test.get_url() << std::endl;
				std::cout << se_test.get_request() << std::endl;
				std::cout << "RUNNING A REQUESTS" << std::endl << std::endl;

       //request a HTTP POST
        curl_easy_setopt(curl, CURLOPT_POST, 1);

        //подробная информация
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_URL, se_test.get_url().c_str());

				//чтобы можно было работать через https
				curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 
				curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);


        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, se_test.get_request().c_str());
        std::stringstream content_stream;


//	      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_response_data);
//	      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content_stream);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &my_xml_file);


        CURLcode code = curl_easy_perform(curl);

        curl_easy_cleanup(curl);


//				fseek(my_xml_file, 0, SEEK_END);   // non-portable
//		    size_t my_xml_file_size = ftell(my_xml_file.stream);


// 		    my_xml_file.seekg(0, std::ifstream::end);
//	 	    size_t my_xml_file_size = my_xml_file.stream->tellg();
 			
//				std::cout << "MY XML FILE SIZE: " << my_xml_file_size << " bytes" << std::endl;	

				
				//проверка размера content_stream
//				content_stream.seekg(0, std::ios::end);
//				int size_of_content_stream = content_stream.tellg();

//				std::cout << "size_of_content_stream " << size_of_content_stream << " bytes" << std::endl << std::endl;


//        std::cout << "CONTENT STREAM" << std::endl << std::endl;
//        std::cout << content_stream.str() << std::endl;

    }

    return 0;
}
