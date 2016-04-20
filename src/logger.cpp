#include <iostream>
#include "logger.hpp"

logger::logger(std::string const &mode) {
    severity_ = mode;
}

//template <typename T>
//logger& logger::operator<<(T const& info) {
//    storage_ << info;
//    return *this;
//}

void logger::print_log() {

    std::cout << "LOG: " << std::endl
    << "-----------------------------------------------------"
    << "-----------------------------------------------------" << std::endl
    << storage_.str() << std::endl;
}

std::string const &logger::get_severity() const {
    return severity_;
}
