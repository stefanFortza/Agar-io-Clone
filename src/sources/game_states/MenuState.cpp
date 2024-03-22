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
                                                playBtn([this] { play(); }),
                                                hostBtn([this] { host(); }) {
	playBtn.setString("Play");
	playBtn.setCharacterSize(50);
	playBtn.setPosition(m_window->getSize().x / 2 - playBtn.getGlobalBounds().width / 2 + 100,
	                    m_window->getSize().y / 2 - playBtn.getGlobalBounds().height / 2);


	hostBtn.setString("Host");
	hostBtn.setCharacterSize(50);
	hostBtn.setPosition(m_window->getSize().x / 2 - playBtn.getGlobalBounds().width / 2 - 100,
	                    m_window->getSize().y / 2 - playBtn.getGlobalBounds().height / 2);
}

void MenuState::handleEvent(const sf::Event &event) {
	playBtn.handleEvent(event);
	hostBtn.handleEvent(event);
}

void MenuState::render() {
	m_window->draw(playBtn);
	m_window->draw(hostBtn);
	// window->draw(playBtn);
}

void MenuState::update(const sf::Time &/*deltaTime*/) {
}

void MenuState::host() {
	// auto server_manager = std::make_unique<ServerManager>();
	auto lobby_state = std::make_unique<ServerLobbyState>(m_game_state_manager, m_window);
	m_game_state_manager->setState(std::move(lobby_state));
}

void MenuState::play() {
	auto lobby_state = std::make_unique<ClientLobbyState>(m_game_state_manager, m_window);
	m_game_state_manager->setState(std::move(lobby_state));
}

MenuState::~MenuState() = default;
