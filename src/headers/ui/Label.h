//
// Created by stefantacu on 21.03.2024.
//

#ifndef LABEL_H
#define LABEL_H
#include "SFML/Graphics/Text.hpp"


class Label : public sf::Text {
public:
	explicit Label(const sf::String &string = "Enter Text", unsigned int characterSize = 24);
};


#endif //LABEL_H
