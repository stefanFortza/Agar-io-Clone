#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Game.hpp"

class Player : public Entity {
public:
    explicit Player(GameContext &context);

    ~Player();

    // const sf::View &GetView() const;

private:
    sf::CircleShape m_player_shape;
    sf::Vector2f dir;
    sf::View m_view;
    float m_speed = 200;

    void updateCurrent(sf::Time delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif
