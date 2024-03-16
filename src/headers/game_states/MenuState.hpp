//
// Created by stefantacu on 13.03.2024.
//

#pragma once

#include "GameStateManager.h"
#include "../ui/Button.h"


class MenuState : public State {
public:
	MenuState(GameStateManager *manager, sf::RenderWindow *window);

	void handleEvent(const sf::Event &event) override;

	void render() override;

	void update(const sf::Time &deltaTime) override;

	void host();

	~MenuState() override;

private:
	sf::Font font;
	Button playBtn;
	Button hostBtn;

	virtual void play();

	void changeState(bool isServer);
};


