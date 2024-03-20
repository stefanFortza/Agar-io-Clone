//
// Created by stefantacu on 14.03.2024.
//

#include "../../headers/game_states/GameState.h"

#include <iostream>

#include "../../headers/Command.h"

GameState::GameState(GameStateManager *manager,
                     sf::RenderWindow *window): State(manager, window),
                                                m_world(manager, window) {
}

void GameState::handleEvent(const sf::Event &event) {
    m_world.handleCommands(m_command_queue);

    m_world.handleEvent(event);
    if (event.type == sf::Event::Closed)
        m_game_state_manager->getNetworkManager()->disconnect();
}

void GameState::render() {
    m_window->draw(m_world);
}

void GameState::update(const sf::Time &deltaTime) {
    m_world.update(deltaTime);
}

GameState::~GameState() = default;

void GameState::handlePlayerJoined(std::string &id) {
    m_world.handlePlayerJoined(id);
}

void GameState::handlePlayerPosition(std::string &id, sf::Vector2f vector2) {
    m_world.handlePlayerPosition(id, vector2);
}

void GameState::handleConnected(std::map<std::string, std::unique_ptr<OnlinePlayerData> > &map) {
    m_world.handleConnectedToServer(map);
}

void GameState::handlePlayerDisconected(const std::string &id) {
    m_world.handlePlayerDisconected(id);
}

void GameState::addCommand(std::unique_ptr<Command> command) {
    m_command_queue.push(std::move(command));
}
