//
// Created by stefantacu on 15.03.2024.
//

#include "../../headers/server/Server.h"

#include <iostream>


Server::Server() = default;

void Server::start() {
	m_socket.bind(50001);
	std::cout << "server started" << "\n";

	// while (true) {
	m_packet.clear();

	sf::IpAddress sender;
	unsigned short port;
	std::string type = "";

	if (m_socket.receive(m_packet, sender, port) == sf::Socket::Done) {
		m_packet >> type;
		std::cout << sender << std::endl;
	}
	// }
}

Server::~Server() {
}
