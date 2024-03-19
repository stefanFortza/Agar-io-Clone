//
// Created by stefantacu on 16.03.2024.
//

#include "../../headers/network/NetworkManager.h"

Client *NetworkManager::getClient() {
    return m_client.get();
}

Server *NetworkManager::getServer() {
    return m_server.get();
}

void NetworkManager::disconnect() {
    if (isServer()) {
        // m_server->disconnect();
    } else {
        m_client->disconnect();
    }
}

NetworkManager::NetworkManager(GameStateManager *manager, const bool is_server,
                               GameState *game_state): m_game_state_manager(manager),
                                                       m_is_server(is_server),
                                                       m_game_state(game_state) {
    if (isServer()) {
        m_server = std::make_unique<Server>(game_state);
    } else {
        m_client = std::make_unique<Client>(game_state);
    }
}

bool NetworkManager::isServer() const {
    return m_is_server;
}

void NetworkManager::receiveData() {
    if (isServer()) {
        m_server->start();
    } else {
        m_client->receivePackets();
    }
}

void NetworkManager::sendData() {
    if (isServer()) {
        m_server->sendData();
    } else {
    }
}
