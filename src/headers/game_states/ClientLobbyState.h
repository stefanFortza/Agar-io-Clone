//
// Created by stefantacu on 20.03.2024.
//

#ifndef CLIENTLOBBYSTATE_H
#define CLIENTLOBBYSTATE_H
#include "LobbyState.h"
#include "../Grid.hpp"
#include "../ui/LobbyPlayerLabels.h"
#include "../ui/Label.h"


class ClientLobbyState : public LobbyState {
private:
    Label m_lobby_label;
    std::unique_ptr<LobbyPlayerLabels> m_player_labels;
    Grid m_grid;

public:
    ClientLobbyState(GameStateManager *manager, sf::RenderWindow *window, std::string name);

    void handleEvent(const sf::Event &event) override;

    void render() override;

    void update(const sf::Time &deltaTime) override;

    void onJoinLobby(const std::map<std::string, OnlinePlayerData> &player_data);

    void onPlayerJoinedLobby(const OnlinePlayerData &player);

    void onGameStarted(const std::map<std::string, OnlinePlayerData> &player_data);
};


#endif //CLIENTLOBBYSTATE_H
