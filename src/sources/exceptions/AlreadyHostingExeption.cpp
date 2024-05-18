//
// Created by stefantacu on 24.04.2024.
//

#include "../../headers/exceptions/AlreadyHostingExeption.h"

AlreadyHostingExeption::AlreadyHostingExeption(const std::string &message)
    : message(message) {
}

std::string AlreadyHostingExeption::getError() {
    return message;
}
