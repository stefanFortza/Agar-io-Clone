//
// Created by stefantacu on 16.03.2024.
//

#include "../../headers/network/NetworkManager.h"


void NetworkManager::disconnect() {
    // if (isServer()) {
    //     // m_server->disconnect();
    // } else {
    //     m_client->disconnect();
    // }
}

void NetworkManager::receiveData() {
    if (ServerManager::getInstance().isRunning()) {
        ServerManager::getInstance().receiveData();
    } else if (ClientManager::getInstance().isRunning()) {
        ClientManager::getInstance().receiveData();
    }
}

void NetworkManager::sendData() {
    // if (isServer()) {
    //     m_server->sendData();
    // } else {
    // }
}
