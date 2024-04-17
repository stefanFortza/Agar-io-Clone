//
// Created by stefantacu on 15.04.2024.
//

#include "../../headers/ui/LobbyPlayerLabel.h"

LobbyPlayerLabel::LobbyPlayerLabel(GameStateManager *manager, sf::RenderWindow *window,
                                   const std::string &name): SceneNode(manager, window, name), m_player_name(name) {
    m_fill.setFillColor(sf::Color(4209888767));
    // faedcd
    m_fill.setOutlineColor(sf::Color::Black);
    m_fill.setOutlineThickness(2);
    m_fill.setSize(
        sf::Vector2f(m_player_name.getGlobalBounds().width + 15, m_player_name.getGlobalBounds().height + 15));
    m_fill.setPosition(m_player_name.getPosition().x, m_player_name.getPosition().y);
    m_fill.setOrigin(3, 3);
}

void LobbyPlayerLabel::handleEventCurrent(const sf::Event &event) {
}

void LobbyPlayerLabel::updateCurrent(const sf::Time &delta) {
}

void LobbyPlayerLabel::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_fill, states);
    target.draw(m_player_name, states);
}
