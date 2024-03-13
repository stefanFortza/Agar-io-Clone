//
// Created by stefantacu on 11.03.2024.
//

#include "GameContext.hpp"

GameContext::GameContext(SFML_Window *window) : m_player_view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f)),
                                                m_window(window) {
}

sf::View &GameContext::getPlayerView() {
    return m_player_view;
}

SFML_Window *GameContext::getSFMLWindow() {
    return m_window;
}
