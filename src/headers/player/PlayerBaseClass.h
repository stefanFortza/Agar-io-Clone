//
// Created by stefantacu on 16.03.2024.
//

#ifndef PLAYERBASECLASS_H
#define PLAYERBASECLASS_H
#include "../entities/Collidable.h"
#include "../entities/Entity.hpp"


class PlayerBaseClass : public Entity, public Collidable {
public:
    explicit PlayerBaseClass(GameStateManager *manager,
                             sf::RenderWindow *window,
                             const std::string &name = "Player");

protected:
    sf::CircleShape m_player_shape;
    sf::Vector2f dir;
    float m_speed = 20;
};


#endif //PLAYERBASECLASS_H
