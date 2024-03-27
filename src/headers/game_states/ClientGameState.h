//
// Created by stefantacu on 23.03.2024.
//

#ifndef CLIENTGAMESTATE_H
#define CLIENTGAMESTATE_H
#include "GameState.h"


class ClientGameState : public GameState {
public:
    ClientGameState(GameStateManager *manager, sf::RenderWindow *window,
                    const std::map<std::string, OnlinePlayerData> &players_data);

private:
    void handleEvent(const sf::Event &event) override;

    void render() override;

    void update(const sf::Time &deltaTime) override;

    void handlePlayerDisconected(const std::string &id);
};


#endif //CLIENTGAMESTATE_H
