//
// Created by stefantacu on 14.03.2024.
//

#include "../../headers/game_states/GameState.h"

GameState::GameState(GameStateManager *manager,
                     sf::RenderWindow *window): State(manager, window),
                                                m_world(manager, window), m_client() {
}

void GameState::handleEvent(const sf::Event &event) {
    m_world.handleEvent(event);
    if (m_game_state_manager->isServer()) {
        m_server.start();
    } else {
        m_client.start();
    }
}

void GameState::render() {
    m_window->draw(m_world);
}

void GameState::update(const sf::Time &deltaTime) {
    m_world.update(deltaTime);
}

GameState::~GameState() = default;
