//
// Created by stefantacu on 14.03.2024.
//

#pragma once
#include "State.hpp"
#include "../Command.h"
#include "../Grid.hpp"
// #include "../World.hpp"
#include "../PlayerCamera.hpp"
#include "../player/PlayersManager.h"

class PlayersManager;

class GameState :
		public State {
protected:
	std::unique_ptr<PlayersManager> m_players_manager;
	Grid m_grid;
	PlayerCamera m_player_camera;
	const std::map<std::string, OnlinePlayerData> &players_data;
	bool gameEnd = false;

public:
	GameState(GameStateManager *manager, sf::RenderWindow *window,
	          const std::map<std::string, OnlinePlayerData> &players_data);


	~GameState();
};



