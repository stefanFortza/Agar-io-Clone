//
// Created by stefantacu on 15.03.2024.
//

#include "../../headers/network/Server.h"

#include <iostream>

#include "../../headers/network/NetworkManager.h"


Server::Server(GameState *game_state): m_game_state(game_state) {
	m_socket.bind(50000);
	m_socket.setBlocking(false);

	auto id = getId(sf::IpAddress::getLocalAddress(), 50000);
	std::unique_ptr<OnlinePlayerData> player = std::make_unique<
		OnlinePlayerData>(sf::IpAddress::getLocalAddress(), 50000);

	m_connected_players[id] = std::move(player);
	std::cout << "server started" << "\n";
}

std::string Server::getId(sf::IpAddress sender, unsigned short port) {
	std::string id(sender.toString());
	id += ":";
	id += std::to_string(port);

	return id;
}

int count = 0;

void Server::start() {
	// while (true) {
	m_packet.clear();
	sf::IpAddress sender;
	unsigned short port;
	// std::string type = "";

	while (m_socket.receive(m_packet, sender, port) == sf::Socket::Done) {
		int type;
		auto id = Server::getId(sender, port);
		m_packet >> type;

		switch (static_cast<PacketType>(type)) {
			case Connected: {
				std::cout << "Player connected to server\n";
				std::cout << type << ' ' << sender << ' ' << port << ' ' << count++ << "\n";
				std::unique_ptr<OnlinePlayerData> player = std::make_unique<OnlinePlayerData>(sender, port);

				// Tell connected player current game data
				sf::Packet packet_for_current_player;
				packet_for_current_player << OnlinePlayersData;
				packet_for_current_player << static_cast<int>(m_connected_players.size());

				// Tell other players a player has joined
				for (const auto &pair: m_connected_players) {
					auto &online_player = pair.second;
					if (online_player->getId() != getId(sf::IpAddress::getLocalAddress(), 50000)) {
						// sf::Packet packet = online_player->getPacket(PlayerJoinedServer);
						sf::Packet packet;
						online_player->getPacket(PlayerJoinedServer, packet);

						m_socket.send(packet, online_player->ip_address, online_player->port);
						std::cout << online_player->ip_address << online_player->port << "\n";
					}

					// packet_for_current_player << online_player->getPacket(OnlinePlayersData);
					online_player->getPacket(OnlinePlayersData, packet_for_current_player);
				}

				m_socket.send(packet_for_current_player, sender, port);

				m_connected_players[id] = std::move(player);
				m_game_state->handlePlayerJoined(id);
				break;
			}
			case PlayerPosition: {
				float x, y;
				m_packet >> x >> y;
				m_game_state->handlePlayerPosition(id, sf::Vector2f(x, y));
				break;
			}
			case PlayerJoinedServer: {
				std::cout << "Player connected to server\n";
				std::cout << type << ' ' << sender << ' ' << port << ' ' << count++ << "\n";
				std::unique_ptr<OnlinePlayerData> player = std::make_unique<OnlinePlayerData>(sender, port);

				// Tell connected player current game data
				sf::Packet packet_for_current_player;
				packet_for_current_player << Connected;
				packet_for_current_player << static_cast<int>(m_connected_players.size());

				// Tell other players a player has joined
				for (const auto &pair: m_connected_players) {
					auto &online_player = pair.second;
					if (online_player->getId() != getId(sf::IpAddress::getLocalAddress(), 50000)) {
						sf::Packet packet;
						online_player->getPacket(PlayerJoinedServer, packet);

						m_socket.send(packet, online_player->ip_address, online_player->port);
						std::cout << online_player->ip_address << online_player->port << "\n";
					}

					online_player->getPacket(Connected, packet_for_current_player);
				}

				m_socket.send(packet_for_current_player, sender, port);

				m_connected_players[id] = std::move(player);
				m_game_state->handlePlayerJoined(id);
				break;
			}
			case OnlinePlayersData:
				break;
		}
	}
	// }
}

void Server::sendData() {
}

// Send a packet to all players
void Server::broadCastToOnlinePlayers(sf::Packet &packet) {
	for (const auto &pair: m_connected_players) {
		auto &online_player = pair.second;
		m_socket.send(packet, online_player->ip_address, online_player->port);
	}
}

void Server::setCurrentPlayerData(float x, float y) {
	m_connected_players[getId(sf::IpAddress::getLocalAddress(), 50000)]->x = x;
	m_connected_players[getId(sf::IpAddress::getLocalAddress(), 50000)]->y = y;
}

void Server::sendPacket(sf::Packet &packet, std::string &id) {
	std::string delimiter = ":";
	auto adress = id.substr(0, id.find(delimiter));
	auto port = id.substr(id.find(delimiter) + 1);
	m_socket.send(packet, adress, std::stoi(port));
}

Server::~Server() {
}
