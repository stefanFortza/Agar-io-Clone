//
// Created by stefantacu on 23.03.2024.
//

#include "../../headers/game_states/ClientGameState.h"

ClientGameState::ClientGameState(GameStateManager *manager, sf::RenderWindow *window,
                                 const std::map<std::string, OnlinePlayerData> &players_data): GameState(
    manager, window, players_data) {
    m_players_manager = std::make_unique<PlayersManager>(manager, window, players_data,
                                                         ClientManager::getInstance().getClientId());
    ClientManager::getInstance().onPlayerDataReceived.connect([this](const OnlinePlayerData &player_data) {
        onPlayerDataReceived(player_data);
    });

    ClientManager::getInstance().onFoodSpawned.connect([this](sf::Vector2f pos) {
        onFoodSpawned(pos);
    });

    ClientManager::getInstance().onFoodEaten.connect([this](OnlinePlayerData data, int id) {
        onFoodEaten(data, id);
    });

    m_players_manager->setCamera(m_player_camera);
}

void ClientGameState::handleEvent(const sf::Event &event) {
    m_players_manager->handleEvent(event);
    m_player_camera.handleEvent(event);
    m_grid.handleEvent(event);
    m_food_manager.handleEvent(event);
    if (event.type == sf::Event::Closed)
        m_game_state_manager->getNetworkManager()->disconnect();
}

void ClientGameState::render() {
    m_window->draw(m_grid);
    m_window->draw(m_food_manager);
    m_window->setView(m_player_camera.getView());
    m_window->draw(*m_players_manager);
}

void ClientGameState::update(const sf::Time &deltaTime) {
    m_grid.update(deltaTime);
    m_player_camera.update(deltaTime);
    m_players_manager->update(deltaTime);
    m_food_manager.update(deltaTime);

    // send local data to server
    OnlinePlayerData data = m_players_manager->getLocalPlayerData();
    data.id = ClientManager::getInstance().getClientId();
    ClientManager::getInstance().sendLocalDataToServer(data);
}

// void ServerGameState::handlePlayerPosition(std::string &id, sf::Vector2f vector2) {
// }

void ClientGameState::onPlayerDataReceived(const OnlinePlayerData &player_data) {
    m_players_manager->handlePlayerDataReceived(player_data);
}

void ClientGameState::onFoodSpawned(sf::Vector2f pos) {
    m_food_manager.spawn(pos);
}

void ClientGameState::onFoodEaten(OnlinePlayerData data, int id) {
    m_food_manager.destroyFood(id);
    m_players_manager->playerAteFood(data);
    std::cout << data << " ate food\n";
}

void ClientGameState::handlePlayerDisconected(const std::string &id) {
}
