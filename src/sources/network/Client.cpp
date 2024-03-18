//
// Created by stefantacu on 15.03.2024.
//

#include "../../headers/network/Client.h"

#include <iostream>

#include "../../headers/network/NetworkManager.h"
#include "SFML/Network/Packet.hpp"

const std::string &Client::getClientId() const {
	return m_client_id;
}

Client::Client(GameState *game_state): m_game_state(game_state), m_client_id() {
	int port = 50001;
	sf::Socket::Status status = m_socket.bind(50001);
	m_socket.setBlocking(false);
	while (status != sf::Socket::Done) {
		port++;
		status = m_socket.bind(port);
	}
	std::cout << "bound to port: " << port << '\n';
	m_client_id = sf::IpAddress::getLocalAddress().toString() + ":" + std::to_string(port);
	sf::Packet packet;
	std::string type = "connected";

	packet << PacketType::PlayerJoinedServer;
	// std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
	m_socket.send(packet, "127.0.0.1", 50000);
}

void Client::start() {
	// std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
	// for (int i = 1; i <= 10; i++)
	//     m_socket.send(message.c_str(), message.size() + 1, "127.0.0.1", 50000);
}

void Client::receivePackets() {
	m_packet.clear();
	sf::IpAddress sender;
	unsigned short port;
	// std::cout << "dsa";

	while (m_socket.receive(m_packet, sender, port) == sf::Socket::Done) {
		std::string id(sender.toString());
		id += std::to_string(port);
		int type;
		m_packet >> type;
		switch (static_cast<PacketType>(type)) {
			case Connected: {
				int i;
				m_packet >> i;
				std::cout << "Connected! Got players data\n" << i;
				while (i) {
					std::string id;
					float x, y;
					m_packet >> id >> x >> y;
					std::string delimiter = ":";
					auto adress = id.substr(0, id.find(delimiter));
					auto player_port = id.substr(id.find(delimiter) + 1, id.length() - 1);

					m_online_players[id] = std::make_unique<OnlinePlayerData>(
						sf::IpAddress(adress), stoi(player_port), x, y);;
					// players[id] = ConnectedPlayer(sf::IpAddress(adress), stoi(port), x, y);

					i--;
				}

				m_game_state->handleConnected(m_online_players);

				break;
			}
			case PlayerPosition: {
				float x, y;
				m_packet >> x >> y;
				m_game_state->handlePlayerPosition(id, sf::Vector2f(x, y));

				break;
			}
			case PlayerJoinedServer:
				std::cout << id << " joined\n";
				m_game_state->handlePlayerJoined(id);
				break;
			case OnlinePlayersData: {
				break;
			}
			default: ;
		}
		m_packet.clear();
	}
}

void Client::sendPacket(sf::Packet &packet) {
	m_socket.send(packet, "127.0.0.1", 50000);
}
