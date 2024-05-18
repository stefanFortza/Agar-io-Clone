//
// Created by stefantacu on 15.05.2024.
//

#ifndef WRONGCHARACTERENTERED_H
#define WRONGCHARACTERENTERED_H
#include <exception>
#include <ostream>
#include <string>


class WrongCharacterEnteredException : public std::exception {
private:
    std::string message;

public:
    explicit WrongCharacterEnteredException(const std::string &message);

    std::string getError();

    friend std::ostream &operator<<(std::ostream &os, const WrongCharacterEnteredException &obj) {
        return os << " message: " << obj.message;
    }
};

#endif //WRONGCHARACTERENTERED_H
