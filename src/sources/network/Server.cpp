//
// Created by stefantacu on 15.03.2024.
//

#include "../../headers/network/Server.h"

#include <iostream>


Server::Server() {
	m_socket.bind(50000);
	m_socket.setBlocking(false);
	std::cout << "server started" << "\n";
}

int count = 0;

void Server::start() {
	// while (true) {
	m_packet.clear();
	sf::IpAddress sender;
	unsigned short port;
	std::string type = "";

	if (m_socket.receive(m_packet, sender, port) == sf::Socket::Done) {
		// m_packet >> type;
		std::cout << sender << ' ' << count++ << "\n";
	}
	// }
}

Server::~Server() {
}
