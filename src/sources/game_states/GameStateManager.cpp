//
// Created by stefantacu on 13.03.2024.
//

#include "../../headers/game_states/GameStateManager.h"
#include "../../headers/network/ServerManager.h"
#include "../../headers/network/ClientManager.h"

#include <iostream>

GameStateManager::GameStateManager() {
} ;

void GameStateManager::handleEvent(const sf::Event &event) const {
	currentState->handleEvent(event);
}

void GameStateManager::render() const {
	currentState->render();
}

void GameStateManager::update(const sf::Time &deltaTime) const {
	currentState->update(deltaTime);
}

void GameStateManager::transitionTo(std::unique_ptr<State> state) {
	// currentState.
	currentState = std::move(state);
}


void GameStateManager::receiveData() {
	if (ServerManager::getInstance().isRunning()) {
		ServerManager::getInstance().receiveData();
	} else if (ClientManager::getInstance().isRunning()) {
		ClientManager::getInstance().receiveData();
	}
}

void GameStateManager::sendData() {
}


GameStateManager::~GameStateManager() = default;
