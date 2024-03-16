#pragma once

#include <SFML/Graphics.hpp>
#include "./game_states/GameStateManager.h"

class GameStateManager;

class Game {
public:
    Game();

    ~Game();

    void handleEvent(const sf::Event &event) const;

    void handleInput();

    void update();

    void render();

    // bool isWindowOpen() const;

    sf::Time getElapsed() const;

    void restartClock();

    void start();

private:
    GameStateManager *m_game_state_manager;
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;
};
