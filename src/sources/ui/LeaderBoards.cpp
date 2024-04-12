//
// Created by stefantacu on 10.04.2024.
//

#include "../../headers/ui/LeaderBoards.h"

#include "../../headers/ui/LeaderBoardsLabel.h"
#include "../../headers/player/PlayersManager.h"

LeaderBoards::LeaderBoards(GameStateManager *manager, sf::RenderWindow *window,
                           const std::map<std::string, OnlinePlayerData> &players_data,
                           const std::string &name): SceneNode(
                                                         manager, window, name), m_players_manager(nullptr) {
    m_background.setSize(sf::Vector2f(300, 500));
    m_background.setFillColor(sf::Color(2, 48, 71, 130));
    m_background.setPosition(30, 30);

    for (size_t i = 0; i < players_data.size(); i++) {
        m_player_labels.emplace_back();
    }
}

void LeaderBoards::handleEventCurrent(const sf::Event &) {
}

bool comparePlayers(const OnlinePlayerData &p1, const OnlinePlayerData &p2) {
    return p1.size > p2.size;
}

void LeaderBoards::updateCurrent(const sf::Time &) {
    if (m_players_manager) {
        m_players_data = m_players_manager->getPlayersData();

        std::sort(m_players_data.begin(), m_players_data.end(), comparePlayers);

        int i = 0;
        for (auto &player_label: m_player_labels) {
            if (i == 5)break;
            player_label.setPlayer(m_players_data[i], i);
            player_label.setPosition(75, 50 + 100 * i);
            i++;
        }
    }
}

void LeaderBoards::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_background);
    for (auto &player_label: m_player_labels) {
        target.draw(player_label, states);
    }
}

void LeaderBoards::handlePlayerDataReceived(const OnlinePlayerData &player_data) {
    m_players[player_data.id] = &player_data;
}

void LeaderBoards::setPlayersManager(PlayersManager *players_manager) {
    m_players_manager = players_manager;
}
