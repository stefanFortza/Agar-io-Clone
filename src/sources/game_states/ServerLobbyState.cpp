//
// Created by stefantacu on 20.03.2024.
//

#include "../../headers/game_states/ServerLobbyState.h"
#include "../ui/LobbyPlayerLabels.h"
#include <iostream>


ServerLobbyState::ServerLobbyState(GameStateManager *manager, sf::RenderWindow *window): LobbyState(manager, window),
    m_lobby_label(nullptr) {
    std::cout << "Da\n";
    ServerManager::getInstance().onPlayerJoinedLobby.connect([this](const OnlinePlayerData &player_data) {
        onPlayerJoinedLobby(player_data);
    });
    m_lobby_label = std::make_unique<Label>("Server Lobby");
    m_lobby_label->setPosition(sf::Vector2f(100, 100));
    m_player_labels = std::make_unique<LobbyPlayerLabels>(manager, window);

    // Start Server after connecting signals
    ServerManager::getInstance().start();
}

void ServerLobbyState::handleEvent(const sf::Event &event) {
}

void ServerLobbyState::render() {
    m_window->draw(*m_lobby_label);
    m_window->draw(*m_player_labels);
}

void ServerLobbyState::update(const sf::Time &deltaTime) {
}

void ServerLobbyState::onPlayerJoinedLobby(const OnlinePlayerData &player) {
    std::cout << "player joined\n";
    m_player_labels->addPlayer(player);
}

