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
                             const std::string &net_id,
                             const std::string &name = "Player");

    OnlinePlayerData getData();

    void setData(const OnlinePlayerData &data);

    sf::FloatRect getBounds() override;

    sf::FloatRect getHitboxBounds();

    void eatFood(Food *food);

    void setSize(float size);

    bool getIsAccelerating() const;

    void setIsAccelerating(bool isAccelerating);

    float getSize() const;

    bool canEat(const PlayerBaseClass &player);

    void die();

    void eatPlayer(const OnlinePlayerData &player_data);

    Signal<float> onSizeChanged;

protected:
    sf::CircleShape m_player_shape;
    sf::CircleShape m_hit_sprite;
    sf::CircleShape m_hitbox;
    sf::Color m_fill_color;
    sf::Color m_outline_color;
    sf::Vector2f m_dir;
    bool m_is_accelerating{};
    bool m_shader_is_glowing_up{};
    bool m_is_dead;
    float m_speed = 20;
    float m_size = 50;
    std::string m_net_id;


    void updateCurrent(const sf::Time &delta) override;

private:
    sf::Time m_elapsed;
};


#endif //PLAYERBASECLASS_H
