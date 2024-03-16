//
// Created by stefantacu on 13.03.2024.
//

#include "../../headers/game_states/GameStateManager.h"

GameStateManager::GameStateManager() = default;

void GameStateManager::handleEvent(const sf::Event &event) const {
	currentState->handleEvent(event);
}

bool GameStateManager::isServer() const {
	return m_is_server;
}

void GameStateManager::setIsServer(bool isServer) {
	m_is_server = isServer;
}

void GameStateManager::render() const {
	currentState->render();
}

void GameStateManager::update(const sf::Time &deltaTime) const {
	currentState->update(deltaTime);
}

void GameStateManager::setState(std::unique_ptr<State> state) {
	currentState = std::move(state);
}

GameStateManager::~GameStateManager() = default;
