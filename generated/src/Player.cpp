//
// Created by stefantacu on 08.03.2024.
//
#include <iostream>
#include <SFMLMath.hpp>
#include <Player.hpp>
#include <SFML/Graphics.hpp>

Player::Player(GameContext &context): Entity(context),
                                      m_player_shape(50.f),
                                      m_view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f)) {
    m_speed = 200;
    m_player_shape.setOrigin(sf::Vector2f(50.f, 50.f));
    m_player_shape.setFillColor(sf::Color::Blue);
    // m_player_shape.setPosition(sf::Vector2f(1280.f / 2.f, 720 / 2.f));
}

Player::~Player() = default;

// const sf::View &Player::GetView() const {
//     return m_view;
// }

void Player::updateCurrent(sf::Time delta) {
    // I need the view
    dir = sf::Vector2f(sf::Mouse::getPosition(m_context.getSFMLWindow()->GetRenderWindow()));
    auto center = m_context.getSFMLWindow()->GetRenderWindow().getSize() / 2U;

    // std::cout << dir.x << " " << dir.y << '\n';
    // dir = dir - m_context.getPlayerView().getCenter();
    dir = dir - static_cast<sf::Vector2f>(center);
    sf::normalize(dir);

    // dir *= delta.asSeconds() * m_speed;
    dir *= m_speed;
    std::cout << center.x << " " << center.y << "\n";
    // std::cout << dir.x << " " << dir.y << '\n';
    // std::cout << sf::getLength(dir) << "\n";
    // m_shape.setPosition(dir);

    // move m_transform instead of shape transform
    // m_player_shape.move(dir);
    // m_view.setCenter(getPosition());
    // m_context.getPlayerView().setCenter(getPosition());

    this->setVelocity(dir);
    // this->move(dir);
}

void Player::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    // target.draw(m_shape, transform);
    target.draw(m_player_shape, states);
}

