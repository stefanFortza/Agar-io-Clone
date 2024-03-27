//
// Created by stefantacu on 23.03.2024.
//

#include "../../headers/game_states/ClientGameState.h"

ClientGameState::ClientGameState(GameStateManager *manager, sf::RenderWindow *window,
                                 const std::map<std::string, OnlinePlayerData> &players_data): GameState(
    manager, window, players_data) {
    m_players_manager = std::make_unique<PlayersManager>(manager, window, players_data,
                                                         ClientManager::getInstance().getClientId());
    m_players_manager->setCamera(m_player_camera);
}

void ClientGameState::handleEvent(const sf::Event &event) {
    m_players_manager->handleEvent(event);
    m_player_camera.handleEvent(event);
    m_grid.handleEvent(event);
    if (event.type == sf::Event::Closed)
        m_game_state_manager->getNetworkManager()->disconnect();
}

void ClientGameState::render() {
    m_window->draw(m_grid);
    m_window->setView(m_player_camera.getView());
    m_window->draw(*m_players_manager);
}

void ClientGameState::update(const sf::Time &deltaTime) {
    m_grid.update(deltaTime);
    m_player_camera.update(deltaTime);
    m_players_manager->update(deltaTime);
}

// void ServerGameState::handlePlayerPosition(std::string &id, sf::Vector2f vector2) {
// }


void ClientGameState::handlePlayerDisconected(const std::string &id) {
}
