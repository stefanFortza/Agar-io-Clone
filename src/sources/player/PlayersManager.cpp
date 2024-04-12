//
// Created by stefantacu on 27.03.2024.
//

#include"../../headers/player/PlayersManager.h"
#include"../../headers/network/ClientManager.h"

PlayersManager::PlayersManager(GameStateManager *manager, sf::RenderWindow *window,
                               const std::map<std::string, OnlinePlayerData> &players_data,
                               const std::string &local_player_id,
                               const std::string &name): SceneNode(manager, window, name) {
    for (auto &player_pair: players_data) {
        if (player_pair.first == local_player_id) {
            m_player = std::make_unique<Player>(manager, window, player_pair.first, player_pair.second.name);
        } else {
            m_remote_players.emplace(std::piecewise_construct,
                                     std::forward_as_tuple(player_pair.first),
                                     std::forward_as_tuple(manager, window, player_pair.first,
                                                           player_pair.second.name));
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

OnlinePlayerData PlayersManager::getLocalPlayerData() {
    if (m_player)
        return m_player->getData();
    return OnlinePlayerData();
}

void PlayersManager::playerAteFood(const OnlinePlayerData &data) {
    if (ClientManager::getInstance().getClientId() == data.id)
        m_player->setData(data);
    else if (m_remote_players.contains(data.id))
        m_remote_players.at(data.id).setData(data);
}

void PlayersManager::playerAtePlayer(const OnlinePlayerData &player1, const OnlinePlayerData &player2) {
    if (NetworkManager::getLocalId() == player1.id) {
        m_player->setData(player1);
        m_player->eatPlayer(player2);
        m_remote_players.at(player2.id).die();
    } else if (NetworkManager::getLocalId() == player2.id) {
        // current player was eaten
        m_remote_players.at(player1.id).setData(player1);
        m_remote_players.at(player1.id).eatPlayer(player2);
        m_player->die();
    } else {
        m_remote_players.at(player1.id).setData(player1);
        m_remote_players.at(player1.id).eatPlayer(player2);
        m_remote_players.at(player2.id).die();
    }
}

void PlayersManager::disconnectPlayer(const std::string &id) {
    if (m_remote_players.contains(id))
        m_remote_players.erase(id);
}

void PlayersManager::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    if (m_player)
        target.draw(*m_player, states);
    for (auto &player_pair: m_remote_players) {
        target.draw(player_pair.second, states);
    }
}

void PlayersManager::setCamera(PlayerCamera *player_camera) {
    player_camera->setTarget(m_player.get());
}

void PlayersManager::handlePlayerDataReceived(const OnlinePlayerData &player_data) {
    if (m_remote_players.contains(player_data.id))
        m_remote_players.at(player_data.id).setData(player_data);
}

std::vector<Collidable *> PlayersManager::getCollidables() {
    std::vector<Collidable *> vec;
    vec.push_back(m_player.get());
    for (auto &pair: m_remote_players) {
        vec.push_back(&pair.second);
    }
    return vec;
}

std::vector<OnlinePlayerData> PlayersManager::getPlayersData() {
    std::vector<OnlinePlayerData> vec;
    vec.push_back(m_player->getData());
    for (auto &pair: m_remote_players) {
        vec.push_back(pair.second.getData());
    }
    return vec;
}
