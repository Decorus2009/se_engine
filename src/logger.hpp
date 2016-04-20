#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <sstream>
#include <string>

struct logger {

public:
    logger(std::string const &mode);

//    template<class T>
//    void write_log(T const& val, std::string mode = "DEBUG");

//    void write_log(std::string info, std::string mode = "DEBUG");
    template <typename T>
    logger& operator<<(T const& info) {
        storage_ << info;
        return *this;
    }

    void print_log();

    std::string const& get_severity() const;
    logger(logger const &) = delete;
    logger &operator=(logger const &) = delete;

private:
//    std::stringstream storage_debug_;
//    std::stringstream storage_release_;
    std::string severity_;
    std::stringstream storage_;
};


#endif //LOGGER_HPP
