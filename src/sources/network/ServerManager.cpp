//
// Created by stefantacu on 15.03.2024.
//

#include "../../headers/network/ServerManager.h"

#include <iostream>
#include "../../headers/utils/Signal.h"
#include "../../headers/network/NetworkManager.h"
#include "../../headers/network/OnlinePlayerData.h"
#include "../../headers/utils/Utils.h"


ServerManager &ServerManager::getInstance() {
	static ServerManager instance;
	return instance;
}

ServerManager::ServerManager(): m_running(false) {
}


const std::map<std::string, OnlinePlayerData> &ServerManager::getConnectedPlayers() const {
	return m_connected_players;
}

const std::string &ServerManager::getServerId() const {
	return m_server_id;
}

int count = 0;

void ServerManager::start() {
	// Set is running
	m_running = true;
	m_socket.bind(50000);
	m_socket.setBlocking(false);

	m_server_id = NetworkUtils::getIdFromAdressAndPort(sf::IpAddress::getLocalAddress(), 50000);

	m_connected_players.emplace(std::piecewise_construct,
	                            std::forward_as_tuple(m_server_id),
	                            std::forward_as_tuple(m_server_id));

	onPlayerJoinedLobby.emit(m_connected_players[m_server_id]);

	std::cout << "server started" << "\n";
}


void ServerManager::receiveData() {
	m_packet.clear();
	sf::IpAddress sender;
	unsigned short port;

	while (m_socket.receive(m_packet, sender, port) == sf::Socket::Done) {
		int type;
		auto id = NetworkUtils::getIdFromAdressAndPort(sender, port);
		m_packet >> type;

		switch (static_cast<PacketType>(type)) {
			// only for client
			case OnlinePlayersData:
			case ConnectedToLobby:
				break;
			case PlayerPosition: {
				float x, y;
				m_packet >> x >> y;

				if (m_connected_players.count(id)) {
					// m_game_state->handlePlayerPosition(id, sf::Vector2f(x, y));
				}
				break;
			}
			case PlayerJoinedLobby:
				handlePlayerJoinedLobby(id);
				break;

			// Broadcast to all players a player disconnected
			case PlayerDisconected: {
				if (id != m_server_id) {
					sf::Packet packet;
					packet << PlayerDisconected << id;
					m_connected_players.erase(id);
					// delete m_connected_players[id];
					// m_game_state->handlePlayerDisconected(id);
					broadCastToOnlinePlayersAndServer(packet);
				}
				break;
			}
			case HeartBeat:
				break;
			case PlayerData: {
				OnlinePlayerData data;
				m_packet >> data;
				handlePlayerData(data);
				break;
			}

			case GameStarted:
				break;
		}
	}
}

void ServerManager::sendData() {
}

void ServerManager::handlePlayerJoinedLobby(std::string id) {
	std::cout << "Player connected to server\n";
	std::cout << id << ' ' << count++ << "\n";

	// HeartBeat
	sf::Packet packet;
	packet << HeartBeat << id;
	sendPacket(packet, id);

	// add player to map
	// OnlinePlayerData player_data_that_joined(id);
	m_connected_players.emplace(std::piecewise_construct,
	                            std::forward_as_tuple(id),
	                            std::forward_as_tuple(id));

	onPlayerJoinedLobby.emit(m_connected_players[id]);

	// Broadcast to online players a player joined the lobby
	packet.clear();
	packet << PlayerJoinedLobby << m_connected_players[id];

	broadCast(packet, id);

	// Tell connected player current lobby data
	sf::Packet packet_for_current_player;
	packet_for_current_player << ConnectedToLobby << static_cast<int>(m_connected_players.size());
	for (auto &connected_player: m_connected_players)
		packet_for_current_player << connected_player.second;

	sendPacket(packet_for_current_player, id);
}

void ServerManager::handlePlayerData(const OnlinePlayerData &data) {
	onPlayerDataReceived.emit(data);

	m_packet.clear();
	m_packet << PlayerData << data;
	broadCast(m_packet, data.id);
}

void ServerManager::setCurrentServerPlayerData(float x, float y) {
	// m_connected_players[getId(sf::IpAddress::getLocalAddress(), 50000)]->setXY(x, y);
}

// Start the game from lobby state
void ServerManager::startGame() {
	sf::Packet packet;
	packet << GameStarted;
	broadCast(packet);
	onGameStarted.emit(m_connected_players);
}

void ServerManager::broadCastLocalData(const OnlinePlayerData &data) {
	m_packet.clear();
	m_packet << PlayerData << data;
	broadCast(m_packet);
}

void ServerManager::broadCastFoodSpawned(sf::Vector2f pos) {
	m_packet.clear();
	m_packet << FoodSpawned << pos;
	broadCast(m_packet);
}

void ServerManager::broadcastFoodEaten(OnlinePlayerData data, Food *food) {
	m_packet.clear();
	m_packet << FoodEaten << food->getId() << data;
	broadCast(m_packet);
}

void ServerManager::sendPacket(sf::Packet &packet, const std::string &id) {
	std::string delimiter = ":";
	auto adress = id.substr(0, id.find(delimiter));
	auto port = id.substr(id.find(delimiter) + 1);
	m_socket.send(packet, adress, std::stoi(port));
}

bool ServerManager::isRunning() const {
	return m_running;
}

// Send a packet to all players including server
void ServerManager::broadCastToOnlinePlayersAndServer(sf::Packet &packet) {
	for (const auto &pair: m_connected_players)
		sendPacket(packet, pair.first);
}

// Send a packet to all players without server and without id specified
void ServerManager::broadCast(sf::Packet &packet, const std::string &id_to_ignore) {
	for (const auto &pair: m_connected_players)
		if (pair.first != m_server_id && pair.first != id_to_ignore)
			sendPacket(packet, pair.first);
}

// Send a packet to all players
void ServerManager::broadCastToOnlinePlayersWithoutServer(sf::Packet &packet) {
	for (const auto &pair: m_connected_players)
		if (pair.first != m_server_id)
			sendPacket(packet, pair.first);
}

ServerManager::~ServerManager() {
}

