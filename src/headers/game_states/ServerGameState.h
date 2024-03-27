//
// Created by stefantacu on 23.03.2024.
//

#ifndef SERVERGAMESTATE_H
#define SERVERGAMESTATE_H
#include "GameState.h"


class ServerGameState : public GameState {
public:
	ServerGameState(GameStateManager *manager, sf::RenderWindow *window,
	                const std::map<std::string, OnlinePlayerData> &players_data);

	void handleEvent(const sf::Event &event) override;

	void render() override;

	void update(const sf::Time &deltaTime) override;

	// void handlePlayerJoined(std::string &id);

	// void handlePlayerPosition(std::string &id, sf::Vector2f vector2);

	// void handleConnected(std::map<std::string, std::unique_ptr<OnlinePlayerData> > &map);

	void handlePlayerDisconected(const std::string &id);
};


#endif //SERVERGAMESTATE_H
