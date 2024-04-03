//
// Created by stefantacu on 08.03.2024.
//
#include <iostream>
#include "../../headers/SFMLMath.hpp"
#include "../../headers/player/Player.hpp"
#include <SFML/Graphics.hpp>

Player::Player(GameStateManager *manager,
               sf::RenderWindow *window, std::string net_id,
               const std::string &name): PlayerBaseClass(manager, window, net_id, name) {
}

Player::~Player() = default;


void Player::handleEventCurrent(const sf::Event &event) {
    // std::cout << "set vel\n";
    switch (event.type) {
        case sf::Event::MouseMoved: {
            dir = sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
            // std::cout << "mouse" << '\n';
            const sf::Vector2f center = sf::Vector2f(static_cast<float>(m_window->getSize().x),
                                                     static_cast<float>(m_window->getSize().y)) / 2.f;
            dir -= center;
            if (sf::getLength(dir) <= 0.1f)
                return;
            sf::normalize(dir);
            dir *= m_speed;
            this->setVelocity(dir);
            break;
        }
        default: break;
    }
}

void Player::updateCurrent(const sf::Time &delta) {
}

void Player::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    // target.draw(m_shape, transform);
    target.draw(m_player_shape, states);
    target.draw(m_hitbox, states);
}

