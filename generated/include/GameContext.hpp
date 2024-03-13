//
// Created by stefantacu on 11.03.2024.
//

#ifndef GAME_CONTEXT_HPP
#define GAME_CONTEXT_HPP
#include <SFML/Graphics.hpp>

#include "SFML_Window.hpp"

class GameContext {
public:
    GameContext(SFML_Window *window);

    sf::View &getPlayerView();

    SFML_Window *getSFMLWindow();

private:
    sf::View m_player_view;
    SFML_Window *m_window;
};

#endif //GAME_CONTEXT_HPP
