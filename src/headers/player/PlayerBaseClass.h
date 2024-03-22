//
// Created by stefantacu on 16.03.2024.
//

#ifndef PLAYERBASECLASS_H
#define PLAYERBASECLASS_H
#include "../Entity.hpp"


class PlayerBaseClass : public Entity {
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
