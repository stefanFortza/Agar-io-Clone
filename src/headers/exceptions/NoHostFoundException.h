//
// Created by stefantacu on 24.04.2024.
//

#ifndef NOHOSTFOUNDEXCEPTION_H
#define NOHOSTFOUNDEXCEPTION_H
#include <exception>
#include <ostream>
#include <string>


class NoHostFoundException : public std::exception {
    std::string message;

public:
    explicit NoHostFoundException(const std::string &message);

    std::string getError();

    friend std::ostream &operator<<(std::ostream &os, const NoHostFoundException &obj) {
        return os << " message: " << obj.message;
    }
};


#endif //NOHOSTFOUNDEXCEPTION_H
