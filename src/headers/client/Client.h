//
// Created by stefantacu on 15.03.2024.
//

#ifndef CLIENT_H
#define CLIENT_H
#include "SFML/Network/UdpSocket.hpp"


class Client {
    sf::UdpSocket m_socket;

public:
    Client();

    void start();
};


#endif //CLIENT_H
