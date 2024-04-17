//
// Created by stefantacu on 22.03.2024.
//

#include "../../headers/ui/LobbyPlayerLabels.h"
#include "../../headers/network/OnlinePlayerData.h"
#include "../../headers/ui/LobbyPlayerLabel.h"

void LobbyPlayerLabels::handleEventCurrent(const sf::Event &event) {
}

void LobbyPlayerLabels::updateCurrent(const sf::Time &delta) {
}

void LobbyPlayerLabels::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    int pos = 2;
    for (auto &pair: m_player_lobby_labels) {
        auto &label = pair.second;
        label->setPosition(100, 100 * pos);
        target.draw(*label);
        pos++;
    }
}

void LobbyPlayerLabels::setCurrentPlayers(const std::map<std::string, OnlinePlayerData> &player_data) {
    for (auto &data: player_data) {
        m_player_lobby_labels[data.first] = std::make_unique<LobbyPlayerLabel>(
            m_game_state_manager, m_window, data.second.name + " " + data.first);
    }
}

void LobbyPlayerLabels::addPlayer(const OnlinePlayerData &player) {
    m_player_lobby_labels[player.id] = std::make_unique<LobbyPlayerLabel>(
        m_game_state_manager, m_window, player.name + " (" + player.id + ")");
}
