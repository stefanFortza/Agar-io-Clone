//
// Created by stefantacu on 14.03.2024.
//

#include "../../headers/game_states/GameState.h"

GameState::GameState(GameStateManager *manager,
                     sf::RenderWindow *window,
                     const std::map<std::string, OnlinePlayerData> &players_data): State(manager, window),
    m_players_manager(nullptr), m_grid(manager, window),
    players_data(players_data), m_player_camera(manager, window),
    m_food_manager(manager, window) {
}


GameState::~GameState() = default;

