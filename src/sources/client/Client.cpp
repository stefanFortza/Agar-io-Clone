//
// Created by stefantacu on 15.03.2024.
//

#include "../../headers/client/Client.h"
#include <SFML/Network/IpAddress.hpp>

Client::Client() = default;

void Client::start() {
   m_socket.bind(50001);
   std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
   m_socket.send(message.c_str(), message.size() + 1, "127.0.0.1", 55001);
}
