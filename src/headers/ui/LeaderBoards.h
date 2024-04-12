//
// Created by stefantacu on 10.04.2024.
//

#ifndef LEADERBOARDS_H
#define LEADERBOARDS_H
#include "Label.h"
#include "LeaderBoardsLabel.h"
#include "../SceneNode.hpp"
#include "../network/OnlinePlayerData.h"

class PlayersManager;

class LeaderBoards : public SceneNode {
private:
    sf::RectangleShape m_background;
    std::map<std::string, const OnlinePlayerData *> m_players;
    std::vector<LeaderBoardsLabel> m_player_labels;
    std::vector<OnlinePlayerData> m_players_data;
    PlayersManager *m_players_manager;

public:
    LeaderBoards(GameStateManager *manager, sf::RenderWindow *window,
                 const std::map<std::string, OnlinePlayerData> &players_data, const std::string &name = "Leaderboards");

    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    void handlePlayerDataReceived(const OnlinePlayerData &player_data);

    void setPlayersManager(PlayersManager *players_manager);
};


#endif //LEADERBOARDS_H
