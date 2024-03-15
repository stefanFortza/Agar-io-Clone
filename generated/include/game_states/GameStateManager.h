//
// Created by stefantacu on 13.03.2024.
//

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "State.hpp"


class State;

class GameStateManager {
public:
	GameStateManager();

	void handleEvent(const sf::Event &event) const;

	void render() const;

	void update(const sf::Time &deltaTime) const;

	void setState(std::unique_ptr<State> state);

	~GameStateManager();

private:
	std::unique_ptr<State> currentState;
};


