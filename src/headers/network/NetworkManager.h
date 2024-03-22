//
// Created by stefantacu on 16.03.2024.
//

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include <memory>
#include "ClientManager.h"
#include "ServerManager.h"
#include "../utils/Signal.h"

class GameStateManager;
class GameState;
class ServerManager;
class ClientManager;

enum NetworkManagerState {
    ServerState,
    ClientState
};

class NetworkManager {
private:
    GameState *m_game_state;

public:
    explicit NetworkManager(NetworkManagerState state);

    void disconnect();

    void receiveData();

    void sendData();
};


#endif //NETWORKMANAGER_H
