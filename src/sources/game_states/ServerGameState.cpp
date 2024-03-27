//
// Created by stefantacu on 23.03.2024.
//

#include "../../headers/game_states/ServerGameState.h"

ServerGameState::ServerGameState(GameStateManager *manager, sf::RenderWindow *window,
                                 const std::map<std::string, OnlinePlayerData> &players_data): GameState(
    manager, window, players_data) {
    std::cout << "Game state\n";
    m_players_manager = std::make_unique<PlayersManager>(manager,
                                                         window, players_data,
                                                         ServerManager::getInstance().getServerId()
    );
    m_players_manager->setCamera(m_player_camera);
}

void ServerGameState::handleEvent(const sf::Event &event) {
    m_players_manager->handleEvent(event);
    m_player_camera.handleEvent(event);
}

void ServerGameState::render() {
    m_window->draw(m_grid);
    m_window->setView(m_player_camera.getView());
    m_window->draw(*m_players_manager);
}

void ServerGameState::update(const sf::Time &deltaTime) {
    m_players_manager->update(deltaTime);
    m_player_camera.update(deltaTime);
}

void ServerGameState::handlePlayerDisconected(const std::string &id) {
}
