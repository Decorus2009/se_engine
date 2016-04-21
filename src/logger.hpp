#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <sstream>
#include <string>

struct logger {

public:
    logger(std::string const &mode);

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

    std::string severity_;
    std::stringstream storage_;
};

#endif //LOGGER_HPP
