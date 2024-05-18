//
// Created by stefantacu on 13.03.2024.
//

#pragma once

#include "GameStateManager.h"
#include "../Grid.hpp"
#include "../ui/Button.h"
#include "../ui/InputField.h"


class MenuState : public State {
public:
	MenuState(GameStateManager *manager, sf::RenderWindow *window);

	void handleEvent(const sf::Event &event) override;

	void render() override;

	void update(const sf::Time &deltaTime) override;

	~MenuState() override;

private:
	InputField m_name_input_field;
	std::unique_ptr<Button> playBtn;
	std::unique_ptr<Button> hostBtn;
	Grid grid;
	bool m_is_transitioning;

	void play();

	void host();
};


