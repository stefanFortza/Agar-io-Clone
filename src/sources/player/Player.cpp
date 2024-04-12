//
// Created by stefantacu on 08.03.2024.
//
#include <iostream>
#include "../../headers/SFMLMath.hpp"
#include "../../headers/player/Player.hpp"
#include <SFML/Graphics.hpp>

#include "../../headers/Grid.hpp"

Player::Player(GameStateManager *manager,
               sf::RenderWindow *window, std::string net_id,
               const std::string &name): PlayerBaseClass(manager, window, net_id, name) {
    this->setVelocity(sf::Vector2f(0, 1) * m_speed);
}


Player::~Player() = default;


void Player::handleEventCurrent(const sf::Event &event) {
    // std::cout << "set vel\n";
    switch (event.type) {
        case sf::Event::MouseMoved: {
            auto x = static_cast<float>(event.mouseMove.x);
            auto y = static_cast<float>(event.mouseMove.y);
            m_dir = sf::Vector2f(x, y);
            // std::cout << "mouse" << '\n';
            const sf::Vector2f center = sf::Vector2f(static_cast<float>(m_window->getSize().x),
                                                     static_cast<float>(m_window->getSize().y)) / 2.f;
            m_dir -= center;
            if (sf::getLength(m_dir) <= 0.1f)
                break;
            sf::normalize(m_dir);

            break;
        }
        default: break;;
        case sf::Event::MouseButtonPressed: {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // this->m_speed = 200;
                this->setIsAccelerating(true);
            }
            break;
        }
        case sf::Event::MouseButtonReleased: {
            if (event.mouseButton.button == sf::Mouse::Left) {
                this->setIsAccelerating(false);
            }
            break;
        }
    }
}

void Player::updateCurrent(const sf::Time &delta) {
    PlayerBaseClass::updateCurrent(delta);
    this->setVelocity(m_dir * m_speed);

    auto pos = this->getPosition();

    pos.x = std::clamp(pos.x, -Grid::m_world_size.x / 2.f, Grid::m_world_size.x / 2.f);
    pos.y = std::clamp(pos.y, -Grid::m_world_size.y / 2.f, Grid::m_world_size.y / 2.f);
    if (pos != this->getPosition())
        this->setPosition(pos);
}

void Player::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    // target.draw(m_shape, transform);
    target.draw(m_player_shape, states);
    target.draw(m_hit_sprite, states);
    target.draw(m_hitbox, states);
}

