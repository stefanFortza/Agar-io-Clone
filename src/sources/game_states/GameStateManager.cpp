//
// Created by stefantacu on 13.03.2024.
//

#include "../../headers/game_states/GameStateManager.h"
#include "../../headers/network/ServerManager.h"
#include "../../headers/network/ClientManager.h"

#include <iostream>

GameStateManager::GameStateManager(): m_network_manager(nullptr) {
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

void GameStateManager::setState(std::unique_ptr<State> state) {
	currentState = std::move(state);
}

void GameStateManager::setNetworkManager(std::unique_ptr<NetworkManager> network_manager) {
	m_network_manager = std::move(network_manager);
}

void GameStateManager::receiveData() {
	if (ServerManager::getInstance().isRunning()) {
		ServerManager::getInstance().receiveData();
	} else if (ClientManager::getInstance().isRunning()) {
		ClientManager::getInstance().receiveData();
	}
}

void GameStateManager::sendData() {
	if (m_network_manager)
		m_network_manager->sendData();
}

NetworkManager *GameStateManager::getNetworkManager() {
	return m_network_manager.get();
}

GameStateManager::~GameStateManager() = default;
