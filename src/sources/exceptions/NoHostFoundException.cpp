//
// Created by stefantacu on 24.04.2024.
//

#include "../../headers/exceptions/NoHostFoundException.h"


NoHostFoundException::NoHostFoundException(const std::string &message)
    : message(message) {
}

std::string NoHostFoundException::getError() {
    return message;
}
