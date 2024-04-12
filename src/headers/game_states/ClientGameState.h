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

    void onPlayerDataReceived(const OnlinePlayerData &player_data);

    void onFoodSpawned(sf::Vector2f pos);

    void onFoodEaten(OnlinePlayerData data, int id);

    void onPlayerEaten(const OnlinePlayerData &player1, const OnlinePlayerData &player2);


    void onPlayerDisconnected(const std::string &id);
};


#endif //CLIENTGAMESTATE_H
