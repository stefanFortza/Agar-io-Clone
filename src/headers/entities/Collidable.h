//
// Created by stefantacu on 27.03.2024.
//

#ifndef COLLIDABLE_H
#define COLLIDABLE_H
#include "SFML/Graphics/Rect.hpp"


class Collidable {
public:
    virtual sf::FloatRect getBounds() = 0;
};


#endif //COLLIDABLE_H
