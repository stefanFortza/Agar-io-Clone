//
// Created by stefantacu on 16.03.2024.
//

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include <memory>
#include "Client.h"
#include "Server.h"

class GameStateManager;
class GameState;
class Server;
class Client;


class NetworkManager {
private:
    GameStateManager *m_game_state_manager;
    bool m_is_server{};
    std::unique_ptr<Client> m_client;

public:
    Client *getClient();

    Server *getServer();

    void disconnect();

private:
    std::unique_ptr<Server> m_server;
    GameState *m_game_state;

public:
    explicit NetworkManager(GameStateManager *manager, bool is_server, GameState *game_state);

    bool isServer() const;

    void receiveData();

    void sendData();
};


#endif //NETWORKMANAGER_H
