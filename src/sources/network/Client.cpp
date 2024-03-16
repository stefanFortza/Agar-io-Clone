//
// Created by stefantacu on 15.03.2024.
//

#include "../../headers/network/Client.h"

Client::Client() {
   m_socket.bind(50001);
   m_socket.setBlocking(false);
}

void Client::start() {
   std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
   m_socket.send(message.c_str(), message.size() + 1, "127.0.0.1", 50000);
}
