//
// Created by stefantacu on 20.03.2024.
//

#include "../../headers/game_states/ClientLobbyState.h"
#include "../../headers/game_states/ClientGameState.h"
#include "../../headers/network/ClientManager.h"


ClientLobbyState::ClientLobbyState(GameStateManager *manager, sf::RenderWindow *window): LobbyState(manager, window),
    m_lobby_label("Client label") {
    ClientManager::getInstance().onJoinedLobby.connect(
        [this](const std::map<std::string, OnlinePlayerData> &player_data) {
            onJoinLobby(player_data);
        });
    ClientManager::getInstance().onPlayerJoinedLobby.connect([this](const OnlinePlayerData &player_data) {
        onPlayerJoinedLobby(player_data);
    });
    ClientManager::getInstance().onGameStarted.connect(
        [this](const std::map<std::string, OnlinePlayerData> &player_data) {
            onGameStarted(player_data);
        });

    m_lobby_label.setPosition(100, 100);
    m_player_labels = std::make_unique<LobbyPlayerLabels>(manager, window);

    // Start Client
    ClientManager::getInstance().start();
}

void ClientLobbyState::handleEvent(const sf::Event &event) {
}

void ClientLobbyState::render() {
    m_window->draw(m_lobby_label);
    m_window->draw(*m_player_labels);
}

void ClientLobbyState::update(const sf::Time &deltaTime) {
}

void ClientLobbyState::onJoinLobby(const std::map<std::string, OnlinePlayerData> &player_data) {
    std::cout << "joined lobby\n";
    m_player_labels->setCurrentPlayers(player_data);
}

void ClientLobbyState::onPlayerJoinedLobby(const OnlinePlayerData &player) {
    std::cout << "player joined\n";
    m_player_labels->addPlayer(player);
}

void ClientLobbyState::onGameStarted(const std::map<std::string, OnlinePlayerData> &player_data) {
    auto client_game_state = std::make_unique<ClientGameState>(m_game_state_manager, m_window, player_data);
    m_game_state_manager->setState(std::move(client_game_state));
}
