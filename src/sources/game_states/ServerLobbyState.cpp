//
// Created by stefantacu on 20.03.2024.
//

#include "../../headers/game_states/ServerLobbyState.h"
#include "../../headers/ui/LobbyPlayerLabels.h"
#include <iostream>

#include "../../headers/game_states/ServerGameState.h"


ServerLobbyState::ServerLobbyState(GameStateManager *manager, sf::RenderWindow *window,
                                   std::string name): LobbyState(manager, window),
                                                      m_lobby_label(nullptr), m_grid(manager, window) {
    std::cout << "Da\n";

    ServerManager::getInstance().onPlayerJoinedLobby.connect([this](const OnlinePlayerData &player_data) {
        onPlayerJoinedLobby(player_data);
    });

    ServerManager::getInstance().onGameStarted.connect(
        [this](const std::map<std::string, OnlinePlayerData> &player_data) {
            onGameStarted(player_data);
        });

    m_lobby_label = std::make_unique<Label>("Server Lobby");
    m_lobby_label->setPosition(sf::Vector2f(100, 100));
    m_player_labels = std::make_unique<LobbyPlayerLabels>(manager, window);
    m_start_game_button = std::make_unique<Button>([this] {
        onStartButtonPressed();
    }, "Start Game");
    m_start_game_button->setCharacterSize(50);


    auto button_pos = static_cast<sf::Vector2f>(window->getSize());
    button_pos.x -= 300 + m_start_game_button->getGlobalBounds().width / 2;
    button_pos.y -= 200 + m_start_game_button->getGlobalBounds().height / 2;
    m_start_game_button->setPosition(button_pos);

    // Start Server after connecting signals
    ServerManager::getInstance().start(name);
}

void ServerLobbyState::handleEvent(const sf::Event &event) {
    m_start_game_button->handleEvent(event);
}

void ServerLobbyState::render() {
    m_window->draw(m_grid);
    m_window->draw(*m_lobby_label);
    m_window->draw(*m_player_labels);
    m_window->draw(*m_start_game_button);
}

void ServerLobbyState::update(const sf::Time &) {
}

void ServerLobbyState::onPlayerJoinedLobby(const OnlinePlayerData &player) {
    std::cout << "player joined\n";
    m_player_labels->addPlayer(player);
}

void ServerLobbyState::onStartButtonPressed() {
    std::cout << "Start game\n";
    ServerManager::getInstance().startGame();
    // m_game_state_manager->setState()
}

void ServerLobbyState::onGameStarted(const std::map<std::string, OnlinePlayerData> &player_data) {
    auto client_game_state = std::make_unique<ServerGameState>(m_game_state_manager, m_window, player_data);
    m_game_state_manager->setState(std::move(client_game_state));
}
