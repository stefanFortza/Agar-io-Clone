//
// Created by stefantacu on 16.03.2024.
//

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include <string>

class GameStateManager;
class GameState;
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

    static void setLocalId(const std::string &id);

    static std::string &getLocalId();

    static std::string m_local_id;
};


#endif //NETWORKMANAGER_H
