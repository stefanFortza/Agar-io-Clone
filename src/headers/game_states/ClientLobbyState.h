//
// Created by stefantacu on 20.03.2024.
//

#ifndef CLIENTLOBBYSTATE_H
#define CLIENTLOBBYSTATE_H
#include "LobbyState.h"
#include "../../sources/ui/LobbyPlayerLabels.h"
#include "../ui/Label.h"


class ClientLobbyState : public LobbyState {
private:
    Label m_lobby_label;
    std::unique_ptr<LobbyPlayerLabels> m_player_labels;

public:
    ClientLobbyState(GameStateManager *manager, sf::RenderWindow *window);

    void handleEvent(const sf::Event &event) override;

    void render() override;

    void update(const sf::Time &deltaTime) override;

    void onJoinLobby(const std::map<std::string, OnlinePlayerData> &player_data);

    void onPlayerJoinedLobby(const OnlinePlayerData &player);
};


#endif //CLIENTLOBBYSTATE_H
