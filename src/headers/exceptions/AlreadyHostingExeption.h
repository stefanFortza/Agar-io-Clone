//
// Created by stefantacu on 24.04.2024.
//

#ifndef ALREADYHOSTINGEXEPTION_H
#define ALREADYHOSTINGEXEPTION_H
#include <exception>
#include <ostream>
#include <string>


class AlreadyHostingExeption : public std::exception {
    std::string message;

public:
    explicit AlreadyHostingExeption(const std::string &message);

    std::string getError();

    friend std::ostream &operator<<(std::ostream &os, const AlreadyHostingExeption &obj) {
        return os << " message: " << obj.message;
    }
};


#endif //ALREADYHOSTINGEXEPTION_H
