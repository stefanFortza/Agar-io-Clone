//
// Created by stefantacu on 15.05.2024.
//

#include "WrongCharacterEnteredException.h"

WrongCharacterEnteredException::WrongCharacterEnteredException(const std::string &message): message(message) {
}

std::string WrongCharacterEnteredException::getError() {
    return message;
}
