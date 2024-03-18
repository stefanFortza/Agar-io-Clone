//
// Created by stefantacu on 08.03.2024.
//
#include <iostream>
#include "../headers/SFMLMath.hpp"
#include "../headers/Player.hpp"
#include <SFML/Graphics.hpp>

Player::Player(GameStateManager *manager,
               sf::RenderWindow *window,
               const std::string &name): PlayerBaseClass(manager, window, name) {
}

Player::~Player() = default;

void Player::handleEventCurrent(const sf::Event &event) {
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

void Player::updateCurrent(const sf::Time & /*delta*/) {
    // I need the window
    // dir = sf::Vector2f(sf::Mouse::getPosition(m_context.getSFMLWindow()->getRenderWindow()));
    // auto center = m_context.getSFMLWindow()->getRenderWindow().getSize() / 2U;
    // auto center = sf::Vector2f(1280 / 2., 720 / 2.);
    // dir -= center;
    // sf::normalize(dir);

    // std::cout << dir.x << " " << dir.y << '\n';
    // dir = dir - m_context.getPlayerView().getCenter();
    // dir = dir - static_cast<sf::Vector2f>(center);
    // sf::normalize(dir);
    //
    // dir *= delta.asSeconds() * m_speed;
    // std::cout << center.x << " " << center.y << "\n";
    // std::cout << dir.x << " " << dir.y << '\n';
    // std::cout << sf::getLength(dir) << "\n";
    // m_shape.setPosition(dir);

    // move m_transform instead of shape transform
    // m_player_shape.move(dir);
    // m_view.setCenter(getPosition());
    // m_context.getPlayerView().setCenter(getPosition());

    // this->setVelocity(dir);
    // this->move(dir);
    if (!m_game_state_manager->getNetworkManager()->isServer()) {
        sf::Packet packet;
        packet << PacketType::PlayerPosition;
        packet << getPosition().x << getPosition().y;
        m_game_state_manager->getNetworkManager()->getClient()->sendPacket(packet);
    } else {
        m_game_state_manager->getNetworkManager()->getServer()->setCurrentPlayerData(getPosition().x, getPosition().y);
    }
}

void Player::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    // target.draw(m_shape, transform);
    target.draw(m_player_shape, states);
}

