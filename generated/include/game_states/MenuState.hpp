//
// Created by stefantacu on 13.03.2024.
//

#pragma once

#include "GameStateManager.h"
#include "SFML_Window.hpp"
#include "ui/Button.h"


class MenuState : public State {
public:
	MenuState(GameStateManager *manager, sf::RenderWindow *window);

	void handleEvent(const sf::Event &event) override;

	void render() override;

	void update(const sf::Time &deltaTime) override;

	~MenuState() override;

private:
	sf::Font font;
	Button playBtn;

	virtual void play();
};


