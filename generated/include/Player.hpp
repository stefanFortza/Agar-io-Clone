#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Node.hpp"
#include <iostream>

class Player : public Node
{
public:
    Player() : m_shape(50.f)
    {
        m_shape.setFillColor(sf::Color::Blue);
        m_shape.setPosition(sf::Vector2f(100.f, 100.f));
    };

    ~Player(){};

private:
    sf::CircleShape m_shape;
    sf::Vector2f dir;

    virtual void onUpdate(sf::RenderWindow &window)
    {
        // dir = sf::Vector2f(sf::Mouse::getPosition(window));
        // // std::cout << dir.x << " " << dir.y << '\n';
        // dir = m_shape.getPosition() - dir;
        // std::cout << dir.x << " " << dir.y << '\n';
        // m_shape.setPosition(dir);
        // m_shape.move(dir);
    }

    virtual void onDraw(sf::RenderWindow &target, const sf::Transform &transform) const
    {
        // target.draw(m_shape, transform);
        target.draw(m_shape);
    }
};

#endif