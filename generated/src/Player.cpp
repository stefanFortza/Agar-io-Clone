//
// Created by stefantacu on 08.03.2024.
//
#include <iostream>
#include <SFMLMath.hpp>
#include "Node.hpp"
#include <Player.hpp>
#include <SFML/Graphics.hpp>

Player::Player() : m_player_shape(50.f), m_view(sf::FloatRect(200.f, 200.f, 300.f, 200.f)) {
    m_speed = 200;
    m_player_shape.setOrigin(sf::Vector2f(50.f, 50.f));
    m_player_shape.setFillColor(sf::Color::Blue);
    m_player_shape.setPosition(sf::Vector2f(100.f, 100.f));
};

Player::~Player() = default;

const sf::View &Player::GetView() {
    return m_view;
}

void Player::onUpdate(sf::Time delta, sf::RenderWindow &window) {
    dir = sf::Vector2f(sf::Mouse::getPosition(window));

    // std::cout << dir.x << " " << dir.y << '\n';
    dir = dir - m_player_shape.getPosition();
    sf::normalize(dir);

    dir *= delta.asSeconds() * m_speed;

    // std::cout << dir.x << " " << dir.y << '\n';
    std::cout << sf::getLength(dir) << "\n";
    // m_shape.setPosition(dir);

    // move m_transform instead of shape transform
    m_player_shape.move(dir);
}

void Player::onDraw(sf::RenderWindow &target, const sf::Transform &/*transform*/) const {
    // target.draw(m_shape, transform);
    target.draw(m_player_shape);
}

