//
// Created by stefantacu on 14.03.2024.
//

#pragma once
#include <queue>

#include "State.hpp"
#include "../Command.h"
#include "../World.hpp"
#include "SFML/Graphics/Text.hpp"


class GameState :
		public State {
private:
	World m_world;
	sf::RenderStates m_render_states;
	bool gameEnd = false;
	std::queue<std::unique_ptr<Command> > m_command_queue;
	// sf::Text endText;

	// void handleEnemyMove(sf::Packet &packet);
	//
	// void handlePutBomb(sf::Packet &packet);
	//
	// void handleExplosion(sf::Packet &packet);
	//
	// void handleTp(sf::Packet &packet);

	// void endGame(PlayerGameState gameEndState);

	// void gameEndEventHandle(const sf::Event &event);

public:
	GameState(GameStateManager *manager, sf::RenderWindow *window);

	void handleEvent(const sf::Event &event) override;

	void render() override;

	void update(const sf::Time &deltaTime) override;

	~GameState();

	void handlePlayerJoined(std::string &id);

	void handlePlayerPosition(std::string &id, sf::Vector2f vector2);

	void handleConnected(std::map<std::string, std::unique_ptr<OnlinePlayerData> > &map);

	void handlePlayerDisconected(const std::string &id);

	void addCommand(std::unique_ptr<Command> command);
};



