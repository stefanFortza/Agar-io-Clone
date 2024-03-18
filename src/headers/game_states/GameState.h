//
// Created by stefantacu on 14.03.2024.
//

#pragma once
#include "State.hpp"
#include "../World.hpp"
#include "SFML/Graphics/Text.hpp"


class GameState :
		public State {
private:
	// LocalPlayer localPlayer;
	// NetPlayer netPlayer;
	World m_world;
	bool gameEnd = false;
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
	GameState(GameStateManager *manager, sf::RenderWindow *window
	          // std::unique_ptr<sf::TcpSocket> server,
	          //          std::array<std::array<int, Level::MAP_WIDTH>, Level::MAP_HEIGHT> &logicArray,
	          //          sf::Vector2i localPlayerPosition, PlayerAppearance localPlayerAppearance,
	          //          sf::Vector2i netPlayerPosition, PlayerAppearance netPlayerAppearance
	);

	void handleEvent(const sf::Event &event) override;

	void render() override;

	void update(const sf::Time &deltaTime) override;

	~GameState();

	void handlePlayerJoined(std::string &id);

	void handlePlayerPosition(std::string &id, sf::Vector2f vector2);

	void handleConnected(std::map<std::string, std::unique_ptr<OnlinePlayerData>> &map);
};



