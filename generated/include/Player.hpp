#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <SFMLMath.hpp>
#include "Node.hpp"

class Player : public Node {
public:
    Player();

    ~Player();

    const sf::View &GetView();

private:
    sf::CircleShape m_player_shape;
    sf::Vector2f dir;
    sf::View m_view;
    float m_speed = 200;

    void onUpdate(sf::Time delta, sf::RenderWindow &window) override;

    void onDraw(sf::RenderWindow &target, const sf::Transform &transform) const override;
};

#endif
