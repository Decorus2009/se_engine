#include <iostream>
#include "logger.hpp"

logger::logger(std::string const &mode) {
    severity_ = mode;
}

//    template<class T>
//    void logger::write_log(T const& val, std::string mode = "DEBUG") {
//
//    (mode == "DEBUG") ? storage_debug_ << val : storage_release_ << val;
//}

void logger::write_log(std::string info, std::string mode) {

    (mode == "DEBUG") ? storage_debug_ << info : storage_release_ << info;
}
void logger::print_log() {

    if (severity_ == "DEBUG") {
        std::cout << storage_debug_.str() << std::endl;
    }
    else {
        std::cout << storage_release_.str() << std::endl;
    }
}

