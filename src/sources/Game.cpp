//
// Created by stefantacu on 07.03.2024.
//
#include "../headers/Game.hpp"
#include <SFML/Graphics.hpp>
#include "../headers/game_states/MenuState.hpp"
#include "../headers/ui/AssetManager.h"

Game::Game() : m_game_state_manager(new GameStateManager()),
               m_window(sf::VideoMode(1280, 720), "Agar.io") {
	// m_window("Chapter 2", sf::Vector2u(1280, 720)) {

	AssetManager::initialize();
	m_window.setFramerateLimit(60);
	m_game_state_manager->transitionTo(std::make_unique<MenuState>(m_game_state_manager, &m_window));
};

Game::~Game() = default;

void Game::handleEvent(const sf::Event &event) const {
	m_game_state_manager->handleEvent(event);
}

void Game::handleInput() {
}

void Game::update() {
	m_game_state_manager->update(m_elapsed);
}

void Game::render() {
}

sf::Time Game::getElapsed() const { return m_elapsed; }

void Game::restartClock() { m_elapsed = m_clock.restart(); }

void Game::start() {
	while (m_window.isOpen()) {
		sf::Event event{};
		m_game_state_manager->receiveData();

		while (m_window.pollEvent(event)) {
			m_game_state_manager->handleEvent(event);

			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		m_window.clear(sf::Color::White);
		m_game_state_manager->update(m_elapsed);
		m_game_state_manager->render();
		m_game_state_manager->sendData();
		m_window.display();

		restartClock();
	}
}

