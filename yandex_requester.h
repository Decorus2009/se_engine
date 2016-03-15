#ifndef YANDEX_REQUESTER
#define YANDEX_REQUESTER


struct yandex_requester {

private: 

	xml_parser parser_;
	req_sender sender_;	


	yandex_requester(yandex_requester const &);
	yandex_requester &operator=(yandex_requester const &);

public: 


}


#endif
