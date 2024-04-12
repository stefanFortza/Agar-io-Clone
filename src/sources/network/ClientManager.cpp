//
// Created by stefantacu on 15.03.2024.
//

#include "../../headers/network/ClientManager.h"

#include <iostream>

#include "../../headers/utils/Utils.h"
#include "SFML/Network/Packet.hpp"

ClientManager::ClientManager(): m_is_running(false) {
}

void ClientManager::start(std::string name) {
	// Set server is running
	m_is_running = true;

	int port = 50001;
	sf::Socket::Status status = m_socket.bind(50001);
	m_socket.setBlocking(false);
	while (status != sf::Socket::Done) {
		port++;
		status = m_socket.bind(port);
	}
	std::cout << "bound to port: " << port << '\n';
	m_client_id = NetworkUtils::getIdFromAdressAndPort(sf::IpAddress::getLocalAddress().toString(), port);
	NetworkManager::setLocalId(m_client_id);

	sf::Packet packet;
	std::string type = "connected";

	// Tell server i joined
	packet << PlayerJoinedLobby << name;
	m_socket.send(packet, "127.0.0.1", 50000);
}


std::string ClientManager::getClientId() {
	return m_client_id;
}

void ClientManager::disconnect() {
	sf::Packet packet;
	packet << PlayerDisconected << m_online_players.at(NetworkManager::getLocalId());
	this->sendPacketToServer(packet);
	// m_socket.send(packet, "127.0.0.1", 50000);
}


ClientManager &ClientManager::getInstance() {
	static ClientManager instance;
	return instance;
}


void ClientManager::receiveData() {
	m_packet.clear();
	sf::IpAddress sender;
	unsigned short port;

	while (m_socket.receive(m_packet, sender, port) == sf::Socket::Done) {
		int type;
		m_packet >> type;
		switch (static_cast<PacketType>(type)) {
			case HeartBeat: {
				m_packet >> m_client_id;
				NetworkManager::setLocalId(m_client_id);
				break;
			}
			case ConnectedToLobby:
				handleJoinedLobby(m_packet);
				break;
			case PlayerPosition: {
				break;
			}
			// When a player joins the current server
			case PlayerJoinedLobby: {
				handlePlayerJoinedLobby(m_packet);
				break;
			}
			case OnlinePlayersData: {
				break;
			}
			case PlayerDisconected: {
				std::string id;
				m_packet >> id;
				handlePlayerDisconnected(id);
				// delete m_online_players[id];
				// m_game_state->handlePlayerDisconected(id);
				break;
			}
			case GameStarted:
				handleGameStarted();
				break;

			case PlayerData: {
				OnlinePlayerData data;
				m_packet >> data;
				onPlayerDataReceived.emit(data);
				break;
			}
			case FoodSpawned: {
				sf::Vector2f pos;
				m_packet >> pos;
				handleFoodSpawned(pos);
				break;
			}
			case FoodEaten: {
				int id;
				OnlinePlayerData data;
				m_packet >> id >> data;
				handleFoodEaten(data, id);
				break;
			}
			case PlayerEaten: {
				OnlinePlayerData player1, player2;
				m_packet >> player1 >> player2;
				handlePlayerEaten(player1, player2);
				break;
			}
			default: ;
		}
		m_packet.clear();
	}
}

void ClientManager::sendLocalDataToServer(OnlinePlayerData data) {
	m_packet.clear();
	m_packet << PlayerData << data;
	sendPacketToServer(m_packet);
}

void ClientManager::handlePlayerJoinedLobby(sf::Packet &packet) {
	OnlinePlayerData player_data;
	packet >> player_data;
	std::cout << player_data.id << " joined\n";
	m_online_players[player_data.id] = player_data;
	onPlayerJoinedLobby.emit(player_data);
}

void ClientManager::handleGameStarted() {
	onGameStarted.emit(m_online_players);
}

void ClientManager::handleFoodSpawned(sf::Vector2f pos) {
	onFoodSpawned.emit(pos);
}

void ClientManager::handleFoodEaten(OnlinePlayerData data, int id) {
	onFoodEaten.emit(data, id);
}

void ClientManager::handlePlayerEaten(const OnlinePlayerData &player1, const OnlinePlayerData &player2) {
	onPlayerEaten.emit(player1, player2);
}

void ClientManager::handlePlayerDisconnected(const std::string &id) {
	onPlayerDisconnected.emit(id);
}

void ClientManager::sendData() {
}

void ClientManager::handleJoinedLobby(sf::Packet &packet) {
	int i;
	packet >> i;
	std::cout << "Connected! Got lobby data\n" << i;
	while (i) {
		OnlinePlayerData player_data;
		packet >> player_data;
		m_online_players[player_data.id] = player_data;
		i--;
	}
	onJoinedLobby.emit(m_online_players);
}

bool ClientManager::isRunning() const {
	return m_is_running;
}

void ClientManager::sendPacketToServer(sf::Packet &packet) {
	m_socket.send(packet, "127.0.0.1", 50000);
}
