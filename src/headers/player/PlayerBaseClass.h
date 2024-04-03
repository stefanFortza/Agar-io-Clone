//
// Created by stefantacu on 16.03.2024.
//

#ifndef PLAYERBASECLASS_H
#define PLAYERBASECLASS_H

#include "../entities/Collidable.h"
#include "../entities/Entity.hpp"
#include "../network/OnlinePlayerData.h"
#include "../utils/Signal.h"


class Food;

class PlayerBaseClass : public Entity, public Collidable {
public:
    explicit PlayerBaseClass(GameStateManager *manager,
                             sf::RenderWindow *window,
                             std::string net_id,
                             const std::string &name = "Player");

    OnlinePlayerData getData();

    void setData(const OnlinePlayerData &data);

    sf::FloatRect getBounds() override;

    void eatFood(Food *food);

    void setSize(float size);

    Signal<float> onSizeChanged;

protected:
    sf::CircleShape m_player_shape;
    sf::CircleShape m_hitbox;
    sf::Vector2f dir;
    float m_speed = 20;
    float m_size = 50;
    std::string m_net_id;
};


#endif //PLAYERBASECLASS_H
