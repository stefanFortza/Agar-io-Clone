//
// Created by stefantacu on 16.03.2024.
//

#include "../../headers/player/PlayerBaseClass.h"


PlayerBaseClass::PlayerBaseClass(GameStateManager *manager,
                                 sf::RenderWindow *window,
                                 const std::string &name): Entity(manager, window, name),
                                                           m_player_shape(50.f) {
    // auto center = sf::Vector2f(static_cast<float>(m_window->getSize().x),
    // static_cast<float>(m_window->getSize().y)) / 2.f;
    // m_player_shape.setOrigin(center);
    m_player_shape.setOrigin(sf::Vector2f(50.f, 50.f));
    m_player_shape.setFillColor(sf::Color::Blue);
}

