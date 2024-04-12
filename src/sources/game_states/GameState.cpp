//
// Created by stefantacu on 14.03.2024.
//

#include "../../headers/game_states/GameState.h"

GameState::GameState(GameStateManager *manager,
                     sf::RenderWindow *window,
                     const std::map<std::string, OnlinePlayerData> &players_data): State(manager, window),
    m_players_manager(nullptr), m_grid(manager, window),
    players_data(players_data), m_player_camera(manager, window),
    m_food_manager(manager, window), m_leaderboards(manager, window, players_data) {
}

void GameState::handleEvent(const sf::Event &) {
}

void GameState::update(const sf::Time &deltaTime) {
    m_grid.update(deltaTime);
    m_player_camera.update(deltaTime);
    m_players_manager->update(deltaTime);
    m_food_manager.update(deltaTime);
    m_leaderboards.update(deltaTime);
}


void GameState::render() {
    m_window->setView(m_player_camera.getView());
    m_window->draw(m_grid);
    m_window->draw(m_food_manager);
    m_window->draw(*m_players_manager);

    // draw ui
    m_window->setView(m_window->getDefaultView());
    m_window->draw(m_leaderboards);
}


GameState::~GameState() = default;

