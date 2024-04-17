//
// Created by stefantacu on 22.03.2024.
//

#ifndef LOBBYPLAYERLABELS_H
#define LOBBYPLAYERLABELS_H
#include "../SceneNode.hpp"
#include "../network/OnlinePlayerData.h"
#include "Label.h"
#include "LobbyPlayerLabel.h"


struct OnlinePlayerData;

class LobbyPlayerLabels : public SceneNode {
    std::map<std::string, std::unique_ptr<LobbyPlayerLabel> > m_player_lobby_labels;

public:
    LobbyPlayerLabels(GameStateManager *manager, sf::RenderWindow *window, const std::string &name = "Player labels")
        : SceneNode(manager, window, name) {
    }

    void setCurrentPlayers(const std::map<std::string, OnlinePlayerData> &player_data);

    void addPlayer(const OnlinePlayerData &player);

private:
    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //LOBBYPLAYERLABELS_H
