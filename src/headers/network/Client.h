//
// Created by stefantacu on 15.03.2024.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <memory>

#include "Server.h"
#include "../../../cmake-build-debug/_deps/sfml-src/include/SFML/Network/UdpSocket.hpp"
#include "SFML/Network/Packet.hpp"


class GameState;
class OnlinePlayerData;

class Client {
    sf::UdpSocket m_socket;
    sf::Packet m_packet;
    GameState *m_game_state;
    std::map<std::string, std::unique_ptr<OnlinePlayerData> > m_online_players;
    std::string m_client_id;

public:
    std::string getClientId();

    void disconnect();

    Client(GameState *game_state);

    void start();

    void receivePackets();

    void sendPacket(sf::Packet &packet);
};


#endif //CLIENT_H
