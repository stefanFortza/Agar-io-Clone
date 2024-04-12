//
// Created by stefantacu on 23.03.2024.
//

#include "../../headers/game_states/ClientGameState.h"
#include "../../headers/network/ClientManager.h"

ClientGameState::ClientGameState(GameStateManager *manager, sf::RenderWindow *window,
                                 const std::map<std::string, OnlinePlayerData> &players_data): GameState(
    manager, window, players_data) {
    m_players_manager = std::make_unique<PlayersManager>(manager, window, players_data,
                                                         ClientManager::getInstance().getClientId());
    m_leaderboards.setPlayersManager(m_players_manager.get());

    ClientManager::getInstance().onPlayerDataReceived.connect([this](const OnlinePlayerData &player_data) {
        onPlayerDataReceived(player_data);
    });

    ClientManager::getInstance().onFoodSpawned.connect([this](sf::Vector2f pos) {
        onFoodSpawned(pos);
    });

    ClientManager::getInstance().onFoodEaten.connect([this](OnlinePlayerData data, int id) {
        onFoodEaten(data, id);
    });

    ClientManager::getInstance().onPlayerEaten.connect([this](const OnlinePlayerData &p1, const OnlinePlayerData &p2) {
        onPlayerEaten(p1, p2);
    });

    ClientManager::getInstance().onPlayerDisconnected.connect([this](const std::string &id) {
        onPlayerDisconnected(id);
    });

    m_players_manager->setCamera(&m_player_camera);
}

void ClientGameState::handleEvent(const sf::Event &event) {
    m_players_manager->handleEvent(event);
    m_player_camera.handleEvent(event);
    m_grid.handleEvent(event);
    m_food_manager.handleEvent(event);

    if (event.type == sf::Event::Closed)
        ClientManager::getInstance().disconnect();
}

void ClientGameState::render() {
    GameState::render();
}

void ClientGameState::update(const sf::Time &deltaTime) {
    GameState::update(deltaTime);

    // send local data to server
    OnlinePlayerData data = m_players_manager->getLocalPlayerData();
    data.id = ClientManager::getInstance().getClientId();
    ClientManager::getInstance().sendLocalDataToServer(data);
}

// void ServerGameState::handlePlayerPosition(std::string &id, sf::Vector2f vector2) {
// }

void ClientGameState::onPlayerDataReceived(const OnlinePlayerData &player_data) {
    m_players_manager->handlePlayerDataReceived(player_data);
    m_leaderboards.handlePlayerDataReceived(player_data);
}

void ClientGameState::onFoodSpawned(sf::Vector2f pos) {
    m_food_manager.spawn(pos);
}

void ClientGameState::onFoodEaten(OnlinePlayerData data, int id) {
    m_food_manager.destroyFood(id);
    m_players_manager->playerAteFood(data);
    std::cout << data << " ate food\n";
}

void ClientGameState::onPlayerEaten(const OnlinePlayerData &player1, const OnlinePlayerData &player2) {
    std::cout << "player eaten" << player1 << player2;
    m_players_manager->playerAtePlayer(player1, player2);
}


void ClientGameState::onPlayerDisconnected(const std::string &id) {
    m_players_manager->disconnectPlayer(id);
}
