//
// Created by stefantacu on 13.03.2024.
//

#include "../../headers/game_states/State.hpp"


State::State(GameStateManager *manager, sf::RenderWindow *window): m_game_state_manager(manager), m_window(window) {
	m_roboto_font.loadFromFile("assets/roboto/Roboto-Light.ttf");
}

State::~State() = default;
