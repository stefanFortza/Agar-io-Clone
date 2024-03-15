//
// Created by stefantacu on 13.03.2024.
//

#include "../../include/game_states/GameStateManager.h"

GameStateManager::GameStateManager() = default;

void GameStateManager::handleEvent(const sf::Event &event) const {
	currentState->handleEvent(event);
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
