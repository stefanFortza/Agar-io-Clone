//
// Created by stefantacu on 13.03.2024.
//

#pragma once


#include <memory>
#include <queue>
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "../network/NetworkManager.h"


class State;
class NetworkManager;

class GameStateManager {
private:
	std::unique_ptr<State> currentState;
	std::queue<std::unique_ptr<State> > m_state_queue;

public:
	GameStateManager();

	void receiveData();

	void handleEvent(const sf::Event &event) const;

	void render() const;

	void update(const sf::Time &deltaTime) const;

	void transitionTo(std::unique_ptr<State> state);


	void sendData();

	~GameStateManager();
};
