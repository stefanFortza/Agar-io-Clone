//
// Created by stefantacu on 27.03.2024.
//

#include"../../headers/player/PlayersManager.h"

PlayersManager::PlayersManager(GameStateManager *manager, sf::RenderWindow *window,
                               const std::map<std::string, OnlinePlayerData> &players_data,
                               const std::string &local_player_id,
                               const std::string &name): SceneNode(manager, window, name) {
    for (auto &player_pair: players_data) {
        if (player_pair.first == local_player_id) {
            m_player = std::make_unique<Player>(manager, window);
        } else {
            m_remote_players.emplace(std::piecewise_construct,
                                     std::forward_as_tuple(player_pair.first),
                                     std::forward_as_tuple(manager, window));
        }
    }
}

void PlayersManager::handleEventCurrent(const sf::Event &event) {
    if (m_player)
        m_player->handleEvent(event);
    for (auto &player_pair: m_remote_players) {
        player_pair.second.handleEvent(event);
    }
}

void PlayersManager::updateCurrent(const sf::Time &delta) {
    if (m_player)
        m_player->update(delta);
    for (auto &player_pair: m_remote_players) {
        player_pair.second.update(delta);
    }
}

void PlayersManager::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    if (m_player)
        target.draw(*m_player);
    for (auto &player_pair: m_remote_players) {
        target.draw(player_pair.second);
    }
}

void PlayersManager::setCamera(PlayerCamera &player_camera) {
    player_camera.setTarget(m_player.get());
}
