#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <sstream>
#include <iostream>
struct logger {

public:
    template <typename T>
    logger& operator<<(T const& value) {
        log_storage_ << value;
        return *this;
    }

    void print_log() {
        std::cout << log_storage_.str() << std::endl;
    }
private:
    std::stringstream log_storage_;
};



#endif //LOGGER_HPP
