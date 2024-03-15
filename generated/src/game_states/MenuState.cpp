//
// Created by stefantacu on 13.03.2024.
//

#include "../include/game_states/MenuState.hpp"

#include <iostream>

#include "game_states/GameState.h"


MenuState::MenuState(GameStateManager *manager,
                     sf::RenderWindow *window): State(manager, window),
                                                playBtn(std::bind(&
                                                                  MenuState::play, this)) {
	// font.loadFromFile("assets/roboto/Roboto-Light.ttf");
	font.loadFromFile("assets/roboto/Roboto-Light.ttf");
	playBtn.setFont(font);
	playBtn.setString("Play");
	playBtn.setCharacterSize(50);
	playBtn.setPosition(m_window->getSize().x / 2 - playBtn.getGlobalBounds().width / 2,
	                    m_window->getSize().y / 2 - playBtn.getGlobalBounds().height / 2);
}

void MenuState::handleEvent(const sf::Event &event) {
	playBtn.handleEvent(event);
}

void MenuState::render() {
	m_window->draw(playBtn);
	// window->draw(playBtn);
}

void MenuState::update(const sf::Time &deltaTime) {
}

void MenuState::play() {
	std::cout << "pressed" << '\n';
	// m_game_state_manager->setState(std::make_unique<ConnectionState>(manager, window));
	m_game_state_manager->setState(std::make_unique<GameState>(m_game_state_manager, m_window));
}

MenuState::~MenuState() = default;
