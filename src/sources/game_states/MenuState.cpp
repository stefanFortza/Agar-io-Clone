//
// Created by stefantacu on 13.03.2024.
//

#include "../../headers/game_states/MenuState.hpp"
#include <iostream>

#include "../../headers/game_states/ClientLobbyState.h"
#include "../../headers/game_states/GameState.h"
#include "../../headers/game_states/LobbyState.h"
#include "../../headers/game_states/ServerLobbyState.h"
#include "../../headers/network/ServerManager.h"


MenuState::MenuState(GameStateManager *manager,
                     sf::RenderWindow *window): State(manager, window),

                                                playBtn(nullptr),
                                                grid(manager, window) {
	playBtn = std::make_unique<Button>([this] { play(); });
	hostBtn = std::make_unique<Button>([this] { host(); });

	playBtn->setString("Play");
	playBtn->setCharacterSize(50);
	playBtn->setPosition(m_window->getSize().x / 2 - playBtn->getGlobalBounds().width / 2 + 100,
	                     m_window->getSize().y / 2 - playBtn->getGlobalBounds().height / 2);


	hostBtn->setString("Host");
	hostBtn->setCharacterSize(50);
	hostBtn->setPosition(m_window->getSize().x / 2 - playBtn->getGlobalBounds().width / 2 - 100,
	                     m_window->getSize().y / 2 - playBtn->getGlobalBounds().height / 2);

	m_name_input_field.setSelected(true);
	m_name_input_field.setPosition(m_window->getSize().x / 2 - 200,
	                               m_window->getSize().y / 2 - 150);
}

void MenuState::handleEvent(const sf::Event &event) {
	m_name_input_field.handleEvent(event);
	if (playBtn)
		playBtn->handleEvent(event);
	if (hostBtn)
		hostBtn->handleEvent(event);
}

void MenuState::render() {
	m_window->draw(grid);
	m_window->draw(m_name_input_field);
	m_window->draw(*playBtn);
	m_window->draw(*hostBtn);
}

void MenuState::update(const sf::Time &deltaTime) {
	m_name_input_field.update(deltaTime);
}

void MenuState::host() {
	// auto server_manager = std::make_unique<ServerManager>();
	auto lobby_state = std::make_unique<ServerLobbyState>(m_game_state_manager, m_window, m_name_input_field.getText());
	// m_game_state_manager->setState(std::move(lobby_state));
	m_game_state_manager->enqueueState(std::move(lobby_state));
}

void MenuState::play() {
	auto lobby_state = std::make_unique<ClientLobbyState>(m_game_state_manager, m_window, m_name_input_field.getText());
	m_game_state_manager->enqueueState(std::move(lobby_state));
	// m_game_state_manager->setState(std::move(lobby_state));
}

MenuState::~MenuState() = default;
