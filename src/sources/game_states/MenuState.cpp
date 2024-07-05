//
// Created by stefantacu on 13.03.2024.
//

#include "../../headers/game_states/MenuState.hpp"
#include <iostream>

#include "../../headers/exceptions/AlreadyHostingExeption.h"
#include "../../headers/exceptions/NoHostFoundException.h"
#include "../../headers/exceptions/WrongCharacterEnteredException.h"
#include "../../headers/game_states/ClientLobbyState.h"
#include "../../headers/game_states/GameState.h"
#include "../../headers/game_states/LobbyState.h"
#include "../../headers/game_states/ServerLobbyState.h"
#include "../../headers/network/ClientManager.h"
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

	m_error_label.setString("");
	m_error_label.setCharacterSize(40);
	m_error_label.setOutlineColor(sf::Color::Black);
	m_error_label.setFillColor(sf::Color::Red);
	m_error_label.setPosition(m_window->getSize().x / 2 - m_error_label.getGlobalBounds().width / 2,
	                          m_window->getSize().y / 2 - m_error_label.getGlobalBounds().height / 2 + 110);
}

void MenuState::handleEvent(const sf::Event &event) {
	try {
		m_name_input_field.handleEvent(event);
	} catch (WrongCharacterEnteredException err) {
		std::cout << err.getError() << '\n';
		m_error_label.setString(err.getError());
	}
	if (playBtn)
		if (playBtn->handleEvent(event))
			return;
	if (hostBtn)
		if (hostBtn->handleEvent(event))
			return;
}

void MenuState::render() {
	m_window->draw(grid);
	m_window->draw(m_name_input_field);
	m_window->draw(m_error_label);
	m_window->draw(*playBtn);
	m_window->draw(*hostBtn);
}

void MenuState::update(const sf::Time &deltaTime) {
	m_name_input_field.update(deltaTime);
	m_error_label.setPosition(m_window->getSize().x / 2 - m_error_label.getGlobalBounds().width / 2,
	                          m_window->getSize().y / 2 - m_error_label.getGlobalBounds().height / 2 + 110);
}

void MenuState::host() {
	// auto server_manager = std::make_unique<ServerManager>();
	try {
		ServerManager::getInstance().tryBind();

		auto lobby_state = std::make_unique<ServerLobbyState>(m_game_state_manager, m_window,
		                                                      m_name_input_field.getText());
		m_game_state_manager->transitionTo(std::move(lobby_state));
		// m_game_state_manager->enqueueState(std::move(lobby_state));
	} catch (AlreadyHostingExeption &e) {
		std::cout << e << '\n';
		m_error_label.setString(e.getError());
	}
}

void MenuState::play() {
	try {
		ClientManager::getInstance().tryConnect();

		auto lobby_state = std::make_unique<ClientLobbyState>(m_game_state_manager, m_window,
		                                                      m_name_input_field.getText());

		// m_game_state_manager->enqueueState(std::move(lobby_state));
		m_game_state_manager->transitionTo(std::move(lobby_state));
	} catch (NoHostFoundException &e) {
		std::cout << e << '\n';
		m_error_label.setString(e.getError());
	}
}

MenuState::~MenuState() = default;
