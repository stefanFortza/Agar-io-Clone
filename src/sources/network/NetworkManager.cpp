//
// Created by stefantacu on 16.03.2024.
//

#include "../../headers/network/NetworkManager.h"
#include "../../headers/network/ServerManager.h"
#include "../../headers/network/ClientManager.h"

std::string NetworkManager::m_local_id;


void NetworkManager::setLocalId(const std::string &id) {
    NetworkManager::m_local_id = id;
}

std::string &NetworkManager::getLocalId() {
    return NetworkManager::m_local_id;
}
